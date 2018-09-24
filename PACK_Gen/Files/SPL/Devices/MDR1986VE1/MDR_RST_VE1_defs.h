#ifndef _MDR_RST_VE1_DEFS_H
#define _MDR_RST_VE1_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


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

#include "MDR_RST_VE1x_defs.h"


/* =======================================================  ADC_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_CLK_ADC_C1    ADC_C1_SEL : 2;            /*!< [1..0] ADC_C1 mux freq select                                    */
      __IM  uint32_t                     : 2;
      __IOM MDR_CLK_ADC_C2    ADC_C2_SEL : 2;            /*!< [5..4] ADC_C2 mux freq select                                    */
      __IM  uint32_t                     : 2;
      __IOM MDR_CLK_DIV_256   ADC_C3_SEL : 4;            /*!< [11..8] ADC_C2 mux output freq devider, [/1, /2, /4 .. /256]     */
      __IM  uint32_t                     : 1;
      __IOM MDR_OnOff         ADC_CLK_EN : 1;            /*!< [13..13] ADC Clock Enable                                        */
      __IM  uint32_t                     : 18;
} MDR_RST_ADC_Bits;

#define MDR_RST_ADC__ADC_C1_SEL_Pos (0UL)                /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C1_SEL (Bit 0)                      */
#define MDR_RST_ADC__ADC_C1_SEL_Msk (0x3UL)              /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C1_SEL (Bitfield-Mask: 0x03)        */
#define MDR_RST_ADC__ADC_C2_SEL_Pos (4UL)                /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C2_SEL (Bit 4)                      */
#define MDR_RST_ADC__ADC_C2_SEL_Msk (0x30UL)             /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C2_SEL (Bitfield-Mask: 0x03)        */
#define MDR_RST_ADC__ADC_C3_SEL_Pos (8UL)                /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C3_SEL (Bit 8)                      */
#define MDR_RST_ADC__ADC_C3_SEL_Msk (0xf00UL)            /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C3_SEL (Bitfield-Mask: 0x0f)        */
#define MDR_RST_ADC__ADC_CLK_EN_Pos (13UL)               /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_CLK_EN (Bit 13)                     */
#define MDR_RST_ADC__ADC_CLK_EN_Msk (0x2000UL)           /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_CLK_EN (Bitfield-Mask: 0x01)        */


/* =======================================================  ETH_CLOCK  ======================================================= */
typedef struct {
      __IOM uint32_t          ETH_BRG     : 8;            /*!< [7..0] Always set to 0!                                          */
      __IOM MDR_BRG_DIV_128   MIL_BRG     : 3;            /*!< [10..8] HCLK freq divider to get MAN_CLOCK, [/1, /2, /4 .. /128] */
      __IM  uint32_t                      : 5;
      __IOM MDR_BRG_DIV_128   PHY_BRG     : 3;            /*!< [18..16] HCLK freq divider to get PHY_CLOCK, [/1, /2, /4 .. /128]*/
      __IM  uint32_t                      : 5;
      __IOM MDR_OnOff         ETH_CLK_EN  : 1;            /*!< [24..24] Ethernet MAC Clock Enable                               */
      __IOM MDR_OnOff         MIL_CLK_EN  : 1;            /*!< [25..25] MIL-STD CLOCK Enable                                    */
      __IOM MDR_OnOff         SLEEP       : 1;            /*!< [26..26] Switch to Sleep mode                                    */
      __IOM MDR_OnOff         PHY_CLK_EN  : 1;            /*!< [27..27] Ethernet PHY CLOCK Enable                               */
      __IOM MDR_CLK_SEL_PHY   PHY_CLK_SEL : 2;            /*!< [29..28] Ethernet PHY CLOCK Select                               */
      __IM  uint32_t                      : 2;
} MDR_RST_ETH_Bits;


