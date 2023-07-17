# Fibonacci

Compute *nth* Fibonacci number according to definition :

F<sub>0</sub> = 0  
F<sub>1</sub> = 1  
F<sub>n</sub> = F<sub>n-1</sub> + F<sub>n-2</sub>

Main focus of this project are Python extensions so for now we stick to naive recursive implementation.

## Python version

```bash
./test.sh python fib.py                                                                                                                  

real	0m8.309s
user	0m8.190s
sys	0m0.105s
```

## C version

```bash
./test.sh ./fib                                                                                                                            

real	0m0.453s
user	0m0.228s
sys	0m0.003s
```
