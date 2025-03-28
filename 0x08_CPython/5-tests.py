import ctypes

lib = ctypes.CDLL('./libPython.so')
lib.print_python_int.argtypes = [ctypes.py_object]
i = -1
lib.print_python_int(i)
i = 0
lib.print_python_int(i)
i = 1
lib.print_python_int(i)
i = 123456789
lib.print_python_int(i)
i = -123456789
lib.print_python_int(i)
i = 12345678901
lib.print_python_int(i)
i = 10304719833506056896
lib.print_python_int(i)
i = -9223372036854775808
lib.print_python_int(i)
i = 9223372036854775807
lib.print_python_int(i)
i = 18446744073709551615
lib.print_python_int(i)
i = -18446744073709551615
lib.print_python_int(i)
i = 18446744073709551616
lib.print_python_int(i)
i = "1"
lib.print_python_int(i)
julien@ubuntu:~/Python Integers$ 
julien@ubuntu:~/Python Integers$ gcc -Wall -Wextra -pedantic -Werror -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.9 5-python.c
julien@ubuntu:~/Python Integers$ python3 5-tests.py 
-1
0
1
123456789
-123456789
12345678901
10304719833506056896
-9223372036854775808
9223372036854775807
18446744073709551615
-18446744073709551615
C unsigned long int overflow
Invalid Int Object