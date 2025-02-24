#include "common_ops.h"
#include "file_header.h"
#include "func0.h"
#include "hreadelf.h"

prog_info prog;

/**
 * main - entry point of the program
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
	size_t bytes_read = 0;
	elf_dt elf_header;

	memset(&elf_header, 0, sizeof(elf_header));
	prog.program_name = argv[0];
	prog.input_name = argv[1];

	if (argc == 2)
	{
		prog.file_desc = open(argv[1], O_RDONLY);
		if (prog.file_desc == -1)
			handle_error(1, 1);

		bytes_read = read(
			prog.file_desc, &elf_header.hdr64, sizeof(elf_header.hdr64));
		if (bytes_read != sizeof(
			elf_header.hdr64) || !check_if_elf((char *)&elf_header.hdr64))
			handle_error(2, 1);
		else
		{
			set_class(elf_header.hdr64.e_ident[EI_CLASS]);
			if (prog.file_class == ELFCLASS32)
			{
				lseek(prog.file_desc, 0, SEEK_SET);
				bytes_read = read(prog.file_desc, &elf_header.hdr32,
								  sizeof(elf_header.hdr32));
				if (bytes_read != sizeof(elf_header.hdr32) ||
					!check_if_elf((char *)&elf_header.hdr32))
					handle_error(2, 1);
			}
			set_endianness(elf_header.hdr64.e_ident[EI_DATA]);
			if (!print_file_header(&elf_header))
				handle_error(0, 1);
		}
	}
	else
	{
		fprintf(stderr, "%s: Usage: %s <ELF-file>\n",
				prog.program_name, prog.program_name);
		return (1);
	}
	return (0);
}
