

#include <stdarg.h>
//#include <stdio.h>
#include "Gpio.h"
#include "clock.h"
#include "Timer.h"
#include "Interrupt.h"
#include "debug_log_printf.h"
#include "Uart.h"






//*****************************************************************************
//
// A mapping from an integer between 0 and 15 to its ASCII character
// equivalent.
//
//*****************************************************************************
const char * const g_pcHex = "0123456789ABCDEF";
#define sTXIDLE 0
#define sTXSTARTBIT 1
#define sTXDATA 2
#define sTXSTOPBIT 3
#define SOFEWARE_MAX_UART_TX_BUF_SIZE	 256	
#define ADVANCE_TX_BUFFER_INDEX(Index) \
		(Index) = ((Index) + 1) % SOFEWARE_MAX_UART_TX_BUF_SIZE 
						

static uint8_t sUartstatus = sTXIDLE;//sUartTXBusy;
uint8_t sdata=0;
static uint8_t sbit;
static uint8_t sUartTXbuf[SOFEWARE_MAX_UART_TX_BUF_SIZE]={0};//UartTXbuf
uint32_t sUart_tx_head=0,sUart_tx_tail=0;
extern unsigned long demotimer0count;

extern uint8_t  SerialInterfaceWrite(const char *pcBuf, unsigned long ulLen);
//-----------------------------------------------------------------------------


/**
 * \brief	ï¿½ï¿½Ê±ï¿½ï¿½0ï¿½ï¿½4ï¿½ï¿½ï¿½ï¿½
 * \details	
 *
 * \param[in]  : 
 * \return[out]  : 
 *
 * \author	jin.zhonghua
 * \version	V01.00
 * \date	2017/08/11 Fri 16:41:39
 * \warning	
 * \copyright	Copyright (c) 2020, Nationz Corporation
 */
void DemoInitTimer(void)
{
	SetModuleClockSwitch((emCG)EM_CG_TIMERCLKEN, (emBool)TRUE);///ï¿½ï¿½ï¿½ï¿½timerÊ±ï¿½ï¿½ ×¢ï¿½ï¿½timerï¿½ï¿½Ê±ï¿½Ó¿ï¿½ï¿½ï¿½Òªï¿½ï¿½SetTimerClockÒ»ï¿½ï¿½ï¿½ï¿½ï¿½Ê¹ï¿½Ã£ï¿½Í¬Ê±Ê¹ï¿½Ã¡ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½â¡£
	SetTimerClock((emTIMER)EM_TIMER_0, (emCLKSC)EM_CLKSC_10M,1000000,(emBool)TRUE);///TIMER0 Ê±ï¿½ï¿½1M
	StartTimer((emTMNUM)EM_TMNUM_0, (emBool)FALSE);

	InitTimer((emTMNUM)EM_TMNUM_0, EM_TMCTL_ISR, 43);
	StartTimer((emTMNUM)EM_TMNUM_0, (emBool)TRUE);
	EnInterrupt((emINTNUM)EM_INTNUM_TIMER0, (emBool)TRUE);
}

/*
* use GPIO9 for debug uart RX
* use timer0 for soft debug uart 
*/
void InitSoftDebugUart(void)
{
	//GPIO9 output 
	SetGPIOFunction((emGPIOFUNCTION)EM_IICEN, (emBool)FALSE); 
	SetGPIODirection((emGPIO)EM_GPIO_SCK, EM_GPIO_OUT); 
	SetGPIOUpDown((emGPIO)EM_GPIO_SCK, (emBool)FALSE, (emBool)FALSE); 
	SetGPIOInterruptMode((emGPIO)EM_GPIO_SCK, (emBool)FALSE, (emBool)FALSE); 
	
	DemoInitTimer();
}

//*****************************************************************************
//
// A mapping from an integer between 0 and 15 to its ASCII character
// equivalent.
//
//*****************************************************************************
uint8_t SoftWareDebugPrint(const char *pdata,unsigned long len)
{
	uint8_t i=0;
	if(((sUart_tx_head+1) % SOFEWARE_MAX_UART_TX_BUF_SIZE)!=sUart_tx_tail)//full then not write
	{
		for(i=0;i<len;i++)
		{
			sUartTXbuf[sUart_tx_head] = *pdata++;
			ADVANCE_TX_BUFFER_INDEX(sUart_tx_head);	
		}
	}
	else 
	{
		sUartTXbuf[sUart_tx_head] = '!';
		ADVANCE_TX_BUFFER_INDEX(sUart_tx_head);	
		sUartTXbuf[sUart_tx_head] = '@';
		ADVANCE_TX_BUFFER_INDEX(sUart_tx_head);	
		sUartTXbuf[sUart_tx_head] = '#';
		ADVANCE_TX_BUFFER_INDEX(sUart_tx_head);	
		sUartTXbuf[sUart_tx_head] = '$';
		ADVANCE_TX_BUFFER_INDEX(sUart_tx_head);	
		sUartTXbuf[sUart_tx_head] = '%';
		ADVANCE_TX_BUFFER_INDEX(sUart_tx_head);	
		sUartTXbuf[sUart_tx_head] = '^';
		ADVANCE_TX_BUFFER_INDEX(sUart_tx_head);	
		sUartTXbuf[sUart_tx_head] = '&';
		ADVANCE_TX_BUFFER_INDEX(sUart_tx_head);	
		sUartTXbuf[sUart_tx_head] = '*';
		ADVANCE_TX_BUFFER_INDEX(sUart_tx_head);	
	
	}
	return 0;
}

