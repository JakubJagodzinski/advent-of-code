#include <iostream>

using namespace std;

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Couldn't open file" << endl;
        return 4;
    }
    char garbage[13];
    size_t time = 0;
    size_t distance = 0;
    fscanf(fin, "%11s", garbage);
    while (true) {
        char c = (char) fgetc(fin);
        if (c == '\n') {
            break;
        }
        if (isdigit(c)) {
            time *= 10;
            time += c - '0';
        }
    }
    fscanf(fin, "%11s", garbage);
    while (true) {
        char c = (char) fgetc(fin);
        if (c == '\n' or feof(fin)) {
            break;
        }
        if (isdigit(c)) {
            distance *= 10;
            distance += c - '0';
        }
    }
    int win_counter = 0;
    for (int j = 0; j <= time; ++j) {
        size_t hold_ms = j;
        size_t ride_ms = time - hold_ms;
        size_t ride_distance = ride_ms * hold_ms;
        if (ride_distance > distance) {
            ++win_counter;
        }
    }
    cout << win_counter;
    fclose(fin);
    return 0;
}
