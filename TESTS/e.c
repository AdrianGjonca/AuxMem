#include <stdio.h>
#include <string.h>
#include <auxmem.h>
#include <stdlib.h>

/*
 * setbytes and getbytes test, within bounds, using string
 * HEAP VERSION
 */

const char test_str[] = "Hello World";

int main() {
	AM_init("/home/adrian/TESTFILES/test_D.bin", 256L);
	AM_setbytes(
		0, 
		(uint8_t *) test_str, 
		strlen(test_str) + 1
	);
	
	char * retrieved_val;
	retrieved_val = (char *) AM_getbytes_heap(
		0,
		strlen(test_str) + 1
	);


	if(strcmp(test_str, retrieved_val)) 
		printf("FAILURE\n");
	else
		printf("SUCCESS\n");
	
	free(retrieved_val);
	AM_quit();
}
