"""Tag 5"""

import sys
import os
from collections import defaultdict, deque
from functools import cache

sys.setrecursionlimit(10000)


# def part1(inp):
#     """Part1"""
#     inp = [list(x) for x in inp.split("\\n")[:-1]]
#     return 0

def check_if_valide(ranges: list, start, end):
    result = []
    for r in ranges:
        if start >= r[0] and start <= r[1] and end >= r[0] and end <= r[1]:
            result = [[-1,-1]]
            break
        if r[0] >= start and r[0] <= end and r[1] >= start and r[1] <= end:
            if start < r[0]:
                res = check_if_valide(ranges, start, r[0] - 1)
                if res != [[-1, -1]]:
                    result.extend(res)
            if end > r[1]:
                res = check_if_valide(ranges, r[1] + 1, end)
                if res != [[-1, -1]]:
                    result.extend(res)
            break
        if start >= r[0] and start <= r[1]:
            start = r[1] + 1
        if end >= r[0] and end <= r[1]:
            end = r[0] - 1
    else:
        result.append([start, end])

    return result


def part2(inp):
    """Part2"""
    first, second = inp.split("\n\n")
    inp = [x.split("-") for x in first.split("\n")]
    inp = [[int(x),int(y)] for x,y in inp]
    ranges = [inp[0]]
    for start,end in inp[1:]:
        temp = check_if_valide(ranges, start, end)
        if temp != [[-1, -1]]:
            ranges.extend(temp)

    return sum([y-x+1 for x,y in ranges])


with open(os.path.join("tag5","input.txt"), "r", encoding="utf-8") as file:
    lines = file.read()

example = """3-5
10-14
16-20
12-18

1
5
8
11
17
32
"""
    
# assert part1(example) == 1, "Part 1"
# print("Part 1: ", part1(lines))

assert part2(example) == 14, "Part 2"
print("Part 2: ", part2(lines))