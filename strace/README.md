# C-Strace

## man or help:

* strace
* ptrace


### Learning Objectives

1. What is strace, and what is its purpose
2. What is ptrace, and what possibilties it offers
3. What are the differences between PTRACE_SINGLESTEP and PTRACE_SYSCALL
4. How to read from and/or write to the memory of a process being traced

### Requirements

- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 20.04 LTS
- Your programs and functions will be compiled with gcc 9.4.0 using the flags -Wall -Werror -Wextra and -pedantic
- All your files should end with a new line
- A README.md file, at the root of the folder of the project, is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- You are not allowed to use global variables
- No more than 5 functions per file
- You are allowed to use the standard library
- All your header files should be include guarded
- In the examples given, please remember that some values may be specific to the computer they are tested on, especially for addresses

## More Info

### Data Structure

This project requires you to parse the files /usr/include/asm/unistd_64.h and /usr/include/asm/unistd_32.h, in order to get the number corresponding to each syscall. It also requires you to do some man-scraping to get information about syscalls prototypes, in order to know the return type of each syscall, as well as its number of arguments and their type.

Since this is a very time-consuming task, you are given a header file, containing all these informations, allowing you to focus on the ptrace part of this project.

Please note that you are completely allowed to use your own data structure(s) and/or to modify the one provided to you, which is only here to help you getting started with strace, it does not contain everything you need for a complete strace.
