#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	for(size_t i = 0; i < size; i++) {
		fputc(0x00, swap_g);
	}
}

void AM_quit() {
	free(file_g);
	fclose(swap_g);
}

#if 1
extern char * file_g;
#endif
