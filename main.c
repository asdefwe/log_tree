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
    printf("======list strcut test======\r\n");
    lg_list_t   List;

    vListInitialise(&List);

    lg_ListItem_t * Item1 = calloc(3*4, 1);

    uint8_t str1[] = "Founction";
    uint8_t CharNumber = sizeof(str1);
    printf("str1 size:%d\r\n", CharNumber);

    // 为列表中的数据申请空间
    Item1->pvOwner = calloc(CharNumber, sizeof(uint8_t));
    memcpy(Item1->pvOwner, str1, CharNumber);
    printf("Item1->pvOwner:%s\r\n", (char*)Item1->pvOwner);
    printf("----------------------------\r\n");

    vListInsertEnd(&List, Item1);

    uint8_t Number = 0;
    lg_ListItem_t * pxIterator = NULL;
    lg_ListItem_t * const ListEndItem = (void*)List.ListEnd.pxPrevious;

    printf("List NumberOfItems:%d\r\n", List.NumberOfItems);
    for(pxIterator = ListEndItem; Number < List.NumberOfItems; pxIterator = (void*)pxIterator->pxPrevious)
    {
        Number++;
        printf("[%d][%s]\r\n",Number ,(char*)(pxIterator->pvOwner));
    }
    printf("============================\r\n");

    printf("list_test \r\n");
    Founction_name_List_t fnl;
    List_Init(&fnl);

    fnl.UpdataList(&fnl.list, "founction1");
    printf("fnl.list.NumberOfItems:%d\r\n", fnl.list.NumberOfItems);
    fnl.printList(&fnl.list);

    fnl.UpdataList(&fnl.list, "founction2");
    printf("fnl.list.NumberOfItems:%d\r\n", fnl.list.NumberOfItems);
    fnl.printList(&fnl.list);

    fnl.UpdataList(&fnl.list, "founction3");
    printf("fnl.list.NumberOfItems:%d\r\n", fnl.list.NumberOfItems);
    fnl.printList(&fnl.list);

    fnl.UpdataList(&fnl.list, "founction2");
    printf("fnl.list.NumberOfItems:%d\r\n", fnl.list.NumberOfItems);
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