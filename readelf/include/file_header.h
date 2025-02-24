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
void type_(uint16_t type);
void machine_(uint16_t machine);

/* header details extraction */
void display_hdr_details_32(Elf32_Ehdr *map32);
void display_hdr_details_64(Elf64_Ehdr *map64);

#endif /* _FILE_HEADER_H_ */
