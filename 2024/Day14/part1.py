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


if __name__ == '__main__':
    robots_stats = load_robots_stats()
    # for robot in robots_stats:
    #     print(robot)

    SECONDS = 100
    for second in range(SECONDS):
        run(robots_stats)

    print(count_quadrants(robots_stats))
