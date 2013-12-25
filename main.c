#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "loader.h"
#include "sim.h"
#include "memory.h"

int main(int argc, char *argv[])
{
	Elf32_Ehdr ehdr;
	Elf32_Shdr shdrs[100];
	Elf32_Phdr phdrs[100];
	FILE *file = fopen(argv[1], "r");
	Elf32_Ehdr *ehdrp = &ehdr;

	mem_init();

	fread(ehdrp, 1, sizeof(ehdr), file);
	load_shdrs(file, ehdrp, shdrs);
	load_phdrs(file, ehdrp, phdrs);
	load_psegs(file, ehdrp, phdrs);

	simulate(ehdrp->e_entry);
	fclose(file);
	mem_destroy();
}

