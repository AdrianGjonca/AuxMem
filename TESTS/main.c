#include <stdio.h>

extern void AM_init(const char * file, size_t size);
extern void AM_quit();
extern char * file_g;

int main() {
	AM_init("/home/adrian/TESTFILES/test.bin", 1024);
	printf("Debug A %s\n", file_g);
	AM_quit();
	return 0;
}
