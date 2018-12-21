#ifndef __SOFTWARE_UART_STDIO_H__
#define __SOFTWARE_UART_STDIO_H__
#include "serial_main.h"

//#define   SoftWareDebugPrint(x,y)	  	SerialInterfaceWrite(x,y)

extern int cli_printf(const char *str,...);
extern void InitSoftDebugUart(void);
extern uint8_t UARTDebugprintf(const char *pcString, ...);

#endif//__SOFTWARE_UART_STDIO_H__


