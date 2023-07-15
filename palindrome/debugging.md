# Debugging Python C extensions

When working on C extensions to Python it's not uncommon to encounter strange bugs. 

My initial version of palindrome extension:

```C
#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *cpalindrome_is_palindrome(PyObject *self, PyObject *args) {
    const char *phrase;
    int l = 0;

    if (!PyArg_ParseTuple(args, "s", &phrase))
        return NULL;

    int h = strlen(phrase) -1;

    if (phrase[h] == '\n')
        h--;

    while (l < h) {
        while (!isalnum(phrase[l] && l < h))
            l++;
        while (!isalnum(phrase[h] && l < h))
            h--;
        if (tolower(phrase[l++] != tolower(phrase[h--])))
            return Py_False;
    }
    return Py_True;
}

static PyMethodDef CVarintMethods[] = {
    {"is_palindrome", cpalindrome_is_palindrome, METH_VARARGS, 
     "check is string is palindrome"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef cpalindromemodule = {
    PyModuleDef_HEAD_INIT, "cpalindrome",
    "A C implementation of is_palindrome function", -1, CVarintMethods};
```
after building it with:

```bash
pip install -e .
```

had this result:

```bash
python C_find_palindromes.py < cases.txt                                               
[2]    4427 segmentation fault  python C_find_palindromes.py < cases.txt
```

How to use debugger for stepping through C extension?

First thing to do is to run native debugger, `lldb` or `gdb`, on python interpreter.
```bash
lldb python
(lldb) target create "python"
Current executable set to 'python' (arm64).
```

our program takes input redirected from `STDIN` and we can specify that with:

```bash
(lldb) settings set target.input-path cases.txt
```
