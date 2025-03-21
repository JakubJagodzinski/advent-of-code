#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cmath>

using namespace std;

#define CODE_LENGTH 6

struct point_t {
    int64_t x;
    int64_t y;
};

size_t count_area(const vector<point_t> &vertices);

size_t count_perimeter(const vector<point_t> &vertices);

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Failed to open file" << endl;
        return -1;
    }
    struct point_t current_position = {0, 0};
    vector<point_t> points;
    points.push_back(current_position);
    while (!feof(fin)) {
        char direction;
        int value;
        char code[CODE_LENGTH];
        fscanf(fin, "%c", &direction);
        fscanf(fin, "%d", &value);
        fscanf(fin, "(#%6s)\n", code);
        switch (direction) {
            case 'U':
                current_position.y -= value;
                break;
            case 'D':
                current_position.y += value;
                break;
            case 'L':
                current_position.x -= value;
                break;
            case 'R':
                current_position.x += value;
                break;
            default:
                break;
        }
        points.push_back(current_position);
    }
    reverse(points.begin(), points.end());
    fseek(fin, 0, SEEK_SET);
    cout << "PART ONE" << endl;
    cout << "Cubic meters of lagoon: " << count_area(points) + count_perimeter(points) / 2 + 1 << endl;
    fclose(fin);
    return 0;
}

size_t count_area(const vector<point_t> &vertices) {
    int64_t sum1 = 0;
    int64_t sum2 = 0;
    size_t vertices_size = vertices.size();
    for (size_t i = 0; i < vertices_size - 1; ++i) {
        sum1 += vertices.at(i).x * vertices.at(i + 1).y;
        sum2 += vertices.at(i).y * vertices.at(i + 1).x;
    }
    sum1 += vertices.at(vertices_size - 1).x * vertices.at(0).y;
    sum2 += vertices.at(0).x * vertices.at(vertices_size - 1).y;
    return abs(sum1 - sum2) / 2;
}

size_t count_perimeter(const vector<point_t> &vertices) {
    size_t perimeter = 0;
    for (size_t i = 0; i < vertices.size() - 1; ++i) {
        perimeter += abs(vertices.at(i).x - vertices.at(i + 1).x) + abs(vertices.at(i).y - vertices.at(i + 1).y);
    }
    perimeter += abs(vertices.at(vertices.size() - 1).x - vertices.at(0).x) + abs(
        vertices.at(vertices.size() - 1).y - vertices.at(0).y);
    return perimeter;
}
