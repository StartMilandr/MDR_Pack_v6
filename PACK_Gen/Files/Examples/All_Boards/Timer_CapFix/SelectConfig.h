#ifndef _TEST_DEFS_H
#define _TEST_DEFS_H

#include <stdint.h>
#include <MDR_Config.h>


//================    PWM Timers, channels and pins Selections  =================

//  Channel Select
#if defined (USE_MDR1986VK214)
  // PWM1: PA0
  #define PWM1_SEL_TIM1_CH1
  // CAP:  PC2
  #define CAP_SEL_TIM2_CH1
  
#elif defined (USE_MDR1986VK234)
  // PWM1: PA4
  #define PWM1_SEL_TIM1_CH3
  // CAP:  PB12
  #define CAP_SEL_TIM2_CH3

#elif defined (USE_MDR1986VE4)
  // PWM1: PC2
  #define PWM1_SEL_TIM2_CH1
  // CAP:  PA2
  #define CAP_SEL_TIM1_CH2

#elif defined (USE_MDR1986VE91)
  // PWM1: PF6 (XP8:9)
  #define PWM1_SEL_TIM1_CH1
  // CAP:  PC4 (XP11:6)
  #define CAP_SEL_TIM3_CH2  

#elif defined (USE_MDR1986VE1)
  // PWM1: PE3
  #define PWM1_SEL_TIM1_CH1
  // CAP:  PB2
  #define CAP_SEL_TIM3_CH2
  
#elif defined (USE_MDR1986VE3)
  // PWM1: PE3 (XP27:22)
  #define PWM1_SEL_TIM1_CH1
  // CAP:  PB2 (LED_3)
  #define CAP_SEL_TIM3_CH2

#elif defined (USE_MDR1901VC1)
  // PWM1: PB10 (D26 - XP33.1:10)
  #define PWM1_SEL_TIM1_CH2
  // CAP:  PB1  (D17 - XP33.1:17)
  #define CAP_SEL_TIM2_CH2
#endif


//================    PWM1  Timers, channels and pins Definitions  =================

#ifdef PWM1_SEL_TIM1_CH1
  #define PWM_IS_TIM1

  #define PWM_TIMex            MDR_TIMER1ex
  #define PWM_TIM              MDR_TIMER1
  #define PWM_TIM_CH           MDR_TIMER1_CH1
  #define PWM_PIN_CH           _pinTim1_CH1
  #define PWM_START_SEL_MSK    TIM1_StartMsk
  
#elif defined (PWM1_SEL_TIM1_CH2)
  #define PWM_IS_TIM1

  #define PWM_TIMex            MDR_TIMER1ex
  #define PWM_TIM              MDR_TIMER1
  #define PWM_TIM_CH           MDR_TIMER1_CH2
  #define PWM_PIN_CH           _pinTim1_CH2
  #define PWM_START_SEL_MSK    TIM1_StartMsk
  
#elif defined (PWM1_SEL_TIM1_CH3)
  #define PWM_IS_TIM1

  #define PWM_TIMex            MDR_TIMER1ex
  #define PWM_TIM              MDR_TIMER1
  #define PWM_TIM_CH           MDR_TIMER1_CH3
  #define PWM_PIN_CH           _pinTim1_CH3
  #define PWM_START_SEL_MSK    TIM1_StartMsk

#elif defined (PWM1_SEL_TIM2_CH1)
  #define PWM_IS_TIM2

  #define PWM_TIMex            MDR_TIMER2ex
  #define PWM_TIM              MDR_TIMER2
  #define PWM_TIM_CH           MDR_TIMER2_CH1
  #define PWM_PIN_CH           _pinTim2_CH1
  #define PWM_START_SEL_MSK    TIM2_StartMsk
  
#elif defined (PWM1_SEL_TIM2_CH3)
  #define PWM_IS_TIM2

  #define PWM_TIMex            MDR_TIMER2ex
  #define PWM_TIM              MDR_TIMER2
  #define PWM_TIM_CH           MDR_TIMER2_CH3
  #define PWM_PIN_CH           _pinTim2_CH3
  #define PWM_START_SEL_MSK    TIM2_StartMsk

#elif defined (PWM1_SEL_TIM4_CH4)
  #define PWM_IS_TIM4

  #define PWM_TIMex            MDR_TIMER4ex
  #define PWM_TIM              MDR_TIMER4
  #define PWM_TIM_CH           MDR_TIMER4_CH4
  #define PWM_PIN_CH           _pinTim4_CH4
  
  #define SYNC_START_UNAVALABLE
#endif

//================    Capture Timers, channels and pins definitions  =================

