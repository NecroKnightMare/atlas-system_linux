#include <stdio.h>
#include <stdlib.h>
#include <libelf.h>
#include <gelf.h>

/*
*Write a program that reproduces the GNU nm command

Usage: hnm [objfile ...]
The output should be the exact same as nm -p
Your sources must be compiled and linked using a Makefile
Your makefile must define the rule hnm and compile the
 needed sources to form the executable hnm
*/

void print_symbols(const char *filename) {
    int fd;
    Elf *elf;
    Elf_Scn *section = NULL;
    Elf_Data *data;
    GElf_Shdr shdr;
    GElf_Sym sym;

    // Initialize libelf
    if (elf_version(EV_CURRENT) == EV_NONE) {
        fprintf(stderr, "Error: ELF library version mismatch.\n");
        exit(EXIT_FAILURE);
    }

    // Open the file
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Initialize ELF descriptor
    elf = elf_begin(fd, ELF_C_READ, NULL);
    if (!elf) {
        fprintf(stderr, "Error initializing ELF.\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Iterate through sections
    while ((section = elf_nextscn(elf, section)) != NULL) {
        gelf_getshdr(section, &shdr);
        if (shdr.sh_type == SHT_SYMTAB || shdr.sh_type == SHT_DYNSYM) {
            data = elf_getdata(section, NULL);
            if (!data) {
                fprintf(stderr, "Error reading section data.\n");
                continue;
            }

            for (size_t i = 0; i < shdr.sh_size / shdr.sh_entsize; i++) {
                if (!gelf_getsym(data, i, &sym)) {
                    fprintf(stderr, "Error reading symbol.\n");
                    continue;
                }

                char type;
                switch (GELF_ST_TYPE(sym.st_info)) {
                    case STT_FUNC: type = 'T'; break;
                    case STT_OBJECT: type = 'D'; break;
                    case STT_SECTION: type = 'S'; break;
                    case STT_FILE: type = 'F'; break;
                    case STT_COMMON: type = 'C'; break;
                    case STT_TLS: type = 'B'; break;
                    default: type = '?'; break;
                }

                printf("%016lx %c %s\n",
                       (unsigned long)sym.st_value,
                       type,
                       elf_strptr(elf, shdr.sh_link, sym.st_name));
            }
        }
    }

    // Clean up
    elf_end(elf);
    close(fd);
}
