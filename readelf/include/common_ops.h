#ifndef _COMMON_OPS_H_
#define _COMMON_OPS_H_

#include <elf.h>
#include <endian.h>
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

/* prototypes for common operations */
int check_if_elf(char *file_map);
void handle_error(int error_code, int err_num);
void adjust_fh_endian_32(Elf32_Ehdr *hdr32);
void adjust_fh_endian_64(Elf64_Ehdr *hdr64);

/* endianness conversions */
static uint16_t byte_swap16(uint16_t num);
static uint32_t byte_swap32(uint32_t num);
static uint64_t byte_swap64(uint64_t num);

#endif /* _COMMON_OPS_H_ */
