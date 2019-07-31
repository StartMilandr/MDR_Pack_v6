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


#define TEST_ID__SIMPLE_FLASH     "1"
#define TEST_ID__COUNT_TIM_CLOCK  "2"
#define TEST_ID__COUNT_CASCADE    "3"
#define TEST_ID__PULSE            "4"
#define TEST_ID__PWM              "5"
#define TEST_ID__PWM_DTG          "6"
#define TEST_ID__PWM_ETRBRK       "7"
#define TEST_ID__CAP_SIMPLEST     "8"
#define TEST_ID__CAP_PERIOD       "9"
#define TEST_ID__COUNT_CAP        "10"
#define TEST_ID__COUNT_ETR        "11"


//  Time defines for microcontrollers for MaxFreq
#if defined (USE_MDR1986VE4) || defined (USE_MDR1986VK214) || defined (USE_MDR1986VK234)
  #define TIM_BRG_LED       MDR_Div128P_div4
  #define TIM_PSG_LED       1000
  #define TIM_PERIOD_LED    4000
  
  #define TIM_BRG_PWM       MDR_Div128P_div1
  #define TIM_PSG_PWM1      100
  //#define TIM_PSG_PWM2      50
  #define TIM_PERIOD_PWM    900

#else
  #define TIM_BRG_LED       MDR_Div128P_div16
  #define TIM_PSG_LED       1000
  #define TIM_PERIOD_LED    4000

  #define TIM_BRG_PWM       MDR_Div128P_div4
  #define TIM_PSG_PWM1      100
  //#define TIM_PSG_PWM2      50
  #define TIM_PERIOD_PWM    900

#endif


//  Длительность мигания LCD перед его выключением, там где LCD конфликтует с ШИМ.
#define LCD_HIDE_DELAY    2000

//  LEDs Available
#if defined (TIMER3_EXIST) && defined (MDRB_LED_3)
  #define USE_TIMER3
#endif

#ifdef  TIMER4_EXIST
  #define LED_SEL_MAX           MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4
  #define LED_SEL_CAP           MDRB_LED_1 | MDRB_LED_2
  #define START_SYNC_SEL_MAX    TIM1_StartMsk | TIM2_StartMsk | TIM3_StartMsk
#elif defined(USE_TIMER3)
  #define LED_SEL_MAX           MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3
  #define LED_SEL_CAP           MDRB_LED_1 | MDRB_LED_2
  #define START_SYNC_SEL_MAX    TIM1_StartMsk | TIM2_StartMsk | TIM3_StartMsk

#elif defined(MDRB_LED_2)
  #define LED_SEL_MAX           MDRB_LED_1 | MDRB_LED_2
  #define LED_SEL_CAP           MDRB_LED_1 | MDRB_LED_2
  #define START_SYNC_SEL_MAX    TIM1_StartMsk | TIM2_StartMsk  
#else
  #define LED_SEL_MAX           MDRB_LED_1
  #define LED_SEL_CAP           MDRB_LED_1
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

  #define LCD_CONFLICT_TIM
  #define LCD_BLINKY_ENA
  
#elif defined (USE_MDR1986VK234)
  // PWM1: PA0, PA1  ETR: PA8, BRK: PA9
  #define PWM1_SEL_TIM1_CH3
  // PWM2: PC2, PC3
  #define PWM2_SEL_TIM2_CH1
  // CAP:  PB12
  #define CAP_SEL_TIM2_CH3

  //#define LCD_CONFLICT_TIM

#elif defined (USE_MDR1986VE4)
  // PWM1: PC2, PC3  ETR: PC6, BRK: PC7
  #define PWM1_SEL_TIM2_CH1
  // PWM2: PA0, PA1
  #define PWM2_SEL_TIM1_CH1
  // CAP:  PA2  ETR: PA8
  #define CAP_SEL_TIM1_CH2
  
  #define LCD_CONFLICT_TIM

#elif defined (USE_MDR1986VE91)
  // PWM1: PF6, PF7  ETR: PF14, BRK: PF15
  #define PWM1_SEL_TIM1_CH1
  // PWM1: PF8, PF9
  #define PWM1_SEL_TIM1_CH2_EX  
  // PWM2: PA5, PA8
  #define PWM2_SEL_TIM2_CH3
  // CAP:  PC4
  #define CAP_SEL_TIM3_CH2
  
