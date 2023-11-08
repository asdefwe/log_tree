#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "log_tree_def.h"

#include <sys/wait.h>

#define log(format, ...)   printf(format"\r\n", ##__VA_ARGS__)

void test_ringbuffer()
{
    uint8_t recivce[4];
    uint8_t buffer[3];
    int time = 0;
    lt_ringbuffer_Init(3);

    while(1)
    {
        gets(recivce);

        for(int i=0;i<3;i++)
        {
            lt_ringbuffer_push(recivce[i]);
        }

        memset(buffer, 0, 4);
        for(int i=0;i<3;i++)
        {
            buffer[i] = lt_ringbuffer_pop();
        }
        log("RingBuffer char:%s", buffer);

    }

}


void printf_test()
{
    lt_ringbuffer_Init(300);

    int i = 600;
    char str[] = "evwdv4856ty?123243";
    float m = 3.1415926;
    int hex = 0x55FCBD;

    int number = my_printf("!@#$%^%\r\nint:%d\r\nstr:%s\r\nfloat:%f\r\nhex:%x\r\nScientific notation:%e\r\n",
                                                         i, str, m, hex, m);
    printf("input number:%d\r\n", number);
    lt_ringbuffer_pop_str();
}


void list_test()
{
    printf("list_test \r\n");
    Founction_name_List_t fnl;
    List_Init(&fnl);

    fnl.UpdataList(&fnl.list, "founction1");
    fnl.printList(&fnl.list);

    fnl.UpdataList(&fnl.list, "founction2");
    fnl.printList(&fnl.list);

    fnl.UpdataList(&fnl.list, "founction3");
    fnl.printList(&fnl.list);

    fnl.UpdataList(&fnl.list, "founction2");
    fnl.printList(&fnl.list);
}

void main()
{
    // test_ringbuffer();

    // printf_test();

    list_test();

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