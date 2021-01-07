#ifndef _PARADATA_H_
#define _PARADATA_H_
/* *****************************************************************
作者：fifteenpeng
描述：本库用于参数的管理，如设置时的上下限限制，是否允许读写限制，读写操作接口。
适用于参数较多场合

本函数操作对象，不可使用强制对齐,否则指针获取访问数据异常。

版本：V1.0 
    暂时不支持64位数据
******************************************************************** */
#include "../inc/DataType.h"

// 类型枚举选择
enum eFBDaType{FBU8_t,FBU16_t,FBU32_t,FBU64_t,FBS8_t,FBS16_t,FBS32_t,FBS64_t};
/* 宏定义 */
/* 
BIT 0   读
BIT 1   写
BIT 2   保留
BIT 3   保留    
BIT 4   类型    8
BIT 5   类型    16
BIT 6   类型    32
BIT 7   符号    0 unsigned  1 signed
 */
#define FB_ATTR_RO     (0x00000001)
#define FB_ATTR_WO     (0x00000002)
#define FB_ATTR_RW     (ATTR_RO | ATTR_WO)

/* 占4bit */
#define FB_ATTR_8      (0x00000010)
#define FB_ATTR_16     (0x00000020)
#define FB_ATTR_32     (0x00000040)
#define FB_ATTR_SIG    (0x00000080)
//end

/* 参数结构体,指针 */
typedef FBParaStr{
    uint16_t ID;    /* 参数下标，便于查找 */
    uint32_t Attr;  /* 参数属性，用于管理 当前数据的相关信息*/
    void * DataP;    /* 数据指针 有些数据无法对齐，则通过读函数获取*/
    void * UplimitP;
    void * DownlimitP;
    int8_t (* Write)(FBPara_t *Ptr,void *DataP,eFBDaType Type);   /* 装载操作 写函数 */
    int8_t (* Read)(FBPara_t *Ptr,void *DataP,eFBDaType Type);    /* 装载操作 读函数 */
    int8_t (* Option)();  /* 装载操作 操作函数，便于回调*/
}FBPara_t;

/*参数数据多时，使用双向链表进行管理，需要编码*/
typedef FBParaLinkStr{
    FBPara_t *p;

    FBParaLink_t *prior;
    FBParaLink_t *next;

}FBParaLink_t;

/* *******************************
参数结构体初始化,给参数赋初值，常量
********************************** */
int8_t FB_ParaInit(void);

/* *****************************
读写权限
返回：-1不允许写，1允许写
******************************* */
int8_t FB_ISWrite(FBPara_t * Ptr);

/* *****************************
上下限
输入：  FBPara_t 处理数据结构体指针
        新数据指针
        传入上下限数据的数据类型,便于准确取出数据比较。

返回：-1超限， 1未超限
******************************* */
int8_t FB_ISUPDOWN(FBPara_t * Ptr,void* NowData,eFBDaType Type)

/****************************
 * 读函数
 * 输入：FBPara_t 处理数据结构体
 *      接收数据的指针
 *      接收数据指针的数据类型
 *      
 * 返回：1成功，-1失败
 * **************************/
int8_t FB_ParaRead(FBPara_t *Ptr,void *DataP,eFBDaType Type);

/****************************
 * 读函数
 * 输入：FBPara_t 处理数据结构体
 *      接收数据的指针
 *      接收数据指针的数据类型
 *      
 * 返回：1成功，-1失败
 * **************************/
int8_t FB_ParaWrite(FBPara_t *Ptr,void *DataP,eFBDaType Type);


/* 操作函数保留，用于其他特殊的的操作，形参不定 */
int8_t ParaOption(void);

#endif