#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

void
init_physical_ram(void){
	custom_ram = (uint8_t *)malloc(RAM_SIZE);
}

void *
free_range_by_pages(void *phy_start_addr, void *phy_end_addr){
	char *page_wise;

	page_wise = (char *)PGROUNDUP((uint64_t)phy_start_addr);
	for (; page_wise + PAGE_SIZE <= (char *)phy_end_addr; page_wise = page_wise + PAGE_SIZE){
		free_page(page_wise);
	}
}

void *
alloc_page(void){
	struct run *r;

	r = free_memory.free_list;
	if (r){
		free_memory.free_list = r->next;
	}

	if (r){
		memset((char *)r, 5, PAGE_SIZE);
	}

	return (void *)r;
}	

void
free_page(void *physical_addr){
	struct run *r;

	if ((uint64_t)physical_addr != 0 || (uint64_t) >= PHY_STOP){
		panic("free_page: physical address invalid or out of range !");
	}

	// filling page with junk.
	memset(physical_addr, 1, PAGE_SIZE);

	r = (struct run *)physical_addr;

	r->next = free_memory.free_list;
	free_memory.free_list = r;
}	


void *
memset(void *addr, char c, int n){
	char *c_addr = (char *)addr;

	for(int i = 0; i < n; i++){
		c_addr[i] = c;
	}
	return c_addr;
}