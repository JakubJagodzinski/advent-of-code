def load_grid():
    grid = []
    with open('input.txt', 'r') as file:
        for line in file.readlines():
            grid.append(list(line.replace('\n', '')))
    return grid


def print_grid(grid):
    for row in grid:
        for column in row:
            print(column, end='')
        print()


def seek_word(grid, row_nr, col_nr):
    first_forward = grid[row_nr - 1][col_nr - 1] == 'M' and grid[row_nr + 1][col_nr + 1] == 'S'
    first_backward = grid[row_nr - 1][col_nr - 1] == 'S' and grid[row_nr + 1][col_nr + 1] == 'M'
    second_forward = grid[row_nr + 1][col_nr - 1] == 'M' and grid[row_nr - 1][col_nr + 1] == 'S'
    second_backward = grid[row_nr + 1][col_nr - 1] == 'S' and grid[row_nr - 1][col_nr + 1] == 'M'
    return (first_forward or first_backward) and (second_forward or second_backward)


def find_two_mas_in_x_shape(grid):
    counter = 0
    for row_nr in range(1, len(grid) - 1):
        for col_nr in range(1, len(grid[row_nr]) - 1):
            if grid[row_nr][col_nr] == 'A':
                counter += seek_word(grid, row_nr, col_nr)
    return counter


if __name__ == '__main__':
    grid = load_grid()
    print_grid(grid)
    print(find_two_mas_in_x_shape(grid))
