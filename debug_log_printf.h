/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef __DEBUG_LOG_PRINTF_H__
#define __DEBUG_LOG_PRINTF_H__

#include <stdio.h>//printf define in this file
#include "stdint.h"//typedef like this uint32_t


#define vPrintf    printf


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif



#ifndef NULL
#define NULL 0
#endif


/****************************************************************************/
/***	  DEBUG FLAG Definitions								  ***/
/****************************************************************************/
#define  USE_SOFT_UAER_FOR_DEBUG	1
/****************************************************************************/
/***      DEBUG ENABLE  Macro Definitions                                 ***/
/****************************************************************************/
#define TRACE_ON			TRUE
#define TRACE_OFF			FALSE
//
#define TRACE_APP   		TRUE
#define TRACE_APP_EVENT   	TRACE_ON
#define TRACE_APP_BDB     	TRUE
#define TRACE_POLL_SLEEP   	TRUE
#define TRACE_MQTT		   	TRUE
#define TRACE_COMPANY	   	TRUE
#define TRACE_ERROR		   	TRUE
#define TRACE_FUNC_NAME		TRUE
#define TRACE_CJSON		    TRUE
#define TRACE_ZCL			TRUE
#define TRACE_CREAT_NETWORK TRUE
#define TRACE_UART_COM      TRUE

/****************************************************************************/
/***      The highest interface for debug log printf  Macro Definitions                                             ***/
/****************************************************************************/
#define vDEBUG_PRINTF1(...)	vPrintf(__VA_ARGS__)
	
