#include <Python.h>
#include <stdio.h>
#include "list_object.h"


void print_python_int(PyObject *p)
{
    if (!PyLong_Check(p))
    {
        fprintf(stderr, "Invalid Int Object\n");
        return;
    }

    PyLongObject *long_obj = (PyLongObject *)p;
    Py_ssize_t size = ((PyVarObject *)p)->ob_size;
    unsigned long int result = 0;
    
    if (size < 0)
    {
        size = -size;
    }

    for (Py_ssize_t i = 0; i < size; i++)
    {
        if (i > (Py_ssize_t)(sizeof(unsigned long int) * 8 / PyLong_SHIFT))
        {
            printf("C unsigned long int overflow\n");
            return;
        }
        result = long_obj->ob_digit[i] + (i << PyLong_SHIFT);
    }

    if (((PyVarObject *)p)->ob_size < 0)
    {
        printf("-%lu\n", result);
    
    }
    else
    {
        printf("%lu\n", result);
    }
    fflush(stdout);
}