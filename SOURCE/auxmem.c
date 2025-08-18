// FILLBUFFER for most simple embedded systems (inc NDS)
//#define FILLBUFFER (1024L * 256)  //256KiB

// FILLBUFFER for most desktop computers
//#define FILLBUFFER (1024L * 1024 * 256) //256MiB



#ifndef FILLBUFFER
#warning "FILLBUFFER must be specicifically defined when compiling for a platform on the basis of how much RAM can be afforded for the operation.\n Default FILLBUFFER is 256MiB."
#define FILLBUFFER (1024L * 1024 * 256)  //256MiB
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <auxmem.h>

char * file_g;
FILE * swap_g;
size_t size_g;
AM_error_t AM_error_g = AM_SUCCESS;

void AM_init(const char * file, size_t size) {
	size_t file_name_len;

	swap_g = fopen(file, "wb+");
	if(!swap_g) exit(1);
	file_name_len = strlen(file);

	file_g = malloc(file_name_len + sizeof(char));
	if(!swap_g) {
		fclose(swap_g);
		exit(1);
	}

	strcpy(file_g, file);

	setvbuf(
		swap_g, 
		NULL, //Buffer char*
                _IONBF, //Potential switch to _IOFBF
		0x00
	);

	size_t div = size / FILLBUFFER;
	size_t rem = size % FILLBUFFER;
	char * zero_buff = calloc(1, FILLBUFFER);

	for(size_t i = 0; i < div; i++) {
		fwrite(zero_buff, 1 , FILLBUFFER, swap_g);
	}
	fwrite(zero_buff, 1, rem, swap_g);

	free(zero_buff);

	size_g = size;
}

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

void AM_quit() {
	free(file_g);
	fclose(swap_g);
}