#define vDEBUG_PRINTF(debug,_fmt_, ...)				\
		do{\
		if(debug)\
		{\
			vPrintf(_fmt_, ##__VA_ARGS__);\
		}\
	}while(0)

#define vDEBUG_PRINTF_CRLF(debug,_fmt_, ...)				\
				do{\
				if(debug)\
				{\
					vPrintf(_fmt_"\n\r", ##__VA_ARGS__);\
				}\
			}while(0)
#define vDEBUG_PRINTF_FUNC_NAME(debug)				\
									do{\
									if(debug)\
									{\
										vPrintf("\r\n[FEIBIT]%s IN\r\n",__FUNCTION__);\
									}\
								}while(0)

#define vDEBUG_PRINTF_FUNC_NAME_OUT(debug)				\
								do{\
								if(debug)\
								{\
									vPrintf("\r\n[FEIBIT]%s OUT\r\n",__FUNCTION__);\
								}\
							}while(0)
#define vDEBUG_PRINTF_FUNC(debug,_fmt_, ...)				\
										do{\
											if(debug)\
											{\
												vPrintf("[%s] "_fmt_"\n\r",__FUNCTION__, ##__VA_ARGS__);\
											}\
										}while(0)

#define vDEBUG_PRINTF_HTTP(debug,_fmt_, ...)				\
	do{\
		if(debug)\
		{\
			vPrintf("[HTTP] "_fmt_"\n\r", ##__VA_ARGS__);\
		}\
	}while(0)

#define vDBG_PF_ERROR(_fmt_, ...)				\
				do{\
					{\
						vPrintf("[ERROR]<%d>[%s] "_fmt_"\n\r",__LINE__,__FUNCTION__, ##__VA_ARGS__);\
					}\
				}while(0)
#define vDEBUG_PRINTF_ERROR1(_fmt_, ...)				\
				do{\
					{\
						vPrintf("[ERROR]<%d>[%s] "_fmt_"\n\r",__LINE__,__FUNCTION__, ##__VA_ARGS__);\
					}\
				}while(0)

#define vDEBUG_PRINTF_HAL(debug,_fmt_, ...)				\
	do{\
		if(debug)\
		{\
			vPrintf("[HAL] "_fmt_"\n\r", ##__VA_ARGS__);\
		}\
	}while(0)

#define vDEBUG_PRINTF_MQTT(debug,_fmt_, ...)				\
	do{\
		if(debug)\
		{\
			vPrintf("[MQTT] "_fmt_"\n\r", ##__VA_ARGS__);\
		}\
	}while(0)

#define vDEBUG_PRINTF_WARNING(debug,_fmt_, ...)				\
	do{\
		if(debug)\
		{\
			vPrintf("[WARNING] "_fmt_"\n\r", ##__VA_ARGS__);\
		}\
	}while(0)

#define vDEBUG_PRINTF_APP(debug,_fmt_, ...)				\
	do{\
		if(debug)\
		{\
			vPrintf("[APP]<%d>[%s]"_fmt_"\n\r",__LINE__,__FUNCTION__, ##__VA_ARGS__);\
		}\
	}while(0)
#define vDEBUG_PRINTF_UART(debug,_fmt_, ...)				\
	do{\
		if(debug)\
		{\
			vPrintf("[UART] "_fmt_"\n\r", ##__VA_ARGS__);\
		}\
	}while(0)
	
#define vDEBUG_PRINTF_COMPANY(debug,_fmt_, ...)				\
		do{\
		if(debug)\
		{\
			vPrintf("[feibit]"_fmt_"\n\r", ##__VA_ARGS__);\
		}\
	}while(0)
#define vDEBUG_PRINTF_ARRAY(debug,inbuf,inlen)				\
					do{\
					if(debug)\
					{\
						vPrintf("inlen1=0x%02x\r\n",inlen);\
						vPrintf("%02x ",inbuf[0]);\
						vPrintf("[Array]->[");\
						printArray(inbuf,inlen);\
						vPrintf("]\r\n");\
					}\
				}while(0)
#define vDEBUG_PRINTF_ZCL(debug,_fmt_, ...)				\
	do{\
		if(debug)\
		{\
			vPrintf("[ZCL]<%d>[%s]"_fmt_"\n\r",__LINE__,__FUNCTION__, ##__VA_ARGS__);\
		}\
	}while(0)
#define vDEBUG_PRINTF_CREATE_NWK(debug,_fmt_, ...)				\
	do{\
		if(debug)\
		{\
			vPrintf("[CreatNWK]<%d>[%s]"_fmt_"\n\r",__LINE__,__FUNCTION__, ##__VA_ARGS__);\
		}\
	}while(0)
#define vDBG_PF_CREATE_NWK(debug,_fmt_, ...)				\
	do{\
		if(debug)\
		{\
			vPrintf("[CreatNWK]<%d>[%s]"_fmt_"\n\r",__LINE__,__FUNCTION__, ##__VA_ARGS__);\
		}\
	}while(0)
	
#define ASSERT(x)		if(!x) return;
#if 0
/* takes a byte out of a uint32_t : var - uint32_t,  ByteNum - byte to take out (0 - 3) */
#define BREAK_UINT32( var, ByteNum ) \
          (uint8_t)((uint32_t)(((var) >>((ByteNum) * 8)) & 0x00FF))

#define BUILD_UINT32(Byte0, Byte1, Byte2, Byte3) \
          ((uint32_t)((uint32_t)((Byte0) & 0x00FF) \
          + ((uint32_t)((Byte1) & 0x00FF) << 8) \
          + ((uint32_t)((Byte2) & 0x00FF) << 16) \
          + ((uint32_t)((Byte3) & 0x00FF) << 24)))

#define BUILD_UINT16(loByte, hiByte) \
          ((uint16_t)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

#define HI_UINT16(a) (((a) >> 8) & 0xFF)
#define LO_UINT16(a) ((a) & 0xFF)

#define BUILD_UINT8(hiByte, loByte) \
          ((uint8_t)(((loByte) & 0x0F) + (((hiByte) & 0x0F) << 4)))

#define HI_UINT8(a) (((a) >> 4) & 0x0F)
#define LO_UINT8(a) ((a) & 0x0F)
#endif

#ifndef GET_BIT
#define GET_BIT(DISCS, IDX)  (((DISCS)[((IDX) / 8)] & BV((IDX) % 8)) ? TRUE : FALSE)
#endif
#ifndef SET_BIT
#define SET_BIT(DISCS, IDX)  (((DISCS)[((IDX) / 8)] |= BV((IDX) % 8)))
#endif
#ifndef CLR_BIT
#define CLR_BIT(DISCS, IDX)  (((DISCS)[((IDX) / 8)] &= (BV((IDX) % 8) ^ 0xFF)))
#endif

extern void spliceCompileTime(char* timeStr);
extern void printCompileTime(void);
extern void printRemainHeap(const char*functionName,int line,char*a);
/****************************************************************************/
/***       LWIP DEBUG Study Macro Definitions                                             ***/
/****************************************************************************/

#if 0
/** lower two bits indicate debug level
 * - 0 all
 * - 1 warning
 * - 2 serious
 * - 3 severe
 */
#define LWIP_DBG_LEVEL_ALL     0x00
#define LWIP_DBG_LEVEL_OFF     LWIP_DBG_LEVEL_ALL /* compatibility define only */
#define LWIP_DBG_LEVEL_WARNING 0x01 /* bad checksums, dropped packets, ... */
#define LWIP_DBG_LEVEL_SERIOUS 0x02 /* memory allocation failures, ... */
#define LWIP_DBG_LEVEL_SEVERE  0x03
#define LWIP_DBG_MASK_LEVEL    0x03

/** flag for LWIP_DEBUGF to enable that debug message */
#define LWIP_DBG_ON            0x80U
/** flag for LWIP_DEBUGF to disable that debug message */
#define LWIP_DBG_OFF           0x00U

/** flag for LWIP_DEBUGF indicating a tracing message (to follow program flow) */
#define LWIP_DBG_TRACE         0x40U
/** flag for LWIP_DEBUGF indicating a state debug message (to follow module states) */
#define LWIP_DBG_STATE         0x20U
/** flag for LWIP_DEBUGF indicating newly added code, not thoroughly tested yet */
#define LWIP_DBG_FRESH         0x10U
/** flag for LWIP_DEBUGF to halt after printing this debug message */
#define LWIP_DBG_HALT          0x08U

#ifndef LWIP_NOASSERT
#define LWIP_ASSERT(message, assertion) do { if(!(assertion)) \
  LWIP_PLATFORM_ASSERT(message); } while(0)
#else  /* LWIP_NOASSERT */
#define LWIP_ASSERT(message, assertion) 
#endif /* LWIP_NOASSERT */

#ifdef CONFIG_DEBUG_BUILD
/** if "expression" isn't true, then print "message" and execute "handler" expression */
#define LWIP_ERROR(message, expression, handler) do { if (!(expression)) { \
  LWIP_PLATFORM_ASSERT(message); handler;}} while(0)
#else
#define LWIP_ERROR(...)
#endif

#define LWIP_PLATFORM_PRINT(_x_) do { wmprintf  _x_ ; } while (0)
	
	
#ifdef LWIP_DEBUG
/** print debug message only if debug message type is enabled...
 *  AND is of correct type AND is at least LWIP_DBG_LEVEL
 */
#define LWIP_DEBUGF(debug, message) do { \
                               if ( \
                                   ((debug) & LWIP_DBG_ON) && \
                                   ((debug) & LWIP_DBG_TYPES_ON) && \
                                   ((s16_t)((debug) & LWIP_DBG_MASK_LEVEL) >= LWIP_DBG_MIN_LEVEL)) { \
                                 LWIP_PLATFORM_PRINT(message); \
                                 if ((debug) & LWIP_DBG_HALT) { \
                                   while(1); \
                                 } \
                               } \
                             } while(0)

#else  /* LWIP_DEBUG */
#define LWIP_DEBUGF(debug, message) 
#endif /* LWIP_DEBUG */
#endif
/****************************************************************************/
/***       openwrt                                            ***/
/****************************************************************************/
enum{
    DBG_ERROR,
    DBG_WARNING,
    DBG_INFO,
    DBG_DEBUG,
    DBG_MSGDUMP,
    DBG_EXCESSIVE,
};
//general simple
#define vDBG_DEBUG(...)    do{if(g_debug_level>=DBG_DEBUG){ printf(__VA_ARGS__);}}while(0)
#define vDBG_INFO(...)     do{if(g_debug_level>=DBG_INFO){ printf(__VA_ARGS__);}}while(0)
#define vDBG_ERR(...)      do{if(g_debug_level>=DBG_ERROR){printf(__VA_ARGS__);}}while(0)
#define vDBG_WARN(...)     do{if(g_debug_level>=DBG_WARNING){printf(__VA_ARGS__);}}while(0)

//module detailedly
#define vDBG_APP(level,_fmt_,...)\
    do{if(g_debug_level>=level){printf("APP::[%s]<%d>"_fmt_"\n\r",__FUNCTION__,__LINE__,##__VA_ARGS__);}}while(0)
    
#define vDBG_MODULE1(level,_fmt_,...)\
    do{if(g_debug_level>=level){printf("MODULE1::[%s]<%d>"_fmt_"\n\r",__FUNCTION__,__LINE__,##__VA_ARGS__);}}while(0)
    
#define vDBG_MODULE2(level,_fmt_,...)\
    do{if(g_debug_level>=level){printf("MODULE2::[%s]<%d>"_fmt_"\n\r",__FUNCTION__,__LINE__,##__VA_ARGS__);}}while(0)
    
#define vDBG_MODULE3(level,_fmt_,...)\
    do{if(g_debug_level>=level){printf("MODULE3::[%s]<%d>"_fmt_"\n\r",__FUNCTION__,__LINE__,##__VA_ARGS__);}}while(0)
    
#endif//__DEBUG_LOG_PRINTF_H__
