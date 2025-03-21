#include <iostream>

#define GIVEN_NUMBERS 10
#define MY_NUMBERS 25

using namespace std;

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Couldn't open file" << endl;
        return 4;
    }
    size_t total_points = 0;
    while (!feof(fin)) {
        char garbage[21];
        fscanf(fin, "%20[^:]: ", garbage);
        int numbers[GIVEN_NUMBERS];
        for (int i = 0; i < GIVEN_NUMBERS; ++i) {
            fscanf(fin, "%d", (numbers + i));
        }
        fscanf(fin, "%1s", garbage);
        int points = 0;
        for (int i = 0; i < MY_NUMBERS; ++i) {
            int number;
            fscanf(fin, "%d", &number);
            for (int j = 0; j < GIVEN_NUMBERS; ++j) {
                if (number == *(numbers + j)) {
                    if (!points) {
                        points = 1;
                    } else {
                        points *= 2;
                    }
                    break;
                }
            }
            fgetc(fin);
        }
        total_points += points;
    }
    fclose(fin);
    cout << total_points;
    return 0;
}
