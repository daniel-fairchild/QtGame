#include "debug.h"
#include <stdio.h>

void dbgprnt(const char* file, const char* line, const char* msg){

    printf("%s:%s:\t%s\n", file, line, msg);
}
