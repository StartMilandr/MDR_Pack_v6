#ifndef __MDR_EBC_CFG0_H__
#define __MDR_EBC_CFG0_H__

#include "MDR_EBC_VE8_Defs.h"
#include "MDR_Config.h"
#include <stdint.h>

//  ======================   ExtBus Config for any region =============================

//  Common settings
#define EBCCFG0_USE_ECC             0
#define EBCCFG0_USE_READY           0
#define EBCCFG0_READ_ONLY           0
#define EBCCFG0_CACHABLE            0
//  Bus width
#define EBCCFG0_DATA_BUS_WIDTH      MDR_EBC_CNTR_BusWidth_8
#define EBCCFG0_DATA_BUS_READ32     1
//  Timings
#define EBCCFG0_WS_SETUP            3
#define EBCCFG0_WS_ACTIVE           MDR_EBC_WS_Delay16_HCLK_4
#define EBCCFG0_WS_HOLD             MDR_EBC_WS_Delay16_HCLK_4
//  ECC
#if   EBCCFG0_USE_ECC
  #define EBCCFG0_ECC_MODE          MDR_EBC_CNTR_ECC_MODE_Sequential
#endif

//  Events IRQ and Captore to log registers ECC_ADR, ECC_DATA, ECC_ECC
#define EBCCFG0_SGL_ECC_IRQ_EN      0
#define EBCCFG0_DBL_ECC_IRQ_EN      0
#define EBCCFG0_SGL_LOG_EN          0
#define EBCCFG0_DBL_LOG_EN          0

//  Test Clock Signal
#define EBCCFG0_SYNC_CLK_POL        MDR_EBC_CNTR_CPOL_Rise

//  External strobe - for Region0 ONLY!
#define EBCCFG0_USE_OCLK            1

#ifdef EBCCFG0_USE_OCLK
  #define EBCCFG0_OCLK_DIV          MDR_EBC_CNTR0_OCLK_Div1
#endif



//  -------------------------------   Implementation  ---------------------------------
#if EBCCFG0_USE_ECC
  #define EBCCFG0_ECC_EN_MSK          MDR_EBC_CNTR_ECC_EN_Msk
  #define EBCCFG0_ECC_MODE_MSK      ((EBCCFG0_ECC_MODE << MDR_EBC_CNTR_ECC_MODE_Pos) & MDR_EBC_CNTR_ECC_MODE_Msk)
#else  
  #define EBCCFG0_ECC_EN_MSK          0
  #define EBCCFG0_ECC_MODE_MSK        0
#endif

#if EBCCFG0_USE_READY
  #define EBCCFG0_USE_READY_MSK       MDR_EBC_CNTR_ECC_EN_Msk
#else  
  #define EBCCFG0_USE_READY_MSK       0
#endif

#if EBCCFG0_READ_ONLY
  #define EBCCFG0_ROM_MSK             MDR_EBC_CNTR_ROM_Msk
#else  
  #define EBCCFG0_ROM_MSK             0
#endif

#if EBCCFG0_CACHABLE
  #define EBCCFG0_CACHABLE_MSK        MDR_EBC_CNTR_CACHABLE_Msk
#else  
  #define EBCCFG0_CACHABLE_MSK        0
#endif

#if EBCCFG0_DATA_BUS_READ32
  #define EBCCFG0_READ32_MSK          MDR_EBC_CNTR_READ_32_Msk
#else  
  #define EBCCFG0_READ32_MSK          0
#endif

#define EBCCFG0_BUS_WIDTH_MSK       ((EBCCFG0_DATA_BUS_WIDTH << MDR_EBC_CNTR_MODE_Pos) & MDR_EBC_CNTR_MODE_Msk)

