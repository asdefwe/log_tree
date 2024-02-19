#include "a.h"
#include "log_tree.h"



extern lt_core_t lt;



void printA()
{
    lt_print(&lt, "file A is running\r\n");
    lt_print(&lt, "file A is over\r\n");

}