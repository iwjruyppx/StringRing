#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>

#include "main.h"
#include "StringRing.h"

#define PRINT_BUFF  64
void osLog(const char * sFormat, ...){
    
    char InputBuff[PRINT_BUFF];
    va_list    args;
    int size;

    va_start(args, sFormat);
    size = vsnprintf(InputBuff,PRINT_BUFF, sFormat, args);
    va_end(args);
    StringRingDataSet(InputBuff, size);
}

void callback(void* data)
{
    char *p = data;
      printf("%s", (p+2));
}


 int main( void )
{
    int count = 0;
    StringRingInit(callback);
    while(1)
    {
        osLog("%d\n",count++);
    }
}



