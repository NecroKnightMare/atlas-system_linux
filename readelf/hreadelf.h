#ifndef _HREADELF_H_
#define _HREADELF_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

void print_error(const char *msg);
void read_elf_header(const char *filename);

#endif 
