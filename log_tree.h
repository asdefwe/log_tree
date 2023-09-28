#ifndef __LOG_TREE_H
#define __LOG_TREE_H

#include "stdio.h"

#define log()  printf()

/*================== log tree kernel ==================*/

	

/*================== ringbuffer ==================*/

typedef unsigned char u8;	



typedef struct{
	u8 buffer[1000];
	u8* Read_p;
	u8* Write_p;
}log_tree_ringbuffer, *log_tree_ringbuffer_p;





/*
  |
  */
// void log_tree_Init(log_tree_ringbuffer_p ringbuffer );



#endif





