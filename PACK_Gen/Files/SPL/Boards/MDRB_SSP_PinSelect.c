#include <MDRB_SSP_PinSelect.h>

//======================  Выбор пинов ======================
#if   defined(USE_BOARD_VE1)
  //  см. MDRB_1986VE1.h
  //  SSP1 pins
  const MDR_SSP_CfgPinGPIO _pinCLK_SSP1 = {MDRB_SPI1_CLK_PC7_Port, MDRB_SPI1_CLK_PC7_Ind, MDRB_SPI1_CLK_PC7_Func};
  const MDR_SSP_CfgPinGPIO _pinFSS_SSP1 = {MDRB_SPI1_FSS_PC8_Port, MDRB_SPI1_FSS_PC8_Ind, MDRB_SPI1_FSS_PC8_Func};
  const MDR_SSP_CfgPinGPIO _pinRX_SSP1  = {MDRB_SPI1_RX_PC6_Port,  MDRB_SPI1_RX_PC6_Ind,  MDRB_SPI1_RX_PC6_Func};
  const MDR_SSP_CfgPinGPIO _pinTX_SSP1  = {MDRB_SPI1_TX_PC5_Port,  MDRB_SPI1_TX_PC5_Ind,  MDRB_SPI1_TX_PC5_Func};

  //  SSP2 pins
  const MDR_SSP_CfgPinGPIO _pinCLK_SSP2 = {MDRB_SPI2_CLK_PC11_Port, MDRB_SPI2_CLK_PC11_Ind, MDRB_SPI2_CLK_PC11_Func};
  const MDR_SSP_CfgPinGPIO _pinFSS_SSP2 = {MDRB_SPI2_FSS_PC12_Port, MDRB_SPI2_FSS_PC12_Ind, MDRB_SPI2_FSS_PC12_Func};
  const MDR_SSP_CfgPinGPIO _pinRX_SSP2  = {MDRB_SPI2_RX_PC10_Port,  MDRB_SPI2_RX_PC10_Ind,  MDRB_SPI2_RX_PC10_Func};
  const MDR_SSP_CfgPinGPIO _pinTX_SSP2  = {MDRB_SPI2_TX_PC9_Port,   MDRB_SPI2_TX_PC9_Ind,   MDRB_SPI2_TX_PC9_Func};


  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP2 = 
                                     { .pPinCLK = &_pinCLK_SSP2,
                                       .pPinTX  = &_pinTX_SSP2,
                                       .pPinRX  = &_pinRX_SSP2,
                                       .pPinFSS = &_pinFSS_SSP2};
  
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1 = 
                                     { .pPinCLK = &_pinCLK_SSP1,
                                       .pPinTX  = &_pinTX_SSP1,
                                       .pPinRX  = &_pinRX_SSP1,
                                       .pPinFSS = &_pinFSS_SSP1}; 
                                       
