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


word_letters = ['X', 'M', 'A', 'S']


def seek_word(grid, row_nr, col_nr, row_delta, col_delta):
    for letter in word_letters:
        if row_nr < 0 or row_nr >= len(grid) or col_nr < 0 or col_nr >= len(grid[row_nr]):
            return 0
        if grid[row_nr][col_nr] != letter:
            return 0
        row_nr += row_delta
        col_nr += col_delta
    return 1


def find_xmas_words(grid):
    counter = 0
    for row_nr in range(len(grid)):
        for col_nr in range(len(grid[row_nr])):
            if grid[row_nr][col_nr] == 'X':
                counter += seek_word(grid, row_nr, col_nr, -1, -1)
                counter += seek_word(grid, row_nr, col_nr, -1, 0)
                counter += seek_word(grid, row_nr, col_nr, -1, 1)
                counter += seek_word(grid, row_nr, col_nr, 0, -1)
                counter += seek_word(grid, row_nr, col_nr, 0, 1)
                counter += seek_word(grid, row_nr, col_nr, 1, -1)
                counter += seek_word(grid, row_nr, col_nr, 1, 0)
                counter += seek_word(grid, row_nr, col_nr, 1, 1)
    return counter


if __name__ == '__main__':
    grid = load_grid()
    print_grid(grid)
    print(find_xmas_words(grid))
