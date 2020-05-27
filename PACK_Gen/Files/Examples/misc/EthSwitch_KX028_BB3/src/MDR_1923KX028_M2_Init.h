#ifndef MDR_1923KX029_MODE2_INIT_H
#define MDR_1923KX029_MODE2_INIT_H

#include <MDR_Config.h>
#include <MDR_1923KX028.h>
#include <MDR_1923KX028_AXI_defs.h>
#include <MDR_1923KX028_Config.h>
#include <MDR_1923KX028_M2_Defs.h>


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
{ MDR_KX028_InitEMAC(emac, CFG_EMAC_NETCFG_GMII_FD_1G); }

__STATIC_INLINE void MDR_KX028_InitEMAC_SGMII_FD_100M_def(MDR_KX028_EMAC_e emac)
{ MDR_KX028_InitEMAC(emac, CFG_EMAC_NETCFG_SGMII_FD_100M); }

__STATIC_INLINE void MDR_KX028_InitEMAC_SGMII_FD_10M_def(MDR_KX028_EMAC_e emac)
{ MDR_KX028_InitEMAC(emac, CFG_EMAC_NETCFG_SGMII_FD_10M); }


//  Hold EMAC in default state after reset
__STATIC_INLINE void MDR_KX028_InitEMAC_None(MDR_KX028_EMAC_e emac)
{ MDR_KX028_WriteAXI(MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_CTRL, AXI_EMAC_CTRL_PORT_DIS_Msk); }


//===================   Init other blocks ===================
void MDR_KX028_InitBMU1(void);
void MDR_KX028_InitBMU2(void);
void MDR_KX028_InitHGPI(void);
void MDR_KX028_InitHIF(void);
void MDR_KX028_InitClassHW1(void);
void MDR_KX028_InitClassHW2(void);
void MDR_KX028_InitTMU(void);

__STATIC_INLINE void MDR_KX028_InitBMU_GPI_TMU_CLASS(void)
{
  MDR_KX028_InitBMU1();
  MDR_KX028_InitBMU2();
  MDR_KX028_InitHGPI();
  MDR_KX028_InitHIF();
  MDR_KX028_InitClassHW1();
  MDR_KX028_InitClassHW2();
  MDR_KX028_InitTMU();
}


//==================    Enable Blocks =================
void MDR_KX028_EnableBlocks(void);


//==================    Other Stuff ========================
//  EMAC GEM GXL timer increment register (0x01DC) count value has to be configured as 20 for 50Mhz
__STATIC_INLINE void MDR_KX028_InitEMAC_TSU(MDR_KX028_EMAC_e emac)
{ MDR_KX028_WriteAXI(MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_TSU_TIM_INC, CFG_TSU_INC_PER_1NS); }



//==================    from Demo-Board code ========================
//  Sync with PCIe driver -? TODO
                void MDR_KX028_SysSoftReset(uint32_t delayMs);
__STATIC_INLINE void MDR_KX028_SysSoftReset_Def(void) { MDR_KX028_SysSoftReset(KX028_SOFT_RESET_DELAY_MS); }

#endif  //MDR_1923KX029_MODE2_INIT_H
