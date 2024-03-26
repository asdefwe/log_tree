/*
 * @Author: asdefwe 535294621@qq.com
 * @Date: 2024-03-01 08:53:35
 * @LastEditors: asdefwe 535294621@qq.com
 * @LastEditTime: 2024-03-26 11:32:01
 * @FilePath: \log_tree\log_tree.c
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */

#include "log_tree.h"


#ifdef __cplusplus
extern "C" {
#endif


/*====================================================*/
/*                     ringbuffer                     */
/*====================================================*/

/**
 * @description: 使用动态内存初始化环形缓冲区
 * @param {lg_Queue_t} *RB_handle: 环形缓存区句柄
 * @param {uint32_t} buffer_size: 环形缓存区大小
 * @return {RB_Return}
 */
uint32_t lt_RB_Init(lg_Queue_t *RB_handle, uint32_t buffer_size)
{
    if (buffer_size < 2)
    {
        return CacheTooSmall;
    }
    if (buffer_size >= BufferSize_MAX)
    {
        return CacheTooLarge;
    }

    RB_handle->buffer.addr = (uint8_t *)calloc(buffer_size, sizeof(uint8_t));
    RB_handle->buffer.read = RB_handle->buffer.addr;
    RB_handle->buffer.write = RB_handle->buffer.addr;
    RB_handle->Length = 0;
    RB_handle->Max_Length = buffer_size;

    return OK;
}

/**
 * @description: 删除环形缓存区
 * @param {lg_Queue_t} *RB_handle: 环形缓存区句柄
 * @return {RB_Return}
 */
uint32_t lt_RB_Del(lg_Queue_t *RB_handle)
{
    free(RB_handle->buffer.addr);
    RB_handle->buffer.read = NULL;
    RB_handle->buffer.write = NULL;
    RB_handle->Length = 0;
    RB_handle->Max_Length = 0;

    return OK;
}

/**
 * @description: 向缓存区中写入字符串
 *               使用strlen()或其他函数时，需要去掉字符串末尾的"0"
 * @param {lg_Queue_t} *RB_handle: 环形缓存区句柄
 * @param {uint8_t} *input_addr: 输入字符串地址
 * @param {uint32_t} write_Length: 需要写入的长度
 * @return {RB_Return}
 */
uint32_t RB_Write_String(lg_Queue_t *RB_handle, uint8_t *input_addr, uint32_t write_Length)
{
    // 如果不够存储空间存放新数据,返回错误
    if ((RB_handle->Length + write_Length) > (RB_handle->Max_Length))
    {
        return BufferExceeded;
    }
    else
    {
        // 设置两次写入长度
        uint32_t write_size_a, write_size_b;

        // 如果顺序可用长度小于需写入的长度，需要将数据拆成两次分别写入
        if ((RB_handle->Max_Length - (uint32_t)(RB_handle->buffer.write - RB_handle->buffer.addr)) < write_Length)
        {
            write_size_a = RB_handle->Max_Length - (RB_handle->buffer.write - RB_handle->buffer.addr); // 从尾指针开始写到储存数组末尾
            write_size_b = write_Length - write_size_a;                                                // 从储存数组开头写数据

            // 分别拷贝a、b段数据到储存数组中
            memcpy(RB_handle->buffer.write, input_addr, write_size_a);
            memcpy(RB_handle->buffer.addr, input_addr + write_size_a, write_size_b);

            RB_handle->Length += write_Length;                               // 记录新存储了多少数据量
            RB_handle->buffer.write = RB_handle->buffer.addr + write_size_b; // 重新定位尾指针位置
        }
        else // 如果顺序可用长度大于或等于需写入的长度，则只需要写入一次
        {
            write_size_a = write_Length; // 从尾指针开始写到储存数组末尾

            memcpy(RB_handle->buffer.write, input_addr, write_size_a);

            RB_handle->Length += write_Length;       // 记录新存储了多少数据量
            RB_handle->buffer.write += write_size_a; // 重新定位尾指针位置

            // 如果写入数据后尾指针刚好写到数组尾部，则回到开头，防止越位
            if (RB_handle->buffer.write == (RB_handle->buffer.addr + RB_handle->Max_Length))
            {
                RB_handle->buffer.write = 0;
            }
        }

        return OK;
    }
}

/**
 * @description: 从缓存区中提取一定数量的字符
 *               本身没有字符串越界判断，需要自己做防越界。
 * @param {lg_Queue_t} *RB_handle: 环形缓存区句柄
 * @param {uint8_t} *output_addr: 提取后对外输出的字符串
 * @param {uint32_t} read_Length: 读取长度
 * @return {RB_Return}:
 */
uint8_t RB_Read_String(lg_Queue_t *RB_handle, uint8_t *output_addr, uint32_t read_Length)
{
    if (read_Length > RB_handle->Length)
    {
        return BufferExceeded;
    }
    else
    {
        uint32_t Read_size_a, Read_size_b;
        if (read_Length > (RB_handle->Max_Length - (uint32_t)(RB_handle->buffer.read - RB_handle->buffer.addr)))
        {
            Read_size_a = RB_handle->Max_Length - (RB_handle->buffer.read - RB_handle->buffer.addr);
            Read_size_b = read_Length - Read_size_a;

            memcpy(output_addr, RB_handle->buffer.read, Read_size_a);
            memcpy(output_addr + Read_size_a, RB_handle->buffer.addr, Read_size_b);

            RB_handle->Length -= read_Length;                              // 记录剩余数据量
            RB_handle->buffer.read = RB_handle->buffer.addr + Read_size_b; // 重新定位头指针位置
        }
        else
        {
            Read_size_a = read_Length;

            memcpy(output_addr, RB_handle->buffer.read, Read_size_a);

            RB_handle->Length -= read_Length;      // 记录剩余数据量
            RB_handle->buffer.read += Read_size_a; // 重新定位头指针位置

            // 如果读取数据后头指针刚好写到数组尾部，则回到开头，防止越位
            if (RB_handle->buffer.read == (RB_handle->buffer.addr + RB_handle->Max_Length))
            {
                RB_handle->buffer.read = 0;
            }
        }
        return OK;
    }
}

/*====================================================*/
/*                       list                         */
/*====================================================*/

/**
 * @description: 初始化链表
 * @param {lg_list_t} * const pxList: 链表句柄
 * @return {void}
 */
void vListInitialise(lg_list_t *const pxList)
{
    /* The list structure contains a list item which is used to mark the
    end of the list.  To initialise the list the list end is inserted
    as the only list entry. */
    pxList->pxIndex = (void *)&(pxList->ListEnd); // 初始化列表，并标记尾列表

    /* The list end next and previous pointers point to itself so we know
    when the list is empty. */
    pxList->ListEnd.pxNext = (void *)&(pxList->ListEnd);     // 通过尾节点定位列表中的首位
    pxList->ListEnd.pxPrevious = (void *)&(pxList->ListEnd); // 通过尾节点定位列表中的尾位

    pxList->NumberOfItems = 0U; // 记录列表中存储的数据
}

/**
 * @description: 将新节点插入列表中最后
 * @param {lg_list_t} * const pxList: 链表句柄
 * @param {lg_ListItem_t} * const pxNewListItem: 需要添加节点的句柄
 * @return {void}
 */
void vListInsertEnd(lg_list_t *const pxList, lg_ListItem_t *const pxNewListItem)
{
    lg_ListItem_t *const pxIndex = pxList->pxIndex;
    lg_ListItem_t *const ListEndItem = (void *)pxIndex->pxPrevious;

    /* Insert a new list item into pxList, but rather than sort the list,
    makes the new list item the last item to be removed by a call to
    listGET_OWNER_OF_NEXT_ENTRY(). */
    pxNewListItem->pxNext = (void *)pxIndex;
    pxNewListItem->pxPrevious = pxIndex->pxPrevious;

    ListEndItem->pxNext = (void *)pxNewListItem;
    pxIndex->pxPrevious = (void *)pxNewListItem;

    (pxList->NumberOfItems)++;
}

/**
 * @description: 移除指定节点
 * @param {lg_list_t} *const pxList: 链表句柄
 * @param {lg_ListItem_t} *const pxItemToRemove: 需要移除节点的句柄
 * @return {uint32_t}: 返回链表成员数量
 */
uint32_t uxListRemove(lg_list_t *const pxList, lg_ListItem_t *const pxItemToRemove)
{
    /* 原逻辑是通过被移除的节点找到主列表
     | 现结构提不包含该指针，函数多传入一个参数代替
    */
    lg_ListItem_t *ItemToRemoveNext = (lg_ListItem_t *)pxItemToRemove->pxNext;
    lg_ListItem_t *ItemToRemovePrevious = (lg_ListItem_t *)pxItemToRemove->pxPrevious;

    ItemToRemoveNext->pxPrevious = pxItemToRemove->pxPrevious;
    ItemToRemovePrevious->pxNext = pxItemToRemove->pxNext;

    /* Make sure the index is left pointing to a valid item. */
    if (pxList->pxIndex == pxItemToRemove)
    {
        pxList->pxIndex = ItemToRemovePrevious;
    }
    (pxList->NumberOfItems)--;

    return pxList->NumberOfItems;
}

/**
 * @description: 将元素插入列表或从列表中删除
 * @param {lg_list_t} *list: 链表句柄
 * @param {uint8_t} *FounctionName: 函数名
 * @return {uint32_t}: 2-插入数据   1-无操作   0-删除数据
 */
uint32_t InsertOrRemove(lg_list_t *list, const uint8_t *FounctionName)
{
    uint8_t Number = 0;
    lg_ListItem_t *pxIterator = NULL;
    lg_ListItem_t *del_pxIterator = NULL;
    lg_ListItem_t *const ListEndItem = (void *)list->ListEnd.pxPrevious;
    lg_ListItem_t *NewListItem = NULL;
    uint8_t NameSize = strlen((char *)FounctionName);

    for (pxIterator = ListEndItem; Number < list->NumberOfItems; pxIterator = (lg_ListItem_t *)pxIterator->pxPrevious)
    {
        if (memcmp(pxIterator->pvOwner, FounctionName, NameSize) == 0)
        {
            goto del;
        }
        Number++;
    }

    /* 申请新链表的存储空间 */
    NewListItem = (lg_ListItem_t *)calloc(12, sizeof(uint8_t));
    NewListItem->pvOwner = (char *)calloc(NameSize, sizeof(uint8_t));
    memcpy(NewListItem->pvOwner, FounctionName, NameSize);
    vListInsertEnd(list, NewListItem);
    return 2;

del:
    if (Number == 0)
        return 1;

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

/**
 * @description: 打印列表成员，显示详细信息
 * @param {lg_list_t} *list: 链表句柄
 * @return {void}
 */
void PrintList(lg_list_t *list)
{
    uint8_t Number = 0;
    lg_ListItem_t *pxIterator = NULL;
    lg_ListItem_t *const ListEndItem = (void *)list->ListEnd.pxNext;

    printf("===== list print =====\r\n");
    for (pxIterator = ListEndItem; Number < list->NumberOfItems; pxIterator = (void *)pxIterator->pxNext)
    {
        Number++;
        printf("[%d] %s\r\n", Number, (char *)(pxIterator->pvOwner));
    }
}

/**
 * @description: 链表初始化
 * @param {Founction_name_List_t*} Fnl:
 * @return {uint32_t}: 0-成功
 */
uint32_t List_Init(Founction_name_List_t *Fnl)
{
    vListInitialise(&Fnl->list);

    Fnl->UpdataList = InsertOrRemove;
    Fnl->printList = PrintList;

    return 0;
}

/*====================================================*/
/*                  log tree kernel                   */
/*====================================================*/

/**
 * @description: 添加LOG单行格式
 * @param {lt_core_t} *lt: log tree 核心句柄
 * @param {uint8_t} *flie: 函数所在文件夹的地址
 * @param {uint8_t} *func: 函数名称
 * @param {uint32_t} line: 函数在文件中的行数
 * @param {uint8_t} *str: 输入字符串
 * @return {void}:
 */
void AddSingleRowFormat(lt_core_t *lt,
                        const uint8_t *flie, const uint8_t *func, const uint32_t line,
                        uint8_t *str)
{
    if (lt->SingleRowFormat.filename == TRUE)
    {
        if (lt->SingleRowFormat.function == TRUE)
        {
            if (lt->SingleRowFormat.line == TRUE)
            {
                sprintf((char *)str, "[%s][%s][%d]", flie, func, line);
            }
            else
            {
                sprintf((char *)str, "[%s][%s]", flie, func);
            }
        }
        else
        {
            if (lt->SingleRowFormat.line == TRUE)
            {
                sprintf((char *)str, "[%s][%d]", flie, line);
            }
            else
            {
                sprintf((char *)str, "[%s]", flie);
            }
        }
    }
    else
    {
        if (lt->SingleRowFormat.function == TRUE)
        {
            if (lt->SingleRowFormat.line == TRUE)
            {
                sprintf((char *)str, "[%s][%d]", func, line);
            }
            else
            {
                sprintf((char *)str, "[%s]", func);
            }
        }
        else
        {
            if (lt->SingleRowFormat.line == TRUE)
            {
                sprintf((char *)str, "[%d]", line);
            }
        }
    }

    strncpy((char *)str + strlen((char *)str), (char *)lt->SingleRowFormat.Interval_format, strlen((char *)lt->SingleRowFormat.Interval_format));
}

/**
 * @description: 添加多行LOG起始的格式字符串，默认“  |”
 * @param {lt_core_t} *lt: log tree 核心句柄
 * @param {uint8_t} *str: 输入字符串
 * @return {void}:
 */
void AddMultipleRowFormat_start(lt_core_t *lt, uint8_t *str)
{
    memcpy(str,
           lt->MultipleRowFormat.FirstTextIndent_format,
           lt->MultipleRowFormat.FirstTextIndent_length);

    *(str + lt->MultipleRowFormat.FirstTextIndent_length) = *lt->MultipleRowFormat.SecondaryTextIndent1_format;
}

/**
 * @description: 添加多行LOG中间的格式字符串，默认“   ”
 * @param {lt_core_t} *lt: log tree 核心句柄
 * @param {uint8_t} *str: 输入字符串
 * @return {void}:
 */
void AddMultipleRowFormat_middle(lt_core_t *lt, uint8_t *str)
{
    memcpy(str,
           lt->MultipleRowFormat.SecondarySecondaryTextIndent_format,
           strlen((char *)lt->MultipleRowFormat.SecondarySecondaryTextIndent_format));
}

/**
 * @description: 添加多行LOG末尾的格式字符串，默认“--”
 * @param {lt_core_t} *lt: log tree 核心句柄
 * @param {uint8_t} *str: 输入字符串
 * @return {void}:
 */
void AddMultipleRowFormat_end(lt_core_t *lt, uint8_t *str)
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

uint8_t TX_buffer[TX_buffer_size];
/**
 * @description: log tree 核心输出函数
 * @param {lt_core_t} *lt: log tree 核心句柄
 * @param {uint8_t} *flie: 函数所在文件夹的地址
 * @param {uint8_t} *func: 函数名称
 * @param {uint32_t} line: 函数在文件中的行数
 * @param {uint8_t} *format: 输入字符串
 * @return {uint32_t}: 输出的字符数量
 */
extern uint32_t lt_printf(lt_core_t *lt, const uint8_t *flie, const uint8_t *func, uint32_t line, uint8_t *format, ...)
{
    va_list args;
    uint32_t count;

    memset(TX_buffer, 0, TX_buffer_size);

    lt->fnl.UpdataList(&lt->fnl.list, func);

    // 添加辅助信息
    if (lt->fnl.list.NumberOfItems == 1)
    {
        AddSingleRowFormat(lt, flie, func, line, TX_buffer);
    }
    else if (lt->fnl.list.NumberOfItems == 2)
    {
        AddMultipleRowFormat_start(lt, TX_buffer);
        AddMultipleRowFormat_end(lt, TX_buffer + strlen((char *)TX_buffer));
        AddSingleRowFormat(lt, flie, func, line, TX_buffer + strlen((char *)TX_buffer));
    }
    else
    {
        AddMultipleRowFormat_start(lt, TX_buffer);
        for (int i = 0; i < lt->fnl.list.NumberOfItems - 2; i++)
        {
            AddMultipleRowFormat_middle(lt, TX_buffer + strlen((char *)TX_buffer));
            AddMultipleRowFormat_start(lt, TX_buffer + strlen((char *)TX_buffer));
        }
        AddMultipleRowFormat_end(lt, TX_buffer + strlen((char *)TX_buffer));
        AddSingleRowFormat(lt, flie, func, line, TX_buffer + strlen((char *)TX_buffer));
    }

    va_start(args, format);
    count = vsnprintf((char *)TX_buffer + strlen((char *)TX_buffer), TX_buffer_size, (char *)format, args);
    va_end(args);

    Console_Output(TX_buffer, strlen((char *)TX_buffer));

    return count;
}

#ifdef __cplusplus
}
#endif




