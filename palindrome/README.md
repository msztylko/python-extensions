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

real	0m0.126s
user	0m0.003s
sys	0m0.002s
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

## Assembly
[c_asm_palindrome.c](https://github.com/msztylko/python-extensions/blob/master/palindrome/c_asm_palindrome.c) - C driver  
[asm_palindrome.asm](https://github.com/msztylko/python-extensions/blob/master/palindrome/asm_palindrome.asm) - Assembly implementation

Built with:

```bash
nasm -g -f macho64 --prefix _ asm_palindrome.asm -o asm_palindrome
cc -g -Wall -arch x86_64  asm_palindrome c_asm_palindrome.c -o c_asm_palindrome
```

```bash
./test.sh ./c_asm_palindrome                                                       

real	0m0.016s
user	0m0.007s
sys	0m0.004s
```

## C vs C-ASM vs ASM

Performance of these programs is so close that we need a better benchmark to better understand what's going on. Quick idea:

```bash
sed 'p;p;p;p;p' cases.txt | sed 'p;p;p;p;p' | sed 'p;p;p;p;p' | sed 'p;p;p;p;p' | sed 'p;p;p;p;p' > benchmark.txt
ls -lah benchmark.txt                                                                  
-rw-r--r--  1 marcin  staff   3.8G Jul 24 08:52 benchmark.txt
```

Almost 4GB should be enough for this test.

Build:

```bash
gcc -O2 c_palindrome.c -o c_palindrome                                                  
gcc -O2 c_like_asm_palindrome.c -o c_like_asm_palindrome                                
nasm -g -f macho64 --prefix _ asm_palindrome.asm -o asm_palindrome                     
gcc -g -Wall -arch x86_64  asm_palindrome c_asm_palindrome.c -o c_asm_palindrome  
```

Original C:
```bash
time ./c_palindrome < benchmark.txt 1>/dev/null                                         
ok
./c_palindrome < benchmark.txt > /dev/null  9.31s user 0.90s system 99% cpu 10.228 total
```

C written like ASM:
```bash
time ./c_like_asm_palindrome < benchmark.txt 1>/dev/null                               
ok
./c_like_asm_palindrome < benchmark.txt > /dev/null  7.38s user 0.85s system 97% cpu 8.461 total
```

Assembly:
```bash
time ./c_asm_palindrome < benchmark.txt 1>/dev/null                                    
ok
./c_asm_palindrome < benchmark.txt > /dev/null  21.41s user 2.47s system 99% cpu 23.876 total
```
