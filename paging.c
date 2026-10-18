#include <stdio.h>
#include "defs.h"

pagetable_t core_pagetable;

int
init_page_table(void){
	free_range_by_pages(custom_ram, custom_ram + RAM_SIZE);
}

pagetable_t
init_paging(void){
	core_pagetable = (pagetable_t)alloc_page();

	memset(core_pagetable, 0, PAGE_SIZE);

	return core_pagetable;
}

pagetable_t
walk(pagetable_t pagetable, uint64_t virtual_addr, int alloc_perm){
	if (virtual_addr >= MAX_VA){
		panic("walk: exceeded virtual address limit !");
	}

	for(int level = 2; level > 0; level = level - 1){
		pte_t *pte = pagetable + (PX(level, virtual_addr));

		if (*pte & PTE_V){
			pagetable = (pagetable_t)PTE_TO_PA(*pte);
		} else {
			if (!(alloc_perm) || (pagetable = (pte_t *)alloc_page()) == 0){
				return 0;
			}
			
			memset(pagetable, 0, PAGE_SIZE);

			*pte = PA_TO_PTE(pagetable) | PTE_V; 
		}
	}

	return pagetable + (PX(0, virtual_addr));
}

void
walk_free(pagetable_t pagetable){

	for(int i = 0; i < 512; i++){
		pte_t pte = pagetable[i];

		if ((pte & PTE_V) && (pte & (PTE_R | PTE_W | PTE_R)) == 0){

			// PTE's PPN points to a child PTE.
			uint64_t child = PTE_TO_PA(pte);
			walk_free((pagetable_t)child);
			pagetable[i] = 0;
		} else if (pte & PTE_V){
			panic("walk_free: leaf");
		}
	}

	free_page((void *)pagetable);
}

int
map_pages(pagetable_t pagetable, uint64_t virtual_addr, uint64_t size, uint64_t physical_addr, int perm){
	uint64_t page_wise, last_page;
	pte_t *pte;

	if ((virtual_addr % PAGE_SIZE) != 0){
		panic("mappages: virtual address not aligned !");
	}

	if ((size % PAGE_SIZE) != 0){
		panic("mappages: size to be allocated not aligned !");
	}

	if (size == 0){
		panic("mappages: 0 size to be allocated ?");
	}

	page_wise = virtual_addr;
	last_page = virtual_addr + size - PAGE_SIZE;

	for(;;){
		pte = walk(pagetable, page_wise, 1);
		
		if (pte == 0){
			return -1;
		}
		if(*pte & PTE_V){
			panic("mappages: virtual address already mapped to another physical address !");		
		}

		*pte = PA_TO_PTE(physical_addr) | perm | PTE_V;

		if (page_wise == last_page){
			break;
		}

		page_wise = page_wise + PAGE_SIZE;
		physical_addr = physical_addr + PAGE_SIZE;
	}

	return 0;
}