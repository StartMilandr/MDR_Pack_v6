#ifndef _MDR_EBC_VE8_DEFS_H
#define _MDR_EBC_VE8_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <MDR_Types.h>


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

/**
  * @brief External Bus Controler (MDR_ExtBus)
  */
  
/* ======================================================  CNTR_Regn0  ======================================================= */

typedef enum {                                  /*!< MDR_ExtBus_CNTR_Regn0_ECC_MODE                                            */
  MDR_EBC_CNTR_ECC_MODE_Parallel = 0,           /*!< Parallel : ECC and data in the same addresses                             */
  MDR_EBC_CNTR_ECC_MODE_Sequential = 1,         /*!< Sequential : ECC in separate address subregion                            */
} MDR_EBC_CNTR_ECC_MODE;

typedef enum {                                  /*!< MDR_ExtBus_CNTR_Regn0_MODE                                                */
  MDR_EBC_CNTR_BusWidth_32  = 0,    /*!< DataBus_32 : 32-bit data bus width                                        */
  MDR_EBC_CNTR_BusWidth_16  = 1,    /*!< DataBus_16 : 16-bit data bus width                                        */
  MDR_EBC_CNTR_BusWidth_8   = 2,    /*!< DataBus_8 : 8-bit data bus width                                          */
  MDR_EBC_CNTR_BusWidth_64  = 3,    /*!< DataBus_64 : 64-bit data bus width                                        */
} MDR_EBC_CNTR_BusWidth;

typedef enum {                         /*!< MDR_ExtBus_CNTR_Regn0_CPOL                                                */
  MDR_EBC_CNTR_CPOL_Rise      = 0,     /*!< Rise : Rise front                                                         */
  MDR_EBC_CNTR_CPOL_Fall      = 1,     /*!< Fall : Fall front                                                         */
} MDR_EBC_CNTR_CPOL;

typedef enum {                                  /*!< MDR_ExtBus_CNTR_Regn0_WS_SETUP                                            */
  MDR_EBC_WS_Delay16_HCLK_1 = 0,    /*!< HCLK_1 : Phase Duration                                                   */
  MDR_EBC_WS_Delay16_HCLK_2 = 1,    /*!< HCLK_2 : Phase Duration                                                   */
  MDR_EBC_WS_Delay16_HCLK_3 = 2,    /*!< HCLK_3 : Phase Duration                                                   */
  MDR_EBC_WS_Delay16_HCLK_4 = 3,    /*!< HCLK_4 : Phase Duration                                                   */
  MDR_EBC_WS_Delay16_HCLK_5 = 4,    /*!< HCLK_5 : Phase Duration                                                   */
  MDR_EBC_WS_Delay16_HCLK_6 = 5,    /*!< HCLK_6 : Phase Duration                                                   */
  MDR_EBC_WS_Delay16_HCLK_7 = 6,    /*!< HCLK_7 : Phase Duration                                                   */
  MDR_EBC_WS_Delay16_HCLK_8 = 7,    /*!< HCLK_8 : Phase Duration                                                   */
  MDR_EBC_WS_Delay16_HCLK_9 = 8,    /*!< HCLK_9 : Phase Duration                                                   */
  MDR_EBC_WS_Delay16_HCLK_10 = 9,   /*!< HCLK_10 : Phase Duration                                                  */
  MDR_EBC_WS_Delay16_HCLK_11 = 10,  /*!< HCLK_11 : Phase Duration                                                  */
  MDR_EBC_WS_Delay16_HCLK_12 = 11,  /*!< HCLK_12 : Phase Duration                                                  */
  MDR_EBC_WS_Delay16_HCLK_13 = 12,  /*!< HCLK_13 : Phase Duration                                                  */
  MDR_EBC_WS_Delay16_HCLK_14 = 13,  /*!< HCLK_14 : Phase Duration                                                  */
  MDR_EBC_WS_Delay16_HCLK_15 = 14,  /*!< HCLK_15 : Phase Duration                                                  */
  MDR_EBC_WS_Delay16_HCLK_16 = 15,  /*!< HCLK_16 : Phase Duration                                                  */
} MDR_EBC_WS_Delay16;

#define MDR_EBC_WS_SETUP      MDR_EBC_WS_Delay16
#define MDR_EBC_WS_HOLD       MDR_EBC_WS_Delay16

