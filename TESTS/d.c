#include <stdio.h>
#include <string.h>
#include <auxmem.h>

/*
 * setbytes and getbytes test, within bounds, using string
 */

const char test_str[] = "Hello World";

int main() {
	AM_init("/home/adrian/TESTFILES/test_D.bin", 256L);
	AM_setbytes(
		0, 
		(uint8_t *) test_str, 
		strlen(test_str) + 1
	);
	
	char retrieved_val[256];

	AM_getbytes(
		0,
		(uint8_t *) retrieved_val,
		sizeof(retrieved_val)
	);

	if(strcmp(test_str, retrieved_val)) 
		printf("FAILURE\n");
	else
		printf("SUCCESS\n");

	AM_quit();
}