int cli_printf(const char *str,...)
{
	int res = 0;
	return res;
}

//*****************************************************************************
//
//! A simple UART based printf function supporting \%c, \%d, \%p, \%s, \%u,
//! \%x, and \%X.
//!
//! \param pcString is the format string.
//! \param ... are the optional arguments, which depend on the contents of the
//! format string.
//!
//! This function is very similar to the C library <tt>fprintf()</tt> function.
//! All of its output will be sent to the UART.  Only the following formatting
//! characters are supported:
//!
//! - \%c to print a character
//! - \%d to print a decimal value
//! - \%s to print a string
//! - \%u to print an unsigned decimal value
//! - \%x to print a hexadecimal value using lower case letters
//! - \%X to print a hexadecimal value using lower case letters (not upper case
//! letters as would typically be used)
//! - \%p to print a pointer as a hexadecimal value
//! - \%\% to print out a \% character
//!
//! For \%s, \%d, \%u, \%p, \%x, and \%X, an optional number may reside
//! between the \% and the format character, which specifies the minimum number
//! of characters to use for that value; if preceded by a 0 then the extra
//! characters will be filled with zeros instead of spaces.  For example,
//! ``\%8d'' will use eight characters to print the decimal value with spaces
//! added to reach eight; ``\%08d'' will use eight characters as well but will
//! add zeroes instead of spaces.
//!
//! The type of the arguments after \e pcString must match the requirements of
//! the format string.  For example, if an integer was passed where a string
//! was expected, an error of some kind will most likely occur.
//!
//! \return None.
//
//*****************************************************************************
uint8_t
UARTDebugprintf(const char *pcString, ...)
{
//	extern volatile portBASE_TYPE xInsideISR;
    unsigned long ulIdx, ulValue, ulPos, ulCount, ulBase, ulNeg;
    char *pcStr, pcBuf[16], cFill;
    va_list vaArgP;
//    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    //
    // Check the arguments.
    //
    ASSERT(pcString != 0);

	//printfmessage("uart_tx_tail=%d,uart_tx_head=%d\r\n",sUart_tx_tail,sUart_tx_head);
    // Don't do anything if no semaphore
    //if (xSemaphore == NULL)
   	// return;

    // Wait till we can get the mutex (Block for 10ms each try)
    //while( xSemaphoreTake( xSemaphore, 10 ) != pdTRUE );

    //
    // Start the varargs processing.
    //
    va_start(vaArgP, pcString);

    //
    // Loop while there are more characters in the string.
    //
    while(*pcString)
    {
        //
        // Find the first non-% character, or the end of the string.
        //
        for(ulIdx = 0; (pcString[ulIdx] != '%') && (pcString[ulIdx] != '\0');
            ulIdx++)
        {
        }

        //
        // Write this portion of the string.
        //
        SoftWareDebugPrint(pcString, ulIdx);

        //
        // Skip the portion of the string that was written.
        //
        pcString += ulIdx;

        //
        // See if the next character is a %.
        //
        if(*pcString == '%')
        {
            //
            // Skip the %.
            //
            pcString++;

            //
            // Set the digit count to zero, and the fill character to space
            // (i.e. to the defaults).
            //
            ulCount = 0;
            cFill = ' ';

            //
            // It may be necessary to get back here to process more characters.
            // Goto's aren't pretty, but effective.  I feel extremely dirty for
            // using not one but two of the beasts.
            //
again:

            //
            // Determine how to handle the next character.
            //
            switch(*pcString++)
            {
                //
                // Handle the digit characters.
                //
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    //
                    // If this is a zero, and it is the first digit, then the
                    // fill character is a zero instead of a space.
                    //
                    if((pcString[-1] == '0') && (ulCount == 0))
                    {
                        cFill = '0';
                    }

                    //
                    // Update the digit count.
                    //
                    ulCount *= 10;
                    ulCount += pcString[-1] - '0';

                    //
                    // Get the next character.
                    //
                    goto again;
                }

                //
                // Handle the %c command.
                //
                case 'c':
                {
                    //
                    // Get the value from the varargs.
                    //
                    ulValue = va_arg(vaArgP, unsigned long);

                    //
                    // Print out the character.
                    //
                    SoftWareDebugPrint((char *)&ulValue, 1);

                    //
                    // This command has been handled.
                    //
                    break;
                }

                //
                // Handle the %d command.
                //
                case 'd':
                {
                    //
                    // Get the value from the varargs.
                    //
                    ulValue = va_arg(vaArgP, unsigned long);

                    //
                    // Reset the buffer position.
                    //
                    ulPos = 0;

                    //
                    // If the value is negative, make it positive and indicate
                    // that a minus sign is needed.
                    //
                    if((long)ulValue < 0)
                    {
                        //
                        // Make the value positive.
                        //
                        ulValue = -(long)ulValue;

                        //
                        // Indicate that the value is negative.
                        //
                        ulNeg = 1;
                    }
                    else
                    {
                        //
                        // Indicate that the value is positive so that a minus
                        // sign isn't inserted.
                        //
                        ulNeg = 0;
                    }

                    //
                    // Set the base to 10.
                    //
                    ulBase = 10;

                    //
                    // Convert the value to ASCII.
                    //
                    goto convert;
                }

                //
                // Handle the %s command.
                //
                case 's':
                {
                    //
                    // Get the string pointer from the varargs.
                    //
                    pcStr = va_arg(vaArgP, char *);

                    //
                    // Determine the length of the string.
                    //
                    for(ulIdx = 0; pcStr[ulIdx] != '\0'; ulIdx++)
                    {
                    }

                    //
                    // Write the string.
                    //
                    SoftWareDebugPrint(pcStr, ulIdx);

                    //
                    // Write any required padding spaces
                    //
                    if(ulCount > ulIdx)
                    {
                        ulCount -= ulIdx;
                        while(ulCount--)
                        {
                            SoftWareDebugPrint(" ", 1);
                        }
                    }
                    //
                    // This command has been handled.
                    //
                    break;
                }

                //
                // Handle the %u command.
                //
                case 'u':
                {
                    //
                    // Get the value from the varargs.
                    //
                    ulValue = va_arg(vaArgP, unsigned long);

                    //
                    // Reset the buffer position.
                    //
                    ulPos = 0;

                    //
                    // Set the base to 10.
                    //
                    ulBase = 10;

                    //
                    // Indicate that the value is positive so that a minus sign
                    // isn't inserted.
                    //
                    ulNeg = 0;

                    //
                    // Convert the value to ASCII.
                    //
                    goto convert;
                }

                //
                // Handle the %x and %X commands.  Note that they are treated
                // identically; i.e. %X will use lower case letters for a-f
                // instead of the upper case letters is should use.  We also
                // alias %p to %x.
                //
                case 'x':
                case 'X':
                case 'p':
                {
                    //
                    // Get the value from the varargs.
                    //
                    ulValue = va_arg(vaArgP, unsigned long);

                    //
                    // Reset the buffer position.
                    //
                    ulPos = 0;

                    //
                    // Set the base to 16.
                    //
                    ulBase = 16;

                    //
                    // Indicate that the value is positive so that a minus sign
                    // isn't inserted.
                    //
                    ulNeg = 0;

                    //
                    // Determine the number of digits in the string version of
                    // the value.
                    //
convert:
                    for(ulIdx = 1;
                        (((ulIdx * ulBase) <= ulValue) &&
                         (((ulIdx * ulBase) / ulBase) == ulIdx));
                        ulIdx *= ulBase, ulCount--)
                    {
                    }

                    //
                    // If the value is negative, reduce the count of padding
                    // characters needed.
                    //
                    if(ulNeg)
                    {
                        ulCount--;
                    }

                    //
                    // If the value is negative and the value is padded with
                    // zeros, then place the minus sign before the padding.
                    //
                    if(ulNeg && (cFill == '0'))
                    {
                        //
                        // Place the minus sign in the output buffer.
                        //
                        pcBuf[ulPos++] = '-';

                        //
                        // The minus sign has been placed, so turn off the
                        // negative flag.
                        //
                        ulNeg = 0;
                    }

                    //
                    // Provide additional padding at the beginning of the
                    // string conversion if needed.
                    //
                    if((ulCount > 1) && (ulCount < 16))
                    {
                        for(ulCount--; ulCount; ulCount--)
                        {
                            pcBuf[ulPos++] = cFill;
                        }
                    }

                    //
                    // If the value is negative, then place the minus sign
                    // before the number.
                    //
                    if(ulNeg)
                    {
                        //
                        // Place the minus sign in the output buffer.
                        //
                        pcBuf[ulPos++] = '-';
                    }

                    //
                    // Convert the value into a string.
                    //
                    for(; ulIdx; ulIdx /= ulBase)
                    {
                        pcBuf[ulPos++] = g_pcHex[(ulValue / ulIdx) % ulBase];
                    }

                    //
                    // Write the string.
                    //
                    SoftWareDebugPrint(pcBuf, ulPos);

                    //
                    // This command has been handled.
                    //
                    break;
                }

                //
                // Handle the %% command.
                //
                case '%':
                {
                    //
                    // Simply write a single %.
                    //
                    SoftWareDebugPrint(pcString - 1, 1);

                    //
                    // This command has been handled.
                    //
                    break;
                }

                //
                // Handle all other commands.
                //
                default:
                {
                    //
                    // Indicate an error.
                    //
                    SoftWareDebugPrint("ERROR", 5);

                    //
                    // This command has been handled.
                    //
                    break;
                }
            }
        }
    }

    //
    // End the varargs processing.
    //