typedef struct {
    __IOM MDR_OnOff               EN         : 1;            /*!< [0..0] Region enable                                                      */
    __IOM MDR_OnOff               ECC_EN     : 1;            /*!< [1..1] ECC Enable                                                         */
    __IOM MDR_EBC_CNTR_ECC_MODE   ECC_MODE   : 1;            /*!< [2..2] ECC Mode                                                           */
    __IOM MDR_OnOff               RDY_WAIT   : 1;            /*!< [3..3] Wait for READY signal                                              */
    __IOM MDR_EBC_CNTR_BusWidth   BusWidth   : 2;            /*!< [5..4] Data bus width                                                     */
    __IOM MDR_OnOff               ReadOnly   : 1;            /*!< [6..6] Read Only bus                                                      */
    __IOM MDR_EBC_CNTR_CPOL       CPOL       : 1;            /*!< [7..7] Clock at Active phase                                              */
    __IOM uint8_t                 WS_ACTIVE  : 8;            /*!< [15..8] Active phase duration Delay = HCLK * (WS_ACTIVE + 1)              */
    __IOM MDR_EBC_WS_SETUP        WS_SETUP   : 4;            /*!< [19..16] Setup phase duration                                             */
    __IOM MDR_EBC_WS_HOLD         WS_HOLD    : 4;            /*!< [23..20] Hold phase duration                                              */
    __IM  uint32_t                           : 1;
    __IOM MDR_OnOff               CACHABLE   : 1;            /*!< [25..25] Read Only bus                                                    */
    __IOM MDR_OnOff               READ_32    : 1;            /*!< [26..26] Operate with 32-bit values                                       */
    __IOM uint32_t                           : 5;
} MDR_EBC_CNTR_Bits;

#define MDR_EBC_CNTR_EN_Pos         (0UL)                   /*!< MDR_ExtBus CNTR_Regn0: EN (Bit 0)                     */
#define MDR_EBC_CNTR_EN_Msk         (0x1UL)                 /*!< MDR_ExtBus CNTR_Regn0: EN (Bitfield-Mask: 0x01)       */
#define MDR_EBC_CNTR_ECC_EN_Pos     (1UL)                   /*!< MDR_ExtBus CNTR_Regn0: ECC_EN (Bit 1)                 */
#define MDR_EBC_CNTR_ECC_EN_Msk     (0x2UL)                 /*!< MDR_ExtBus CNTR_Regn0: ECC_EN (Bitfield-Mask: 0x01)   */
#define MDR_EBC_CNTR_ECC_MODE_Pos   (2UL)                   /*!< MDR_ExtBus CNTR_Regn0: ECC_MODE (Bit 2)               */
#define MDR_EBC_CNTR_ECC_MODE_Msk   (0x4UL)                 /*!< MDR_ExtBus CNTR_Regn0: ECC_MODE (Bitfield-Mask: 0x01) */
#define MDR_EBC_CNTR_RDY_WAIT_Pos   (3UL)                   /*!< MDR_ExtBus CNTR_Regn0: RDY_WAIT (Bit 3)               */
#define MDR_EBC_CNTR_RDY_WAIT_Msk   (0x8UL)                 /*!< MDR_ExtBus CNTR_Regn0: RDY_WAIT (Bitfield-Mask: 0x01) */
#define MDR_EBC_CNTR_MODE_Pos       (4UL)                   /*!< MDR_ExtBus CNTR_Regn0: MODE (Bit 4)                   */
#define MDR_EBC_CNTR_MODE_Msk       (0x30UL)                /*!< MDR_ExtBus CNTR_Regn0: MODE (Bitfield-Mask: 0x03)     */
#define MDR_EBC_CNTR_ROM_Pos        (6UL)                   /*!< MDR_ExtBus CNTR_Regn0: ROM (Bit 6)                    */
#define MDR_EBC_CNTR_ROM_Msk        (0x40UL)                /*!< MDR_ExtBus CNTR_Regn0: ROM (Bitfield-Mask: 0x01)      */
#define MDR_EBC_CNTR_CPOL_Pos       (7UL)                   /*!< MDR_ExtBus CNTR_Regn0: CPOL (Bit 7)                   */
#define MDR_EBC_CNTR_CPOL_Msk       (0x80UL)                /*!< MDR_ExtBus CNTR_Regn0: CPOL (Bitfield-Mask: 0x01)     */
#define MDR_EBC_CNTR_WS_ACTIVE_Pos  (8UL)                   /*!< MDR_ExtBus CNTR_Regn0: WS_ACTIVE (Bit 8)              */
#define MDR_EBC_CNTR_WS_ACTIVE_Msk  (0xff00UL)              /*!< MDR_ExtBus CNTR_Regn0: WS_ACTIVE (Bitfield-Mask: 0xff) */
#define MDR_EBC_CNTR_WS_SETUP_Pos   (16UL)                  /*!< MDR_ExtBus CNTR_Regn0: WS_SETUP (Bit 16)              */
#define MDR_EBC_CNTR_WS_SETUP_Msk   (0xf0000UL)             /*!< MDR_ExtBus CNTR_Regn0: WS_SETUP (Bitfield-Mask: 0x0f) */
#define MDR_EBC_CNTR_WS_HOLD_Pos    (20UL)                  /*!< MDR_ExtBus CNTR_Regn0: WS_HOLD (Bit 20)               */
#define MDR_EBC_CNTR_WS_HOLD_Msk    (0xf00000UL)            /*!< MDR_ExtBus CNTR_Regn0: WS_HOLD (Bitfield-Mask: 0x0f)  */
#define MDR_EBC_CNTR_CACHABLE_Pos   (25UL)                  /*!< MDR_ExtBus CNTR_Regn0: CACHABLE (Bit 25)              */
#define MDR_EBC_CNTR_CACHABLE_Msk   (0x2000000UL)           /*!< MDR_ExtBus CNTR_Regn0: CACHABLE (Bitfield-Mask: 0x01) */
#define MDR_EBC_CNTR_READ_32_Pos    (26UL)                  /*!< MDR_ExtBus CNTR_Regn0: READ_32 (Bit 26)               */
#define MDR_EBC_CNTR_READ_32_Msk    (0x4000000UL)           /*!< MDR_ExtBus CNTR_Regn0: READ_32 (Bitfield-Mask: 0x01)  */

