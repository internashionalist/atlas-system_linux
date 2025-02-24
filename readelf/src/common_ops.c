#include "common_ops.h"
#include "hreadelf.h"

/**
 * byte_swap16 - swaps the byte order of a 16-bit number
 * @num: 16-bit number to swap
 *
 * Return: byte-swapped 16-bit number
 */
uint16_t byte_swap16(uint16_t num)
{
    return ((num >> 8) & 0xFF) | ((num & 0xFF) << 8);
}

/**
 * byte_swap32 - swaps the byte order of a 32-bit number
 * @num: 32-bit number to swap
 *
 * Return: byte-swapped 32-bit number
 */
uint32_t byte_swap32(uint32_t num)
{
    return ((num >> 24) & 0xFF) | ((num >> 8) & 0xFF00) |
           ((num << 8) & 0xFF0000) | ((num << 24) & 0xFF000000);
}

/**
 * byte_swap64 - swaps the byte order of a 64-bit number
 * @num: 64-bit number to swap
 *
 * Return: byte-swapped 64-bit number
 */
uint64_t byte_swap64(uint64_t num)
{
    return ((num >> 56) & 0xFF) | ((num >> 40) & 0xFF00) |
           ((num >> 24) & 0xFF0000) | ((num >> 8) & 0xFF000000) |
           ((num << 8) & 0xFF00000000) | ((num << 24) & 0xFF0000000000) |
           ((num << 40) & 0xFF000000000000) |
           ((num << 56) & 0xFF00000000000000);
}

/**
 * check_if_elf - checks if file is an ELF file based on magic bytes
 * @file_map: pointer to the start of the file
 *
 * Return: 1 if ELF file, 0 otherwise
 */
int check_if_elf(char *file_map)
{
    if (file_map[0] == 0x7f && file_map[1] == 'E' && file_map[2] == 'L' &&
        file_map[3] == 'F')
    {
        return 1;
    }
    return 0;
}

/**
 * handle_error - handles error messages based on error code
 * @error_code: error type (1 = open file, 2 = read file)
 * @err_num: error number for system error messages
 *
 * Return: void
 */
void handle_error(int error_code, int err_num)
{
    if (error_code == 1)
    {
        fprintf(stderr, "%s: %s\n", prog.program_name, FILE_NOT_FOUND_MSG);
    }
    else if (error_code == 2)
    {
        fprintf(stderr, "%s: %s\n", prog.program_name, INVALID_ELF_MSG);
    }

    if (err_num)
    {
        perror("Error");
    }
    exit(EXIT_FAILURE);
}

/**
 * adjust_fh_endian_32 - adjusts ELF header endianness for 32-bit files
 * @hdr32: pointer to 32-bit ELF header
 *
 * Return: void
 */
void adjust_fh_endian_32(Elf32_Ehdr *hdr32)
{
    if (prog.endianness != LSB)
    {
        hdr32->e_version = byte_swap32(hdr32->e_version);
        hdr32->e_entry = byte_swap32(hdr32->e_entry);
        hdr32->e_phoff = byte_swap32(hdr32->e_phoff);
        hdr32->e_shoff = byte_swap32(hdr32->e_shoff);
        hdr32->e_flags = byte_swap32(hdr32->e_flags);
    }

    hdr32->e_ehsize = byte_swap16(hdr32->e_ehsize);
    hdr32->e_phentsize = byte_swap16(hdr32->e_phentsize);
    hdr32->e_phnum = byte_swap16(hdr32->e_phnum);
    hdr32->e_shentsize = byte_swap16(hdr32->e_shentsize);
    hdr32->e_shnum = byte_swap16(hdr32->e_shnum);
    hdr32->e_shstrndx = byte_swap16(hdr32->e_shstrndx);
}

/**
 * adjust_fh_endian_64 - adjusts the ELF header endianness for 64-bit files
 * @hdr64: pointer to 64-bit ELF header
 *
 * Return: void
 */
void adjust_fh_endian_64(Elf64_Ehdr *hdr64)
{
    if (prog.endianness != LSB)
    {
        hdr64->e_version = byte_swap32(hdr64->e_version);
        hdr64->e_entry = byte_swap64(hdr64->e_entry);
        hdr64->e_phoff = byte_swap64(hdr64->e_phoff);
        hdr64->e_shoff = byte_swap64(hdr64->e_shoff);
        hdr64->e_flags = byte_swap32(hdr64->e_flags);
    }

    hdr64->e_ehsize = byte_swap16(hdr64->e_ehsize);
    hdr64->e_phentsize = byte_swap16(hdr64->e_phentsize);
    hdr64->e_phnum = byte_swap16(hdr64->e_phnum);
    hdr64->e_shentsize = byte_swap16(hdr64->e_shentsize);
    hdr64->e_shnum = byte_swap16(hdr64->e_shnum);
    hdr64->e_shstrndx = byte_swap16(hdr64->e_shstrndx);
}
