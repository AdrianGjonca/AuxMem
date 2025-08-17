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

#include <auxmem.h>

char * file_g;
FILE * swap_g;

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
}

void AM_quit() {
	free(file_g);
	fclose(swap_g);
}
