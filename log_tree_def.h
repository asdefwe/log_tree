#ifndef __LOG_TREE_DEF_H
#define __LOG_TREE_DEF_H

#include "stdio.h"
#include "stdint.h"
#include "log_tree.h"

#define log()  printf()

/*================== log tree kernel ==================*/
typedef unsigned char u8;	
typedef uint8_t lt_uint8_t;
typedef uint16_t lt_uint16_t;
typedef uint32_t lt_uint32_t;	

typedef lt_uint32_t lt_err_t;

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          


/*================== ringbuffer ==================*/

typedef struct{
	lt_uint8_t buffer[buffer_size];
	lt_uint8_t* buffer_start;
	lt_uint8_t* buffer_end;
}lt_ringbuffer_t;



typedef struct{	
	lt_uint8_t* read_p;
	lt_uint8_t* write_p;
	lt_ringbuffer_t ringbuffer;
}log_tree_ringbuffer, *log_tree_ringbuffer_p;



/*================== log tree ==================*/

typedef struct{	
	lt_uint8_t layers ;
	lt_uint8_t format;
}lt_type_t;

typedef struct{	
	lt_uint8_t layers ;
	lt_uint8_t format;
}lt_logtree;

/*
  |
  */
// void log_tree_Init(log_tree_ringbuffer_p ringbuffer );



#endif





