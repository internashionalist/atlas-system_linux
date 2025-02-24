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

/**
 * osabi_ - prints the ELF OS/ABI (Operating System/ABI)
 * @osabi: ELF OS/ABI value
 */
void osabi_(unsigned char osabi)
{
	switch (osabi)
	{
	case ELFOSABI_SYSV:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_HPUX:
		printf("HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n");
		break;
	case ELFOSABI_LINUX:
		printf("Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
		break;
	case ELFOSABI_IRIX:
		printf("IRIX\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		printf("TRU64 UNIX\n");
		break;
	default:
		printf("<unknown: %x>\n", osabi);
		break;
	}
}

/**
 * type_ - prints the ELF type (e.g., executable, shared object)
 * @type: ELF file type
 */
void type_(uint16_t type)
{
	switch (type)
	{
	case ET_NONE:
		printf("None\n");
		break;
	case ET_REL:
		printf("REL (Relocatable file)\n");
		break;
	case ET_EXEC:
		printf("EXEC (Executable file)\n");
		break;
	case ET_DYN:
		printf("DYN (Shared object file)\n");
		break;
	case ET_CORE:
		printf("Core file\n");
		break;
	default:
		printf("<unknown: %x>\n", type);
		break;
	}
}

/**
 * machine_ - prints the ELF machine architecture
 * @machine: ELF machine architecture
 */
void machine_(uint16_t machine)
{
	switch (machine)
	{
	case EM_NONE:
		printf("None\n");
		break;
	case EM_SPARC:
		printf("Sparc\n");
		break;
	case EM_386:
		printf("Intel 80386\n");
		break;
	case EM_X86_64:
		printf("Advanced Micro Devices X86-64\n");
		break;
	default:
		printf("<unknown: %x>\n", machine);
		break;
	}
}
