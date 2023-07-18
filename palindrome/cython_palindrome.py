import re
import sys

from cython_palindrome import is_palindrome


if __name__ == "__main__":
    for line in sys.stdin:
        if is_palindrome(line):
            sys.stdout.write(line)
