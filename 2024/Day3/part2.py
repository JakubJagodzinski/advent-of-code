import re

if __name__ == '__main__':
    with open('input.txt', 'rt') as f:
        pattern = r'mul\((\d+),(\d+)\)'
        result = 0
        all_lines = ''
        for line in f.readlines():
            all_lines += line
        chunks = all_lines.split('do()')
        for chunk in chunks:
            if "don't()" in chunk:
                chunk = chunk.split("don't()")[0]
            matches = re.findall(pattern, chunk)
            for match in matches:
                result += int(match[0]) * int(match[1])
        print(result)
