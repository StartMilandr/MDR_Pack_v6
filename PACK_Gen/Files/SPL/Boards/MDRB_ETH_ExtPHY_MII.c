#include <MDR_GPIO.h>
#include <MDR_Funcs.h>
#include "MDRB_ETH_ExtPHY_MII.h"



#ifdef USE_ESila
  // PA9 = CSR_DV, PA16 = MDIO, PA17 = MDC
  #define MDR_MII_A_PINS    MDR_Pin_9 | MDR_Pin_16 | MDR_Pin_17
  // PB7 = TX_EN, PB8 = RXD_0, PB9 = RXD_1, PB12 = TXD_0, PB13 = TXD_1, PB16 = RMII_CLK, PB17 = RX_ERR, PB18 = RESET
  #define MDR_MII_B_PINS    MDR_Pin_7  | MDR_Pin_8  | MDR_Pin_9  | MDR_Pin_12 \
                          | MDR_Pin_13 | MDR_Pin_16 | MDR_Pin_17 | MDR_Pin_18

  void MDR_ETH_ExtPHY_InitPinsMII(void)
  {
    MDR_PinDig_GroupPinCfg groupPinCfg;  
    MDR_Port_InitDigGroupPinCfg(MDR_Off, MDR_PIN_MAXFAST, &groupPinCfg);

    MDR_GPIO_Enable(MDR_GPIO_A);
    MDR_GPIO_Enable(MDR_GPIO_B);
  
    MDR_GPIO_InitDigFunc(MDR_GPIO_A, MDR_MII_A_PINS, MDR_Pin_PullOff, MDR_PIN_FUNC_8, &groupPinCfg);
    MDR_GPIO_InitDigFunc(MDR_GPIO_B, MDR_MII_B_PINS, MDR_Pin_PullOff, MDR_PIN_FUNC_8, &groupPinCfg);
  }
  
  void MDR_ETH_ExtPHY_Reset(uint32_t delayTicks)
  {
    MDR_GPIO_ClearPins(MDR_GPIO_B, MDR_Pin_18);
    MDR_Delay(delayTicks);
    MDR_GPIO_SetPins(MDR_GPIO_B, MDR_Pin_18);    
  }
#endif

