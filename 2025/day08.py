import time
import math
import heapq


def straight_line_distance(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2 + (p1[2] - p2[2])**2)


def pair_key(p1, p2):
    return tuple(sorted((p1, p2)))


def all_the_computation(lines, max_count=10**1000):
    distances_min_heap = []
    already_calculated = set()
    points = set()

    for line in lines:
        x, y, z = line.strip().split(',')
        points.add((int(x), int(y), int(z)))

    for p1 in points:
        for p2 in points:
            if p1 != p2:
                key = pair_key(p1, p2)
                if key not in already_calculated:
                    already_calculated.add(key)
                    distance = straight_line_distance(p1, p2)
                    heapq.heappush(distances_min_heap, (distance, key))
    
    circuits = []
    location = {}
    for i, p in enumerate(points):
        circuits.append({p})
        location[p] = i

    lp1, lp2 = None, None
    while distances_min_heap and max_count > 0:
        max_count -= 1
        _, (p1, p2) = heapq.heappop(distances_min_heap)
        v1, v2 = location[p1], location[p2]
        if v1 == v2:
            pass
        else:
            lp1, lp2 = p1, p2
            for p in circuits[v2]:
                location[p] = v1
                circuits[v1].add(p)
            circuits[v2].clear()

    return circuits, lp1, lp2


def part_1(lines):
    circuits, _, _ = all_the_computation(lines, max_count=1000)
    len_circuits = sorted([len(c) for c in circuits], reverse=True)
    return len_circuits[0] * len_circuits[1] * len_circuits[2]


def part_2(lines):
    _, lp1, lp2 = all_the_computation(lines)
    return lp1[0] * lp2[0]


def run(func, arg, n):
    print(f"-> Part {n}")
    T = time.time()
    print("Result  =", func(arg))
    print("Runtime =", round(time.time() - T, 4), "seconds\n")


if __name__ == '__main__':
    with open("input.txt", "r") as f:
        lines = f.readlines()
    run(part_1, lines, 1)
    run(part_2, lines, 2)
