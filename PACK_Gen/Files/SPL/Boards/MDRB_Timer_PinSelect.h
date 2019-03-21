#ifndef _MDRB_TIMER_PINSELECT_H
#define _MDRB_TIMER_PINSELECT_H

#include <MDRB_BoardSelect.h>
#include <MDR_Timer.h>


//======================  Выбор пинов ======================
#if   defined(USE_BOARD_VE1)
  //  см. MDRB_1986VE1.h
  
  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH1;
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH1;
  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH2;
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH2;
  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH3;
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH3;
  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH4;
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH4;  
  extern const MDR_Timer_CfgPinGPIO _pinTim1_ETR;
  extern const MDR_Timer_CfgPinGPIO _pinTim1_BRK;

  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH1;
  extern const MDR_Timer_CfgPinGPIO _pinTim2_nCH1;
  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH2;
  extern const MDR_Timer_CfgPinGPIO _pinTim2_nCH2;
  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH3;
  extern const MDR_Timer_CfgPinGPIO _pinTim2_nCH3;
  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH4;
  extern const MDR_Timer_CfgPinGPIO _pinTim2_nCH4;  
  extern const MDR_Timer_CfgPinGPIO _pinTim2_ETR;
  extern const MDR_Timer_CfgPinGPIO _pinTim2_BRK; 

  extern const MDR_Timer_CfgPinGPIO _pinTim3_CH1;
  extern const MDR_Timer_CfgPinGPIO _pinTim3_nCH1;
  extern const MDR_Timer_CfgPinGPIO _pinTim3_CH2;
  extern const MDR_Timer_CfgPinGPIO _pinTim3_nCH2;
  extern const MDR_Timer_CfgPinGPIO _pinTim3_CH3;
  extern const MDR_Timer_CfgPinGPIO _pinTim3_nCH3;
  extern const MDR_Timer_CfgPinGPIO _pinTim3_CH4;
  extern const MDR_Timer_CfgPinGPIO _pinTim3_nCH4;  
  extern const MDR_Timer_CfgPinGPIO _pinTim3_ETR;
  extern const MDR_Timer_CfgPinGPIO _pinTim3_BRK; 
  
  extern const MDR_Timer_CfgPinGPIO _pinTim4_CH1; 
  extern const MDR_Timer_CfgPinGPIO _pinTim4_nCH1; 
  extern const MDR_Timer_CfgPinGPIO _pinTim4_CH2; 
  extern const MDR_Timer_CfgPinGPIO _pinTim4_nCH2; 
  extern const MDR_Timer_CfgPinGPIO _pinTim4_CH3; 
  extern const MDR_Timer_CfgPinGPIO _pinTim4_nCH3; 
  extern const MDR_Timer_CfgPinGPIO _pinTim4_CH4; 
  extern const MDR_Timer_CfgPinGPIO _pinTim4_nCH4; 
  extern const MDR_Timer_CfgPinGPIO _pinTim4_ETR; 
  extern const MDR_Timer_CfgPinGPIO _pinTim4_BRK; 


#elif defined(USE_BOARD_VE3)
  //  см. MDRB_1986VE3.h



