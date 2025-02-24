#include "file_header.h"
#include "hreadelf.h"

/**
 * fh_details_32 - prints file header information for 32-bit ELF file
 * @map_32: Elf32_Ehdr info struct for 32-bit input file
 */
void display_hdr_details_32(Elf32_Ehdr *map_32)
{
    printf("%s", HDR_MAGIC); magic_(map_32->e_ident);
    printf("  %-35s", HDR_CLASS); class_(map_32->e_ident[EI_CLASS]);
    printf("  %-35s", HDR_DATA); data_(map_32->e_ident[EI_DATA]);
    printf("  %-35s", HDR_VERSION); version_(map_32->e_ident[EI_VERSION]);
    printf("  %-35s", HDR_OSABI); osabi_(map_32->e_ident[EI_OSABI]);
    printf("  %-35s%d\n", HDR_ABI_VER, map_32->e_ident[EI_ABIVERSION]);
    printf("  %-35s", HDR_TYPE); type_(map_32->e_type);
    printf("  %-35s", HDR_MACHINE); machine_(map_32->e_machine);
    printf("  %-35s0x%x\n", HDR_FILE_VER, map_32->e_version);
    printf("  %-35s0x%x\n", HDR_ENT_PT, map_32->e_entry);
    printf("  %-35s0x%x\n", HDR_FLAGS, map_32->e_flags);
    printf("  %-35s%d (bytes)\n", HDR_SIZE, map_32->e_ehsize);
    printf("  %-35s%d\n", HDR_PHNUM, map_32->e_phnum);
    printf("  %-35s%d (bytes)\n", HDR_PHENTSIZ, map_32->e_phentsize);
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
    printf("%s", HDR_MAGIC), magic_(map_64->e_ident);
    printf("  %-35s", HDR_CLASS), class_(map_64->e_ident[EI_CLASS]);
    printf("  %-35s", HDR_DATA), data_(map_64->e_ident[EI_DATA]);
    printf("  %-35s", HDR_VERSION), version_(map_64->e_ident[EI_VERSION]);
    printf("  %-35s", HDR_OSABI), osabi_(map_64->e_ident[EI_OSABI]);
    printf("  %-35s%d\n", HDR_ABI_VER, map_64->e_ident[EI_ABIVERSION]);
    printf("  %-35s", HDR_TYPE), type_(map_64->e_type);
    printf("  %-35s", HDR_MACHINE), machine_(map_64->e_machine);
    printf("  %-35s0x%x\n", HDR_FILE_VER, map_64->e_version);
    printf("  %-35s0x%lx\n", HDR_ENT_PT, map_64->e_entry);
    printf("  %-35s0x%x\n", HDR_FLAGS, map_64->e_flags);
    printf("  %-35s%d (bytes)\n", HDR_SIZE, map_64->e_ehsize);
    printf("  %-35s%d\n", HDR_PHNUM, map_64->e_phnum);
    printf("  %-35s%d (bytes)\n", HDR_PHENTSIZ, map_64->e_phentsize);
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

    printf("  Magic:   ");
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
    printf("  Class:                             ");
    if (clas == ELFCLASS32)
        printf("ELF32\n");
    else if (clas == ELFCLASS64)
        printf("ELF64\n");
}

/**
 * data_ - prints the ELF data encoding (little-endian or big-endian)
 * @dat: ELF data encoding (either ELFDATA2LSB or ELFDATA2MSB)
 */
void data_(unsigned char dat)
{
    printf("  Data:                              ");
    if (dat == ELFDATA2LSB)
        printf("2's complement, little endian\n");
    else if (dat == ELFDATA2MSB)
        printf("2's complement, big endian\n");
}

/**
 * version_ - prints the ELF version
 * @version: ELF version
 */
void version_(unsigned char version)
{
    printf("  Version:                           %d (current)\n", version);
}

/**
 * osabi_ - prints the ELF OS/ABI (Operating System/ABI)
 * @osabi: ELF OS/ABI value
 */
void osabi_(unsigned char osabi)
{
    printf("  OS/ABI:                            ");
    switch (osabi)
    {
        case ELFOSABI_SYSV: printf("UNIX - System V\n"); break;
        case ELFOSABI_HPUX: printf("HP-UX\n"); break;
        case ELFOSABI_NETBSD: printf("NetBSD\n"); break;
        case ELFOSABI_LINUX: printf("Linux\n"); break;
        case ELFOSABI_SOLARIS: printf("Unix - Solaris\n"); break;
        case ELFOSABI_AIX: printf("AIX\n"); break;
        case ELFOSABI_IRIX: printf("IRIX\n"); break;
        case ELFOSABI_FREEBSD: printf("FreeBSD\n"); break;
        case ELFOSABI_TRU64: printf("TRU64 UNIX\n"); break;
        case ELFOSABI_ARM: printf("ARM\n"); break;
        case ELFOSABI_STANDALONE: printf("Standalone\n"); break;
        default: printf("Unknown\n"); break;
    }
}

