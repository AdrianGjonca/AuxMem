#include <stdio.h>

#include <auxmem.h>

/*
 * Set and read of bytes test
 */
int main() {
	AM_init("/home/adrian/TESTFILES/test_A.bin", 1024L);
	AM_setbyte(10, 0xFA);
	AM_setbyte(11, 0xCE);
	uint8_t a = AM_getbyte(10);
	uint8_t b = AM_getbyte(11);
	
	if(a == 0xFA && b == 0xCE) printf("SUCCESS\n");
	else printf("FAILURE\n");

	AM_quit();
	return 0;
}
