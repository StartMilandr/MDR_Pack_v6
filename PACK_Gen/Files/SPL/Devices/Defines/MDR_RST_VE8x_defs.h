#ifndef _MDR_RST_VE8X_DEFS_H
#define _MDR_RST_VE8X_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


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

#define MDR_CLK_READY_BY_BKP
#define MDR_CLK_LIKE_VE8

/* ==========================================================  KEY  ========================================================== */
#define MDR_RST_CLOCK_KEY_Value_Pos       (0UL)                     /*!< MDR_RST_CLOCK KEY: Value (Bit 0)                      */
#define MDR_RST_CLOCK_KEY_Value_Msk       (0xffffffffUL)            /*!< MDR_RST_CLOCK KEY: Value (Bitfield-Mask: 0xffffffff)  */


//---------------   MAX_Clock  ---------------
typedef enum {
  MAXCLK_HSI      = 0,
  MAXCLK_HSIdiv2  = 1,
  MAXCLK_HSE0     = 2,
  MAXCLK_HSE0div2 = 3,
  MAXCLK_HSE1     = 4,
  MAXCLK_HSE1div2 = 5,
  MAXCLK_LSI      = 6,
  MAXCLK_LSE      = 7,
  MAXCLK_PLL0     = 8,
  MAXCLK_PLL1     = 9,
  MAXCLK_PLL2     = 10,
  MAXCLK_ERR      = 11,   //  Error Value - reserved
} MDR_MAXCLK_SEL;

typedef struct {
      __IOM MDR_MAXCLK_SEL  Select : 4;            /*!< [3..0] Select MAX_CLOCK source                                            */
      __IM  uint32_t               : 28;
} MDR_RST_MAX_CLK_Bits;

#define MDR_RST_CLOCK_MAX_CLK_Select_Pos  (0UL)                     /*!< MDR_RST_CLOCK MAX_CLK: Select (Bit 0)                 */
#define MDR_RST_CLOCK_MAX_CLK_Select_Msk  (0xfUL)                   /*!< MDR_RST_CLOCK MAX_CLK: Select (Bitfield-Mask: 0x0f)   */


//---------------   CPU_CLK Bits and LSI/LSE_CLK Bits  ---------------

typedef struct {
      __IOM uint16_t    DIV                 : 16;   /*!< [15..0] CPU_CLock div from MAX_CLOCK,  CPU_CLK = MAX_CLK/(DIV+1)      */
      __IOM MDR_OnOff   EN_CHK_EVENT0       : 1;    /*!< [16..16] Go to HSI on lose active clock                               */
      __IOM MDR_OnOff   EN_CHK_EVENT1       : 1;    /*!< [17..17] Go to HSI if active clock is low                             */
      __IOM MDR_OnOff   EN_CHK_EVENT2       : 1;    /*!< [18..18] Go to HSI if active clock is High                            */
      __IOM MDR_OnOff   EN_CHK_EVENT3       : 1;    /*!< [19..19] Go to HSI if active clock is Highest                         */
      __IOM MDR_OnOff   EN_CHK              : 1;    /*!< [20..20] Clock Checker enable                                         */
      __IOM MDR_OnOff   CLR_CHK_SHIFT_REG0  : 1;    /*!< [21..21] Clear Min Freq level                                         */
      __IOM MDR_OnOff   CLR_CHK_SHIFT_REG1  : 1;    /*!< [22..22] Clear Max Freq level                                         */
      __IOM MDR_OnOff   CLR_CHK_EVENT0      : 1;    /*!< [23..23] Clear no freq event                                          */
      __IOM MDR_OnOff   CLR_CHK_EVENT1      : 1;    /*!< [24..24] Clear low freq event                                         */
      __IOM MDR_OnOff   CLR_CHK_EVENT2      : 1;    /*!< [25..25] Clear high freq event                                        */
      __IOM MDR_OnOff   CLR_CHK_EVENT3      : 1;    /*!< [26..26] Clear highest freq event                                     */
      __IM  uint32_t                        : 5;
} MDR_RST_CLK_CPU_Bits;


