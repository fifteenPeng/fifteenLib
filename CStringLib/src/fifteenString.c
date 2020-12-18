#include "../inc/fifteenString.h"


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
// int8_t GetStringNumber(uint8_t * Buff,int32_t * NumP,uint16_t * ProcLen ,uint32_t * Magn,uint16_t DataLen)
int8_t FB_GetStringNumber(uint8_t * Buff,GSNStr_t *Ptr,uint16_t BuffLen)
{
    // 判断符号位 +1 正数  +1 负数
    int8_t polarity = 1;
    // int32_t number1 = 0;
    int32_t numbertemp = 0;
    int8_t decimalsflag = 0;
    uint16_t Cnt = 0;      //遍历字符串
    uint16_t Len = 0;

    if(Ptr == NULL)
        return -1;
    
    Ptr->ProcLen = 0;
    Ptr->Magn = 1;
    Ptr->NumP = 0;
    Ptr->DataLen = 0;

    /* 未指定字符长度 */
    if(BuffLen == 0)
        Len = 11;   //数据长度 9 + 符号位1 + 小数点位
    else
        Len = BuffLen;

    //符号处理
    if (Buff[Cnt] == '-')
    {
        Cnt += 1;
        polarity = -1;
    }
    else if (Buff[Cnt] == '+')
    {
        Cnt += 1;
        polarity = 1;
    }
    else if(Buff[Cnt] >= '0' && Buff[Cnt] <= '9')
    {
        /* 无符号 */
        Cnt = 0;
        polarity = 1;
    }
    else
    {
        /* 异常非字符 数据 */
        return -1;
    }
    Ptr->ProcLen += Cnt;


    for (; Cnt < Len && Buff[Cnt] != 0; Cnt++)
    {
        if (Buff[Cnt] >= '0' && Buff[Cnt] <= '9')
        {
            // printf("1 ");
            // 正数部分
            numbertemp = Buff[Cnt] - '0';
            // number1 = number1 * 10 + numbertemp;
            Ptr->NumP = Ptr->NumP * 10 + numbertemp;
            Ptr->ProcLen++;
            Ptr->DataLen++; 
            //小数标志
            if(decimalsflag == 1)
                Ptr->Magn*=10;

            /* 数据长度超限 */
            if(Ptr->DataLen>=9)
                break;
        }
        else if(Buff[Cnt] == '.')
        {
            //其他字符
            if(decimalsflag == 0)
            {
                decimalsflag = 1;
                Ptr->ProcLen++;
                continue;
            }
            else
                break;
        }
        else
        {
            break;
        }
        
    }

    /* 未能处理完 */
    if(Cnt < BuffLen)
        return -1;

    if(Ptr->DataLen>0)
    {
        // Ptr->NumP = number1 * polarity;
        Ptr->NumP *= polarity;
        return 1;
    }

    return -1;
}


#ifdef FIFTEEN_TEST
int8_t FB_GetStringNumber_test(uint8_t flag)
{
    if(flag != 1)
        return 0;

    printf("GetStringNumber_test: \r\n");

    // uint8_t *buff = "12345.10";
    // uint8_t *buff = "-12345.1000";
    // uint8_t *buff = "+12345.1000";
    uint8_t *buff = "+12.345";

    GSNStr_t Number;
    if(FB_GetStringNumber(buff,&Number,0) > 0)
    {
        printf("Number:%ld,ProcLen:%d,magn:%d\r\n",Number.NumP,Number.ProcLen,Number.Magn);
    }
    else
    {
        printf("change fail\r\n");
    }
}

