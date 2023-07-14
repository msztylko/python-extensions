# Palindrome

`cases.txt` contains a bunch of sentences with some of them being [palindromes](https://en.wikipedia.org/wiki/Palindrome). Example: 
> Won’t lovers revolt now?

`palidromes.txt` is a list of valid palindromes from `cases.txt`

The task is to find and print all the lines from `cases.txt` that are palindromes.

`test.sh` is a basic benchmark for this problem

## Python version

```bash
./test.sh python find_palindromes.py

real	0m0.131s
user	0m0.113s
sys	0m0.014s
```

## C version

```bash
./test.sh ./palindrome                                                                

real	0m0.006s
user	0m0.004s
sys	0m0.001s
```

## Python with C extension

> add benchmark once ready

### Writing C extensions to Python

Main reference for this topic: https://docs.python.org/3/extending/extending.html
