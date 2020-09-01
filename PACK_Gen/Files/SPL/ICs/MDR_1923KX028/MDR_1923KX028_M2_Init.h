#ifndef MDR_1923KX029_MODE2_INIT_H
#define MDR_1923KX029_MODE2_INIT_H

#include <MDR_Config.h>
#include <MDR_1923KX028.h>
#include <MDR_1923KX028_AXI_defs.h>
#include <MDR_1923KX028_Config.h>
#include <MDR_1923KX028_GlobConst.h>

//===================   Host ===================
void MDR_KX028_M2_TMU_InitTailDropGPI(MDR_KX028_GPI_e gpi, uint16_t maxFrameInHostQueue, uint32_t waitCyclesMax);

__STATIC_INLINE void MDR_KX028_M2_HostPort_InitTailDrop(uint16_t maxFrameInHostQueue, uint32_t waitCyclesMax)
{
  MDR_KX028_M2_TMU_InitTailDropGPI(KX028_HGPI, maxFrameInHostQueue, waitCyclesMax);
}

//===================   Init EMAC blocks ===================
void MDR_KX028_InitEMAC(MDR_KX028_EMAC_e emac, uint32_t netCfgReg);

//  FullDuplex
__STATIC_INLINE void MDR_KX028_InitEMAC_GMII_FD_1G_def(MDR_KX028_EMAC_e emac)
{ MDR_KX028_InitEMAC(emac, CFG_EMAC_NETCFG_GMII_FD_1G); }

__STATIC_INLINE void MDR_KX028_InitEMAC_MII_FD_100M_def(MDR_KX028_EMAC_e emac)
{ MDR_KX028_InitEMAC(emac, CFG_EMAC_NETCFG_MII_FD_100M); }

__STATIC_INLINE void MDR_KX028_InitEMAC_MII_FD_10M_def(MDR_KX028_EMAC_e emac)
{ MDR_KX028_InitEMAC(emac, CFG_EMAC_NETCFG_MII_FD_10M); }


// HalfDuplex
__STATIC_INLINE void MDR_KX028_InitEMAC_MII_HD_100M_def(MDR_KX028_EMAC_e emac)
{ MDR_KX028_InitEMAC(emac, CFG_EMAC_NETCFG_MII_HD_100M); }

__STATIC_INLINE void MDR_KX028_InitEMAC_MII_HD_10M_def(MDR_KX028_EMAC_e emac)
{ MDR_KX028_InitEMAC(emac, CFG_EMAC_NETCFG_MII_HD_10M); }


//  Full Duplex SGMII
__STATIC_INLINE void MDR_KX028_InitEMAC_SGMII_FD_1G_def(MDR_KX028_EMAC_e emac)
{ MDR_KX028_InitEMAC(emac, CFG_EMAC_NETCFG_SGMII_FD_1G); }

__STATIC_INLINE void MDR_KX028_InitEMAC_SGMII_FD_100M_def(MDR_KX028_EMAC_e emac)
{ MDR_KX028_InitEMAC(emac, CFG_EMAC_NETCFG_SGMII_FD_100M); }

__STATIC_INLINE void MDR_KX028_InitEMAC_SGMII_FD_10M_def(MDR_KX028_EMAC_e emac)
{ MDR_KX028_InitEMAC(emac, CFG_EMAC_NETCFG_SGMII_FD_10M); }


//  Hold EMAC in default state after reset
__STATIC_INLINE void MDR_KX028_InitEMAC_None(MDR_KX028_EMAC_e emac)
{ MDR_KX028_WriteAXI(MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_CTRL, AXI_EMAC_CTRL_PORT_DIS_Msk); }


void MDR_KX028_WritePortStruct(MDR_KX028_EMAC_e emac, uint32_t regClassStruct1, uint32_t regClassStruct2 );
void MDR_KX028_InitEGPI(MDR_KX028_EMAC_e emac);
void MDR_KX028_InitETGPI(MDR_KX028_EMAC_e emac);

//  EMAC GEM GXL timer increment register (0x01DC) count value has to be configured as 20 for 50Mhz
__STATIC_INLINE void MDR_KX028_InitEMAC_TSU(MDR_KX028_EMAC_e emac)
{ MDR_KX028_WriteAXI(MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_TSU_TIM_INC, CFG_TSU_INC_PER_1NS); }


void MDR_KX028_InitEMAC_GEM(MDR_KX028_EMAC_e emac);

//===================   Init other blocks ===================
//void MDR_KX028_SysSoftReset(MDR_KX028_DelayMs DelayFunc);

void MDR_KX028_InitBMU1(MDR_KX028_DelayMs DelayFunc);
void MDR_KX028_InitBMU2(MDR_KX028_DelayMs DelayFunc);
void MDR_KX028_InitHGPI(void);
void MDR_KX028_InitHIF(void);
void MDR_KX028_InitClassHW1(void);
void MDR_KX028_InitClassHW2(void);
void MDR_KX028_InitTMU(void);

