#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "log_tree.h"

#define log(format, ...)   printf(format"\r\n", ##__VA_ARGS__)

lt_core_t lt = lt_Default_Setting();


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
    lt_print(&lt, "funcD is running\r\n");
}

void functionC()
{
    lt_print(&lt, "funcC is running, will run func D\r\n");
    functionD();
}

void functionB()
{
    lt_print(&lt, "funcB is running, will run func C\r\n");
    functionC();
    lt_print(&lt, "funcB is run 123456\r\n");
    lt_print(&lt, "funcB is run over\r\n");
}

void functionA()
{
    lt_print(&lt, "funcA is running, will run func B\r\n");
    functionB();
}

void main()
{
    // list_test();
   
    List_Init(&lt.fnl);
    
    printf("======================\r\n");
    lt_print(&lt, "log tree test is running\r\n");
    functionA();
    lt_print(&lt, "print test\r\n");
    lt_print(&lt, "log tree test over\r\n");

}







