#include <iostream>
#include <cstring>

#define MOVES 754
#define MOVE_LEN 3
#define STARTING_POSITIONS 6

using namespace std;

size_t gcd(size_t a, size_t b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a%b);
}

size_t lcm(size_t a, size_t b) {
    if (a > b) {
        return (a/gcd(a, b)) * b;
    }
    return (b/gcd(a, b)) * a;
}

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Couldn't open file" << endl;
        return 4;
    }
    char move_instruction[301] = {0};
    fscanf(fin, "%300[^\n]\n\n", move_instruction);
    char moves[MOVES][3][MOVE_LEN];
    for (int i = 0; i < MOVES; ++i) {
        fscanf(fin, "%3s = (%3s, %3s)\n", *(*(moves + i) + 0), *(*(moves + i) + 1), *(*(moves + i) + 2));
    }
    fclose(fin);
    int current_positions[STARTING_POSITIONS];
    int current_position_index = 0;
    for (int i = 0; i < MOVES; ++i) {
        if (*(*(*(moves + i) + 0) + 2) == 'A') {
            *(current_positions + current_position_index) = i;
            ++current_position_index;
        }
    }
    char *instr_ptr = move_instruction;
    size_t total_moves[STARTING_POSITIONS] = {0};
    bool is_ready[STARTING_POSITIONS];
    memset(is_ready, false, STARTING_POSITIONS * sizeof(bool));
    int ready_counter = 0;
    while (ready_counter != STARTING_POSITIONS) {
        char *next_moves[STARTING_POSITIONS];
        switch (*instr_ptr) {
            case 'L':
                for (int i = 0; i < STARTING_POSITIONS; ++i) {
                    *(next_moves + i) = *(*(moves + *(current_positions + i)) + 1);
                }
                break;
            case 'R':
                for (int i = 0; i < STARTING_POSITIONS; ++i) {
                    *(next_moves + i) = *(*(moves + *(current_positions + i)) + 2);
                }
                break;
        }
        for (int i = 0; i < STARTING_POSITIONS; ++i) {
            for (int j = 0; j < MOVES; ++j) {
                if (!*(is_ready + i) and strncmp(*(*(moves + j) + 0), *(next_moves + i), 3) == 0) {
                    *(current_positions + i) = j;
                    ++*(total_moves + i);
                    if (*(*(*(moves + *(current_positions + i)) + 0) + 2) == 'Z') {
                        *(is_ready + i) = true;
                        ++ready_counter;
                    }
                }
            }
        }
        ++instr_ptr;
        if (*instr_ptr == '\0') {
            instr_ptr = move_instruction;
        }
    }
    cout << "Put these to LCM caluclator:" << endl;
    for (int i = 0; i < STARTING_POSITIONS; ++i) {
        cout << *(total_moves + i) << endl;
    }
    return 0;
}
