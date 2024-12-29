from pathlib import Path
from sys import argv


XMAS_CONT = []

def main():
    global XMAS_CONT
    
    try:
        FILE_PATH = Path(argv[1])
    except IndexError:
        print("USAGE: python day4.py [FILE]")
        return

    if not FILE_PATH.exists():
        print(f"ERR: {FILE_PATH} not found!")
        return

    with open(FILE_PATH, 'r') as file:
        for line in file:
            XMAS_CONT.append(line.strip())
    
    xmas_count = 0

    for row, line in enumerate(XMAS_CONT):
        for col in range(len(line)):
            xmas_count += 1 if is_mas_x(row, col) else 0
    
    print(xmas_count)

def count_xmas(row, col) -> int:
    """Traverses the contents of XMAS, in every direction to find all XMAS's"""
    global XMAS_CONT
    if XMAS_CONT[row][col] != 'X':
        return 0
    xmas_count = 0
    # Directions
    directions = [(0,1),(1,0),
                  (1,1),(-1,1)] 
    for dirs in directions:
        xmas_count += 1 if is_xmas(row, col, dirs) else 0

    return xmas_count

def is_xmas(row:int, col:int, differences:tuple[int, int], _depth=0, _depth_dif=1, _t="") -> bool:
    """Validates if the direction from the origin is a valid XMAS"""
    if _depth == 4 and _depth_dif == 1:
        return True

    if _depth == 0 and _depth_dif == -1:
        return True
    
    if not (0 <= row < len(XMAS_CONT)):
        return False
    
    if not (0 <= col < len(XMAS_CONT[0])):
        return False
    
    # Easier to debug this way
    _current = "XMAS"[_depth]
    _to_match = XMAS_CONT[row][col]
    
    
    if _to_match == _current:
        _t += _current
        row += differences[0]
        col += differences[1]
        return is_xmas(row, col, differences, _depth + _depth_dif,_depth_dif=_depth_dif, _t=_t)
    
    return False
    
def is_mas_x(row:int, col:int) -> bool:
    global XMAS_CONT
    if XMAS_CONT[row][col] != 'A':
        return False
    
    def check_diagonal(dirs:tuple[int,int]) -> bool:
        x, y = dirs
        return is_xmas(row - x, col - y, dirs, 1, 1) or \
            is_xmas(row - x, col - y, dirs, 3, -1)

    diag1 = check_diagonal((1, -1))
    diag2 = check_diagonal((1, 1))

    
    return (diag1 and diag2)


if __name__ == "__main__":
    main()