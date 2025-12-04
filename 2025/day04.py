import time
import numpy as np

AREA = [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]


def prepare_matrix(lines):
    matrix = [[0 if ch == '.' else 1 for ch in l.rstrip('\n')] for l in lines]
    return np.pad(np.array(matrix), 1)


def part_1(lines):
    pad_matrix = prepare_matrix(lines)
    count = 0
    for i, row in enumerate(pad_matrix[1:-1], start=1):
        for j, value in enumerate(row[1:-1], start=1):
            if value == 1:
                val = 0
                for i2, j2 in AREA:
                    i2, j2 = i2+i, j2+j 
                    val += pad_matrix[i2][j2]
                if val < 4:
                    count += 1
    return count


def part_2(lines):
    pad_matrix = prepare_matrix(lines)
    count, prev_count = 0, -1
    while count != prev_count:
        coords_removed_rolls = []
        prev_count = count
        for i, row in enumerate(pad_matrix[1:-1], start=1):
            for j, value in enumerate(row[1:-1], start=1):
                if value == 1:
                    val = 0
                    for i2, j2 in AREA:
                        i2, j2 = i2+i, j2+j 
                        val += pad_matrix[i2][j2]
                    if val < 4:
                        coords_removed_rolls.append((i, j))
                        count += 1
        for i, j in coords_removed_rolls:
            pad_matrix[i][j] = 0
    return count


if __name__ == '__main__':
    with open("input.txt", "r") as file:
        lines = file.readlines()

    T = time.time()
    print(part_1(lines))
    print("Runtime (part 1) =", round(time.time() - T, 4), "seconds\n")
    
    T = time.time()
    print(part_2(lines))
    print("Runtime (part 2) =", round(time.time() - T, 4), "seconds\n")
