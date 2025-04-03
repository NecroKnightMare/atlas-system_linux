#include <Python.h>
#include <stdio.h>
#include <unicodeobject.h>
#include "list_object.h"

// Correct output for the function print_python_list

void print_python_string(PyObject *p)
{


    printf("[.] string object info\n");
    fflush(stdout);

    if (!PyUnicode_Check(p))
    {
        printf("  [ERROR] Invalid String Object\n");
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
    printf("  type: %s\n", type);
    printf("  length: %zd\n", length);
    printf("  value: %s\n", value);
    }
}
// Current output:
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
// [.] string object info
//   [ERROR] Invalid String Object
//   length: 10
//   value: スプーンは存在しない
//   length: 10
//   value: スプーンは存在しない
// [.] string object info
//   [ERROR] Invalid String Object
//   length: 10
//   value: スプーンは存在しない
// [.] string object info
//   length: 10
//   value: スプーンは存在しない
// [.] string object info
//   [ERROR] Invalid String Object
