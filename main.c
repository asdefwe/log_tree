#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "log_tree.h"

#include <sys/wait.h>

#define log(format, ...)   printf(format"\r\n", ##__VA_ARGS__)

lt_core_t lt = lt_Default_Setting;

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

#define fnl_test    lt.fnl

    Founction_name_List_t fnl1;
    List_Init(&fnl_test);
    printf("-------------------------------------------\r\n");
    printf("Save founction1\r\n");
    fnl_test.UpdataList(&fnl_test.list, "asdgv");
    fnl_test.printList(&fnl_test.list);
    printf("-------------------------------------------\r\n");
    printf("Save founction2\r\n");
    fnl_test.UpdataList(&fnl_test.list, "15609");
    fnl_test.printList(&fnl_test.list);
    printf("-------------------------------------------\r\n");
    printf("Save founction3\r\n");
    fnl_test.UpdataList(&fnl_test.list, "[tyn]");
    fnl_test.printList(&fnl_test.list);
    printf("-------------------------------------------\r\n");
    printf("Save founction4\r\n");
    fnl_test.UpdataList(&fnl_test.list, "vb456");
    fnl_test.printList(&fnl_test.list);
    printf("-------------------------------------------\r\n");
    printf("Save founction5\r\n");
    fnl_test.UpdataList(&fnl_test.list, "-+*/+");
    fnl_test.printList(&fnl_test.list);
    printf("-------------------------------------------\r\n");
    printf("Save founction6\r\n");
    fnl_test.UpdataList(&fnl_test.list, "#!$*^");
    fnl_test.printList(&fnl_test.list);
    printf("-------------------------------------------\r\n");
    printf("Save founction7\r\n");
    fnl_test.UpdataList(&fnl_test.list, "dfb0b");
    fnl_test.printList(&fnl_test.list);
    printf("-------------------------------------------\r\n");
    printf("Del until founction6\r\n");
    fnl_test.UpdataList(&fnl_test.list, "#!$*^");
    fnl_test.printList(&fnl_test.list);
    printf("-------------------------------------------\r\n");
    printf("Del until founction6\r\n");
    fnl_test.UpdataList(&fnl_test.list, "#!$*^");
    fnl_test.printList(&fnl_test.list);
    printf("-------------------------------------------\r\n");
    printf("Del until founction3\r\n");
    fnl_test.UpdataList(&fnl_test.list, "[tyn]");
    fnl_test.printList(&fnl_test.list);
    printf("-------------------------------------------\r\n");
}

void functionC()
{
    lt_printf(&lt, __FILE__, __func__, __LINE__, "function is run\r\n\r\n");
}

void functionB()
{
    lt_printf(&lt, __FILE__, __func__, __LINE__, "func is running\r\n\r\n");
    functionC();
}

void functionA()
{
    lt_printf(&lt, __FILE__, __func__, __LINE__, "function is running\r\n\r\n");
    functionB();
}

void main()
{
    // test_ringbuffer();

    // printf_test();

    // list_test();


    memset(&lt, 0, sizeof(lt));
    List_Init(&lt.fnl);

    printf("[%s][%s][%d]\r\n", __FILE__, __func__, __LINE__);
    printf("======================\r\n");

    log("SingleRowFormat.Interval_forma:%s", lt.SingleRowFormat.Interval_format);
    log("MultipleRowFormat.FirstTextIndent_format:%s", lt.MultipleRowFormat.FirstTextIndent_format);
    log("MultipleRowFormat.SecondaryTextIndent_format:%s", lt.MultipleRowFormat.SecondaryTextIndent_format);
    log("MultipleRowFormat.SecondarySecondaryTextIndent_format:%s", lt.MultipleRowFormat.SecondarySecondaryTextIndent_format);

    printf("======================\r\n");
    lt_printf(&lt, __FILE__, __func__, __LINE__, "is running\r\n\r\n");
    functionA();

}







