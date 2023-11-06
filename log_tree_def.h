#ifndef __LOG_TREE_DEF_H
#define __LOG_TREE_DEF_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>

#include "log_tree.h"






                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          


/*===============================================================*/
/*                           ringbuffer                          */
/*===============================================================*/

typedef struct{	
	uint8_t* 	buffer;
	uint64_t	buffer_size;
	uint64_t 	length;
	uint8_t* 	read;
	uint8_t* 	write;
}log_tree_ringbuffer_t, *log_tree_ringbuffer_p;

void lt_ringbuffer_Init(long unsigned int size);
uint32_t lt_ringbuffer_push(uint8_t data);
uint8_t lt_ringbuffer_pop(void);
uint32_t lt_ringbuffer_push_str(uint8_t* str, int size);
uint32_t lt_ringbuffer_pop_str(void);


/*===============================================================*/
/*                              list                             */
/*===============================================================*/
// 借鉴FreeRTOS的列表定义

/*
 | Definition of the only type of object that a list can contain.
 */
typedef struct 
{
	uint32_t	xItemValue;				// 量化节点位置
	struct xLIST_ITEM*  pxNext;			/*< Pointer to the next ListItem_t in the list. */
	struct xLIST_ITEM*  pxPrevious;		/*< Pointer to the previous ListItem_t in the list. */
	void * pvOwner;						/*< Pointer to the object (normally a TCB) that contains the list item.  There is therefore a two way link between the object containing the list item and the list item itself. */
}lg_ListItem_t;

typedef struct 
{					
	uint32_t	xItemValue;				// 量化节点位置
	struct xLIST_ITEM*  pxNext;			// 下一个节点
	struct xLIST_ITEM*  pxPrevious;		// 上一个节点
}lg_MiniListItem_t;


typedef struct 
{
	uint32_t	NumberOfItems;		// 列表中成员的数量
	lg_ListItem_t* 	pxIndex;		/*< Used to walk through the list */
	lg_MiniListItem_t ListEnd;		/*< List item that contains the maximum possible item value meaning it is always at the end of the list and is therefore used as a marker. */
}lg_list_t;

// 节点最大值
#define MAX_List	0xFFFFFFFFUL






/*===============================================================*/
/*                        log tree kernel                        */
/*===============================================================*/

/*	
 |	[position][function1][line]   log_tree begin
 |		↑     	   ↑	   ↑    ↑
 |		|     	   |       |  与输出内容的间隔格式						
 |		|     	   |     是否显示代码行数
 |      |	     是否显示函数名
 |	是否显示文件路径
*/

// log_tree 的单行格式设置
typedef struct 
{
	uint8_t filename;				//是否显示文件路径
	uint8_t function;				//是否显示函数名
	uint8_t	line;					//是否显示代码行数
	uint8_t	Interval_format;	 	//与输出内容的间隔格式
}lt_SingleRowFormat_t;

/*
 |	[function1] log_tree begin
 | 		|--[function2] fbbdfbdfbdfbdfb
 | 		|     |--[function3] iwqqwe568941
 | 		|     |     |--[function4] 489516qwd
 | 		|--[funciton2] dqw4896156
 | 		|--[funciton2] 4615wdxvc489
 |    ↑ ↑ ↑      ↑
 |	  | | |    次级次级缩进格式
 |    | | 次级缩进长度
 |    | 次级缩进格式
 |   首行缩进长度
 */
typedef struct 
{
	uint8_t FirstTextIndent_length;					//首行缩进长度
	uint8_t	SecondaryTextIndent_format;				//次级缩进格式
	uint8_t	SecondaryTextIndent_length;				//次级缩进长度
	uint8_t	SecondarySecondaryTextIndent_format;	//次级次级缩进格式
}lt_MultipleLineFormat_t;

typedef struct 
{
	lt_SingleRowFormat_t 		SingleRowFormat;
	lt_MultipleLineFormat_t		MultipleLineFormat;
	lg_list_t FunctionName;
	uint8_t	isbegin;
	log_tree_ringbuffer_p log_buff;
}lt_core_t;



/*
  |
  */
// void log_tree_Init(log_tree_ringbuffer_p ringbuffer );







#ifdef __cplusplus
}
#endif

#endif





