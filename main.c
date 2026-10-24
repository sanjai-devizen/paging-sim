#include <stdio.h>
#include "defs.h"

int main(){
        init_physical_ram();
        init_page_table();
        pagetable_t root_page_table = init_paging();
                
        printf("\nRAM starts at: %p", (void *)custom_ram);
        printf("\nRAM ends at: %p", (void *)custom_ram + RAM_SIZE - 1);
        printf("\nROOT page table at: %p", (void *)root_page_table);
        printf("\nPaging system initialized successfully!\n");
        return 0;
}