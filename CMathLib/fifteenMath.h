#ifndef _FIFTEEN_MATH_H_
#define _FIFTEEN_MATH_H_
/* *****************************************************************
作者：fifteenpeng
描述：本库用于常用数学曲线算法设计，如一次曲线，二次曲线
数据类型：单精度浮点型
******************************************************************** */
#include "../inc/DataType.h"
#include "../inc/Config.h"

/* 斜率原始数据长度 */
#define MAX_LINEAR_COUNT  50

/* 一次函数 linear function*/
/* 一次函数 相关元素  y = k*x + b */

typedef struct linearKeyStr
{
    float X;    /* 需要存储原始的 X 值，用于查找当前处于哪一段 */
    float K;
    float B;
}linearKey_t;

typedef struct FB_LinearStr{
    // 有效数据段
    int16_t Num;
    linearKey_t *Key;
}FB_Linear_t;


/* **************
* 数据初始化
 ******************/
void FB_Math_Init(void);


/* 
计算斜率函数：
输入：接收数据段指针，数据长度,数组指针float* X  数组指针float* X
输出：

返回：0失败  1成功

失败原因：两个相邻的X不允许相等；
 */
int8_t FB_SetValueLinear(FB_Linear_t* Ptr,int16_t Len,float* X, float* Y);


/* **************************
*求值函数：

输入：一次函数关键量指针，数据段长度，X值，
输出：Y值指针
返回：0 失败   1成功

排序类型：递增 递减
递增：
X < x0 属于K0 段 x0<= X <=x1 属于K0 段 x1<= X <=x2 属于K1 段  X > x2 属于K1段

递减：
X > x0 属于K0 段 x0>= X >=x1 属于K0 段 x1>= X >=x2 属于K1 段  X < x2 属于K1段

***************************** */
int8_t FB_GetValueLinear(FB_Linear_t* Ptr,int16_t Len,float X, float * Y);




/* 二次函数 quadratic function */

#ifdef FIFTEEN_TEST
void fifteenMath_test(void);
#endif

#endif