#include <stdio.h>
#include "loader.h"

void ehdr_stats(Elf32_Ehdr *hdrp);
int load_shdrs(FILE *file, Elf32_Ehdr *ehdr, Elf32_Shdr *shdrs);


int main(int argc, char *argv[])
{
	Elf32_Ehdr ehdr;
	Elf32_Shdr shdrs[100];
	FILE *file = fopen(argv[1], "r");
	Elf32_Ehdr *ehdrp = &ehdr;

	fread(ehdrp, 1, sizeof(ehdr), file);

	ehdr_stats(ehdrp);
	load_shdrs(file, ehdrp, shdrs);

	fclose(file);
}

int load_shdrs(FILE *file, Elf32_Ehdr *ehdr, Elf32_Shdr *shdrs)
{
	int i;
	fseek(file, ehdr->e_shoff, 0);
	for (i = 0; i < ehdr->e_shnum; i++)
	{
		fread(shdrs + i, 1, sizeof(Elf32_Shdr), file);
		printf("sh_type:	%d\n", shdrs[i].sh_type);
	}
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
