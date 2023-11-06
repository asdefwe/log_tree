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

typedef struct{	
	lt_uint8_t layers ;
	lt_uint8_t format;
}lt_type_t;

typedef struct{	
	lt_uint8_t layers ;
	lt_uint8_t format;
}lt_logtree;




/*	
 |	  [position][function1][line]   log_tree begin
 |			   |					|				 |      |
 |			   |					|                |   与输出内容的间隔格式						
 |			   |                    |        是否显示代码行数
 |             |			是否显示函数名、
 |		是否显示文件路径
*/

// log_tree 的单行格式设置
typedef struct lt_SingleRowFormat_t
{
	uint8_t filename;					  //是否显示文件路径
	uint8_t function;				 	   //是否显示函数名
	uint8_t	line;						  		//是否显示代码行数
	uint8_t	Interval_format;	 //与输出内容的间隔格式
};

/*
 |	[function1] log_tree begin
 | 		   |--[function2] fbbdfbdfbdfbdfb
 | 		   |     |--[function3] iwqqwe568941
 | 		   |     |     |--[function4] 489516qwd
 | 		   |--[funciton2] dqw4896156
 | 		   |--[funciton2] 4615wdxvc489
 | 
 |
 |
 |
 |
 */





/*
  |
  */
// void log_tree_Init(log_tree_ringbuffer_p ringbuffer );



#endif





