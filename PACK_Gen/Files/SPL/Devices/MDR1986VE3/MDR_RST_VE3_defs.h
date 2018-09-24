#ifndef _MDR_RST_VE3_DEFS_H
#define _MDR_RST_VE3_DEFS_H

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
      __IM  uint32_t                     : 2;
      __IOM MDR_CLK_SEL_HSIE2 AUC_C1_SEL : 2;            /*!< [17..16] AUC_C1 mux input select                                 */
      __IM  uint32_t                     : 2;
      __IOM MDR_CLK_AUC_C2    AUC_C2_SEL : 2;            /*!< [21..20] AUC_C2 mux input select                                 */
      __IM  uint32_t                     : 2;
      __IOM MDR_CLK_DIV_256   AUC_C3_SEL : 4;            /*!< [27..24] AUC_C3 mux input select                                 */
      __IM  uint32_t                     : 3;
      __IOM MDR_OnOff         AUC_CLK_EN : 1;            /*!< [31..31] AudioCodec Clock Enable                                 */
} MDR_RST_ADC_Bits;

#define MDR_RST_ADC__ADC_C1_SEL_Pos (0UL)                /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C1_SEL (Bit 0)                      */
#define MDR_RST_ADC__ADC_C1_SEL_Msk (0x3UL)              /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C1_SEL (Bitfield-Mask: 0x03)        */
#define MDR_RST_ADC__ADC_C2_SEL_Pos (4UL)                /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C2_SEL (Bit 4)                      */
#define MDR_RST_ADC__ADC_C2_SEL_Msk (0x30UL)             /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C2_SEL (Bitfield-Mask: 0x03)        */
#define MDR_RST_ADC__ADC_C3_SEL_Pos (8UL)                /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C3_SEL (Bit 8)                      */
#define MDR_RST_ADC__ADC_C3_SEL_Msk (0xf00UL)            /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C3_SEL (Bitfield-Mask: 0x0f)        */
#define MDR_RST_ADC__ADC_CLK_EN_Pos (13UL)               /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_CLK_EN (Bit 13)                     */
#define MDR_RST_ADC__ADC_CLK_EN_Msk (0x2000UL)           /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_ADC__AUC_C1_SEL_Pos (16UL)               /*!< MDR_RST_CLOCK ADC_CLOCK: AUC_C1_SEL (Bit 16)                     */
#define MDR_RST_ADC__AUC_C1_SEL_Msk (0x30000UL)          /*!< MDR_RST_CLOCK ADC_CLOCK: AUC_C1_SEL (Bitfield-Mask: 0x03)        */
#define MDR_RST_ADC__AUC_C2_SEL_Pos (20UL)               /*!< MDR_RST_CLOCK ADC_CLOCK: AUC_C2_SEL (Bit 20)                     */
#define MDR_RST_ADC__AUC_C2_SEL_Msk (0x300000UL)         /*!< MDR_RST_CLOCK ADC_CLOCK: AUC_C2_SEL (Bitfield-Mask: 0x03)        */
#define MDR_RST_ADC__AUC_C3_SEL_Pos (24UL)               /*!< MDR_RST_CLOCK ADC_CLOCK: AUC_C3_SEL (Bit 24)                     */
#define MDR_RST_ADC__AUC_C3_SEL_Msk (0xf000000UL)        /*!< MDR_RST_CLOCK ADC_CLOCK: AUC_C3_SEL (Bitfield-Mask: 0x0f)        */
#define MDR_RST_ADC__AUC_CLK_EN_Pos (31UL)               /*!< MDR_RST_CLOCK ADC_CLOCK: AUC_CLK_EN (Bit 31)                     */
#define MDR_RST_ADC__AUC_CLK_EN_Msk (0x80000000UL)       /*!< MDR_RST_CLOCK ADC_CLOCK: AUC_CLK_EN (Bitfield-Mask: 0x01)        */


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
      __IOM MDR_OnOff         ETH2_CLK_EN : 1;            /*!< [30..30] Ethernet2 MAC Clock Enable                              */  
      __IM  uint32_t                      : 1;
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
#define MDR_RST_ETH__ETH2_CLK_EN_Pos (30UL)              /*!< MDR_RST_CLOCK ETH_CLOCK: ETH2_CLK_EN (Bit 30)         */
#define MDR_RST_ETH__ETH2_CLK_EN_Msk (0x40000000UL)      /*!< MDR_RST_CLOCK ETH_CLOCK: ETH2_CLK_EN (Bitfield-Mask: 0x01) */


