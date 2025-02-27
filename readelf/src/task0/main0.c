#include "common_ops.h"
#include "file_header.h"
#include "elf_details.h"
#include "hreadelf.h"

/**
 * main - entry point, reads and prints ELF file header
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	size_t bytes_read = 0;
	elf_dt elf_header;							   /* init info struct */
	prog_info prog = {.file_class = ELFCLASSNONE}; /* init prog struct */

	memset(&elf_header, 0, sizeof(elf_header)); /* clear memory */
	prog.program_name = argv[0];				/* set program name */
	prog.input_name = argv[1];					/* set input name */
	if (argc == 2)
	{
		prog.file_desc = open(argv[1], O_RDONLY); /* open file */
		if (prog.file_desc == -1)
			handle_error(1, 1); /* open error */
		bytes_read = read(		/* read (64-bit) */
						  prog.file_desc, &elf_header.hdr64, sizeof(elf_header.hdr64));
		if (bytes_read != sizeof(
							  elf_header.hdr64) ||
			!check_if_elf((char *)&elf_header.hdr64))
			handle_error(2, 1); /* read error */
		else
		{
			set_class(elf_header.hdr64.e_ident[EI_CLASS], &prog);
			if (prog.file_class == ELFCLASS32) /* 32-bit ELF */
			{
				lseek(prog.file_desc, 0, SEEK_SET); /* reset pointer */
				bytes_read = read(prog.file_desc, &elf_header.hdr32,
								  sizeof(elf_header.hdr32)); /* read 32-bit */
				if (bytes_read != sizeof(elf_header.hdr32) ||
					!check_if_elf((char *)&elf_header.hdr32))
					handle_error(2, 1); /* read error */
			}
			set_endianness(elf_header.hdr64.e_ident[EI_DATA], &prog);
			if (!print_file_header(&elf_header, &prog))
				handle_error(0, 1); /* invalid data */
		}
	}
	else
	{
		fprintf(stderr, "%s: Usage: %s <ELF-file>\n",
				prog.program_name, prog.program_name); /* usage error */
	}
	return (0);
}
