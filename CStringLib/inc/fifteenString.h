#ifndef _FIFTEENSTRING_H_
#define _FIFTEENSTRING_H_
/* *****************************************************************
作者：fifteenpeng
描述：本库用于日常处理字符文件，提取重要数据。处理ASCII命令等信息
******************************************************************** */


#include "../inc/DataType.h"


/* *******************************
函数名：
描述：输入字符串，提取出数值返回值均为整数
输入：
输出：
返回：-1 提取失败  1提取成功
********************************** */
int8_t GetStringNumber(uint8_t * cp,void * NumP,uint8_t symb,uint8_t NumTpye);

#endif