#include <MDR_BKP_RTC.h>
#include <MDR_Funcs.h>

//  Если нет в MDR_Config.h
#ifndef CFG_RTC_ResetTicks
  #define CFG_RTC_ResetTicks  10
#endif

void MDR_RTC_WaitCanWrite(void)
{
  while ((MDR_BKP->RTC_CS & MDR_BKP_RTC_CS_WEC_Msk) != 0);
}

void MDR_RTC_Init(MDR_RTC_CfgRegs *cfgRegs, uint32_t divToTimeStep_20bit, uint32_t alarmTime)
{
  MDR_BKP_ClockOn();
  
  // Set Calibr and Clock Select
  uint32_t regOF = MDR_BKP->REG_0F;
  regOF &= ~(cfgRegs->regBKP0F_MaskClr | MDR_BKP_REG_0F_RTC_EN_Msk | MDR_BKP_REG_0F_RTC_RESET_Msk);
  regOF |=  (cfgRegs->regBKP0F_MaskSet);
  // RTC reset and 
  MDR_BKP->REG_0F = regOF | MDR_BKP_REG_0F_RTC_RESET_Msk;
  MDR_Delay(CFG_RTC_ResetTicks);
  MDR_BKP->REG_0F = regOF;
  
  //  Set HSI/HSE clock divs and enable
  MDR_CLOCK->RTC_CLOCK = cfgRegs->regRTC_Clock;

  //  Apply IQRx_en, 
  MDR_BKP->RTC_CS = cfgRegs->regRTC_CS;
	
	//	Prescaller
  MDR_RTC_WaitCanWrite();
	MDR_BKP->RTC_PRL = divToTimeStep_20bit;
	
	//	CNTR
	MDR_RTC_WaitCanWrite();
	MDR_BKP->RTC_CNT = 0;
	//	ALARM
	MDR_RTC_WaitCanWrite();
  MDR_BKP->RTC_ALRM = alarmTime;
}

void MDR_RTC_ReinitInterval(uint32_t fromTime, uint32_t alarmTime)
{
  //	DIV
	MDR_RTC_WaitCanWrite();
	MDR_BKP->RTC_DIV = 0;   
	//	CNTR
	MDR_RTC_WaitCanWrite();
	MDR_BKP->RTC_CNT = fromTime;
	//	ALARM
	MDR_RTC_WaitCanWrite();
  MDR_BKP->RTC_ALRM = alarmTime;
}

void MDR_RTC_Stop(void)
{
	MDR_RTC_WaitCanWrite();
  MDR_BKP->REG_0F &= ~MDR_BKP_REG_0F_RTC_EN_Msk;  
}

void MDR_RTC_Start(void)
{
	MDR_RTC_WaitCanWrite();
  MDR_BKP->REG_0F |= MDR_BKP_REG_0F_RTC_EN_Msk;  
}

void MDR_RTC_ClearEvents(uint32_t selEvents)
{
  MDR_RTC_WaitCanWrite();
  MDR_BKP->RTC_CS |= selEvents;
}

uint32_t MDR_RTC_GetTimeProt(uint32_t minGap) 
{ 
  uint32_t regCnt;
  uint32_t result;
  do {
    regCnt = MDR_BKP->RTC_CNT;
    result = MDR_BKP->RTC_CNT;
  } while ((result - regCnt) > minGap);
  return result;
}

