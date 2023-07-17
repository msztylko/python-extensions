#define PY_SSIZE_T_CLEAN
#include <Python.h>

long long fib(int n) {
    if (n < 2)
        return n;
    else    
        return fib(n-1) + fib(n-2);
}

static PyObject *cfibonacci_fib(PyObject *self, PyObject *args) {
    int n;
    long long out;
    
    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    
    out = fib(n);
    return PyLong_FromLong(out);
}

static PyMethodDef CFibonacciMethods[] = {
    {"fib", cfibonacci_fib, METH_VARARGS, "compute nth Fibonacci number"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef cfibonaccimodule = {
    PyModuleDef_HEAD_INIT, "cfibonacci",
    "A C implementation of Fibonacci function", -1, CFibonacciMethods
};

PyMODINIT_FUNC PyInit_cfibonacci(void) { return PyModule_Create(&cfibonaccimodule); }
