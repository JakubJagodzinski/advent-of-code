#include <iostream>
#include <cstring>

using namespace std;

#define WIDTH 110
#define HEIGHT 110

struct point_t {
    int x;
    int y;
};

void move_up(const char (&map)[HEIGHT][WIDTH], char (&energized_map)[HEIGHT][WIDTH], point_t current_position);

void move_down(const char (&map)[HEIGHT][WIDTH], char (&energized_map)[HEIGHT][WIDTH], point_t current_position);

void move_left(const char (&map)[HEIGHT][WIDTH], char (&energized_map)[HEIGHT][WIDTH], point_t current_position);

void move_right(const char (&map)[HEIGHT][WIDTH], char (&energized_map)[HEIGHT][WIDTH], point_t current_position);

size_t count_energized_field(const char (&energized_map)[HEIGHT][WIDTH]);

void display_energized_map(const char (&energized_map)[HEIGHT][WIDTH]);

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Failed to open file" << endl;
        return -1;
    }
    char map[HEIGHT][WIDTH];
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            fscanf(fin, "%c", (*(map + y) + x));
        }
        fgetc(fin);
    }
    fclose(fin);
    char energized_map[HEIGHT][WIDTH] = {0};
    size_t energized_counter = count_energized_field(energized_map);
    cout << "PART TWO" << endl;
    size_t max_energized_counter = energized_counter;
    for (int x = 0; x < WIDTH; ++x) {
        memset(energized_map, 0, WIDTH * HEIGHT);
        move_down(map, energized_map, {x, -1});
        energized_counter = count_energized_field(energized_map);
        if (energized_counter > max_energized_counter) {
            max_energized_counter = energized_counter;
        }
        memset(energized_map, 0, WIDTH * HEIGHT);
        move_up(map, energized_map, {x, HEIGHT});
        energized_counter = count_energized_field(energized_map);
        if (energized_counter > max_energized_counter) {
            max_energized_counter = energized_counter;
        }
    }
    for (int y = 0; y < HEIGHT; ++y) {
        memset(energized_map, 0, WIDTH * HEIGHT);
        move_right(map, energized_map, {-1, y});
        energized_counter = count_energized_field(energized_map);
        if (energized_counter > max_energized_counter) {
            max_energized_counter = energized_counter;
        }
        memset(energized_map, 0, WIDTH * HEIGHT);
        move_left(map, energized_map, {WIDTH, y});
        energized_counter = count_energized_field(energized_map);
        if (energized_counter > max_energized_counter) {
            max_energized_counter = energized_counter;
        }
    }
    cout << "Max energized counter: " << max_energized_counter << endl;
    return 0;
}

/// bit masks:
///     format : [symbol] -> value (move_function -> move_function)
///     [/] -> 1 (down -> left)(right -> up);       2 (up -> right)(left -> down);
///     [\] -> 1 (right -> down)(up -> left);       2 (down -> right)(left -> up);
///     [|] -> 1 (left -> up)(left -> down);        2 (right -> up)(right -> down);
///     [-] -> 1 (down -> left)(down -> right);     2 (up -> left)(up -> right);

void move_up(const char (&map)[HEIGHT][WIDTH], char (&energized_map)[HEIGHT][WIDTH], point_t current_position) {
    while (--current_position.y >= 0) {
        switch (*(*(map + current_position.y) + current_position.x)) {
            case '/':
                if ((*(*(energized_map + current_position.y) + current_position.x) & 2) != 2) {
                    *(*(energized_map + current_position.y) + current_position.x) |= 2;
                    move_right(map, energized_map, current_position);
                }
                return;
            case '\\':
                if ((*(*(energized_map + current_position.y) + current_position.x) & 1) != 1) {
                    *(*(energized_map + current_position.y) + current_position.x) |= 1;
                    move_left(map, energized_map, current_position);
                }
                return;
            case '-':
                if ((*(*(energized_map + current_position.y) + current_position.x) & 1) != 1) {
                    *(*(energized_map + current_position.y) + current_position.x) |= 1;
                    move_left(map, energized_map, current_position);
                    move_right(map, energized_map, current_position);
                }
                return;
            case '|':
                *(*(energized_map + current_position.y) + current_position.x) |= 1;
                break;
            default:
                ++*(*(energized_map + current_position.y) + current_position.x);
                break;
        }
    }
}

