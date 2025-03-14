def read_rules_and_updates():
    with open('input.txt', 'rt') as file:
        rules = []
        rules_part = True
        updates = []
        for line in file.readlines():
            if line == '\n':
                rules_part = False
                continue
            if rules_part:
                rules.append(line.replace('\n', '').split('|'))
            else:
                updates.append(line.replace('\n', '').split(','))
    rules = [[int(rule_as_int) for rule_as_int in rule] for rule in rules]
    updates = [[int(update_as_int) for update_as_int in update] for update in updates]
    return rules, updates


def find_rule(rules, before=None, after=None):
    for rule in rules:
        if rule[0] == before and rule[1] == after:
            return rule


if __name__ == '__main__':
    rules, correct_updates = read_rules_and_updates()
    incorrect_updates = []
    for correct_update in correct_updates:
        check_next_update = False
        for i in range(len(correct_update) - 1):
            if check_next_update:
                break
            for j in range(len(correct_update) - 1 - i):
                if find_rule(rules, before=correct_update[j + 1], after=correct_update[j]):
                    incorrect_updates.append(correct_update)
                    check_next_update = True
                    break
    correct_updates = [update for update in correct_updates if update not in incorrect_updates]
    correct_updates_middles_sum = 0
    for correct_update in correct_updates:
        correct_updates_middles_sum += correct_update[len(correct_update) // 2]
    print(correct_updates_middles_sum)
