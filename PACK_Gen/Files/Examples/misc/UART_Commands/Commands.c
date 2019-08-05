#include "Commands.h"
#include <MDR_Types.h>
#include <MDRB_LEDs.h>
#include <MDR_SysTimer.h>

#define DATA_LEN	20
static uint8_t dataStream[DATA_LEN];
static uint32_t dataCnt = 0;

static bool doExecCommand = false;

void LedToggle(void);
void LedSyclicToggleOn(void);
void LedSyclicToggleOff(void);

#define SYS_TIMER_PERIOD		50000000
uint32_t LED_SyclicInd = 0;


static pVoidFunc_void CommandHandlers[] = 
{
  LedToggle,
	LedSyclicToggleOn,
	LedSyclicToggleOff
};

bool COMM_AddData(uint8_t data)
{
	if (dataCnt == DATA_LEN)
		return false;
	else
	{
		dataStream[dataCnt] = data;
		++dataCnt;
		return false;
	}
}

void COMM_DataThreadCompleted(void)
{
	doExecCommand = true;
}

bool COMM_CheckDoExecCommand(void)
{
	return doExecCommand;
}

bool COMM_ExecCommand(void)
{
	uint8_t comID = dataStream[0];
	if (comID > DATA_LEN)
		return false;
	
	//	Call CommandHandler
	CommandHandlers[comID]();
	
	//	Clear Data index for nextComand
	dataCnt = 0;	
	doExecCommand = false;
	return true;
}


//	===========	Command Handlers	=============
void LedToggle(void)	
{
	LED_Toggle(dataStream[1]);
}

void LedSyclicToggleOn(void)
{
	LED_SyclicInd = dataStream[1];
	MDR_SysTimerStart(SYS_TIMER_PERIOD);
}

void LedSyclicToggleOff(void)
{
	MDR_SysTimerStop();
	LED_Off(LED_SyclicInd);
}

void SysTick_Handler(void)
{
	LED_Toggle(LED_SyclicInd);
}
