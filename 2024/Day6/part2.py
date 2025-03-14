def load_map():
    guard_position = [0, 0]
    grid = []
    with open('input.txt', 'rt') as f:
        row_nr = 0
        for row in f.readlines():
            row = row.replace('\n', '')
            row_content = []
            column_nr = 0
            for column in row:
                if column == '^':
                    guard_position = [column_nr, row_nr]
                    row_content.append(False)
                elif column == '#':
                    row_content.append(True)
                else:
                    row_content.append(False)
                column_nr += 1
            grid.append(row_content)
            row_nr += 1
    return guard_position, grid


DIRECTION_UP = 'up'
DIRECTION_RIGHT = 'right'
DIRECTION_DOWN = 'down'
DIRECTION_LEFT = 'left'


def get_next_direction(current_direction):
    if current_direction == DIRECTION_UP:
        return DIRECTION_RIGHT
    elif current_direction == DIRECTION_RIGHT:
        return DIRECTION_DOWN
    elif current_direction == DIRECTION_DOWN:
        return DIRECTION_LEFT
    elif current_direction == DIRECTION_LEFT:
        return DIRECTION_UP


def is_field_obstacle(grid, x, y):
    return grid[y][x] == True


def is_field_out(grid, x, y):
    return y < 0 or y >= len(grid) or x < 0 or x >= len(grid[0])


def print_grid(grid, guard_position=None, guard_direction=None):
    for row_nr in range(len(grid)):
        for col_nr in range(len(grid[0])):
            if guard_position is not None and row_nr == guard_position[1] and col_nr == guard_position[0]:
                print(DIRECTIONS_SYMBOL[guard_direction], end='')
            else:
                if grid[row_nr][col_nr] == True:
                    print('#', end='')
                else:
                    print('.', end='')
        print()
    print()
    print()


def sum_all_visited_fields(visited_grid):
    visited_sum = 0
    for row_nr in range(len(visited_grid)):
        for col_nr in range(len(visited_grid[0])):
            if visited_grid[row_nr][col_nr] == True:
                visited_sum += 1
    return visited_sum


DIRECTIONS_SYMBOL = {'up': '^',
                     'right': '>',
                     'down': 'v',
                     'left': '<', }


def create_visited_grid(width, height):
    visited_grid = []
    for row_nr in range(height):
        row = []
        for col_nr in range(width):
            row.append(False)
        visited_grid.append(row)
    return visited_grid


if __name__ == '__main__':
    guard_position, grid = load_map()
    visited_grid = create_visited_grid(len(grid), len(grid[0]))
    visited_grid[guard_position[1]][guard_position[0]] = True
    current_direction = DIRECTION_UP

    while True:
        guard_x, guard_y = guard_position

        if current_direction == DIRECTION_UP:
            next_x, next_y = guard_x, guard_y - 1
        elif current_direction == DIRECTION_RIGHT:
            next_x, next_y = guard_x + 1, guard_y
        elif current_direction == DIRECTION_DOWN:
            next_x, next_y = guard_x, guard_y + 1
        elif current_direction == DIRECTION_LEFT:
            next_x, next_y = guard_x - 1, guard_y

        if is_field_out(grid, next_x, next_y):
            break

        if is_field_obstacle(grid, next_x, next_y):
            current_direction = get_next_direction(current_direction)
        else:
            guard_position = next_x, next_y

        visited_grid[guard_position[1]][guard_position[0]] = True
        # print_grid(grid, guard_position, current_direction)
        # print_grid(visited_grid)

    print(sum_all_visited_fields(visited_grid))
