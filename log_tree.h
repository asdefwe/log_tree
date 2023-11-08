#ifndef __LOG_TREE_H
#define __LOG_TREE_H

#ifdef __cplusplus
extern "C" {
#endif



/*=========== log tree setting ===========*/ 
#define USE_std 1


/*=========== log tree setting over ===========*/ 

#define TX_buffer_size 80
#define RX_buffer_size  124


#define lt_sucess	0
#define lt_Insufficient_buffer	1


#define RingBuffer_DEBUG 0

#if RingBuffer_DEBUG

#endif
// 
#if USE_std
#include <stdlib.h>
#else

#endif

int my_printf(const uint8_t *format, ...);






#ifdef __cplusplus
}
#endif


#endif

