#include <stdio.h>

#include <auxmem.h>

int main() {
	AM_init("/home/adrian/TESTFILES/test_A.bin", 1024L);
	AM_setbyte(10, 0xFA);
	AM_setbyte(11, 0xCE);
	printf("%02X %02X\n", 
		AM_getbyte(10),
		AM_getbyte(11)
	);
	AM_quit();
	return 0;
}
