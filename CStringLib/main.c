#include "../inc/DataType.h"
#include "../inc/Config.h"

#ifdef FIFTEEN_TEST

#include "stdio.h"
#include "fifteenString.h"


/* 编译指令：$ gcc main.c ./src/fifteenString.c -o c */
int main(void)
{

    // int8_t a = 100;
    // int8_t b = -100;
    
    // int64_t c = 0;
    // uint64_t d = 0;

    // c = a;
    // d = b;
    // printf("a:%x,b:%x,c:%x,d:%x \r\n",a,b,c,d);


    FB_GetStringNumber_test(1);
    FB_SetStringNumber_test(1);
    FB_StrCmp_test(1);

    return 1;
}

#endif