# Fibonacci

Compute *nth* Fibonacci number according to definition :

F<sub>0</sub> = 0  
F<sub>1</sub> = 1  
F<sub>n</sub> = F<sub>n-1</sub> + F<sub>n-2</sub>

Main focus of this project are Python extensions so for now we stick to naive recursive implementation.

As a first test I'm computing first 41 Fibonacci numbers. Any number after that takes too long in Python with naive implementation.

## Python

[py_fib.py](https://github.com/msztylko/python-extensions/blob/master/fibonacci/py_fib.py)

```bash
./test.sh python py_fib.py                                                     

real	2m26.874s
user	2m25.839s
sys	0m0.798s
```

## C

[c_fib.c](https://github.com/msztylko/python-extensions/blob/master/fibonacci/c_fib.c)

Compiled with: `gcc -O2 c_fib.c -o c_fib`

```bash
./test.sh ./c_fib                                                              

real	0m2.385s
user	0m2.152s
sys	0m0.013s
```

## Python with C extension

[pyc_fib.py](https://github.com/msztylko/python-extensions/blob/master/fibonacci/pyc_fib.py) - Python driver  
[cfibonaccimodule.c](https://github.com/msztylko/python-extensions/blob/master/fibonacci/cfibonaccimodule.c) - C implementation

```bash
./test.sh python pyc_fib.py                                                     

real	0m2.391s
user	0m2.167s
sys	0m0.016s
```

## Cython

[cython_fib.py](https://github.com/msztylko/python-extensions/blob/master/fibonacci/cython_fib.py) - Python driver  
[cython_fib.pyx](https://github.com/msztylko/python-extensions/blob/master/fibonacci/cython_fib.pyx) - Cython implementation

```bash
./test.sh python cython_fib.py                                                 

real	0m34.384s
user	0m34.032s
sys	0m0.235s
```
