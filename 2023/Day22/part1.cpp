#include <iostream>
#include <vector>

using namespace std;

#define TOTAL_CUBES 1249

struct point_t {
    int x;
    int y;
    int z;
};

struct cube_t {
    struct point_t begin;
    struct point_t end;
};

void swap_cubes_vertically(vector <struct cube_t> &cubes);

void settle_cubes_vertically(vector <struct cube_t> &cubes);

int count_safe_disintegration(vector <struct cube_t> (&cubes));

void display_cubes(const vector <struct cube_t> &cubes);

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Failed to open file" << endl;
        return -1;
    }
    vector <struct cube_t> cubes;
    for (int i = 0; i < TOTAL_CUBES; ++i) {
        struct cube_t cube = {0, 0, 0, 0, 0, 0};
        fscanf(fin, "%d,%d,%d~%d,%d,%d\n", &cube.begin.x, &cube.begin.y, &cube.begin.z,
               &cube.end.x, &cube.end.y, &cube.end.z);
        cubes.push_back(cube);
    }
    swap_cubes_vertically(cubes);
    settle_cubes_vertically(cubes);
    //display_cubes(cubes);
    int counter = count_safe_disintegration(cubes);
    cout << "Cubes that can be safely disintegrated: " << counter << endl;
    fclose(fin);
    return 0;
}

void swap_cubes_vertically(vector <struct cube_t> &cubes) {
    for (int i = 0; i < TOTAL_CUBES - 1; ++i) {
        for (int j = 0; j < TOTAL_CUBES - 1 - i; ++j) {
            if (cubes.at(j).begin.z > cubes.at(j + 1).begin.z) {
                struct cube_t temp = cubes[j];
                cubes.at(j) = cubes[j + 1];
                cubes.at(j + 1) = temp;
            }
        }
    }
}

void settle_cubes_vertically(vector <struct cube_t> &cubes) {
    for (int i = 0; i < TOTAL_CUBES; ++i) {
        int new_z = 1;
        for (int j = 0; j < TOTAL_CUBES; ++j) {
            if (j != i and cubes.at(j).end.z < cubes.at(i).begin.z) {
                if (((cubes.at(i).begin.x <= cubes.at(j).end.x) and (cubes.at(i).end.x >= cubes.at(j).begin.x)) and
                    ((cubes.at(i).begin.y <= cubes.at(j).end.y) and (cubes.at(i).end.y >= cubes.at(j).begin.y))) {
                    if (cubes.at(j).end.z + 1 > new_z) {
                        new_z = cubes.at(j).end.z + 1;
                    }
                }
            }
        }
        int offset = cubes.at(i).begin.z - new_z;
        cubes.at(i).begin.z -= offset;
        cubes.at(i).end.z -= offset;
    }
}

int count_safe_disintegration(vector <struct cube_t> (&cubes)) {
    int counter = TOTAL_CUBES;
    for (int k = 0; k < TOTAL_CUBES; ++k) {
        struct cube_t temp = cubes.at(k);
        cubes.erase(cubes.begin() + k);
        for (int i = 0; i < TOTAL_CUBES - 1; ++i) {
            int new_z = 1;
            for (int j = 0; j < TOTAL_CUBES - 1; ++j) {
                if (j != i and cubes.at(j).end.z < cubes.at(i).begin.z) {
                    if (((cubes.at(i).begin.x <= cubes.at(j).end.x) and (cubes.at(i).end.x >= cubes.at(j).begin.x)) and
                        ((cubes.at(i).begin.y <= cubes.at(j).end.y) and (cubes.at(i).end.y >= cubes.at(j).begin.y))) {
                        if (cubes.at(j).end.z + 1 > new_z) {
                            new_z = cubes.at(j).end.z + 1;
                        }
                    }
                }
            }
            int offset = cubes.at(i).begin.z - new_z;
            if (offset > 0) {
                --counter;
                break;
            }
        }
        cubes.insert(cubes.begin() + k, temp);
    }
    return counter;
}

void display_cubes(const vector <struct cube_t> &cubes) {
    cout << "[x,y,z][x,y,z]" << endl;
    for (int i = 0; i < TOTAL_CUBES; ++i) {
        cout << "[" << cubes.at(i).begin.x << "," << cubes.at(i).begin.y << "," << cubes.at(i).begin.z << "]";
        cout << "[" << cubes.at(i).end.x << "," << cubes.at(i).end.y << "," << cubes.at(i).end.z << "]" << endl;
    }
    cout << endl;
}