//  For Region_0 ONLY:
typedef enum {                                  /*!< MDR_ExtBus_CNTR_Regn0_OCLK_DIV                                            */
  MDR_EBC_CNTR0_OCLK_Div1 = 0,     /*!< DIV_1 : OCLK Prescaller                                                   */
  MDR_EBC_CNTR0_OCLK_Div2 = 1,     /*!< DIV_2 : OCLK Prescaller                                                   */
  MDR_EBC_CNTR0_OCLK_Div3 = 2,     /*!< DIV_3 : OCLK Prescaller                                                   */
  MDR_EBC_CNTR0_OCLK_Div4 = 3,     /*!< DIV_4 : OCLK Prescaller                                                   */
  MDR_EBC_CNTR0_OCLK_Div5 = 4,     /*!< DIV_5 : OCLK Prescaller                                                   */
  MDR_EBC_CNTR0_OCLK_Div6 = 5,     /*!< DIV_6 : OCLK Prescaller                                                   */
  MDR_EBC_CNTR0_OCLK_Div7 = 6,     /*!< DIV_7 : OCLK Prescaller                                                   */
  MDR_EBC_CNTR0_OCLK_Div8 = 7,     /*!< DIV_8 : OCLK Prescaller                                                   */
  MDR_EBC_CNTR0_OCLK_Div9 = 8,     /*!< DIV_9 : OCLK Prescaller                                                   */
  MDR_EBC_CNTR0_OCLK_Div10 = 9,    /*!< DIV_10 : OCLK Prescaller                                                  */
  MDR_EBC_CNTR0_OCLK_Div11 = 10,   /*!< DIV_11 : OCLK Prescaller                                                  */
  MDR_EBC_CNTR0_OCLK_Div12 = 11,   /*!< DIV_12 : OCLK Prescaller                                                  */
  MDR_EBC_CNTR0_OCLK_Div13 = 12,   /*!< DIV_13 : OCLK Prescaller                                                  */
  MDR_EBC_CNTR0_OCLK_Div14 = 13,   /*!< DIV_14 : OCLK Prescaller                                                  */
  MDR_EBC_CNTR0_OCLK_Div15 = 14,   /*!< DIV_15 : OCLK Prescaller                                                  */
  MDR_EBC_CNTR0_OCLK_Div16 = 15,   /*!< DIV_16 : OCLK Prescaller                                                  */
} MDR_EBC_CNTR0_OCLK_DIV;
              
