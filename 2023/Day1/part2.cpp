#include <iostream>
#include <cstring>

using namespace std;

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Couldn't open file" << endl;
        return 4;
    }
    char digits[9][7] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    size_t sum = 0;
    while (!feof(fin)) {
        char buffer[101] = {0};
        int index = 0;
        fscanf(fin, "%100[^\n]\n", buffer);
        bool first_digit_read = false;
        int first_digit = 0;
        int last_digit = 0;
        while (*(buffer + index)) {
            if (isdigit(*(buffer + index))) {
                if (!first_digit_read) {
                    first_digit = *(buffer + index) - '0';
                    first_digit_read = true;
                } else {
                    last_digit = *(buffer + index) - '0';
                }
            } else {
                for (int i = 0; i < 9; ++i) {
                    if ((strlen(*(digits + i)) <= strlen(buffer + index)) and (strncmp(*(digits + i), buffer + index,
                                                                                   strlen(*(digits + i))) == 0)) {
                        if (!first_digit_read) {
                            first_digit = i + 1;
                            first_digit_read = true;
                        } else {
                            last_digit = i + 1;
                        }
                        break;
                    }
                }
            }
            ++index;
        }
        if (last_digit == 0) {
            last_digit = first_digit;
        }
        sum += (first_digit * 10) + last_digit;
    }
    fclose(fin);
    cout << "PART TWO:" << endl;
    cout << sum << endl;
    return 0;
}