typedef struct {
      __IM  uint32_t                      : 16;
      __IOM MDR_OnOff   EN_CHK_EVENT0     : 1;        /*!< [16..16] Go to HSI on lose active clock                                   */
      __IOM MDR_OnOff   EN_CHK_EVENT1     : 1;        /*!< [17..17] Go to HSI if active clock is low                                 */
      __IOM MDR_OnOff   EN_CHK_EVENT2     : 1;        /*!< [18..18] Go to HSI if active clock is High                                */
      __IOM MDR_OnOff   EN_CHK_EVENT3     : 1;        /*!< [19..19] Go to HSI if active clock is Highest                             */
      __IOM MDR_OnOff   EN_CHK            : 1;        /*!< [20..20] Clock Checker enable                                             */
      __IOM MDR_OnOff   CLR_CHK_SHIFT_REG0: 1;        /*!< [21..21] Clear Min Freq level                                             */
      __IOM MDR_OnOff   CLR_CHK_SHIFT_REG1: 1;        /*!< [22..22] Clear Max Freq level                                             */
      __IOM MDR_OnOff   CLR_CHK_EVENT0    : 1;        /*!< [23..23] Clear no freq event                                              */
      __IOM MDR_OnOff   CLR_CHK_EVENT1    : 1;        /*!< [24..24] Clear low freq event                                             */
      __IOM MDR_OnOff   CLR_CHK_EVENT2    : 1;        /*!< [25..25] Clear high freq event                                            */
      __IOM MDR_OnOff   CLR_CHK_EVENT3    : 1;        /*!< [26..26] Clear highest freq event                                         */
      __IM  uint32_t                      : 5;
} MDR_RST_CLK_LSIE_Bits;

