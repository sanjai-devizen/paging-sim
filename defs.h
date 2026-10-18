#ifndef DEFS_H
#define DEFS_H

// Having our own 16 MB RAM
#define RAM_SIZE (16 * 1024 * 1024)

uint8_t *custom_ram;

// Following the SV39 RISC-V architecture
#define PAGE_SIZE  4096 // bytes per page
#define PAGE_SHIFT 12   // bits of offset within a page

#define PGROUNDUP(sz)  (((sz) + PGSIZE - 1) & ~(PGSIZE - 1))
#define PGROUNDDOWN(a) (((a)) & ~(PGSIZE - 1))

#define PTE_V (1L << 0) // valid
#define PTE_R (1L << 1)
#define PTE_W (1L << 2)
#define PTE_X (1L << 3)
#define PTE_U (1L << 4) // user can access

// shift a physical address to the right place for a PTE.
#define PA2PTE(pa) ((((uint64)pa) >> 12) << 10)

#define PTE2PA(pte) (((pte) >> 10) << 12)

#define PTE_FLAGS(pte) ((pte) & 0x3FF)

// extract the three 9-bit page table indices from a virtual address.
#define PXMASK         0x1FF // 9 bits
#define PXSHIFT(level) (PGSHIFT + (9 * (level)))
#define PX(level, va)  ((((uint64)(va)) >> PXSHIFT(level)) & PXMASK)

// one beyond the highest possible virtual address.
// MAXVA is actually one bit less than the max allowed by
// Sv39, to avoid having to sign-extend virtual addresses
// that have the high bit set.
#define MAXVA (1L << (9 + 9 + 9 + 12 - 1))

typedef uint64_t *pagetable_t;
typedef uint64_t pte_t; 

// alloc.c
struct run{
	struct run *next;
};

struct {
	struct run *free_list;
} free_memory;

// paging.c
int 		init_page_table(void);
pagetable_t init_paging(void);

// alloc.c
void 		init_physical_ram(void);
void *		free_range_by_pages(void *phy_start_addr, void *phy_end_addr);
void *		memset(void *addr, char c, int n);
void *		alloc_page(void);

#endif