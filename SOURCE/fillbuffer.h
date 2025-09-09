#ifndef FILLBUFFER
// FILLBUFFER for most simple embedded systems (inc NDS)
//#define FILLBUFFER (1024L * 256)  //256KiB

// FILLBUFFER for most desktop computers
//#define FILLBUFFER (1024L * 1024 * 256) //256MiB

#ifdef __NDS__
#define FILLBUFFER (1024L * 256) //256KiB
#endif

#ifndef FILLBUFFER
#warning "FILLBUFFER must be specicifically defined when compiling for a platform on the basis of how much RAM can be afforded for the operation.\n Default FILLBUFFER is 256MiB."
#define FILLBUFFER (1024L * 1024 * 256)  //256MiB
#endif

#endif

