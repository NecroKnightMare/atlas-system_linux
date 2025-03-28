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

    // printf("[*] Python list info\n");
    // printf("[*] Size of the Python List = %zd\n", size);
    // printf("[*] Allocated = %zd\n", ((PyListObject *)p)->allocated);
    
    for (Py_ssize_t i = 0; i < size; i++) 
    {
        PyObject *item = PyList_GetItem(p, i);
        if (PyUnicode_Check(item))
        {
            printf("str\n");
        } else if (PyLong_Check(item))
        {
            printf("int\n");
        } else if (PyFloat_Check(item))
        {
            printf("float\n");
        } else if (item == Py_None)
        {
            printf("NoneType\n");
        } else {
            printf("unknown\n");
        }
        printf("Element %zd: ", i);
        
        printf("[*] Python list info\n");
        printf("[*] Size of the Python List = %zd\n", size);
        printf("[*] Allocated = %zd\n", ((PyListObject *)p)->allocated);
            
            // output statement is wrong-should be:
            // Element 0: str
            // not : Element 0: [*] Python list info
            // Not i or size, logic may be missing
            // printf("Element %zd: ", i);

            // PyList_Append(p, item);
            // if (item == NULL)
            // {
            //     fprintf(stderr, "Error: Item %zd is -1\n", i);
            //     continue;
            // }
    }
}
