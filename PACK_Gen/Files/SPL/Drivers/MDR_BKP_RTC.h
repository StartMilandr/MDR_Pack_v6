#ifndef _MDR_BKP_RTC_H
#define _MDR_BKP_RTC_H

#include <MDR_Config.h>
#include <stdint.h>

//=====================   BKP   ======================

typedef enum {
    MDR_BKP_REG0  = 0
  , MDR_BKP_REG1  = 1
  , MDR_BKP_REG2  = 2
  , MDR_BKP_REG3  = 3
  , MDR_BKP_REG4  = 4
  , MDR_BKP_REG5  = 5
  , MDR_BKP_REG6  = 6
  , MDR_BKP_REG7  = 7
  , MDR_BKP_REG8  = 8
  , MDR_BKP_REG9  = 9
  , MDR_BKP_REG10 = 10
  , MDR_BKP_REG11 = 11
  , MDR_BKP_REG12 = 12
  , MDR_BKP_REG13 = 13
} MDR_BKP_REGs;

__STATIC_INLINE void MDR_BKP_ClockOn(void)
{
  MDR_CLOCK->MDR_CLK_EN_REG_BKP |= MDR_CLK_EN_BIT_BKP;
}

__STATIC_INLINE void MDR_BKP_ClockOff(void)
{
  MDR_CLOCK->MDR_CLK_EN_REG_BKP &= ~MDR_CLK_EN_BIT_BKP;
}

__STATIC_INLINE void MDR_BKP_SetReg(MDR_BKP_REGs bkpReg, uint32_t value)
{
  MDR_BKP->REG_User[(uint32_t)bkpReg] = value;
}

__STATIC_INLINE uint32_t MDR_BKP_GetReg(MDR_BKP_REGs bkpReg)
{
  return MDR_BKP->REG_User[(uint32_t)bkpReg];
}


//=====================   BKP   ======================

//  Get registers from MDR_RTC_Cfg1.h
typedef struct {
  uint32_t regRTC_CS;
  uint32_t regRTC_Clock;
  uint32_t regBKP0F_MaskSet;
  uint32_t regBKP0F_MaskClr;
} MDR_RTC_CfgRegs;

void MDR_RTC_Init(MDR_RTC_CfgRegs *cfgRegs, uint32_t divToTimeStep_20bit, uint32_t alarmTime);

__STATIC_INLINE void MDR_RTC_NVIC_InitIRQ(uint32_t priority)
{
  NVIC_EnableIRQ(BKP_IRQn);
  NVIC_SetPriority(BKP_IRQn, priority);
}

//  TODO: разобраться, надо ли обнулять регист DIV!?
void MDR_RTC_ReinitInterval(uint32_t fromTime, uint32_t alarmTime);

void MDR_RTC_Start(void);
void MDR_RTC_Stop(void);

__STATIC_INLINE uint32_t MDR_RTC_GetTime(void) { return MDR_BKP->RTC_CNT; }

uint32_t MDR_RTC_GetTimeProt(uint32_t minGap);


#define MDR_RTC_EVENT_CNT_OV      MDR_BKP_RTC_CS_OWF_Msk
#define MDR_RTC_EVENT_CNT         MDR_BKP_RTC_CS_SECF_Msk
#define MDR_RTC_EVENT_ALARM       MDR_BKP_RTC_CS_ALRF_Msk
#define MDR_RTC_EVENT_CNT_OV_IRQ  MDR_BKP_RTC_CS_OWF_IE_Msk
#define MDR_RTC_EVENT_CNT_IRQ     MDR_BKP_RTC_CS_SECF_IE_Msk
#define MDR_RTC_EVENT_ALARM_IRQ   MDR_BKP_RTC_CS_ALRF_IE_Msk

void MDR_RTC_ClearEvents(uint32_t selEvents);

__STATIC_INLINE void MDR_RTC_ClearEventsIRQ_All(void) 
{ 
  MDR_RTC_ClearEvents(MDR_RTC_EVENT_CNT_OV_IRQ | MDR_RTC_EVENT_CNT_IRQ | MDR_RTC_EVENT_ALARM_IRQ); 
}


#endif //_MDR_BKP_RTC_H

