#ifndef _TEST_DEFS_H
#define _TEST_DEFS_H

#include <stdint.h>
#include <MDR_Config.h>

typedef void  (*pTestFunc_void)(void);
  
typedef struct {
  pTestFunc_void            funcInit;
  pTestFunc_void            funcFinit;
  pTestFunc_void            funcChange;
  pTestFunc_void            funcExec;
  pTestFunc_void            funcMainLoop;
  pTestFunc_void            funcHandlerTim1;
  pTestFunc_void            funcHandlerTim2;
  pTestFunc_void            funcHandlerTim3;
  pTestFunc_void            funcHandlerTim4;
} TestInterface;



//  Time defines for microcontrollers for MaxFreq
#if   defined (USE_MDR1986VE1)

#elif defined (USE_MDR1986VE3)

#elif defined (USE_MDR1986VE9x)
  #define TIM_BRG_LED       MDR_BRG_div16
  #define TIM_PSG_LED       1000
  #define TIM_PERIOD_LED    4000

  #define TIM_BRG_PWM       MDR_BRG_div4
  #define TIM_PSG_PWM1      100
  #define TIM_PSG_PWM2      50
  #define TIM_PERIOD_PWM    800

#elif defined (USE_MDR1901VC1)

#elif defined (USE_MDR1986VE4) || defined (USE_MDR1986VK214) || defined (USE_MDR1986VK234)
  #define TIM_BRG_LED       MDR_BRG_div4
  #define TIM_PSG_LED       1000
  #define TIM_PERIOD_LED    4000
  
  #define TIM_BRG_PWM       MDR_BRG_div1
  #define TIM_PSG_PWM1      100
  #define TIM_PSG_PWM2      50
  #define TIM_PERIOD_PWM    900
#endif




//  Длительность мигания LCD перед его выключением, там где LCD конфликтует с ШИМ.
#define LCD_HIDE_DELAY    2000

//  LEDs Available
#ifdef  TIMER3_EXIST
  #define LED_SEL               MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3
  #define START_SYNC_SEL_MAX    TIM1_StartMsk | TIM2_StartMsk | TIM3_StartMsk
#else
  #define LED_SEL               MDRB_LED_1 | MDRB_LED_2
  #define START_SYNC_SEL_MAX    TIM1_StartMsk | TIM2_StartMsk
#endif

#ifdef  TIMER3_EXIST
  #define LED_SEL_MAX           MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4
#else
  #define LED_SEL_MAX           LED_SEL
#endif


#endif  //_TEST_DEFS_H