int8_t FB_SetStringNumber_test(uint8_t flag)
{
    if(flag != 1)
        return 0;

    printf("SetStringNumber_test: \r\n");

    // uint8_t *buff = "12345.10";
    // uint8_t *buff = "-12345.1000";
    // uint8_t *buff = "+12345.1000";
    uint8_t buff[100] = {0};

    GSNStr_t Number;
    Number.NumP = -12345;
    Number.Magn = 1000;
    Number.symbol = 1;

    if(FB_SetStringNumber(buff,&Number,0) > 0)
    {
        printf("Number:%s,ProcLen:%d\r\n",buff,Number.ProcLen);
    }
    else
    {
        printf("change fail\r\n");
    }
}
#endif

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
暂无错误
********************************** */
// int8_t GetStringNumber(uint8_t * Buff,int32_t * NumP,uint16_t * ProcLen ,uint32_t * Magn,uint16_t DataLen)
int8_t FB_SetStringNumber(uint8_t * Buff,GSNStr_t *Ptr,uint16_t IntLen)
{

    int32_t number1 = 0;
    int32_t numbertemp = 0;
    int32_t numbertemp1 = 0;

    uint16_t Cnt = 0;      //遍历字符串
    uint16_t Len = 0;
    int8_t i = 0;
    uint8_t * Buff1 = NULL;
    
    uint16_t integerlen = 0;
    uint8_t temp;

    if(Ptr->Magn == 0)
        Ptr->Magn = 1;
    Ptr->ProcLen=0;

    /* 带符号 */
    if(Ptr->symbol == 1)
    {
        if(Ptr->NumP>=0)
            Buff[Ptr->ProcLen] = '+';
        else
            Buff[Ptr->ProcLen] = '-';        
        Ptr->ProcLen=1;
    }

    /* 字符补码，无法输出ASCII */
    if(Ptr->NumP < 0)
        Ptr->NumP = 0 - Ptr->NumP;
    
    Buff1 = &Buff[Ptr->ProcLen];
    /* 整数占几位？，小数占几位？ */


        // numbertemp = Ptr->Magn;
        // for(i=0; numbertemp>1; i++)
        // {
        //     numbertemp/=10;
        //     i++;
        // }
        /* 整数 */
        numbertemp = Ptr->NumP / Ptr->Magn;
        for (i = 0; numbertemp > 0; i++)
        {
            Buff1[i] = numbertemp % 10 + '0';
            numbertemp = numbertemp / 10;
        }

        /* 装载数据 */
        if (i > 0)
        {
            for (integerlen = 0; integerlen < (i / 2); integerlen++)
            {
                temp = Buff1[integerlen];
                Buff1[integerlen] = Buff1[i - integerlen - 1];
                Buff1[i - integerlen - 1] = temp;
            }
            integerlen = i;
        }
        /* 调整数据长度 */
        
        
    if(IntLen != 0)
    {
        if(integerlen < IntLen)
        {
            // printf("IntLen %d,integerlen %d",IntLen,integerlen);
            temp = IntLen - integerlen;

            /* 往后搬运 */
            for(i=integerlen;  i>=0;  i--)
            {
                Buff1[i+temp] = Buff1[i];
            }
            /* 填充 */
            for(i=0;i<temp;i++)
            {
                Buff1[i] = '0';
            }

            integerlen = IntLen;
        }
        else
        {
            /* 大于或等于 数据有效 */
            // return -1;
        }
        //装载小数点
    }
    else
    {
        /* code */
    }

    Ptr->ProcLen+=integerlen;
    if(Ptr->Magn>1)
    {
    /* 小数部分 */
    /* 装载小数点 */
    Buff1[Ptr->ProcLen-1] = '.';
    Ptr->ProcLen += 1;
    Buff1 = &Buff1[Ptr->ProcLen-1];

    numbertemp = Ptr->NumP % Ptr->Magn;
    for (i = 0; numbertemp > 0; i++)
    {
        Buff1[i] = numbertemp % 10 + '0';
        numbertemp = numbertemp / 10;
    }

    /* 装载数据 */
    if (i > 0)
    {
        for (integerlen = 0; integerlen < (i / 2); integerlen++)
        {
            temp = Buff1[integerlen];
            Buff1[integerlen] = Buff1[i - integerlen - 1];
            Buff1[i - integerlen - 1] = temp;
        }
        integerlen = i;
        Ptr->ProcLen+=integerlen;
    }

    }
    else
    {
        /* 转换结束 */
    }
    

    return 1;
}


/*************************PF*************************
描述：转化字符串，转化成浮点数；
输入：需要返回的浮点数指针，需要转化的数据指针,转化字符长度
输出: 转换成功返回 1，转换失败返回 0

失败标志：
遇到非法字符，
*/
char My_AtoF(float *fnumberP,char *Arry, int len)
{

float fnumber1 = 0;

float fnumbertemp = 0;
float fnumberCnt = 0;    //小数点计数器
char decimalpoint = 0; //小数点标记
int polarity = 1;      // 1 正数， -1 负数

int Cnt = 0; //遍历字符串

if (Arry[Cnt] == '-')
{
    //符号判断
    Cnt += 1;
    polarity = -1;
}
else if (Arry[Cnt] == '+')
{
    Cnt += 1;
     polarity = 1;
}

for (; Cnt < len && Arry[Cnt] != 0; Cnt++)
{

    if (Arry[Cnt] == '.')
    {
        if (decimalpoint == 0)
        {
            decimalpoint = 1;
            fnumberCnt = 1.0;
            continue;
        }
        else
        {
            return 0; //遇到多个小数点
        }
    }
    else if (Arry[Cnt] >= '0' && Arry[Cnt] <= '9')
        {
            // 正数部分
            if (decimalpoint == 0)
            {
                fnumbertemp = Arry[Cnt] - '0';
                fnumber1 = fnumber1 * 10 + fnumbertemp;
            }
            // 小数部分
            else
            {
                /* code */
                fnumbertemp = Arry[Cnt] - '0';
                fnumberCnt *= 10.0;
                fnumbertemp = fnumbertemp / fnumberCnt;
                fnumber1 = fnumber1 + fnumbertemp;
            }
        }
    else
    {
        return 0; //其他字符
    }
}

*fnumberP = fnumber1 * polarity;
return 1;
}

/*
*************************PF*************************
描述：转化字符串，转化成IP地址
输入：接收结果的IP地址指针，需要转化的数据指针,字符长度
输出: 转换成功返回 1，转换失败返回 0

失败标志：
遇到非法字符，
*/
int8_t My_AtoIP(uint8_t *IPaddr,int8_t *Arry, int len)
{
//192.168.1.12
int32_t number[4] = {0};
int32_t numbertemp = 0;


int8_t Cnt = 0; //遍历字符串
int8_t IPcnt = 0;//当前为IP哪一段；

for (Cnt=0; Cnt < len && Arry[Cnt] != 0; Cnt++)
{

    if (Arry[Cnt] == '.')
    {
        if (IPcnt < 3)
        {
            IPcnt++;
            continue;
        }
        else
        {
            return 0; //遇到多个小数点
        }
    }
    else if (Arry[Cnt] >= '0' && Arry[Cnt] <= '9')
        {
            // 正数部分
            numbertemp = Arry[Cnt] - '0';
            number[IPcnt] = number[IPcnt] * 10 + numbertemp;

            if(number[IPcnt] <= 255)
                IPaddr[IPcnt] = number[IPcnt];
            else
                return 0;

        }
    else
    {
        return 0; //其他字符
    }
}

return 1;
}