#define MDR_RST_ETH__ETH_BRG_Pos     (0UL)                /*!< MDR_RST_CLOCK ETH_CLOCK: ETH_BRG (Bit 0)                         */
#define MDR_RST_ETH__ETH_BRG_Msk     (0xffUL)             /*!< MDR_RST_CLOCK ETH_CLOCK: ETH_BRG (Bitfield-Mask: 0xff)           */
#define MDR_RST_ETH__MIL_BRG_Pos     (8UL)                /*!< MDR_RST_CLOCK ETH_CLOCK: MIL_BRG (Bit 8)                         */
#define MDR_RST_ETH__MIL_BRG_Msk     (0x700UL)            /*!< MDR_RST_CLOCK ETH_CLOCK: MIL_BRG (Bitfield-Mask: 0x07)           */
#define MDR_RST_ETH__PHY_BRG_Pos     (16UL)               /*!< MDR_RST_CLOCK ETH_CLOCK: PHY_BRG (Bit 16)                        */
#define MDR_RST_ETH__PHY_BRG_Msk     (0x70000UL)          /*!< MDR_RST_CLOCK ETH_CLOCK: PHY_BRG (Bitfield-Mask: 0x07)           */
#define MDR_RST_ETH__ETH_CLK_EN_Pos  (24UL)               /*!< MDR_RST_CLOCK ETH_CLOCK: ETH_CLK_EN (Bit 24)                     */
#define MDR_RST_ETH__ETH_CLK_EN_Msk  (0x1000000UL)        /*!< MDR_RST_CLOCK ETH_CLOCK: ETH_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_ETH__MIL_CLK_EN_Pos  (25UL)               /*!< MDR_RST_CLOCK ETH_CLOCK: MIL_CLK_EN (Bit 25)                     */
#define MDR_RST_ETH__MIL_CLK_EN_Msk  (0x2000000UL)        /*!< MDR_RST_CLOCK ETH_CLOCK: MIL_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_ETH__SLEEP_Pos       (26UL)               /*!< MDR_RST_CLOCK ETH_CLOCK: SLEEP (Bit 26)                          */
#define MDR_RST_ETH__SLEEP_Msk       (0x4000000UL)        /*!< MDR_RST_CLOCK ETH_CLOCK: SLEEP (Bitfield-Mask: 0x01)             */
#define MDR_RST_ETH__PHY_CLK_EN_Pos  (27UL)               /*!< MDR_RST_CLOCK ETH_CLOCK: PHY_CLK_EN (Bit 27)                     */
#define MDR_RST_ETH__PHY_CLK_EN_Msk  (0x8000000UL)        /*!< MDR_RST_CLOCK ETH_CLOCK: PHY_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_ETH__PHY_CLK_SEL_Pos (28UL)               /*!< MDR_RST_CLOCK ETH_CLOCK: PHY_CLK_SEL (Bit 28)                    */
#define MDR_RST_ETH__PHY_CLK_SEL_Msk (0x30000000UL)       /*!< MDR_RST_CLOCK ETH_CLOCK: PHY_CLK_SEL (Bitfield-Mask: 0x03)       */


/* =============================================  RST CLOCK Block  ========================================================= */

typedef struct {                                /*!<       MDR_RST_CLOCK Structure                                    */
  union {
    __IM  uint32_t       CLOCK_STATUS;                /*!< (@ 0x00000000) Clock Status Register                                      */
    MDR_RST_STATUS_Bits  CLOCK_STATUS_b;
  };  
  union {
    __IOM uint32_t       PLL_CONTROL;                 /*!< (@ 0x00000004) PLL Control Register                                       */
    MDR_RST_PLL_Bits     PLL_CONTROL_b;
  };  
  union {
    __IOM uint32_t       HS_CONTROL;                  /*!< (@ 0x00000008) HSE Generator Control                                      */
    MDR_RST_HS_Bits      HS_CONTROL_b;
  };  
  union {
    __IOM uint32_t       CPU_CLOCK;                   /*!< (@ 0x0000000C) CPU Clock Control                                          */
    MDR_RST_CPU_Bits     CPU_CLOCK_b;
  };
  union {
    __IOM uint32_t       USB_CLOCK;                   /*!< (@ 0x00000010) USB Clock Control                                          */
    MDR_RST_USB_Bits     USB_CLOCK_b;
  };
  union {
    __IOM uint32_t       ADC_CLOCK;                   /*!< (@ 0x00000014) ADC Clock Control                                          */
    MDR_RST_ADC_Bits     ADC_CLOCK_b;
  };  
  union {
    __IOM uint32_t       RTC_CLOCK;                   /*!< (@ 0x00000018) RTC Clock Control                                          */
    MDR_RST_RTC_Bits     RTC_CLOCK_b;
  };
  union {
    __IOM uint32_t       PER_CLOCK;                   /*!< (@ 0x0000001C) Peripherials Clock Control                                 */
    MDR_RST_PER_Bits     PER_CLOCK_b;
  }; 
  union {
    __IOM uint32_t       CAN_CLOCK;                   /*!< (@ 0x00000020) CAN's Clock Control                                        */
    MDR_RST_CAN_Bits     CAN_CLOCK_b;
  } ;
  union {
    __IOM uint32_t       TIM_CLOCK;                   /*!< (@ 0x00000024) Timer's Clock Control                                      */
    MDR_RST_TIM_Bits     TIM_CLOCK_b;
  };  
  union {
    __IOM uint32_t       UART_CLOCK;                  /*!< (@ 0x00000028) UART's Clock Control                                       */
    MDR_RST_UART_Bits    UART_CLOCK_b;
  };  
  union {
    __IOM uint32_t       SSP_CLOCK;                   /*!< (@ 0x0000002C) SSP's Clock Control                                        */
    MDR_RST_SSP_Bits     SSP_CLOCK_b;
  };

  __IM  uint32_t         RESERVED;                    /*!< (@ 0x00000030) RESERVED                                                    */

  union {
    __IOM uint32_t       ETH_CLOCK;                   /*!< (@ 0x00000034) Ethernet and MIL Clock Control                             */
    MDR_RST_ETH_Bits     ETH_CLOCK_b;
  } ;

} MDR_RST_CLOCK_Type;


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

#endif  //_MDR_RST_VE1_DEFS_H
