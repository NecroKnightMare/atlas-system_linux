#include <Python.h>
#include <stdio.h>
#include "list_object.h"

void print_python_string(PyObject *p)
{
    if (!PyUnicode_Check(p))
    {
        fprintf(stderr, "[ERROR] Invalid String Object\n");
        return;
    }

    Py_ssize_t length = ((PyASCIIObject *)p)->length;
    const char *type = ((PyASCIIObject *)p)->state.ascii ? "compact ascii" : "compact unicode object";
    const char *value = PyUnicode_AsUTF8(p);

    printf("[.] string object info\n");
    printf("  type: %s\n", type);
    printf("  length: %zd\n", length);
    printf("  value: %s\n", value);

    fflush(stdout);
}