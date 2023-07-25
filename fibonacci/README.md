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

Built with `python setup.py build_ext --inplace`

```bash
./test.sh python pyc_fib.py                                                     

real	0m2.391s
user	0m2.167s
sys	0m0.016s
```

## Cython

[cython_fib.py](https://github.com/msztylko/python-extensions/blob/master/fibonacci/cython_fib.py) - Python driver  
[cython_fib.pyx](https://github.com/msztylko/python-extensions/blob/master/fibonacci/cython_fib.pyx) - Cython implementation

Built with `python setup.py build_ext --inplace`

```bash
./test.sh python cython_fib.py                                                 

real	0m34.384s
user	0m34.032s
sys	0m0.235s
```

## Assembly

[c_asm_fib.c](https://github.com/msztylko/python-extensions/blob/master/fibonacci/c_asm_fib.c) - C driver  
[asm_fib.asm](https://github.com/msztylko/python-extensions/blob/master/fibonacci/asm_fib.asm) - Assembly implementation

Built with:
```bash
nasm -g -f macho64 --prefix _ asm_fib.asm -o asm_fib
cc -g -Wall -arch x86_64  asm_fib c_asm_fib.c -o c_asm_fib
```

```bash
./test.sh ./c_asm_fib                                                              

real	0m3.493s
user	0m3.271s
sys	0m0.012s
```

It's slower than C version, but the point here was to just make it work and explore posibility of writing Python extensions in Assembly.
