#ifndef HNM_FUNCS_H
#define HNM_FUNCS_H

#include <stddef.h>
#include <elf.h>

void process_elf64(const char *filename, unsigned char *data, size_t size);
void process_elf32(const char *filename, unsigned char *data, size_t size);

#endif /* HNM_FUNCS_H */
