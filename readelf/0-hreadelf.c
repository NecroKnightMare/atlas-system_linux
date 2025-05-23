#include "hreadelf.h"
#include "elf_utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

void print_elf_header(const char *filename);

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error: Can't open file");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        perror("Error: Can't stat file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    void *file_data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file_data == MAP_FAILED) {
        perror("Error: mmap failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Call the function to print ELF header
    print_elf_header(argv[1]);

    munmap(file_data, st.st_size);
    close(fd);
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
    
    // using to debug// can't figure out to test, says I don't have
    // sortix32 in my directory? Don't even know how to go about that.
    printf("EI_OSABI: %x\n", header.e_ident[EI_OSABI]); 
    
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
        case ELFOSABI_AIX: printf("  OS/ABI:                            UNIX - AIX\n"); break;
        case ELFOSABI_IRIX: printf("  OS/ABI:                            UNIX - IRIX\n"); break;
        case ELFOSABI_FREEBSD: printf("  OS/ABI:                            UNIX - FreeBSD\n"); break;
        case ELFOSABI_TRU64: printf("  OS/ABI:                            UNIX - TRU64\n"); break;
        case ELFOSABI_MODESTO: printf("  OS/ABI:                            Novell - Modesto\n"); break;
        case ELFOSABI_OPENBSD: printf("  OS/ABI:                            UNIX - OpenBSD\n"); break;
        case ELFOSABI_ARM: printf("  OS/ABI:                            ARM\n"); break;
        case ELFOSABI_STANDALONE: printf("  OS/ABI:                            Standalone (embedded)\n"); break;
        default: printf("  OS/ABI:                            <unknown: %x>\n", header.e_ident[EI_OSABI]);
    }

    printf("  ABI Version:                       %u\n", header.e_ident[EI_ABIVERSION]);

    // File type handling
    switch(header.e_type) {
        case ET_NONE: printf("  Type:                              No file type\n"); break;
        case ET_REL: printf("  Type:                              Relocatable file\n"); break;
        case ET_EXEC: printf("  Type:                              EXEC (Executable file)\n"); break;
        case ET_DYN: printf("  Type:                              Shared object file\n"); break;
        case ET_CORE: printf("  Type:                              Core file\n"); break;
        default: printf("  Type:                              <unknown: %u>\n", header.e_type);
    }

    // Machine type handling
    switch(header.e_machine) {
        case EM_386: printf("  Machine:                           Intel 80386\n"); break;
        case EM_X86_64: printf("  Machine:                           Advanced Micro Devices X86-64\n"); break;
        case EM_SPARC: printf("  Machine:                           Sparc\n"); break;
        default: printf("  Machine:                           <unknown: %u>\n", header.e_machine);
    }

    printf("  Version:                           0x%x\n", header.e_version);
    printf("  Entry point address:               0x%lx\n", (unsigned long)header.e_entry);
    printf("  Start of program headers:          %u (bytes into file)\n", header.e_phoff);
    printf("  Start of section headers:          %u (bytes into file)\n", header.e_shoff);
    printf("  Flags:                             0x%x\n", header.e_flags);
    printf("  Size of this header:               %u (bytes)\n", header.e_ehsize);
    printf("  Size of program headers:           %u (bytes)\n", header.e_phentsize);
    printf("  Number of program headers:         %u\n", header.e_phnum);
    printf("  Size of section headers:           %u (bytes)\n", header.e_shentsize);
    printf("  Number of section headers:         %u\n", header.e_shnum);
    printf("  Section header string table index: %u\n", header.e_shstrndx);
}
