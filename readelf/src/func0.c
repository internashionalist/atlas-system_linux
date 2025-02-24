#include "common.h"
#include "func0.h"
#include "hreadelf.h"

/**
 * print_file_header - prints the ELF file header
 * @elf_data: ELF file data structure
 *
 * Return: 1 on success, 0 if invalid data
 */
int print_file_header(elf_info *elf_data)
{
    if (!elf_data) /* if NULL or invalid data */
    {
        return (0);
    }

    printf("ELF Header:\n"); /* print header */

    if (prog.file_class == ELFCLASS32) /* 32-bit ELF */
    {
        if (prog.endianness == LITTLE_ENDIAN)
        {
            adjust_fh_endian_32(&elf_data->hdr32);
        }

        display_hdr_details_32(&elf_data->hdr32);
    }
    else if (prog.file_class == ELFCLASS64) /* 64-bit ELF */
    {
        if (prog.endianness == BIG_ENDIAN)
        {
            adjust_fh_endian_64(&elf_data->hdr64);
        }

        display_hdr_details_64(&elf_data->hdr64);
    }

    return (1);
}

/**
 * set_endianness - sets ELF file endianness in program info struct
 * @ELF_end: endianness of ELF file
 *
 * Return: void
 */
void set_endianness(unsigned char ELF_end)
{
    if (ELF_end == ELFDATA2LSB)
    {
        prog.endianness = LITTLE_ENDIAN;
    }
    else if (ELF_end == ELFDATA2MSB)
    {
        prog.endianness = BIG_ENDIAN;
    }
}

/**
 * set_class - sets ELF file class in program info struct
 * @ELF_cls: file class of ELF file
 *
 * Return: void
 */
void set_class(unsigned char ELF_cls)
{
    if (ELF_cls == ELFCLASS32)
    {
        prog.file_class = ELFCLASS32;
    }
    else if (ELF_cls == ELFCLASS64)
    {
        prog.file_class = ELFCLASS64;
    }
}
