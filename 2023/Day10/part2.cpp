#include <iostream>

using namespace std;

#define WIDTH 20
#define HEIGHT 10

struct point_t {
    int x;
    int y;
};

bool move_up(const char (&map)[HEIGHT][WIDTH], char (&backtrack_map)[HEIGHT][WIDTH], struct point_t &current_position);

bool
move_down(const char (&map)[HEIGHT][WIDTH], char (&backtrack_map)[HEIGHT][WIDTH], struct point_t &current_position);

bool
move_left(const char (&map)[HEIGHT][WIDTH], char (&backtrack_map)[HEIGHT][WIDTH], struct point_t &current_position);

bool
move_right(const char (&map)[HEIGHT][WIDTH], char (&backtrack_map)[HEIGHT][WIDTH], struct point_t &current_position);

void get_area(char (&backtrack_map)[HEIGHT][WIDTH], struct point_t current_point);

bool is_enclosed(char (&backtrack_map)[HEIGHT][WIDTH], struct point_t current_point);

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Couldn't open file" << endl;
        return 4;
    }
    char map[HEIGHT][WIDTH];
    char backtrack_map[HEIGHT][WIDTH] = {0};
    for (int y = 0; y < HEIGHT; ++y) {
        fscanf(fin, "%20[^\n]\n", *(map + y));
    }
    fclose(fin);
    struct point_t starting_point = {0, 0};
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (*(*(map + y) + x) == 'S') {
                starting_point = {x, y};
                break;
            }
        }
    }
    int loop_distance = 0;
    struct point_t current_position = starting_point;
    while (true) {
        bool moved = false;
        if (move_up(map, backtrack_map, current_position)) {
            moved = true;
        } else if (move_down(map, backtrack_map, current_position)) {
            moved = true;
        } else if (move_left(map, backtrack_map, current_position)) {
            moved = true;
        } else if (move_right(map, backtrack_map, current_position)) {
            moved = true;
        }
        ++loop_distance;
        if (!moved) {
            break;
        }
    }
    for (int y = 0; y < HEIGHT; ++y) {
        //bool to_break = false;
        for (int x = 0; x < WIDTH; ++x) {
            is_enclosed(backtrack_map, {x, y});
            /*if (x == 11 and y == 3) {
                to_break = true;
                break;
            }*/
        }
        /*if (to_break) {
            break;
        }*/
    }
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            cout << *(*(backtrack_map + y) + x);
        }
        cout << endl;
    }
    return 0;
}

bool move_up(const char (&map)[HEIGHT][WIDTH], char (&backtrack_map)[HEIGHT][WIDTH], struct point_t &current_position) {
    if (*(*(map + current_position.y) + current_position.x) != '-' and
        *(*(map + current_position.y) + current_position.x) != '7' and
        *(*(map + current_position.y) + current_position.x) != 'F' and
        (current_position.y > 0) and
        (*(*(backtrack_map + current_position.y - 1) + current_position.x) != '.') and
        ((*(*(map + current_position.y - 1) + current_position.x) == '|') or
         (*(*(map + current_position.y - 1) + current_position.x) == 'F') or
         (*(*(map + current_position.y - 1) + current_position.x) == '7'))) {
        *(*(backtrack_map + current_position.y) + current_position.x) = '.';
        --current_position.y;
        return true;
    }
    return false;
}

bool
move_down(const char (&map)[HEIGHT][WIDTH], char (&backtrack_map)[HEIGHT][WIDTH], struct point_t &current_position) {
    if (*(*(map + current_position.y) + current_position.x) != '-' and
        *(*(map + current_position.y) + current_position.x) != 'L' and
        *(*(map + current_position.y) + current_position.x) != 'J' and
        (current_position.y < HEIGHT - 1) and
        (*(*(backtrack_map + current_position.y + 1) + current_position.x) != '.') and
        ((*(*(map + current_position.y + 1) + current_position.x) == '|') or
         (*(*(map + current_position.y + 1) + current_position.x) == 'L') or
         (*(*(map + current_position.y + 1) + current_position.x) == 'J'))) {
        *(*(backtrack_map + current_position.y) + current_position.x) = '.';
        ++current_position.y;
        return true;
    }
    return false;
}

