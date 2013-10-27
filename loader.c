#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "loader.h"
#include "helper.h"

#include <string.h>

int load_shdrs(FILE *file, Elf32_Ehdr *ehdr, Elf32_Shdr *shdrs)
{
	int i, j;
	char buf[1024];
	fseek(file, ehdr->e_shoff, 0);
	for (i = 0; i < ehdr->e_shnum; i++)
	{
		fread(shdrs + i, 1, sizeof(Elf32_Shdr), file);
	}
}

int load_strtab(FILE *file, Elf32_Shdr *shdr, char *buf)
{
	int pre_pos = ftell(file);
	fseek(file, shdr->sh_offset, 0);
	fread(buf, 1, shdr->sh_size, file);
	fseek(file, pre_pos, 0);
	return 1;
}

void ehdr_stats(Elf32_Ehdr *hdrp)
{
	int i;
	printf("e_ident\n");
	for (i = 0; i < 4; i++)
		printf("%c\n", hdrp->e_ident[i]);
 	printf("EI_CLASS:	%d\n", hdrp->e_ident[4]);
	printf("EI_DATA:	%d\n", hdrp->e_ident[5]);
	printf("EI_VERSION:	%d\n", hdrp->e_ident[6]);
	printf("EI_PAD:		%d\n", hdrp->e_ident[7]);
	printf("E_TYPE:		%d\n", hdrp->e_type);
	printf("E_MACHINE:	%d\n", hdrp->e_machine);
	printf("E_VERSION:	%d\n", hdrp->e_version);
	printf("E_ENTRY:	0x%x\n", hdrp->e_entry);
	printf("e_phoff:	%d\n", hdrp->e_phoff);
	printf("e_shoff:	%d\n", hdrp->e_shoff);
	printf("e_flags:	%d\n", hdrp->e_flags);
	printf("e_ehsize:	%d\n", hdrp->e_ehsize);
	printf("e_phentsize:	%d\n", hdrp->e_phentsize);
	printf("e_phnum:	%d\n", hdrp->e_phnum);
	printf("e_shentsize:	%d\n", hdrp->e_shentsize);
	printf("e_shnum:	%d\n", hdrp->e_shnum);
	printf("e_shstrndx:	%d\n", hdrp->e_shstrndx);
}

int load_psegs(FILE *file, Elf32_Ehdr *ehdr, Elf32_Phdr *phdrs)
{
	int i, cseg_loaded = 0;
	int word;

	for (i = 0; i < ehdr->e_phnum; i++)
	{
		Elf32_Phdr *hdr = phdrs + i;
		if (hdr->p_type == PT_LOAD) {
			fseek(file, hdr->p_offset, 0);
			segments[segment_cnt].offset = hdr->p_vaddr;
			segments[segment_cnt].size   = hdr->p_memsz;
			segments[segment_cnt].content = malloc(hdr->p_memsz);
			fread(segments[segment_cnt].content, 1, hdr->p_filesz, file);

			memcpy(&word, segments[segment_cnt].content, 4);
			// printdw(word);
			segment_cnt++;
		}
	}
}
int load_phdrs(FILE *file, Elf32_Ehdr *ehdr, Elf32_Phdr *phdrs)
{
	int i;
	int cseg_loaded = 0;
	fseek(file, ehdr->e_phoff, 0);

	for (i = 0; i < ehdr->e_phnum; i++)
		fread(phdrs+i, 1, sizeof(Elf32_Phdr), file);
	return 0;
}
