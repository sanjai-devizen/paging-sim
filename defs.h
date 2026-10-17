#ifndef DEFS_H
#define DEFS_H

// Having our own 16 MB RAM
#define RAM_SIZE (16 * 1024 * 1024)

uint8_t custom_ram[RAM_SIZE];

// Following the SV39 RISC-V architecture
#define PAGE_SIZE 4096

uint64_t *pagetable;
uint64_t pte; 

typedef struct run{
	struct run *next;
};

#endif