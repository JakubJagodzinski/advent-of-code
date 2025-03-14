def load_frequencies_grid():
    with open('input.txt', 'rt') as f:
        frequencies_grid = list()
        for line in f.readlines():
            line = line.replace('\n', '')
            frequencies_grid.append([column for column in line])
        return frequencies_grid


def get_frequencies_set(frequencies_grid):
    frequencies_set = set()
    for row in frequencies_grid:
        for column in row:
            frequencies_set.add(column)
    frequencies_set.remove('.')
    return frequencies_set


def create_frequency_locations_list(frequencies_grid, frequency):
    frequency_locations = list()
    for row_nr in range(len(frequencies_grid)):
        for column_nr in range(len(frequencies_grid[row_nr])):
            if frequencies_grid[row_nr][column_nr] == frequency:
                frequency_locations.append((column_nr, row_nr))
    return frequency_locations


def create_frequencies_locations_dictionary(frequencies_set, frequencies_grid):
    frequencies_locations_dictionary = dict()
    for frequency in frequencies_set:
        frequencies_locations_dictionary[frequency] = create_frequency_locations_list(frequencies_grid, frequency)
    return frequencies_locations_dictionary


def mark_antinodes_for_frequency(frequency_locations, antinodes_grid):
    antinodes_grid_width = len(antinodes_grid[0])
    antinodes_grid_height = len(antinodes_grid)
    for first_index in range(0, len(frequency_locations) - 1):
        for second_index in range(first_index + 1, len(frequency_locations)):
            x_first_frequency = frequency_locations[first_index][0]
            y_first_frequency = frequency_locations[first_index][1]
            x_second_frequency = frequency_locations[second_index][0]
            y_second_frequency = frequency_locations[second_index][1]
            x_delta_frequencies = abs(x_second_frequency - x_first_frequency)
            y_delta_frequencies = abs(y_second_frequency - y_first_frequency)
            x_delta_antinodes = x_delta_frequencies
            y_delta_antinodes = y_delta_frequencies
            x_left, x_right = min(x_first_frequency, x_second_frequency), max(x_first_frequency, x_second_frequency)
            y_up, y_down = min(y_first_frequency, y_second_frequency), max(y_first_frequency, y_second_frequency)
            is_primary_diagonal = x_first_frequency <= x_second_frequency and y_first_frequency <= y_second_frequency
            if is_primary_diagonal:
                x_left_up_antinode = x_left - x_delta_antinodes
                y_left_up_antinode = y_up - y_delta_antinodes
                if x_left_up_antinode >= 0 and y_left_up_antinode >= 0:
                    antinodes_grid[y_left_up_antinode][x_left_up_antinode] = '#'
                x_right_down_antinode = x_right + x_delta_antinodes
                y_right_down_antinode = y_down + y_delta_antinodes
                if x_right_down_antinode < antinodes_grid_width and y_right_down_antinode < antinodes_grid_height:
                    antinodes_grid[y_right_down_antinode][x_right_down_antinode] = '#'
            else:
                x_right_up_antinode = x_right + x_delta_antinodes
                y_right_up_antinode = y_up - y_delta_antinodes
                if x_right_up_antinode < antinodes_grid_width and y_right_up_antinode >= 0:
                    antinodes_grid[y_right_up_antinode][x_right_up_antinode] = '#'
                x_left_down_antinode = x_left - x_delta_antinodes
                y_left_down_antinode = y_down + y_delta_antinodes
                if x_left_down_antinode >= 0 and y_left_down_antinode < antinodes_grid_height:
                    antinodes_grid[y_left_down_antinode][x_left_down_antinode] = '#'


def create_empty_antinodes_grid(width, height):
    empty_antinodes_grid = list()
    for row_nr in range(height):
        row = []
        for column_nr in range(width):
            row.append('.')
        empty_antinodes_grid.append(row)
    return empty_antinodes_grid


def create_antinodes_grid(frequencies_locations, grid_width, grid_height):
    antinodes_grid = create_empty_antinodes_grid(grid_width, grid_height)
    for frequency_locations in frequencies_locations.values():
        mark_antinodes_for_frequency(frequency_locations, antinodes_grid)
    return antinodes_grid


def print_2d_grid(grid):
    for row in grid:
        for column in row:
            print(column, end='')
        print()
    print()


def count_all_antinodes(antinodes_grid):
    antinodes_counter = 0
    for row in antinodes_grid:
        for column in row:
            if column == '#':
                antinodes_counter += 1
    return antinodes_counter


if __name__ == '__main__':
    frequencies_grid = load_frequencies_grid()
    # print_2d_grid(frequencies_grid)
    frequencies_set = get_frequencies_set(frequencies_grid)
    # print(frequencies_set)
    frequencies_locations = create_frequencies_locations_dictionary(frequencies_set, frequencies_grid)
    # print(frequencies_locations)
    grid_width = len(frequencies_grid[0])
    grid_height = len(frequencies_grid)
    antinodes_grid = create_antinodes_grid(frequencies_locations, grid_width, grid_height)
    # print_2d_grid(antinodes_grid)
    print(count_all_antinodes(antinodes_grid))
