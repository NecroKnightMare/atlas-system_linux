#include <Python.h> // use gcc $(python-config --include) when compiling
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>
#include "list_object.h"



void print_python_list(PyObject *p)
{
    if (!PyList_Check(p)) 
    {
        fprintf(stderr, "Invalid PyObject: Not a list\n");
        return;
    }

    Py_ssize_t size = PyList_Size(p);
    // Py_ssize_t allocated = ((PyListObject *)p)->allocated;

    printf("[*] Python list info\n");
    printf("[*] Size of the Python List = %zd\n", size);
    printf("[*] Allocated = %zd\n", ((PyListObject *)p)->allocated);
    
    for (Py_ssize_t i = 0; i < size; i++) 
    {
        PyObject *item = PyList_GetItem(p, i);
        if (PyUnicode_Check(item))
        {
            printf("Element %zd: str\n", i);
        } else if (PyLong_Check(item))
        {
            printf("Element %zd: int\n", i);
        } else if (PyFloat_Check(item))
        {
            printf("Element %zd: float\n", i);
        } else if (PyTuple_Check(item))
        {
            printf("Element %zd: tuple\n", i);
        } else if (PyList_Check(item))
        {
            printf("Element %zd: list\n", i);
        } else if (item == Py_None)
        {
            printf("Element %zd: NoneType\n", i);
        } else {
            printf("Element %zd: unknown\n", i);
        }
        
    }
}
