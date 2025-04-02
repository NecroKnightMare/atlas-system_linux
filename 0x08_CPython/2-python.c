#include <Python.h> // use gcc $(python-config --includes) when compiling
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
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
        // Task 1 PyObject *item = PyList_GetItem(p, i);
        // Task 2 line 29
        PyObject *item = ((PyListObject *)p)->ob_item[i];
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

void print_python_bytes(PyObject *p)
{
   if (!PyBytes_Check(p)) 
   {
       fprintf(stderr, "Invalid PyObject_Bytes\n");
       return;
   }

    Py_ssize_t size = PyBytes_Size(p);
    char *bytes = PyBytes_AsString(p);

    printf("[.] bytes info\n");
    printf(" size: %zd\n" , size);
    printf(" trying string: %s\n", bytes);

    Py_ssize_t print_size = (size > 10) ? 10 : size;
    printf(" first %zd bytes:", print_size + 1);
    for (Py_ssize_t i = 0; i < size && i < 10; i++) 
    {
        printf("%02x ", (unsigned char)bytes[i]);
    }
    if (size >= print_size)
    {
        printf(" %02x", 0);
    }
    printf("\n");
}