#define MDR_RST_CLK_DIV_Pos           (0UL)               /*!< MDR_RST_CLOCK CPU_CLK: DIV (Bit 0)                    */
#define MDR_RST_CLK_DIV_Msk           (0xffffUL)          /*!< MDR_RST_CLOCK CPU_CLK: DIV (Bitfield-Mask: 0xffff)    */
#define MDR_RST_CLK_EN_CHK_EVENT0_Pos (16UL)              /*!< MDR_RST_CLOCK CPU_CLK: EN_CHK_EVENT0 (Bit 16)         */
#define MDR_RST_CLK_EN_CHK_EVENT0_Msk (0x10000UL)         /*!< MDR_RST_CLOCK CPU_CLK: EN_CHK_EVENT0 (Bitfield-Mask: 0x01) */
#define MDR_RST_CLK_EN_CHK_EVENT1_Pos (17UL)              /*!< MDR_RST_CLOCK CPU_CLK: EN_CHK_EVENT1 (Bit 17)         */
#define MDR_RST_CLK_EN_CHK_EVENT1_Msk (0x20000UL)         /*!< MDR_RST_CLOCK CPU_CLK: EN_CHK_EVENT1 (Bitfield-Mask: 0x01) */
#define MDR_RST_CLK_EN_CHK_EVENT2_Pos (18UL)              /*!< MDR_RST_CLOCK CPU_CLK: EN_CHK_EVENT2 (Bit 18)         */
#define MDR_RST_CLK_EN_CHK_EVENT2_Msk (0x40000UL)         /*!< MDR_RST_CLOCK CPU_CLK: EN_CHK_EVENT2 (Bitfield-Mask: 0x01) */
#define MDR_RST_CLK_EN_CHK_EVENT3_Pos (19UL)              /*!< MDR_RST_CLOCK CPU_CLK: EN_CHK_EVENT3 (Bit 19)         */
#define MDR_RST_CLK_EN_CHK_EVENT3_Msk (0x80000UL)         /*!< MDR_RST_CLOCK CPU_CLK: EN_CHK_EVENT3 (Bitfield-Mask: 0x01) */
#define MDR_RST_CLK_EN_CHK_Pos        (20UL)              /*!< MDR_RST_CLOCK CPU_CLK: EN_CHK (Bit 20)                */
#define MDR_RST_CLK_EN_CHK_Msk        (0x100000UL)        /*!< MDR_RST_CLOCK CPU_CLK: EN_CHK (Bitfield-Mask: 0x01)   */
#define MDR_RST_CLK_CLR_CHK_SHIFT_REG0_Pos (21UL)         /*!< MDR_RST_CLOCK CPU_CLK: CLR_CHK_SHIFT_REG0 (Bit 21)    */
#define MDR_RST_CLK_CLR_CHK_SHIFT_REG0_Msk (0x200000UL)   /*!< MDR_RST_CLOCK CPU_CLK: CLR_CHK_SHIFT_REG0 (Bitfield-Mask: 0x01) */
#define MDR_RST_CLK_CLR_CHK_SHIFT_REG1_Pos (22UL)         /*!< MDR_RST_CLOCK CPU_CLK: CLR_CHK_SHIFT_REG1 (Bit 22)    */
#define MDR_RST_CLK_CLR_CHK_SHIFT_REG1_Msk (0x400000UL)   /*!< MDR_RST_CLOCK CPU_CLK: CLR_CHK_SHIFT_REG1 (Bitfield-Mask: 0x01) */
#define MDR_RST_CLK_CLR_CHK_EVENT0_Pos (23UL)             /*!< MDR_RST_CLOCK CPU_CLK: CLR_CHK_EVENT0 (Bit 23)        */
#define MDR_RST_CLK_CLR_CHK_EVENT0_Msk (0x800000UL)       /*!< MDR_RST_CLOCK CPU_CLK: CLR_CHK_EVENT0 (Bitfield-Mask: 0x01) */
#define MDR_RST_CLK_CLR_CHK_EVENT1_Pos (24UL)             /*!< MDR_RST_CLOCK CPU_CLK: CLR_CHK_EVENT1 (Bit 24)        */
#define MDR_RST_CLK_CLR_CHK_EVENT1_Msk (0x1000000UL)      /*!< MDR_RST_CLOCK CPU_CLK: CLR_CHK_EVENT1 (Bitfield-Mask: 0x01) */
#define MDR_RST_CLK_CLR_CHK_EVENT2_Pos (25UL)             /*!< MDR_RST_CLOCK CPU_CLK: CLR_CHK_EVENT2 (Bit 25)        */
#define MDR_RST_CLK_CLR_CHK_EVENT2_Msk (0x2000000UL)      /*!< MDR_RST_CLOCK CPU_CLK: CLR_CHK_EVENT2 (Bitfield-Mask: 0x01) */
#define MDR_RST_CLK_CLR_CHK_EVENT3_Pos (26UL)             /*!< MDR_RST_CLOCK CPU_CLK: CLR_CHK_EVENT3 (Bit 26)        */
#define MDR_RST_CLK_CLR_CHK_EVENT3_Msk (0x4000000UL)      /*!< MDR_RST_CLOCK CPU_CLK: CLR_CHK_EVENT3 (Bitfield-Mask: 0x01) */


//---------------   CPU Status Bits  ---------------
typedef struct {
      __IOM uint32_t    MAX_CLK_SHIFT_REG0 : 8;    /*!< [7..0] Max factor detected for SLOW                                    */
      __IOM uint32_t    MAX_CLK_SHIFT_REG1 : 8;    /*!< [15..8] Max factor detected for FAST                                   */
      __IOM MDR_OnOff   EVENT0             : 1;            /*!< [16..16] Event SLOWEST                                         */
      __IOM MDR_OnOff   EVENT1             : 1;            /*!< [17..17] Event SLOW                                            */
      __IOM MDR_OnOff   EVENT2             : 1;            /*!< [18..18] Event FAST                                            */
      __IOM MDR_OnOff   EVENT3             : 1;            /*!< [19..19] Event FASTEST                                         */
      __IM  uint32_t                       : 12;
} MDR_RST_CPU_STAT_Bits;