/* ======================================================  PER2_CLOCK  =======================================================  */
typedef struct {
      __IOM MDR_OnOff   AUC_CLK_EN   : 1;          /*!< [0..0] AudioCodec Clock Enable                                          */
      __IOM MDR_OnOff   LED_CLK_EN   : 1;          /*!< [1..1] LED Clock Enable                                                 */
      __IOM MDR_OnOff   KEY_CLK_EN   : 1;          /*!< [2..2] Keyboard Clock Enable                                            */
      __IOM MDR_OnOff   PORTG_CLK_EN : 1;          /*!< [3..3] PORT_G Clock Enable                                              */
      __IOM MDR_OnOff   UART3_CLK_EN : 1;          /*!< [4..4] UART3 Clock Enable                                               */
      __IOM MDR_OnOff   UART4_CLK_EN : 1;          /*!< [5..5] UART4 Clock Enable                                               */
      __IOM MDR_OnOff   SSP4_CLK_EN  : 1;          /*!< [6..6] SSP4 Clock Enable                                                */
      __IOM MDR_OnOff   PORTH_CLK_EN : 1;          /*!< [7..7] PORT_H Clock Enable                                              */
      __IOM MDR_OnOff   PORTI_CLK_EN : 1;          /*!< [8..8] PORT_I Clock Enable                                              */
      __IM uint32_t                  : 23;
} MDR_RST_PER2_Bits;

#define MDR_RST_PER2__AUC_CLK_EN_Pos   (0UL)             /*!< MDR_RST_CLOCK PER2_CLOCK: AUC_CLK_EN (Bit 0)                      */
#define MDR_RST_PER2__AUC_CLK_EN_Msk   (0x1UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: AUC_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_PER2__LED_CLK_EN_Pos   (1UL)             /*!< MDR_RST_CLOCK PER2_CLOCK: LED_CLK_EN (Bit 1)                      */
#define MDR_RST_PER2__LED_CLK_EN_Msk   (0x2UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: LED_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_PER2__KEY_CLK_EN_Pos   (2UL)             /*!< MDR_RST_CLOCK PER2_CLOCK: KEY_CLK_EN (Bit 2)                      */
#define MDR_RST_PER2__KEY_CLK_EN_Msk   (0x4UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: KEY_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_PER2__PORTG_CLK_EN_Pos (3UL)             /*!< MDR_RST_CLOCK PER2_CLOCK: PORTG_CLK_EN (Bit 3)                    */
#define MDR_RST_PER2__PORTG_CLK_EN_Msk (0x8UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: PORTG_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_PER2__UART3_CLK_EN_Pos (4UL)             /*!< MDR_RST_CLOCK PER2_CLOCK: UART3_CLK_EN (Bit 4)                    */
#define MDR_RST_PER2__UART3_CLK_EN_Msk (0x10UL)          /*!< MDR_RST_CLOCK PER2_CLOCK: UART3_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_PER2__UART4_CLK_EN_Pos (5UL)             /*!< MDR_RST_CLOCK PER2_CLOCK: UART4_CLK_EN (Bit 5)                    */
#define MDR_RST_PER2__UART4_CLK_EN_Msk (0x20UL)          /*!< MDR_RST_CLOCK PER2_CLOCK: UART4_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_PER2__SSP4_CLK_EN_Pos  (6UL)             /*!< MDR_RST_CLOCK PER2_CLOCK: SSP4_CLK_EN (Bit 6)                     */
#define MDR_RST_PER2__SSP4_CLK_EN_Msk  (0x40UL)          /*!< MDR_RST_CLOCK PER2_CLOCK: SSP4_CLK_EN (Bitfield-Mask: 0x01)       */
#define MDR_RST_PER2__PORTH_CLK_EN_Pos (7UL)             /*!< MDR_RST_CLOCK PER2_CLOCK: PORTH_CLK_EN (Bit 7)                    */
#define MDR_RST_PER2__PORTH_CLK_EN_Msk (0x80UL)          /*!< MDR_RST_CLOCK PER2_CLOCK: PORTH_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_PER2__PORTI_CLK_EN_Pos (8UL)             /*!< MDR_RST_CLOCK PER2_CLOCK: PORTI_CLK_EN (Bit 8)                    */
#define MDR_RST_PER2__PORTI_CLK_EN_Msk (0x100UL)         /*!< MDR_RST_CLOCK PER2_CLOCK: PORTI_CLK_EN (Bitfield-Mask: 0x01)      */

