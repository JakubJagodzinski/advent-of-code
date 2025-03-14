if __name__ == "__main__":
    first = []
    second = []
    with open('input.txt', 'r') as f:
        for line in f.readlines():
            line = line.replace('\n', '').split(' ')
            line = [element for element in line if element != '']
            first.append(int(line[0]))
            second.append(int(line[1]))
    first.sort()
    second.sort()
    sum = 0
    for i in range(len(first)):
        sum += abs(first[i] - second[i])
    print(sum)