#define MDR_RST_CPU_STAT_MAX_CLK_SHIFT_REG0_Pos (0UL)         /*!< MDR_RST_CLOCK CPU_STAT: MAX_CLK_SHIFT_REG0 (Bit 0)    */
#define MDR_RST_CPU_STAT_MAX_CLK_SHIFT_REG0_Msk (0xffUL)      /*!< MDR_RST_CLOCK CPU_STAT: MAX_CLK_SHIFT_REG0 (Bitfield-Mask: 0xff) */
#define MDR_RST_CPU_STAT_MAX_CLK_SHIFT_REG1_Pos (8UL)         /*!< MDR_RST_CLOCK CPU_STAT: MAX_CLK_SHIFT_REG1 (Bit 8)    */
#define MDR_RST_CPU_STAT_MAX_CLK_SHIFT_REG1_Msk (0xff00UL)    /*!< MDR_RST_CLOCK CPU_STAT: MAX_CLK_SHIFT_REG1 (Bitfield-Mask: 0xff) */
#define MDR_RST_CPU_STAT_EVENT0_Pos (16UL)                    /*!< MDR_RST_CLOCK CPU_STAT: EVENT0 (Bit 16)               */
#define MDR_RST_CPU_STAT_EVENT0_Msk (0x10000UL)               /*!< MDR_RST_CLOCK CPU_STAT: EVENT0 (Bitfield-Mask: 0x01)  */
#define MDR_RST_CPU_STAT_EVENT1_Pos (17UL)                    /*!< MDR_RST_CLOCK CPU_STAT: EVENT1 (Bit 17)               */
#define MDR_RST_CPU_STAT_EVENT1_Msk (0x20000UL)               /*!< MDR_RST_CLOCK CPU_STAT: EVENT1 (Bitfield-Mask: 0x01)  */
#define MDR_RST_CPU_STAT_EVENT2_Pos (18UL)                    /*!< MDR_RST_CLOCK CPU_STAT: EVENT2 (Bit 18)               */
#define MDR_RST_CPU_STAT_EVENT2_Msk (0x40000UL)               /*!< MDR_RST_CLOCK CPU_STAT: EVENT2 (Bitfield-Mask: 0x01)  */
#define MDR_RST_CPU_STAT_EVENT3_Pos (19UL)                    /*!< MDR_RST_CLOCK CPU_STAT: EVENT3 (Bit 19)               */
#define MDR_RST_CPU_STAT_EVENT3_Msk (0x80000UL)               /*!< MDR_RST_CLOCK CPU_STAT: EVENT3 (Bitfield-Mask: 0x01)  */


//---------------   Clock Checker Bits  ---------------
typedef struct {
      __IOM uint16_t PRES_REG2  : 16;           /*!< [15..0]  FreqRef Prescaller for Slow                                      */
      __IOM uint16_t PRES_REG0  : 16;           /*!< [31..16] FreqRef Prescaller for Fast                                      */
} MDR_RST_CLK_CHK0_Bits;

#define MDR_RST_CHK0_REG2_Pos (0UL)                  /*!< MDR_RST_CLOCK CPU_CHK0: PRES_REG2 (Bit 0)             */
#define MDR_RST_CHK0_REG2_Msk (0xffffUL)             /*!< MDR_RST_CLOCK CPU_CHK0: PRES_REG2 (Bitfield-Mask: 0xffff) */
#define MDR_RST_CHK0_REG0_Pos (16UL)                 /*!< MDR_RST_CLOCK CPU_CHK0: PRES_REG0 (Bit 16)            */
#define MDR_RST_CHK0_REG0_Msk (0xffff0000UL)         /*!< MDR_RST_CLOCK CPU_CHK0: PRES_REG0 (Bitfield-Mask: 0xffff) */


typedef struct {
      __IOM uint16_t PRES_REG3  : 16;           /*!< [15..0]  Clock Prescaller for Fast                                        */
      __IOM uint16_t PRES_REG1  : 16;           /*!< [31..16] Clock Prescaller for Slow                                        */
} MDR_RST_CLK_CHK1_Bits;

