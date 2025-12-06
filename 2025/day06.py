import time
from functools import reduce
import re


def part_1(lines):
    total = 0
    parsed = []
    for line in lines:
        parsed.append(line.split())
    n_columns = len(parsed[0]) if parsed[0] else 0
    for i in range(n_columns):
        numbers = [int(line[i]) for line in parsed[:-1]]
        match parsed[-1][i]:
            case '*':
                total += reduce(lambda x, y: x * y, numbers)
            case '+':
                total += reduce(lambda x, y: x + y, numbers)
            case _:
                pass
    return total


def part_2(lines):
    total = 0
    symbols = re.findall(r'([+*] *)(?: |$)', lines[-1])
    n_symbols = len(symbols)
    n_rows = len(lines) - 1
    p = 0
    total = 0
    for i in range(n_symbols):
        max_len_number = len(symbols[i])
        symbol = symbols[i][0]
        total_aux = 0 if symbol == '+' else 1
        for j in range(max_len_number - 1, -1, -1):
            number = ""
            for k in range(n_rows):
                number += lines[k][p+j]
            if number:
                match symbol:
                    case '+':
                        total_aux += int(number)
                    case '*':
                        total_aux *= int(number)
                    case _:
                        raise Exception("AAAAA")
        total += total_aux
        p += max_len_number + 1
    return total


def run(func, arg):
    T = time.time()
    print(func(arg))
    print("Runtime (part 1) =", round(time.time() - T, 4), "seconds\n")


if __name__ == '__main__':
    with open("input.txt", "r") as f:
        lines = f.readlines()
    run(part_1, lines)
    run(part_2, lines)
