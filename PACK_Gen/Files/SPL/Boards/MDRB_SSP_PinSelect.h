#ifndef _MDRB_SSP_PIN_SELECT_H
#define _MDRB_SSP_PIN_SELECT_H

#include <MDR_SSP.h>
#include <MDRB_BoardSelect.h>

#if   defined(USE_BOARD_VE1)
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP2;  
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1; 
                                       
#elif defined(USE_BOARD_VE3)
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP2;                                       
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP4;
  
#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP2;  
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1;
    
#elif defined(USE_BOARD_VE92)
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP2;  
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1;  
                                       
#elif defined(USE_BOARD_VE93)
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1;
                                       
#elif defined(USE_BOARD_VC1)
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP2;  
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1;
                                       
#elif defined (USE_MDR1986VE4)
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1;

#elif defined (USE_MDR1986VK214)
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1;
                                       
#elif defined (USE_MDR1986VK234)
  extern const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1;
#endif


#endif  //_MDRB_SSP_PIN_SELECT_H

