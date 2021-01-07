#include "../inc/DataType.h"
#include "../inc/Config.h"

#ifdef FIFTEEN_TEST

#include "stdio.h"
#include "fifteenMath.h"


/* 编译指令：$  gcc main.c fifteenMath.c -o a */
int main(void)
{
    uint8_t ch;
    fifteenMath_test();
    scanf("%c",&ch);
    return 1;
}

#endif