def load_map():
    with open('input.txt') as f:
        map = []
        for line in f:
            line = line.replace('\n', '')
            row = []
            for char in line:
                if char != '.':
                    row.append(int(char))
                else:
                    row.append(-1)
            map.append(row)
        return map


TRAILHEAD_START_HEIGHT = 0
TRAILHEAD_END_HEIGHT = 9


def count_trailhead_score(map, previous_height, column_nr, row_nr, visited_map):
    if row_nr < 0 or row_nr >= len(map) or column_nr < 0 or column_nr >= len(map[0]):
        return
    if not map[row_nr][column_nr] - previous_height == 1:
        return
    if map[row_nr][column_nr] == TRAILHEAD_END_HEIGHT:
        visited_map[row_nr][column_nr] = True
        return
    count_trailhead_score(map, map[row_nr][column_nr], column_nr, row_nr - 1, visited_map)
    count_trailhead_score(map, map[row_nr][column_nr], column_nr - 1, row_nr, visited_map)
    count_trailhead_score(map, map[row_nr][column_nr], column_nr + 1, row_nr, visited_map)
    count_trailhead_score(map, map[row_nr][column_nr], column_nr, row_nr + 1, visited_map)


def create_empty_visited_map(map):
    visited_map = []
    for row_nr in range(len(map)):
        row = [False] * len(map[0])
        visited_map.append(row)
    return visited_map


def count_visited_peaks(visited_map):
    visited_peaks = 0
    for row_nr in range(len(visited_map)):
        for column_nr in range(len(visited_map[row_nr])):
            if visited_map[row_nr][column_nr]:
                visited_peaks += 1
    return visited_peaks


def count_trailheads_scores(map):
    scores = []
    for row_nr in range(len(map)):
        for col_nr in range(len(map[row_nr])):
            if map[row_nr][col_nr] == 0:
                visited_map = create_empty_visited_map(map)
                count_trailhead_score(map, -1, col_nr, row_nr, visited_map)
                scores.append(count_visited_peaks(visited_map))
    return scores


if __name__ == '__main__':
    map = load_map()
    scores = count_trailheads_scores(map)
    print(scores)
    print(sum(scores))
