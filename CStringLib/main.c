#include "stdio.h"
#include "./inc/fifteenString.h"
#include "./inc/DataType.h"

/* 编译指令：$ gcc main.c ./src/fifteenString.c -o c */
int main(void)
{
    FB_GetStringNumber_test(1);
    FB_SetStringNumber_test(1);
    FB_StrCmp_test(1);
    return 1;
}