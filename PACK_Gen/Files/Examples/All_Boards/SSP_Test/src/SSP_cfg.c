#include "SSP_cfg.h"

MDR_SSP_Config cfgSSP = {
  //  Config
  .DataBits = SSP_DataBits_16,
  .FrameFormat = SSP_Frame_SPI,
  .SPI_Mode = SPI_CPHA0_CPOL0,
  
  // BitRate                        // BitRate = SSP_Clock / (PSR * (1 + SCR))
  .DivSCR_0_255 = 0,                // 0 - 255, Serial Clock Rate
  .DivPSR_2_254 = 14,               // 2 - 254, EVEN ONLY! Clock prescaller
                                    // 14 - делитель, при котором у меня на плате обмены мастера со слейвом проходит успешно
  //  DMA
  .DMA_TX_Enable = MDR_Off,
  .DMA_RX_Enable = MDR_Off
};

MDR_SSP_ConfigEx cfgSSPex = {
  .divSSP_Clock     = MDR_BRG_div1,
  .cfgSSP           = &cfgSSP,
  .activateNVIC_IRQ = true,
  .priorityIRQ      = 1
};

//  ------  Смена количества бит в посылке  ------
uint16_t Cfg_DataMaxValue = 0xFFFF;
void Cfg_NextDataBits(void)
{
  if (cfgSSP.DataBits == MDR_SSP_DATABITS_MAX)
  {
    cfgSSP.DataBits = MDR_SSP_DATABITS_MIN;
    Cfg_DataMaxValue = 0x000F;
  }
  else
  {
    cfgSSP.DataBits++;
    Cfg_DataMaxValue = (Cfg_DataMaxValue << 1) | 1;
  }
}

//  ------  Смена активного режима SPI - CPO и CPH  ------
void Cfg_NextSPI_Mode(void)
{
  if (cfgSSP.SPI_Mode == SPI_CPHA1_CPOL1)
    cfgSSP.SPI_Mode = SPI_CPHA0_CPOL0;
  else
    cfgSSP.SPI_Mode++;
}

//  ------  Смена активного протокола обмена SPI, SSI, Microwire  ------
void Cfg_NextSSP_FrameFormat(void)
{
  //для SSP_Frame_Microwire отдельный тест, т.к. особый протокол
  if (cfgSSP.FrameFormat == SSP_Frame_SSI)
    cfgSSP.FrameFormat = SSP_Frame_SPI;
  else
    cfgSSP.FrameFormat++;  
}

char *Cfg_getActiveFrameName(void)
{
  switch (cfgSSP.FrameFormat) {
    case SSP_Frame_SPI: return "SPI";
    case SSP_Frame_SSI: return "SSI";
    case SSP_Frame_Microwire: return "MCR";
    default: return "Err";
  }  
}


//  ------  Смена активного делителя скорости  ------
//  Этот делитель можно инкрементировать по 2. По +1 нельзя - младший бит не значащий!
#define DIV_INC_STEP     2
//  Чтобы не листать скорость слишком далеко. При соединении RX-TX через резистор 100Ом, успешный обмен при делителе = 6
#define DIV_MAX         30  

void Cfg_NextDIV_PSR_2_254(void)
{
  cfgSSPex.cfgSSP->DivPSR_2_254 += DIV_INC_STEP;
  if (cfgSSPex.cfgSSP->DivPSR_2_254 > DIV_MAX)
    cfgSSPex.cfgSSP->DivPSR_2_254 = 2; 
}


//  ------  Индекс блока SSP - для отображения на LCD  ------
uint32_t Cfg_GetIndexSPI(const MDR_SSP_TypeEx *exSSPx)
{
  if (exSSPx == MDR_SSP1ex)
    return 1;
#ifdef MDR_SSP2    
  else if (exSSPx == MDR_SSP2ex)
    return 2;
#endif
#ifdef MDR_SSP3    
  else if (exSSPx == MDR_SSP3ex)
    return 3;  
#endif
#ifdef MDR_SSP4  
  else if (exSSPx == MDR_SSP4ex)
    return 4;
#endif
  
  return 0;
}
  
