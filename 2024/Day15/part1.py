EXAMPLE_DATA = 'example.txt'
INPUT_DATA = 'input.txt'


def load_data(filename):
    with open(filename, 'rt') as f:
        grid = []
        while True:
            line = f.readline().replace('\n', '')
            if len(line) == 0:
                break
            grid.append([char for char in line])
        moves = []
        while True:
            line = f.readline().replace('\n', '')
            if len(line) == 0:
                break
            for char in line:
                moves.append(char)
        return grid, moves


def get_robot_position(grid):
    for row_nr in range(len(grid)):
        for col_nr in range(len(grid[row_nr])):
            if grid[row_nr][col_nr] == '@':
                return row_nr, col_nr


MOVEMENT_VECTORS = {'^': (0, -1),
                    'v': (0, 1),
                    '<': (-1, 0),
                    '>': (1, 0)}


def perform_moves(grid, moves):
    robot_position = get_robot_position(grid)
    for move in moves:
        col_delta, row_delta = MOVEMENT_VECTORS[move]
        if grid[robot_position[0] + row_delta][robot_position[1] + col_delta] == '#':
            continue
        elif grid[robot_position[0] + row_delta][robot_position[1] + col_delta] == '.':
            grid[robot_position[0]][robot_position[1]] = '.'
            robot_position = (robot_position[0] + row_delta, robot_position[1] + col_delta)
            grid[robot_position[0]][robot_position[1]] = '@'
        elif grid[robot_position[0] + row_delta][robot_position[1] + col_delta] == 'O':
            box_position = (robot_position[0] + row_delta, robot_position[1] + col_delta)
            can_be_pushed = True
            while True:
                if grid[box_position[0] + row_delta][box_position[1] + col_delta] == '#':
                    can_be_pushed = False
                    break
                elif grid[box_position[0] + row_delta][box_position[1] + col_delta] == '.':
                    box_position = (box_position[0] + row_delta, box_position[1] + col_delta)
                    break
                else:
                    box_position = (box_position[0] + row_delta, box_position[1] + col_delta)
            if can_be_pushed:
                grid[robot_position[0]][robot_position[1]] = '.'
                robot_position = (robot_position[0] + row_delta, robot_position[1] + col_delta)
                grid[robot_position[0]][robot_position[1]] = '@'
                grid[box_position[0]][box_position[1]] = 'O'
        # print_grid(grid)


def print_grid(grid):
    for row_nr in range(len(grid)):
        for col_nr in range(len(grid[row_nr])):
            print(grid[row_nr][col_nr], end='')
        print()
    print()


def count_gps_box_distance(grid):
    distances_sum = 0
    for row_nr in range(len(grid)):
        for col_nr in range(len(grid[row_nr])):
            if grid[row_nr][col_nr] == 'O':
                distances_sum += row_nr * 100 + col_nr
    return distances_sum


if __name__ == '__main__':
    grid, moves = load_data(INPUT_DATA)
    # print(grid)
    # print(moves)
    # print(get_robot_position(grid))
    print_grid(grid)
    perform_moves(grid, moves)
    print(count_gps_box_distance(grid))
