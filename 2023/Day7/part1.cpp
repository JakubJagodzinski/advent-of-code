#include <iostream>
#include <cstring>

using namespace std;

#define TYPES 13
#define CARDS 1000
#define CARD_LENGTH 5

char order[TYPES] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

/// Every hand is exactly one type. From strongest to weakest, they are:

/// Five of a kind, where all five cards have the same label: AAAAA
/// Four of a kind, where four cards have the same label and one card has a different label: AA8AA
/// Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
/// Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
/// Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
/// One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
/// High card, where all cards' labels are distinct: 23456

int compare_card(char first, char second) {
    int first_power = 0;
    int second_power = 0;
    for (int i = 0; i < TYPES; ++i) {
        if (*(order + i) == first) {
            first_power = i;
        }
        if (*(order + i) == second) {
            second_power = i;
        }
    }
    return first_power - second_power;
}

int *get_types_counter(const char* card) {
    int *counter = new int[TYPES];
    memset(counter, 0, TYPES * sizeof(int));
    for (int i = 0; i < CARD_LENGTH; ++i) {
        for (int j = 0; j < TYPES; ++j) {
            if (*(card + i) == *(order + j)) {
                ++(*(counter + j));
            }
        }
    }
    return counter;
}

bool is_of_a_kind(const char* card, int number) {
    int *counter = get_types_counter(card);
    for (int i = 0; i < TYPES; ++i) {
        if (*(counter + i) == number) {
            delete[] counter;
            return true;
        }
    }
    delete[] counter;
    return false;
}

bool is_full_house(const char* card) {
    return is_of_a_kind(card, 3) and is_of_a_kind(card, 2);
}

bool is_two_pair(const char* card) {
    int *counter = get_types_counter(card);
    int pairs = 0;
    for (int i = 0; i < TYPES; ++i) {
        if (*(counter + i) == 2) {
            ++pairs;
        }
    }
    delete[] counter;
    return pairs == 2;
}

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Couldn't open file" << endl;
        return 4;
    }
    char cards[CARDS][CARD_LENGTH];
    int cards_bid[CARDS];
    for (int i = 0; i < CARDS; ++i) {
        fscanf(fin, "%5s %d\n", *(cards + i), cards_bid + i);
    }
    fclose(fin);
    int cards_power[CARDS] = {0};
    for (int i = 0; i < CARDS; ++i) {
        if (is_of_a_kind(*(cards + i), 5)) {
            *(cards_power + i) = 7;
        } else if (is_of_a_kind(*(cards + i), 4)) {
            *(cards_power + i) = 6;
        } else if (is_full_house(*(cards + i))) {
            *(cards_power + i) = 5;
        } else if (is_of_a_kind(*(cards + i), 3)) {
            *(cards_power + i) = 4;
        } else if (is_two_pair(*(cards + i))) {
            *(cards_power + i) = 3;
        } else if (is_of_a_kind(*(cards + i), 2)) {
            *(cards_power + i) = 2;
        } else {
            *(cards_power + i) = 1;
        }
    }
    for (int i = 0; i < CARDS; ++i) {
        cout << "Card " << i + 1 << ": [";
        for (int j = 0; j < CARD_LENGTH; ++j) {
            cout << *(*(cards + i) + j);
        }
        cout << "] - ";
        switch (*(cards_power + i)) {
            case 7:
                cout << "Five of a kind";
                break;
            case 6:
                cout << "Four of a kind";
                break;
            case 5:
                cout << "Full house";
                break;
            case 4:
                cout << "Three of a kind";
                break;
            case 3:
                cout << "Two pair";
                break;
            case 2:
                cout << "One pair";
                break;
            case 1:
                cout << "High card";
                break;
            default:
                break;
        }
        cout << endl;
    }
    int cards_rank[CARDS] = {0};
    for (int i = 0; i < CARDS; ++i) {
        int highest_rank_index;
        for (int j = 0; j < CARDS; ++j) {
            if (*(cards_rank + j) == 0) {
                highest_rank_index = j;
                break;
            }
        }
        for (int j = 0; j < CARDS; ++j) {
            if (j != highest_rank_index and *(cards_rank + j) == 0) {
                if (*(cards_power + j) > *(cards_power + highest_rank_index)) {
                    highest_rank_index = j;
                } else if (*(cards_power + j) == *(cards_power + highest_rank_index)) {
                    for (int k = 0; k < CARD_LENGTH; ++k) {
                        int compare_result = compare_card(*(*(cards + j) + k), *(*(cards + highest_rank_index) + k));
                        if (compare_result != 0) {
                            if (compare_result > 0) {
                                highest_rank_index = j;
                            }
                            break;
                        }
                    }
                }
            }
        }
        *(cards_power + highest_rank_index) = 0;
        *(cards_rank + highest_rank_index) = CARDS - i;
    }
    size_t total_winnings = 0;
    for (int i = 0; i < CARDS; ++i) {
        total_winnings += *(cards_bid + i) * *(cards_rank + i);
    }
    cout << endl;
    cout << "Total winnings: " << total_winnings << endl;
    return 0;
}
