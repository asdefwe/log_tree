#include "log_tree_def.h"
#include "log_tree.h"

#include <stdio.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif


uint32_t lt_ringbuffer_push_str(uint8_t* str, int size);
uint32_t lt_ringbuffer_pop_str(void);



/*====================================================*/
/*            private Cropping <stdio.h>              */
/*====================================================*/
// 参考文档
// https://blog.csdn.net/plm199513100/article/details/104905990
// https://www.runoob.com/cprogramming/c-function-vsprintf.html
// https://wenku.csdn.net/answer/cd802c5640a44ac29cbc2f67173b20a5

#include <stdio.h>
#include <stdarg.h>


char TX_buffer[TX_buffer_size];
int my_printf(const uint8_t *format, ...) 
{
    va_list args;
    int count;

    va_start(args,format);
    count = vsnprintf(TX_buffer, TX_buffer_size, format, args);
    va_end(args);

    return lt_ringbuffer_push_str(TX_buffer, count);
}



/*====================================================*/
/*                     ringbuffer                     */
/*====================================================*/
#define ringbuffer_end_address  (lt_ringbuffer.buffer + lt_ringbuffer.buffer_size - 1)

log_tree_ringbuffer_t lt_ringbuffer;

void lt_ringbuffer_Init(long unsigned int size)
{
    //使用标准malloc函数申请空间
    uint8_t* buffer = (uint8_t*)malloc(size);
    lt_ringbuffer.buffer = buffer;      //记录ringbuffer的开始地址
    
    //
    lt_ringbuffer.buffer_size = size;
    lt_ringbuffer.length = 0;
    
    //初始化
    lt_ringbuffer.write = lt_ringbuffer.buffer;
    lt_ringbuffer.read = lt_ringbuffer.buffer;

#if RingBuffer_DEBUG
    printf("RingBuffer address:%lu\r\n", (long unsigned int)buffer);
#endif
}

uint32_t lt_ringbuffer_push(uint8_t data)
{
    //检测缓存中是否还有空闲空间
    if(lt_ringbuffer.length == lt_ringbuffer.buffer_size)
    {
        return 1;
    }

    //写入数据，并记录缓存数据的数量
    *lt_ringbuffer.write =  data;
    lt_ringbuffer.length++;

#if RingBuffer_DEBUG
    printf("write data:%c\t", *lt_ringbuffer.write);
    printf("write address:%lu\t", (long unsigned int)lt_ringbuffer.write);
    printf("ringbuffer.length:%lu\r\n", (long unsigned int)lt_ringbuffer.length);
#endif

    //移动写指针
    lt_ringbuffer.write++;
    if(lt_ringbuffer.write > ringbuffer_end_address)
    {
        lt_ringbuffer.write = lt_ringbuffer.buffer;
    }

    return lt_sucess;
}

uint8_t lt_ringbuffer_pop(void)
{
    uint8_t data = 0;

    // 检测缓存中是否有数据
    if(lt_ringbuffer.length == 0) 
    {
        return 1;
    }

    // 读取缓存中的数据
    data = *lt_ringbuffer.read;
    lt_ringbuffer.length--;

#if RingBuffer_DEBUG
    printf("read data:%c\t", *lt_ringbuffer.read);
    printf("read address:%lu\t", (long unsigned int)lt_ringbuffer.read);
    printf("ringbuffer length:%ld\r\n", lt_ringbuffer.length);
#endif

    // 移动读指针
    lt_ringbuffer.read++;
    if(lt_ringbuffer.read > ringbuffer_end_address)
    {
        lt_ringbuffer.read = lt_ringbuffer.buffer;
    }

    return data;
}

uint32_t lt_ringbuffer_push_str(uint8_t* str, int size)
{
    uint32_t i = 0;

    do
    {
       lt_ringbuffer_push(*(str + i));
       i++;
    } while (size--);
    return i;
}


#if RX_buffer_size > 0
uint8_t RX_Buffer[RX_buffer_size];
#else
uint8_t RX_Buffer;
#endif

uint32_t lt_ringbuffer_pop_str(void)
{
    int i=0;

#if RX_buffer_size > 0
    memset(RX_Buffer, 0, RX_buffer_size);
    do
    {
       RX_Buffer[i] = lt_ringbuffer_pop();
       i++;
    } while (lt_ringbuffer.length);
#else

#endif

    printf("%s", RX_Buffer);

    return 0;
}




/*====================================================*/
/*                       list                         */
/*====================================================*/

