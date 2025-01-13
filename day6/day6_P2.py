from sys import argv, exit 
from pathlib import Path
from rich.progress import track


class Guard:
    OBSTACLE_SIGN = "#"
    GUARD_SIGN = "^"
    LOOP_LIMIT = 500
    directions = [(-1, 0), (0, 1), (1, 0), (0,-1)] # Up, right, down, left
    current_direction = 0 # Indexes into directions

    def __init__(self, map:list[str]) -> None:
        self.visited = set()
        self.revisited = set()
        self.position:tuple[int,int]|None = None
        self.revisit_count = 0

        self.map = map
        
        for x, row in enumerate(map):
            try:
                y = row.index(self.GUARD_SIGN)
            except ValueError:
                y = None
            else:
                break

        if y is None:
            raise Exception("Guard not found!")
        
        self.MAPSIZE = (len(map), len(map[0]))
        self.position = (x, y) 
                

    def turn(self):
        self.current_direction = (self.current_direction + 1) % 4
    
    def has_left(self, next_pos:tuple[int,int]|None=None) -> bool:
        """Checks if guard is still within the map"""
        if next_pos:
            x = 0 <= next_pos[0] < self.MAPSIZE[0] and 0 <= next_pos[1] < self.MAPSIZE[1]
            return not x

        x = 0 <= self.position[0] < self.MAPSIZE[0] and 0 <= self.position[1] < self.MAPSIZE[1]
        return not x
    
    def progress(self) -> bool:
        
        if self.position in self.visited:
            if self.position in self.revisited:
                self.revisit_count += 1
            else:
                self.revisited.add(self.position)
                self.revisit_count = 0
        else:
            self.visited.add(self.position)
            self.revisit_count = 0
        
        
        if self.has_left(self.get_new_position()):
            return False
        
        if self.is_facing_obstacle():
            self.turn()
        
        self.position = self.get_new_position()

        return True
    
    def is_facing_obstacle(self) -> bool:
        next_pos = self.get_new_position()

        if self.map[next_pos[0]][next_pos[1]] == self.OBSTACLE_SIGN:
            return True
        return False
    
    def get_new_position(self) -> tuple[int,int]|None:
        """Gets next position based on the direction of the guard,
        returns None if out of bounds"""
        new_x = self.position[0] + self.directions[self.current_direction][0]
        new_y = self.position[1] + self.directions[self.current_direction][1]
        return (new_x, new_y)

    def is_looped(self) -> bool:
        x = (self.visited == self.revisited) or self.revisit_count > len(self.revisited)
        return x 
    
    @classmethod
    def is_valid_position(cls, character):
        return (character != cls.GUARD_SIGN and character != cls.OBSTACLE_SIGN) 

def main() -> None:
    """Add an obstruction to the map so that the guard loops"""
    # * STEPS:
    # ? For every element in map, if it isn't the guard or an obstruction. place an obstruction
    # ? If the guard is in a loop, increment a counter
    # ? If the number of distinct places visited == non-distinct places visited, guard is stuck


    if len(argv) != 2:
        exit("USAGE: python day6.py [FILE]")
    
    FILEPATH = Path(argv[1])
    if not FILEPATH.exists():
        exit(f"{FILEPATH} does not exist!")
    
    with open(FILEPATH, 'r') as file:
        contents = [line.strip() for line in file]
    
    looped_counter = 0
    for x, row in track(enumerate(contents), description="Working..."):
        for y in range(len(row)):
            looped_counter += 1 if try_looped_map(contents, (x, y)) else 0
    
    print(f"{(x, y)}")
    print(f"Number of possible looped obstructions: {looped_counter}")


def try_looped_map(map:list[str], coordinates:tuple[int,int]) -> bool:
    x, y = coordinates
    
    if not Guard.is_valid_position(map[x][y]):
        return False
    
    # Change map(add obstruction)

    original_row = map[x]

    new_row = original_row[:y] + Guard.OBSTACLE_SIGN + original_row[y+1:]
    map[x] = new_row
    
    


    guard = Guard(map)

    while True:
        if not guard.progress():
            map[x] = original_row
            return False
        
        if guard.is_looped():
            map[x] = original_row
            return True
        




if __name__ == "__main__":
    main()