import time
import numpy as np

def part_1(lines):
    matrix = [[0 if ch == '.' else 1 for ch in l.rstrip('\n')] for l in lines]
    pad_matrix = np.pad(np.array(matrix), 1)
    count = 0
    for i, row in enumerate(pad_matrix[1:-1], start=1):
        for j, value in enumerate(row[1:-1], start=1):
            if value == 1:
                val = (pad_matrix[i][j+1] + pad_matrix[i][j-1] 
                       + pad_matrix[i-1][j] + pad_matrix[i+1][j]  
                       + pad_matrix[i-1][j-1] + pad_matrix[i-1][j+1]
                       + pad_matrix[i+1][j-1] + pad_matrix[i+1][j+1])
                if val < 4:
                    count += 1
    return count


def part_2(lines):
    matrix = [[0 if ch == '.' else 1 for ch in l.rstrip('\n')] for l in lines]
    pad_matrix = np.pad(np.array(matrix), 1)
    count = 0
    prev_count = -1
    while count != prev_count:
        coords_removed_rolls = []
        prev_count = count
        for i, row in enumerate(pad_matrix[1:-1], start=1):
            for j, value in enumerate(row[1:-1], start=1):
                if value == 1:
                    val = (pad_matrix[i][j+1] + pad_matrix[i][j-1] 
                        + pad_matrix[i-1][j] + pad_matrix[i+1][j]  
                        + pad_matrix[i-1][j-1] + pad_matrix[i-1][j+1]
                        + pad_matrix[i+1][j-1] + pad_matrix[i+1][j+1])
                    if val < 4:
                        coords_removed_rolls.append((i, j))
                        count += 1
        for i, j in coords_removed_rolls:
            pad_matrix[i][j] = 0
    return count


if __name__ == '__main__':
    with open("input.txt", "r") as f:
        lines = f.readlines()
        
    T = time.time()
    print(part_1(lines))
    print("Runtime (part 1) =", round(time.time() - T, 3), "seconds\n")
    
    T = time.time()
    print(part_2(lines))
    print("Runtime (part 2) =", round(time.time() - T, 3), "seconds\n")