//======================  Список доступных блоков SSP ======================

#if defined(USE_BOARD_VE1)
  
  const MDR_SSP_TypeEx  *SSP_List[] = {MDR_SSP1ex, MDR_SSP2ex, MDR_SSP3ex};
  
#elif defined(USE_BOARD_VE3) || defined(USE_BOARD_VC1)

  const MDR_SSP_TypeEx  *SSP_List[] = {MDR_SSP1ex, MDR_SSP2ex, MDR_SSP3ex, MDR_SSP4ex};
  
#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94) || defined(USE_BOARD_VE92) || defined(USE_BOARD_VE93)  

  const MDR_SSP_TypeEx  *SSP_List[] = {MDR_SSP1ex, MDR_SSP2ex};
  
#elif defined(USE_BOARD_VE4) || defined(USE_BOARD_VK214) || defined(USE_BOARD_VK234)
  
  const MDR_SSP_TypeEx  *SSP_List[] = {MDR_SSP1ex};
  
#endif  


uint32_t listLenSSP = sizeof(SSP_List)/sizeof(SSP_List[0]);  
uint8_t  activeIndSSP = 0;

uint8_t NextIndexSSP(void)
{
  ++activeIndSSP;
  if (activeIndSSP >= listLenSSP)
    activeIndSSP = 0;
  
  return activeIndSSP;
}
  
