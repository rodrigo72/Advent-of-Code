import time


def part_1(lines):
    for i, val in enumerate(lines[0]):
        if val == 'S':
            break
    count_splits = 0
    beam_directions = set({i})
    len_columns = len(lines[0])
    for line in lines[1:]:
        beam_directions_aux = set()
        for i, char in enumerate(line):
            if char == '^' and i in beam_directions:
                count_splits += 1
                if i+1 < len_columns:
                    beam_directions_aux.add(i+1)
                if i-1 >= 0:
                    beam_directions_aux.add(i-1)
                beam_directions.remove(i)
        beam_directions.update(beam_directions_aux)
    return count_splits


def part_2(lines):
    for i, val in enumerate(lines[0]):
        if val == 'S':
            start_col = i
            break
    
    n_cols = len(lines[0])
    n_rows = len(lines)
    memo = {} # key = position (row, col)
              # value = timelines down from that position
    
    # depth-first recursion -> memo values start from the bottom
    def count_timelines(row, col):
        if row >= n_rows:  # reached the end => completed timeline => +1
            return 1
        
        key = (row, col)
        if key in memo:  # prevents re-calculation
            return memo[key]
        
        if lines[row][col] == '^':
            count = 0
            if col - 1 >= 0:  # go left
                count += count_timelines(row + 1, col - 1)
            if col + 1 < n_cols:  # go right
                count += count_timelines(row + 1, col + 1)
        else:  # continue straight down
            count = count_timelines(row + 1, col)
        
        memo[key] = count
        return count
    
    return count_timelines(1, start_col)


def run(func, arg, n):
    print(f"\n-> Part {n}")
    T = time.time()
    print("Result  =", func(arg))
    print("Runtime =", round(time.time() - T, 4), "seconds\n")


if __name__ == '__main__':
    with open("input.txt", "r") as f:
        lines = f.readlines()
    run(part_1, lines, 1)
    run(part_2, lines, 2)
