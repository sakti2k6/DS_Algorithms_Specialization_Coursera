# Uses python3
import sys

def gcd_naive(a, b):
    current_gcd = 1
    for d in range(2, min(a, b) + 1):
        if a % d == 0 and b % d == 0:
            if d > current_gcd:
                current_gcd = d

    return current_gcd


def gcd_ecludian(a,b):
    if (a == 0) :
        return b
    return gcd_ecludian(b%a, a)

"""
if __name__ == "__main__":
    input = sys.stdin.read()
    a, b = map(int, input.split())
    print(gcd_naive(a, b))
"""

n = [int(x) for x in input().split()]
print (gcd_naive(n[0],n[1]))
print (gcd_ecludian(n[0],n[1]))