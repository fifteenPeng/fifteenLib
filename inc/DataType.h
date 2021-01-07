#ifndef __DATATYPE_H_
#define __DATATYPE_H_

/* *****************************************************************
作者：fifteenpeng
描述：便于各库的移植，在此定义数据类型
******************************************************************** */
#ifndef NULL
#define NULL 0
#endif // !NULL

#ifndef uint8_t
#define uint8_t unsigned char
#endif // !1

#ifndef int8_t
#define int8_t  char
#endif // !int8_t

#ifndef uint16_t
#define uint16_t unsigned short int
#endif // !uint16_t

#ifndef int16_t
#define int16_t short int
// typedef short int int16_t
#endif // !int16_t

#ifndef uint32_t
#define uint32_t unsigned int
#endif // !uint32_t

#ifndef int32_t
#define int32_t int
#endif // !int32_t


#ifndef uint64_t
#define uint64_t unsigned long int
#endif 

#ifndef int64_t
#define int64_t long int
#endif 

/* 布尔类型 */
#ifndef TRUE
#define TRUE 1
#endif // !TRUE

#ifndef FALSE
#define FALSE 0
#endif // !TRUE
// typedef unsigned char  uint8;  
// typedef signed   char  int8;   
// typedef unsigned short uint16; 
// typedef signed   short int16;  
// typedef unsigned int   uint32; 
// typedef signed   int   int32;  
// typedef float          fp32;   
// typedef double         fp64;   

#endif