// 初始化列表
void vListInitialise( lg_list_t * const pxList )
{
	/* The list structure contains a list item which is used to mark the
	end of the list.  To initialise the list the list end is inserted
	as the only list entry. */
	pxList->pxIndex = (void*) &( pxList->ListEnd );			// 初始化列表，并标记尾列表

	/* The list end next and previous pointers point to itself so we know
	when the list is empty. */
	pxList->ListEnd.pxNext = (void*) &( pxList->ListEnd );	 // 通过尾节点定位列表中的首位
	pxList->ListEnd.pxPrevious = (void*) &( pxList->ListEnd ); // 通过尾节点定位列表中的尾位

	pxList->NumberOfItems = 0U;     //记录列表中存储的数据

}

// 将新节点插入列表中最后
void vListInsertEnd(lg_list_t * const pxList, lg_ListItem_t * const pxNewListItem )
{
    lg_ListItem_t * const pxIndex = pxList->pxIndex;
    lg_ListItem_t * const ListEndItem = (void *)pxList->pxIndex->pxPrevious;

	/* Insert a new list item into pxList, but rather than sort the list,
	makes the new list item the last item to be removed by a call to
	listGET_OWNER_OF_NEXT_ENTRY(). */
	pxNewListItem->pxNext = (void *)pxIndex;
	pxNewListItem->pxPrevious = pxList->ListEnd.pxPrevious;

    ListEndItem->pxNext = (void *)pxIndex;
	pxIndex->pxPrevious = (void *)pxNewListItem;

	( pxList->NumberOfItems )++;
}

// 移除指定节点
uint32_t uxListRemove(lg_list_t * const pxList, lg_ListItem_t * const pxItemToRemove )
{
    /* 原逻辑是通过被移除的节点找到主列表
     | 现结构提不包含该指针，函数多传入一个参数代替
    */
   lg_ListItem_t* ItemToRemoveNext = (lg_ListItem_t*)pxItemToRemove->pxNext;
   lg_ListItem_t* ItemToRemovePrevious = (lg_ListItem_t*)pxItemToRemove->pxPrevious;

	ItemToRemoveNext->pxPrevious = pxItemToRemove->pxPrevious;
	ItemToRemovePrevious->pxNext = pxItemToRemove->pxNext;

	/* Make sure the index is left pointing to a valid item. */
	if( pxList->pxIndex == pxItemToRemove )
	{
		pxList->pxIndex = ItemToRemovePrevious;
	}

	( pxList->NumberOfItems )--;

	return pxList->NumberOfItems;
}

uint32_t InsertOrRemove(lg_list_t* list, char* FounctionName)
{
    uint8_t Number = 0;
    lg_ListItem_t * pxIterator = NULL;
    lg_ListItem_t * const ListEndItem = (void*)list->ListEnd.pxPrevious;
    uint8_t NameSize = sizeof(FounctionName);

    for(pxIterator = ListEndItem; Number < list->NumberOfItems; pxIterator = (void*)pxIterator->pxNext)
    {
        Number++;
        if(memcmp(FounctionName, pxIterator->pvOwner, NameSize) == 0) 
        {
            goto del;
        }  
    }

    /* 申请新链表的存储空间 */
    lg_ListItem_t* NewListItem = (lg_ListItem_t*)calloc(12, sizeof(char));
    NewListItem->pvOwner = (char*)calloc(NameSize, sizeof(char));
    memcpy(NewListItem->pvOwner, FounctionName, NameSize);
    vListInsertEnd(list, NewListItem);

    return 0;

del:
    for(pxIterator = ListEndItem; Number > 0; pxIterator = (void*)pxIterator->pxNext)
    {
        Number--;
        uxListRemove(list, NewListItem);
    }
    return 0;
}

void PrintList(lg_list_t* list)
{
    uint8_t Number = 0;
    lg_ListItem_t * pxIterator = NULL;
    lg_ListItem_t * const ListEndItem = (void*)list->ListEnd.pxPrevious;

    for(pxIterator = ListEndItem; Number > list->NumberOfItems; pxIterator = (void*)pxIterator->pxNext)
    {
        printf("[%s]\r\n", (char*)(list->pxIndex->pvOwner));
    }
}

uint32_t List_Init(Founction_name_List_t* Fnl)
{
    vListInitialise(&Fnl->list);

    Fnl->UpdataList = InsertOrRemove;
    Fnl->printList = PrintList;

    return 0;
}



#ifdef __cplusplus
}
#endif




