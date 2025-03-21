#include <iostream>
#include <cstring>

#define MOVES 754
#define MOVE_LEN 3

using namespace std;

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
    int current_position;
    for (int i = 0; i < MOVES; ++i) {
        if (strncmp(*(*(moves + i) + 0), "AAA", 3) == 0) {
            current_position = i;
            break;
        }
    }
    char *instr_ptr = move_instruction;
    size_t total_moves = 0;
    while (instr_ptr) {
        char *next_move;
        switch (*instr_ptr) {
            case 'L':
                next_move = *(*(moves + current_position) + 1);
                break;
            case 'R':
                next_move = *(*(moves + current_position) + 2);
                break;
        }
        for (int i = 0; i < MOVES; ++i) {
            if (strncmp(*(*(moves + i) + 0), next_move, 3) == 0) {
                current_position = i;
                ++total_moves;
                break;
            }
        }
        if (strncmp(*(*(moves + current_position) + 0), "ZZZ", 3) == 0) {
            break;
        }
        ++instr_ptr;
        if (*instr_ptr == '\0') {
            instr_ptr = move_instruction;
        }
    }
    cout << "Total moves: " << total_moves << endl;
    return 0;
}
