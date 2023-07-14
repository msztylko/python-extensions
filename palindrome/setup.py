from distutils.core import setup, Extension

def main():
    setup(name="cpalindrome",
          version="1.0.0",
          description="is_palindrome check in C",
          ext_modules=[Extension("cpalindrome", ["cpalindromemodule.c"])])

if __name__ == '__main__':
    main()
