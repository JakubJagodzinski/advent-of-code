#include <iostream>
#include <stack>

#define GIVEN_NUMBERS 10
#define MY_NUMBERS 25
#define TOTAL_CARDS 219

using namespace std;

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Couldn't open file" << endl;
        return 4;
    }
    int cards_given[TOTAL_CARDS][GIVEN_NUMBERS];
    int cards_numbers[TOTAL_CARDS][MY_NUMBERS];
    int card_index = 0;
    while (!feof(fin)) {
        char garbage[21];
        fscanf(fin, "%20[^:]: ", garbage);
        for (int i = 0; i < GIVEN_NUMBERS; ++i) {
            fscanf(fin, "%d", *(cards_given + card_index) + i);
        }
        fscanf(fin, "%3s", garbage);
        for (int i = 0; i < MY_NUMBERS; ++i) {
            fscanf(fin, "%d", *(cards_numbers + card_index) + i);
        }
        ++card_index;
    }
    size_t total_scratchcards = 0;
    stack <int> cards_indexes;
    bool first_cycle = true;
    do {
        for (int i = 0; i < TOTAL_CARDS; ++i) {
            if (!first_cycle and cards_indexes.empty()) {
                break;
            }
            if (first_cycle or (!first_cycle and i == cards_indexes.top())) {
                int correct_numbers = 0;
                for (int j = 0; j < MY_NUMBERS; ++j) {
                    for (int k = 0; k < GIVEN_NUMBERS; ++k) {
                        if (*(*(cards_numbers + i) + j) == *(*(cards_given + i) + k)) {
                            ++correct_numbers;
                        }
                    }
                }
                if (!first_cycle) {
                    cards_indexes.pop();
                }
                for (int j = 0; j < correct_numbers; ++j) {
                    cards_indexes.push(i + j + 1);
                    ++total_scratchcards;
                }
            }
        }
        first_cycle = false;
    } while (!cards_indexes.empty());
    fclose(fin);
    cout << total_scratchcards + TOTAL_CARDS << endl;
    return 0;
}
