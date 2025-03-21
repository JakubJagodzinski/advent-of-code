#include <iostream>

using namespace std;

#define WIDTH 100
#define HEIGHT 100

void roll_north(char (&map)[HEIGHT][WIDTH]);

void roll_south(char (&map)[HEIGHT][WIDTH]);

void roll_east(char (&map)[HEIGHT][WIDTH]);

void roll_west(char (&map)[HEIGHT][WIDTH]);

size_t count_load(const char (&map)[HEIGHT][WIDTH]);

void display_map(const char (&map)[HEIGHT][WIDTH]);

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
        fscanf(fin, "\n");
    }
    fclose(fin);
    for (size_t i = 0; i < 1000; ++i) {
        roll_north(map);
        roll_west(map);
        roll_south(map);
        roll_east(map);
        //display_map(map);
    }
    cout << "PART TWO:" << endl;
    cout << "Total load: " << count_load(map) << endl;
    return 0;
}

void roll_north(char (&map)[HEIGHT][WIDTH]) {
    for (int x = 0; x < WIDTH; ++x) {
        int index_empty = 0;
        for (int y = 0; y < HEIGHT; ++y) {
            switch (*(*(map + y) + x)) {
                case '#':
                    index_empty = y + 1;
                    break;
                case 'O':
                    *(*(map + index_empty) + x) = 'O';
                    if (index_empty != y) {
                        *(*(map + y) + x) = '.';
                        ++index_empty;
                    } else {
                        index_empty = y + 1;
                    }
                    break;
            }
        }
    }
}

void roll_south(char (&map)[HEIGHT][WIDTH]) {
    for (int x = 0; x < WIDTH; ++x) {
        int index_empty = HEIGHT - 1;
        for (int y = HEIGHT - 1; y >= 0; --y) {
            switch (*(*(map + y) + x)) {
                case '#':
                    index_empty = y - 1;
                    break;
                case 'O':
                    *(*(map + index_empty) + x) = 'O';
                    if (index_empty != y) {
                        *(*(map + y) + x) = '.';
                        --index_empty;
                    } else {
                        index_empty = y - 1;
                    }
                    break;
            }
        }
    }
}

void roll_east(char (&map)[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; ++y) {
        int index_empty = WIDTH - 1;
        for (int x = WIDTH - 1; x >= 0; --x) {
            switch (*(*(map + y) + x)) {
                case '#':
                    index_empty = x - 1;
                    break;
                case 'O':
                    *(*(map + y) + index_empty) = 'O';
                    if (index_empty != x) {
                        *(*(map + y) + x) = '.';
                        --index_empty;
                    } else {
                        index_empty = x - 1;
                    }
                    break;
            }
        }
    }
}

void roll_west(char (&map)[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; ++y) {
        int index_empty = 0;
        for (int x = 0; x < WIDTH; ++x) {
            switch (*(*(map + y) + x)) {
                case '#':
                    index_empty = x + 1;
                    break;
                case 'O':
                    *(*(map + y) + index_empty) = 'O';
                    if (index_empty != x) {
                        *(*(map + y) + x) = '.';
                        ++index_empty;
                    } else {
                        index_empty = x + 1;
                    }
                    break;
            }
        }
    }
}

size_t count_load(const char (&map)[HEIGHT][WIDTH]) {
    size_t total_load = 0;
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            if (*(*(map + y) + x) == 'O') {
                total_load += HEIGHT - y;
            }
        }
    }
    return total_load;
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
