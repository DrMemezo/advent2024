from pathlib import Path
from sys import argv, exit

MAP = []
MAP_X_LEN:int
MAP_Y_LEN:int

class Antenna:
    global MAP

    def __init__(self, position:tuple[int, int], sign:str) -> None:
        self.position = position
        # if MAP[position[0]][position[1]] != sign:
        #     raise ValueError(f"Signs are different!\nSign given:{sign}\nSign on Map:{MAP[position[0]][position[1]]}")
        self.sign = sign

    def calc_distance(self, ant_pair:'Antenna') -> tuple[int, int]:
        if self.sign != ant_pair.sign:
            raise ValueError(f"Signs are not the same!")
        
        if self == ant_pair:
            raise ValueError(f"These are the same antenna")

        new_position = [0, 0]
        for index, pos in enumerate(self.position):
            new_position[index] = ant_pair.position[index] - pos
        
        return tuple(new_position)

    def __repr__(self):
        return f"<{self.sign}, {self.position}>"

    

def get_antennas() -> list[Antenna]:
    global MAP
    ants = [Antenna((row, col), MAP[row][col]) 
            for row, col in get_next_position() 
            if MAP[row][col] != '.']
    return ants


def get_next_position():
    global MAP
    for row_num, row in enumerate(MAP):
        for col in range(len(row)):
            yield (row_num, col)

def get_antinode_pos(base_pos:tuple[int,int], man_dist:tuple[int,int], multiplier:int) -> tuple[int,int]|None:
    global MAP_X_LEN, MAP_Y_LEN

    new_man_distance = tuple(map(lambda pos: pos * multiplier, man_dist))
    antinode_pos = (base_pos[0] + new_man_distance[0], base_pos[1] + new_man_distance[1])

    if 0 <= antinode_pos[0] < MAP_X_LEN and 0 <= antinode_pos[1] < MAP_Y_LEN:
        return antinode_pos   

    return None

def get_all_antinodes(base_pos:tuple[int, int], man_dist:tuple[int, int]) -> set[tuple[int, int]]|None:

    antinodes = set()    
    mul = 0
    while True:
        if ant := get_antinode_pos(base_pos, man_dist, mul):
            antinodes.add(ant)
            mul += 1
            continue
        break
    
    return antinodes

def main():
    global MAP, MAP_Y_LEN, MAP_X_LEN

    if len(argv) != 2:
        exit("USAGE: python day8.py [FILE]")


    file_path = Path(argv[1])
    if not file_path.exists():
        exit("File not found")

    # Initialize Map
    with open(file_path) as file:
        MAP = [line.strip() for line in file]
    MAP_X_LEN = len(MAP)
    MAP_Y_LEN = len(MAP[0])

    # Get a set of all antennas
    antennas = get_antennas()
    
    # For every antenna, check for all antinodes of that antenna
    antinodes = set()
    for ant_curr in antennas:
        for ant_pair in antennas:
            try:
                 man_distance = ant_curr.calc_distance(ant_pair)
            except ValueError:
                continue
            
            if antinode_pos := get_all_antinodes(ant_curr.position, man_distance):
                antinodes = antinodes.union(antinode_pos)


           # print(f"{ant_curr} pair at {ant_pair.position}")
    
    print(len(antinodes))
            


                
                

    # Get an antinode bY:
        # Finding a second antenna
        # Calculating the manhattan distance from both antennas
        # Calculating the position of the antinode (i.e 2 * Distance)
        # If the position is valid (not out of bounds), add it to a set of valid antinode positions
        # Calculate the lenght of the antinodes set


if __name__ == "__main__":
    main()