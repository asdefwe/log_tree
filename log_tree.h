#ifndef __LOG_TREE_H
#define __LOG_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log_tree_def.h"

/* 
 |  编译器必须是C99标准以上
*/


/*=========== 输入/输出接口 ===========*/

//输入接口
int lt_printf(lt_core_t* lt, const uint8_t* flie, const uint8_t* func, uint32_t line, uint8_t *format, ...);
#define lt_print(lt, format, ...)  lt_printf(lt, __FILE__, __func__, __LINE__, format,  ##__VA_ARGS__)

/* 输出接口示例
 | 
*/
#include <stdio.h>

#define Console_Output(str, len)    {            \
    printf("%.*s", len, str);                     \
}

/*=========== log tree setting over ===========*/ 

#define TX_buffer_size  256
#define RX_buffer_size  124


#define lt_sucess	0
#define lt_Insufficient_buffer	1


// 
#if USE_std
#include <stdlib.h>
#else

#endif



uint32_t List_Init(Founction_name_List_t* fnl);

uint32_t lt_RB_Init(lg_Queue_t *RB_handle, uint32_t buffer_size);

uint32_t lt_RB_Del(lg_Queue_t *RB_handle);

uint32_t RB_Write_String(lg_Queue_t *RB_handle, uint8_t *input_addr, uint32_t write_Length);

uint8_t RB_Read_String(lg_Queue_t *RB_handle, uint8_t *output_addr, uint32_t read_Length);



#ifdef __cplusplus
}
#endif


#endif


