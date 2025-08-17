#include <stdio.h>

#include <auxmem.h>

int main() {
	//So I don't fry my SSD this large one won't be part of the unit tests
	//AM_init("/home/adrian/TESTFILES/test.bin", 1024L * 1024 * 1024 * 4);
	
	AM_init("/home/adrian/TESTFILES/test.bin", 123456L);
	AM_quit();
	return 0;
}
