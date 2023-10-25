#ifndef __LOG_TREE_H
#define __LOG_TREE_H

/*=========== log tree setting ===========*/ 
#define USE_std 1


/*=========== log tree setting over ===========*/ 



#define lt_sucess	0
#define lt_Insufficient_buffer	1


#define RingBuffer_DEBUG 0

#if RingBuffer_DEBUG
#include <stdio.h>
#endif
// 
#if USE_std
#include <stdlib.h>
#else

#endif



void lt_ringbuffer_Init(long unsigned int size);
uint32_t lt_ringbuffer_push(uint8_t data);
uint8_t lt_ringbuffer_pop(void);

#endif

