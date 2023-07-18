import cython

def fib(n: cython.int) -> cython.int:
    if n < 2:
        return n
    else:
        return fib(n-1) + fib(n-2)
