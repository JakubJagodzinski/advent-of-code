#include <iostream>

using namespace std;

#define LENGTH 20

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Failed to open file" << endl;
        return -1;
    }
    size_t hash_sum = 0;
    while (!feof(fin)) {
        char str[LENGTH] = {0};
        fscanf(fin, "%20[^,],", str);
        char *str_ptr = str;
        int current_value = 0;
        while (*str_ptr) {
            current_value += (unsigned char) *str_ptr;
            current_value *= 17;
            current_value %= 256;
            ++str_ptr;
        }
        hash_sum += current_value;
    }
    cout << "Sum of hash: " << hash_sum << endl;
    return 0;
}
