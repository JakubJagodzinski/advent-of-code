def load_reports():
    with open('input.txt', 'rt') as f:
        reports = list()
        for line in f.readlines():
            line = line.replace('\n', '')
            numbers = [int(number) for number in line.split(' ')]
            reports.append(numbers)
        return reports


def is_report_save(report):
    is_correct = True
    ascending = True
    descending = True
    for i in range(len(report) - 1):
        if report[i] > report[i + 1]:
            ascending = False
        elif report[i] < report[i + 1]:
            descending = False
        difference = abs(report[i] - report[i + 1])
        if difference < 1 or difference > 3:
            is_correct = False
            break
    return is_correct and (ascending or descending)


def count_save_reports(reports):
    counter = 0
    for report in reports:
        if is_report_save(report):
            counter += 1
    return counter


if __name__ == '__main__':
    reports = load_reports()
    print(count_save_reports(reports))
