#include <Python.h>
#include <stdio.h>
#include <unicodeobject.h>
#include "list_object.h"

// Tried removing fflush and isolating print 
// statements still get wrong output for checker

// Correct output - case: s = b"There is no spoon"

// [copy_files] Filed copied: main_2.py
// [copy_files] Filed copied: output_2
// [exec_bash] Command to run:
// cat output_2
// su student_jail -c 'timeout 30 bash -c '"'"'cat output_2'"'"''
// [exec_bash] Return code: 0
// [exec_bash] Student stdout:
// [.] string object info
//   [ERROR] Invalid String Object
// [exec_bash] Student stdout length: 55
// [exec_bash] Student stderr:
// [exec_bash] Student stderr length: 0
// [exec_bash] Command to run:
// LANG=C.UTF-8 timeout 10s ./main_2.py
// su student_jail -c 'timeout 30 bash -c '"'"'LANG=C.UTF-8 timeout 10s ./main_2.py'"'"''
// [exec_bash] Return code: 0
// [exec_bash] Student stdout:
// [ERROR] Invalid String Object
// [exec_bash] Student stdout length: 30
// [exec_bash] Student stderr:
// [exec_bash] Student stderr length: 0
void print_python_string(PyObject *p)
{
    // Somewhere in this logic its printing an extra line...

    printf("[.] string object info\n");
    fflush(stdout);

    if (!PyUnicode_Check(p))
    {
        printf("[ERROR] Invalid String Object\n");
        // fflush(stdout);
        return;
    }

    Py_ssize_t length = ((PyASCIIObject *)p)->length;
    const char *type = ((PyASCIIObject *)p)->state.ascii ? "compact ascii" : "compact unicode object";
    const char *value = PyUnicode_AsUTF8(p);

    if (value == NULL)
    {
        printf("[ERROR] Failed to convert string to UTF-8\n");
        return;
    }
    else
    {
    //printf("[.] string object info\n");
    printf("  type: %s\n", type);
    printf("  length: %zd\n", length);
    printf("  value: %s\n", value);
    }
}
// Current output:
// 0x08_CPython# python3 ./4-tests.py
// [.] string object info
//   type: compact ascii
//   length: 24
//   value: The spoon does not exist
// [.] string object info
//   type: compact unicode object
//   length: 19
//   value: ложка не существует
// [.] string object info
//   type: compact unicode object
//   length: 24
//   value: La cuillère n'existe pas
// [.] string object info
//   type: compact unicode object
//   length: 5
//   value: 勺子不存在
// [.] string object info
//   type: compact unicode object
//   length: 14
//   value: 숟가락은 존재하지 않는다.
// [.] string object info
//   type: compact unicode object
//   length: 10
//   value: スプーンは存在しない
// [ERROR] Invalid String Object