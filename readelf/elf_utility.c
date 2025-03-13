#include "elf_utility.h"
#include <stdio.h>
#include <elf.h>

uint16_t swap16(uint16_t value) {
    return (value >> 8) | (value << 8);
}

uint32_t swap32(uint32_t value) {
    return ((value >> 24) & 0xff) | ((value >> 8) & 0xff00) |
           ((value << 8) & 0xff0000) | ((value << 24) & 0xff000000);
}

uint64_t swap64(uint64_t value) {
    return ((uint64_t)swap32(value & 0xffffffff) << 32) | swap32(value >> 32);
}

void handle_endianess(void *header, int is_64bit, int is_big_endian) {
    if (is_big_endian) {
        if (is_64bit) {
            Elf64_Ehdr *hdr = (Elf64_Ehdr *)header;
            hdr->e_entry = swap64(hdr->e_entry);
            hdr->e_phoff = swap64(hdr->e_phoff);
            hdr->e_shoff = swap64(hdr->e_shoff);
        } else {
            Elf32_Ehdr *hdr = (Elf32_Ehdr *)header;
            hdr->e_entry = swap32(hdr->e_entry);
            hdr->e_phoff = swap32(hdr->e_phoff);
            hdr->e_shoff = swap32(hdr->e_shoff);
        }
    }
}

void process_elf_header(const void *file_data) {
    const unsigned char *e_ident = (unsigned char *)file_data;

    int is_64bit = (e_ident[EI_CLASS] == ELFCLASS64);
    int is_big_endian = (e_ident[EI_DATA] == ELFDATA2MSB);

    if (is_64bit) {
        Elf64_Ehdr *header = (Elf64_Ehdr *)file_data;
        handle_endianess(header, 1, is_big_endian);

        printf("ELF64 Header:\n");
        printf("  Entry point address: 0x%lx\n", header->e_entry);
        printf("  Start of program headers: %lu (bytes into file)\n", header->e_phoff);
        printf("  Start of section headers: %lu (bytes into file)\n", header->e_shoff);
        printf("  Number of section headers: %u\n", header->e_shnum);
    } else {
        Elf32_Ehdr *header = (Elf32_Ehdr *)file_data;
        handle_endianess(header, 0, is_big_endian);

        printf("ELF32 Header:\n");
        printf("  Entry point address: 0x%x\n", header->e_entry);
        printf("  Start of program headers: %u (bytes into file)\n", header->e_phoff);
        printf("  Start of section headers: %u (bytes into file)\n", header->e_shoff);
        printf("  Number of section headers: %u\n", header->e_shnum);
    }
}