typedef struct {
    __IOM MDR_OnOff               EN         : 1;            /*!< [0..0] Region enable                                                      */
    __IOM MDR_OnOff               ECC_EN     : 1;            /*!< [1..1] ECC Enable                                                         */
    __IOM MDR_EBC_CNTR_ECC_MODE   ECC_MODE   : 1;            /*!< [2..2] ECC Mode                                                           */
    __IOM MDR_OnOff               RDY_WAIT   : 1;            /*!< [3..3] Wait for READY signal                                              */
    __IOM MDR_EBC_CNTR_BusWidth   BusWidth   : 2;            /*!< [5..4] Data bus width                                                     */
    __IOM MDR_OnOff               ReadOnly   : 1;            /*!< [6..6] Read Only bus                                                      */
    __IOM MDR_EBC_CNTR_CPOL       CPOL       : 1;            /*!< [7..7] Clock at Active phase                                              */
    __IOM uint8_t                 WS_ACTIVE  : 8;            /*!< [15..8] Active phase duration Delay = HCLK * (WS_ACTIVE + 1)              */
    __IOM MDR_EBC_WS_SETUP        WS_SETUP   : 4;            /*!< [19..16] Setup phase duration                                             */
    __IOM MDR_EBC_WS_HOLD         WS_HOLD    : 4;            /*!< [23..20] Hold phase duration                                              */
    __IM  uint32_t                           : 1;
    __IOM MDR_OnOff               CACHABLE   : 1;            /*!< [25..25] Read Only bus                                                    */
    __IOM MDR_OnOff               READ_32    : 1;            /*!< [26..26] Operate with 32-bit values                                       */
    __IOM MDR_OnOff               OCLK_EN    : 1;            /*!< [27..27] Enable OCLK output signal                                        */
    __IOM MDR_EBC_CNTR0_OCLK_DIV  OCLK_DIV   : 4;            /*!< [31..28] OCLK Prescaller                                                  */
} MDR_EBC_CNTR0_Bits;

#define MDR_EBC_CNTR0_OCLK_EN_Pos   (27UL)                  /*!< MDR_ExtBus CNTR_Regn0: OCLK_EN (Bit 27)               */
#define MDR_EBC_CNTR0_OCLK_EN_Msk   (0x8000000UL)           /*!< MDR_ExtBus CNTR_Regn0: OCLK_EN (Bitfield-Mask: 0x01)  */
#define MDR_EBC_CNTR0_OCLK_DIV_Pos  (28UL)                  /*!< MDR_ExtBus CNTR_Regn0: OCLK_DIV (Bit 28)              */
#define MDR_EBC_CNTR0_OCLK_DIV_Msk  (0xf0000000UL)          /*!< MDR_ExtBus CNTR_Regn0: OCLK_DIV (Bitfield-Mask: 0x0f) */


/* ========================================================  ECC_CS0  ======================================================== */

typedef struct {
    __IOM MDR_OnOff   SECC         : 1;            /*!< [0..0] Signle error detected                                              */
    __IOM MDR_OnOff   DECC         : 1;            /*!< [1..1] Double error detected                                              */
    __IOM MDR_OnOff   SECC_IE      : 1;            /*!< [2..2] Single error IRQ enable                                            */
    __IOM MDR_OnOff   DECC_IE      : 1;            /*!< [3..3] Double error IRQ enable                                            */
    __IOM MDR_OnOff   FIX_SECC     : 1;            /*!< [4..4] Log Single Error to regs                                           */
    __IOM MDR_OnOff   FIX_DECC     : 1;            /*!< [5..5] Log Double Error to regs                                           */
    __IOM MDR_OnOff   CLR_SECC_CNT : 1;            /*!< [6..6] Clear Sigle error counter                                          */
    __IOM MDR_OnOff   CLR_DECC_CNT : 1;            /*!< [7..7] Clear Double error counter                                         */
    __IOM uint32_t    DECC_CNT     : 8;            /*!< [15..8] Double error counter                                              */
    __IOM uint32_t    SECC_CNT     : 16;           /*!< [31..16] Single error counter                                             */
} MDR_EBC_ECC_CS;

