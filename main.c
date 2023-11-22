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

void functionD()
{
    lt_printf(&lt, __FILE__, __func__, __LINE__, "funcD is running\r\n");
}

void functionC()
{
    lt_printf(&lt, __FILE__, __func__, __LINE__, "funcC is running, will run func D\r\n");
    functionD();
}

void functionB()
{
    lt_printf(&lt, __FILE__, __func__, __LINE__, "funcB is running, will run func C\r\n");
    functionC();
    lt_printf(&lt, __FILE__, __func__, __LINE__, "funcB is run 123456\r\n");
    lt_printf(&lt, __FILE__, __func__, __LINE__, "funcB is run over\r\n");
}

void functionA()
{
    lt_printf(&lt, __FILE__, __func__, __LINE__, "funcA is running, will run func B\r\n");
    functionB();
}

void main()
{
    // test_ringbuffer();

    // printf_test();

    // list_test();
   
    List_Init(&lt.fnl);

    printf("[%s][%s][%d]\r\n", __FILE__, __func__, __LINE__);
    printf("======================\r\n");

    log("lt.SingleRowFormat.filename:%d", lt.SingleRowFormat.filename);
    log("lt.SingleRowFormat.function:%d", lt.SingleRowFormat.function);
    log("lt.SingleRowFormat.line:%d", lt.SingleRowFormat.line);
    log("lt.SingleRowFormat.Interval_format:%s", lt.SingleRowFormat.Interval_format);
    log("SingleRowFormat.Interval_forma:%s", lt.SingleRowFormat.Interval_format);
    log("MultipleRowFormat.FirstTextIndent_format:%s", lt.MultipleRowFormat.FirstTextIndent_format);
    log("MultipleRowFormat.SecondaryTextIndent1_format:%s", lt.MultipleRowFormat.SecondaryTextIndent1_format);
    log("MultipleRowFormat.SecondaryTextIndent2_format:%s", lt.MultipleRowFormat.SecondaryTextIndent2_format);
    log("MultipleRowFormat.SecondaryTextIndent_length:%d", lt.MultipleRowFormat.SecondaryTextIndent2_length);
    log("MultipleRowFormat.SecondarySecondaryTextIndent_format:%s", lt.MultipleRowFormat.SecondarySecondaryTextIndent_format);
    
    printf("======================\r\n");
    lt_printf(&lt, __FILE__, __func__, __LINE__, "log tree test is running\r\n");
    functionA();

    lt_printf(&lt, __FILE__, __func__, __LINE__, "log tree test over\r\n");

    // lt.fnl.printList(&lt.fnl.list);
}







