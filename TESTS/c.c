#include <stdio.h>

#include <auxmem.h>

/*
 * Failure state on read test
 * AND 0x00 byte return
 */

int main() {
	AM_init("/home/adrian/TESTFILES/test_B.bin", 1024L);
	
	AM_error_t a = AM_error_g;
	uint8_t data = AM_getbyte(1024);
	AM_error_t b = AM_error_g;
	
	if(a == AM_SUCCESS && b == AM_FAILURE && data == 0x00) printf("SUCCESS\n");
	else printf("FAILURE\n");

	AM_quit();
	return 0;
}
