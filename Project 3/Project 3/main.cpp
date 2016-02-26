#include "ppmimage.h"

/**
Error Messages:
1xx I/O error
	101 - failed to read image
	102 - failed to write image
2xx Message R/W error
	201 - message is too large
	202 - no message found
**/

#if defined(WIN32) || defined(_WIN32) 
#define PATH_SEPARATOR "\\" 
#else 
#define PATH_SEPARATOR "/" 
#endif 

int main() {

}