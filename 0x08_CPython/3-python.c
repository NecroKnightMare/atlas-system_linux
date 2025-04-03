#include <Python.h>
#include <stdio.h>
#include "list_object.h"

void print_python_list(PyObject *p)
{
    if (!PyList_Check(p))
    {
        fprintf(stderr, "[ERROR] Invalid List Object\n");
        return;
    }

    PyListObject *list = (PyListObject *)p;
    Py_ssize_t size = ((PyVarObject *)p)->ob_size;
    Py_ssize_t allocated = list->allocated;

    printf("[*] Python list info\n");
    printf("[*] Size of the Python List = %zd\n", size);
    printf("[*] Allocated = %zd\n", allocated);

    for (Py_ssize_t i = 0; i < size; i++)
    {
        PyObject *element = list->ob_item[i];
        printf("Element %zd: %s\n", i, element->ob_type->tp_name);

        if (PyBytes_Check(element))
            print_python_bytes(element);
        else if (PyFloat_Check(element))
            print_python_float(element);
    }
    fflush(stdout);
}

void print_python_bytes(PyObject *p)
{
    if (!PyBytes_Check(p))
    {
        fprintf(stderr, "[ERROR] Invalid Bytes Object\n");
        return;
    }

    PyBytesObject *bytesObj = (PyBytesObject *)p;
    Py_ssize_t size = ((PyVarObject *)p)->ob_size;
    char *bytes = bytesObj->ob_sval;

    printf("[.] bytes object info\n");
    printf("  size: %zd\n", size);
    printf("  trying string: %s\n", bytes);

    Py_ssize_t print_size = (size > 10) ? 10 : size;
    printf("  first %zd bytes:", print_size + 1);

    for (Py_ssize_t i = 0; i < print_size; i++)
    {
        printf(" %02x", (unsigned char)bytes[i]);
    }

    if (size <= 10)
    {
        printf(" %02x", 0);
    }
    printf("\n");
    fflush(stdout);
}

void print_python_float(PyObject *p)
{
    if (!PyFloat_Check(p))
    {
        fprintf(stderr, "[ERROR] Invalid Float Object\n");
        return;
    }

    double value = ((PyFloatObject *)p)->ob_fval;

    printf("[.] float object info\n");
    printf("  value: %.16g\n", value);
    fflush(stdout);
}