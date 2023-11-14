#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "log_tree.h"

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
        // gets(recivce);

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

    // int number = my_printf("!@#$%^%\r\nint:%d\r\nstr:%s\r\nfloat:%f\r\nhex:%x\r\nScientific notation:%e\r\n",
    //                                                      i, str, m, hex, m);
    // printf("input number:%d\r\n", number);
    lt_ringbuffer_pop_str();
}

void list_test()
{
    printf("======list strcut test======\r\n");
    Founction_name_List_t fnl;
    List_Init(&fnl);
    printf("-------------------------------------------\r\n");
    printf("Save founction1\r\n");
    fnl.UpdataList(&fnl.list, "founction1");
    fnl.printList(&fnl.list);
    printf("-------------------------------------------\r\n");
    printf("Save founction2\r\n");
    fnl.UpdataList(&fnl.list, "founction2");
    fnl.printList(&fnl.list);
    printf("-------------------------------------------\r\n");
    printf("Save founction3\r\n");
    fnl.UpdataList(&fnl.list, "founction3");
    fnl.printList(&fnl.list);
    printf("-------------------------------------------\r\n");
    printf("Save founction4\r\n");
    fnl.UpdataList(&fnl.list, "founction4");
    fnl.printList(&fnl.list);
    printf("-------------------------------------------\r\n");
    printf("Save founction5\r\n");
    fnl.UpdataList(&fnl.list, "founction5");
    fnl.printList(&fnl.list);
    printf("-------------------------------------------\r\n");
    printf("Del founction5\r\n");
    fnl.UpdataList(&fnl.list, "founction5");
    fnl.printList(&fnl.list);
    printf("-------------------------------------------\r\n");
    printf("Del founction4\r\n");
    fnl.UpdataList(&fnl.list, "founction4");
    fnl.printList(&fnl.list);
    printf("-------------------------------------------\r\n");
}

void main()
{
    // test_ringbuffer();

    // printf_test();

    // list_test();

    lt_core_t lt = lt_Default_Setting;

    printf("[%s][%s][%d]\r\n", __FILE__, __func__, __LINE__);

    log("SingleRowFormat.Interval_forma:%s", lt.SingleRowFormat.Interval_format);
    log("MultipleRowFormat.FirstTextIndent_format:%s", lt.MultipleRowFormat.FirstTextIndent_format);
    log("MultipleRowFormat.SecondaryTextIndent_format:%s", lt.MultipleRowFormat.SecondaryTextIndent_format);
    log("MultipleRowFormat.SecondarySecondaryTextIndent_format:%s", lt.MultipleRowFormat.SecondarySecondaryTextIndent_format);

}