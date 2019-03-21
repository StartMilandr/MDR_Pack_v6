#include "MDRB_Timer_PinSelect.h"

//======================  Выбор пинов ======================
#if   defined(USE_BOARD_VE1)

  const MDR_Timer_CfgPinGPIO _pinTim1_CH1  = {MDR_GPIO_E,  3, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH1 = {MDR_GPIO_B,  8, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim1_CH2  = {MDR_GPIO_E,  4, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH2 = {MDR_GPIO_B, 10, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim1_CH3  = {MDR_GPIO_E,  5, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH3 = {MDR_GPIO_B, 12, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim1_CH4  = {MDR_GPIO_E,  6, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH4 = {MDR_GPIO_B, 14, MDR_PIN_OVER};  
  const MDR_Timer_CfgPinGPIO _pinTim1_ETR  = {MDR_GPIO_C,  0, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_BRK  = {MDR_GPIO_C,  0, MDR_PIN_OVER};

  const MDR_Timer_CfgPinGPIO _pinTim2_CH1  = {MDR_GPIO_E,  7, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH1 = {MDR_GPIO_B,  9, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_CH2  = {MDR_GPIO_E,  8, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH2 = {MDR_GPIO_B, 11, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_CH3  = {MDR_GPIO_E,  9, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH3 = {MDR_GPIO_B, 13, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_CH4  = {MDR_GPIO_E, 10, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH4 = {MDR_GPIO_B, 15, MDR_PIN_OVER};  
  const MDR_Timer_CfgPinGPIO _pinTim2_ETR  = {MDR_GPIO_C,  1, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim2_BRK  = {MDR_GPIO_C,  1, MDR_PIN_OVER}; 

  const MDR_Timer_CfgPinGPIO _pinTim3_CH1  = {MDR_GPIO_B,  0, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH1 = {MDR_GPIO_B,  1, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_CH2  = {MDR_GPIO_B,  2, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH2 = {MDR_GPIO_B,  3, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_CH3  = {MDR_GPIO_B,  4, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH3 = {MDR_GPIO_B,  5, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_CH4  = {MDR_GPIO_B,  6, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH4 = {MDR_GPIO_B,  7, MDR_PIN_OVER};  
  const MDR_Timer_CfgPinGPIO _pinTim3_ETR  = {MDR_GPIO_D, 12, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim3_BRK  = {MDR_GPIO_A,  5, MDR_PIN_ALT}; 
  
  const MDR_Timer_CfgPinGPIO _pinTim4_CH1  = {MDR_GPIO_A,  6, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_nCH1 = {MDR_GPIO_A,  7, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_CH2  = {MDR_GPIO_A,  8, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_nCH2 = {MDR_GPIO_A,  9, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_CH3  = {MDR_GPIO_A, 10, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_nCH3 = {MDR_GPIO_A, 11, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_CH4  = {MDR_GPIO_A, 12, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_nCH4 = {MDR_GPIO_A, 13, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_ETR  = {MDR_GPIO_A, 15, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_BRK  = {MDR_GPIO_A, 14, MDR_PIN_ALT};
                                       
#elif defined(USE_BOARD_VE3)

  const MDR_Timer_CfgPinGPIO _pinTim1_CH1  = {MDR_GPIO_E,  3, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH1 = {MDR_GPIO_B,  8, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim1_CH2  = {MDR_GPIO_E,  4, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH2 = {MDR_GPIO_B, 10, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim1_CH3  = {MDR_GPIO_E,  5, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH3 = {MDR_GPIO_B, 12, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim1_CH4  = {MDR_GPIO_E,  6, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH4 = {MDR_GPIO_B, 14, MDR_PIN_OVER};  
  const MDR_Timer_CfgPinGPIO _pinTim1_ETR  = {MDR_GPIO_C,  0, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_BRK  = {MDR_GPIO_C,  0, MDR_PIN_OVER};

  const MDR_Timer_CfgPinGPIO _pinTim2_CH1  = {MDR_GPIO_E,  7, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH1 = {MDR_GPIO_B,  9, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_CH2  = {MDR_GPIO_E,  8, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH2 = {MDR_GPIO_B, 11, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_CH3  = {MDR_GPIO_E,  9, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH3 = {MDR_GPIO_B, 13, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_CH4  = {MDR_GPIO_E, 10, MDR_PIN_MAIN};
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH4 = {MDR_GPIO_B, 15, MDR_PIN_OVER};  
  const MDR_Timer_CfgPinGPIO _pinTim2_ETR  = {MDR_GPIO_C,  1, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim2_BRK  = {MDR_GPIO_C,  1, MDR_PIN_OVER}; 

  const MDR_Timer_CfgPinGPIO _pinTim3_CH1  = {MDR_GPIO_B,  0, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH1 = {MDR_GPIO_B,  1, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_CH2  = {MDR_GPIO_B,  2, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH2 = {MDR_GPIO_B,  3, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_CH3  = {MDR_GPIO_B,  4, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH3 = {MDR_GPIO_B,  5, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_CH4  = {MDR_GPIO_B,  6, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH4 = {MDR_GPIO_B,  7, MDR_PIN_OVER};  
  const MDR_Timer_CfgPinGPIO _pinTim3_ETR  = {MDR_GPIO_D, 12, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim3_BRK  = {MDR_GPIO_A,  5, MDR_PIN_ALT}; 
  
  const MDR_Timer_CfgPinGPIO _pinTim4_CH1  = {MDR_GPIO_I, 1,  MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_nCH1 = {MDR_GPIO_I, 2,  MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_CH2  = {MDR_GPIO_I, 3,  MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_nCH2 = {MDR_GPIO_I, 4,  MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_CH3  = {MDR_GPIO_I, 5, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_nCH3 = {MDR_GPIO_I, 6, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_CH4  = {MDR_GPIO_I, 7, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_nCH4 = {MDR_GPIO_I, 8, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_ETR  = {MDR_GPIO_I, 10, MDR_PIN_ALT}; 
  const MDR_Timer_CfgPinGPIO _pinTim4_BRK  = {MDR_GPIO_I, 9, MDR_PIN_ALT};  
  
#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)

  //    Ucc - XP9_11
  //    GND - XP11_2
  
  const MDR_Timer_CfgPinGPIO _pinTim1_CH1  = {MDR_GPIO_F, 6,  MDR_PIN_ALT};     // A6  - PF0  - XP8_9
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH1 = {MDR_GPIO_F, 7,  MDR_PIN_ALT};     // A7  - PF7  - XP8_10
  const MDR_Timer_CfgPinGPIO _pinTim1_CH2  = {MDR_GPIO_F, 8,  MDR_PIN_ALT};     // A8  - PF8  - XP8_11
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH2 = {MDR_GPIO_F, 9,  MDR_PIN_ALT};     // A9  - PF9  - XP8_12
  const MDR_Timer_CfgPinGPIO _pinTim1_CH3  = {MDR_GPIO_F, 10, MDR_PIN_ALT};     // A10 - PF10 - XP8_13
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH3 = {MDR_GPIO_F, 11, MDR_PIN_ALT};     // A11 - PF11 - XP8_14
  const MDR_Timer_CfgPinGPIO _pinTim1_CH4  = {MDR_GPIO_F, 12, MDR_PIN_ALT};     // A12 - PF12 - XP8_15
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH4 = {MDR_GPIO_F, 13, MDR_PIN_ALT};     // A13 - PF13 - XP8_16
  const MDR_Timer_CfgPinGPIO _pinTim1_ETR  = {MDR_GPIO_F, 14, MDR_PIN_ALT};     // A14 - PF14 - XP8_19
  const MDR_Timer_CfgPinGPIO _pinTim1_BRK  = {MDR_GPIO_F, 15, MDR_PIN_ALT};     // A15 - PF15 - XP8_20

  const MDR_Timer_CfgPinGPIO _pinTim2_CH1  = {MDR_GPIO_A, 1,  MDR_PIN_OVER};    // D1  - PA1  - XP10_35
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH1 = {MDR_GPIO_A, 2,  MDR_PIN_OVER};    // D2  - PA2  - XP10_36
  const MDR_Timer_CfgPinGPIO _pinTim2_CH2  = {MDR_GPIO_A, 3,  MDR_PIN_OVER};    // D3  - PA3  - XP10_31
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH2 = {MDR_GPIO_A, 4,  MDR_PIN_OVER};    // D4  - PA4  - XP10_32
  const MDR_Timer_CfgPinGPIO _pinTim2_CH3  = {MDR_GPIO_A, 5,  MDR_PIN_OVER};    // D5  - PA5  - XP10_29
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH3 = {MDR_GPIO_A, 8,  MDR_PIN_OVER};    // D8  - PA8  - XP10_28
  const MDR_Timer_CfgPinGPIO _pinTim2_CH4  = {MDR_GPIO_A, 9,  MDR_PIN_OVER};    // D9  - PA9  - XP10_25
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH4 = {MDR_GPIO_A, 10, MDR_PIN_OVER};    // D10 - PA10 - XP10_26
  const MDR_Timer_CfgPinGPIO _pinTim2_ETR  = {MDR_GPIO_A, 12, MDR_PIN_OVER};    // D15 - PA12 - XP10_24
  const MDR_Timer_CfgPinGPIO _pinTim2_BRK  = {MDR_GPIO_A, 11, MDR_PIN_OVER};    // D14 - PA11 - XP10_23

  const MDR_Timer_CfgPinGPIO _pinTim3_CH1  = {MDR_GPIO_C, 2,  MDR_PIN_ALT};     // nWE - PC2  - XP11_12
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH1 = {MDR_GPIO_C, 3,  MDR_PIN_ALT};     // BE0 - PC3  - XP11_5
  const MDR_Timer_CfgPinGPIO _pinTim3_CH2  = {MDR_GPIO_C, 4,  MDR_PIN_ALT};     // BE1 - PC4  - XP11_6
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH2 = {MDR_GPIO_C, 5,  MDR_PIN_ALT};     // BE2 - PC5  - XP11_7
  const MDR_Timer_CfgPinGPIO _pinTim3_CH3  = {MDR_GPIO_C, 6,  MDR_PIN_ALT};     // BE3 - PC6  - XP11_8
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH3 = {MDR_GPIO_C, 7,  MDR_PIN_ALT};     // CLOCK - PC7 - XP11_9
  const MDR_Timer_CfgPinGPIO _pinTim3_CH4  = {MDR_GPIO_B, 7,  MDR_PIN_OVER};    // D23  - PB7  - XP10_11
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH4 = {MDR_GPIO_B, 8,  MDR_PIN_OVER};    // D24  - PB8  - XP10_12
  const MDR_Timer_CfgPinGPIO _pinTim3_ETR  = {MDR_GPIO_C, 10, MDR_PIN_ALT};     //        PC10 - XP11_30
  const MDR_Timer_CfgPinGPIO _pinTim3_BRK  = {MDR_GPIO_C, 11, MDR_PIN_ALT};     //        PC11 - XP11_29
  
#elif defined(USE_BOARD_VE92)
  
  
#elif defined(USE_BOARD_VE93)

  
#elif defined(USE_BOARD_VC1)
  const MDR_Timer_CfgPinGPIO _pinTim1_CH1  = {MDR_GPIO_B, 4,  MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH1 = {MDR_GPIO_B, 9,  MDR_PIN_ALT};  
  const MDR_Timer_CfgPinGPIO _pinTim1_CH2  = {MDR_GPIO_B, 10, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH2 = {MDR_GPIO_B, 11, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_ETR  = {MDR_GPIO_A, 12, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim1_BRK  = {MDR_GPIO_A, 13, MDR_PIN_OVER};  

  const MDR_Timer_CfgPinGPIO _pinTim2_CH2  = {MDR_GPIO_B, 1,  MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_ETR  = {MDR_GPIO_B, 9,  MDR_PIN_OVER};

  const MDR_Timer_CfgPinGPIO _pinTim3_CH3  = {MDR_GPIO_F, 7,  MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH3 = {MDR_GPIO_F, 8,  MDR_PIN_OVER};
  

#elif defined (USE_MDR1986VE4) 
  
#elif defined (USE_MDR1986VK214) 
  
  const MDR_Timer_CfgPinGPIO _pinTim1_CH1  = {MDR_GPIO_A, 0,  MDR_PIN_MAIN};    // S0  - PA0
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH1 = {MDR_GPIO_A, 1,  MDR_PIN_MAIN};    // S1  - PA1
  const MDR_Timer_CfgPinGPIO _pinTim1_ETR  = {MDR_GPIO_A, 8,  MDR_PIN_MAIN};    // S8  - PA8
  const MDR_Timer_CfgPinGPIO _pinTim1_BRK  = {MDR_GPIO_A, 9,  MDR_PIN_MAIN};    // S9  - PA9
    
  const MDR_Timer_CfgPinGPIO _pinTim2_CH1  = {MDR_GPIO_C, 2,  MDR_PIN_MAIN};    // ADC2 - PC2
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH1 = {MDR_GPIO_C, 3,  MDR_PIN_MAIN};    // ADC1 - PC3
  const MDR_Timer_CfgPinGPIO _pinTim2_ETR  = {MDR_GPIO_C, 5,  MDR_PIN_MAIN};    // S21  - PC5
  const MDR_Timer_CfgPinGPIO _pinTim2_BRK  = {MDR_GPIO_C, 6,  MDR_PIN_MAIN};    // S22  - PC6
  
#elif defined (USE_MDR1986VK234)
  
  const MDR_Timer_CfgPinGPIO _pinTim1_CH1  = {MDR_GPIO_A, 0,  MDR_PIN_MAIN};    // PA0
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH1 = {MDR_GPIO_A, 1,  MDR_PIN_MAIN};    // PA1
  const MDR_Timer_CfgPinGPIO _pinTim1_CH2  = {MDR_GPIO_A, 2,  MDR_PIN_MAIN};    // PA2
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH2 = {MDR_GPIO_A, 3,  MDR_PIN_MAIN};    // PA3
  const MDR_Timer_CfgPinGPIO _pinTim1_CH3  = {MDR_GPIO_A, 4,  MDR_PIN_MAIN};    // PA4
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH3 = {MDR_GPIO_A, 5,  MDR_PIN_MAIN};    // PA5
  const MDR_Timer_CfgPinGPIO _pinTim1_CH4  = {MDR_GPIO_A, 6,  MDR_PIN_MAIN};    // PA6  
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH4 = {MDR_GPIO_A, 7,  MDR_PIN_MAIN};    // PA7    
  const MDR_Timer_CfgPinGPIO _pinTim1_ETR  = {MDR_GPIO_A, 8,  MDR_PIN_MAIN};    // PA8
  const MDR_Timer_CfgPinGPIO _pinTim1_BRK  = {MDR_GPIO_A, 9,  MDR_PIN_MAIN};    // PA9
    
  const MDR_Timer_CfgPinGPIO _pinTim2_CH1  = {MDR_GPIO_C, 2,  MDR_PIN_MAIN};    // PC2
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH1 = {MDR_GPIO_C, 3,  MDR_PIN_MAIN};    // PC3
  const MDR_Timer_CfgPinGPIO _pinTim2_CH2  = {MDR_GPIO_B, 10, MDR_PIN_MAIN};    // PB10
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH2 = {MDR_GPIO_B, 11, MDR_PIN_MAIN};    // PB11
  const MDR_Timer_CfgPinGPIO _pinTim2_CH3  = {MDR_GPIO_B, 12, MDR_PIN_MAIN};    // PB12
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH3 = {MDR_GPIO_B, 13, MDR_PIN_MAIN};    // PB13
  const MDR_Timer_CfgPinGPIO _pinTim2_CH4  = {MDR_GPIO_B, 14, MDR_PIN_MAIN};    // PB14
  //  НЕТ _pinTim2_nCH4
  const MDR_Timer_CfgPinGPIO _pinTim2_ETR  = {MDR_GPIO_C, 6,  MDR_PIN_MAIN};    // PC6
  const MDR_Timer_CfgPinGPIO _pinTim2_BRK  = {MDR_GPIO_C, 7,  MDR_PIN_MAIN};    // PC7
  
#endif