//    FlushUdpBuffer();
    va_end(vaArgP);
 	/*if( xInsideISR != pdFALSE )
 	{
 		xSemaphoreGiveFromISR( xSemaphore, &xHigherPriorityTaskWoken);
 	}
 	else
 	{
// 		xSemaphoreGive( xSemaphore );
 	}*/
	return 0;

}


/**
 * \brief	¶¨Ê±Æ÷ÖÐ¶Ï0ÑùÀý
 * \details	ÔÚ´ËÖÐ¶ÏÖÐµÄInitTimer³õÊ¼»¯Ò»¶¨Óë³õÊ¼»¯Ê±(DemoInitTimer)±£³ÖÒ»ÖÂ
 *
 * \param[in]  : 
 * \return[out]  : 
 *
 * \author	jin.zhonghua
 * \version	V01.00
 * \date	2017/08/11 Fri 17:02:26
 * \warning	
 * \copyright	Copyright (c) 2020, Nationz Corporation
 */
#if 0
__irq void IsrTimer0(void)
{
	GetTimerStatus(EM_TMNUM_0);
	demotimer0count++;
	InitTimer(EM_TMNUM_0, EM_TMCTL_ISR, 43);
}
#else
__irq void IsrTimer0(void)
{
	//GetTimerStatus(EM_TMNUM_0);
	demotimer0count++;
	//InitTimer(EM_TMNUM_0, EM_TMCTL_ISR, 1000000);
	
	GetTimerStatus(EM_TMNUM_0);
	InitTimer((emTMNUM)EM_TMNUM_0, EM_TMCTL_ISR, 41);
	#if 1
	/*
	if(sdata==0x01) // this bit is high
	{
	   sdata =0x00;
	   SetGPIO(EM_GPIO_SCK,EM_GPIO_HIGH);
	
	}
	else
	{
	 	sdata =0x01;
		SetGPIO(EM_GPIO_SCK,EM_GPIO_LOW);
	}*/
	#else
	switch (sUartstatus)
	{
		case sTXIDLE://
			if(sUart_tx_tail != sUart_tx_head) // if no empty
			{
		 // cv = *(dataBuf + uart_tail)
				sdata= sUartTXbuf[sUart_tx_tail];
			//	printf("%x", data);
				sUart_tx_tail++;
				if(sUart_tx_tail >= SOFEWARE_MAX_UART_TX_BUF_SIZE )
				{
					sUart_tx_tail = 0;
				}
				 sUartstatus = sTXSTARTBIT;
			  
			 }
			 else  // finish
			 {
		   
			   //sUartTXBusy = false;
			   break;
			 }
		case sTXSTARTBIT:
			SetGPIO(EM_GPIO_SCK,EM_GPIO_LOW);
			sUartstatus = sTXDATA;
			break;
		case sTXDATA:
			if(sdata&0x01) // this bit is high
			{
			
			   SetGPIO(EM_GPIO_SCK,EM_GPIO_HIGH);
			
			}
			else
			{
			
				SetGPIO(EM_GPIO_SCK,EM_GPIO_LOW);
			}
			sdata >>= 1;
			
			sbit=sbit+1;
			if(sbit>7) 
			{
				sbit =0;
				sUartstatus = sTXSTOPBIT;
			}
			
			break;
		case sTXSTOPBIT:
			SetGPIO(EM_GPIO_SCK,EM_GPIO_HIGH);
			sUartstatus = sTXIDLE;
			break;
	}
	
	
#endif
	
}
#endif

