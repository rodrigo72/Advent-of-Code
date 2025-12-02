import re
import math


def digit_count(n):
    if n == 0:
        return 1
    return int(math.log10(n)) + 1


def split_number(n, d):
    half = d // 2
    pow10 = 10 ** half
    return n // pow10, n % pow10


def part_1(pairs):
    total = 0
    for start, end in pairs:
        pointer = start
        while pointer <= end:
            n_digits = digit_count(pointer)
            if n_digits % 2 == 0:  # symmetrical
                a, b = split_number(pointer, n_digits)
                if a == b:
                    total += pointer
                    pointer = (a+1) * 10**(n_digits//2) + (a+1)
                elif a < b:
                    pointer = (a+1) * 10**(n_digits//2) + (a+1)
                else:
                    pointer = a * 10**(n_digits//2) + a
            else:  # asymmetrical 
                pointer = 10**n_digits + 10**(n_digits // 2)
    return total


def generate_repeated_numbers(start, end):
    invalid = set()
    n_digits_end = digit_count(end)
    for l in range(1, n_digits_end // 2 + 1):  # l = length of the sequence
        min_seq = 10**(l-1)  # l = 2 => 10
        max_seq = 10**l - 1  # l = 2 => 99 
        for seq in range(min_seq, max_seq + 1):
            n = seq * (10**l) + seq  # seq = 12 => n = 1212
            while n <= end:
                if n >= start:
                    invalid.add(n)
                n = n * (10**l) + seq  # 1212 --> 121212
    return invalid


def part_2(pairs):
    total = 0
    for start, end in pairs:
        total += sum(generate_repeated_numbers(start, end))
    return total


if __name__ == '__main__':
    with open("input.txt", "r") as file:
        line = file.readline().strip()
        pairs = [(int(a), int(b)) for a, b in re.findall(r'(\d+)-(\d+)(?:,|$)', line)]
        print(part_1(pairs))
        print(part_2(pairs))
