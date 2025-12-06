import time
from linked_list import LinkedList


def parse_and_refine_intervals(lines):
    ll = LinkedList()
    intervals = []
    for i, line in enumerate(lines):
        if line == '\n':
            break
        a, b = map(int, line.strip().split('-'))
        intervals.append((a, b))

    sorted_intervals = sorted(intervals, key=lambda x: (x[0], x[1]))  # O(n log n)
    ll = LinkedList.from_list(sorted_intervals)  # O(n)

    n1 = ll.head
    n2 = n1.next
    while n1 and n2:  # O(n)
        a, b = n1.data
        c, d = n2.data
        if a == c:
            if b >= d:  # (3, 10)  (3, 5)
                ll.delete_node(n2)
                n2 = n1.next
            else:  # (3, 5) (3, 10)
                ll.delete_node(n1)
                n1 = n2
                n2 = n2.next
        else:
            n1 = n2
            n2 = n2.next
    
    n1 = ll.head
    n2 = n1.next
    while n1 and n2:  # O(n)
        a, b = n1.data
        c, d = n2.data
        if b >= c:
            if b >= d:  # (2, 10) (3, 9) or (2, 10) (3, 10)
                ll.delete_node(n2)
                n2 = n1.next
            else:  # (2, 5) (3, 6)
                n1.data = (a, d)
                ll.delete_node(n2)
                n2 = n1.next
        else:
            n1 = n2
            n2 = n2.next
    
    return ll.display(), i


def part_1(lines):
    count = 0
    refined_intervals, i = parse_and_refine_intervals(lines)    
    len_ri = len(refined_intervals)
    for line in lines[i+1:]:  # O(n log n)
        value = int(line.rstrip('\n'))
        left, right = 0, len_ri - 1
        while left <= right:
            mid = (left + right) // 2
            if (refined_intervals[mid][0] <= value
                and refined_intervals[mid][1] >= value):
                count += 1
                break
            elif refined_intervals[mid][0] > value: # 2 -> (3, 10)
                right = mid - 1  # [ o O | m | - - ]
            elif refined_intervals[mid][1] < value: # 9 -> (7, 8)
                left = mid + 1   # [ - - | m | O o ]
    return count
                

def part_2(lines):
    count = 0
    refined_intervals, _ = parse_and_refine_intervals(lines)
    for a, b in refined_intervals:
        count += b - a + 1
    return count
        

if __name__ == '__main__':
    with open("input.txt", "r") as f:
        lines = f.readlines()

    T = time.time()
    print(part_1(lines))
    print("Runtime (part 1) =", round(time.time() - T, 4), "seconds\n")
    
    T = time.time()
    print(part_2(lines))
    print("Runtime (part 2) =", round(time.time() - T, 4), "seconds\n")
