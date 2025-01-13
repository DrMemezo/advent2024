from sys import argv, exit 
from pathlib import Path

class Guard:
    OBSTACLE_SIGN = "#"
    GUARD_SIGN = "^"
    directions = [(-1, 0), (0, 1), (1, 0), (0,-1)] # Up, right, down, left
    current_direction = 0 # Indexes into directions

    def __init__(self, map:list[str]) -> None:
        self.visited = set()
        self.position:tuple[int,int]|None = None

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
        self.visited.add(self.position)
        
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

def main() -> None:
    if len(argv) != 2:
        exit("USAGE: python day6.py [FILE]")
    
    FILEPATH = Path(argv[1])
    if not FILEPATH.exists():
        exit(f"{FILEPATH} does not exist!")
    
    with open(FILEPATH, 'r') as file:
        contents = [line.strip() for line in file]
    
    guard = Guard(contents)

    while True:
        if not guard.progress():
            break
        

    print(f"Guard visited {len(guard.visited)} distinct positions") 


if __name__ == "__main__":
    main()