#elif defined (USE_MDR1986VE92)
  // PWM1: PE2 (Comp), PE3 (Left)  ETR: PD5 (X13:10), BRK: PD6 (X13:11)
  #define PWM1_SEL_TIM2_CH3
  // PWM2: PB2 (X13:15), PB3 (X13:16)
  #define PWM2_SEL_TIM3_CH2
  // CAP:  PB0 (X13:13)  ETR: PB4 (X13:17)
  #define CAP_SEL_TIM3_CH1  
   
  #define LCD_CONFLICT_LED
  
#elif defined (USE_MDR1986VE93)
  // PWM1: PA1 (X25:12), PA2 (X25:9)  ETR: - , BRK: -
  #define PWM1_SEL_TIM1_CH1
  // PWM2: PB5 (X24:18), PB6 (X24:19)
  #define PWM2_SEL_TIM3_CH3
  // CAP:  PE0 (Comp_DAC)  ETR: -
  #define CAP_SEL_TIM2_CH1  
  
  #define NO_ETR_PIN  
  #define LCD_CONFLICT_LED
  #define LCD_CONFLICT_TIM

#elif defined (USE_MDR1986VE1)
  // PWM1: PA12, PA13  ETR: PA15, BRK: PA14
  #define PWM1_SEL_TIM4_CH4
  // PWM1: PA8, PA9
  #define PWM1_SEL_TIM4_CH2_EX  
  // PWM2: PE9, PB13
  #define PWM2_SEL_TIM2_CH3
  // CAP:  PB0  ETR: PD12
  #define CAP_SEL_TIM3_CH1
  
#elif defined (USE_MDR1986VE3)
  // PWM1: PI7, PI8  ETR: PI10, BRK: PI9
  #define PWM1_SEL_TIM4_CH4
  // PWM1: PI1, PI2
  #define PWM1_SEL_TIM4_CH1_EX  
  // PWM2: PB6 (LED7), PB7 (LED8)
  #define PWM2_SEL_TIM3_CH4
  // CAP:  PE8 (XP27:27)  ETR: PC1 (XP26:11)
  #define CAP_SEL_TIM2_CH2

#elif defined (USE_MDR1901VC1)
  // PWM1: PB10 (pin 10), PB11 (7)  ETR: PA12 (24), BRK: PA13 (21)  - all in XP33.1 (pin)
  #define PWM1_SEL_TIM1_CH2
  // PWM1: PB4 (16), PB9 (9)  - in XP33.1
  #define PWM1_SEL_TIM1_CH1_EX  
  // PWM2: PF7 (10), PF8 (11) - in XP32.1
  #define PWM2_SEL_TIM3_CH3
  // CAP:  PB1 (17)  ETR: PB9 (9) - in XP33.1
  #define CAP_SEL_TIM2_CH2
  
  #define USE_SECOND_CHANNEL

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

#elif defined (PWM1_SEL_TIM1_CH2)
  #define PWM1_IS_TIM1

  #define PWM1_TIMex            MDR_TIMER1ex
  #define PWM1_TIM              MDR_TIMER1
  #define PWM1_TIM_CH           MDR_TIMER1_CH2
  #define PWM1_PIN_CH           _pinTim1_CH2
  #define PWM1_PIN_nCH          _pinTim1_nCH2
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
  #define PWM1_START_SEL_MSK    TIM2_StartMsk

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

//  --------  Additional channel for PWM1  ------------
#ifdef PWM1_SEL_TIM1_CH2_EX
  #define PWM1_TIM_CH_EX        MDR_TIMER1_CH2
  #define PWM1_PIN_CH_EX        _pinTim1_CH2
  #define PWM1_PIN_nCH_EX       _pinTim1_nCH2

#elif defined (PWM1_SEL_TIM4_CH2_EX)
  #define PWM1_TIM_CH_EX        MDR_TIMER4_CH2
  #define PWM1_PIN_CH_EX        _pinTim4_CH2
  #define PWM1_PIN_nCH_EX       _pinTim4_nCH2
  
#elif defined (PWM1_SEL_TIM1_CH1_EX)
  #define PWM1_TIM_CH_EX        MDR_TIMER1_CH1
  #define PWM1_PIN_CH_EX        _pinTim1_CH1
  #define PWM1_PIN_nCH_EX       _pinTim1_nCH1
  
#endif


//================    PWM2  Timers, channels and pins Definitions  =================

#ifdef PWM2_SEL_TIM1_CH1
  #define PWM2_TIMex            MDR_TIMER1ex
  #define PWM2_TIM              MDR_TIMER1
  #define PWM2_TIM_CH           MDR_TIMER1_CH1
  #define PWM2_PIN_CH           _pinTim1_CH1
  #define PWM2_PIN_nCH          _pinTim1_nCH1
  #define PWM2_START_SEL_MSK    TIM1_StartMsk

