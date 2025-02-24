#ifndef _HREADELF_H_
#define _HREADELF_H_

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

/* endianness */
#define LSB 1
#define MSB 2

/* error messages */
#define ERROR_MSG ": Error: "
#define FILE_NOT_FOUND_MSG ": File not found"
#define INVALID_ELF_MSG "Invalid ELF file - magic bytes mismatch"

/* ELF header identifiers */
#define HDR_MAGIC " Magic:   "
#define HDR_CLASS "Class:"
#define HDR_DATA "Data:"
#define HDR_VERSION "Version:"
#define HDR_OSABI "OS/ABI:"
#define HDR_ABI_VER "ABI Version:"
#define HDR_TYPE "Type:"
#define HDR_MACHINE "Machine:"
#define HDR_FILE_VER "Version:"
#define HDR_ENT_PT "Entry point address:"
#define HDR_FLAGS "Flags:"
#define HDR_SIZE "Size of this header:"
#define HDR_PHENTSIZ "Size of program headers:"
#define HDR_PHNUM "Number of program headers:"
#define HDR_SHENTSIZ "Size of section headers:"
#define HDR_SHNUM "Number of section headers:"
#define HDR_SHSTRNDX "Section header string table index:"

/**
 * struct program_info - contains information about the program
 * @program_name:   program name
 * @input_name:     input ELF file name
 * @file_desc:      file descriptor for the ELF file
 * @file_class:     file class (1 for 32-bit, 2 for 64-bit)
 * @endianness:     endianness of the ELF file (1 for little, 2 for big)
 */
typedef struct program_info
{
    char *program_name; /* program name */
    char *input_name;   /* input ELF file name */
    int file_desc;      /* ELF file descriptor */
    int file_class;     /* 1 for 32-bit, 2 for 64-bit */
    int endianness;     /* 1 for little, 2 for big */
} prog_info;

/**
 * elf_info - holds the parsed ELF header data
 * @hdr32:   32-bit ELF header structure
 * @hdr64:   64-bit ELF header structure
 */
typedef struct elf_info
{
    Elf32_Ehdr hdr32;   /* 32-bit ELF header */
    Elf64_Ehdr hdr64;   /* 64-bit ELF header */
} elf_dt;

/* reference to program_info */
extern prog_info prog;

#endif /* _HREADELF_H_ */
