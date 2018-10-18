#ifndef _MDR_BKP_RTC_H
#define _MDR_BKP_RTC_H

#include "MDR_Config.h"

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
  MDR_CLOCK->MDR_CLK_EN_REG_PER_b.BKP_CLK_EN  = MDR_On;
}

__STATIC_INLINE void MDR_BKP_ClockOff(void)
{
  MDR_CLOCK->MDR_CLK_EN_REG_PER_b.BKP_CLK_EN  = MDR_Off;
}

__STATIC_INLINE void MDR_BKP_SetReg(MDR_BKP_REGs bkpReg, uint32_t value)
{
  MDR_BKP->REG_xx[(uint32_t)bkpReg] = value;
}

__STATIC_INLINE uint32_t MDR_BKP_GetReg(MDR_BKP_REGs bkpReg)
{
  return MDR_BKP->REG_xx[(uint32_t)bkpReg];
}

#endif //_MDR_BKP_RTC_H

