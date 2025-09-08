#include <stdio.h>
#include <stdbool.h>

#include <auxmem.h>
#include <auxmem/heap.h>

/*
 * Some basic heap tests
 */

int main() {
	AM_init("/home/adrian/TESTFILES/test_F.bin", 256L);
	AMALLOC_init();

	AM_addr_t a = AMALLOC_alloc(100);
	AM_addr_t b = AMALLOC_alloc(100);
	AM_addr_t c = AMALLOC_alloc(100);

	bool part1 = (
		a != 0 &&
		b != 0 &&
		c == 0
	);

	AMALLOC_free(b);

	c = AMALLOC_alloc(100);

	bool part2 = c != 0;
	bool part3 = c == b;
	bool part4 = AMALLOC_getfree() == 55; //Remember one byte gets spared for the NULL value
	
	AMALLOC_free(a);
	AMALLOC_free(c);

	bool part5 = AMALLOC_isempty();
	
	if(part1 && part2 && part3 && part4 && part5) {
		printf("SUCCESS\n");
	}else{
		printf("FAILURE [%s%s%s%s%s]\n",
			part1 ? "Y" : "N",
			part2 ? "Y" : "N",
			part3 ? "Y" : "N",
			part4 ? "Y" : "N",
			part5 ? "Y" : "N"
		);
	}

	AM_quit();
	return 0;
}
