#include "ParaData.h"

/* *******************************
参数结构体初始化,给参数赋初值，常量
********************************** */
int8_t FB_ParaInit(void)
{

}

/* *****************************
读写权限
返回：-1不允许写，1允许写
******************************* */
int8_t FB_ISWrite(FBPara_t * Ptr)
{
    if(Ptr->Attr & FB_ATTR_WO)
        return 1;
    else
        return -1;    
}

/* *****************************
上下限
输入：  FBPara_t 处理数据结构体指针
        上下限指针
        传入上下限数据的数据类型,便于准确取出数据比较。

返回：-1超限， 1未超限
******************************* */
int8_t FB_ISUPDOWN(FBPara_t * Ptr,void* NowData,eFBDaType Type)
{
    // 统一数据 保证比较的 唯一性；
    int64_t DownD = 0;
    int64_t UpD = 0;
    int64_t NowD = 0;

    // 无符号        
    switch (Type)
    {
    case FBU8_t:
        NowD = *(uint8_t *)NowData;
        break;
    case FBS8_t:
        NowD = *(int8_t *)NowData;
        break;
    case FBU16_t:
        NowD = *(uint16_t *)NowData;
        break;
    case FBS16_t:
        NowD = *(int16_t *)NowData;
        break;
    case FBU32_t:
        NowD = *(uint32_t *)NowData;
        break;
    case FBS32_t:
        NowD = *(int32_t *)NowData;
        break;                           
    default:
        break;
    }


    if(Ptr->Attr & FB_ATTR_SIG)
    {
        // 有符号
        // 取出位数
        if(Ptr->Attr & FB_ATTR_8 )
        {
            UpD = *(int8_t *)Ptr->UplimitP;
            DownD = *(int8_t *)Ptr->DownlimitP;
        }
        else if(Ptr->Attr & FB_ATTR_16)
        {
            UpD = *(int16_t *)Ptr->UplimitP;
            DownD = *(int16_t *)Ptr->DownlimitP;
        }
        else if(Ptr->Attr & FB_ATTR_32)
        {
            UpD = *(int32_t *)Ptr->UplimitP;
            DownD = *(int32_t *)Ptr->DownlimitP;
        }
    }
    else
    {

        if(Ptr->Attr & FB_ATTR_8 )
        {
            UpD = *(uint8_t *)Ptr->UplimitP;
            DownD = *(uint8_t *)Ptr->DownlimitP;
        }
        else if(Ptr->Attr & FB_ATTR_16)
        {
            UpD = *(uint16_t *)Ptr->UplimitP;
            DownD = *(uint16_t *)Ptr->DownlimitP;
        }
        else if(Ptr->Attr & FB_ATTR_32)
        {
            UpD = *(uint32_t *)Ptr->UplimitP;
            DownD = *(uint32_t *)Ptr->DownlimitP;
        }

    }
    
    if(NowD > UpD || NowD < DownD)
    {
        return -1;
    }
    
    return 1;
}

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