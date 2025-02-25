#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>

void print_elf_header(const char *filename) {
    int fd;
    Elf64_Ehdr header;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

}

    if (read(fd, &header, sizeof(header)) != sizeof(header)) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (header.e_ident[EI_MAG0] != ELFMAG0 ||
        header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 ||
        header.e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "Not an ELF file.\n");
        close(fd);
        exit(EXIT_FAILURE);
    }