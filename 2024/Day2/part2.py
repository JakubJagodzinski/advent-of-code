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
        else:
            original = report
            for index_to_remove in range(len(report)):
                temporary = [report[index] for index in range(len(report)) if index != index_to_remove]
                if is_report_save(temporary):
                    counter += 1
                    break
    return counter


if __name__ == '__main__':
    reports = load_reports()
    print(count_save_reports(reports))
