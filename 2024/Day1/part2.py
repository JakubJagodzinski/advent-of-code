if __name__ == "__main__":
    first = []
    second = []
    with open('input.txt', 'r') as f:
        for line in f.readlines():
            line = line.replace('\n', '').split(' ')
            line = [element for element in line if element != '']
            first.append(int(line[0]))
            second.append(int(line[1]))
    similarity_score = 0
    for i in range(len(first)):
        similarity_score += first[i] * second.count(first[i])
    print(similarity_score)