bool
move_left(const char (&map)[HEIGHT][WIDTH], char (&backtrack_map)[HEIGHT][WIDTH], struct point_t &current_position) {
    if (*(*(map + current_position.y) + current_position.x) != '|' and
        *(*(map + current_position.y) + current_position.x) != 'L' and
        *(*(map + current_position.y) + current_position.x) != 'F' and
        (current_position.x > 0) and
        (*(*(backtrack_map + current_position.y) + current_position.x - 1) != '.') and
        ((*(*(map + current_position.y) + current_position.x - 1) == '-') or
         (*(*(map + current_position.y) + current_position.x - 1) == 'L') or
         (*(*(map + current_position.y) + current_position.x - 1) == 'F'))) {
        *(*(backtrack_map + current_position.y) + current_position.x) = '.';
        --current_position.x;
        return true;
    }
    return false;
}

bool
move_right(const char (&map)[HEIGHT][WIDTH], char (&backtrack_map)[HEIGHT][WIDTH], struct point_t &current_position) {
    if (*(*(map + current_position.y) + current_position.x) != '|' and
        *(*(map + current_position.y) + current_position.x) != '7' and
        *(*(map + current_position.y) + current_position.x) != 'J' and
        (current_position.x < WIDTH - 1) and
        (*(*(backtrack_map + current_position.y) + current_position.x + 1) != '.') and
        ((*(*(map + current_position.y) + current_position.x + 1) == '-') or
         (*(*(map + current_position.y) + current_position.x + 1) == 'J') or
         (*(*(map + current_position.y) + current_position.x + 1) == '7'))) {
        *(*(backtrack_map + current_position.y) + current_position.x) = '.';
        ++current_position.x;
        return true;
    }
    return false;
}

bool is_enclosed(char (&backtrack_map)[HEIGHT][WIDTH], struct point_t current_point) {
    if (*(*(backtrack_map + current_point.y) + current_point.x) == '.' or
        *(*(backtrack_map + current_point.y) + current_point.x) == 'I') {
        return true;
    }
    if (current_point.x == 0 or current_point.x == WIDTH - 1 or current_point.y == 0 or current_point.y == HEIGHT - 1 or
        *(*(backtrack_map + current_point.y) + current_point.x) == 'O') {
        if (*(*(backtrack_map + current_point.y) + current_point.x) != '.' and
            *(*(backtrack_map + current_point.y) + current_point.x) != 'I') {
            *(*(backtrack_map + current_point.y) + current_point.x) = 'O';
        }
        return false;
    }
    *(*(backtrack_map + current_point.y) + current_point.x) = ',';
    bool is_enclosed_up = *(*(backtrack_map + current_point.y - 1) + current_point.x) == ',' or
                          is_enclosed(backtrack_map, {current_point.x, current_point.y - 1});
    bool is_enclosed_down = *(*(backtrack_map + current_point.y + 1) + current_point.x) == ',' or
                            is_enclosed(backtrack_map, {current_point.x, current_point.y + 1});
    bool is_enclosed_left = *(*(backtrack_map + current_point.y) + current_point.x - 1) == ',' or
                            is_enclosed(backtrack_map, {current_point.x - 1, current_point.y});
    bool is_enclosed_right = *(*(backtrack_map + current_point.y) + current_point.x + 1) == ',' or
                             is_enclosed(backtrack_map, {current_point.x + 1, current_point.y});
    if (is_enclosed_up and is_enclosed_down and is_enclosed_left and is_enclosed_right) {
        *(*(backtrack_map + current_point.y) + current_point.x) = 'I';
        return true;
    } else {
        *(*(backtrack_map + current_point.y) + current_point.x) = 'O';
        return false;
    }
}
