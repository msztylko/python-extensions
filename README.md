# python-extensions
because life's too short for slow software

## Debugging

Main [notes about debugging C extensions](https://github.com/msztylko/python-extensions/blob/master/debugging.md)

## [Palindrome](https://github.com/msztylko/python-extensions/tree/master/palindrome)

First example of making Python code faster.

## [Fibonacci](https://github.com/msztylko/python-extensions/tree/master/fibonacci)

Second example.

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

static PyMethodDef CPalindromeMethods[] = {
    {"is_palindrome", cpalindrome_is_palindrome, METH_VARARGS, 
     "check is string is palindrome"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef cpalindromemodule = {
    PyModuleDef_HEAD_INIT, "cpalindrome",
    "A C implementation of is_palindrome function", -1, CPalindromeMethods};

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
