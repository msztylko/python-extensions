import sys


def is_palindrome(phrase):
    # TODO: regex to remove whitespace
    phrase = phrase.strip()
    return phrase == phrase[::-1]


if __name__ == "__main__":
    for line in sys.stdin:
        if is_palindrome(line):
            sys.stdout.write(line)
