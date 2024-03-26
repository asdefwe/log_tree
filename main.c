#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "log_tree.h"

#include "a.h"

#define log(format, ...)   printf(format"\r\n", ##__VA_ARGS__)

lt_core_t lt = lt_Default_Setting();


void functionD()
{
    lt_print(&lt, "funcD is running\r\n");
    lt_print(&lt, "funcD is over\r\n");
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
    printA();
    lt_print(&lt, "funcB is run over\r\n");
}

void functionA()
{
    lt_print(&lt, "funcA is running, will run func B\r\n");
    functionB();
}

void main()
{
    List_Init(&lt.fnl);
    
    printf("======================\r\n");
    lt_print(&lt, "log tree test is running\r\n");
    functionA();
    lt_print(&lt, "print test\r\n");
    lt_print(&lt, "log tree test over\r\n");
    printf("======================\r\n\r\n");

    lg_Queue_t RB;
    uint8_t str[1000] = {0};
    uint8_t str1[] = "abcdefg123()*&...$#@0abd345/*-+/*+";
    uint8_t str2[] = "123----------74891561*)(^&*$%^@#$!@-";

    lt_RB_Init(&RB, 60);
    int i;

    i = RB_Write_String(&RB, str1, 34);
    printf("RB return %d Length:%d\r\n", i, RB.Length);
    i = RB_Write_String(&RB, str2, 36);
    printf("RB return %d Length:%d\r\n", i, RB.Length);

    i = RB_Read_String(&RB, str, 34);
    printf("RB return %d Length:%d\r\n", i, RB.Length);

    printf("%d %s\r\n", strlen(str), str);
    memset(str, 0, 1000);

    i = RB_Write_String(&RB, str1, 34);
    printf("RB return %d Length:%d\r\n", i, RB.Length);
    i = RB_Read_String(&RB, str, 20);
    printf("RB return %d Length:%d\r\n", i, RB.Length);
    printf("%d %s\r\n", strlen(str), str);
    memset(str, 0, 1000);
    
    i = RB_Write_String(&RB, str2, 46);
    printf("RB return %d Length:%d\r\n", i, RB.Length);
    i = RB_Read_String(&RB, str, 60);
    printf("RB return %d Length:%d\r\n", i, RB.Length);

    printf("%d %s\r\n", strlen(str), str);

}





