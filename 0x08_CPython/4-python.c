#include <Python.h>
#include <stdio.h>
#include <unicodeobject.h>
#include "list_object.h"

void print_python_string(PyObject *p)
{
    // Somewhere in this logic its printing an extra line...
    if (!PyUnicode_Check(p))
    {
        printf("[ERROR] Invalid String Object\n");
        fflush(stderr);
        return;
    }

    Py_ssize_t length = ((PyASCIIObject *)p)->length;
    const char *type = ((PyASCIIObject *)p)->state.ascii ? "compact ascii" : "compact unicode object";
    const char *value = PyUnicode_AsUTF8(p);

    if (value == NULL)
    {
        fprintf(stderr, "[ERROR] Failed to convert string to UTF-8\n");
        return;
    }

    printf("[.] string object info\n");
    printf("  type: %s\n", type);
    printf("  length: %zd\n", length);
    printf("  value: %s\n", value);

     fflush(stdout);
}