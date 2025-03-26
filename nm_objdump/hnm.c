#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <elf.h>
#include "hnm_funcs.h"

/**
 * main -			entry point for hnm program
 * @argc:			argument count
 * @argv:			argument vector
 *
 * Return:			0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
	int i;
	int fd;
	struct stat st;
	unsigned char *data;						/* mmap'd data */

	if (argc < 2)								/* no args */
		return (fprintf(stderr, "Usage: %s [objfile ...]\n", argv[0]), 1);
	for (i = 1; i < argc; i++)					/* loop through args */
	{
		fd = open(argv[i], O_RDONLY);			/* open each file */
		if (fd < 0 || fstat(fd, &st) < 0)		/* open or fstat error */
		{
			perror(argv[i]);					/* probably don't need */
			if (fd >= 0)
				close(fd);
			continue;
		}
												/* mmap the file */
		data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		if (data == MAP_FAILED)					/* mmap error */
		{
			perror(argv[i]);					/* (unneeded?) */
			close(fd);
			continue;
		}
		if ((size_t)st.st_size < sizeof(Elf64_Ehdr) ||
			memcmp(data, ELFMAG, SELFMAG) != 0)		/* not ELF */
			fprintf(stderr, "%s: Not an ELF file.\n", argv[i]);
		else if (data[EI_CLASS] == ELFCLASS64)		/* 64-bit */
			process_elf64(argv[i], data, st.st_size);
		else if (data[EI_CLASS] == ELFCLASS32)		/* 32-bit */
			process_elf32(argv[i], data, st.st_size);
		else										/* unknown */
			fprintf(stderr, "%s: Unknown ELF class.\n", argv[i]);

		munmap(data, st.st_size);					/* unmap */
		close(fd);
	}
	return (0);
}
