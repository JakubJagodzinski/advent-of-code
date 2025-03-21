#include <iostream>
#include <cstring>

using namespace std;

#define ROW_COL 21

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Couldn't open file \"input.txt\"" << endl;
        return 4;
    }
    size_t sum_of_predictions = 0;
    while (!feof(fin)) {
        char buffer[201];
        char *buffer_ptr = buffer;
        fscanf(fin, "%200[^\n]\n", buffer);
        int history[ROW_COL][ROW_COL];
        int counter = 0;
        while (buffer_ptr) {
            if (sscanf(buffer_ptr, "%d", (*(history) + counter))!= 1) {
                break;
            }
            buffer_ptr = strchr(buffer_ptr, ' ');
            if (buffer_ptr) {
                ++buffer_ptr;
            }
            ++counter;
        }
        int last_row_index;
        int last_row_length;
        for (int row = 0; row < ROW_COL - 1; ++row) {
            int zeros_counter = 0;
            for (int col = 0; col < counter - 1 - row; ++col) {
                *(*(history + row + 1) + col) = *(*(history + row) + col + 1) - *(*(history + row) + col);
                if (*(*(history + row + 1) + col) == 0) {
                    ++zeros_counter;
                }
            }
            if (zeros_counter == counter - 1 - row) {
                last_row_index = row + 1;
                last_row_length = zeros_counter + 1;
                *(*(history + row + 1) + last_row_length - 1) = 0;
                break;
            }
        }
        for (int row = last_row_index - 1; row >= 0; --row) {
            *(*(history + row) + last_row_length + (last_row_index - row) - 1) = *(*(history + row) + last_row_length + (last_row_index - row) - 2) + *(*(history + row + 1) + last_row_length + (last_row_index - row) - 2);
        }
        sum_of_predictions += *(*(history) + counter);
    }
    fclose(fin);
    cout << "Sum of predictions: " << sum_of_predictions << endl;
    return 0;
}
