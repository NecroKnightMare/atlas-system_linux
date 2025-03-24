# C - ELF: nm/objdump

## Resources
### Read or watch:

* (ELF Wikipedia)[https://en.wikipedia.org/wiki/Executable_and_Linkable_Format]

* (ELF)[https://stevens.netmeister.org/631/elf.html]

* (Executable and Linkable Format (ELF))[https://www.cs.cmu.edu/afs/cs/academic/class/15213-f00/docs/elf.pdf]

* (The ELF Object File Format: Introduction)[https://www.linuxjournal.com/article/1059]

* (The ELF Object File Format by Dissection)[https://www.linuxjournal.com/article/1060]

## man or help:

* elf (5)
* nm (1)
* objdump (1)

### Learning Objectives

1. What is the ELF format
2. What are the commands nm and objdump
3. How to use them properly
4. How to parse the content of an ELF file
5. What information can be extracted from an ELF file
6. What are the differences between nm and objdump

## Requirements

* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 20.04 LTS
* Your C programs and functions will be compiled with gcc 9.4.0 using the flags -Wall -Werror -Wextra and -pedantic
* All your files should end with a new line
* A README.md file, at the root of the folder of the project, is mandatory
* Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
* You are not allowed to have more than 5 functions per file
* All your header files should be include guarded
* Allowed Functions and System Calls
* Unless specified otherwise, you are allowed to use the C standard library
- You’re not allowed to use system(3)
-You’re not allowed to use exec*(2 and 3)

## Tests

* Your program must be able to handle both 32-bit and 64-bit ELF files
* Your program must be able to handle both little and big endian ELF files
* Your program must be able to handle all types of ELF files

### More Info
- See also /usr/include/elf.h

![alt text](ELF_Executable_and_Linkable_Format_diagram_by_Ange_Albertini.png)