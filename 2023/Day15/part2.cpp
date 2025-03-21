#include <iostream>
#include <cstring>

using namespace std;

#define BOXES 256
#define LENS 10
#define LENGTH 20

int get_lens_in_box_number(const char (&boxes)[BOXES][LENS][LENGTH], int box_nr);

void display_boxes(const char (&boxes)[BOXES][LENS][LENGTH]);

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Failed to open file" << endl;
        return -1;
    }
    char boxes[BOXES][LENS][LENGTH] = {0};
    while (!feof(fin)) {
        char instruction[LENGTH] = {0};
        char *str_ptr = instruction;
        fscanf(fin, "%25[^,],", instruction);
        //cout << "After \"" << instruction << "\":" << endl;
        int box_nr = 0;
        while (*str_ptr != '-' and *str_ptr != '=') {
            box_nr += (unsigned char) *str_ptr;
            box_nr *= 17;
            box_nr %= 256;
            ++str_ptr;
        }
        char lens_name[LENGTH] = {0};
        char *operation = ((strchr(instruction, '-') ? strchr(instruction, '-') : strchr(instruction, '=')));
        strncpy(lens_name, instruction, operation - instruction);
        bool found = false;
        int lens_in_box = get_lens_in_box_number(boxes, box_nr);
        for (int lens_nr = 0; lens_nr < lens_in_box; ++lens_nr) {
            if ((strlen(lens_name) == strlen(boxes[box_nr][lens_nr]) - 1) and strncmp(boxes[box_nr][lens_nr], lens_name, strlen(lens_name)) == 0) {
                switch (*operation) {
                    case '-':
                        memset(boxes[box_nr][lens_nr], 0, LENGTH * sizeof(char));
                        for (int i = lens_nr; i < lens_in_box; ++i) {
                            strncpy(boxes[box_nr][i], boxes[box_nr][i + 1], LENGTH);
                        }
                        break;
                    case '=':
                        boxes[box_nr][lens_nr][strlen(boxes[box_nr][lens_nr]) - 1] = *(operation + 1);
                        break;
                }
                found = true;
                break;
            }
        }
        if (!found and *operation == '=') {
            strcpy(boxes[box_nr][lens_in_box], lens_name);
            boxes[box_nr][lens_in_box][strlen(boxes[box_nr][lens_in_box])] = *(operation + 1);
            boxes[box_nr][lens_in_box][strlen(boxes[box_nr][lens_in_box])] = '\0';
        }
        //display_boxes(boxes);
        //cout << endl;
    }
    size_t total_focusing_power = 0;
    for (int box_nr = 0; box_nr < BOXES; ++box_nr) {
        int lens_in_box = get_lens_in_box_number(boxes, box_nr);
        if (lens_in_box) {
            for (int lens_nr = 0; lens_nr < lens_in_box; ++lens_nr) {
                total_focusing_power += (box_nr + 1) * (lens_nr + 1) * (boxes[box_nr][lens_nr][strlen(boxes[box_nr][lens_nr]) - 1] - '0');
            }
        }
    }
    cout << "Total focusing power: " << total_focusing_power << endl;
    return 0;
}

int get_lens_in_box_number(const char (&boxes)[BOXES][LENS][LENGTH], int box_nr) {
    int counter = 0;
    for (int lens_nr = 0; lens_nr < LENS; ++lens_nr) {
        if (boxes[box_nr][lens_nr][0] == '\0') {
            break;
        }
        ++counter;
    }
    return counter;
}

void display_boxes(const char (&boxes)[BOXES][LENS][LENGTH]) {
    for (int box_nr = 0; box_nr < BOXES; ++box_nr) {
        int lens_in_box = get_lens_in_box_number(boxes, box_nr);
        if (lens_in_box) {
            cout << "Box " << box_nr << ": ";
            for (int lens_nr = 0; lens_nr < lens_in_box; ++lens_nr) {
                int name_len = (int) strlen(boxes[box_nr][lens_nr]) - 1;
                cout << "[";
                for (int name_index = 0; name_index < name_len; ++name_index) {
                    cout << boxes[box_nr][lens_nr][name_index];
                }
                cout << " " << boxes[box_nr][lens_nr][name_len] << "] ";
            }
            cout << endl;
        }
    }
}
