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
#if defined (USE_MDR1986VE4) || defined (USE_MDR1986VK214) || defined (USE_MDR1986VK234)
  #define TIM_BRG_LED       MDR_BRG_div4
  #define TIM_PSG_LED       1000
  #define TIM_PERIOD_LED    4000
  
  #define TIM_BRG_PWM       MDR_BRG_div1
  #define TIM_PSG_PWM1      100
  //#define TIM_PSG_PWM2      50
  #define TIM_PERIOD_PWM    900

#else
  #define TIM_BRG_LED       MDR_BRG_div16
  #define TIM_PSG_LED       1000
  #define TIM_PERIOD_LED    4000

  #define TIM_BRG_PWM       MDR_BRG_div4
  #define TIM_PSG_PWM1      100
  //#define TIM_PSG_PWM2      50
  #define TIM_PERIOD_PWM    900

#endif




//  Длительность мигания LCD перед его выключением, там где LCD конфликтует с ШИМ.
#define LCD_HIDE_DELAY    2000

//  LEDs Available
#ifdef  TIMER4_EXIST
  #define LED_SEL               MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4
  #define START_SYNC_SEL_MAX    TIM1_StartMsk | TIM2_StartMsk | TIM3_StartMsk
#elif defined(TIMER3_EXIST)
  #define LED_SEL               MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3
  #define START_SYNC_SEL_MAX    TIM1_StartMsk | TIM2_StartMsk | TIM3_StartMsk
#else
  #define LED_SEL               MDRB_LED_1 | MDRB_LED_2
  #define START_SYNC_SEL_MAX    TIM1_StartMsk | TIM2_StartMsk
#endif


//================    PWM Timers, channels and pins Selections  =================

//  Channel Select
#if defined (USE_MDR1986VK214)
  // PWM1: PA0, PA1  ETR: PA8, BRK: PA9
  #define PWM1_SEL_TIM1_CH1
  // PWM2: PC2, PC3
  #define PWM2_SEL_TIM2_CH1  
  // CAP:  PC2
  #define CAP_SEL_TIM2_CH1

  #define LCD_CONFLICT
  
#elif defined (USE_MDR1986VK234)
  // PWM1: PA0, PA1  ETR: PA8, BRK: PA9
  #define PWM1_SEL_TIM1_CH3
  // PWM2: PC2, PC3
  #define PWM2_SEL_TIM2_CH1
  // CAP:  PB12
  #define CAP_SEL_TIM2_CH3

  //#define LCD_CONFLICT

#elif defined (USE_MDR1986VE91)
  // PWM1: PF6, PF7  ETR: PF14, BRK: PF15
  #define PWM1_SEL_TIM1_CH1
  // PWM1: PF8, PF9
  #define PWM1_SEL_TIM1_CH2_EX  
  // PWM2: PA5, PA8
  #define PWM2_SEL_TIM2_CH3
  // CAP:  PC4
  #define CAP_SEL_TIM3_CH2

#elif defined (USE_MDR1986VE1)
  // PWM1: PA12, PA13  ETR: PA15, BRK: PA14
  #define PWM1_SEL_TIM4_CH4
  // PWM1: PA8, PA9
  #define PWM1_SEL_TIM4_CH2_EX  
  // PWM2: PE9, PB13
  #define PWM2_SEL_TIM2_CH3
  // CAP:  PB0  ETR: PD12
  #define CAP_SEL_TIM3_CH1
#endif


//================    PWM1  Timers, channels and pins Definitions  =================

#ifdef PWM1_SEL_TIM1_CH1
  #define PWM1_IS_TIM1

  #define PWM1_TIMex            MDR_TIMER1ex
  #define PWM1_TIM              MDR_TIMER1
  #define PWM1_TIM_CH           MDR_TIMER1_CH1
  #define PWM1_PIN_CH           _pinTim1_CH1
  #define PWM1_PIN_nCH          _pinTim1_nCH1
  #define PWM1_START_SEL_MSK    TIM1_StartMsk
  
  #define PWM1_PIN_ETR          _pinTim1_ETR
  #define PWM1_PIN_BRK          _pinTim1_BRK

