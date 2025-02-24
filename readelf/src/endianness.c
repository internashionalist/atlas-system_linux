#include "common_ops.h"
#include "hreadelf.h"

/**
 * adjust_fh_endian_32 - adjusts ELF header endianness for 32-bit files
 * @hdr32: pointer to 32-bit ELF header
 *
 * Return: void
 */
void adjust_fh_endian_32(Elf32_Ehdr *hdr32)
{
	if (prog.endianness != LSB)
	{
		hdr32->e_type = byte_swap16(hdr32->e_type);
		hdr32->e_machine = byte_swap16(hdr32->e_machine);
		hdr32->e_version = byte_swap32(hdr32->e_version);
		hdr32->e_entry = byte_swap32(hdr32->e_entry);
		hdr32->e_phoff = byte_swap32(hdr32->e_phoff);
		hdr32->e_shoff = byte_swap32(hdr32->e_shoff);
		hdr32->e_flags = byte_swap32(hdr32->e_flags);
	}

	hdr32->e_ehsize = byte_swap16(hdr32->e_ehsize);
	hdr32->e_phentsize = byte_swap16(hdr32->e_phentsize);
	hdr32->e_phnum = byte_swap16(hdr32->e_phnum);
	hdr32->e_shentsize = byte_swap16(hdr32->e_shentsize);
	hdr32->e_shnum = byte_swap16(hdr32->e_shnum);
	hdr32->e_shstrndx = byte_swap16(hdr32->e_shstrndx);
}

/**
 * adjust_fh_endian_64 - adjusts the ELF header endianness for 64-bit files
 * @hdr64: pointer to 64-bit ELF header
 *
 * Return: void
 */
void adjust_fh_endian_64(Elf64_Ehdr *hdr64)
{
	if (prog.endianness != MSB)
	{
		hdr64->e_type = byte_swap16(hdr64->e_type);
		hdr64->e_machine = byte_swap16(hdr64->e_machine);
		hdr64->e_version = byte_swap32(hdr64->e_version);
		hdr64->e_entry = byte_swap64(hdr64->e_entry);
		hdr64->e_phoff = byte_swap64(hdr64->e_phoff);
		hdr64->e_shoff = byte_swap64(hdr64->e_shoff);
		hdr64->e_flags = byte_swap32(hdr64->e_flags);
	}

	hdr64->e_ehsize = byte_swap16(hdr64->e_ehsize);
	hdr64->e_phentsize = byte_swap16(hdr64->e_phentsize);
	hdr64->e_phnum = byte_swap16(hdr64->e_phnum);
	hdr64->e_shentsize = byte_swap16(hdr64->e_shentsize);
	hdr64->e_shnum = byte_swap16(hdr64->e_shnum);
	hdr64->e_shstrndx = byte_swap16(hdr64->e_shstrndx);
}
