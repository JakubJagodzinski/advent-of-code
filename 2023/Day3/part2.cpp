#include <iostream>

#define WIDTH 140
#define HEIGHT 140

using namespace std;

struct point_t {
    int x;
    int y;
};

int read_number (int x, int y, char (&schematic)[HEIGHT][WIDTH]) {
    struct point_t start_point = {-1, -1};
    int i = x;
    while (true) {
        if (i == 0 or !isdigit(*(*(schematic + y) + i))) {
            if (!isdigit(*(*(schematic + y) + i))) {
                start_point = {i + 1, y};
            } else {
                start_point = {i, y};
            }
            break;
        }
        --i;
    }
    struct point_t end_point = {-1, -1};
    i = x;
    while (true) {
        if (i == WIDTH - 1 or !isdigit(*(*(schematic + y) + i))) {
            if (!isdigit(*(*(schematic + y) + i))) {
                end_point = {i - 1, y};
            } else {
                end_point = {i, y};
            }
            break;
        }
        ++i;
    }
    int number = 0;
    for (int k = start_point.x; k <= end_point.x; ++k) {
        number *= 10;
        number += *(*(schematic + y) + k) - '0';
        *(*(schematic + y) + k) = '.';
    }
    return number;
}

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
        for (int x = 0; x < WIDTH; ++x) {
            if (*(*(schematic + y) + x) == '*') {
                int first_number = 0;
                int second_number = 0;
                if (x > 0 and isdigit(*(*(schematic + y) + (x - 1)))) {
                    if (!first_number) {
                        first_number = read_number(x - 1, y, schematic);
                    } else {
                        second_number = read_number(x - 1, y, schematic);
                    }
                }
                if (x < WIDTH - 1 and isdigit(*(*(schematic + y) + (x + 1)))) {
                    if (!first_number) {
                        first_number = read_number(x + 1, y, schematic);
                    } else {
                        second_number = read_number(x + 1, y, schematic);
                    }
                }
                if (y < HEIGHT - 1 and x < WIDTH - 1 and isdigit(*(*(schematic + y + 1) + (x + 1)))) {
                    if (!first_number) {
                        first_number = read_number(x + 1, y + 1, schematic);
                    } else {
                        second_number = read_number(x + 1, y + 1, schematic);
                    }
                }
                if (y < HEIGHT - 1 and x > 0 and isdigit(*(*(schematic + y + 1) + (x - 1)))) {
                    if (!first_number) {
                        first_number = read_number(x - 1, y + 1, schematic);
                    } else {
                        second_number = read_number(x - 1, y + 1, schematic);
                    }
                }
                if (y > 0 and x < WIDTH - 1 and isdigit(*(*(schematic + y - 1) + (x + 1)))) {
                    if (!first_number) {
                        first_number = read_number(x + 1, y - 1, schematic);
                    } else {
                        second_number = read_number(x + 1, y - 1, schematic);
                    }
                }
                if (y > 0 and x > 0 and isdigit(*(*(schematic + y - 1) + (x - 1)))) {
                    if (!first_number) {
                        first_number = read_number(x - 1, y - 1, schematic);
                    } else {
                        second_number = read_number(x - 1, y - 1, schematic);
                    }
                }
                if (y > 0 and isdigit(*(*(schematic + y - 1) + (x)))) {
                    if (!first_number) {
                        first_number = read_number(x, y - 1, schematic);
                    } else {
                        second_number = read_number(x, y - 1, schematic);
                    }
                }
                if (y < HEIGHT - 1 and isdigit(*(*(schematic + y + 1) + (x)))) {
                    if (!first_number) {
                        first_number = read_number(x, y + 1, schematic);
                    } else {
                        second_number = read_number(x, y + 1, schematic);
                    }
                }
                sum += first_number * second_number;
            }
        }
    }
    cout << sum;
    return 0;
}
