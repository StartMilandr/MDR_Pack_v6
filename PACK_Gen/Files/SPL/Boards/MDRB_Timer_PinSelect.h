#ifndef _MDRB_TIMER_PINSELECT_H
#define _MDRB_TIMER_PINSELECT_H

#include <MDRB_BoardSelect.h>
#include <MDR_Timer.h>


//======================  Выбор пинов ======================
#if   defined(USE_BOARD_VE1)
  //  см. MDRB_1986VE1.h
  
                                       
#elif defined(USE_BOARD_VE3)
  //  см. MDRB_1986VE3.h



#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)

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
  
#elif defined(USE_BOARD_VE92)
  //  см. MDRB_1986VE92.h
  
  
#elif defined(USE_BOARD_VE93)
  //  см. MDRB_1986VE93.h

  
#elif defined(USE_BOARD_VC1)
  //  см. MDRB_1901VС1.h

  
#elif defined (USE_MDR1986VE4) || defined (USE_MDR1986VK214) || defined (USE_MDR1986VK234)
  //  см. MDRB_1986VE4.h / MDRB_1986VK214.h / MDRB_1986VK234.h  
                                                                           

#endif


#endif  //_MDRB_TIMER_PINSELECT_H

