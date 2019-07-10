#ifndef _MDR_CLK_Checker_DEFS_H
#define _MDR_CLK_Checker_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include "MDR_Config.h"
#include "MDR_Types.h"


/* ========================================  Start of section using anonymous unions  ======================================== */
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
  #pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif
/* ========================================  Start of section using anonymous unions  ======================================== */

//  Для упрощения понимания введены переименования регистров!

typedef struct {
      uint16_t                        : 16;
      MDR_OnOff   EN_SLOW_EVENT0      : 1;
      MDR_OnOff   EN_SLOW_EVENT1      : 1;
      MDR_OnOff   EN_FAST_EVENT2      : 1;
      MDR_OnOff   EN_FAST_EVENT3      : 1;
      MDR_OnOff   EN_CHK              : 1;
      MDR_OnOff   CLR_SHIFT_SLOW      : 1;
      MDR_OnOff   CLR_SHIFT_FAST      : 1;
      MDR_OnOff   CLR_SLOW_EVENT0     : 1;
      MDR_OnOff   CLR_SLOW_EVENT1     : 1;
      MDR_OnOff   CLR_FAST_EVENT2     : 1;
      MDR_OnOff   CLR_FAST_EVENT3     : 1;
      uint32_t                        : 5;
} MDR_CLK_CHK_CTRL_Bits;


#define MDR_CLK_CHK_EN_SLOW_EVENT0_Pos  (16UL)       
#define MDR_CLK_CHK_EN_SLOW_EVENT0_Msk  (0x10000UL)  
#define MDR_CLK_CHK_EN_SLOW_EVENT1_Pos  (17UL)       
#define MDR_CLK_CHK_EN_SLOW_EVENT1_Msk  (0x20000UL)  
#define MDR_CLK_CHK_EN_FAST_EVENT2_Pos  (18UL)       
#define MDR_CLK_CHK_EN_FAST_EVENT2_Msk  (0x40000UL)  
#define MDR_CLK_CHK_EN_FAST_EVENT3_Pos  (19UL)       
#define MDR_CLK_CHK_EN_FAST_EVENT3_Msk  (0x80000UL)  
#define MDR_CLK_CHK_EN_Pos              (20UL)       
#define MDR_CLK_CHK_EN_Msk              (0x100000UL) 
#define MDR_CLK_CHK_CLR_SHIFT_SLOW_Pos  (21UL)       
#define MDR_CLK_CHK_CLR_SHIFT_SLOW_Msk  (0x200000UL) 
#define MDR_CLK_CHK_CLR_SHIFT_FAST_Pos  (22UL)       
#define MDR_CLK_CHK_CLR_SHIFT_FAST_Msk  (0x400000UL) 
#define MDR_CLK_CHK_CLR_SLOW_EVENT0_Pos (23UL)       
#define MDR_CLK_CHK_CLR_SLOW_EVENT0_Msk (0x800000UL) 
#define MDR_CLK_CHK_CLR_SLOW_EVENT1_Pos (24UL)       
#define MDR_CLK_CHK_CLR_SLOW_EVENT1_Msk (0x1000000UL)
#define MDR_CLK_CHK_CLR_FAST_EVENT2_Pos (25UL)       
#define MDR_CLK_CHK_CLR_FAST_EVENT2_Msk (0x2000000UL)
#define MDR_CLK_CHK_CLR_FAST_EVENT3_Pos (26UL)       
#define MDR_CLK_CHK_CLR_FAST_EVENT3_Msk (0x4000000UL)

#define MDR_CLK_CHK_CLR_ALL_EVENTS    ( MDR_CLK_CHK_CLR_SHIFT_SLOW_Msk  | MDR_CLK_CHK_CLR_SHIFT_FAST_Msk    \
                                      | MDR_CLK_CHK_CLR_SLOW_EVENT0_Msk | MDR_CLK_CHK_CLR_SLOW_EVENT1_Msk   \
                                      | MDR_CLK_CHK_CLR_FAST_EVENT2_Msk | MDR_CLK_CHK_CLR_FAST_EVENT3_Msk)

#define MDR_CLK_CHK_SEL_ALL             (0x07FF0000UL)
#define MDR_CLK_CHK_SEL_EN_EVENTS     (MDR_CLK_CHK_EN_SLOW_EVENT0_Msk | MDR_CLK_CHK_EN_SLOW_EVENT1_Msk |    \
                                       MDR_CLK_CHK_EN_FAST_EVENT2_Msk | MDR_CLK_CHK_EN_FAST_EVENT3_Msk)

typedef union {
    uint32_t              CTRL;
    MDR_CLK_CHK_CTRL_Bits CTRL_b;
} MDR_CLKCHK_Ctrl;

//---------------   Status Bits  ---------------
typedef struct {
      uint32_t    MAX_CLK_SHIFT_SLOW : 8;  
      uint32_t    MAX_CLK_SHIFT_FAST : 8;  
      MDR_OnOff   SLOW_EVENT0        : 1;  
      MDR_OnOff   SLOW_EVENT1        : 1;  
      MDR_OnOff   FAST_EVENT2        : 1;  
      MDR_OnOff   FAST_EVENT3        : 1;  
      uint32_t                       : 12;
} MDR_CLK_CHK_STAT_Bits;