//  Additional initialization - from driver (not needed by specification) - TODO check!
void MDR_KX028_InitClassHW1_Ex(void);
void MDR_KX028_InitClassHW2_Ex(void);
void MDR_KX028_InitHGPI_Ex(void);
void MDR_KX028_InitEGPI_Ex(MDR_KX028_EMAC_e emac);
void MDR_KX028_InitETGPI_Ex(MDR_KX028_EMAC_e emac);
void MDR_KX028_InitTMU_Ex(void);
void MDR_KX028_InitHIF_Ex(void);
void MDR_KX028_InitEMAC_ex(MDR_KX028_EMAC_e emac);


__STATIC_INLINE void MDR_KX028_InitBMU_GPI_TMU_CLASS(MDR_KX028_DelayMs DelayFunc)
{
  MDR_KX028_InitBMU1(DelayFunc);
  MDR_KX028_InitBMU2(DelayFunc);
  MDR_KX028_InitHGPI();
  MDR_KX028_InitHIF();
  MDR_KX028_InitClassHW1();
  MDR_KX028_InitClassHW2();
  MDR_KX028_InitTMU();
}

__STATIC_INLINE void MDR_KX028_InitBMU_GPI_TMU_CLASS_ex(MDR_KX028_DelayMs DelayFunc)
{
  MDR_KX028_InitClassHW1_Ex();
  MDR_KX028_InitClassHW2_Ex();
  MDR_KX028_InitHGPI_Ex();
  MDR_KX028_InitTMU_Ex();
  MDR_KX028_InitHIF_Ex();
  
  MDR_KX028_EMAC_e emac;
  for (emac = KX028_EMAC1; emac < KX028_EMAC_NUMS; ++emac)
  {
    MDR_KX028_InitEGPI_Ex(emac);
    MDR_KX028_InitETGPI_Ex(emac);
  }
}

__STATIC_INLINE void MDR_KX028_InitAll_BeforeEMAC(MDR_KX028_DelayMs DelayFunc)
{
  MDR_KX028_InitBMU1(DelayFunc);
  MDR_KX028_InitBMU2(DelayFunc);
}

void MDR_KX028_InitAll_AfterEMAC(MDR_KX028_DelayMs DelayFunc, bool doExtraInit);


//==================    Enable Blocks =================
void MDR_KX028_EnableBlocks(void);




//===================   HGPI, HIF Init (Host) ===================
//void MDR_KX028_InitHGPI(void);
//void MDR_KX028_InitHIF(void);

//==================    from Demo-Board code ========================
//  Sync with PCIe driver -? TODO
void MDR_KX028_SysSoftReset(MDR_KX028_DelayMs DelayFunc);



//===================   EMACs MDIO Control  ==========================
// 1923KX028 PCLK is 200MHz (Classificator works at 400MHz)
typedef enum {
  //  KX028_MDC_Div8   = 0, //000: divide pclk by 8 (pclk up to 20 MHz) 
  //  KX028_MDC_Div16  = 1, //001: divide pclk by 16 (pclk up to 40 MHz) 
  //  KX028_MDC_Div32  = 2, //010: divide pclk by 32 (pclk up to 80 MHz) 
  //  KX028_MDC_Div48  = 3, //011: divide pclk by 48 (pclk up to 120MHz) 
  //  KX028_MDC_Div64  = 4, //100: divide pclk by 64 (pclk up to 160 MHz) 
  KX028_MDC_Div96  = 5, //101: divide pclk by 96 (pclk up to 240 MHz) - 
  KX028_MDC_Div128 = 6, //110: divide pclk by 128 (pclk up to 320 MHz) 
  KX028_MDC_Div224 = 7, //111: divide pclk by 224 (pclk up to 540 MHz).
} MDR_KX028_MDC_DIV;

void MDR_KX028_MDIO_Init(MDR_KX028_EMAC_e emac, MDR_KX028_MDC_DIV divMDC);

//It takes about 2000 pclk cycles to complete, when MDC is set for pclk divide by 32 in the network configuration register = 10us
bool MDR_KX028_MDIO_Write(MDR_KX028_EMAC_e emac, uint16_t addrPHY, uint16_t addrRegInPHY, uint16_t value, uint32_t delayTicks_10us);
bool MDR_KX028_MDIO_Read (MDR_KX028_EMAC_e emac, uint16_t addrPHY, uint16_t addrRegInPHY, uint16_t *value, uint32_t delayTicks_10us);
bool MDR_KX028_MDIO_Mask(MDR_KX028_EMAC_e emac, uint16_t addrPHY, uint16_t addrRegInPHY, uint16_t clrMask, uint16_t setMask, uint32_t delayTicks_10us);


#endif  //MDR_1923KX029_MODE2_INIT_H