#elif defined (PWM1_SEL_TIM1_CH3)
  #define PWM1_IS_TIM1

  #define PWM1_TIMex            MDR_TIMER1ex
  #define PWM1_TIM              MDR_TIMER1
  #define PWM1_TIM_CH           MDR_TIMER1_CH3
  #define PWM1_PIN_CH           _pinTim1_CH3
  #define PWM1_PIN_nCH          _pinTim1_nCH3
  #define PWM1_START_SEL_MSK    TIM1_StartMsk

  #define PWM1_PIN_ETR          _pinTim1_ETR
  #define PWM1_PIN_BRK          _pinTim1_BRK

#elif defined (PWM1_SEL_TIM2_CH1)
  #define PWM1_IS_TIM2

  #define PWM1_TIMex            MDR_TIMER2ex
  #define PWM1_TIM              MDR_TIMER2
  #define PWM1_TIM_CH           MDR_TIMER2_CH1
  #define PWM1_PIN_CH           _pinTim2_CH1
  #define PWM1_PIN_nCH          _pinTim2_nCH1
  #define PWM1_START_SEL_MSK    TIM2_StartMsk
  
  #define PWM1_PIN_ETR          _pinTim2_ETR
  #define PWM1_PIN_BRK          _pinTim2_BRK

#elif defined (PWM1_SEL_TIM2_CH3)
  #define PWM1_IS_TIM2

  #define PWM1_TIMex            MDR_TIMER2ex
  #define PWM1_TIM              MDR_TIMER2
  #define PWM1_TIM_CH           MDR_TIMER2_CH3
  #define PWM1_PIN_CH           _pinTim2_CH3
  #define PWM1_PIN_nCH          _pinTim2_nCH3
  #define PWM1_START_SEL_MSK    TIM1_StartMsk

  #define PWM1_PIN_ETR          _pinTim2_ETR
  #define PWM1_PIN_BRK          _pinTim2_BRK

#elif defined (PWM1_SEL_TIM4_CH4)
  #define PWM1_IS_TIM4

  #define PWM1_TIMex            MDR_TIMER4ex
  #define PWM1_TIM              MDR_TIMER4
  #define PWM1_TIM_CH           MDR_TIMER4_CH4
  #define PWM1_PIN_CH           _pinTim4_CH4
  #define PWM1_PIN_nCH          _pinTim4_nCH4
  
  //#define PWM1_START_SEL_MSK    TIM1_StartMsk
  #define SYNC_START_UNAVALABLE

  #define PWM1_PIN_ETR          _pinTim4_ETR
  #define PWM1_PIN_BRK          _pinTim4_BRK
#endif

//  Additional channel for PWM1
#ifdef PWM1_SEL_TIM1_CH2_EX
  #define PWM1_TIM_CH_EX        MDR_TIMER1_CH2
  #define PWM1_PIN_CH_EX        _pinTim1_CH2
  #define PWM1_PIN_nCH_EX       _pinTim1_nCH2

#elif defined (PWM1_SEL_TIM4_CH2_EX)
  #define PWM1_TIM_CH_EX        MDR_TIMER4_CH2
  #define PWM1_PIN_CH_EX        _pinTim4_CH2
  #define PWM1_PIN_nCH_EX       _pinTim4_nCH2
#endif


//================    PWM2  Timers, channels and pins Definitions  =================
#ifdef PWM2_SEL_TIM2_CH1
  #define PWM2_TIMex            MDR_TIMER2ex
  #define PWM2_TIM              MDR_TIMER2
  #define PWM2_TIM_CH           MDR_TIMER2_CH1
  #define PWM2_PIN_CH           _pinTim2_CH1
  #define PWM2_PIN_nCH          _pinTim2_nCH1
  #define PWM2_START_SEL_MSK    TIM2_StartMsk