#define MDR_CLK_CHK_STAT_MAX_CLK_SHIFT_SLOW_Pos (0UL)     
#define MDR_CLK_CHK_STAT_MAX_CLK_SHIFT_SLOW_Msk (0xffUL)  
#define MDR_CLK_CHK_STAT_MAX_CLK_SHIFT_FAST_Pos (8UL)     
#define MDR_CLK_CHK_STAT_MAX_CLK_SHIFT_FAST_Msk (0xff00UL)
#define MDR_CLK_CHK_STAT_SLOW_EVENT0_Pos        (16UL)           
#define MDR_CLK_CHK_STAT_SLOW_EVENT0_Msk        (0x10000UL)      
#define MDR_CLK_CHK_STAT_SLOW_EVENT1_Pos        (17UL)           
#define MDR_CLK_CHK_STAT_SLOW_EVENT1_Msk        (0x20000UL)      
#define MDR_CLK_CHK_STAT_FAST_EVENT2_Pos        (18UL)           
#define MDR_CLK_CHK_STAT_FAST_EVENT2_Msk        (0x40000UL)      
#define MDR_CLK_CHK_STAT_FAST_EVENT3_Pos        (19UL)           
#define MDR_CLK_CHK_STAT_FAST_EVENT3_Msk        (0x80000UL)      


typedef union {
    uint32_t              STAT;
    MDR_CLK_CHK_STAT_Bits STAT_b;
} MDR_CLKCHK_Status;


//---------------   Clock Checker Bits  ---------------
typedef struct {
      uint16_t PRES_HSI_Slow  : 16;   //  REG2
      uint16_t PRES_HSI_Fast  : 16;   //  REG0
} MDR_CLK_CHK0_Bits;

#define MDR_CLK_CHK0_PRES_HSI_SLOW_Pos (0UL)         
#define MDR_CLK_CHK0_PRES_HSI_SLOW_Msk (0xffffUL)    
#define MDR_CLK_CHK0_PRES_HSI_FAST_Pos (16UL)        
#define MDR_CLK_CHK0_PRES_HSI_FAST_Msk (0xffff0000UL)


typedef struct {
      uint16_t PRES_CLK_Slow  : 16;   //  REG3
      uint16_t PRES_CLK_Fast  : 16;   //  REG1
} MDR_CLK_CHK1_Bits;

#define MDR_CLK_CHK1_PRES_CLK_SLOW_Pos (0UL)          
#define MDR_CLK_CHK1_PRES_CLK_SLOW_Msk (0xffffUL)     
#define MDR_CLK_CHK1_PRES_CLK_FAST_Pos (16UL)         
#define MDR_CLK_CHK1_PRES_CLK_FAST_Msk (0xffff0000UL) 


typedef struct {
      uint8_t BASE_SLOW_EVENT0  : 8;
      uint8_t BASE_SLOW_EVENT1  : 8;
      uint8_t BASE_FAST_EVENT2  : 8;
      uint8_t BASE_FAST_EVENT3  : 8;
} MDR_CLK_CHK2_Bits;

#define MDR_RST_CHK2_BASE_SLOW_EVENT0_Pos (0UL)         
#define MDR_RST_CHK2_BASE_SLOW_EVENT0_Msk (0xffUL)      
#define MDR_RST_CHK2_BASE_SLOW_EVENT1_Pos (8UL)         
#define MDR_RST_CHK2_BASE_SLOW_EVENT1_Msk (0xff00UL)    
#define MDR_RST_CHK2_BASE_FAST_EVENT2_Pos (16UL)        
#define MDR_RST_CHK2_BASE_FAST_EVENT2_Msk (0xff0000UL)  
#define MDR_RST_CHK2_BASE_FAST_EVENT3_Pos (24UL)        
#define MDR_RST_CHK2_BASE_FAST_EVENT3_Msk (0xff000000UL)


typedef struct {
  union {
    uint32_t              CTRL;    
    MDR_CLK_CHK_CTRL_Bits CTRL_b;
  } ;
  union {
    uint32_t              CLK_CHK0;
    MDR_CLK_CHK0_Bits     CLK_CHK0_b;
  } ;  
  union {
    uint32_t              CLK_CHK1;
    MDR_CLK_CHK1_Bits     CLK_CHK1_b;
  } ;  
  union {
    uint32_t              CLK_CHK2;
    MDR_CLK_CHK2_Bits     CLK_CHK2_b;
  } ;
  union {
    uint32_t              STAT;
    MDR_CLK_CHK_STAT_Bits STAT_b;
  } ;  
} MDR_CLKCHK_Regs;


typedef struct {
  MDR_OnOff   SLOW_EVENT0 : 1;
  MDR_OnOff   SLOW_EVENT1 : 1;
  MDR_OnOff   FAST_EVENT2 : 1;
  MDR_OnOff   FAST_EVENT3 : 1;
  uint32_t                : 28;
} MDR_CLKCHK_EventSel_bits;


/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#endif
/* =========================================  End of section using anonymous unions  ========================================= */

#ifdef __cplusplus
}
#endif

#endif  //_MDR_CLK_Checker_DEFS_H
