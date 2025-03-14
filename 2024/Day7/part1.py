def load_equations():
    equations = []
    with open('input.txt', 'rt') as f:
        for line in f.readlines():
            line = line.replace('\n', '')
            result, line = line.split(':')
            result = int(result)
            numbers = line.strip().split(' ')
            numbers = list(map(int, numbers))
            equations.append([result, numbers])
    return equations


MULTIPLY = '*'
ADD = '+'


def fit_equation(expected_result, current_result, numbers, number_index, operand):
    if number_index == len(numbers):
        return False

    if operand == MULTIPLY:
        current_result *= numbers[number_index]
    elif operand == ADD:
        current_result += numbers[number_index]

    if current_result == expected_result and number_index == len(numbers) - 1:
        return True

    number_index += 1

    multiply_result = fit_equation(expected_result, current_result, numbers, number_index, MULTIPLY)
    add_result = fit_equation(expected_result, current_result, numbers, number_index, ADD)

    return multiply_result or add_result


if __name__ == '__main__':
    equations = load_equations()
    correct_sum = 0

    for equation in equations:
        result = equation[0]
        numbers = equation[1]
        if fit_equation(result, numbers[0], numbers, 1, MULTIPLY) or fit_equation(result, 0, numbers, 0, ADD):
            correct_sum += result

    print(correct_sum)
