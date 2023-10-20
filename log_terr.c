#include "log_tree_def.h"
#include "log_tree.h"
 


/*=========================================*/
/*                                          ringbuffer                                       */
/*=========================================*/

log_tree_ringbuffer lt_ringbuffer;

static void lt_ringbuffer_Init()
{
    //记录ringbuffer的开始和结束地址
    lt_ringbuffer.ringbuffer.buffer_start = &lt_ringbuffer.ringbuffer.buffer[0];
    lt_ringbuffer.ringbuffer.buffer_end = &lt_ringbuffer.ringbuffer.buffer[buffer_size-1];
    
    //初始化
    lt_ringbuffer.read_p = lt_ringbuffer.ringbuffer.buffer_start;
    lt_ringbuffer.write_p = lt_ringbuffer.ringbuffer.buffer_start;
}

lt_err_t lt_ringbuffer_push(uint8_t* data)
{
    uint8_t len;

    len = strlen(data);
    if(lt_ringbuffer.write_p >lt_ringbuffer.read_p)
    {
        if(len > (lt_ringbuffer.read_p - lt_ringbuffer.ringbuffer.buffer_start) + 
                       (lt_ringbuffer.ringbuffer.buffer_end - lt_ringbuffer.write_p))
        return lt_Insufficient_buffer;
    }
    else if(lt_ringbuffer.read_p > lt_ringbuffer.write_p)
    {
        if(len > (lt_ringbuffer.read_p - lt_ringbuffer.write_p))
        return lt_Insufficient_buffer;
    }

    *lt_ringbuffer.write_p =  data;
    lt_ringbuffer.write_p++;

    if(lt_ringbuffer.write_p == lt_ringbuffer.ringbuffer.buffer_end)
    {
        lt_ringbuffer.write_p = lt_ringbuffer.ringbuffer.buffer_start;
    }
    return lt_sucess;
}

uint8_t lt_ringbuffer_pop(void)
{
    uint8_t data;
    uint8_t len;

    len = strlen(data);
    if(lt_ringbuffer.write_p >lt_ringbuffer.read_p)
    {
        if(len > (lt_ringbuffer.read_p - lt_ringbuffer.ringbuffer.buffer_start) + 
                       (lt_ringbuffer.ringbuffer.buffer_end - lt_ringbuffer.write_p))
        return lt_Insufficient_buffer;
    }
    else if(lt_ringbuffer.read_p > lt_ringbuffer.write_p)
    {
        if(len > (lt_ringbuffer.read_p - lt_ringbuffer.write_p))
        return lt_Insufficient_buffer;
    }

    data = *lt_ringbuffer.read_p;
    lt_ringbuffer.read_p++;

    if(lt_ringbuffer.read_p == lt_ringbuffer.ringbuffer.buffer_end)
    {
        lt_ringbuffer.read_p = lt_ringbuffer.ringbuffer.buffer_start;
    }

    return data;
}




// void lt_init(lt_type_t tpye)
// {

// }

