#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct rule_t {
    char part;
    char condition;
    int value;
    string dst_name;
};

struct workflow_t {
    string name;
    vector <struct rule_t> rules;
    string otherwise_dst;
};

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == nullptr) {
        cout << "Failed to open file" << endl;
        return -1;
    }
    vector <struct workflow_t> workflows;
    while (true) {
        char workflow_name[21] = {0};
        char rules_buffer[101] = {0};
        if (fscanf(fin, "%20[^{]{%100[^}]}\n", workflow_name, rules_buffer) != 2) {
            break;
        }
        struct workflow_t new_workflow;
        new_workflow.name = string(workflow_name);
        char *rules_buffer_ptr = rules_buffer;
        while (rules_buffer_ptr) {
            struct rule_t new_rule;
            char dst_name[21] = {0};
            if (strchr(rules_buffer_ptr, ':')) {
                sscanf(rules_buffer_ptr, "%c%c%d:%20[^,]", &new_rule.part, &new_rule.condition, &new_rule.value, dst_name);
                new_rule.dst_name = string(dst_name);
                new_workflow.rules.push_back(new_rule);
            } else {
                sscanf(rules_buffer_ptr, "%20s", dst_name);
                new_workflow.otherwise_dst = string(dst_name);
            }
            rules_buffer_ptr = strchr(rules_buffer_ptr, ',');
            if (rules_buffer_ptr) {
                ++rules_buffer_ptr;
            }
        }
        workflows.push_back(new_workflow);
    }
    size_t ratings_sum = 0;
    struct workflow_t *starting_workflow;
    for (auto & workflow : workflows) {
        if (workflow.name == "in") {
            starting_workflow = &workflow;
            break;
        }
    }
    while (!feof(fin)) {
        int x;
        int m;
        int a;
        int s;
        fscanf(fin, "{x=%d,m=%d,a=%d,s=%d}\n", &x, &m, &a, &s);
        struct workflow_t *current = starting_workflow;
        while (true) {
            string next_workflow_name = current->otherwise_dst;
            for (auto & rule : current->rules) {
                bool condition_met = false;
                switch (rule.part) {
                    case 'x':
                        if ((rule.condition == '>' and x > rule.value) or (rule.condition == '<' and x < rule.value)) {
                            condition_met = true;
                        }
                        break;
                    case 'm':
                        if ((rule.condition == '>' and m > rule.value) or (rule.condition == '<' and m < rule.value)) {
                            condition_met = true;
                        }
                        break;
                    case 'a':
                        if ((rule.condition == '>' and a > rule.value) or (rule.condition == '<' and a < rule.value)) {
                            condition_met = true;
                        }
                        break;
                    case 's':
                        if ((rule.condition == '>' and s > rule.value) or (rule.condition == '<' and s < rule.value)) {
                            condition_met = true;
                        }
                        break;
                }
                if (condition_met) {
                    next_workflow_name = rule.dst_name;
                    break;
                }
            }
            if (next_workflow_name == "R") {
                break;
            }
            if (next_workflow_name == "A") {
                ratings_sum += x + m + a + s;
                break;
            }
            for (auto & workflow : workflows) {
                if (workflow.name == next_workflow_name) {
                    current = &workflow;
                    break;
                }
            }
        }
    }
    fclose(fin);
    cout << "Ratings sum for all accepted parts = " << ratings_sum << endl;
    return 0;
}
