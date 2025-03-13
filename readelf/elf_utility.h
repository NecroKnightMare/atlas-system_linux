#ifndef ELF_UTILITY_H
#define ELF_UTILITY_H

#include <stdint.h>
#include <elf.h>

// Function prototypes
void process_elf_header(const void *file_data);
void handle_endianess(void *header, int is_64bit, int is_big_endian);
uint16_t swap16(uint16_t value);
uint32_t swap32(uint32_t value);
uint64_t swap64(uint64_t value);

#endif 
