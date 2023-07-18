from distutils.core import setup, Extension
from Cython.Build import cythonize


def main():
    setup(
        name="cpalindrome",
        version="1.0.0",
        description="is_palindrome check in C",
        ext_modules=[Extension("cpalindrome", ["cpalindromemodule.c"])],
    )
    setup(
        name="Cython palindrome",
        version="1.0.0",
        ext_modules=cythonize("cython_palindrome.pyx"),
        zip_safe=False,
    )


if __name__ == "__main__":
    main()
