#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>


void print_symbols(const char *filename) {
    Elf *elf;
    Elf_Scn *section;
    Elf_Data *data;
    GElf_Shdr shdr;
    GElf_Sym sym;
    int fd;

    if (elf_version(EV_CURRENT) == EV_NONE) {
        fprintf(stderr, "libelf version error\n");
        exit(EXIT_FAILURE);
    }

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    elf = elf_begin(fd, ELF_C_READ, NULL);
    if (!elf) {
        fprintf(stderr, "elf_begin error\n");
        exit(EXIT_FAILURE);
    }

    section = NULL;
    while ((section = elf_nextscn(elf, section)) != NULL) {
        gelf_getshdr(section, &shdr);
        if (shdr.sh_type == SHT_SYMTAB || shdr.sh_type == SHT_DYNSYM) {
            data = elf_getdata(section, NULL);
            for (size_t i = 0; i < shdr.sh_size / shdr.sh_entsize; ++i) {
                gelf_getsym(data, i, &sym);
                printf("%08lx %c %s\n",
                       (unsigned long)sym.st_value,
                       ELF32_ST_TYPE(sym.st_info),
                       elf_strptr(elf, shdr.sh_link, sym.st_name));
            }
        }
    }

    elf_end(elf);
    close(fd);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        // Assume a.out as the default file
        print_symbols("a.out");
    } else {
        for (int i = 1; i < argc; ++i) {
            print_symbols(argv[i]);
        }
    }

    return EXIT_SUCCESS;
}
