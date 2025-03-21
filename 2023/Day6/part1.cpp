#include <iostream>

using namespace std;

#define VALUES 4

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Couldn't open file" << endl;
        return 4;
    }
    char garbage[13];
    int times[VALUES];
    int distances[VALUES];
    fscanf(fin, "%11s", garbage);
    for (int i = 0; i < VALUES; ++i) {
        fscanf(fin, "%d", times + i);
    }
    fscanf(fin, "%12s", garbage);
    for (int i = 0; i < VALUES; ++i) {
        fscanf(fin, "%d", distances + i);
    }
    int ratio = 1;
    for (int i = 0; i < VALUES; ++i) {
        int win_counter = 0;
        for (int j = 0; j <= *(times + i); ++j) {
            int hold_ms = j;
            int ride_ms = *(times + i) - hold_ms;
            int distance = ride_ms * hold_ms;
            if (distance > *(distances + i)) {
                ++win_counter;
            }
        }
        if (win_counter) {
            ratio *= win_counter;
        }
    }
    cout << ratio;
    fclose(fin);
    return 0;
}
