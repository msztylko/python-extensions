# Palindrome

`cases.txt` contains a bunch of sentences with some of them being [palindromes](https://en.wikipedia.org/wiki/Palindrome). Example: 
> Won’t lovers revolt now?

`palidromes.txt` is a list of valid palindromes from `cases.txt`

The task is to find and print all the lines from `cases.txt` that are palindromes.

`test.sh` is a basic benchmark for this problem

## Python

[py_palindrome.py](https://github.com/msztylko/python-extensions/blob/master/palindrome/py_palindrome.py)

```bash
./test.sh python py_palindrome.py                                               

real	0m0.049s
user	0m0.040s
sys	0m0.006s
```

## C

[c_palindrome.c](https://github.com/msztylko/python-extensions/blob/master/palindrome/c_palindrome.c)

Compiled with `gcc -O2 c_palindrome.c -o c_palindrome`

```bash
./test.sh ./c_palindrome                                                      
ok

real	0m0.636s
user	0m0.004s
sys	0m0.003s
```

2 orders of magnitude faster for this example.

## Python with C extension

[pyc_palindrome.py](https://github.com/msztylko/python-extensions/blob/master/palindrome/pyc_palindrome.py) - Python driver  
[cpalindromemodule.c](https://github.com/msztylko/python-extensions/blob/master/palindrome/cpalindromemodule.c) - C implementation  

Built with `python setup.py build_ext --inplace`

```bash
./test.sh python pyc_palindrome.py                                             

real	0m0.265s
user	0m0.029s
sys	0m0.006s
```

Not as fast as pure C version due to overhead of transforming to/from Python data structures.

## Cython

[cython_palindrome.py](https://github.com/msztylko/python-extensions/blob/master/palindrome/cython_palindrome.py) - Python driver  
[cython_palindrome.pyx](https://github.com/msztylko/python-extensions/blob/master/palindrome/cython_palindrome.pyx) - Cython implementation  

Built with `python setup.py build_ext --inplace`

```bash
./test.sh python cython_palindrome.py                                          

real	0m0.053s
user	0m0.044s
sys	0m0.006s
```

This is slower than the pure Python version 🤔

