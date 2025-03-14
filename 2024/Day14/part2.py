import re


def load_robots_stats():
    with open('input.txt', 'rt') as f:
        robots = []
        for line in f.readlines():
            line = line.replace('\n', '')
            matches = re.findall(r"-?\d+", line)
            robots.append([int(match) for match in matches])
        return robots


# example
# AREA_WIDTH = 11
# AREA_HEIGHT = 7

# input
AREA_WIDTH = 101
AREA_HEIGHT = 103


def run(robots):
    for robot in robots:
        robot_x = robot[0]
        robot_y = robot[1]
        robot_x_delta = robot[2]
        robot_y_delta = robot[3]
        robot_x += robot_x_delta
        robot_y += robot_y_delta
        if robot_x >= AREA_WIDTH:
            robot_x = abs(robot_x % AREA_WIDTH)
        elif robot_x < 0:
            robot_x = AREA_WIDTH - abs(robot_x)
        if robot_y >= AREA_HEIGHT:
            robot_y = abs(robot_y % AREA_HEIGHT)
        elif robot_y < 0:
            robot_y = AREA_HEIGHT - abs(robot_y)
        robot[0] = robot_x
        robot[1] = robot_y


def count_quadrants(robots):
    top_left_quadrant = 0
    top_right_quadrant = 0
    bottom_left_quadrant = 0
    bottom_right_quadrant = 0
    half_height = (AREA_HEIGHT // 2)
    half_width = (AREA_WIDTH // 2)
    for robot in robots:
        robot_x = robot[0]
        robot_y = robot[1]
        if robot_x < half_width and robot_y < half_height:
            # top_left_quadrant
            top_left_quadrant += 1
        elif robot_x > half_width and robot_y < half_height:
            # top_right_quadrant
            top_right_quadrant += 1
        elif robot_x < half_width and robot_y > half_height:
            # bottom_left_quadrant
            bottom_left_quadrant += 1
        elif robot_x > half_width and robot_y > half_height:
            # bottom_right_quadrant
            bottom_right_quadrant += 1
    return top_left_quadrant * top_right_quadrant * bottom_left_quadrant * bottom_right_quadrant


def contains_robot_at_position(robots, x, y):
    for robot in robots:
        if robot[0] == x and robot[1] == y:
            return True


def display_positions(robots):
    for row_nr in range(AREA_HEIGHT):
        for col_nr in range(AREA_WIDTH):
            if contains_robot_at_position(robots, col_nr, row_nr):
                print('#', end='')
            else:
                print(' ', end='')
        print()
    print()


def count_manhattan_distance(x_1, y_1, x_2, y_2):
    return abs(x_1 - x_2) + abs(y_1 - y_2)


def count_avg_robots_distances(robots):
    distances = 0
    for i in range(len(robots) - 1):
        for j in range(i + 1, len(robots)):
            distances += count_manhattan_distance(robots[i][0], robots[i][1], robots[j][0], robots[j][1])
    return distances // (len(robots) * (len(robots) - 1) // 2)


DISTANCE_THRESHOLD = (AREA_WIDTH + AREA_HEIGHT) // 4

if __name__ == '__main__':
    robots_stats = load_robots_stats()
    # for robot in robots_stats:
    #     print(robot)

    second = 0
    while True:
        run(robots_stats)
        avg_robots_distance = count_avg_robots_distances(robots_stats)
        if avg_robots_distance < DISTANCE_THRESHOLD:
            print('*' * 120, second)
            display_positions(robots_stats)
        second += 1

    # print(count_quadrants(robots_stats))