#define MDR_RST_CHK1_REG3_Pos (0UL)                  /*!< MDR_RST_CLOCK CPU_CHK1: PRES_REG3 (Bit 0)             */
#define MDR_RST_CHK1_REG3_Msk (0xffffUL)             /*!< MDR_RST_CLOCK CPU_CHK1: PRES_REG3 (Bitfield-Mask: 0xffff) */
#define MDR_RST_CHK1_REG1_Pos (16UL)                 /*!< MDR_RST_CLOCK CPU_CHK1: PRES_REG1 (Bit 16)            */
#define MDR_RST_CHK1_REG1_Msk (0xffff0000UL)         /*!< MDR_RST_CLOCK CPU_CHK1: PRES_REG1 (Bitfield-Mask: 0xffff) */


typedef struct {
      __IOM uint8_t BASE_REG0   : 8;            /*!< [7..0] Min factor for SLOWEST                                             */
      __IOM uint8_t BASE_REG1   : 8;            /*!< [15..8] Min factor for SLOW                                               */
      __IOM uint8_t BASE_REG2   : 8;            /*!< [23..16] Max factor for FAST                                              */
      __IOM uint8_t BASE_REG3   : 8;            /*!< [31..24] Max factor for FASTEST                                           */
} MDR_RST_CLK_CHK2_Bits;

#define MDR_RST_CHK2_REG0_Pos (0UL)                  /*!< MDR_RST_CLOCK CPU_CHK2: BASE_REG0 (Bit 0)             */
#define MDR_RST_CHK2_REG0_Msk (0xffUL)               /*!< MDR_RST_CLOCK CPU_CHK2: BASE_REG0 (Bitfield-Mask: 0xff) */
#define MDR_RST_CHK2_REG1_Pos (8UL)                  /*!< MDR_RST_CLOCK CPU_CHK2: BASE_REG1 (Bit 8)             */
#define MDR_RST_CHK2_REG1_Msk (0xff00UL)             /*!< MDR_RST_CLOCK CPU_CHK2: BASE_REG1 (Bitfield-Mask: 0xff) */
#define MDR_RST_CHK2_REG2_Pos (16UL)                 /*!< MDR_RST_CLOCK CPU_CHK2: BASE_REG2 (Bit 16)            */
#define MDR_RST_CHK2_REG2_Msk (0xff0000UL)           /*!< MDR_RST_CLOCK CPU_CHK2: BASE_REG2 (Bitfield-Mask: 0xff) */
#define MDR_RST_CHK2_REG3_Pos (24UL)                 /*!< MDR_RST_CLOCK CPU_CHK2: BASE_REG3 (Bit 24)            */
#define MDR_RST_CHK2_REG3_Msk (0xff000000UL)         /*!< MDR_RST_CLOCK CPU_CHK2: BASE_REG3 (Bitfield-Mask: 0xff) */


typedef struct {
    union {
    __IOM uint32_t        CPU_CHK0;             /*!< (@ 0x00000014) Clock Checker Register                                     */
    MDR_RST_CLK_CHK0_Bits CPU_CHK0_b;
  } ;  
  union {
    __IOM uint32_t        CPU_CHK1;             /*!< (@ 0x00000018) Clock Checker Register                                     */
    MDR_RST_CLK_CHK1_Bits CPU_CHK1_b;
  } ;  
  union {
    __IOM uint32_t        CPU_CHK2;                    /*!< (@ 0x0000001C) Clock Checker Register                                     */
    MDR_RST_CLK_CHK1_Bits CPU_CHK2_b;
  } ;
} MDR_RST_CLK_CHECKER;


