#include <iostream>

using namespace std;

#define WIDTH 131
#define HEIGHT 131
#define MAX_MOVES 64

struct point_t {
    int x;
    int y;
};

void display_map(const char (&map)[HEIGHT][WIDTH]);

void mark_field(char (&map)[HEIGHT][WIDTH], struct point_t position, char symbol);

void mark_fields(char (&map)[HEIGHT][WIDTH], struct point_t current_position);

void make_move(char (&map)[HEIGHT][WIDTH], int max_counter);

size_t count_fields(const char (&map)[HEIGHT][WIDTH]);

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
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (*(*(map + y) + x) == 'S') {
                *(*(map + y) + x) = 'O';
                break;
            }
        }
    }
    make_move(map, MAX_MOVES);
    cout << "PART ONE" << endl;
    display_map(map);
    cout << "Total fields: " << count_fields(map) << endl;
    cout << "PART TWO" << endl;
    return 0;
}

void display_map(const char (&map)[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            cout << *(*(map + y) + x);
        }
        cout << endl;
    }
    cout << endl;
}

void mark_fields(char (&map)[HEIGHT][WIDTH], struct point_t current_position) {
    static char symbol = 'O';
    if (*(*(map + current_position.y) + current_position.x) == 'O') {
        symbol = 'o';
    } else {
        symbol = 'O';
    }
    *(*(map + current_position.y) + current_position.x) = '.';
    mark_field(map, {current_position.x + 1, current_position.y}, symbol);
    mark_field(map, {current_position.x - 1, current_position.y}, symbol);
    mark_field(map, {current_position.x, current_position.y + 1}, symbol);
    mark_field(map, {current_position.x, current_position.y - 1}, symbol);
}

void mark_field(char (&map)[HEIGHT][WIDTH], struct point_t position, char symbol) {
    if (position.x >= 0 and position.x < WIDTH and position.y >= 0 and position.y < HEIGHT and *(*(map + position.y) + position.x) != '#') {
        *(*(map + position.y) + position.x) = symbol;
    }
}

void make_move(char (&map)[HEIGHT][WIDTH], int max_counter) {
    for (int i = 0; i < max_counter; ++i) {
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                if ((i % 2 == 0 and *(*(map + y) + x) == 'O') or (i % 2 != 0 and *(*(map + y) + x) == 'o')) {
                    mark_fields(map, {x, y});
                }
            }
        }
    }
}

size_t count_fields(const char (&map)[HEIGHT][WIDTH]) {
    size_t counter = 0;
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (*(*(map + y) + x) == 'O' or *(*(map + y) + x) == 'o') {
                ++counter;
            }
        }
    }
    return counter;
}