#define MDR_EBC_ECC_CS_SECC_Pos       (0UL)                     /*!< MDR_ExtBus ECC_CS0: SECC (Bit 0)                      */
#define MDR_EBC_ECC_CS_SECC_Msk       (0x1UL)                   /*!< MDR_ExtBus ECC_CS0: SECC (Bitfield-Mask: 0x01)        */
#define MDR_EBC_ECC_CS_DECC_Pos       (1UL)                     /*!< MDR_ExtBus ECC_CS0: DECC (Bit 1)                      */
#define MDR_EBC_ECC_CS_DECC_Msk       (0x2UL)                   /*!< MDR_ExtBus ECC_CS0: DECC (Bitfield-Mask: 0x01)        */
#define MDR_EBC_ECC_CS_SECC_IE_Pos    (2UL)                     /*!< MDR_ExtBus ECC_CS0: SECC_IE (Bit 2)                   */
#define MDR_EBC_ECC_CS_SECC_IE_Msk    (0x4UL)                   /*!< MDR_ExtBus ECC_CS0: SECC_IE (Bitfield-Mask: 0x01)     */
#define MDR_EBC_ECC_CS_DECC_IE_Pos    (3UL)                     /*!< MDR_ExtBus ECC_CS0: DECC_IE (Bit 3)                   */
#define MDR_EBC_ECC_CS_DECC_IE_Msk    (0x8UL)                   /*!< MDR_ExtBus ECC_CS0: DECC_IE (Bitfield-Mask: 0x01)     */
#define MDR_EBC_ECC_CS_FIX_SECC_Pos   (4UL)                     /*!< MDR_ExtBus ECC_CS0: FIX_SECC (Bit 4)                  */
#define MDR_EBC_ECC_CS_FIX_SECC_Msk   (0x10UL)                  /*!< MDR_ExtBus ECC_CS0: FIX_SECC (Bitfield-Mask: 0x01)    */
#define MDR_EBC_ECC_CS_FIX_DECC_Pos   (5UL)                     /*!< MDR_ExtBus ECC_CS0: FIX_DECC (Bit 5)                  */
#define MDR_EBC_ECC_CS_FIX_DECC_Msk   (0x20UL)                  /*!< MDR_ExtBus ECC_CS0: FIX_DECC (Bitfield-Mask: 0x01)    */
#define MDR_EBC_ECC_CS_CLR_SECC_CNT_Pos (6UL)                   /*!< MDR_ExtBus ECC_CS0: CLR_SECC_CNT (Bit 6)              */
#define MDR_EBC_ECC_CS_CLR_SECC_CNT_Msk (0x40UL)                /*!< MDR_ExtBus ECC_CS0: CLR_SECC_CNT (Bitfield-Mask: 0x01) */
#define MDR_EBC_ECC_CS_CLR_DECC_CNT_Pos (7UL)                   /*!< MDR_ExtBus ECC_CS0: CLR_DECC_CNT (Bit 7)              */
#define MDR_EBC_ECC_CS_CLR_DECC_CNT_Msk (0x80UL)                /*!< MDR_ExtBus ECC_CS0: CLR_DECC_CNT (Bitfield-Mask: 0x01) */
#define MDR_EBC_ECC_CS_DECC_CNT_Pos   (8UL)                     /*!< MDR_ExtBus ECC_CS0: DECC_CNT (Bit 8)                  */
#define MDR_EBC_ECC_CS_DECC_CNT_Msk   (0xff00UL)                /*!< MDR_ExtBus ECC_CS0: DECC_CNT (Bitfield-Mask: 0xff)    */
#define MDR_EBC_ECC_CS_SECC_CNT_Pos   (16UL)                    /*!< MDR_ExtBus ECC_CS0: SECC_CNT (Bit 16)                 */
#define MDR_EBC_ECC_CS_SECC_CNT_Msk   (0xffff0000UL)            /*!< MDR_ExtBus ECC_CS0: SECC_CNT (Bitfield-Mask: 0xffff)  */

