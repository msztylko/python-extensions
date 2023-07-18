from distutils.core import setup, Extension
from Cython.Build import cythonize


def main():
    setup(
        name="cfibonacci",
        version="1.0.0",
        description="nth Fibonaccie number in C",
        ext_modules=[Extension("cfibonacci", ["cfibonaccimodule.c"])],
    )
    setup(
        name="Cython fibonacci",
        version="1.0.0",
        ext_modules=cythonize("cython_fib.pyx"),
        zip_safe=False,
    )


if __name__ == "__main__":
    main()
