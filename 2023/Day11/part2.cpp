#include <iostream>

using namespace std;

#define WIDTH 140
#define HEIGHT 140
#define SCALAR 1000000

struct point_t {
    int x;
    int y;
};

struct paths_t {
    point_t a;
    point_t b;
    int length;
};

int main() {
    FILE *fin = fopen("input.txt", "r");
    char map[HEIGHT][WIDTH];
    size_t distances[HEIGHT][WIDTH];
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            *(*(distances + y) + x) = 1;
        }
    }
    for (int y = 0; y < HEIGHT; ++y) {
        fscanf(fin, "%140s\n", *(map + y));
    }
    fclose(fin);
    //check cols for galaxies
    int galaxies_counter = 0;
    for (int x = 0; x < WIDTH; ++x) {
        bool galaxies_found = false;
        for (int y = 0; y < HEIGHT; ++y) {
            if (*(*(map + y) + x) == '#') {
                galaxies_found = true;
                ++galaxies_counter;
            }
        }
        if (!galaxies_found) {
            for (int y = 0; y < HEIGHT; ++y) {
                *(*(distances + y) + x) = SCALAR;
            }
        }
    }
    auto *galaxies_coords = new struct point_t[galaxies_counter];
    int galaxies_index = 0;
    // check rows for galaxies
    for (int y = 0; y < HEIGHT; ++y) {
        bool galaxy_found = false;
        for (int x = 0; x < WIDTH; ++x) {
            if (*(*(map + y) + x) == '#') {
                galaxy_found = true;
                *(galaxies_coords + galaxies_index++) = {x, y};
            }
        }
        if (!galaxy_found) {
            for (int x = 0; x < WIDTH; ++x) {
                *(*(distances + y) + x) = SCALAR;
            }
        }
    }

    size_t shortest_paths_sum = 0;
    for (int i = 0; i < galaxies_counter - 1; ++i) {
        for (int j = i + 1; j < galaxies_counter; ++j) {
            point_t current_point = *(galaxies_coords + i);
            size_t path_length = 0;
            while (true) {
                if (current_point.x < (galaxies_coords + j)->x) {
                    ++current_point.x;
                } else if (current_point.x > (galaxies_coords + j)->x) {
                    --current_point.x;
                } else if (current_point.y < (galaxies_coords + j)->y) {
                    ++current_point.y;
                } else if (current_point.y > (galaxies_coords + j)->y) {
                    --current_point.y;
                }
                if (*(*(map + current_point.y) + current_point.x) != '#') {
                    path_length += *(*(distances + current_point.y) + current_point.x);
                } else {
                    ++path_length;
                }
                if (current_point.x == (galaxies_coords + j)->x and current_point.y == (galaxies_coords + j)->y) {
                    break;
                }
            }
            shortest_paths_sum += path_length;
        }
    }
    cout << "Shortest paths sum: " << shortest_paths_sum << endl;
    free(galaxies_coords);
    return 0;
}
