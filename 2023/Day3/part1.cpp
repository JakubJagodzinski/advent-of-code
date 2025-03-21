#include <iostream>

#define WIDTH 140
#define HEIGHT 140

using namespace std;

struct point_t {
    int x;
    int y;
};

int main() {
    char schematic[HEIGHT][WIDTH];
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Couldn't open file" << endl;
        return 4;
    }
    for (int y = 0; y < HEIGHT; ++y) {
        fscanf(fin, "%140s\n", *(schematic + y));
    }
    fclose(fin);
    size_t sum = 0;
    for (int y = 0; y < HEIGHT; ++y) {
        struct point_t point_begin = {-1, -1};
        struct point_t point_end = {0, 0};
        int number = 0;
        for (int x = 0; x < WIDTH; ++x) {
            if (isdigit(*(*(schematic + y) + x))) {
                if (point_begin.x == -1) {
                    point_begin = {x, y};
                }
                number *= 10;
                number += *(*(schematic + y) + x) - '0';
            }
            if (point_begin.x != -1 and (!isdigit(*(*(schematic + y) + x)) or x == WIDTH - 1)) {
                if (!isdigit(*(*(schematic + y) + x))) {
                    point_end = {x - 1, y};
                } else {
                    point_end = {x, y};
                }
                bool is_adjacent = false;
                for (int i = point_begin.x; i <= point_end.x; ++i) {
                    if (i > 0 and !isdigit(*(*(schematic + y) + (i - 1))) and *(*(schematic + y) + (i - 1)) != '.') {
                        is_adjacent = true;
                        break;
                    }
                    if (i < WIDTH - 1 and !isdigit(*(*(schematic + y) + (i + 1))) and *(*(schematic + y) + (i + 1)) != '.') {
                        is_adjacent = true;
                        break;
                    }
                    if (y > 0 and i > 0 and !isdigit(*(*(schematic + y - 1) + (i - 1))) and *(*(schematic + y - 1) + (i - 1)) != '.') {
                        is_adjacent = true;
                        break;
                    }
                    if (y > 0 and i < WIDTH - 1 and !isdigit(*(*(schematic + y - 1) + (i + 1))) and *(*(schematic + y - 1) + (i + 1)) != '.') {
                        is_adjacent = true;
                        break;
                    }
                    if (y > 0 and !isdigit(*(*(schematic + y - 1) + (i))) and *(*(schematic + y - 1) + (i)) != '.') {
                        is_adjacent = true;
                        break;
                    }
                    if (y < HEIGHT - 1 and !isdigit(*(*(schematic + y + 1) + (i))) and *(*(schematic + y + 1) + (i)) != '.') {
                        is_adjacent = true;
                        break;
                    }
                    if (y < HEIGHT - 1 and i < WIDTH - 1 and !isdigit(*(*(schematic + y + 1) + (i + 1))) and *(*(schematic + y + 1) + (i + 1)) != '.') {
                        is_adjacent = true;
                        break;
                    }
                    if (y < HEIGHT - 1 and i > 0 and !isdigit(*(*(schematic + y + 1) + (i - 1))) and *(*(schematic + y + 1) + (i - 1)) != '.') {
                        is_adjacent = true;
                        break;
                    }
                }
                if (is_adjacent) {
                    sum += number;
                }
                number = 0;
                point_begin = {-1, -1};
                point_end = {0, 0};
            }
        }
    }
    cout << sum;
    return 0;
}
