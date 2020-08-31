#include <MDR_1986VE1_MII.h>
#include <MDR_1986VE1_MII_defs.h>
#include <MDR_GPIO.h>
#include "MDR_1986VE1_MII_Config.h"

static void MII_PinsInit(void)
{
  //  PortE
  MDR_Port_ApplyMask applyMask = {
  .MaskCLR = {
    .clrPins = VE1_MII_SEL,       // RXTX, OE, ANALOG, FGEN
    .clrFUNC = VE1_MII_FUNC_CLR,  
    .clrHiLo = VE1_MII_HILO_CLR,  // PD, PULL 
    .clrPWR  = VE1_MII_PWR_CLR, 
    },
  .MaskSET = {
    .RXTX   = 0,
    .OE     = 0,
    .FUNC   = VE1_MII_FUNC_SET,
    .ANALOG = VE1_MII_SEL,
    .PULL   = 0,
    .PD     = 0,
    .PWR    = VE1_MII_PWR_SET,
    .GFEN   = 0,
    }
  };
  
  MDR_GPIO_Enable(VE1_MII_PORT);
  MDR_GPIO_MaskApply(VE1_MII_PORT, &applyMask);  
  
  //  PortF
  MDR_Port_ApplyMask applyMaskPF = {
  .MaskCLR = {
    .clrPins = VE1_MII_PF_SEL,       // RXTX, OE, ANALOG, FGEN
    .clrFUNC = VE1_MII_PF_FUNC_CLR,  
    .clrHiLo = VE1_MII_PF_HILO_CLR,  // PD, PULL 
    .clrPWR  = VE1_MII_PF_PWR_CLR, 
    },
  .MaskSET = {
    .RXTX   = 0,
    .OE     = 0,
    .FUNC   = VE1_MII_PF_FUNC_SET,
    .ANALOG = VE1_MII_PF_SEL,
    .PULL   = 0,
    .PD     = 0,
    .PWR    = VE1_MII_PF_PWR_SET,
    .GFEN   = 0,
    }
  };
  
  MDR_GPIO_Enable(VE1_MII_PF_PORT);
  MDR_GPIO_MaskApply(VE1_MII_PF_PORT, &applyMaskPF);    
}

void MDR_1986VE1_MII_SetPhyClockHSE(void)
{
  MDR_CLOCK->ETH_CLOCK = MDR_MaskClrSet(MDR_CLOCK->ETH_CLOCK,
     MDR_RST_ETH__PHY_BRG_Msk    | MDR_RST_ETH__ETH_BRG_Msk | MDR_RST_ETH__PHY_CLK_EN_Msk | MDR_RST_ETH__ETH_CLK_EN_Msk | MDR_RST_ETH__PHY_CLK_SEL_Msk
   , MDR_ETH_CLK_EN_MASK) 
  | VAL2FLD_Pos(MDR_PHY_HSE, MDR_RST_ETH__PHY_CLK_SEL_Pos);
}

void MDR_1986VE1_MII_Init(void)
{   
  //  Init MAC with internal PHY
  MDR_ETH_MAC_CfgRegs  cfgRegs = MDR_ETH_MAC_INIT_MII(128, MDC_DIV_le160MHz);
  MDR_ETH_InitCfg      initCfg = {
    .cfgRegsMAC = &cfgRegs,
    .phyCfgReg  = ETHCFG1_REG_PHY_CTRL_MII
  };  
  MDR_Eth_Init(MDR_ETH1, &initCfg);  
  //  Reset Internal PHY
  MDR_ETH1->PHY_CTRL = ETHCFG1_REG_PHY_CTRL_MII;  
  //  Enable MII Pins
  MII_PinsInit();
}