#elif defined (PWM2_SEL_TIM1_CH2)
  #define PWM2_TIMex            MDR_TIMER1ex
  #define PWM2_TIM              MDR_TIMER1
  #define PWM2_TIM_CH           MDR_TIMER1_CH2
  #define PWM2_PIN_CH           _pinTim1_CH2
  #define PWM2_PIN_nCH          _pinTim1_nCH2
  #define PWM2_START_SEL_MSK    TIM1_StartMsk

#elif defined (PWM2_SEL_TIM2_CH1)
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

#elif defined (PWM2_SEL_TIM3_CH2)
  #define PWM2_TIMex            MDR_TIMER3ex
  #define PWM2_TIM              MDR_TIMER3
  #define PWM2_TIM_CH           MDR_TIMER3_CH2
  #define PWM2_PIN_CH           _pinTim3_CH2
  #define PWM2_PIN_nCH          _pinTim3_nCH2
  #define PWM2_START_SEL_MSK    TIM3_StartMsk

#elif defined (PWM2_SEL_TIM3_CH3)
  #define PWM2_TIMex            MDR_TIMER3ex
  #define PWM2_TIM              MDR_TIMER3
  #define PWM2_TIM_CH           MDR_TIMER3_CH3
  #define PWM2_PIN_CH           _pinTim3_CH3
  #define PWM2_PIN_nCH          _pinTim3_nCH3
  #define PWM2_START_SEL_MSK    TIM3_StartMsk

#elif defined (PWM2_SEL_TIM3_CH4)
  #define PWM2_TIMex            MDR_TIMER3ex
  #define PWM2_TIM              MDR_TIMER3
  #define PWM2_TIM_CH           MDR_TIMER3_CH4
  #define PWM2_PIN_CH           _pinTim3_CH4
  #define PWM2_PIN_nCH          _pinTim3_nCH4
  #define PWM2_START_SEL_MSK    TIM3_StartMsk
#endif


//================    Capture Timers, channels and pins definitions  =================

#ifdef CAP_SEL_TIM1_CH2
  #define CAP_TIMex            MDR_TIMER1ex
  #define CAP_TIM              MDR_TIMER1
  #define CAP_TIM_CH           MDR_TIMER1_CH2
  #define CAP_START_SEL_MSK    TIM1_StartMsk
  
  #define CAP_PIN_CH           _pinTim1_CH2
  #define CAP_PIN_nCH          _pinTim1_nCH2
  #define CAP_PIN_ETR          _pinTim1_ETR

  #define CAP_EVENT_CH         TIM_Event_CH2
  #define CAP_EVENT_RISE       TIM_FL_CCR_CAP_CH2
  #define CAP_EVENT_FALL       TIM_FL_CCR1_CAP_CH2
  
#elif defined (CAP_SEL_TIM2_CH1)
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
    
#elif defined (CAP_SEL_TIM2_CH2)
  #define CAP_TIMex            MDR_TIMER2ex
  #define CAP_TIM              MDR_TIMER2
  #define CAP_TIM_CH           MDR_TIMER2_CH2
  #define CAP_START_SEL_MSK    TIM2_StartMsk

  #define CAP_PIN_CH           _pinTim2_CH2
  #define CAP_PIN_nCH          _pinTim2_nCH2
  #define CAP_PIN_ETR          _pinTim2_ETR

  #define CAP_EVENT_CH         TIM_Event_CH2
  #define CAP_EVENT_RISE       TIM_FL_CCR_CAP_CH2
  #define CAP_EVENT_FALL       TIM_FL_CCR1_CAP_CH2

#elif defined (CAP_SEL_TIM3_CH3)
  #define CAP_TIMex            MDR_TIMER3ex
  #define CAP_TIM              MDR_TIMER3
  #define CAP_TIM_CH           MDR_TIMER3_CH3
  #define CAP_START_SEL_MSK    TIM3_StartMsk

  #define CAP_PIN_CH           _pinTim3_CH3
  #define CAP_PIN_nCH          _pinTim3_nCH3
  #define CAP_PIN_ETR          _pinTim3_ETR

  #define CAP_EVENT_CH         TIM_Event_CH3
  #define CAP_EVENT_RISE       TIM_FL_CCR_CAP_CH3
  #define CAP_EVENT_FALL       TIM_FL_CCR1_CAP_CH3
#endif

#endif  //_TEST_DEFS_H

