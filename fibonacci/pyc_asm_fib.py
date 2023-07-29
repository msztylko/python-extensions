import sys

import cfibonacci


if __name__ == "__main__":
    for line in sys.stdin:
        n = int(line.split()[0])
        print(f"{n}\t{cfibonacci.fib(n)}")
