#include "stdio.h"
#include "log_tree_def.h"

#define log(format, ...)   printf(format"\r\n", ##__VA_ARGS__)

void main()
{
    log_tree_ringbuffer test;
    // memset(test.ringbuffer.buffer[0], 0, sizeof(test.ringbuffer.buffer));
    test.ringbuffer.buffer_start = &test.ringbuffer.buffer[0];
    test.ringbuffer.buffer_end = &test.ringbuffer.buffer[buffer_size-1];
    
    //初始化
    test.read_p = test.ringbuffer.buffer_start;
    test.write_p = test.ringbuffer.buffer_start;

    log("test.read_p:%ld\ttest.write_p:%ld", test.read_p, test.write_p);
    log("test.ringbuffer.buffer[0]:%ld\ttest.ringbuffer.buffer[999]:%ld",&test.ringbuffer.buffer[0], &test.ringbuffer.buffer[999] );
    log("test.ringbuffer.buffer size:%ld", &test.ringbuffer.buffer[999] - &test.ringbuffer.buffer[0] + 1);







    // unsigned char asf, sdcv;
    // asf = "c";
    // lt_ringbuffer_push(asf);
    // sdcv = lt_ringbuffer_pop();
    // printf("sdcv:%d\r\n", sdcv);
}