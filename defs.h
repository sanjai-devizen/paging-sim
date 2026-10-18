#ifndef DEFS_H
#define DEFS_H

#include <stdint.h> // Required for uint8_t and uint64_t

#define RAM_SIZE (16 * 1024 * 1024)

// Use extern so the variables are only defined once in alloc.c
extern uint8_t *custom_ram;

struct run {
    struct run *next;
};

// Define a type for the struct so we can instantiate it cleanly
struct free_mem_struct {
    struct run *free_list;
};
extern struct free_mem_struct free_memory;

// Standardize macro names to match your usage in paging.c and alloc.c
#define PAGE_SIZE  4096 
#define PGSHIFT 12   

#define PGROUNDUP(sz)  (((sz) + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))
#define PGROUNDDOWN(a) (((a)) & ~(PAGE_SIZE - 1))

#define PTE_V (1L << 0) 
#define PTE_R (1L << 1)
#define PTE_W (1L << 2)
#define PTE_X (1L << 3)
#define PTE_U (1L << 4) 

// Standardize naming to what you used in paging.c
#define PA_TO_PTE(pa) ((((uint64_t)pa) >> 12) << 10)
#define PTE_TO_PA(pte) (((pte) >> 10) << 12)

#define PTE_FLAGS(pte) ((pte) & 0x3FF)

#define PXMASK         0x1FF 
#define PXSHIFT(level) (PGSHIFT + (9 * (level)))
#define PX(level, va)  ((((uint64_t)(va)) >> PXSHIFT(level)) & PXMASK)

#define MAX_VA (1L << (9 + 9 + 9 + 12 - 1))

typedef uint64_t *pagetable_t;
typedef uint64_t pte_t;

// Prototypes
int init_page_table(void);
pagetable_t init_paging(void);
void init_physical_ram(void);
void *free_range_by_pages(void *phy_start_addr, void *phy_end_addr);
void *memset(void *addr, char c, int n);
void *alloc_page(void);
void free_page(void *physical_addr);
void panic(char *message); // Added panic prototype

#endif