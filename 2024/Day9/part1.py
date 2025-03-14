def load_disk_structure():
    with open('input.txt', 'rt') as f:
        disk_structure = f.read()
        return disk_structure


def establish_disk_content(disk_structure):
    disk_content = list()
    for block_nr in range(len(disk_structure)):
        block_size = int(disk_structure[block_nr])
        if block_nr % 2 == 0:
            for element_nr in range(block_size):
                disk_content.append(str(block_nr // 2))
        else:
            for element_nr in range(block_size):
                disk_content.append('.')
    return disk_content


def move_blocks_leftward(disk_content):
    for right_block_nr in range(len(disk_content) - 1, 0, -1):
        for left_block_nr in range(len(disk_content)):
            if right_block_nr == left_block_nr:
                return disk_content
            if disk_content[left_block_nr] == '.':
                disk_content[left_block_nr] = disk_content[right_block_nr]
                disk_content[right_block_nr] = '.'
                break
    return disk_content


def count_checksum(disk_content):
    checksum = 0
    for block_index, block_nr in enumerate(disk_content):
        if block_nr != '.':
            checksum += block_index * int(block_nr)
    return checksum


if __name__ == '__main__':
    disk_structure = load_disk_structure()
    # print(disk_structure)
    disk_content = establish_disk_content(disk_structure)
    # print(disk_content)
    disk_content = move_blocks_leftward(disk_content)
    # print(disk_content)
    checksum = count_checksum(disk_content)
    print(checksum)