void move_down(const char (&map)[HEIGHT][WIDTH], char (&energized_map)[HEIGHT][WIDTH], point_t current_position) {
    while (++current_position.y < HEIGHT) {
        switch (*(*(map + current_position.y) + current_position.x)) {
            case '/':
                if ((*(*(energized_map + current_position.y) + current_position.x) & 1) != 1) {
                    *(*(energized_map + current_position.y) + current_position.x) |= 1;
                    move_left(map, energized_map, current_position);
                }
                return;
            case '\\':
                if ((*(*(energized_map + current_position.y) + current_position.x) & 2) != 2) {
                    *(*(energized_map + current_position.y) + current_position.x) |= 2;
                    move_right(map, energized_map, current_position);
                }
                return;
            case '-':
                if ((*(*(energized_map + current_position.y) + current_position.x) & 1) != 1) {
                    *(*(energized_map + current_position.y) + current_position.x) |= 1;
                    move_left(map, energized_map, current_position);
                    move_right(map, energized_map, current_position);
                }
                return;
            case '|':
                *(*(energized_map + current_position.y) + current_position.x) |= 1;
                break;
            default:
                ++*(*(energized_map + current_position.y) + current_position.x);
                break;
        }
    }
}

void move_left(const char (&map)[HEIGHT][WIDTH], char (&energized_map)[HEIGHT][WIDTH], point_t current_position) {
    while (--current_position.x >= 0) {
        switch (*(*(map + current_position.y) + current_position.x)) {
            case '/':
                if ((*(*(energized_map + current_position.y) + current_position.x) & 2) != 2) {
                    *(*(energized_map + current_position.y) + current_position.x) |= 2;
                    move_down(map, energized_map, current_position);
                }
                return;
            case '\\':
                if ((*(*(energized_map + current_position.y) + current_position.x) & 2) != 2) {
                    *(*(energized_map + current_position.y) + current_position.x) |= 2;
                    move_up(map, energized_map, current_position);
                }
                return;
            case '|':
                if ((*(*(energized_map + current_position.y) + current_position.x) & 1) != 1) {
                    *(*(energized_map + current_position.y) + current_position.x) |= 1;
                    move_up(map, energized_map, current_position);
                    move_down(map, energized_map, current_position);
                }
                return;
            case '-':
                *(*(energized_map + current_position.y) + current_position.x) |= 1;
                break;
            default:
                ++*(*(energized_map + current_position.y) + current_position.x);
                break;
        }
    }
}

void move_right(const char (&map)[HEIGHT][WIDTH], char (&energized_map)[HEIGHT][WIDTH], point_t current_position) {
    while (++current_position.x < WIDTH) {
        switch (*(*(map + current_position.y) + current_position.x)) {
            case '/':
                if ((*(*(energized_map + current_position.y) + current_position.x) & 1) != 1) {
                    *(*(energized_map + current_position.y) + current_position.x) |= 1;
                    move_up(map, energized_map, current_position);
                }
                return;
            case '\\':
                if ((*(*(energized_map + current_position.y) + current_position.x) & 1) != 1) {
                    *(*(energized_map + current_position.y) + current_position.x) |= 1;
                    move_down(map, energized_map, current_position);
                }
                return;
            case '|':
                if ((*(*(energized_map + current_position.y) + current_position.x) & 1) != 1) {
                    *(*(energized_map + current_position.y) + current_position.x) |= 1;
                    move_up(map, energized_map, current_position);
                    move_down(map, energized_map, current_position);
                }
                return;
            case '-':
                *(*(energized_map + current_position.y) + current_position.x) |= 1;
                break;
            default:
                ++*(*(energized_map + current_position.y) + current_position.x);
                break;
        }
    }
}

size_t count_energized_field(const char (&energized_map)[HEIGHT][WIDTH]) {
    size_t energized_counter = 0;
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (*(*(energized_map + y) + x)) {
                ++energized_counter;
            }
        }
    }
    return energized_counter;
}

void display_energized_map(const char (&energized_map)[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (*(*(energized_map + y) + x)) {
                cout << (int) *(*(energized_map + y) + x);
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }
    cout << endl;
}
