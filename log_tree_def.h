#ifndef __LOG_TREE_DEF_H
#define __LOG_TREE_DEF_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>



/*===============================================================*/
/*                           ringbuffer                          */
/*===============================================================*/

typedef struct
{	
	uint8_t* 	buffer;
	uint8_t* 	read;
	uint8_t* 	write;

}lt_QueueBuffer_Core_t;

typedef struct 
{
	uint32_t	buffer_size;
	lt_QueueBuffer_Core_t buffer;

}lg_Queue_t;


void lt_ringbuffer_Init(long unsigned int size);



/*===============================================================*/
/*                              list                             */
/*===============================================================*/
// 借鉴FreeRTOS的列表定义

/*
 | Definition of the only type of object that a list can contain.
 */
typedef struct 
{
	struct lg_ListItem_t*  pxNext;			/*<  指向列表中下一个ListItem_t的指针。  */
	struct lg_ListItem_t*  pxPrevious;		/*<  指向列表中上一个ListItem_t的指针。  */
	void * pvOwner;						/*< Pointer to the object (normally a TCB) that contains the list item.  There is therefore a two way link between the object containing the list item and the list item itself. */

}lg_ListItem_t;

typedef struct 
{					
	struct lg_ListItem_t*  pxNext;			// 下一个节点
	struct lg_ListItem_t*  pxPrevious;		// 上一个节点

}lg_MiniListItem_t;

typedef struct 
{
	uint32_t	NumberOfItems;		// 列表中成员的数量
	lg_ListItem_t* 	pxIndex;		/*< Used to walk through the list */
	lg_MiniListItem_t ListEnd;		/*< List item that contains the maximum possible item value meaning it is always at the end of the list and is therefore used as a marker. */

}lg_list_t;

// 最终的结构体
typedef struct 
{
	/* 主要结构体 */
	lg_list_t list;

	/* 外置接口函数 */
	uint32_t (*UpdataList)(lg_list_t* Fnl, const uint8_t* FounctionName);
	void (*printList)(lg_list_t* list);

}Founction_name_List_t;

uint32_t List_Init(Founction_name_List_t* fnl);





/*===============================================================*/
/*                        log tree kernel                        */
/*===============================================================*/

/*	
 |	[position][function1][line] log_tree begin
 |		↑     	   ↑	   ↑   ↑
 |		|     	   |       | 与输出内容的间隔格式						
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
	uint8_t*	Interval_format;	 	//与输出内容的间隔格式

}lt_SingleRowFormat_t;

/*				   ===========================================
 |				     [function1] log_tree begin		        ||        
 | 首行缩进格式------>  |--[function2] fbbdfbdfbdfbdfb       ||            
 | 				       |     |--[function3] iwqqwe568941    ||        
 | 次级缩进格式-------->|     |--[function4] 489516qwd       ||        	
 | 				       |--[funciton2] dqw4896156            ||       
 | 				       |--[funciton2] 4615wdxvc489          ||  
 |                 ===========================================       
 |  			     ↑   ↑    ↑
 |				     |   |    次级次级缩进格式
 |  			     |   次级缩进长度 
 |  			    首行缩进长度
 */
typedef struct 
{
	uint8_t*	FirstTextIndent_format;					//首行缩进格式
	uint8_t		FirstTextIndent_length;					//首行缩进长度
	uint8_t*	SecondaryTextIndent1_format;				//次级缩进格式
	uint8_t*	SecondaryTextIndent2_format;				//次级缩进格式
	uint8_t		SecondaryTextIndent2_length;				//次级缩进长度
	uint8_t*	SecondarySecondaryTextIndent_format;	//次级次级缩进格式

}lt_MultipleRowFormat_t;

typedef struct 
{
	lt_SingleRowFormat_t 		SingleRowFormat;		//单行格式
	lt_MultipleRowFormat_t		MultipleRowFormat;		//多行间格式
	Founction_name_List_t 		fnl;					//函数名列表
	// log_tree_ringbuffer_p 		log_buff;				//输出缓存		
	uint8_t	isbegin;		
	
}lt_core_t;



/*
  |
  */
// void log_tree_Init(log_tree_ringbuffer_p ringbuffer );

#define TRUE	1
#define FALSE	0

#define lt_Default_Setting() {										\
	.SingleRowFormat.filename = FALSE,								\
	.SingleRowFormat.function = TRUE,								\
	.SingleRowFormat.line = FALSE,									\
	.SingleRowFormat.Interval_format = " ",							\
	.MultipleRowFormat.FirstTextIndent_format = " ",				\
	.MultipleRowFormat.FirstTextIndent_length = 1,					\
	.MultipleRowFormat.SecondaryTextIndent1_format = "|",			\
	.MultipleRowFormat.SecondaryTextIndent2_format = "-",			\
	.MultipleRowFormat.SecondaryTextIndent2_length = 1,				\
	.MultipleRowFormat.SecondarySecondaryTextIndent_format = " "  	\
}



#ifdef __cplusplus
}
#endif

#endif





