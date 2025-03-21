#include <iostream>
#include <cstring>

using namespace std;

#define MAX_RED_CUBES 12
#define MAX_GREEN_CUBES 13
#define MAX_BLUE_CUBES 14

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Couldn't open file" << endl;
        return 4;
    }
    size_t id_sum = 0;
    size_t id = 1;
    size_t total_power = 0;
    while (!feof(fin)) {
        char buffer[201] = {0};
        char garbage[10];
        fscanf(fin, "%10[^:]: %200[^\n]\n", garbage, buffer);
        bool possible = true;
        char *buffer_position = buffer;
        int red_cubes_max = 1;
        int green_cubes_max = 1;
        int blue_cubes_max = 1;
        while (buffer_position) {
            char set[31] = {0};
            sscanf(buffer_position, "%30[^;\n]", set);
            buffer_position = strchr(buffer_position, ';');
            if (buffer_position) {
                buffer_position += 2;
            }
            int red_cubes = 0;
            int green_cubes = 0;
            int blue_cubes = 0;
            char *set_position = set;
            while (set_position) {
                char color[10] = {0};
                int quantity = 0;
                sscanf(set_position, "%d %9[^,]", &quantity, color);
                set_position = strchr(set_position, ',');
                if (set_position) {
                    set_position += 2;
                }
                if (strcmp("red", color) == 0) {
                    red_cubes = quantity;
                    if (red_cubes > red_cubes_max) {
                        red_cubes_max = red_cubes;
                    }
                } else if (strcmp("green", color) == 0) {
                    green_cubes = quantity;
                    if (green_cubes > green_cubes_max) {
                        green_cubes_max = green_cubes;
                    }
                } else if (strcmp("blue", color) == 0) {
                    blue_cubes = quantity;
                    if (blue_cubes > blue_cubes_max) {
                        blue_cubes_max = blue_cubes;
                    }
                }
                if (red_cubes > MAX_RED_CUBES or green_cubes > MAX_GREEN_CUBES or blue_cubes > MAX_BLUE_CUBES) {
                    possible = false;
                }
            }
        }
        total_power += red_cubes_max * green_cubes_max * blue_cubes_max;
        if (possible) {
            id_sum += id;
        }
        ++id;
    }
    fclose(fin);
    cout << "PART ONE:" << endl;
    cout << "Total power: " << total_power;
    return 0;
}
