#ifndef _PARADATA_H_
#define _PARADATA_H_
/* *****************************************************************
作者：fifteenpeng
描述：本库用于参数的管理，如设置时的上下限限制，是否允许读写限制。
适用于参数较多场合

本函数操作对象，不可使用强制对齐
******************************************************************** */
#include "../inc/DataType.h"

/* 宏定义 */
/* 
BIT 0   读
BIT 1   写
BIT 2   保留
BIT 3   保留
BIT 4   类型  8位  16位  32 位 64位
BIT 5   类型
BIT 6   符号  0 unsigned  1 signed
 */
#define ATTR_RO 0x01
#define ATTR_WO 0x02
#define ATTR_RW (ATTR_RO | ATTR_RO)

// 0B 000
// 0B 001
// 0B 010
// 0B 011

// 0B 100
// 0B 101
// 0B 110
// 0B 111

#define ATTR_8  (0x00 << 4)
#define ATTR_16 (0x01 << 4)
#define ATTR_32 (0x02 << 4)
#define ATTR_64 (0x03 << 4)
#define ATTR_SIG (0x01 << 6)
//end

/* 参数结构体,指针 */
typedef FBParaStr{
    uint32_t Attr;  /* 参数属性，用于管理 当前数据的相关信息*/
    void * Data;
    void * uplimit;
    void * Downlimit;
    void (* Write)(); /* 装载操作 写函数 */
    void (* Read)(); /* 装载操作 读函数 */
    void (* Option)(); /* 装载操作 操作函数，便于回调*/
}FBParaStr_t;

/* *******************************
参数结构体初始化,给参数赋初值，常量
********************************** */
int8_t FB_ParaInit(void);

/* *****************************
读写权限
******************************* */
int8_t FB_ISRW(FBParaStr_t * Ptr);

/* *****************************
上下限
******************************* */
int8_t FB_ISUPDOWN(FBParaStr_t * Ptr);


#endif