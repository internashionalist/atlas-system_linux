#ifndef _FILE_HEADER_H_
#define _FILE_HEADER_H_

#include "hreadelf.h"

#include <elf.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/* Prototypes for data printing */
void magic_(unsigned char *ident);
void class_(unsigned char clas);
void data_(unsigned char dat);
void version_(unsigned char version);
void osabi_(unsigned char osabi);
void abi_version_(unsigned char abi_version);
void type_(uint16_t type);
void machine_(uint16_t machine);
void file
void entry_point_(uint64_t entry);
void program_offset_(uint64_t offset);
void section_offset_(uint64_t offset);
void flags_(uint32_t flags);
void header_size_(uint16_t size);
void program_header_size_(uint16_t size);
void program_header_count_(uint16_t count);
void section_header_size_(uint16_t size);
void section_header_count_(uint16_t count);
void section_header_str_index_(uint16_t index);

/* header details extraction */
void display_hdr_details_32(Elf32_Ehdr *map32);
void display_hdr_details_64(Elf64_Ehdr *map64);

#endif /* _FILE_HEADER_H_ */
