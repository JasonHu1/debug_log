#include "debug_log_printf.h"
/* ------------------------------------------------------------------------------------------------
*                                            Defines
* ------------------------------------------------------------------------------------------------
*/

/* ------------------------------------------------------------------------------------------------
*                                         Global Variables
* ------------------------------------------------------------------------------------------------
*/


/************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */
int g_debug_level= DBG_INFO;
/*********************************************************************
 * LOCAL VARIABLES
 */


/*********************************************************************
* LOCAL FUNCTIONS
*/


static char timeString[30]={0};	
static char cvTimeString[30]={0};

const char *date[12][2]={
{"Jan","01"},
{"Feb","02"},
{"Mar","03"},
{"Apr","04"},
{"May","05"},
{"Jun","06"},
{"Jul","07"},
{"Aug","08"},
{"Sep","09"},
{"Oct","10"},
{"Nov","11"},
{"Dec","12"}};


void spliceCompileTime(char* timeStr)
{
	timeStr = timeString;

	memcpy(timeString,__DATE__,sizeof(__DATE__));
	timeString[11] = 0x20;//" ";
	memcpy(&timeString[12],__TIME__,sizeof(__TIME__));
	vPrintf("%s\r\n",timeStr);
}
/*
 *printf format:20180629073606
 * demo the Two level pointer
 *
 * uint8_t *p=NULL;
 * convertCompileTimeToVersionNumber(&p);
 * vDEBUG_PRINTF_APP(TRACE_APP,"SubVer:%s",p);
 */
void convertCompileTimeToVersionNumber(char** timeStr)
{
	char yearStr[5];
	char monthStr[15];
	char dayStr[3];
	char hourStr[3];
	char minuteStr[3];
	char secondStr[3];
	int i;
	int cnt =sizeof(__DATE__);

	printCompileTime();
	*timeStr = cvTimeString;

	memcpy(cvTimeString,__DATE__,cnt);
	memcpy(&cvTimeString[12],__TIME__,sizeof(__TIME__));
	
	for(i=0;i<cnt;i++)
	{
	  if(cvTimeString[i]==' ')
	  {
	  	break;
	  }
	  vDEBUG_PRINTF_APP(TRACE_OFF,"i++");
	}
	
	vDEBUG_PRINTF_APP(TRACE_OFF,"i=%d",i);
	memcpy(monthStr,&cvTimeString[0],i);
	monthStr[i] = '\0';
	
	for(i=0;i<12;i++)
		{
		if(strcmp(monthStr,date[i][0])==0)
			{
				strcpy(monthStr,date[i][1]);
				break;
			}
		vDEBUG_PRINTF_APP(TRACE_OFF,"iii++");
		}
		
	/*get the string*/
	if(cvTimeString[4]==' ')
	{
		cvTimeString[4] = '0';
	}
	memcpy(dayStr,&cvTimeString[4],2);	
	memcpy(yearStr,&cvTimeString[7],4);
	memcpy(hourStr,&cvTimeString[12],2);
	memcpy(minuteStr,&cvTimeString[15],2);
	memcpy(secondStr,&cvTimeString[18],2);
	
    /*splice the string*/
	memcpy(&cvTimeString[0],yearStr,4);	
	memcpy(&cvTimeString[4],monthStr,2);
	memcpy(&cvTimeString[6],dayStr,2);
	
	memcpy(&cvTimeString[8],hourStr,2);
	memcpy(&cvTimeString[10],minuteStr,2);
	memcpy(&cvTimeString[12],secondStr,2);
	cvTimeString[14]='\0';
}

void printCompileTime(void)
{
	vPrintf("%s %s\r\n",__DATE__,__TIME__);
}


void printRemainHeap(const char*functionName,int line,char*a)
{	
	//vPrintf("[%s]<%d>HeapSize:%d-%s\r\n",functionName,line,xPortGetFreeHeapSize(),a);
}
void printArray(uint8_t *inbuf,uint8_t inlen)

{
	uint8_t j;
	vPrintf("inlen=0x%02x\r\n",inlen);
	for(j=0;j<inlen;j++)
	{
		vPrintf("%02x ",inbuf[j]);
	}
}