#ifdef CAP_SEL_TIM1_CH2
  #define CAP_TIMex            MDR_TIMER1ex
  #define CAP_TIM              MDR_TIMER1
  #define CAP_TIM_CH_NEXT      MDR_TIMER1_CH1
  #define CAP_TIM_CH           MDR_TIMER1_CH2  
  #define CAP_START_SEL_MSK    TIM1_StartMsk
  
  #define CAP_PIN_CH           _pinTim1_CH2

  #define CAP_EVENT_CH         TIM_FL_CCR_CAP_CH2
  #define CAP_EVENT_CH_NEXT    TIM_FL_CCR_CAP_CH1
  
#elif defined (CAP_SEL_TIM2_CH1)
  #define CAP_TIMex            MDR_TIMER2ex
  #define CAP_TIM              MDR_TIMER2
  #define CAP_TIM_CH_NEXT      MDR_TIMER2_CH4
  #define CAP_TIM_CH           MDR_TIMER2_CH1
  #define CAP_START_SEL_MSK    TIM2_StartMsk
  
  #define CAP_PIN_CH           _pinTim2_CH1

  #define CAP_EVENT_CH         TIM_FL_CCR_CAP_CH1
  #define CAP_EVENT_CH_NEXT    TIM_FL_CCR_CAP_CH4

#elif defined (CAP_SEL_TIM2_CH3)
  #define CAP_TIMex            MDR_TIMER2ex
  #define CAP_TIM              MDR_TIMER2
  #define CAP_TIM_CH_NEXT      MDR_TIMER2_CH2
  #define CAP_TIM_CH           MDR_TIMER2_CH3
  #define CAP_START_SEL_MSK    TIM2_StartMsk

  #define CAP_PIN_CH           _pinTim2_CH3

  #define CAP_EVENT_CH         TIM_FL_CCR_CAP_CH3
  #define CAP_EVENT_CH_NEXT    TIM_FL_CCR_CAP_CH2
  
#elif defined (CAP_SEL_TIM3_CH1)
  #define CAP_TIMex            MDR_TIMER3ex
  #define CAP_TIM              MDR_TIMER3
  #define CAP_TIM_CH_NEXT      MDR_TIMER3_CH4
  #define CAP_TIM_CH           MDR_TIMER3_CH1
  #define CAP_START_SEL_MSK    TIM3_StartMsk

  #define CAP_PIN_CH           _pinTim3_CH1

  #define CAP_EVENT_CH         TIM_FL_CCR_CAP_CH1
  #define CAP_EVENT_CH_NEXT    TIM_FL_CCR_CAP_CH4
  
#elif defined (CAP_SEL_TIM3_CH2)
  #define CAP_TIMex            MDR_TIMER3ex
  #define CAP_TIM              MDR_TIMER3
  #define CAP_TIM_CH_NEXT      MDR_TIMER3_CH1
  #define CAP_TIM_CH           MDR_TIMER3_CH2
  #define CAP_START_SEL_MSK    TIM3_StartMsk

  #define CAP_PIN_CH           _pinTim3_CH2

  #define CAP_EVENT_CH         TIM_FL_CCR_CAP_CH2
  #define CAP_EVENT_CH_NEXT    TIM_FL_CCR_CAP_CH1
    
#elif defined (CAP_SEL_TIM2_CH2)
  #define CAP_TIMex            MDR_TIMER2ex
  #define CAP_TIM              MDR_TIMER2
  #define CAP_TIM_CH_NEXT      MDR_TIMER2_CH1
  #define CAP_TIM_CH           MDR_TIMER2_CH2
  #define CAP_START_SEL_MSK    TIM2_StartMsk

  #define CAP_PIN_CH           _pinTim2_CH2

  #define CAP_EVENT_CH         TIM_FL_CCR_CAP_CH2
  #define CAP_EVENT_CH_NEXT    TIM_FL_CCR_CAP_CH1

//#elif defined (CAP_SEL_TIM3_CH3)
//  #define CAP_TIMex            MDR_TIMER3ex
//  #define CAP_TIM              MDR_TIMER3
//  #define CAP_TIM_CH_NEXT      MDR_TIMER3_CH2
//  #define CAP_TIM_CH           MDR_TIMER3_CH3
//  #define CAP_START_SEL_MSK    TIM3_StartMsk

//  #define CAP_PIN_CH           _pinTim3_CH3

//  #define CAP_EVENT_CH         TIM_FL_CCR_CAP_CH2
//  #define CAP_EVENT_CH_NEXT    TIM_FL_CCR1_CAP_CH3
#endif

#endif  //_TEST_DEFS_H

