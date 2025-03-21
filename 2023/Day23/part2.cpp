#include <iostream>

using namespace std;

#define HEIGHT 141
#define WIDTH 141

struct point_t {
    int x;
    int y;
};

struct field_t {
    char field;
    bool visited;
};

struct field_t map[HEIGHT][WIDTH];
struct point_t start_point;
struct point_t end_point;
int max_length = 0;

void find_longest_path(struct point_t position, int length);

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Failed to open file" << endl;
        return -1;
    }
    for (auto & y : map) {
        for (auto & x : y) {
            fscanf(fin, "%c", &x.field);
            x.visited = (x.field == '#');
        }
        fscanf(fin, "\n");
    }
    fclose(fin);
    for (int x = 0; x < WIDTH; ++x) {
        if (map[0][x].field == '.') {
            start_point = {x, 0};
        }
        if (map[HEIGHT - 1][x].field == '.') {
            end_point = {x, HEIGHT - 1};
        }
    }
    map[start_point.y][start_point.x].visited = true;
    cout << "It may take a few minutes... (6470 for this input)" << endl;
    find_longest_path({start_point.x, start_point.y + 1}, 1);
    cout << "Max length = " << max_length << endl;
    return 0;
}

void find_longest_path(struct point_t position, int length) {
    if (position.y == end_point.y and position.x == end_point.x) {
        if (length > max_length) {
            max_length = length;
        }
        return;
    }
    map[position.y][position.x].visited = true;
    if (position.y > 0 and !map[position.y - 1][position.x].visited) {
        find_longest_path({position.x, position.y - 1}, length + 1);
    }
    if (position.y < HEIGHT - 1 and !map[position.y + 1][position.x].visited) {
        find_longest_path({position.x, position.y + 1}, length + 1);
    }
    if (position.x > 0 and !map[position.y][position.x - 1].visited) {
        find_longest_path({position.x - 1, position.y}, length + 1);
    }
    if (position.x < WIDTH - 1 and !map[position.y][position.x + 1].visited) {
        find_longest_path({position.x + 1, position.y}, length + 1);
    }
    map[position.y][position.x].visited = false;
}
