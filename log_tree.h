#ifndef __LOG_TREE_H
#define __LOG_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "log_tree_def.h"

/* 
 |  编译器必须是C99标准以上
*/

#include <stdio.h>

/*=========== 输入/输出接口 ===========*/

//输入接口
#define lt_print(lt, format, ...)  lt_printf(lt, __FILE__, __func__, __LINE__, format,  ##__VA_ARGS__)

//输出接口
// extern void Console_Output(uint8_t* str, uint32_t len)
// {
//     printf("%.*s\n", len, str);
// }

/*=========== log tree setting over ===========*/ 

#define TX_buffer_size  256
#define RX_buffer_size  124


#define lt_sucess	0
#define lt_Insufficient_buffer	1


#define RingBuffer_DEBUG 0

#if RingBuffer_DEBUG

#endif
// 
#if USE_std
#include <stdlib.h>
#else

#endif








#ifdef __cplusplus
}
#endif


#endif

