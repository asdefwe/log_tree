#include "log_tree_def.h"
#include "log_tree.h"
#include <string.h>




/*=========================================*/
/*                       private Cropping <stdio.h>                        */
/*=========================================*/
//https://blog.csdn.net/plm199513100/article/details/104905990



/*=========================================*/
/*                                          ringbuffer                                       */
/*=========================================*/
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
    //
    if(lt_ringbuffer.length == lt_ringbuffer.buffer_size)
    {
        return 1;
    }

    //
    *lt_ringbuffer.write =  data;
    lt_ringbuffer.length++;
    #if RingBuffer_DEBUG
    printf("write data:%c\t", *lt_ringbuffer.write);
    printf("write address:%lu\t", (long unsigned int)lt_ringbuffer.write);
    printf("ringbuffer.length:%lu\r\n", (long unsigned int)lt_ringbuffer.length);
    #endif

    //
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

    //
    if(lt_ringbuffer.length == 0) 
    {
        return 1;
    }

    //
    data = *lt_ringbuffer.read;
    lt_ringbuffer.length--;
    #if RingBuffer_DEBUG
    printf("read data:%c\t", *lt_ringbuffer.read);
    printf("read address:%lu\t", (long unsigned int)lt_ringbuffer.read);
    printf("ringbuffer length:%ld\r\n", lt_ringbuffer.length);
    #endif

    //
    lt_ringbuffer.read++;
    if(lt_ringbuffer.read > ringbuffer_end_address)
    {
        lt_ringbuffer.read = lt_ringbuffer.buffer;
    }

    return data;
}




// void lt_init(lt_type_t tpye)
// {

// }

