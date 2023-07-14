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

### Writing C extensions for Python

Main reference for this topic: https://docs.python.org/3/extending/extending.html

At a minimum 2 files are needed:
1. `cpalindromemodule.c` - C extension module
2. `setup.py` - script used to create Python extension

[`cpalindromemodule.c`](https://github.com/msztylko/python-extensions/blob/master/palindrome/cpalindromemodule.c)
```C
#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *cpalindrome_is_palindrome(PyObject *self, PyObject *args) {
}

static PyMethodDef CVarintMethods[] = {
    {"is_palindrome", cpalindrome_is_palindrome, METH_VARARGS, 
     "check is string is palindrome"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef cpalindromemodule = {
    PyModuleDef_HEAD_INIT, "cpalindrome",
    "A C implementation of is_palindrome function", -1, CVarintMethods};

PyMODINIT_FUNC PyInit_cpalindrome(void) { return PyModule_Create(&cpalindromemodule); }
```

[`setup.py`](https://github.com/msztylko/python-extensions/blob/master/palindrome/setup.py)
```python
from distutils.core import setup, Extension

def main():
    setup(name="cpalindrome",
          version="1.0.0",
          description="is_palindrome check in C",
          ext_modules=[Extension("cpalindrome", ["cpalindromemodule.c"])])

if __name__ == '__main__':
    main()
```
To install C extension you can run `pip install -e .` in the directory with C code and `setup.py`
