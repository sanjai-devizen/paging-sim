#include <stdio.h>
#include "defs.h"

int main(){
        init_physical_ram();
        init_page_table();
        init_paging();
        
        printf("Paging system initialized successfully!\n");
        return 0;
}