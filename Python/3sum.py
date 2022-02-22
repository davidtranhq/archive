from itertools import combinations

try:
    while True:
        numbers = [int(n) for n in input().split()]
        zeroes = {tuple(sorted(n)) for n in combinations(numbers, 3) if sum(n) == 0}
        for z in zeroes: print(*z)
        print()
except (EOFError, KeyboardInterrupt) as e:
    pass