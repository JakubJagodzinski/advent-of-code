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


shapes_map = list()


def visit_region(map, map_width, map_height, row_nr, col_nr, region_name, region_stats, region_nr):
    if row_nr < 0 or col_nr < 0 or row_nr >= map_height or col_nr >= map_width or map[row_nr][col_nr] != region_name:
        region_stats[1] += 1
        return
    if shapes_map[row_nr][col_nr] != -1:
        return
    if map[row_nr][col_nr] == region_name:
        region_stats[0] += 1
        shapes_map[row_nr][col_nr] = region_nr
    visit_region(map, map_width, map_height, row_nr + 1, col_nr, region_name, region_stats, region_nr)
    visit_region(map, map_width, map_height, row_nr - 1, col_nr, region_name, region_stats, region_nr)
    visit_region(map, map_width, map_height, row_nr, col_nr + 1, region_name, region_stats, region_nr)
    visit_region(map, map_width, map_height, row_nr, col_nr - 1, region_name, region_stats, region_nr)


def create_shapes_map(map):
    shapes_map = list()
    for row_nr in range(len(map)):
        shapes_map.append([-1 for _ in range(len(map[row_nr]))])
    return shapes_map


def count_region_sides(region_nr):
    shapes_map_height = len(shapes_map)
    shapes_map_width = len(shapes_map[0])
    up_down_horizontal_sides = 0
    for row_nr in range(shapes_map_height):
        continuous = False
        for col_nr in range(shapes_map_width):
            if shapes_map[row_nr][col_nr] == region_nr:
                if row_nr - 1 < 0 or shapes_map[row_nr - 1][col_nr] != region_nr:
                    if not continuous:
                        up_down_horizontal_sides += 1
                        continuous = True
                else:
                    continuous = False
            else:
                continuous = False
    down_up_horizontal_sides = 0
    for row_nr in reversed(range(shapes_map_height)):
        continuous = False
        for col_nr in range(shapes_map_width):
            if shapes_map[row_nr][col_nr] == region_nr:
                if row_nr + 1 >= shapes_map_height or shapes_map[row_nr + 1][col_nr] != region_nr:
                    if not continuous:
                        down_up_horizontal_sides += 1
                        continuous = True
                else:
                    continuous = False
            else:
                continuous = False
    left_right_vertical_sides = 0
    for col_nr in range(shapes_map_width):
        continuous = False
        for row_nr in range(shapes_map_height):
            if shapes_map[row_nr][col_nr] == region_nr:
                if col_nr - 1 < 0 or shapes_map[row_nr][col_nr - 1] != region_nr:
                    if not continuous:
                        left_right_vertical_sides += 1
                        continuous = True
                else:
                    continuous = False
            else:
                continuous = False
    right_left_vertical_sides = 0
    for col_nr in reversed(range(shapes_map_width)):
        continuous = False
        for row_nr in range(shapes_map_height):
            if shapes_map[row_nr][col_nr] == region_nr:
                if col_nr + 1 >= shapes_map_width or shapes_map[row_nr][col_nr + 1] != region_nr:
                    if not continuous:
                        right_left_vertical_sides += 1
                        continuous = True
                else:
                    continuous = False
            else:
                continuous = False
    return up_down_horizontal_sides, down_up_horizontal_sides, left_right_vertical_sides, right_left_vertical_sides


def get_regions_statistics(map):
    global shapes_map
    regions_statistics = list()
    map_height = len(map)
    map_width = len(map[0])
    shapes_map = create_shapes_map(map)
    region_nr = -1
    for row_nr in range(map_height):
        for col_nr in range(map_width):
            if shapes_map[row_nr][col_nr] == -1:
                region_nr += 1
                region_stats = [0, 0]
                visit_region(map, map_width, map_height, row_nr, col_nr, map[row_nr][col_nr], region_stats, region_nr)
                regions_statistics.append(region_stats)
    return regions_statistics


if __name__ == '__main__':
    map = load_map()
    regions_statistics = get_regions_statistics(map)
    # print(regions_statistics)
    result = 0
    # for row in shapes_map:
    #     print(row)
    # print()
    for region_nr, region_stats in enumerate(regions_statistics):
        region_sides = count_region_sides(region_nr)
        # print(region_nr, region_sides)
        result += region_stats[0] * sum(region_sides)
    print(result)
