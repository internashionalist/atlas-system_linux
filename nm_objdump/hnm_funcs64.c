#include "hnm_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>

/**
 * find_symtab64 -	finds the symbol table section in a 64-bit ELF file
 * @ehdr:			pointer to the ELF header.
 * @sections:		pointer to the section headers.
 *
 * Return:			pointer to the symbol table section, or NULL if not
 *					found.
 */
static Elf64_Shdr *find_symtab64(const Elf64_Ehdr *ehdr,
								 Elf64_Shdr *sections)
{
	int i;
	Elf64_Shdr *symtab_section;					/* pointer to symtab */

	symtab_section = NULL;
	for (i = 0; i < (int)ehdr->e_shnum; i++)	/* loop through sections */
	{
		if (sections[i].sh_type == SHT_SYMTAB)	/* if found */
		{
			symtab_section = &sections[i];		/* set the pointer, break */
			break;
		}
	}
	if (!symtab_section)						/* if symtab not found */
	{
		for (i = 0; i < (int)ehdr->e_shnum; i++)  /* search for dynsym */
		{
			if (sections[i].sh_type == SHT_DYNSYM)
			{
				symtab_section = &sections[i];
				break;
			}
		}
	}
	return (symtab_section);					/* return the pointer */
}

/**
 * get_symbol_char64 -		gets nm-style symbol char for a 64-bit ELF symbol
 * @sym:					pointer to the ELF symbol
 * @sections:				pointer to the section headers
 * @sh_strtab:				section header string table
 *
 * Return:					symbol character
 */
static char get_symbol_char64(Elf64_Sym *sym, Elf64_Shdr *sections,
							  char *sh_strtab)
{
	unsigned char bind = ELF64_ST_BIND(sym->st_info);
	unsigned char type = ELF64_ST_TYPE(sym->st_info);
	Elf64_Shdr *sec;
	const char *sec_name;

	if (type == STT_FILE)					/* file symbol */
		return (0);
	if (bind == STB_WEAK)					/* weak symbol */
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
	if (sym->st_shndx == SHN_COMMON)
		return ((bind == STB_LOCAL) ? 'c' : 'C');
	if (type == STT_FUNC)
		return ((bind == STB_LOCAL) ? 't' : 'T');
	sec = &sections[sym->st_shndx];
	if (sec->sh_type == SHT_NOBITS)			/* .bss check*/
		return ((bind == STB_LOCAL) ? 'b' : 'B');
	if (!sh_strtab)
		return ('?');
	sec_name = sh_strtab + sec->sh_name;
	if (strcmp(sec_name, ".text") == 0 ||
		strcmp(sec_name, ".init_array") == 0 ||
		strcmp(sec_name, ".fini_array") == 0 ||
		(sec->sh_flags & SHF_EXECINSTR))
		return ((bind == STB_LOCAL) ? 't' : 'T');
	if (strcmp(sec_name, ".data") == 0 ||
		((sec->sh_flags & SHF_ALLOC) && (sec->sh_flags & SHF_WRITE)))
		return ((bind == STB_LOCAL) ? 'd' : 'D');
	if (strcmp(sec_name, ".bss") == 0)		/* explicit .bss check */
		return ((bind == STB_LOCAL) ? 'b' : 'B');
	if (strcmp(sec_name, ".rodata") == 0 ||
		(sec->sh_flags & SHF_ALLOC))
		return ((bind == STB_LOCAL) ? 'r' : 'R');
	return ('?');
}

/**
 * print_symbol64 -		prints a 64-bit ELF symbol in nm format
 * @sym:				pointer to the ELF symbol
 * @sections:			pointer to the section headers
 * @sh_strtab:			string table for section names
 * @sym_strtab:			string table for symbol names
 */
static void print_symbol64(Elf64_Sym *sym, Elf64_Shdr *sections,
						   char *sh_strtab, char *sym_strtab)
{
	const char *name = sym_strtab + sym->st_name;
	char c = get_symbol_char64(sym, sections, sh_strtab);

	if (!name || name[0] == '\0' || c == 0)	/* skip empty names, files */
		return;
	if (sym->st_shndx == SHN_UNDEF)			/* undefined */
		printf("%16s %c %s\n", "", c, name);
	else									/* actual symbol */
		printf("%016lx %c %s\n", sym->st_value, c, name);
}

/**
 * process_elf64 -		processes a 64-bit ELF file and print its symbols
 * @filename:			name of the file to process
 * @data:				pointer to the mmapp'd file data
 * @size:				size of the file
 *
 * Return:				void
 */
void process_elf64(const char *filename, unsigned char *data, size_t size)
{
	Elf64_Ehdr *ehdr;
	Elf64_Shdr *sections;
	Elf64_Shdr *symtab_section;
	char *sh_strtab;
	char *sym_strtab;
	int num_symbols;
	Elf64_Sym *symtab;
	int i;

	(void)size;								/* unused */
	ehdr = (Elf64_Ehdr *)data;
	if (ehdr->e_type == ET_DYN)
		return;
	sections = (Elf64_Shdr *)(data + ehdr->e_shoff);
	sh_strtab = (char *)(data +
						 sections[ehdr->e_shstrndx].sh_offset);
	symtab_section = find_symtab64(ehdr, sections);
	if (symtab_section == NULL)				/* no symbol table */
	{
		fprintf(stderr, "%s: no symbol table found.\n", filename);
		return;
	}
	/* get symbol table and string table */
	num_symbols = symtab_section->sh_size / sizeof(Elf64_Sym);
	symtab = (Elf64_Sym *)(data + symtab_section->sh_offset);
	sym_strtab = (char *)(data +
						  sections[symtab_section->sh_link].sh_offset);
	/* print each symbol */
	for (i = 0; i < num_symbols; i++)
	{
		print_symbol64(&symtab[i], sections, sh_strtab, sym_strtab);
	}
}
