#include <stdio.h>
#include "defs.h"

int 
main(){
	init_physical_ram();
	init_paging_table();
	init_paging();

	return 0;
}