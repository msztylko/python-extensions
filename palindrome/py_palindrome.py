import re
import sys


def is_palindrome(phrase):
    left = 0
    right = len(phrase) - 1
    
    if phrase[right] == '\n':
        right -= 1

    while left < right:
        while (not phrase[left].isalnum() and left < right):
            left += 1
        while (not phrase[right].isalnum() and left < right):
            right -= 1
        if phrase[left].lower() != phrase[right].lower():
            return False
        left += 1
        right -= 1
    return True


if __name__ == "__main__":
    for line in sys.stdin:
        if is_palindrome(line):
            sys.stdout.write(line)
