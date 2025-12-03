import time
from functools import reduce


def part_1(file):
    total = 0
    for line in file:
        bank = line.strip()
        p1, p2 = int(bank[0]), int(bank[1])
        for battery in bank[2:]:
            joltage = int(battery)
            if p2 > p1:
                p1 = p2
                p2 = joltage
            elif p2 < joltage:
                p2 = joltage
        total += p1 * 10 + p2            
    return total


def part_2(file):
    total = 0
    for line in file:
        vals = list(map(int, line.strip()))
        n = len(vals)
        start = 0
        chosen = []
        for pos in range(12): # 12 values need to be found
            end = n - 12 + pos  # interval expands 1 pos at the end every iteraton
            max_idx, max_digit = start, -1
            for idx in range(start, end + 1):  # find max digit within the interval
                v = vals[idx]
                if v > max_digit:
                    max_digit, max_idx = v, idx
                    if max_digit == 9:  # more efficient
                        break
            chosen.append(max_digit)
            start = max_idx + 1  # set the new start
        total += reduce(lambda acc, digit: acc * 10 + digit, chosen, 0)
    return total


if __name__ == '__main__':
    with open("input.txt", "r") as file:
        T = time.time()
        print(part_1(file))
        print("Runtime (part 1) =", round(time.time() - T, 3), "seconds\n")

    with open("input.txt", "r") as file:
        T = time.time()
        print(part_2_v2(file))
        print("Runtime (part 1) =", round(time.time() - T, 3), "seconds\n")