//======================  Выбор пинов ======================
#if   defined(USE_BOARD_VE1)
  //  см. MDRB_1986VE1.h
  //  SSP1 pins
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP1 = {MDRB_SPI1_CLK_PC7_Port, MDRB_SPI1_CLK_PC7_Ind, MDRB_SPI1_CLK_PC7_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP1 = {MDRB_SPI1_FSS_PC8_Port, MDRB_SPI1_FSS_PC8_Ind, MDRB_SPI1_FSS_PC8_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP1  = {MDRB_SPI1_RX_PC6_Port,  MDRB_SPI1_RX_PC6_Ind,  MDRB_SPI1_RX_PC6_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP1  = {MDRB_SPI1_TX_PC5_Port,  MDRB_SPI1_TX_PC5_Ind,  MDRB_SPI1_TX_PC5_Func};

  //  SSP2 pins
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP2 = {MDRB_SPI2_CLK_PC11_Port, MDRB_SPI2_CLK_PC11_Ind, MDRB_SPI2_CLK_PC11_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP2 = {MDRB_SPI2_FSS_PC12_Port, MDRB_SPI2_FSS_PC12_Ind, MDRB_SPI2_FSS_PC12_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP2  = {MDRB_SPI2_RX_PC10_Port,  MDRB_SPI2_RX_PC10_Ind,  MDRB_SPI2_RX_PC10_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP2  = {MDRB_SPI2_TX_PC9_Port,   MDRB_SPI2_TX_PC9_Ind,   MDRB_SPI2_TX_PC9_Func};

  const MDR_SSP_TypeEx * SSP_MASTER = MDR_SSP2ex;
  const MDR_SSP_TypeEx * SSP_SLAVE  = MDR_SSP1ex;

  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Master = 
                                     { .pPinCLK = &_pinCLK_SSP2,
                                       .pPinTX  = &_pinTX_SSP2,
                                       .pPinRX  = &_pinRX_SSP2,
                                       .pPinFSS = &_pinFSS_SSP2};
  
  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Slave = 
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
  
  const MDR_SSP_TypeEx * SSP_MASTER = MDR_SSP4ex;
  const MDR_SSP_TypeEx * SSP_SLAVE  = MDR_SSP2ex;  
  
  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Slave =  //CFG_PinsSSP_Master = 
                                     { .pPinCLK = &_pinCLK_SSP2,
                                       .pPinTX  = &_pinTX_SSP2,
                                       .pPinRX  = &_pinRX_SSP2,
                                       .pPinFSS = &_pinFSS_SSP2};  
                                     
  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Master = // CFG_PinsSSP_Slave = 
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
  
  const MDR_SSP_TypeEx * SSP_MASTER = MDR_SSP2ex;
  const MDR_SSP_TypeEx * SSP_SLAVE  = MDR_SSP1ex;
  
  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Master = 
                                     { .pPinCLK = &_pinCLK_SSP2,
                                       .pPinTX  = &_pinTX_SSP2,
                                       .pPinRX  = &_pinRX_SSP2,
                                       .pPinFSS = &_pinFSS_SSP2};  
  
  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Slave = 
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

  const MDR_SSP_TypeEx * SSP_MASTER = MDR_SSP2ex;
  const MDR_SSP_TypeEx * SSP_SLAVE  = MDR_SSP1ex;  
  
  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Master = 
                                     { .pPinCLK = &_pinCLK_SSP2,
                                       .pPinTX  = &_pinTX_SSP2,
                                       .pPinRX  = &_pinRX_SSP2,
                                       .pPinFSS = &_pinFSS_SSP2};  
  
  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Slave = 
                                     { .pPinCLK = &_pinCLK_SSP1,
                                       .pPinTX  = &_pinTX_SSP1,
                                       .pPinRX  = &_pinRX_SSP1,
                                       .pPinFSS = &_pinFSS_SSP1};  
                                       
#elif defined(USE_BOARD_VE93)
  //  см. MDRB_1986VE93.h
  //  SSP1
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP1  = {MDRB_SPI1_RX_PF3_Port,  MDRB_SPI1_RX_PF3_Ind,  MDRB_SPI1_RX_PF3_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP1  = {MDRB_SPI1_TX_PF0_Port,  MDRB_SPI1_TX_PF0_Ind,  MDRB_SPI1_TX_PF0_Func};  

  const MDR_SSP_TypeEx * SSP_MASTER = MDR_SSP1ex;
 
  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Master = 
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

  const MDR_SSP_TypeEx * SSP_MASTER = MDR_SSP2ex;
  const MDR_SSP_TypeEx * SSP_SLAVE  = MDR_SSP1ex;  
  
  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Master = 
                                     { .pPinCLK = &_pinCLK_SSP2,
                                       .pPinTX  = &_pinTX_SSP2,
                                       .pPinRX  = &_pinRX_SSP2,
                                       .pPinFSS = &_pinFSS_SSP2};  
  
  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Slave = 
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

  const MDR_SSP_TypeEx * SSP_MASTER = MDR_SSP1ex;
  
  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Master = 
                                     { .pPinCLK = &_pinCLK_SSP1,
                                       .pPinTX  = &_pinTX_SSP1,
                                       .pPinRX  = &_pinRX_SSP1,
                                       .pPinFSS = &_pinFSS_SSP1};                                       

#elif defined (USE_MDR1986VK214)
  #define USE_BOARD_VK214
#elif defined (USE_MDR1986VK234)
  //  см. MDRB_1986VK234.h
  //  SSP1
  static const MDR_SSP_CfgPinGPIO _pinCLK_SSP1 = {MDRB_SPI1_CLK_PA13_Port, MDRB_SPI1_CLK_PA13_Ind, MDRB_SPI1_CLK_PA13_Func};
  static const MDR_SSP_CfgPinGPIO _pinFSS_SSP1 = {MDRB_SPI1_FSS_PA12_Port, MDRB_SPI1_FSS_PA12_Ind, MDRB_SPI1_FSS_PA12_Func};
  static const MDR_SSP_CfgPinGPIO _pinRX_SSP1  = {MDRB_SPI1_RX_PA14_Port,  MDRB_SPI1_RX_PA14_Ind,  MDRB_SPI1_RX_PA14_Func};
  static const MDR_SSP_CfgPinGPIO _pinTX_SSP1  = {MDRB_SPI1_TX_PA15_Port,  MDRB_SPI1_TX_PA15_Ind,  MDRB_SPI1_TX_PA15_Func};

  const MDR_SSP_TypeEx * SSP_MASTER = MDR_SSP1ex;
  
  static const MDR_SSP_CfgPinsGPIO CFG_PinsSSP_Master = 
                                     { .pPinCLK = &_pinCLK_SSP1,
                                       .pPinTX  = &_pinTX_SSP1,
                                       .pPinRX  = &_pinRX_SSP1,
                                       .pPinFSS = &_pinFSS_SSP1};
#endif

                                       
#define SSP_PIN_COUNT   4

typedef struct {
  MDR_Port_ApplyMask     applyGPIO_Pins[SSP_PIN_COUNT];
  //  Backup настройки пинов до переключения на функции SSP
  MDR_GPIO_CfgRegs       tempGPIOPins[SSP_PIN_COUNT];
  const MDR_GPIO_Port*   SSP_GPIOPort[SSP_PIN_COUNT];

  uint32_t usedPortCount;
} SSP_ApplyPinMasks;

static SSP_ApplyPinMasks applyPinsMaster, applyPinsSlave;


static void SSP_PrepareCaptureMasks(const MDR_SSP_CfgPinsGPIO *pCFG_PinsSSP2, MDR_PIN_PWR pinsPower, SSP_ApplyPinMasks *pinMasks)
{
  uint32_t i;
  uint32_t portInd;
  MDR_PinDig_PermRegs pinsPermRegs;
  
  if (pCFG_PinsSSP2 == NULL)
    return;
  
  //  Обнуление настроечный масок
  for (i = 0; i < SSP_PIN_COUNT; ++i)
    MDR_Port_MaskClear(&pinMasks->applyGPIO_Pins[i]);  
  
  //  Базовые настройки пинов
  MDR_GPIO_InitDigPermRegs(MDR_PIN_PullPush, pinsPower, MDR_Off, MDR_Off, &pinsPermRegs);
  
  //  Формирование конфигурационных масок AND и OR 
  //  CLK
  if (pCFG_PinsSSP2->pPinCLK != NULL)
  {
    portInd = 0;
    pinMasks->SSP_GPIOPort[portInd] = pCFG_PinsSSP2->pPinCLK->portGPIO;
    MDR_GPIO_ClockOn(pCFG_PinsSSP2->pPinCLK->portGPIO);
    MDR_GPIO_MaskAddPin(pCFG_PinsSSP2->pPinCLK->pinIndex, MDR_Pin_In, pCFG_PinsSSP2->pPinCLK->pinFunc, &pinsPermRegs, &pinMasks->applyGPIO_Pins[portInd]);
  }
  
  //  TX
  if (pCFG_PinsSSP2->pPinTX != NULL)
  {
    if (pCFG_PinsSSP2->pPinTX->portGPIO != pinMasks->SSP_GPIOPort[0])
    {
      portInd = 0;
      pinMasks->SSP_GPIOPort[portInd] = pCFG_PinsSSP2->pPinTX->portGPIO;
      MDR_GPIO_ClockOn(pCFG_PinsSSP2->pPinTX->portGPIO);
    }
    MDR_GPIO_MaskAddPin(pCFG_PinsSSP2->pPinTX->pinIndex, MDR_Pin_In, pCFG_PinsSSP2->pPinTX->pinFunc, &pinsPermRegs, &pinMasks->applyGPIO_Pins[portInd]);
  }
  
  // RX
  if (pCFG_PinsSSP2->pPinRX != NULL)
  {
    if (pCFG_PinsSSP2->pPinRX->portGPIO == pinMasks->SSP_GPIOPort[0])
      portInd = 0;
    else if (pCFG_PinsSSP2->pPinRX->portGPIO == pinMasks->SSP_GPIOPort[1])
      portInd = 1;
    else
    {
      portInd = 2;
      pinMasks->SSP_GPIOPort[portInd] = pCFG_PinsSSP2->pPinRX->portGPIO;
      MDR_GPIO_ClockOn(pCFG_PinsSSP2->pPinRX->portGPIO);
    }
    MDR_GPIO_MaskAddPin(pCFG_PinsSSP2->pPinRX->pinIndex, MDR_Pin_In, pCFG_PinsSSP2->pPinRX->pinFunc, &pinsPermRegs, &pinMasks->applyGPIO_Pins[portInd]);
  }
  
  // FSS
  if (pCFG_PinsSSP2->pPinFSS != NULL)
  {
    if (pCFG_PinsSSP2->pPinFSS->portGPIO == pinMasks->SSP_GPIOPort[0])
      portInd = 0;
    else if (pCFG_PinsSSP2->pPinFSS->portGPIO == pinMasks->SSP_GPIOPort[1])
      portInd = 1;
    else if (pCFG_PinsSSP2->pPinFSS->portGPIO == pinMasks->SSP_GPIOPort[2])
      portInd = 2;    
    else
    {
      portInd = 3;
      pinMasks->SSP_GPIOPort[portInd] = pCFG_PinsSSP2->pPinFSS->portGPIO;
      MDR_GPIO_ClockOn(pCFG_PinsSSP2->pPinFSS->portGPIO);
    }
    MDR_GPIO_MaskAddPin(pCFG_PinsSSP2->pPinFSS->pinIndex, MDR_Pin_In, pCFG_PinsSSP2->pPinFSS->pinFunc, &pinsPermRegs, &pinMasks->applyGPIO_Pins[portInd]);
  }
  
  pinMasks->usedPortCount = portInd + 1;
}
	
void Cfg_SSP_CapturePinsInit(MDR_PIN_PWR pinsPower)
{
  SSP_PrepareCaptureMasks(&CFG_PinsSSP_Master, pinsPower, &applyPinsMaster);
#ifndef BDR_NO_SLAVE_SSP  
  SSP_PrepareCaptureMasks(&CFG_PinsSSP_Slave, pinsPower, &applyPinsSlave);
#endif
}

void Cfg_SSP_Master_CapturePins(void)
{
  uint32_t i;
  
  for (i = 0; i < applyPinsMaster.usedPortCount; ++i)
  {
    MDR_GPIO_ReadRegs(applyPinsMaster.SSP_GPIOPort[i], &applyPinsMaster.tempGPIOPins[i]);
    MDR_GPIO_MaskApplyEx(applyPinsMaster.SSP_GPIOPort[i], &applyPinsMaster.applyGPIO_Pins[i], &applyPinsMaster.tempGPIOPins[i]);
  } 
}

void Cfg_SSP_Master_ReleasePins(void)
{
  uint32_t i;
  
  for (i = 0; i < applyPinsMaster.usedPortCount; ++i)
  {
    MDR_GPIO_WriteRegs(applyPinsMaster.SSP_GPIOPort[i], &applyPinsMaster.tempGPIOPins[i]);
  } 
}

void Cfg_SSP_Slave_CapturePins(void)
{
  uint32_t i;
  
  for (i = 0; i < applyPinsSlave.usedPortCount; ++i)
  {
    MDR_GPIO_ReadRegs(applyPinsSlave.SSP_GPIOPort[i], &applyPinsSlave.tempGPIOPins[i]);
    MDR_GPIO_MaskApplyEx(applyPinsSlave.SSP_GPIOPort[i], &applyPinsSlave.applyGPIO_Pins[i], &applyPinsSlave.tempGPIOPins[i]);
  } 
}

void Cfg_SSP_Slave_ReleasePins(void)
{
  uint32_t i;
  
  for (i = 0; i < applyPinsSlave.usedPortCount; ++i)
  {
    MDR_GPIO_WriteRegs(applyPinsSlave.SSP_GPIOPort[i], &applyPinsSlave.tempGPIOPins[i]);
  } 
}



