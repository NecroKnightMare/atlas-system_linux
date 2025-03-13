#include "hreadelf.h"

void print_error(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(98);
}

void read_elf_header(const char *filename)
{
    int fd;
    Elf64_Ehdr header;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        print_error("Error: Cannot open file");

    if (read(fd, &header, sizeof(header)) != sizeof(header))
    {
        close(fd);
        print_error("Error: Cannot read ELF header");
    }

    if (header.e_ident[EI_MAG0] != ELFMAG0 ||
        header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 ||
        header.e_ident[EI_MAG3] != ELFMAG3)
    {
        close(fd);
        print_error("Error: Not an ELF file");
    }

    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++)
        printf("%02x ", header.e_ident[i]);
    printf("\n");

    printf("  Class:                             %s\n",
           header.e_ident[EI_CLASS] == ELFCLASS64 ? "ELF64" : "ELF32");

    printf("  Data:                              %s\n",
           header.e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");

    printf("  Version:                           %d (current)\n", header.e_ident[EI_VERSION]);

    printf("  OS/ABI:                            %s\n",
           header.e_ident[EI_OSABI] == ELFOSABI_SYSV ? "UNIX - System V" : "Other");

    printf("  ABI Version:                       %d\n", header.e_ident[EI_ABIVERSION]);

    printf("  Type:                              %s\n",
           header.e_type == ET_EXEC ? "EXEC (Executable file)" : "Other");

    printf("  Machine:                           %s\n",
           header.e_machine == EM_SPARC ? "Sparc" : "Other");

    printf("  Version:                           0x%x\n", header.e_version);
    printf("  Entry point address:               0x%lx\n", header.e_entry);
    printf("  Start of program headers:          %lu (bytes into file)\n", header.e_phoff);
    printf("  Start of section headers:          %lu (bytes into file)\n", header.e_shoff);
    printf("  Flags:                             0x%x\n", header.e_flags);
    printf("  Size of this header:               %u (bytes)\n", header.e_ehsize);
    printf("  Size of program headers:           %u (bytes)\n", header.e_phentsize);
    printf("  Number of program headers:         %u\n", header.e_phnum);
    printf("  Size of section headers:           %u (bytes)\n", header.e_shentsize);
    printf("  Number of section headers:         %u\n", header.e_shnum);
    printf("  Section header string table index: %u\n", header.e_shstrndx);

    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        exit(98);
    }

    read_elf_header(argv[1]);

    return 0;
}