//--------------- HSEx Bits  ------------------  
typedef struct {
      __IM  uint32_t                        : 16;
      __IOM MDR_OnOff   EN_CHK_EVENT0       : 1;    /*!< [16..16] Go to HSI on lose active clock                                   */
      __IOM MDR_OnOff   EN_CHK_EVENT1       : 1;    /*!< [17..17] Go to HSI if active clock is low                                 */
      __IOM MDR_OnOff   EN_CHK_EVENT2       : 1;    /*!< [18..18] Go to HSI if active clock is High                                */
      __IOM MDR_OnOff   EN_CHK_EVENT3       : 1;    /*!< [19..19] Go to HSI if active clock is Highest                             */
      __IOM MDR_OnOff   EN_CHK              : 1;    /*!< [20..20] Clock Checker enable                                             */
      __IOM MDR_OnOff   CLR_CHK_SHIFT_REG0  : 1;    /*!< [21..21] Clear Min Freq level                                             */
      __IOM MDR_OnOff   CLR_CHK_SHIFT_REG1  : 1;    /*!< [22..22] Clear Max Freq level                                             */
      __IOM MDR_OnOff   CLR_CHK_EVENT0      : 1;    /*!< [23..23] Clear no freq event                                              */
      __IOM MDR_OnOff   CLR_CHK_EVENT1      : 1;    /*!< [24..24] Clear low freq event                                             */
      __IOM MDR_OnOff   CLR_CHK_EVENT2      : 1;    /*!< [25..25] Clear high freq event                                            */
      __IOM MDR_OnOff   CLR_CHK_EVENT3      : 1;    /*!< [26..26] Clear highest freq event                                         */
      __IOM MDR_OnOff   HSE_ON              : 1;    /*!< [27..27] Generator Enable                                                 */
      __IOM MDR_OnOff   HSE_BYP             : 1;    /*!< [28..28] ByPass Mode                                                      */
      __IOM MDR_OnOff   FILTER_EN           : 1;    /*!< [29..29] Filter Enable                                                    */
      __IM uint32_t                         : 2;
} MDR_RST_HSE_CLK_Bits;

