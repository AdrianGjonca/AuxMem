#include <stdio.h>

#include <auxmem.h>

/*
 * Failure state on write test
 */

int main() {
	AM_init("/home/adrian/TESTFILES/test_B.bin", 1024L);
	
	AM_error_t a = AM_error_g;
	AM_setbyte(1024, 0xFA);
	AM_error_t b = AM_error_g;
	
	if(a == AM_SUCCESS && b == AM_FAILURE) printf("SUCCESS\n");
	else printf("FAILURE\n");

	AM_quit();
	return 0;
}
