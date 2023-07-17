# Fibonacci

Compute *nth* Fibonacci number according to definition :

F<sub>0</sub> = 0  
F<sub>1</sub> = 1  
F<sub>n</sub> = F<sub>n-1</sub> + F<sub>n-2</sub>

Main focus of this project are Python extensions so for now we stick to naive recursive implementation.

As a first test I'm computing first 41 Fibonacci numbers. Any number after that takes too long in Python with naive implementation.

## Python version

```bash
./test.sh python fib.py                                                                                                 

real	2m27.822s
user	2m26.932s
sys	0m0.705s
```

## C version

```bash
./test.sh ./fib                                                                        

real	0m2.151s
user	0m2.145s
sys	0m0.005s
```

## Python with C extension

```bash
./test.sh python cfib.py                                                               

real	0m2.262s
user	0m2.178s
sys	0m0.083s
```