#define MDR_EBC_CLR_STATUS_ALL      MDR_EBC_ECC_CS_SECC_Msk | MDR_EBC_ECC_CS_DECC_Msk | MDR_EBC_ECC_CS_CLR_SECC_CNT_Msk | MDR_EBC_ECC_CS_CLR_DECC_CNT_Msk


/* ========================================================  ECC_ECC  ======================================================== */
#define MDR_ExtBus_ECC_ECC_ECC_Pos        (0UL)                     /*!< MDR_ExtBus ECC_ECC: ECC (Bit 0)                       */
#define MDR_ExtBus_ECC_ECC_ECC_Msk        (0xffUL)                  /*!< MDR_ExtBus ECC_ECC: ECC (Bitfield-Mask: 0xff)         */


/* ====================================================  ExtBus structure  ===================================================== */
typedef struct {                                /*!< (@ 0x40005000) MDR_ExtBus Structure                                       */
  __IOM uint32_t        KEY;                    /*!< (@ 0x00000000) Unlock Block registers                                     */  
  union {
    __IOM uint32_t      CNTR_RGN0;              /*!< (@ 0x00000004) Region_0 (0x1000_0000) Control                             */
    MDR_EBC_CNTR0_Bits  CNTR_RGN_b;
  } ;  
  union {
    __IOM uint32_t      CNTR_RGN1;             /*!< (@ 0x00000008) Region_1 (0x1800_0000) Control                             */
    MDR_EBC_CNTR_Bits   CNTR_RGN1_b;    
  } ;  
  union {
    __IOM uint32_t      CNTR_RGN2;             /*!< (@ 0x0000000C) Region_2 (0x5000_0000) Control                             */
    MDR_EBC_CNTR_Bits   CNTR_RGN2_b;    
  } ;  
  union {
    __IOM uint32_t      CNTR_RGN3;             /*!< (@ 0x00000010) Region_3 (0x5800_0000) Control                             */
    MDR_EBC_CNTR_Bits   CNTR_RGN3_b;        
  } ;  
  union {
    __IOM uint32_t      CNTR_RGNn4;             /*!< (@ 0x00000014) Region_4 (0x6000_0000) Control                             */
    MDR_EBC_CNTR_Bits   CNTR_RGN4_b;      
  } ;    
  union {
    __IOM uint32_t      CNTR_RGN5;             /*!< (@ 0x00000018) Region_5 (0x6800_0000) Control                             */
    MDR_EBC_CNTR_Bits   CNTR_RGN5_b;      
  } ;    
  union {
    __IOM uint32_t      CNTR_RGN6;             /*!< (@ 0x0000001C) Region_6 (0x7000_0000) Control                             */
    MDR_EBC_CNTR_Bits   CNTR_RGN6_b;    
  } ;  
  union {
    __IOM uint32_t      CNTR_RGN7;             /*!< (@ 0x00000020) Region_7 (0x8000_0000) Control                             */
    MDR_EBC_CNTR_Bits   CNTR_RGN7_b;        
  } ;
  __IOM uint32_t        ECC_BASE0;              /*!< (@ 0x00000024) Base address for sequential ECC                            */
  __IOM uint32_t        ECC_BASE1;              /*!< (@ 0x00000028) Base address for sequential ECC                            */
  __IOM uint32_t        ECC_BASE2;              /*!< (@ 0x0000002C) Base address for sequential ECC                            */
  __IOM uint32_t        ECC_BASE3;              /*!< (@ 0x00000030) Base address for sequential ECC                            */
  __IOM uint32_t        ECC_BASE4;              /*!< (@ 0x00000034) Base address for sequential ECC                            */
  __IOM uint32_t        ECC_BASE5;              /*!< (@ 0x00000038) Base address for sequential ECC                            */
  __IOM uint32_t        ECC_BASE6;              /*!< (@ 0x0000003C) Base address for sequential ECC                            */
  __IOM uint32_t        ECC_BASE7;              /*!< (@ 0x00000040) Base address for sequential ECC                            */
  
  union {
    __IOM uint32_t      ECC_CS0;                /*!< (@ 0x00000044) ECC region Control and Status                              */
    MDR_EBC_ECC_CS      ECC_CS0_b;
  } ;  
  union {
    __IOM uint32_t      ECC_CS1;                /*!< (@ 0x00000048) ECC region Control and Status                              */
    MDR_EBC_ECC_CS      ECC_CS1_b;
  } ;
  union {
    __IOM uint32_t      ECC_CS2;                /*!< (@ 0x0000004C) ECC region Control and Status                              */
    MDR_EBC_ECC_CS      ECC_CS2_b;
  } ;  
  union {
    __IOM uint32_t      ECC_CS3;                /*!< (@ 0x00000050) ECC region Control and Status                              */
    MDR_EBC_ECC_CS      ECC_CS3_b;    
  } ;  
  union {
    __IOM uint32_t      ECC_CS4;                /*!< (@ 0x00000054) ECC region Control and Status                              */
    MDR_EBC_ECC_CS      ECC_CS4_b;    
  } ;  
  union {
    __IOM uint32_t      ECC_CS5;                /*!< (@ 0x00000058) ECC region Control and Status                              */
    MDR_EBC_ECC_CS      ECC_CS5_b;
  } ;  
  union {
    __IOM uint32_t      ECC_CS6;                /*!< (@ 0x0000005C) ECC region Control and Status                              */
    MDR_EBC_ECC_CS      ECC_CS6_b;    
  } ;
  
  union {
    __IOM uint32_t      ECC_CS7;                /*!< (@ 0x00000060) ECC region Control and Status                              */
    MDR_EBC_ECC_CS      ECC_CS7_b;    
  } ;
  __IM  uint32_t        RESERVED[12];
  __IOM uint32_t        ECC_ADR;                /*!< (@ 0x00000094) Last ECC error address                                     */
  __IOM uint32_t        ECC_DATA;               /*!< (@ 0x00000098) Last ECC error Data                                        */  
  union {
    __IOM uint32_t      ECC_ECC;                /*!< (@ 0x0000009C) Last ECC error ECC                                         */    
    struct {
      __IOM uint32_t ECC        : 8;            /*!< [7..0] Last wrong ECC                                                     */
    } ECC_ECC_b;
  } ;
} MDR_EBC_Type;                                 /*!< Size = 160 (0xa0)                                                         */


