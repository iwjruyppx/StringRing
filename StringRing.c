/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "StringRing.h"

#define HEADER_SIZE    2
#define MAX_QUEUE_LEN   3
#define MAX_DATA_SIZE    128

static const char HEADER[HEADER_SIZE] ={0,0};

typedef struct
{
    uint8_t q_index;
    uint8_t d_index;
    char data[MAX_QUEUE_LEN][MAX_DATA_SIZE];
    void (*callback)(void* evtData);
}data_t;

static data_t mem;

static void HeaderSetUp(void)
{
    mem.q_index = (mem.q_index+1)%MAX_QUEUE_LEN;
    mem.d_index = 0;
    memset(mem.data[mem.q_index],0x00,MAX_DATA_SIZE);
    for(int i=0;i<HEADER_SIZE;i++)
    {
        mem.data[mem.q_index][mem.d_index] = HEADER[i];
        mem.d_index++;
    }
}

void StringRingDataSet(char * data, int len)
{
    for(int i=0;i<len;i++)
    {
        mem.data[mem.q_index][mem.d_index] = data[i];
        mem.d_index++;
        if(mem.d_index >= MAX_DATA_SIZE)
        {
            mem.callback(mem.data[mem.q_index]);
            HeaderSetUp();            
        }
    }
}

void StringRingInit(void callback(void*))
{
    mem.q_index = 0;
    mem.d_index = 0;
    mem.callback = callback;
    memset(mem.data,0x00,MAX_QUEUE_LEN*MAX_DATA_SIZE);
    HeaderSetUp();
}