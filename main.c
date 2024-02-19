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

}