/* ====================================================  UART_SSP_CLOCK  ===================================================== */
typedef struct {
      __IOM MDR_BRG_DIV_128  UART3_BRG  : 3;          /*!< [2..0] HCLK freq divider to get UART3_CLOCK, [/1, /2, /4 .. /128]    */
      __IM  uint32_t                    : 5;
      __IOM MDR_BRG_DIV_128  UART4_BRG  : 3;          /*!< [10..8] HCLK freq divider to get UART4_CLOCK, [/1, /2, /4 .. /128]   */
      __IM  uint32_t                    : 5;
      __IOM MDR_BRG_DIV_128  SSP3_BRG   : 3;          /*!< [18..16] HCLK freq divider to get SSP3_CLOCK, [/1, /2, /4 .. /128]   */
      __IM  uint32_t                    : 5;
      __IOM MDR_OnOff      UART3_CLK_EN : 1;          /*!< [24..24] UART3_CLOCK enable                                          */
      __IOM MDR_OnOff      UART4_CLK_EN : 1;          /*!< [25..25] UART4_CLOCK enable                                          */
      __IOM MDR_OnOff       SSP3_CLK_EN : 1;          /*!< [26..26] SSP3_CLOCK enable                                           */
      __IM uint32_t                     : 5;
} MDR_RST_UARTSSP_Bits;

#define MDR_RST_UARTSSP__UART3_BRG_Pos    (0UL)          /*!< MDR_RST_CLOCK UART_SSP_CLOCK: UART3_BRG (Bit 0)                   */
#define MDR_RST_UARTSSP__UART3_BRG_Msk    (0x7UL)        /*!< MDR_RST_CLOCK UART_SSP_CLOCK: UART3_BRG (Bitfield-Mask: 0x07)     */
#define MDR_RST_UARTSSP__UART4_BRG_Pos    (8UL)          /*!< MDR_RST_CLOCK UART_SSP_CLOCK: UART4_BRG (Bit 8)                   */
#define MDR_RST_UARTSSP__UART4_BRG_Msk    (0x700UL)      /*!< MDR_RST_CLOCK UART_SSP_CLOCK: UART4_BRG (Bitfield-Mask: 0x07)     */
#define MDR_RST_UARTSSP__SSP3_BRG_Pos     (16UL)         /*!< MDR_RST_CLOCK UART_SSP_CLOCK: SSP3_BRG (Bit 16)                   */
#define MDR_RST_UARTSSP__SSP3_BRG_Msk     (0x70000UL)    /*!< MDR_RST_CLOCK UART_SSP_CLOCK: SSP3_BRG (Bitfield-Mask: 0x07)      */
#define MDR_RST_UARTSSP__UART3_CLK_EN_Pos (24UL)         /*!< MDR_RST_CLOCK UART_SSP_CLOCK: UART3_CLK_EN (Bit 24)               */
#define MDR_RST_UARTSSP__UART3_CLK_EN_Msk (0x1000000UL)  /*!< MDR_RST_CLOCK UART_SSP_CLOCK: UART3_CLK_EN (Bitfield-Mask: 0x01)  */
#define MDR_RST_UARTSSP__UART4_CLK_EN_Pos (25UL)         /*!< MDR_RST_CLOCK UART_SSP_CLOCK: UART4_CLK_EN (Bit 25)               */
#define MDR_RST_UARTSSP__UART4_CLK_EN_Msk (0x2000000UL)  /*!< MDR_RST_CLOCK UART_SSP_CLOCK: UART4_CLK_EN (Bitfield-Mask: 0x01)  */
#define MDR_RST_UARTSSP__SSP3_CLK_EN_Pos  (26UL)         /*!< MDR_RST_CLOCK UART_SSP_CLOCK: SSP3_CLK_EN (Bit 26)                */
#define MDR_RST_UARTSSP__SSP3_CLK_EN_Msk  (0x4000000UL)  /*!< MDR_RST_CLOCK UART_SSP_CLOCK: SSP3_CLK_EN (Bitfield-Mask: 0x01)   */


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
  union {
    __IOM uint32_t       PER2_CLOCK;                  /*!< (@ 0x00000038) Peripherials Clock Control 2                               */
    MDR_RST_PER2_Bits    PER2_CLOCK_b;
  } ;
  union {
    __IOM uint32_t        UART_SSP_CLOCK;              /*!< (@ 0x0000003C) UART and SSP Clock Control                                 */
    MDR_RST_UARTSSP_Bits  UART_SSP_CLOCK_b;
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

#endif  //_MDR_RST_VE3_DEFS_H
