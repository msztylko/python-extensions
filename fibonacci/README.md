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
./test.sh python py_fib.py                                                     [6956407] 

real	2m26.874s
user	2m25.839s
sys	0m0.798s
```

## C

[c_fib.c](https://github.com/msztylko/python-extensions/blob/master/fibonacci/c_fib.c)

Compiled with: `gcc -O2 c_fib.c -o c_fib`

```bash

```

## Python with C extension



```bash
./test.sh python cfib.py                                                               

real	0m2.262s
user	0m2.178s
sys	0m0.083s
```
