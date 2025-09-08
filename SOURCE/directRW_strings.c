/* directRW_strings.c
 * 	Handles the direct access of strings from virtual memory.
 * 	Handles both byte(s) read and write.
 */
/*
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

#include <auxmem.h>

bool dangerous_g = 0;
size_t strcap_g = 1024;

void AM_set_strcap(size_t str_cap) {
	strcap_g = str_cap;
}

void AM_setstring(AM_addr_t address, const char * string) {
	size_t size = strlen(string)+1;
	uint_t * data = (uint_t *) string;
	AM_setbytes(address, data, size);
}

extern void AM_getbytes(AM_addr_t address, char * mutstring) {
	int j = 0;
	for(AM_addr_t i = address; i < strcap_g && i < size_g; i++, j++) {
		
	}
}
*/
