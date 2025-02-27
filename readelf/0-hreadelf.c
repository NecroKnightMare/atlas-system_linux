#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

void print_elf_header(const char *filename);

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    print_elf_header(argv[1]);
    return 0;
}

void print_elf_header(const char *filename) {
    int fd;
    Elf32_Ehdr header;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (read(fd, &header, sizeof(header)) != sizeof(header)) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    // Validate ELF magic
    if (header.e_ident[EI_MAG0] != ELFMAG0 ||
        header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 ||
        header.e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "Not an ELF file\n");
        exit(EXIT_FAILURE);
    }

    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", header.e_ident[i]);
    }
    printf("\n");

    printf("  Class:                             %s\n",
           header.e_ident[EI_CLASS] == ELFCLASS64 ? "ELF64" :
           header.e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32" : "Invalid class");

    printf("  Data:                              %s\n",
           header.e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" :
           header.e_ident[EI_DATA] == ELFDATA2MSB ? "2's complement, big endian" : "Invalid data encoding");

    printf("  Version:                           %d (current)\n", header.e_ident[EI_VERSION]);

    // OS/ABI handling
    switch(header.e_ident[EI_OSABI]) {
        case ELFOSABI_SYSV: printf("  OS/ABI:                            UNIX - System V\n"); break;
        case ELFOSABI_HPUX: printf("  OS/ABI:                            UNIX - HP-UX\n"); break;
        case ELFOSABI_NETBSD: printf("  OS/ABI:                            UNIX - NetBSD\n"); break;
        case ELFOSABI_LINUX: printf("  OS/ABI:                            UNIX - Linux\n"); break;
        case ELFOSABI_SOLARIS: printf("  OS/ABI:                            UNIX - Solaris\n"); break;
        case 0x53: printf("  OS/ABI:                            Sortix\n"); break;
        default: printf("  OS/ABI:                            <unknown: %x>\n", header.e_ident[EI_OSABI]);
    }

    printf("  ABI Version:                       %d\n", header.e_ident[EI_ABIVERSION]);

    // File type handling
    switch(header.e_type) {
        case ET_NONE