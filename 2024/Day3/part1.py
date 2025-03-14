import re

if __name__ == '__main__':
    with open('input.txt', 'rt') as f:
        pattern = r'mul\((\d+),(\d+)\)'
        result = 0
        for line in f.readlines():
            matches = re.findall(pattern, line)
            for match in matches:
                result += int(match[0]) * int(match[1])
        print(result)
