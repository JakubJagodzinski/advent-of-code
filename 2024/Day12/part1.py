def load_map():
    with open('input.txt', 'rt') as f:
        map = []
        for line in f.readlines():
            line = line.replace('\n', '')
            map.append([column for column in line])
        return map


def create_regions_dict(map):
    regions_dict = dict()
    for row_nr in range(len(map)):
        for col_nr in range(len(map[row_nr])):
            regions_dict[map[row_nr][col_nr]] = {'area': 0,
                                                 'perimeter': 0}
    return regions_dict


def create_visited_map(map):
    visited_map = list()
    for row_nr in range(len(map)):
        visited_map.append([False] * len(map[row_nr]))
    return visited_map


visited_map = list()


def visit_region(map, map_width, map_height, row_nr, col_nr, region_name, region_stats):
    if row_nr < 0 or col_nr < 0 or row_nr >= map_height or col_nr >= map_width or map[row_nr][col_nr] != region_name:
        region_stats[1] += 1
        return
    if visited_map[row_nr][col_nr]:
        return
    if map[row_nr][col_nr] == region_name:
        region_stats[0] += 1
        visited_map[row_nr][col_nr] = True
    visit_region(map, map_width, map_height, row_nr + 1, col_nr, region_name, region_stats)
    visit_region(map, map_width, map_height, row_nr - 1, col_nr, region_name, region_stats)
    visit_region(map, map_width, map_height, row_nr, col_nr + 1, region_name, region_stats)
    visit_region(map, map_width, map_height, row_nr, col_nr - 1, region_name, region_stats)


def get_regions_statistics(map):
    global visited_map
    regions_statistics = list()
    map_height = len(map)
    map_width = len(map[0])
    visited_map = create_visited_map(map)
    for row_nr in range(map_height):
        for col_nr in range(map_width):
            if not visited_map[row_nr][col_nr]:
                region_stats = [0, 0]
                visit_region(map, map_width, map_height, row_nr, col_nr, map[row_nr][col_nr], region_stats)
                regions_statistics.append(region_stats)
    return regions_statistics


if __name__ == '__main__':
    map = load_map()
    regions_statistics = get_regions_statistics(map)
    print(regions_statistics)
    result = 0
    for region_stats in regions_statistics:
        result += region_stats[1] * region_stats[0]
    print(result)
