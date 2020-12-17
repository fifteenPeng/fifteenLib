#include "../inc/fifteenString.h"



/**
 * ******PF*********************
 * 输入带小数点的字符串
 * 字符串转换成数据,小数点右移动多少位。
 * */

int32_t FS_AtoF(char *Arry,uint8_t pointlen)
{
    int8_t i = 0;
    int8_t j = 0;
    int32_t data = 0;
    char * Point = 0;

    /* 正数 */
    for(i = 0; (Arry[i]>='0'&& Arry[i]<='9'); i++)
    {
        data = data*10 + Arry[i] - '0';
    }

    if(Arry[i] == '.')
    {
        Point = &Arry[i + 1];
        for(j = 0; (Point[j]>='0'&& Point[j]<='9') && j<pointlen; j++)
        {
            data = data*10 + Point[j] - '0';
        }
    }

    if(j<pointlen)
    {
        for(; j<pointlen; j++)
        {
            data = data*10;
            // DispChar("7");
        }
    }

    return data;    
}

/*
*************************PF*************************
描述：转化字符串，转化成浮点数；
输入：浮点数指针，需要转化的数据指针，转化字符长度
输出: 转换成功返回 1，转换失败返回 0

失败标志：
遇到非法字符，
*/
char My_AtoInt(int *NumberP,char *Arry, int len)
{
// 判断符号位
int number1 = 0;

int numbertemp = 0;

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
    if (Arry[Cnt] >= '0' && Arry[Cnt] <= '9')
    {
        // 正数部分
        numbertemp = Arry[Cnt] - '0';
        number1 = number1 * 10 + numbertemp;
    }
    else
    {
        return 0; //其他字符
    }
}

*NumberP = number1 * polarity;
return 1;

}
/******************************************
 * 浮点数转换成字符串
 * 输入：fnumberP   浮点数， 
 *      Arry        返回的字符串，
 *      Pointlen    保留几位小数数
 * 返回：已转换的长度
 * 例如：-1.22  Pointlen=3  输出-1.220  
 * 精度受限
 * ****************************************/
int My_FtoA(float fnumberP,char *Arry, int Pointlen)
{
    int number; /* 整数部分 */
    int numbertemp; /* 整数部分 */
    float decimals = 0; /* 小数部分 */
    float decimalstemp; /* 小数部分 */
    int len = 0;
    int integerlen = 0;
    int i = 0;
    char chartemp;
    char *Arry2 = NULL;

    if(fnumberP<0)
    {
        Arry[0] = '-';
        fnumberP = -fnumberP;
    }
    else
    {
        Arry[0] = '+';
    }
    
    Arry2 = &Arry[1];


    number = fnumberP;
    decimals = decimals;//消除警告
    decimals = fnumberP - number;
    // 整数数据大小    
    numbertemp = number;
    for(i=0; numbertemp>0; i++)
    {
        Arry2[i] = numbertemp%10 + '0';
        numbertemp = numbertemp/10;
    }

    if(i>0)
    {
        for(integerlen=0; integerlen<(i/2); integerlen++)
        {
            chartemp = Arry2[integerlen];
            Arry2[integerlen] = Arry2[i-integerlen-1];

            Arry2[i-integerlen-1] = chartemp;
        }
        integerlen = i;
    }
    else
    {
        Arry2[0] = '0';
        integerlen = 1;
    }

    Arry2[integerlen] = '.';
    //小数部分： 不能单独提取出小数进行计算，否则会出现，小数部分精度不对,存储精度足够。
    decimalstemp = fnumberP;
    for(i=0;i<Pointlen;i++)
    {
        decimalstemp = decimalstemp * 10;
        numbertemp = decimalstemp;
        Arry2[integerlen+1+i] = numbertemp %10 + '0';
    }
    
    len = 1+integerlen+1+Pointlen;
    return len;
}

/*
*************************PF*************************
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
char My_AtoIP(uint8_t *IPaddr,char *Arry, int len)
{
//192.168.1.12
int number[4] = {0};
int numbertemp = 0;


int Cnt = 0; //遍历字符串
int IPcnt = 0;//当前为IP哪一段；

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