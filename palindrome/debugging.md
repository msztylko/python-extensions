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

### Build Python C extension with debug symbols

I'm not sure if `pip` can be used for that, so I `pip uninstall cpalindrome` first.
Then I run:

```bash
CFLAGS='-Wall -O0 -g' python setup.py install
```

Back to `lldb`

```bash
lldb python                                                                    
(lldb) target create "python"
Current executable set to 'python' (arm64).
(lldb) settings set target.input-path cases.txt
(lldb) r C_find_palindromes.py 
Process 10234 launched: '/Users/marcin/code/python-extensions/palindrome/.venv/bin/python' (arm64)
Process 10234 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x101b00000)
    frame #0: 0x00000001005b7dc4 cpalindrome.cpython-310-darwin.so`cpalindrome_is_palindrome(self=0x0000000101987d80, args=0x0000000101926560) at cpalindromemodule.c:17:17
   14  	        h--;
   15  	
   16  	    while (l < h) {
-> 17  	        while (!isalnum(phrase[l] && l < h))
   18  	            l++;
   19  	        while (!isalnum(phrase[h] && l < h))
   20  	            h--;
Target 0: (python) stopped.
```

We see no more information about optimizations and unavailable symbols. Let's set a breakpoint and rerun the process:

```bash
b cpalindrome_is_palindrome
Breakpoint 1: where = cpalindrome.cpython-310-darwin.so`cpalindrome_is_palindrome + 20 at cpalindromemodule.c:6:9, address = 0x00000001005b7d38
(lldb) r
There is a running process, kill it and restart?: [Y/n] y
Process 10234 exited with status = 9 (0x00000009) 
Process 10239 launched: '/Users/marcin/code/python-extensions/palindrome/.venv/bin/python' (arm64)
Process 10239 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x00000001005b7d38 cpalindrome.cpython-310-darwin.so`cpalindrome_is_palindrome(self=0x0000000101087d80, args=0x0000000101026560) at cpalindromemodule.c:6:9
   3   	
   4   	static PyObject *cpalindrome_is_palindrome(PyObject *self, PyObject *args) {
   5   	    const char *phrase;
-> 6   	    int l = 0;
   7   	
   8   	    if (!PyArg_ParseTuple(args, "s", &phrase))
   9   	        return NULL;
Target 0: (python) stopped.
```

We've already seen that `l` has a incorrect value when the program segfaults. Let's watch this variable to better understand what's going on.

```bash
w s v l
Watchpoint created: Watchpoint 1: addr = 0x16fdfec3c size = 4 state = enabled type = w
    declare @ '/Users/marcin/code/python-extensions/palindrome/cpalindromemodule.c:6'
    watchpoint spec = 'l'
    new value: 0
```
then we can `continue` until something interesting happens. It doesn't take long to see that:
```bash
-> 17  	        while (!isalnum(phrase[l] && l < h))
   18  	            l++;
```
is the problem - we are missing parenthesis in the call to `isalnum`.

Fixed version:

```C
...

    while (l < h) {
        while (!isalnum(phrase[l]) && l < h)
            l++;
        while (!isalnum(phrase[h]) && l < h)
            h--;
        if (tolower(phrase[l++] != tolower(phrase[h--])))
            return Py_False;
    }
    return Py_True;
```

Let's rerun everything:

```bash
CFLAGS='-Wall -O0 -g' python setup.py install
...
python C_find_palindromes.py < cases.txt                                       
python(13349,0x10164c580) malloc: *** error for object 0x101190408: pointer being freed was not allocated
python(13349,0x10164c580) malloc: *** set a breakpoint in malloc_error_break to debug
[1]    13349 abort      python C_find_palindromes.py < cases.txt
```
And we have a new issue... more opportunities to practice!

From just reading the source code I realized there's one more issue with parenthesis.

Fixed version:

```C
...
    while (l < h) {
        while (!isalnum(phrase[l]) && l < h)
            l++;
        while (!isalnum(phrase[h]) && l < h)
            h--;
        if (tolower(phrase[l++]) != tolower(phrase[h--]))
            return Py_False;
    }
    return Py_True;
```

I spent some time playing with this bug in `lldb` that it was more tricky. I realized that the error might be related to `Py_False` and `Py_True` so I went back to [documentation](https://docs.python.org/3/c-api/bool.html) and replace it with `Py_RETURN_FALSE` and `Py_RETURN_TRUE` respectively.