/**
 * abi_version_ - prints the ELF ABI version
 * @abi_version: ELF ABI version
 */
void abi_version_(unsigned char abi_version)
{
    printf("  ABI Version:                       %d\n", abi_version);
}

/**
 * type_ - prints the ELF type (e.g., executable, shared object)
 * @type: ELF file type
 */
void type_(uint16_t type)
{
    printf("  Type:                              ");
    switch (type)
    {
        case ET_NONE: printf("None\n"); break;
        case ET_REL: printf("Relocatable file\n"); break;
        case ET_EXEC: printf("EXEC (Executable file)\n"); break;
        case ET_DYN: printf("Shared object file\n"); break;
        case ET_CORE: printf("Core file\n"); break;
        default: printf("Unknown\n"); break;
    }
}

/**
 * machine_ - prints the ELF machine architecture
 * @machine: ELF machine architecture
 */
void machine_(uint16_t machine)
{
    printf("  Machine:                           ");
    switch (machine)
    {
        case EM_NONE: printf("None\n"); break;
        case EM_M32: printf("AT&T WE 32100\n"); break;
        case EM_SPARC: printf("Sparc\n"); break;
        case EM_386: printf("Intel 80386\n"); break;
        case EM_68K: printf("Motorola 68000\n"); break;
        case EM_88K: printf("Motorola 88000\n"); break;
        case EM_860: printf("Intel 80860\n"); break;
        case EM_MIPS: printf("MIPS R3000\n"); break;
        case EM_PPC: printf("PowerPC\n"); break;
        case EM_ARM: printf("ARM\n"); break;
        default: printf("Unknown\n"); break;
    }
}

/**
 * void file_version_ - prints the ELF file version
 * @version: ELF file version
 */
void file_version_(uint32_t version)
{
    printf("  Version:                           0x%x\n", version);
}

/**
 * entry_point_ - prints the ELF entry point address
 * @entry: ELF entry point address
 */
void entry_point_(uint64_t entry)
{
    printf("  Entry point address:               0x%lx\n", entry);
}

/**
 * program_offset_ - prints the ELF program header offset
 * @offset: ELF program header offset
 */
void program_offset_(uint64_t offset)
{
    printf(
        "  Start of program headers:          %lu (bytes into file)\n", offset);
}

/**
 * section_offset_ - prints the ELF section header offset
 * @offset: ELF section header offset
 */
void section_offset_(uint64_t offset)
{
    printf(
        "  Start of section headers:          %lu (bytes into file)\n", offset);
}

/**
 * flags_ - prints the ELF flags
 * @flags: ELF flags
 */
void flags_(uint32_t flags)
{
    if (flags == 0)
        printf("  Flags:                             0x0\n");
    else
        printf("  Flags:                             0x%x\n", flags);
}

/**
 * header_size_ - prints the ELF header size
 * @size: ELF header size
 */
void header_size_(uint16_t size)
{
    printf("  Size of this header:               %u (bytes)\n", size);
}

/**
 * program_header_size_ - prints the size of the program headers
 * @size: ELF program header size
 */
void program_header_size_(uint16_t size)
{
    printf("  Size of program headers:           %u (bytes)\n", size);
}

/**
 * program_header_count_ - prints the number of program headers
 * @count: number of program headers
 */
void program_header_count_(uint16_t count)
{
    printf("  Number of program headers:         %u\n", count);
}

/**
 * section_header_size_ - prints the size of section headers
 * @size: ELF section header size
 */
void section_header_size_(uint16_t size)
{
    printf("  Size of section headers:           %u (bytes)\n", size);
}

/**
 * section_header_count_ - prints the number of section headers
 * @count: number of section headers
 */
void section_header_count_(uint16_t count)
{
    printf("  Number of section headers:         %u\n", count);
}

/**
 * section_header_str_index_ - prints the section header string table index
 * @index: section header string table index
 */
void section_header_str_index_(uint16_t index)
{
    printf("  Section header string table index: %u\n", index);
}
