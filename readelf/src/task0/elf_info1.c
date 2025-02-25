#include "common_ops.h"
#include "file_header.h"

/**
 * magic_ - prints the ELF magic bytes in hex
 * @ident: pointer to the ELF identification array
 */
void magic_(unsigned char *ident)
{
	int i;

	for (i = 0; i < 16; i++)
	{
		printf("%02x ", ident[i]);
	}
	printf("\n");
}

/**
 * class_ - prints the ELF class (32-bit or 64-bit)
 * @clas: ELF class (either ELFCLASS32 or ELFCLASS64)
 */
void class_(unsigned char clas)
{
	if (clas == ELFCLASS32)
		printf("ELF32\n");
	else if (clas == ELFCLASS64)
		printf("ELF64\n");
	else if (clas == ELFCLASSNONE)
		printf("None\n");
	else
		printf("<unknown: %x>\n", clas);
}

/**
 * data_ - prints the ELF data encoding (little-endian or big-endian)
 * @dat: ELF data encoding (either ELFDATA2LSB or ELFDATA2MSB)
 */
void data_(unsigned char dat)
{
	if (dat == ELFDATA2LSB)
		printf("2's complement, little endian\n");
	else if (dat == ELFDATA2MSB)
		printf("2's complement, big endian\n");
	else if (dat == ELFDATANONE)
		printf("None\n");
	else
		printf("<unknown: %x>\n", dat);
}

/**
 * version_ - prints the ELF version
 * @version: ELF version
 */
void version_(unsigned char version)
{
	if (version == EV_CURRENT)
		printf("%d (current)\n", version);
	if (version == EV_NONE)
		printf("None\n");
	else if (!version)
		printf("<unknown: %x>\n", version);
}
