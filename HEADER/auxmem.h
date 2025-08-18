#include <stddef.h>
#include <stdint.h>

typedef size_t AM_addr_t;
typedef enum {
	AM_SUCCESS,
	AM_FAILURE 
	//TODO comprehensive error states
} AM_error_t;

extern AM_error_t AM_error_g;

extern void AM_init(const char * file, size_t size);

extern void AM_setbyte(AM_addr_t address, uint8_t byte_value);
extern uint8_t AM_getbyte(AM_addr_t address);

extern void AM_setbytes(AM_addr_t address, uint8_t * byte_array, size_t size);
extern void AM_getbytes(AM_addr_t address, uint8_t * byte_array, size_t size);
extern uint8_t * AM_getbytes_heap(AM_addr_t address, size_t size);

extern void AM_quit();
