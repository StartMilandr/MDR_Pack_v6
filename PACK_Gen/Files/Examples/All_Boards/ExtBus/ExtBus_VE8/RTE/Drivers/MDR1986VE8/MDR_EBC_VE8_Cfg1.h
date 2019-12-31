#ifndef __MDR_EBC_CFG1_H__
#define __MDR_EBC_CFG1_H__

#include "MDR_EBC_VE8_Defs.h"
#include "MDR_Config.h"
#include <stdint.h>

//  ======================   ExtBus Config for any region =============================
//    Definitions in MDR_1986VE8.h:
//    #define MDR_EBC_RGN0_START_ADDR       0x10000000
//    #define MDR_EBC_RGN1_START_ADDR       0x18000000
//    #define MDR_EBC_RGN2_START_ADDR       0x50000000
//    #define MDR_EBC_RGN3_START_ADDR       0x58000000
//    #define MDR_EBC_RGN4_START_ADDR       0x60000000
//    #define MDR_EBC_RGN5_START_ADDR       0x68000000
//    #define MDR_EBC_RGN6_START_ADDR       0x70000000
//    #define MDR_EBC_RGN7_START_ADDR       0x80000000

//    #define MDR_EBC_RGN0_LEN              0x08000000
//    #define MDR_EBC_RGN1_LEN              0x08000000
//    #define MDR_EBC_RGN2_LEN              0x08000000
//    #define MDR_EBC_RGN3_LEN              0x08000000
//    #define MDR_EBC_RGN4_LEN              0x08000000
//    #define MDR_EBC_RGN5_LEN              0x08000000
//    #define MDR_EBC_RGN6_LEN              0x10000000
//    #define MDR_EBC_RGN7_LEN              0x60000000

//  Common settings
#define EBCCFG1_USE_ECC             0
#define EBCCFG1_USE_READY           0
#define EBCCFG1_READ_ONLY           0
#define EBCCFG1_CACHABLE            0
//  Bus width
#define EBCCFG1_DATA_BUS_WIDTH      MDR_EBC_CNTR_BusWidth_8
#define EBCCFG1_DATA_BUS_READ32     1
//  Timings
#define EBCCFG1_WS_SETUP            3
#define EBCCFG1_WS_ACTIVE           MDR_EBC_WS_Delay16_HCLK_4
#define EBCCFG1_WS_HOLD             MDR_EBC_WS_Delay16_HCLK_4
//  ECC
#if   EBCCFG1_USE_ECC
  #define EBCCFG1_ECC_MODE          MDR_EBC_CNTR_ECC_MODE_Sequential
#endif

//  Events IRQ and Captore to log registers ECC_ADR, ECC_DATA, ECC_ECC
#define EBCCFG1_SGL_ECC_IRQ_EN      0
#define EBCCFG1_DBL_ECC_IRQ_EN      0
#define EBCCFG1_SGL_LOG_EN          0
#define EBCCFG1_DBL_LOG_EN          0

//  Test Clock Signal
#define EBCCFG1_SYNC_CLK_POL        MDR_EBC_CNTR_CPOL_Rise


//  -------------------------------   Implementation  ---------------------------------
#if EBCCFG1_USE_ECC
  #define EBCCFG1_ECC_EN_MSK          MDR_EBC_CNTR_ECC_EN_Msk
  #define EBCCFG1_ECC_MODE_MSK      ((EBCCFG1_ECC_MODE << MDR_EBC_CNTR_ECC_MODE_Pos) & MDR_EBC_CNTR_ECC_MODE_Msk)
#else  
  #define EBCCFG1_ECC_EN_MSK          0
  #define EBCCFG1_ECC_MODE_MSK        0
#endif

#if EBCCFG1_USE_READY
  #define EBCCFG1_USE_READY_MSK       MDR_EBC_CNTR_ECC_EN_Msk
#else  
  #define EBCCFG1_USE_READY_MSK       0
#endif

#if EBCCFG1_READ_ONLY
  #define EBCCFG1_ROM_MSK             MDR_EBC_CNTR_ROM_Msk