#elif defined (PWM2_SEL_TIM2_CH3)
  #define PWM2_TIMex            MDR_TIMER2ex
  #define PWM2_TIM              MDR_TIMER2
  #define PWM2_TIM_CH           MDR_TIMER2_CH3
  #define PWM2_PIN_CH           _pinTim2_CH3
  #define PWM2_PIN_nCH          _pinTim2_nCH3
  #define PWM2_START_SEL_MSK    TIM2_StartMsk

#elif defined (PWM2_SEL_TIM1_CH2)
#elif defined (PWM2_SEL_TIM1_CH2)
#endif


//================    Capture Timers, channels and pins definitions  =================

#ifdef CAP_SEL_TIM2_CH1
  #define CAP_TIMex            MDR_TIMER2ex
  #define CAP_TIM              MDR_TIMER2
  #define CAP_TIM_CH           MDR_TIMER2_CH1
  #define CAP_START_SEL_MSK    TIM2_StartMsk
  
  #define CAP_PIN_CH           _pinTim2_CH1
  #define CAP_PIN_nCH          _pinTim2_nCH1
  #define CAP_PIN_ETR          _pinTim2_ETR

  #define CAP_EVENT_CH         TIM_Event_CH1
  #define CAP_EVENT_RISE       TIM_FL_CCR_CAP_CH1
  #define CAP_EVENT_FALL       TIM_FL_CCR1_CAP_CH1
 

#elif defined (CAP_SEL_TIM2_CH3)
  #define CAP_TIMex            MDR_TIMER2ex
  #define CAP_TIM              MDR_TIMER2
  #define CAP_TIM_CH           MDR_TIMER2_CH3
  #define CAP_START_SEL_MSK    TIM2_StartMsk

  #define CAP_PIN_CH           _pinTim2_CH3
  #define CAP_PIN_nCH          _pinTim2_nCH3
  #define CAP_PIN_ETR          _pinTim2_ETR

  #define CAP_EVENT_CH         TIM_Event_CH3
  #define CAP_EVENT_RISE       TIM_FL_CCR_CAP_CH3
  #define CAP_EVENT_FALL       TIM_FL_CCR1_CAP_CH3

#elif defined (CAP_SEL_TIM3_CH2)
  #define CAP_TIMex            MDR_TIMER3ex
  #define CAP_TIM              MDR_TIMER3
  #define CAP_TIM_CH           MDR_TIMER3_CH2
  #define CAP_START_SEL_MSK    TIM3_StartMsk

  #define CAP_PIN_CH           _pinTim3_CH2
  #define CAP_PIN_nCH          _pinTim3_nCH2
  #define CAP_PIN_ETR          _pinTim3_ETR

  #define CAP_EVENT_CH         TIM_Event_CH2
  #define CAP_EVENT_RISE       TIM_FL_CCR_CAP_CH2
  #define CAP_EVENT_FALL       TIM_FL_CCR1_CAP_CH2
  
#elif defined (CAP_SEL_TIM3_CH1)
  #define CAP_TIMex            MDR_TIMER3ex
  #define CAP_TIM              MDR_TIMER3
  #define CAP_TIM_CH           MDR_TIMER3_CH1
  #define CAP_START_SEL_MSK    TIM3_StartMsk

  #define CAP_PIN_CH           _pinTim3_CH1
  #define CAP_PIN_nCH          _pinTim3_nCH1
  #define CAP_PIN_ETR          _pinTim3_ETR

  #define CAP_EVENT_CH         TIM_Event_CH1
  #define CAP_EVENT_RISE       TIM_FL_CCR_CAP_CH1
  #define CAP_EVENT_FALL       TIM_FL_CCR1_CAP_CH1


#endif

#endif  //_TEST_DEFS_H

