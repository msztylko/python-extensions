import re
import sys


def is_palindrome(phrase):
    # remove whitespace
    pattern = re.compile(r'\W')
    phrase = re.sub(pattern, '', phrase)
    # all to lowercase
    phrase = ''.join(char.lower() for char in phrase)
    return phrase == phrase[::-1]


if __name__ == "__main__":
    for line in sys.stdin:
        if is_palindrome(line):
            sys.stdout.write(line)