#else  
  #define EBCCFG1_ROM_MSK             0
#endif

#if EBCCFG1_CACHABLE
  #define EBCCFG1_CACHABLE_MSK        MDR_EBC_CNTR_CACHABLE_Msk
#else  
  #define EBCCFG1_CACHABLE_MSK        0
#endif

#if EBCCFG1_DATA_BUS_READ32
  #define EBCCFG1_READ32_MSK          MDR_EBC_CNTR_READ_32_Msk
#else  
  #define EBCCFG1_READ32_MSK          0
#endif

#define EBCCFG1_BUS_WIDTH_MSK       ((EBCCFG1_DATA_BUS_WIDTH << MDR_EBC_CNTR_MODE_Pos) & MDR_EBC_CNTR_MODE_Msk)

#define EBCCFG1_WS_SETUP_MSK        ((EBCCFG1_WS_SETUP  << MDR_EBC_CNTR_WS_SETUP_Pos)  & MDR_EBC_CNTR_WS_SETUP_Msk)
#define EBCCFG1_WS_ACTIVE_MSK       ((EBCCFG1_WS_ACTIVE << MDR_EBC_CNTR_WS_ACTIVE_Pos) & MDR_EBC_CNTR_WS_ACTIVE_Msk)
#define EBCCFG1_WS_HOLD_MSK         ((EBCCFG1_WS_HOLD   << MDR_EBC_CNTR_WS_HOLD_Pos)   & MDR_EBC_CNTR_WS_HOLD_Msk)

#define EBCCFG1_CPOL_MSK            ((EBCCFG1_SYNC_CLK_POL << MDR_EBC_CNTR_CPOL_Pos) & MDR_EBC_CNTR_CPOL_Msk)  


#if EBCCFG1_SGL_ECC_IRQ_EN
  #define EBCCFG1_SGL_IE_MSK          MDR_EBC_ECC_CS_SECC_IE_Msk
#else  
  #define EBCCFG1_SGL_IE_MSK          0
#endif

#if EBCCFG1_DBL_ECC_IRQ_EN
  #define EBCCFG1_DBL_IE_MSK          MDR_EBC_ECC_CS_DECC_IE_Msk
#else  
  #define EBCCFG1_DBL_IE_MSK          0
#endif

#if EBCCFG1_SGL_LOG_EN
  #define EBCCFG1_SGL_FIX_MSK         MDR_EBC_ECC_CS_FIX_SECC_Msk
#else  
  #define EBCCFG1_SGL_FIX_MSK         0
#endif

#if EBCCFG1_DBL_LOG_EN
  #define EBCCFG1_DBL_FIX_MSK         MDR_EBC_ECC_CS_FIX_DECC_Msk
#else  
  #define EBCCFG1_DBL_FIX_MSK         0
#endif


//  -------------------------------   Export CFG    -----------------------------------

#define EBCCFG1_REG_CTRL            EBCCFG1_ECC_EN_MSK   | EBCCFG1_ECC_MODE_MSK  | EBCCFG1_USE_READY_MSK | EBCCFG1_ROM_MSK  \
                                  | EBCCFG1_CACHABLE_MSK | EBCCFG1_READ32_MSK    | EBCCFG1_BUS_WIDTH_MSK                    \
                                  | EBCCFG1_WS_SETUP_MSK | EBCCFG1_WS_ACTIVE_MSK | EBCCFG1_WS_HOLD_MSK   | EBCCFG1_CPOL_MSK 

#define EBCCFG1_REG_CS              EBCCFG1_SGL_IE_MSK | EBCCFG1_DBL_IE_MSK | EBCCFG1_SGL_FIX_MSK | EBCCFG1_DBL_FIX_MSK

#define EBCCFG1_CFG_REGS(ecc_base_addr)         { .CNTR = EBCCFG0_REG_CTRL,  .ECC_BASE = ecc_base_addr, .CS = EBCCFG0_REG_CS};


#endif // __MDR_EBC_CFG1_H__
