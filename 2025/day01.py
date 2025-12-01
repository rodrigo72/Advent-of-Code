
def part_1():
    pointer = 50
    dial = list(range(100))
    counter = 0
    with open("input.txt", "r") as file:
        for line in file:
            line = line.strip()
            direction = str(line[0])
            distance = int(line[1:])
            if direction == 'L':
                distance = distance * -1
            aux_val = pointer + distance
            pointer = aux_val % 100
            if pointer == 0:
                counter += 1
    return counter


def part_2():
    pointer = 50
    dial = list(range(100))
    counter = 0

    with open("input.txt", "r") as file:
        for line in file:
            line = line.strip()
            direction = str(line[0])
            distance = int(line[1:])

            if direction == 'R':
                distance_to_zero = abs(pointer - 100)
                additional_distance = distance - distance_to_zero
                pointer = additional_distance % 100
            else:
                distance_to_zero = pointer
                additional_distance = distance - distance_to_zero
                pointer = 100 - (additional_distance % 100)

            if additional_distance == 0:
                counter += 1
            elif distance_to_zero != 0 and additional_distance > 0:
                counter += 1 + abs(additional_distance // 100)
            elif additional_distance > 0:
                counter += abs(additional_distance // 100)

    return counter

def part_2_v2():
    pointer = 50
    counter = 0

    with open("input.txt", "r") as file:
        for line in file:
            line = line.strip()
            direction = line[0]
            distance = int(line[1:])

            if direction == 'R':
                distance_to_next_zero = abs(pointer - 100)
                pointer = (pointer + distance) % 100
            elif direction == 'L':
                distance_to_next_zero = pointer
                pointer = (pointer - distance) % 100

            if distance_to_next_zero == 0:
                distance_to_next_zero = 100

            if distance >= distance_to_next_zero:
                counter += 1 + (distance - distance_to_next_zero) // 100

    return counter


if __name__ == '__main__':
    print(f"Part 1: {part_1()}")
    print(f"Part 2: {part_2_v2()}")