/* =============================================  ExtBus Regions structures  ==================================================*/
typedef struct {
  union {
    __IOM uint32_t      CNTR;             
    MDR_EBC_CNTR0_Bits  CNTR_b;
    };    
    __IM  uint32_t      _reserved1[7];
    __IOM uint32_t      ECC_BASE;         
    __IM  uint32_t      _reserved2[7];
  union {
    __IOM uint32_t      CS;
    MDR_EBC_ECC_CS      CS_b;
  } ;      
} MDR_EBC_RGN0_Type;


typedef struct {
  union {
    __IOM uint32_t      CNTR;
    MDR_EBC_CNTR_Bits   CNTR_b;
  };
    __IM  uint32_t      _reserved1[7];
    __IOM uint32_t      ECC_BASE;         
    __IM  uint32_t      _reserved2[7];
  union {
    __IOM uint32_t      CS;
    MDR_EBC_ECC_CS      CS_b;
  } ;   
} MDR_EBC_RGN_Type;


typedef struct {
  __IOM uint32_t        ADR;                /*!< (@ 0x00000094) Last ECC error address                                     */
  __IOM uint32_t        DATA;               /*!< (@ 0x00000098) Last ECC error Data                                        */  
  union {
    __IOM uint32_t      ECC;                /*!< (@ 0x0000009C) Last ECC error ECC                                         */    
    struct {
      __IOM uint32_t ECC        : 8;        /*!< [7..0] Last wrong ECC                                                     */
    } ECC_ECC_b;
  } ;    
} MDR_EBC_ECC_ERR_Type;



//  Region ConfigRegs
typedef struct {
  union {
    __IOM uint32_t      CNTR;
    MDR_EBC_CNTR_Bits   CNTR_b;
  };
    __IOM uint32_t      ECC_BASE;         
  union {
    __IOM uint32_t      CS;
    MDR_EBC_ECC_CS      CS_b;
  } ;   
} MDR_EBC_RGN_CfgRegs;


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


#endif  //_MDR_EBC_VE8_DEFS_H
