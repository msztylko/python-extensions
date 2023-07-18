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

2 orders of magnitude faster for this example.

## Python with C extension

```bash
./test.sh python C_find_palindromes.py                                         

real	0m0.030s
user	0m0.023s
sys	0m0.005s
```

Not as fast as pure C version due to overhead of transforming to/from Python data structures. But still an order of magnitude improvement over pure Python version!
