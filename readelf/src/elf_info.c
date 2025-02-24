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
