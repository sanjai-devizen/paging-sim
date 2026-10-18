#include <stdio.h>
#include "defs.h"

void
panic(char *message){
	printf("\npanic: %s", message);
	exit(1);
}