#ifndef _FUNC0_H_
#define _FUNC0_H_

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

/* prototypes for Task 0 */
int print_file_header(elf_dt *elf_data);
void set_endianness(unsigned char ELF_end);
void set_class(unsigned char ELF_class);

#endif /* _FUNC0_H_ */
