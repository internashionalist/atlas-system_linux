#include "file_header.h"
#include "hreadelf.h"

/**
 * fh_details_32 - prints file header information for 32-bit ELF file
 * @map_32: Elf32_Ehdr info struct for 32-bit input file
 */
void display_hdr_details_32(Elf32_Ehdr *map_32)
{
	printf(" %s", HDR_MAGIC);
	magic_(map_32->e_ident);
	printf("  %-35s", HDR_CLASS);
	class_(map_32->e_ident[EI_CLASS]);
	printf("  %-35s", HDR_DATA);
	data_(map_32->e_ident[EI_DATA]);
	printf("  %-35s", HDR_VERSION);
	version_(map_32->e_ident[EI_VERSION]);
	printf("  %-35s", HDR_OSABI);
	osabi_(map_32->e_ident[EI_OSABI]);
	printf("  %-35s%d\n", HDR_ABI_VER, map_32->e_ident[EI_ABIVERSION]);
	printf("  %-35s", HDR_TYPE);
	type_(map_32->e_type);
	printf("  %-35s", HDR_MACHINE);
	machine_(map_32->e_machine);
	printf("  %-35s0x%x\n", HDR_FILE_VER, map_32->e_version);
	printf("  %-35s0x%x\n", HDR_ENT_PT, map_32->e_entry);
	printf("  %-35s%d (bytes into file)\n", HDR_PHOFF, map_32->e_phoff);
	printf("  %-35s%d (bytes into file)\n", HDR_SHOFF, map_32->e_shoff);
	printf("  %-35s0x%x\n", HDR_FLAGS, map_32->e_flags);
	printf("  %-35s%d (bytes)\n", HDR_SIZE, map_32->e_ehsize);
	printf("  %-35s%d (bytes)\n", HDR_PHENTSIZ, map_32->e_phentsize);
	printf("  %-35s%d\n", HDR_PHNUM, map_32->e_phnum);
	printf("  %-35s%d (bytes)\n", HDR_SHENTSIZ, map_32->e_shentsize);
	printf("  %-35s%d\n", HDR_SHNUM, map_32->e_shnum);
	printf("  %-35s%d\n", HDR_SHSTRNDX, map_32->e_shstrndx);
}

/**
 * fh_details_64 - prints file header information for 64-bit ELF file
 * @map_64: Elf64_Ehdr info struct for 64-bit input file
 */
void display_hdr_details_64(Elf64_Ehdr *map_64)
{
	printf(" %s", HDR_MAGIC), magic_(map_64->e_ident);
	printf("  %-35s", HDR_CLASS), class_(map_64->e_ident[EI_CLASS]);
	printf("  %-35s", HDR_DATA), data_(map_64->e_ident[EI_DATA]);
	printf("  %-35s", HDR_VERSION), version_(map_64->e_ident[EI_VERSION]);
	printf("  %-35s", HDR_OSABI), osabi_(map_64->e_ident[EI_OSABI]);
	printf("  %-35s%d\n", HDR_ABI_VER, map_64->e_ident[EI_ABIVERSION]);
	printf("  %-35s", HDR_TYPE), type_(map_64->e_type);
	printf("  %-35s", HDR_MACHINE), machine_(map_64->e_machine);
	printf("  %-35s0x%x\n", HDR_FILE_VER, map_64->e_version);
	printf("  %-35s0x%lx\n", HDR_ENT_PT, map_64->e_entry);
	printf("  %-35s%ld (bytes into file)\n", HDR_PHOFF, map_64->e_phoff);
	printf("  %-35s%ld (bytes into file)\n", HDR_SHOFF, map_64->e_shoff);
	printf("  %-35s0x%x\n", HDR_FLAGS, map_64->e_flags);
	printf("  %-35s%d (bytes)\n", HDR_SIZE, map_64->e_ehsize);
	printf("  %-35s%d (bytes)\n", HDR_PHENTSIZ, map_64->e_phentsize);
	printf("  %-35s%d\n", HDR_PHNUM, map_64->e_phnum);
	printf("  %-35s%d (bytes)\n", HDR_SHENTSIZ, map_64->e_shentsize);
	printf("  %-35s%d\n", HDR_SHNUM, map_64->e_shnum);
	printf("  %-35s%d\n", HDR_SHSTRNDX, map_64->e_shstrndx);
}