#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)

  //    Ucc - XP9_11
  //    GND - XP11_2
  
  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH1;    // A6  - PF0  - XP8_9
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH1;   // A7  - PF7  - XP8_10
  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH2;    // A8  - PF8  - XP8_11
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH2;   // A9  - PF9  - XP8_12
  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH3;    // A10 - PF10 - XP8_13
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH3;   // A11 - PF11 - XP8_14
  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH4;    // A12 - PF12 - XP8_15
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH4;   // A13 - PF13 - XP8_16
  extern const MDR_Timer_CfgPinGPIO _pinTim1_ETR;    // A14 - PF14 - XP8_19
  extern const MDR_Timer_CfgPinGPIO _pinTim1_BRK;    // A15 - PF15 - XP8_20

  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH1;    // D1  - PA1  - XP10_35
  extern const MDR_Timer_CfgPinGPIO _pinTim2_nCH1;   // D2  - PA2  - XP10_36
  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH2;    // D3  - PA3  - XP10_31
  extern const MDR_Timer_CfgPinGPIO _pinTim2_nCH2;   // D4  - PA4  - XP10_32
  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH3;    // D5  - PA5  - XP10_29
  extern const MDR_Timer_CfgPinGPIO _pinTim2_nCH3;   // D8  - PA8  - XP10_28
  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH4;    // D9  - PA9  - XP10_25
  extern const MDR_Timer_CfgPinGPIO _pinTim2_nCH4;   // D10 - PA10 - XP10_26
  extern const MDR_Timer_CfgPinGPIO _pinTim2_ETR;    // D15 - PA12 - XP10_24
  extern const MDR_Timer_CfgPinGPIO _pinTim2_BRK;    // D14 - PA11 - XP10_23

  extern const MDR_Timer_CfgPinGPIO _pinTim3_CH1;    // nWE - PC2  - XP11_12
  extern const MDR_Timer_CfgPinGPIO _pinTim3_nCH1;   // BE0 - PC3  - XP11_5
  extern const MDR_Timer_CfgPinGPIO _pinTim3_CH2;    // BE1 - PC4  - XP11_6
  extern const MDR_Timer_CfgPinGPIO _pinTim3_nCH2;   // BE2 - PC5  - XP11_7
  extern const MDR_Timer_CfgPinGPIO _pinTim3_CH3;    // BE3 - PC6  - XP11_8
  extern const MDR_Timer_CfgPinGPIO _pinTim3_nCH3;   // CLOCK - PC7 - XP11_9
  extern const MDR_Timer_CfgPinGPIO _pinTim3_CH4;    // D23  - PB7  - XP10_11
  extern const MDR_Timer_CfgPinGPIO _pinTim3_nCH4;   // D24  - PB8  - XP10_12
  extern const MDR_Timer_CfgPinGPIO _pinTim3_ETR;    //        PC10 - XP11_30
  extern const MDR_Timer_CfgPinGPIO _pinTim3_BRK;    //        PC11 - XP11_29  
  
#elif defined(USE_BOARD_VE92)
  //  см. MDRB_1986VE92.h
  
  
#elif defined(USE_BOARD_VE93)
  //  см. MDRB_1986VE93.h

  
#elif defined(USE_BOARD_VC1)
  //  см. MDRB_1901VС1.h

  
#elif defined (USE_MDR1986VE4) 

#elif defined (USE_MDR1986VK214) 
                                                                          
  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH1;     // S0  - PA0
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH1;    // S1  - PA1
  extern const MDR_Timer_CfgPinGPIO _pinTim1_ETR;     // S8  - PA8
  extern const MDR_Timer_CfgPinGPIO _pinTim1_BRK;     // S9  - PA9
    
  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH1;     // ADC2 - PC2
  extern const MDR_Timer_CfgPinGPIO _pinTim2_nCH1;    // ADC1 - PC3
  extern const MDR_Timer_CfgPinGPIO _pinTim2_ETR;     // S21  - PC5
  extern const MDR_Timer_CfgPinGPIO _pinTim2_BRK;     // S22  - PC6                                                                           

#elif  defined (USE_MDR1986VK234)

  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH1;    // PA0
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH1;   // PA1
  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH2;    // PA2
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH2;   // PA3
  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH3;    // PA4
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH3;   // PA5
  extern const MDR_Timer_CfgPinGPIO _pinTim1_CH4;    // PA6  
  extern const MDR_Timer_CfgPinGPIO _pinTim1_nCH4;   // PA7    
  extern const MDR_Timer_CfgPinGPIO _pinTim1_ETR;    // PA8
  extern const MDR_Timer_CfgPinGPIO _pinTim1_BRK;    // PA9
    
  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH1;    // PC2
  extern const MDR_Timer_CfgPinGPIO _pinTim2_nCH1;   // PC3
  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH2;    // PB10
  extern const MDR_Timer_CfgPinGPIO _pinTim2_nCH2;   // PB11
  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH3;    // PB12
  extern const MDR_Timer_CfgPinGPIO _pinTim2_nCH3;   // PB13
  extern const MDR_Timer_CfgPinGPIO _pinTim2_CH4;    // PB14
  //  НЕТ _pinTim2_nCH4
  extern const MDR_Timer_CfgPinGPIO _pinTim2_ETR;    // PC6
  extern const MDR_Timer_CfgPinGPIO _pinTim2_BRK;    // PC7

#endif


#endif  //_MDRB_TIMER_PINSELECT_H

