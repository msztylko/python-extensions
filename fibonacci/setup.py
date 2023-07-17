from distutils.core import setup, Extension

def main():
    setup(name="cfibonacci",
          version="1.0.0",
          description="nth Fibonaccie number in C",
          ext_modules=[Extension("cfibonacci", ["cfibonaccimodule.c"])])

if __name__ == '__main__':
    main()
