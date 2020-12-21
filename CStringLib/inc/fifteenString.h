#ifndef _FIFTEENSTRING_H_
#define _FIFTEENSTRING_H_
/* *****************************************************************
作者：fifteenpeng
描述：本库用于日常处理字符文件，提取重要数据。处理ASCII命令等信息
******************************************************************** */
#include "../inc/DataType.h"

typedef struct GSNStr
{
     int32_t NumP;
    // int64_t NumP;
    uint16_t ProcLen;
    uint16_t DataLen;
    int32_t Magn;
    /* 是否带符号输出 */
    uint8_t symbol;
    /* data */
}GSNStr_t;

/* *******************************
函数名：
描述：输入字符串，提取出数值返回值均为整数，皆为带符号处理
    如果是小数，则放大为整数接收

输入：
    * buff    需要处理的字符串指针
    * GSNStr_t 相关数据信息结构体
    DataLen 指定处理数据长度，为0时则直接处理
输出：
返回：-1 提取失败  1提取成功

错误描述：
1.指定数据长度时，遇到非数字数据
2.处理数据超过int32_t数值
3.
********************************** */
int8_t FB_GetStringNumber(uint8_t * Buff,GSNStr_t *Ptr,uint16_t BuffLen);
/* *******************************
函数名：
描述：设置返回的字符串长度

输入：
    * buff    输出的数组
    * GSNStr_t 相关数据信息结构体
    IntLen  整数的所占的位数
输出：
返回：-1 转换失败  1转换成功

错误描述：
********************************** */
// int8_t GetStringNumber(uint8_t * Buff,int32_t * NumP,uint16_t * ProcLen ,uint32_t * Magn,uint16_t DataLen)
int8_t FB_SetStringNumber(uint8_t * Buff,GSNStr_t *Ptr,uint16_t IntLen);

/* *******************************
函数名：
描述：比较指定的字符串，匹配说明，保证数据的不越界
    '*' 任意字符 
    '#' 数字字符 '0' '9'
    '%' 符号字符 '+' '-'
输入：
    * buff1  数组
    * buff2  数组2
    
输出：
返回：-1 转换失败  1转换成功

错误描述：
********************************** */
int8_t FB_StrCmp(int8_t* buff1,int8_t* buff2);


#ifdef FIFTEEN_TEST
int8_t FB_GetStringNumber_test(uint8_t flag);
int8_t FB_SetStringNumber_test(uint8_t flag);
int8_t FB_StrCmp_test(uint8_t flag);
#endif

#endif