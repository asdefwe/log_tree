
#include "log_tree.h"


#ifdef __cplusplus
extern "C" {
#endif


/*====================================================*/
/*                     ringbuffer                     */
/*====================================================*/
#define ringbuffer_end_address  (lt_ringbuffer.buffer + lt_ringbuffer.buffer_size - 1)

// log_tree_ringbuffer_t lt_ringbuffer;

// void lt_ringbuffer_Init(long unsigned int size)
// {
//     // 使用标准malloc函数申请空间
//     uint8_t* buffer = (uint8_t*)malloc(size);
//     lt_ringbuffer.buffer = buffer;      //记录ringbuffer的开始地址
    
    
//     lt_ringbuffer.buffer_size = size;
//     lt_ringbuffer.length = 0;
    
//     // 初始化
//     lt_ringbuffer.write = lt_ringbuffer.buffer;
//     lt_ringbuffer.read = lt_ringbuffer.buffer;

// }




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
    lg_ListItem_t * const ListEndItem = (void*)pxIndex->pxPrevious;

	/* Insert a new list item into pxList, but rather than sort the list,
	makes the new list item the last item to be removed by a call to
	listGET_OWNER_OF_NEXT_ENTRY(). */
	pxNewListItem->pxNext = (void *)pxIndex;
	pxNewListItem->pxPrevious = pxIndex->pxPrevious;

    ListEndItem->pxNext = (void*)pxNewListItem;
	pxIndex->pxPrevious = (void*)pxNewListItem;

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

// 函  数：将元素插入列表或从列表中删除
// 参  数：列表指针  函数名
// 返回值：2-插入数据   1-无操作   0-删除数据
uint32_t InsertOrRemove(lg_list_t* list, const uint8_t* FounctionName)
{
    uint8_t Number = 0;
    lg_ListItem_t * pxIterator = NULL;
    lg_ListItem_t * del_pxIterator = NULL;
    lg_ListItem_t * const ListEndItem = (void*)list->ListEnd.pxPrevious;
    uint8_t NameSize = strlen(FounctionName);

    for(pxIterator = ListEndItem; Number < list->NumberOfItems; pxIterator = (lg_ListItem_t *)pxIterator->pxPrevious)
    {
        if(memcmp(pxIterator->pvOwner, FounctionName, NameSize) == 0) 
        {
            goto del;
        }
        Number++;
    }

    /* 申请新链表的存储空间 */
    lg_ListItem_t* NewListItem = (lg_ListItem_t*)calloc(12, sizeof(uint8_t));
    NewListItem->pvOwner = (char*)calloc(NameSize, sizeof(uint8_t));
    memcpy(NewListItem->pvOwner, FounctionName, NameSize);
    vListInsertEnd(list, NewListItem);
    return 1;

del:
    if(Number == 0) return 1;

    pxIterator = ListEndItem;
    do
    {
        del_pxIterator = (lg_ListItem_t *)pxIterator;
        pxIterator = (lg_ListItem_t *)pxIterator->pxPrevious;
        uxListRemove(list, del_pxIterator);
        free(del_pxIterator->pvOwner);
        free(del_pxIterator);
        Number--;
    } while (Number > 0);

    return 0;
}

void PrintList(lg_list_t* list)
{
    uint8_t Number = 0;
    lg_ListItem_t * pxIterator = NULL;
    lg_ListItem_t * const ListEndItem = (void*)list->ListEnd.pxNext;

    printf("===== list print =====\r\n");
    for(pxIterator = ListEndItem; Number < list->NumberOfItems; pxIterator = (void*)pxIterator->pxNext)
    {
        Number++;
        printf("[%d] %s\r\n", Number, (char*)(pxIterator->pvOwner));
    }
}

uint32_t List_Init(Founction_name_List_t* Fnl)
{
    vListInitialise(&Fnl->list);

    Fnl->UpdataList = InsertOrRemove;
    Fnl->printList = PrintList;

    return 0;
}

/*====================================================*/
/*                  log tree kernel                   */
/*====================================================*/

void AddSingleRowFormat(lt_core_t* lt,
                        const uint8_t* flie, const uint8_t* func, const uint32_t line,
                        uint8_t* str)
{
    if(lt->SingleRowFormat.filename == TRUE)
    {
        if(lt->SingleRowFormat.function == TRUE)
        {
            if(lt->SingleRowFormat.line == TRUE)
            {
                sprintf(str, "[%s][%s][%d]", flie, func, line);
            }
            else
            {
                sprintf(str, "[%s][%s]", flie, func);
            }
        }
        else
        {
            if(lt->SingleRowFormat.line == TRUE)
            {
                sprintf(str, "[%s][%d]", flie, line);
            }
            else
            {
                sprintf(str, "[%s]", flie);
            }
        }

    }
    else
    {
        if(lt->SingleRowFormat.function == TRUE)
        {
            if(lt->SingleRowFormat.line == TRUE)
            {
                sprintf(str, "[%s][%d]", func, line);
            }
            else
            {
                sprintf(str, "[%s]", func);
            }
        }
        else
        {
            if(lt->SingleRowFormat.line == TRUE)
            {
                sprintf(str, "[%d]", line);
            }
        }
    }

    strncpy(str + strlen(str), lt->SingleRowFormat.Interval_format, strlen(lt->SingleRowFormat.Interval_format));
}   

//添加“  |”
void AddMultipleRowFormat_start(lt_core_t* lt, uint8_t* str)
{ 
    memcpy(str, 
           lt->MultipleRowFormat.FirstTextIndent_format, 
           lt->MultipleRowFormat.FirstTextIndent_length);

    *(str + lt->MultipleRowFormat.FirstTextIndent_length) = * lt->MultipleRowFormat.SecondaryTextIndent1_format;
}

//添加      “   ”
void AddMultipleRowFormat_middle(lt_core_t* lt, uint8_t* str)
{
    memcpy(str, 
           lt->MultipleRowFormat.SecondarySecondaryTextIndent_format,
           strlen(lt->MultipleRowFormat.SecondarySecondaryTextIndent_format));
}

//添加      “--”
void AddMultipleRowFormat_end(lt_core_t* lt, uint8_t* str)
{
    memcpy(str, 
           lt->MultipleRowFormat.SecondaryTextIndent2_format, 
           lt->MultipleRowFormat.SecondaryTextIndent2_length);
}

/*====================================================*/
/*            private Cropping <stdio.h>              */
/*====================================================*/
// 参考文档
// https://blog.csdn.net/plm199513100/article/details/104905990
// https://www.runoob.com/cprogramming/c-function-vsprintf.html
// https://wenku.csdn.net/answer/cd802c5640a44ac29cbc2f67173b20a5

#include <stdarg.h>

char TX_buffer[TX_buffer_size];
extern int lt_printf(lt_core_t* lt,
              const uint8_t* flie, const uint8_t* func, uint32_t line,
              uint8_t *format, ...) 
{
    va_list args;
    int count;
    int res;

    memset(TX_buffer, 0, TX_buffer_size);

    res = lt->fnl.UpdataList(&lt->fnl.list, func);

    //添加辅助信息
    if(lt->fnl.list.NumberOfItems == 1)
    {
        AddSingleRowFormat(lt, flie, func, line, TX_buffer);
    }
    else if(lt->fnl.list.NumberOfItems == 2)
    {
        AddMultipleRowFormat_start(lt, TX_buffer);
        AddMultipleRowFormat_end(lt, TX_buffer + strlen(TX_buffer));
        AddSingleRowFormat(lt, flie, func, line, TX_buffer + strlen(TX_buffer));
    }
    else
    {
        AddMultipleRowFormat_start(lt, TX_buffer);
        for(int i=0;i<lt->fnl.list.NumberOfItems - 2;i++)
        {
            AddMultipleRowFormat_middle(lt, TX_buffer + strlen(TX_buffer));
            AddMultipleRowFormat_start(lt, TX_buffer + strlen(TX_buffer));
        }
        AddMultipleRowFormat_end(lt, TX_buffer + strlen(TX_buffer));
        AddSingleRowFormat(lt, flie, func, line, TX_buffer + strlen(TX_buffer));
    }

    va_start(args,format);
    count = vsnprintf(TX_buffer + strlen(TX_buffer), TX_buffer_size, format, args);
    va_end(args);

    Console_Output(TX_buffer, strlen(TX_buffer));

    return count;
}































#ifdef __cplusplus
}
#endif



