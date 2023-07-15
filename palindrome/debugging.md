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

### How to use debugger for stepping through C extension?

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

I was not sure where should I put the breakpoint, so let's start by simply running the program


```bash
r C_find_palindromes.py 
Process 6720 launched: '/Users/marcin/code/python-extensions/palindrome/.venv/bin/python' (arm64)
cpalindrome.cpython-310-darwin.so was compiled with optimization - stepping may behave oddly; variables may not be available.
Process 6720 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x101200000)
    frame #0: 0x00000001005b7e3c cpalindrome.cpython-310-darwin.so`cpalindrome_is_palindrome(self=<unavailable>, args=<unavailable>) at cpalindromemodule.c:17:17 [opt]
   14  	        h--;
   15  	
   16  	    while (l < h) {
-> 17  	        while (!isalnum(phrase[l] && l < h))
   18  	            l++;
   19  	        while (!isalnum(phrase[h] && l < h))
   20  	            h--;
Target 0: (python) stopped.
```

There's already a couple of useful informations, but let's quickly look around

```bash
(lldb) p l
(int) $0 = 1542544
(lldb) p h
(int) $1 = 26
```

Ok, that doesn't look right.

At this stage I was able to spot the typo in the code (can you?), but let's keep playing with the debugger. I see 2 useful adjustments:
1. `cpalindrome.cpython-310-darwin.so was compiled with optimization - stepping may behave oddly; variables may not be available.` - so let's compile it without optimizations and with debug symbols, it's my code so no problem with that.
2. Debugger stopped because of `EXC_BAD_ACCESS` in function `cpalindrome_is_palindrome`. We can set a breakpoint there before it segfaults.
