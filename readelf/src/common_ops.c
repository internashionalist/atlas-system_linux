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
	return (((num >> 8) & 0xFF) | ((num & 0xFF) << 8));
}

/**
 * byte_swap32 - swaps the byte order of a 32-bit number
 * @num: 32-bit number to swap
 *
 * Return: byte-swapped 32-bit number
 */
uint32_t byte_swap32(uint32_t num)
{
	return (((num >> 24) & 0xFF) | ((num >> 8) & 0xFF00) |
		   ((num << 8) & 0xFF0000) | ((num << 24) & 0xFF000000));
}

/**
 * byte_swap64 - swaps the byte order of a 64-bit number
 * @num: 64-bit number to swap
 *
 * Return: byte-swapped 64-bit number
 */
uint64_t byte_swap64(uint64_t num)
{
	return (((num >> 56) & 0xFF) | ((num >> 40) & 0xFF00) |
		   ((num >> 24) & 0xFF0000) | ((num >> 8) & 0xFF000000) |
		   ((num << 8) & 0xFF00000000) | ((num << 24) & 0xFF0000000000) |
		   ((num << 40) & 0xFF000000000000) |
		   ((num << 56) & 0xFF00000000000000));
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
		return (1);
	}
	return (0);
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
	prog_info prog = {0};

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
