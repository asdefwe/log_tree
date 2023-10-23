#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "log_tree_def.h"

#define log(format, ...)   printf(format"\r\n", ##__VA_ARGS__)

void test_ringbuffer()
{
    char str[100];

    while(1)
    {
        scanf("%s", str);
        lt_ringbuffer_push(str);
        char casdv = lt_ringbuffer_pop();
        printf("%s\r\n", casdv);

    }

}


void main()
{
    test_ringbuffer();


    // char* test1 = (uint8_t*)malloc(1000);
    // char data1[10] = "abcdefg";
    // char data2[10] = "hijklmn";
    // strcpy(test1, data1);
    // strcpy(test1+strlen(data1)+1, data2);
    // log("malloc address:0x%x", test1);
    // log("test1:%s\ttest1:%d", test1, strlen(data1));
    // log("test1:%s\ttest1:%d", data2, strlen(data2));
    // log("malloc end address:0x%x", test1+1000);
    // free(test1);
    // log("====== free test ======");
    // log("test1:%s\ttest1:%d", test1, strlen(data1));

  
}