#elif defined(USE_BOARD_VE3)
  //  см. MDRB_1986VE3.h

  //  SSP2 pins
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP2 = {MDRB_SPI2_CLK_PC11_Port, MDRB_SPI2_CLK_PC11_Ind, MDRB_SPI2_CLK_PC11_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP2 = {MDRB_SPI2_FSS_PC12_Port, MDRB_SPI2_FSS_PC12_Ind, MDRB_SPI2_FSS_PC12_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP2  = {MDRB_SPI2_RX_PC10_Port,  MDRB_SPI2_RX_PC10_Ind,  MDRB_SPI2_RX_PC10_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP2  = {MDRB_SPI2_TX_PC9_Port,   MDRB_SPI2_TX_PC9_Ind,   MDRB_SPI2_TX_PC9_Func};

  //  SSP4 pins
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP4 = {MDRB_SPI4_CLK_PI12_Port, MDRB_SPI4_CLK_PI12_Ind, MDRB_SPI4_CLK_PI12_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP4 = {MDRB_SPI4_FSS_PI11_Port, MDRB_SPI4_FSS_PI11_Ind, MDRB_SPI4_FSS_PI11_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP4  = {MDRB_SPI4_RX_PI14_Port,  MDRB_SPI4_RX_PI14_Ind,  MDRB_SPI4_RX_PI14_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP4  = {MDRB_SPI4_TX_PI13_Port,  MDRB_SPI4_TX_PI13_Ind,  MDRB_SPI4_TX_PI13_Func};
  
  
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP2 =
                                     { .pPinCLK = &_pinCLK_SSP2,
                                       .pPinTX  = &_pinTX_SSP2,
                                       .pPinRX  = &_pinRX_SSP2,
                                       .pPinFSS = &_pinFSS_SSP2};  
                                     
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP4 =
                                     { .pPinCLK = &_pinCLK_SSP4,
                                       .pPinTX  = &_pinTX_SSP4,
                                       .pPinRX  = &_pinRX_SSP4,
                                       .pPinFSS = &_pinFSS_SSP4};
  
#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)
  //  см. MDRB_1986VE91.h
  //  SSP1 pins
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP1 = {MDRB_SPI1_CLK_PD10_Port, MDRB_SPI1_CLK_PD10_Ind, MDRB_SPI1_CLK_PD10_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP1 = {MDRB_SPI1_FSS_PD9_Port,  MDRB_SPI1_FSS_PD9_Ind,  MDRB_SPI1_FSS_PD9_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP1  = {MDRB_SPI1_RX_PD11_Port,  MDRB_SPI1_RX_PD11_Ind,  MDRB_SPI1_RX_PD11_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP1  = {MDRB_SPI1_TX_PD12_Port,  MDRB_SPI1_TX_PD12_Ind,  MDRB_SPI1_TX_PD12_Func};

  //  SSP2 pins
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP2 = {MDRB_SPI2_CLK_PD5_Port, MDRB_SPI2_CLK_PD5_Ind, MDRB_SPI2_CLK_PD5_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP2 = {MDRB_SPI2_FSS_PD3_Port, MDRB_SPI2_FSS_PD3_Ind, MDRB_SPI2_FSS_PD3_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP2  = {MDRB_SPI2_RX_PD2_Port,  MDRB_SPI2_RX_PD2_Ind,  MDRB_SPI2_RX_PD2_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP2  = {MDRB_SPI2_TX_PD6_Port,  MDRB_SPI2_TX_PD6_Ind,  MDRB_SPI2_TX_PD6_Func};
  
  
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP2 = 
                                     { .pPinCLK = &_pinCLK_SSP2,
                                       .pPinTX  = &_pinTX_SSP2,
                                       .pPinRX  = &_pinRX_SSP2,
                                       .pPinFSS = &_pinFSS_SSP2};  
  
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1 = 
                                     { .pPinCLK = &_pinCLK_SSP1,
                                       .pPinTX  = &_pinTX_SSP1,
                                       .pPinRX  = &_pinRX_SSP1,
                                       .pPinFSS = &_pinFSS_SSP1};
    
#elif defined(USE_BOARD_VE92)
  //  см. MDRB_1986VE92.h
  //  SSP1 pins
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP1 = {MDRB_SPI1_CLK_PF1_Port, MDRB_SPI1_CLK_PF1_Ind, MDRB_SPI1_CLK_PF1_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP1 = {MDRB_SPI1_FSS_PF2_Port, MDRB_SPI1_FSS_PF2_Ind, MDRB_SPI1_FSS_PF2_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP1  = {MDRB_SPI1_RX_PF3_Port,  MDRB_SPI1_RX_PF3_Ind,  MDRB_SPI1_RX_PF3_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP1  = {MDRB_SPI1_TX_PF0_Port,  MDRB_SPI1_TX_PF0_Ind,  MDRB_SPI1_TX_PF0_Func};
    
  //  SSP2 pins
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP2 = {MDRB_SPI2_CLK_PD5_Port, MDRB_SPI2_CLK_PD5_Ind, MDRB_SPI2_CLK_PD5_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP2 = {MDRB_SPI2_FSS_PD3_Port, MDRB_SPI2_FSS_PD3_Ind, MDRB_SPI2_FSS_PD3_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP2  = {MDRB_SPI2_RX_PD2_Port,  MDRB_SPI2_RX_PD2_Ind,  MDRB_SPI2_RX_PD2_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP2  = {MDRB_SPI2_TX_PD6_Port,  MDRB_SPI2_TX_PD6_Ind,  MDRB_SPI2_TX_PD6_Func};

  
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP2 = 
                                     { .pPinCLK = &_pinCLK_SSP2,
                                       .pPinTX  = &_pinTX_SSP2,
                                       .pPinRX  = &_pinRX_SSP2,
                                       .pPinFSS = &_pinFSS_SSP2};  
  
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1 = 
                                     { .pPinCLK = &_pinCLK_SSP1,
                                       .pPinTX  = &_pinTX_SSP1,
                                       .pPinRX  = &_pinRX_SSP1,
                                       .pPinFSS = &_pinFSS_SSP1};  
                                       
#elif defined(USE_BOARD_VE93)
  //  см. MDRB_1986VE93.h
  //  SSP1
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP1  = {MDRB_SPI1_RX_PF3_Port,  MDRB_SPI1_RX_PF3_Ind,  MDRB_SPI1_RX_PF3_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP1  = {MDRB_SPI1_TX_PF0_Port,  MDRB_SPI1_TX_PF0_Ind,  MDRB_SPI1_TX_PF0_Func};  

 
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1 = 
                                     { .pPinCLK = NULL,
                                       .pPinTX  = &_pinTX_SSP1,
                                       .pPinRX  = &_pinRX_SSP1,
                                       .pPinFSS = NULL};
                                       
#elif defined(USE_BOARD_VC1)
  //  см. MDRB_1901VС1.h
  //  SSP1 pins
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP1 = {MDRB_SPI1_CLK_PA14_Port, MDRB_SPI1_CLK_PA14_Ind, MDRB_SPI1_CLK_PA14_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP1 = {MDRB_SPI1_FSS_PA15_Port, MDRB_SPI1_FSS_PA15_Ind, MDRB_SPI1_FSS_PA15_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP1  = {MDRB_SPI1_RX_PA12_Port,  MDRB_SPI1_RX_PA12_Ind,  MDRB_SPI1_RX_PA12_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP1  = {MDRB_SPI1_TX_PA13_Port,  MDRB_SPI1_TX_PA13_Ind,  MDRB_SPI1_TX_PA13_Func};
    
  //  SSP2 pins
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP2 = {MDRB_SPI2_CLK_PA8_Port,  MDRB_SPI2_CLK_PA8_Ind,  MDRB_SPI2_CLK_PA8_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP2 = {MDRB_SPI2_FSS_PA9_Port,  MDRB_SPI2_FSS_PA9_Ind,  MDRB_SPI2_FSS_PA9_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP2  = {MDRB_SPI2_RX_PA11_Port,  MDRB_SPI2_RX_PA11_Ind,  MDRB_SPI2_RX_PA11_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP2  = {MDRB_SPI2_TX_PA10_Port,  MDRB_SPI2_TX_PA10_Ind,  MDRB_SPI2_TX_PA10_Func};

  
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP2 = 
                                     { .pPinCLK = &_pinCLK_SSP2,
                                       .pPinTX  = &_pinTX_SSP2,
                                       .pPinRX  = &_pinRX_SSP2,
                                       .pPinFSS = &_pinFSS_SSP2};  
  
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1 = 
                                     { .pPinCLK = &_pinCLK_SSP1,
                                       .pPinTX  = &_pinTX_SSP1,
                                       .pPinRX  = &_pinRX_SSP1,
                                       .pPinFSS = &_pinFSS_SSP1};

                                       
#elif defined (USE_MDR1986VE4)
  //  см. MDRB_1986VE4.h
  //  SSP1
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP1 = {MDRB_SPI1_CLK_PA13_Port, MDRB_SPI1_CLK_PA13_Ind, MDRB_SPI1_CLK_PA13_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP1 = {MDRB_SPI1_FSS_PA12_Port, MDRB_SPI1_FSS_PA12_Ind, MDRB_SPI1_FSS_PA12_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP1  = {MDRB_SPI1_RX_PA14_Port,  MDRB_SPI1_RX_PA14_Ind,  MDRB_SPI1_RX_PA14_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP1  = {MDRB_SPI1_TX_PA15_Port,  MDRB_SPI1_TX_PA15_Ind,  MDRB_SPI1_TX_PA15_Func};

  
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1 = 
                                     { .pPinCLK = &_pinCLK_SSP1,
                                       .pPinTX  = &_pinTX_SSP1,
                                       .pPinRX  = &_pinRX_SSP1,
                                       .pPinFSS = &_pinFSS_SSP1};                                       

#elif defined (USE_MDR1986VK214)
  //  см. MDRB_1986VK214.h
  //  SSP1
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP1 = {MDRB_SPI1_CLK_PC11_Port, MDRB_SPI1_CLK_PC11_Ind, MDRB_SPI1_CLK_PC11_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP1 = {MDRB_SPI1_FSS_PC10_Port, MDRB_SPI1_FSS_PC10_Ind, MDRB_SPI1_FSS_PC10_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP1  = {MDRB_SPI1_RX_PC12_Port,  MDRB_SPI1_RX_PC12_Ind,  MDRB_SPI1_RX_PC12_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP1  = {MDRB_SPI1_TX_PC13_Port,  MDRB_SPI1_TX_PC13_Ind,  MDRB_SPI1_TX_PC13_Func};

  
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1 = 
                                     { .pPinCLK = &_pinCLK_SSP1,
                                       .pPinTX  = &_pinTX_SSP1,
                                       .pPinRX  = &_pinRX_SSP1,
                                       .pPinFSS = &_pinFSS_SSP1};
                                       
#elif defined (USE_MDR1986VK234)
  //  см. MDRB_1986VK234.h
  //  SSP1
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP1 = {MDRB_SPI1_CLK_PA13_Port, MDRB_SPI1_CLK_PA13_Ind, MDRB_SPI1_CLK_PA13_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP1 = {MDRB_SPI1_FSS_PA12_Port, MDRB_SPI1_FSS_PA12_Ind, MDRB_SPI1_FSS_PA12_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP1  = {MDRB_SPI1_RX_PA14_Port,  MDRB_SPI1_RX_PA14_Ind,  MDRB_SPI1_RX_PA14_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP1  = {MDRB_SPI1_TX_PA15_Port,  MDRB_SPI1_TX_PA15_Ind,  MDRB_SPI1_TX_PA15_Func};

  
  const MDR_SSP_CfgPinsGPIO MDRB_PinsSSP1 = 
                                     { .pPinCLK = &_pinCLK_SSP1,
                                       .pPinTX  = &_pinTX_SSP1,
                                       .pPinRX  = &_pinRX_SSP1,
                                       .pPinFSS = &_pinFSS_SSP1};
#endif