#define MDR_RST_HSE_EN_CHK_EVENT0_Pos   (16UL)            /*!< MDR_RST_CLOCK HSE0_CLK: EN_CHK_EVENT0 (Bit 16)        */
#define MDR_RST_HSE_EN_CHK_EVENT0_Msk   (0x10000UL)       /*!< MDR_RST_CLOCK HSE0_CLK: EN_CHK_EVENT0 (Bitfield-Mask: 0x01) */
#define MDR_RST_HSE_EN_CHK_EVENT1_Pos   (17UL)            /*!< MDR_RST_CLOCK HSE0_CLK: EN_CHK_EVENT1 (Bit 17)        */
#define MDR_RST_HSE_EN_CHK_EVENT1_Msk   (0x20000UL)       /*!< MDR_RST_CLOCK HSE0_CLK: EN_CHK_EVENT1 (Bitfield-Mask: 0x01) */
#define MDR_RST_HSE_EN_CHK_EVENT2_Pos   (18UL)            /*!< MDR_RST_CLOCK HSE0_CLK: EN_CHK_EVENT2 (Bit 18)        */
#define MDR_RST_HSE_EN_CHK_EVENT2_Msk   (0x40000UL)       /*!< MDR_RST_CLOCK HSE0_CLK: EN_CHK_EVENT2 (Bitfield-Mask: 0x01) */
#define MDR_RST_HSE_EN_CHK_EVENT3_Pos   (19UL)            /*!< MDR_RST_CLOCK HSE0_CLK: EN_CHK_EVENT3 (Bit 19)        */
#define MDR_RST_HSE_EN_CHK_EVENT3_Msk   (0x80000UL)       /*!< MDR_RST_CLOCK HSE0_CLK: EN_CHK_EVENT3 (Bitfield-Mask: 0x01) */
#define MDR_RST_HSE_EN_CHK_Pos          (20UL)            /*!< MDR_RST_CLOCK HSE0_CLK: EN_CHK (Bit 20)               */
#define MDR_RST_HSE_EN_CHK_Msk          (0x100000UL)      /*!< MDR_RST_CLOCK HSE0_CLK: EN_CHK (Bitfield-Mask: 0x01)  */
#define MDR_RST_HSE_CLR_CHK_SHIFT_REG0_Pos (21UL)         /*!< MDR_RST_CLOCK HSE0_CLK: CLR_CHK_SHIFT_REG0 (Bit 21)   */
#define MDR_RST_HSE_CLR_CHK_SHIFT_REG0_Msk (0x200000UL)   /*!< MDR_RST_CLOCK HSE0_CLK: CLR_CHK_SHIFT_REG0 (Bitfield-Mask: 0x01) */
#define MDR_RST_HSE_CLR_CHK_SHIFT_REG1_Pos (22UL)         /*!< MDR_RST_CLOCK HSE0_CLK: CLR_CHK_SHIFT_REG1 (Bit 22)   */
#define MDR_RST_HSE_CLR_CHK_SHIFT_REG1_Msk (0x400000UL)   /*!< MDR_RST_CLOCK HSE0_CLK: CLR_CHK_SHIFT_REG1 (Bitfield-Mask: 0x01) */
#define MDR_RST_HSE_CLR_CHK_EVENT0_Pos  (23UL)            /*!< MDR_RST_CLOCK HSE0_CLK: CLR_CHK_EVENT0 (Bit 23)       */
#define MDR_RST_HSE_CLR_CHK_EVENT0_Msk  (0x800000UL)      /*!< MDR_RST_CLOCK HSE0_CLK: CLR_CHK_EVENT0 (Bitfield-Mask: 0x01) */
#define MDR_RST_HSE_CLR_CHK_EVENT1_Pos  (24UL)            /*!< MDR_RST_CLOCK HSE0_CLK: CLR_CHK_EVENT1 (Bit 24)       */
#define MDR_RST_HSE_CLR_CHK_EVENT1_Msk  (0x1000000UL)     /*!< MDR_RST_CLOCK HSE0_CLK: CLR_CHK_EVENT1 (Bitfield-Mask: 0x01) */
#define MDR_RST_HSE_CLR_CHK_EVENT2_Pos  (25UL)            /*!< MDR_RST_CLOCK HSE0_CLK: CLR_CHK_EVENT2 (Bit 25)       */
#define MDR_RST_HSE_CLR_CHK_EVENT2_Msk  (0x2000000UL)     /*!< MDR_RST_CLOCK HSE0_CLK: CLR_CHK_EVENT2 (Bitfield-Mask: 0x01) */
#define MDR_RST_HSE_CLR_CHK_EVENT3_Pos  (26UL)            /*!< MDR_RST_CLOCK HSE0_CLK: CLR_CHK_EVENT3 (Bit 26)       */
#define MDR_RST_HSE_CLR_CHK_EVENT3_Msk  (0x4000000UL)     /*!< MDR_RST_CLOCK HSE0_CLK: CLR_CHK_EVENT3 (Bitfield-Mask: 0x01) */
#define MDR_RST_HSE_HSE_ON_Pos          (27UL)            /*!< MDR_RST_CLOCK HSE0_CLK: HSE_ON (Bit 27)               */
#define MDR_RST_HSE_HSE_ON_Msk          (0x8000000UL)     /*!< MDR_RST_CLOCK HSE0_CLK: HSE_ON (Bitfield-Mask: 0x01)  */
#define MDR_RST_HSE_HSE_BYP_Pos         (28UL)            /*!< MDR_RST_CLOCK HSE0_CLK: HSE_BYP (Bit 28)              */
#define MDR_RST_HSE_HSE_BYP_Msk         (0x10000000UL)    /*!< MDR_RST_CLOCK HSE0_CLK: HSE_BYP (Bitfield-Mask: 0x01) */
#define MDR_RST_HSE_FILTER_EN_Pos       (29UL)            /*!< MDR_RST_CLOCK HSE0_CLK: FILTER_EN (Bit 29)            */
#define MDR_RST_HSE_FILTER_EN_Msk       (0x20000000UL)    /*!< MDR_RST_CLOCK HSE0_CLK: FILTER_EN (Bitfield-Mask: 0x01) */


//--------------- SYNC PeriphClock Bits (CPU Clock)  ------------------ 
typedef struct {
      __IOM uint32_t    DIV        : 16;           /*!< [15..0] MAX_Clock Div to PeriphClock                                      */
      __IOM MDR_OnOff   CLK_EN     : 1;            /*!< [16..16] PeriphClock Enable                                               */
      __IM  uint32_t               : 15;
} MDR_RST_SYNC_CLK_Bits;

