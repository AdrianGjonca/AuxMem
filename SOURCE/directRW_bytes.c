/* directRW_bytes.c
 * 	Handles the direct access of bytes from virtual memory.
 * 	Handles both byte(s) read and write.
 */

#include "private.h"
#include <auxmem.h>

void AM_setbyte(AM_addr_t address, uint8_t byte_value) {
	if(address >= size_g) {
		AM_error_g = AM_FAILURE;
		return;
	}else {
		AM_error_g = AM_SUCCESS;
	}
	//TODO investigate if a SEEK_CUR system would be faster
	fseek(swap_g, address, SEEK_SET);
	fputc(byte_value, swap_g);
}

uint8_t AM_getbyte(AM_addr_t address) {
	if(address >= size_g) {
		AM_error_g = AM_FAILURE;
		return 0x00;
	}else {
		AM_error_g = AM_SUCCESS;
	}

	fseek(swap_g, address, SEEK_SET);
	return fgetc(swap_g);
}

void AM_setbytes(AM_addr_t address, uint8_t * byte_array, size_t size) {
	if(address + size - 1 >= size_g) {
		AM_error_g = AM_FAILURE;
		return;
	}else {
		AM_error_g = AM_SUCCESS;
	}
	for(size_t i = 0; i < size; i++) {
		AM_setbyte(address + i, byte_array[i]);
	}
}

void AM_getbytes(AM_addr_t address, uint8_t * byte_array, size_t size) {
	if(address + size - 1 >= size_g) {
		AM_error_g = AM_FAILURE;
		return;
	}else {
		AM_error_g = AM_SUCCESS;
	}
	for(size_t i = 0; i < size; i++) {
		byte_array[i] = AM_getbyte(address + i);
	}
}

uint8_t * AM_getbytes_heap(AM_addr_t address, size_t size) {
	uint8_t * byte_array = malloc(size * sizeof(uint8_t));
	if(byte_array == NULL) {
		AM_error_g = AM_FAILURE;
		return NULL;
	}
	//AM_error_g carried on from call below
	AM_getbytes(address, byte_array, size); 
	return byte_array;
}

