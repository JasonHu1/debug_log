#ifndef __APP_DEFS_TYPE_H_
#define __APP_DEFS_TYPE_H_


#include "stdio.h"

#define TYPE_VER				"V01.00"


#ifdef _TYPE_EXTERN_
#define EXT_TYPE	
#else
#define EXT_TYPE				extern
#endif // _TYPE_EXTERN_


//-----------------------------------------------------------------------------

#ifndef true
#define true					1
#endif // true

#ifndef false
#define false					0
#endif // false


// Table 193 -- Logic Values
#ifndef YES
#define YES						1
#endif // YES

#ifndef NO
#define NO						0
#endif // NO

#ifndef SET
#define SET						1
#endif // SET

#ifndef CLEAR
#define CLEAR					0
#endif // CLEAR

#ifndef NULL
#define NULL					0
#endif // NULL

#ifndef Z_EXTADDR_LEN
#define Z_EXTADDR_LEN   		8
#endif

#ifndef SUCCESS
#define SUCCESS                   0x00
#endif

#ifndef  FAILURE
#define FAILURE                   0x01
#endif
//-----------------------------------------------------------------------------

typedef unsigned char			BYTE;

typedef	unsigned char			UINT8;	///<unsigned char

typedef	signed char             INT8;	///< char

typedef signed   char   		int8;
typedef signed   char   		int8_t;

typedef	unsigned short			UINT16;	///<unsigned char

typedef	signed short            INT16;	///<short

typedef unsigned int            UINT32;	///<unsigned int

typedef	signed int              INT32;	///<int

typedef unsigned char			BOOL;	///<BOOL

typedef unsigned int 			U32;

typedef unsigned short 			U16;

typedef unsigned char 			U8;

typedef signed short 			S16;

typedef signed int 				S32;

typedef signed char 			S8;

typedef unsigned long long 		UINT64;

typedef unsigned long long 		U64;

typedef UINT8					uint8; 

typedef unsigned char		    uint8_t; 

typedef UINT16					uint16;

typedef unsigned int			uint32_t;

typedef unsigned short  		uint16_t;

typedef unsigned int            uint32;

typedef	signed short            int16;

typedef uint8   				byte;

typedef	signed int              int32;

typedef int32   				int24;

typedef uint32 					uint24;

typedef uint8 					Status_t;

typedef Status_t 				ZStatus_t;

typedef ZStatus_t				afStatus_t;

#define HI_UINT16(a) ((unsigned char)(((unsigned int)(a) >> 8) & 0xFF))
#define LO_UINT16(a) ((unsigned char)((unsigned int)(a) & 0xFF))
#define BUILD_UINT16(loByte, hiByte) \
          ((short)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))
 
#endif//__APP_DEFS_TYPE_H_