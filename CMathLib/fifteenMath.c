#include "fifteenMath.h"



/* **************
* 数据初始化
 ******************/
void FB_Math_Init(void)
{
    
}


/***************
 * 计算KB 值
 * 输入：两点坐标，接收的KB值指针；
 * 返回：0错误， 1正确
 * *************/
int8_t FB_Calc_K_B(float x1, float  y1, float x2,  float y2, float *k,  float *b)
{
	if(x2==x1 && y2!=y1) //容错处理；
	{
		return 0;
	}
	else if(x2==x1 && y2==y1) //容错处理,同一个点；
    {
        *k = 1;
        *b = y2- x2*(*k);

    }
    else
    {
        *k = (y2-y1)/(x2-x1);
	    *b = y2- x2*(*k);
    }

	return 1;
}


/* 
计算斜率函数：
输入：接收数据段指针，数据点个数,数组指针float* X  数组指针float* X
输出：

返回：0失败  1成功
 */
int8_t FB_SetValueLinear(FB_Linear_t* Ptr,int16_t Len,float* X, float* Y)
{
    int16_t i;
    int8_t result;
    i = 0;

    // 区间个数 =  总点数 - 1
    result = 1;
    Ptr->Num = 0;
    for(i=0;i<Len-1;i++)
    {
        // if(X[i]!=INVALID_CALIVAL && X[i+1] != INVALID_CALIVAL)
        // {
            Ptr->Num++;
            Ptr->Key[i].X = X[i];
			Ptr->Key[i+1].X = X[i+1];
            if(FB_Calc_K_B(X[i],Y[i],X[i+1],Y[i+1],&Ptr->Key[i].K,&Ptr->Key[i].B) == 0)
            {
                result = 0;
            }
        // }
    }

    return result;
}


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
int8_t FB_GetValueLinear(FB_Linear_t* Ptr,int16_t Len,float Xval, float * Y)
{
    int16_t i = 0;
	int8_t searchFlag = 0;


    /* Num 当前是第几段，区间数据 */
    if(Ptr->Num >= 1)	
    {
        // 判断当前X是递增,还是递减；
        if(Ptr->Key[0].X > Ptr->Key[Ptr->Num].X)
        {
            /* 递减 */
            for(i = 0; i< Ptr->Num; i++)
            {
                //位于区间；
                if(Xval <= Ptr->Key[i].X && Xval >= Ptr->Key[i+1].X)
                {
                    searchFlag = 1;			
                    *Y = Xval * Ptr->Key[i].K + Ptr->Key[i].B;
                    break;
                }
            }

            if(searchFlag != 1) 
            {
                /* 位于首 */
                if(Xval > Ptr->Key[0].X)
                {
                        *Y = Xval * Ptr->Key[0].K + Ptr->Key[0].B;
                        searchFlag = 1;

                }
                /* 位于尾 */
                else if(Xval < Ptr->Key[Ptr->Num].X)
                {
                        *Y = Xval * Ptr->Key[Ptr->Num - 1].K + Ptr->Key[Ptr->Num - 1].B; 
                        searchFlag = 1;
                }
            }
        }
        else
        {

            // 递增
            for(i = 0; i< Ptr->Num; i++)
            {
                //位于区间；
                if(Xval >= Ptr->Key[i].X && Xval <= Ptr->Key[i+1].X)
                {
                    searchFlag = 1;			
                    *Y = Xval * Ptr->Key[i].K + Ptr->Key[i].B;
                    break;
                }
            }

            if(searchFlag != 1)
            {
                /* 位于首 */
                if(Xval < Ptr->Key[0].X)
                {
                    *Y = Xval * Ptr->Key[0].K + Ptr->Key[0].B;
                    searchFlag = 1;
                }
                /* 位于尾 */
                else if(Xval > Ptr->Key[Ptr->Num].X)
                {
                    *Y = Xval * Ptr->Key[Ptr->Num - 1].K + Ptr->Key[Ptr->Num - 1].B; 
                    searchFlag = 1;
                }
            } 

        }/* end if(Ptr->Key[0].X > Ptr->Key[Ptr->Num].X) */
    }

    /* 找不到则返回失败 */
    return searchFlag;
}

#ifdef FIFTEEN_TEST

// 测试函数
// float DATA_X[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34};
// float DATA_Y[]={101,200,297,392,485,576,665,752,837,920,1001,1080,1157,1232,1305,1376,1445,1512,1577,1640,1701,1760,1817,1872,1925,1976,2025,2072,2117,2160,2201,2240,2277,2312,};

// float DATA_X[]={34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
// float DATA_Y[]={3401,3269,3139,3011,2885,2761,2639,2519,2401,2285,2171,2059,1949,1841,1735,1631,1529,1429,1331,1235,1141,1049,959,871,785,701,619,539,461,385,311,239,169,101};
float DATA_X[]= {-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,};
float DATA_Y[]= {-1499,-1384,-1271,-1160,-1051,-944,-839,-736,-635,-536,-439,-344,-251,-160,-71,16,101,184,265,344,421,496,569,640,709,776,841,904,965,1024,1081,1136,1189,1240};

/* 当前数据计算值 */
FB_Linear_t LinearKB;

/* 为了动态保证数据内存 改用指针 */
linearKey_t LinearKBKey[MAX_LINEAR_COUNT];

void fifteenMath_test(void)
{
    uint16_t Len = 34;
    int16_t i;

    // float X = 36;
    // float X = 19;
    // float X = 0.5;
     float X = -17;
    //  float X = -12;

    float Y = 0;

    LinearKB.Key = LinearKBKey;

    FB_Math_Init();

    FB_SetValueLinear(&LinearKB,Len,DATA_X,DATA_Y);

    for(i=0; i<Len; i++)
    {
        printf("%d,X:%f,K:%f,B:%f\r\n",i,LinearKB.Key[i].X,LinearKB.Key[i].K,LinearKB.Key[i].B);
    }

    FB_GetValueLinear(&LinearKB,Len,X,&Y);

    printf("Y:%f\r\n",Y);

}

#endif 