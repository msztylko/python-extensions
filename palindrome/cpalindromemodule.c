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
        while (!isalnum(phrase[l]) && l < h)
            l++;
        while (!isalnum(phrase[h]) && l < h)
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

PyMODINIT_FUNC PyInit_cpalindrome(void) { return PyModule_Create(&cpalindromemodule); }
