#include <Python.h> // use gcc $(python-config --include) when compiling
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>
#include "list_object.h"



void print_python_list(PyObject *p)
{
    if (!PyList_Check(p)) {
        fprintf(stderr, "Invalid PyObject: Not a list\n");
        return;
    }

    Py_ssize_t size = PyList_Size(p);
    
    for (Py_ssize_t i = 0; i < size; i++) 
    {
    PyObject *item = PyList_GetItem(p, i);
        if (item == NULL) 
        {
            fprintf(stderr, "Error: Item %zd is NULL\n", i);
            continue;
        }
        if (item == Py_None) 
        {
            fprintf(stderr, "Error: Item %zd is None\n", i);
            continue;
        }
        if (item == Py_False) 
        {
            fprintf(stderr, "Error: Item %zd is False\n", i);
            continue;
        }
       
        printf("[*] Python list info\n");
        printf("[*] Size of the Python List = %zd\n", size);
        printf("[*] Allocated = %zd\n", ((PyListObject *)p)->allocated);
        // output statement is wrong-should be:
        // Element 0: str
        // not : Element 0: [*] Python list info
        // Not i or size, logic may be missing
        printf("Element %zd: ", );

        // PyList_Append(p, item);
        // if (item == NULL)
        // {
        //     fprintf(stderr, "Error: Item %zd is -1\n", i);
        //     continue;
        // }
    }
}