#define MDR_RST_SYNC_CLK_DIV_Pos     (0UL)                     /*!< MDR_RST_CLOCK ETH_CLK: DIV (Bit 0)                    */
#define MDR_RST_SYNC_CLK_DIV_Msk     (0xffffUL)                /*!< MDR_RST_CLOCK ETH_CLK: DIV (Bitfield-Mask: 0xffff)    */
#define MDR_RST_SYNC_CLK_CLK_EN_Pos  (16UL)                    /*!< MDR_RST_CLOCK ETH_CLK: CLK_EN (Bit 16)                */
#define MDR_RST_SYNC_CLK_CLK_EN_Msk  (0x10000UL)               /*!< MDR_RST_CLOCK ETH_CLK: CLK_EN (Bitfield-Mask: 0x01)   */


//--------------- ASYNC PeriphClock Bits (CPU Clock)  ------------------ 
typedef enum {                                  /*!< MDR_RST_CLOCK_ETH_CLK_SELECT                                              */
  MDR_RST_ASYNC_IN_HSI     = 0,     /*!< HSI : Clock Source                                                        */
  MDR_RST_ASYNC_IN_HSE0    = 1,     /*!< HSE0 : Clock Source                                                       */
  MDR_RST_ASYNC_IN_HSE1    = 2,     /*!< HSE1 : Clock Source                                                       */
  MDR_RST_ASYNC_IN_LSI     = 3,     /*!< LSI : Clock Source                                                        */
  MDR_RST_ASYNC_IN_LSE     = 4,     /*!< LSE : Clock Source                                                        */
  MDR_RST_ASYNC_IN_PLL0    = 5,     /*!< PLL0 : Clock Source                                                       */
  MDR_RST_ASYNC_IN_PLL1    = 6,     /*!< PLL1 : Clock Source                                                       */
  MDR_RST_ASYNC_IN_PLL2    = 7,     /*!< PLL2 : Clock Source                                                       */
  MDR_RST_ASYNC_IN_MAX_CLK = 13,    /*!< MAX_CLK : Clock Source                                                    */
} MDR_RST_ASYNC_IN_SEL;

typedef struct {
      __IOM uint32_t              DIV        : 16;           /*!< [15..0] Div to PeriphClock                                                */
      __IOM MDR_OnOff             CLK_EN     : 1;            /*!< [16..16] PeriphClock Enable                                               */
      __IM  uint32_t                         : 11;
      __IOM MDR_RST_ASYNC_IN_SEL  SELECT     : 4;            /*!< [31..28] PeriphClock Enable                                               */
} MDR_RST_ASYNC_CLK_Bits;

#define MDR_RST_ASYNC_CLK_DIV_Pos     (0UL)                     /*!< MDR_RST_CLOCK ETH_CLK: DIV (Bit 0)                    */
#define MDR_RST_ASYNC_CLK_DIV_Msk     (0xffffUL)                /*!< MDR_RST_CLOCK ETH_CLK: DIV (Bitfield-Mask: 0xffff)    */
#define MDR_RST_ASYNC_CLK_CLK_EN_Pos  (16UL)                    /*!< MDR_RST_CLOCK ETH_CLK: CLK_EN (Bit 16)                */
#define MDR_RST_ASYNC_CLK_CLK_EN_Msk  (0x10000UL)               /*!< MDR_RST_CLOCK ETH_CLK: CLK_EN (Bitfield-Mask: 0x01)   */
#define MDR_RST_ASYNC_CLK_SELECT_Pos  (28UL)                    /*!< MDR_RST_CLOCK ETH_CLK: SELECT (Bit 28)                */
#define MDR_RST_ASYNC_CLK_SELECT_Msk  (0xf0000000UL)            /*!< MDR_RST_CLOCK ETH_CLK: SELECT (Bitfield-Mask: 0x0f)   */



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

#endif  //_MDR_RST_VE8X_DEFS_H
