from math import sqrt

def prime(a):
    if a & 0x02 == 2 or a % 5 == 0: return False
    if a < 2: return False
    for x in range(2, int(sqrt(a)) + 1):
        if a % x == 0:
            return False
    return True

x = int(input())
i = x - 1
j = x + 1
while not prime(i):
    i -= 1
while not prime(j):
    j += 1

print(f'{i} < {x} < {j}')