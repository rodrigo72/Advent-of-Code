import time
import heapq

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
        bank = line.strip()
        vals = list(map(int, bank))
        n = len(vals)
        prev = -1
        chosen = []
        for pos in range(12):
            start = prev + 1
            end = n - (12 - pos)
            max_digit = -1
            max_idx = start
            for idx in range(start, end + 1):
                v = vals[idx]
                if v > max_digit:
                    max_digit = v
                    max_idx = idx
                    if max_digit == 9:
                        break
            chosen.append(max_digit)
            prev = max_idx
        number = 0
        for d in chosen:
            number = number * 10 + d
        total += number
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
