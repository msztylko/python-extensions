import sys

import cpalindrome


if __name__ == "__main__":
    for line in sys.stdin:
        if cpalindrome.is_palindrome(line):
            sys.stdout.write(line)
