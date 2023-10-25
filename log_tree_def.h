#ifndef __LOG_TREE_DEF_H
#define __LOG_TREE_DEF_H


#include <stdint.h>

#include "log_tree.h"



/*================== log tree kernel ==================*/


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          


/*================== ringbuffer ==================*/




typedef struct{	
	uint8_t* 	buffer;
	uint64_t	 buffer_size;
	uint64_t 	length;
	uint8_t* 	read;
	uint8_t* 	write;
}log_tree_ringbuffer_t, *log_tree_ringbuffer_p;



/*================== ringbuffer ==================*/



/*================== log tree ==================*/

// typedef struct{	
// 	lt_uint8_t layers ;
// 	lt_uint8_t format;
// }lt_type_t;

// typedef struct{	
// 	lt_uint8_t layers ;
// 	lt_uint8_t format;
// }lt_logtree;

/*
  |
  */
// void log_tree_Init(log_tree_ringbuffer_p ringbuffer );



#endif





