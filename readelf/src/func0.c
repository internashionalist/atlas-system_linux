#include "common_ops.h"
#include "file_header.h"
#include "elf_details.h"
#include "hreadelf.h"

/**
 * print_file_header - prints the ELF file header
 * @elf_data: ELF file data structure
 *
 * Return: 1 on success, 0 if invalid data
 */
int print_file_header(elf_dt *elf_data, prog_info *prog)
{
	if (elf_data == NULL)
	{
		return (0);
	}

	printf("ELF Header:\n");

	if (prog->file_class == ELFCLASS32)
	{
		if (prog->endianness == MSB)
		{
			adjust_fh_endian_32(&elf_data->hdr32, prog);
		}

		display_hdr_details_32(&elf_data->hdr32);
	}
	else if (prog->file_class == ELFCLASS64)
	{
		if (prog->endianness == MSB)
		{
			adjust_fh_endian_64(&elf_data->hdr64, prog);
		}

		display_hdr_details_64(&elf_data->hdr64);
	}
	else
	{
		return (0);
	}

	return (1);
}

/**
 * set_endianness - sets ELF file endianness in program info struct
 * @ELF_end: endianness of ELF file
 *
 * Return: void
 */
void set_endianness(unsigned char ELF_end, prog_info *prog)
{
	if (ELF_end == ELFDATA2LSB)
	{
		prog->endianness = LSB;
	}
	else if (ELF_end == ELFDATA2MSB)
	{
		prog->endianness = MSB;
	}
}

/**
 * set_class - sets ELF file class in program info struct
 * @ELF_cls: file class of ELF file
 *
 * Return: void
 */
void set_class(unsigned char ELF_cls, prog_info *prog)
{
	if (ELF_cls == ELFCLASS32)
	{
		prog->file_class = ELFCLASS32;
	}
	else if (ELF_cls == ELFCLASS64)
	{
		prog->file_class = ELFCLASS64;
	}
}
