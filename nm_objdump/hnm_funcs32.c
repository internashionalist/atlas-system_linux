#include "hnm_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>

/**
 * find_symtab32 -		finds the symbol table section in a 32-bit ELF file.
 * @ehdr:				pointer to the ELF header
 * @sections:			pointer to the section headers.
 *
 * Return:				pointer to the symbol table section, or NULL if not
 *						found.
 */
static Elf32_Shdr *find_symtab32(const Elf32_Ehdr *ehdr,
								 Elf32_Shdr *sections)
{
	int i;
	Elf32_Shdr *symtab_section;

	symtab_section = NULL;
	for (i = 0; i < (int)ehdr->e_shnum; i++)
	{
		if (sections[i].sh_type == SHT_SYMTAB)
		{
			symtab_section = &sections[i];
			break;
		}
	}
	if (!symtab_section)
	{
		for (i = 0; i < (int)ehdr->e_shnum; i++)
		{
			if (sections[i].sh_type == SHT_DYNSYM)
			{
				symtab_section = &sections[i];
				break;
			}
		}
	}
	return (symtab_section);
}

/**
 * get_symbol_char32 -		gets the nm symbol character for a 32-bit ELF
 *							symbol.
 * @sym:					pointer to the ELF symbol.
 * @sections:				pointer to the section headers.
 * @sh_strtab:				section header string table.
 *
 * Return:					char representing symbol type.
 */
static char get_symbol_char32(Elf32_Sym *sym, Elf32_Shdr *sections,
							  char *sh_strtab)
{
	unsigned char bind = ELF32_ST_BIND(sym->st_info);
	unsigned char type = ELF32_ST_TYPE(sym->st_info);
	Elf32_Shdr *sec;
	const char *sec_name;

	if (type == STT_FILE)
		return (0);
	if (bind == STB_WEAK)
	{
		if (sym->st_shndx == SHN_UNDEF)
			return ((type == STT_OBJECT) ? 'v' : 'w');
		else
			return ((type == STT_OBJECT) ? 'V' : 'W');
	}
	if (sym->st_shndx == SHN_UNDEF)
		return ('U');
	if (sym->st_shndx == SHN_ABS)
		return ((bind == STB_LOCAL) ? 'a' : 'A');
	if (type == STT_FUNC)
		return ((bind == STB_LOCAL) ? 't' : 'T');
	sec = &sections[sym->st_shndx];
	if (sec->sh_type == SHT_NOBITS)
		return ((bind == STB_LOCAL) ? 'b' : 'B');
	if (!sh_strtab)
		return ('?');
	sec_name = sh_strtab + sec->sh_name;
	if (strcmp(sec_name, ".text") == 0 ||
		(sec->sh_flags & SHF_EXECINSTR))
		return ((bind == STB_LOCAL) ? 't' : 'T');
	if (strcmp(sec_name, ".data") == 0 ||
		((sec->sh_flags & SHF_ALLOC) && (sec->sh_flags & SHF_WRITE)))
		return ((bind == STB_LOCAL) ? 'd' : 'D');
	if (strcmp(sec_name, ".bss") == 0)
		return ((bind == STB_LOCAL) ? 'b' : 'B');
	if (strcmp(sec_name, ".rodata") == 0 ||
		(sec->sh_flags & SHF_ALLOC))
		return ((bind == STB_LOCAL) ? 'r' : 'R');
	return ('?');
}

/**
 * print_symbol32 -			prints a 32-bit ELF symbol in nm format.
 * @sym:					pointer to the ELF symbol.
 * @sections:				pointer to the section headers.
 * @sh_strtab:				string table for section names.
 * @sym_strtab:				string table for symbol names.
 */
static void print_symbol32(Elf32_Sym *sym, Elf32_Shdr *sections,
						   char *sh_strtab, char *sym_strtab)
{
	const char *name = sym_strtab + sym->st_name;
	char c = get_symbol_char32(sym, sections, sh_strtab);

	if (!name || name[0] == '\0' || c == 0)	/* skip empty names, files */
		return;
	if (sym->st_shndx == SHN_UNDEF)
		printf("%8s %c %s\n", "", c, name);
	else
		printf("%08x %c %s\n", sym->st_value, c, name);
}

/**
 * process_elf32 -			process a 32-bit ELF file and print its symbols.
 * @filename:				name of the file to process.
 * @data:					pointer to the mmapped file data.
 * @size:					size of the file.
 */
void process_elf32(const char *filename, unsigned char *data, size_t size)
{
	Elf32_Ehdr *ehdr;
	Elf32_Shdr *sections;
	Elf32_Shdr *symtab_section;
	char *sh_strtab;
	char *sym_strtab;
	int num_symbols;
	Elf32_Sym *symtab;
	int i;

	(void)size;
	ehdr = (Elf32_Ehdr *)data;
	sections = (Elf32_Shdr *)(data + ehdr->e_shoff);
	sh_strtab = (char *)(data + sections[ehdr->e_shstrndx].sh_offset);
	symtab_section = find_symtab32(ehdr, sections);
	if (symtab_section == NULL)
	{
		fprintf(stderr, "%s: no symbol table found.\n", filename);
		return;
	}
	num_symbols = symtab_section->sh_size / sizeof(Elf32_Sym);
	symtab = (Elf32_Sym *)(data + symtab_section->sh_offset);
	sym_strtab = (char *)(data + sections[symtab_section->sh_link].sh_offset);
	for (i = 0; i < num_symbols; i++)
	{
		print_symbol32(&symtab[i], sections, sh_strtab, sym_strtab);
	}
}