#define EBCCFG0_WS_SETUP_MSK        ((EBCCFG0_WS_SETUP  << MDR_EBC_CNTR_WS_SETUP_Pos)  & MDR_EBC_CNTR_WS_SETUP_Msk)
#define EBCCFG0_WS_ACTIVE_MSK       ((EBCCFG0_WS_ACTIVE << MDR_EBC_CNTR_WS_ACTIVE_Pos) & MDR_EBC_CNTR_WS_ACTIVE_Msk)
#define EBCCFG0_WS_HOLD_MSK         ((EBCCFG0_WS_HOLD   << MDR_EBC_CNTR_WS_HOLD_Pos)   & MDR_EBC_CNTR_WS_HOLD_Msk)

#define EBCCFG0_CPOL_MSK            ((EBCCFG0_SYNC_CLK_POL << MDR_EBC_CNTR_CPOL_Pos) & MDR_EBC_CNTR_CPOL_Msk)  

#if EBCCFG0_USE_OCLK
  #define EBCCFG0_OCLK_EN_MSK         MDR_EBC_CNTR0_OCLK_EN_Msk
  #define EBCCFG0_OCLK_DIV_MSK      ((EBCCFG0_OCLK_DIV << MDR_EBC_CNTR0_OCLK_DIV_Pos) & MDR_EBC_CNTR0_OCLK_DIV_Msk)
#else
  #define EBCCFG0_OCLK_EN_MSK         0
  #define EBCCFG0_OCLK_DIV_MSK        0
#endif


#if EBCCFG0_SGL_ECC_IRQ_EN
  #define EBCCFG0_SGL_IE_MSK          MDR_EBC_ECC_CS_SECC_IE_Msk
#else  
  #define EBCCFG0_SGL_IE_MSK          0
#endif

#if EBCCFG0_DBL_ECC_IRQ_EN
  #define EBCCFG0_DBL_IE_MSK          MDR_EBC_ECC_CS_DECC_IE_Msk
#else  
  #define EBCCFG0_DBL_IE_MSK          0
#endif

#if EBCCFG0_SGL_LOG_EN
  #define EBCCFG0_SGL_FIX_MSK         MDR_EBC_ECC_CS_FIX_SECC_Msk
#else  
  #define EBCCFG0_SGL_FIX_MSK         0
#endif

#if EBCCFG0_DBL_LOG_EN
  #define EBCCFG0_DBL_FIX_MSK         MDR_EBC_ECC_CS_FIX_DECC_Msk
#else  
  #define EBCCFG0_DBL_FIX_MSK         0
#endif


//  -------------------------------   Export CFG    -----------------------------------

#define EBCCFG0_REG_CTRL            EBCCFG0_ECC_EN_MSK   | EBCCFG0_ECC_MODE_MSK  | EBCCFG0_USE_READY_MSK | EBCCFG0_ROM_MSK  \
                                  | EBCCFG0_CACHABLE_MSK | EBCCFG0_READ32_MSK    | EBCCFG0_BUS_WIDTH_MSK                    \
                                  | EBCCFG0_WS_SETUP_MSK | EBCCFG0_WS_ACTIVE_MSK | EBCCFG0_WS_HOLD_MSK   | EBCCFG0_CPOL_MSK 

#define EBCCFG0_REG_CTRL0           EBCCFG0_REG_CTRL | EBCCFG0_OCLK_EN_MSK | EBCCFG0_OCLK_DIV_MSK

#define EBCCFG0_REG_CS              EBCCFG0_SGL_IE_MSK | EBCCFG0_DBL_IE_MSK | EBCCFG0_SGL_FIX_MSK | EBCCFG0_DBL_FIX_MSK

#define EBCCFG0_CFG_REGS(ecc_base_addr)       { .CNTR = EBCCFG0_REG_CTRL,  .ECC_BASE = ecc_base_addr, .CS = EBCCFG0_REG_CS};
#define EBCCFG0_CFG_REGS_EX(ecc_base_addr)    { .CNTR = EBCCFG0_REG_CTRL0, .ECC_BASE = ecc_base_addr, .CS = EBCCFG0_REG_CS};



#endif // __MDR_EBC_CFG0_H__
