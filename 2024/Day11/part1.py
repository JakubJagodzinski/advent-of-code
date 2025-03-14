def load_stones():
    with open('input.txt', 'rt') as f:
        stones = f.readline()
        stones = stones.replace('\n', '').split(' ')
        stones = [int(stone) for stone in stones]
        return stones

def perform_blink(stones):
    new_stones = []
    for stone in stones:
        if stone == 0:
            new_stones.append(1)
        elif len(str(stone)) % 2 == 0:
            stone_as_str = str(stone)
            stone_a = stone_as_str[:len(stone_as_str) // 2]
            stone_b = stone_as_str[len(stone_as_str) // 2:]
            new_stones.append(int(stone_a))
            new_stones.append(int(stone_b))
        else:
            new_stones.append(stone * 2024)
    return new_stones

if __name__ == '__main__':
    stones = load_stones()
    for i in range(75):
        stones = perform_blink(stones)
        print(i, len(stones))
