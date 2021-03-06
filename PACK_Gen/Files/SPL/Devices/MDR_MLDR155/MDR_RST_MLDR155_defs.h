#ifndef _MDR_RST_ESila_DEFS_H
#define _MDR_RST_ESila_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <MDR_RST_VE8x_defs.h>


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

#define MDR_HAS_PLL3

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
  MAXCLK_PLL3     = 11,
  MAXCLK_ERR      = 12,   //  Error Value - reserved
} MDR_MAXCLK_SEL;

typedef struct {
      __IOM MDR_MAXCLK_SEL  Select : 4;            /*!< [3..0] Select MAX_CLOCK source                                            */
      __IM  uint32_t               : 28;
} MDR_RST_MAX_CLK_Bits;

#define MDR_RST_CLOCK_MAX_CLK_Select_Pos  (0UL)                     /*!< MDR_RST_CLOCK MAX_CLK: Select (Bit 0)                 */
#define MDR_RST_CLOCK_MAX_CLK_Select_Msk  (0xfUL)                   /*!< MDR_RST_CLOCK MAX_CLK: Select (Bitfield-Mask: 0x0f)   */


//---------------   PER Clock  ---------------
typedef struct {
      __IM  uint32_t            : 13;
      __IOM MDR_OnOff PortA_CLK_EN : 1;          /*!< [13..13] GPIO Port Clock Enable                                           */
      __IOM MDR_OnOff PortB_CLK_EN : 1;          /*!< [14..14] GPIO Port Clock Enable                                           */
      __IOM MDR_OnOff PortC_CLK_EN : 1;          /*!< [15..15] GPIO Port Clock Enable                                           */
      __IOM MDR_OnOff PortD_CLK_EN : 1;          /*!< [16..16] GPIO Port Clock Enable                                           */
      __IM  uint32_t            : 4;
      __IOM MDR_OnOff SDIO_CLK_EN : 1;           /*!< [21..21] SDIO Clock Enable                                                */
      __IOM MDR_OnOff SSP1_CLK_EN : 1;           /*!< [22..22] SSP1 Clock Enable                                                */
      __IOM MDR_OnOff SSP2_CLK_EN : 1;           /*!< [23..23] SSP2 Clock Enable                                                */
      __IOM MDR_OnOff CAN1_CLK_EN : 1;           /*!< [24..24] CAN1 Clock Enable                                                */
      __IOM MDR_OnOff CAN2_CLK_EN : 1;           /*!< [25..25] CAN2 Clock Enable                                                */
      __IOM MDR_OnOff UART1_CLK_EN : 1;          /*!< [26..26] UART1 Clock Enable                                               */
      __IOM MDR_OnOff UART2_CLK_EN : 1;          /*!< [27..27] UART2 Clock Enable                                               */
      __IOM MDR_OnOff UART3_CLK_EN : 1;          /*!< [28..28] UART3 Clock Enable                                               */
      __IOM MDR_OnOff UART4_CLK_EN : 1;          /*!< [29..29] UART4 Clock Enable                                               */
      __IOM MDR_OnOff MIL_CLK_EN : 1;            /*!< [30..30] MIL Clock Enable                                                 */
      __IOM MDR_OnOff USB_CLK_EN : 1;            /*!< [31..31] USB Clock Enable                                                 */
} MDR_RST_PER0_Bits;

#define MDR_RST_PER0_PORTA_CLK_EN_Pos (13UL)              /*!< MDR_RST_CLOCK PER0_CLK: PortA_CLK_EN (Bit 13)         */
#define MDR_RST_PER0_PORTA_CLK_EN_Msk (0x2000UL)          /*!< MDR_RST_CLOCK PER0_CLK: PortA_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_PORTB_CLK_EN_Pos (14UL)              /*!< MDR_RST_CLOCK PER0_CLK: PortB_CLK_EN (Bit 14)         */
#define MDR_RST_PER0_PORTB_CLK_EN_Msk (0x4000UL)          /*!< MDR_RST_CLOCK PER0_CLK: PortB_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_PORTC_CLK_EN_Pos (15UL)              /*!< MDR_RST_CLOCK PER0_CLK: PortC_CLK_EN (Bit 15)         */
#define MDR_RST_PER0_PORTC_CLK_EN_Msk (0x8000UL)          /*!< MDR_RST_CLOCK PER0_CLK: PortC_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_PORTD_CLK_EN_Pos (16UL)              /*!< MDR_RST_CLOCK PER0_CLK: PortD_CLK_EN (Bit 16)         */
#define MDR_RST_PER0_PORTD_CLK_EN_Msk (0x10000UL)         /*!< MDR_RST_CLOCK PER0_CLK: PortD_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_SDIO_CLK_EN_Pos (21UL)               /*!< MDR_RST_CLOCK PER0_CLK: SDIO_CLK_EN (Bit 21)          */
#define MDR_RST_PER0_SDIO_CLK_EN_Msk (0x200000UL)         /*!< MDR_RST_CLOCK PER0_CLK: SDIO_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_SSP1_CLK_EN_Pos (22UL)               /*!< MDR_RST_CLOCK PER0_CLK: SSP1_CLK_EN (Bit 22)          */
#define MDR_RST_PER0_SSP1_CLK_EN_Msk (0x400000UL)         /*!< MDR_RST_CLOCK PER0_CLK: SSP1_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_SSP2_CLK_EN_Pos (23UL)               /*!< MDR_RST_CLOCK PER0_CLK: SSP2_CLK_EN (Bit 23)          */
#define MDR_RST_PER0_SSP2_CLK_EN_Msk (0x800000UL)         /*!< MDR_RST_CLOCK PER0_CLK: SSP2_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_CAN1_CLK_EN_Pos (24UL)               /*!< MDR_RST_CLOCK PER0_CLK: CAN1_CLK_EN (Bit 24)          */
#define MDR_RST_PER0_CAN1_CLK_EN_Msk (0x1000000UL)        /*!< MDR_RST_CLOCK PER0_CLK: CAN1_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_CAN2_CLK_EN_Pos (25UL)               /*!< MDR_RST_CLOCK PER0_CLK: CAN2_CLK_EN (Bit 25)          */
#define MDR_RST_PER0_CAN2_CLK_EN_Msk (0x2000000UL)        /*!< MDR_RST_CLOCK PER0_CLK: CAN2_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_UART1_CLK_EN_Pos (26UL)              /*!< MDR_RST_CLOCK PER0_CLK: UART1_CLK_EN (Bit 26)         */
#define MDR_RST_PER0_UART1_CLK_EN_Msk (0x4000000UL)       /*!< MDR_RST_CLOCK PER0_CLK: UART1_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_UART2_CLK_EN_Pos (27UL)              /*!< MDR_RST_CLOCK PER0_CLK: UART2_CLK_EN (Bit 27)         */
#define MDR_RST_PER0_UART2_CLK_EN_Msk (0x8000000UL)       /*!< MDR_RST_CLOCK PER0_CLK: UART2_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_UART3_CLK_EN_Pos (28UL)              /*!< MDR_RST_CLOCK PER0_CLK: UART3_CLK_EN (Bit 28)         */
#define MDR_RST_PER0_UART3_CLK_EN_Msk (0x10000000UL)      /*!< MDR_RST_CLOCK PER0_CLK: UART3_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_UART4_CLK_EN_Pos (29UL)              /*!< MDR_RST_CLOCK PER0_CLK: UART4_CLK_EN (Bit 29)         */
#define MDR_RST_PER0_UART4_CLK_EN_Msk (0x20000000UL)      /*!< MDR_RST_CLOCK PER0_CLK: UART4_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_MIL_CLK_EN_Pos (30UL)                /*!< MDR_RST_CLOCK PER0_CLK: MIL_CLK_EN (Bit 30)           */
#define MDR_RST_PER0_MIL_CLK_EN_Msk (0x40000000UL)        /*!< MDR_RST_CLOCK PER0_CLK: MIL_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER0_USB_CLK_EN_Pos (31UL)                /*!< MDR_RST_CLOCK PER0_CLK: USB_CLK_EN (Bit 31)           */
#define MDR_RST_PER0_USB_CLK_EN_Msk (0x80000000UL)        /*!< MDR_RST_CLOCK PER0_CLK: USB_CLK_EN (Bitfield-Mask: 0x01) */


typedef struct {
      __IOM MDR_OnOff TIM1_CLK_EN : 1;           /*!< [0..0] Timer1 Clock Enable                                                */
      __IOM MDR_OnOff TIM2_CLK_EN : 1;           /*!< [1..1] Timer1 Clock Enable                                                */
      __IOM MDR_OnOff TIM3_CLK_EN : 1;           /*!< [2..2] Timer3 Clock Enable                                                */
      __IOM MDR_OnOff TIM4_CLK_EN : 1;           /*!< [3..3] Timer4 Clock Enable                                                */
      __IOM MDR_OnOff CAP1_CLK_EN : 1;           /*!< [4..4] Capture1 Clock Enable                                              */
      __IOM MDR_OnOff CAP2_CLK_EN : 1;           /*!< [5..5] Capture2 Clock Enable                                              */
      __IOM MDR_OnOff CAP3_CLK_EN : 1;           /*!< [6..6] Capture3 Clock Enable                                              */
      __IOM MDR_OnOff CAP4_CLK_EN : 1;           /*!< [7..7] Capture4 Clock Enable                                              */
      __IOM MDR_OnOff QEP1_CLK_EN : 1;           /*!< [8..8] Encoder1 Clock Enable                                              */
      __IOM MDR_OnOff QEP2_CLK_EN : 1;           /*!< [9..9] Encoder2 Clock Enable                                              */
      __IOM MDR_OnOff PWM1_CLK_EN : 1;           /*!< [10..10] PWM1 Clock Enable                                                */
      __IOM MDR_OnOff PWM2_CLK_EN : 1;           /*!< [11..11] PWM2 Clock Enable                                                */
      __IOM MDR_OnOff PWM3_CLK_EN : 1;           /*!< [12..12] PWM3 Clock Enable                                                */
      __IOM MDR_OnOff PWM4_CLK_EN : 1;           /*!< [13..13] PWM4 Clock Enable                                                */
      __IOM MDR_OnOff PWM5_CLK_EN : 1;           /*!< [14..14] PWM5 Clock Enable                                                */
      __IOM MDR_OnOff PWM6_CLK_EN : 1;           /*!< [15..15] PWM6 Clock Enable                                                */
      __IOM MDR_OnOff PWM7_CLK_EN : 1;           /*!< [16..16] PWM7 Clock Enable                                                */
      __IOM MDR_OnOff PWM8_CLK_EN : 1;           /*!< [17..17] PWM8 Clock Enable                                                */
      __IOM MDR_OnOff PWM9_CLK_EN : 1;           /*!< [18..18] PWM9 Clock Enable                                                */
      __IOM MDR_OnOff ADC1_CLK_EN : 1;           /*!< [19..19] ADC1 Clock Enable                                                */
      __IOM MDR_OnOff ADC2_CLK_EN : 1;           /*!< [20..20] ADC2 Clock Enable                                                */
      __IOM MDR_OnOff ADC3_CLK_EN : 1;           /*!< [21..21] ADC3 Clock Enable                                                */
      __IOM MDR_OnOff DAC1_CLK_EN : 1;           /*!< [22..22] DAC1 Clock Enable                                                */
      __IOM MDR_OnOff DAC2_CLK_EN : 1;           /*!< [23..23] DAC2 Clock Enable                                                */
      __IOM MDR_OnOff DAC3_CLK_EN : 1;           /*!< [24..24] DAC3 Clock Enable                                                */
      __IOM MDR_OnOff DAC4_CLK_EN : 1;           /*!< [25..25] DAC4 Clock Enable                                                */
      __IOM MDR_OnOff CMP1_CLK_EN : 1;           /*!< [26..26] Comparator1 Clock Enable                                         */
      __IOM MDR_OnOff CMP2_CLK_EN : 1;           /*!< [27..27] Comparator2 Clock Enable                                         */
      __IOM MDR_OnOff CMP3_CLK_EN : 1;           /*!< [28..28] Comparator3 Clock Enable                                         */
      __IOM MDR_OnOff CMP4_CLK_EN : 1;           /*!< [29..29] Comparator4 Clock Enable                                         */
      __IOM MDR_OnOff I2C_CLK_EN : 1;            /*!< [30..30] I2C Clock Enable                                                 */
      __IOM MDR_OnOff CORDIC_CLK_EN : 1;         /*!< [31..31] CORDIC Clock Enable                                              */
} MDR_RST_PER1_Bits;

#define MDR_RST_PER1_TIM1_CLK_EN_Pos (0UL)                /*!< MDR_RST_CLOCK PER1_CLK: TIM1_CLK_EN (Bit 0)           */
#define MDR_RST_PER1_TIM1_CLK_EN_Msk (0x1UL)              /*!< MDR_RST_CLOCK PER1_CLK: TIM1_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_TIM2_CLK_EN_Pos (1UL)                /*!< MDR_RST_CLOCK PER1_CLK: TIM2_CLK_EN (Bit 1)           */
#define MDR_RST_PER1_TIM2_CLK_EN_Msk (0x2UL)              /*!< MDR_RST_CLOCK PER1_CLK: TIM2_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_TIM3_CLK_EN_Pos (2UL)                /*!< MDR_RST_CLOCK PER1_CLK: TIM3_CLK_EN (Bit 2)           */
#define MDR_RST_PER1_TIM3_CLK_EN_Msk (0x4UL)              /*!< MDR_RST_CLOCK PER1_CLK: TIM3_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_TIM4_CLK_EN_Pos (3UL)                /*!< MDR_RST_CLOCK PER1_CLK: TIM4_CLK_EN (Bit 3)           */
#define MDR_RST_PER1_TIM4_CLK_EN_Msk (0x8UL)              /*!< MDR_RST_CLOCK PER1_CLK: TIM4_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_CAP1_CLK_EN_Pos (4UL)                /*!< MDR_RST_CLOCK PER1_CLK: CAP1_CLK_EN (Bit 4)           */
#define MDR_RST_PER1_CAP1_CLK_EN_Msk (0x10UL)             /*!< MDR_RST_CLOCK PER1_CLK: CAP1_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_CAP2_CLK_EN_Pos (5UL)                /*!< MDR_RST_CLOCK PER1_CLK: CAP2_CLK_EN (Bit 5)           */
#define MDR_RST_PER1_CAP2_CLK_EN_Msk (0x20UL)             /*!< MDR_RST_CLOCK PER1_CLK: CAP2_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_CAP3_CLK_EN_Pos (6UL)                /*!< MDR_RST_CLOCK PER1_CLK: CAP3_CLK_EN (Bit 6)           */
#define MDR_RST_PER1_CAP3_CLK_EN_Msk (0x40UL)             /*!< MDR_RST_CLOCK PER1_CLK: CAP3_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_CAP4_CLK_EN_Pos (7UL)                /*!< MDR_RST_CLOCK PER1_CLK: CAP4_CLK_EN (Bit 7)           */
#define MDR_RST_PER1_CAP4_CLK_EN_Msk (0x80UL)             /*!< MDR_RST_CLOCK PER1_CLK: CAP4_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_QEP1_CLK_EN_Pos (8UL)                /*!< MDR_RST_CLOCK PER1_CLK: QEP1_CLK_EN (Bit 8)           */
#define MDR_RST_PER1_QEP1_CLK_EN_Msk (0x100UL)            /*!< MDR_RST_CLOCK PER1_CLK: QEP1_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_QEP2_CLK_EN_Pos (9UL)                /*!< MDR_RST_CLOCK PER1_CLK: QEP2_CLK_EN (Bit 9)           */
#define MDR_RST_PER1_QEP2_CLK_EN_Msk (0x200UL)            /*!< MDR_RST_CLOCK PER1_CLK: QEP2_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_PWM1_CLK_EN_Pos (10UL)               /*!< MDR_RST_CLOCK PER1_CLK: PWM1_CLK_EN (Bit 10)          */
#define MDR_RST_PER1_PWM1_CLK_EN_Msk (0x400UL)            /*!< MDR_RST_CLOCK PER1_CLK: PWM1_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_PWM2_CLK_EN_Pos (11UL)               /*!< MDR_RST_CLOCK PER1_CLK: PWM2_CLK_EN (Bit 11)          */
#define MDR_RST_PER1_PWM2_CLK_EN_Msk (0x800UL)            /*!< MDR_RST_CLOCK PER1_CLK: PWM2_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_PWM3_CLK_EN_Pos (12UL)               /*!< MDR_RST_CLOCK PER1_CLK: PWM3_CLK_EN (Bit 12)          */
#define MDR_RST_PER1_PWM3_CLK_EN_Msk (0x1000UL)           /*!< MDR_RST_CLOCK PER1_CLK: PWM3_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_PWM4_CLK_EN_Pos (13UL)               /*!< MDR_RST_CLOCK PER1_CLK: PWM4_CLK_EN (Bit 13)          */
#define MDR_RST_PER1_PWM4_CLK_EN_Msk (0x2000UL)           /*!< MDR_RST_CLOCK PER1_CLK: PWM4_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_PWM5_CLK_EN_Pos (14UL)               /*!< MDR_RST_CLOCK PER1_CLK: PWM5_CLK_EN (Bit 14)          */
#define MDR_RST_PER1_PWM5_CLK_EN_Msk (0x4000UL)           /*!< MDR_RST_CLOCK PER1_CLK: PWM5_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_PWM6_CLK_EN_Pos (15UL)               /*!< MDR_RST_CLOCK PER1_CLK: PWM6_CLK_EN (Bit 15)          */
#define MDR_RST_PER1_PWM6_CLK_EN_Msk (0x8000UL)           /*!< MDR_RST_CLOCK PER1_CLK: PWM6_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_PWM7_CLK_EN_Pos (16UL)               /*!< MDR_RST_CLOCK PER1_CLK: PWM7_CLK_EN (Bit 16)          */
#define MDR_RST_PER1_PWM7_CLK_EN_Msk (0x10000UL)          /*!< MDR_RST_CLOCK PER1_CLK: PWM7_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_PWM8_CLK_EN_Pos (17UL)               /*!< MDR_RST_CLOCK PER1_CLK: PWM8_CLK_EN (Bit 17)          */
#define MDR_RST_PER1_PWM8_CLK_EN_Msk (0x20000UL)          /*!< MDR_RST_CLOCK PER1_CLK: PWM8_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_PWM9_CLK_EN_Pos (18UL)               /*!< MDR_RST_CLOCK PER1_CLK: PWM9_CLK_EN (Bit 18)          */
#define MDR_RST_PER1_PWM9_CLK_EN_Msk (0x40000UL)          /*!< MDR_RST_CLOCK PER1_CLK: PWM9_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_ADC1_CLK_EN_Pos (19UL)               /*!< MDR_RST_CLOCK PER1_CLK: ADC1_CLK_EN (Bit 19)          */
#define MDR_RST_PER1_ADC1_CLK_EN_Msk (0x80000UL)          /*!< MDR_RST_CLOCK PER1_CLK: ADC1_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_ADC2_CLK_EN_Pos (20UL)               /*!< MDR_RST_CLOCK PER1_CLK: ADC2_CLK_EN (Bit 20)          */
#define MDR_RST_PER1_ADC2_CLK_EN_Msk (0x100000UL)         /*!< MDR_RST_CLOCK PER1_CLK: ADC2_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_ADC3_CLK_EN_Pos (21UL)               /*!< MDR_RST_CLOCK PER1_CLK: ADC3_CLK_EN (Bit 21)          */
#define MDR_RST_PER1_ADC3_CLK_EN_Msk (0x200000UL)         /*!< MDR_RST_CLOCK PER1_CLK: ADC3_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_DAC1_CLK_EN_Pos (22UL)               /*!< MDR_RST_CLOCK PER1_CLK: DAC1_CLK_EN (Bit 22)          */
#define MDR_RST_PER1_DAC1_CLK_EN_Msk (0x400000UL)         /*!< MDR_RST_CLOCK PER1_CLK: DAC1_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_DAC2_CLK_EN_Pos (23UL)               /*!< MDR_RST_CLOCK PER1_CLK: DAC2_CLK_EN (Bit 23)          */
#define MDR_RST_PER1_DAC2_CLK_EN_Msk (0x800000UL)         /*!< MDR_RST_CLOCK PER1_CLK: DAC2_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_DAC3_CLK_EN_Pos (24UL)               /*!< MDR_RST_CLOCK PER1_CLK: DAC3_CLK_EN (Bit 24)          */
#define MDR_RST_PER1_DAC3_CLK_EN_Msk (0x1000000UL)        /*!< MDR_RST_CLOCK PER1_CLK: DAC3_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_DAC4_CLK_EN_Pos (25UL)               /*!< MDR_RST_CLOCK PER1_CLK: DAC4_CLK_EN (Bit 25)          */
#define MDR_RST_PER1_DAC4_CLK_EN_Msk (0x2000000UL)        /*!< MDR_RST_CLOCK PER1_CLK: DAC4_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_CMP1_CLK_EN_Pos (26UL)               /*!< MDR_RST_CLOCK PER1_CLK: CMP1_CLK_EN (Bit 26)          */
#define MDR_RST_PER1_CMP1_CLK_EN_Msk (0x4000000UL)        /*!< MDR_RST_CLOCK PER1_CLK: CMP1_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_CMP2_CLK_EN_Pos (27UL)               /*!< MDR_RST_CLOCK PER1_CLK: CMP2_CLK_EN (Bit 27)          */
#define MDR_RST_PER1_CMP2_CLK_EN_Msk (0x8000000UL)        /*!< MDR_RST_CLOCK PER1_CLK: CMP2_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_CMP3_CLK_EN_Pos (28UL)               /*!< MDR_RST_CLOCK PER1_CLK: CMP3_CLK_EN (Bit 28)          */
#define MDR_RST_PER1_CMP3_CLK_EN_Msk (0x10000000UL)       /*!< MDR_RST_CLOCK PER1_CLK: CMP3_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_CMP4_CLK_EN_Pos (29UL)               /*!< MDR_RST_CLOCK PER1_CLK: CMP4_CLK_EN (Bit 29)          */
#define MDR_RST_PER1_CMP4_CLK_EN_Msk (0x20000000UL)       /*!< MDR_RST_CLOCK PER1_CLK: CMP4_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_I2C_CLK_EN_Pos (30UL)                /*!< MDR_RST_CLOCK PER1_CLK: I2C_CLK_EN (Bit 30)           */
#define MDR_RST_PER1_I2C_CLK_EN_Msk (0x40000000UL)        /*!< MDR_RST_CLOCK PER1_CLK: I2C_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER1_CORDIC_CLK_EN_Pos (31UL)             /*!< MDR_RST_CLOCK PER1_CLK: CORDIC_CLK_EN (Bit 31)        */
#define MDR_RST_PER1_CORDIC_CLK_EN_Msk (0x80000000UL)     /*!< MDR_RST_CLOCK PER1_CLK: CORDIC_CLK_EN (Bitfield-Mask: 0x01) */


//--------------- LSI/LSE/HSE0/HSE1/PLLx status Bits  ------------------
typedef struct {
      __IOM uint8_t   MAX_CLK_SHIFT_REG0 : 8;    /*!< [7..0] Max factor detected for SLOW                                              */
      __IOM uint8_t   MAX_CLK_SHIFT_REG1 : 8;    /*!< [15..8] Max factor detected for FAST                                             */
      __IOM MDR_OnOff EVENT0            : 1;            /*!< [16..16] Event SLOWEST                                                   */
      __IOM MDR_OnOff EVENT1            : 1;            /*!< [17..17] Event SLOW                                                      */
      __IOM MDR_OnOff EVENT2            : 1;            /*!< [18..18] Event FAST                                                      */
      __IOM MDR_OnOff EVENT3            : 1;            /*!< [19..19] Event FASTEST                                                   */
      __IOM MDR_OnOff READY             : 1;            /*!< [20..20] Clock Ready                                                     */
      __IM  uint32_t                    : 11;
} MDR_RST_CLK_STAT_Bits;

#define MDR_RST_CLK_STAT_MAX_CLK_SHIFT_REG0_Pos (0UL)         /*!< MDR_RST_CLOCK CPU_STAT: MAX_CLK_SHIFT_REG0 (Bit 0)    */
#define MDR_RST_CLK_STAT_MAX_CLK_SHIFT_REG0_Msk (0xffUL)      /*!< MDR_RST_CLOCK CPU_STAT: MAX_CLK_SHIFT_REG0 (Bitfield-Mask: 0xff) */
#define MDR_RST_CLK_STAT_MAX_CLK_SHIFT_REG1_Pos (8UL)         /*!< MDR_RST_CLOCK CPU_STAT: MAX_CLK_SHIFT_REG1 (Bit 8)    */
#define MDR_RST_CLK_STAT_MAX_CLK_SHIFT_REG1_Msk (0xff00UL)    /*!< MDR_RST_CLOCK CPU_STAT: MAX_CLK_SHIFT_REG1 (Bitfield-Mask: 0xff) */
#define MDR_RST_CLK_STAT_EVENT0_Pos (16UL)                    /*!< MDR_RST_CLOCK CPU_STAT: EVENT0 (Bit 16)               */
#define MDR_RST_CLK_STAT_EVENT0_Msk (0x10000UL)               /*!< MDR_RST_CLOCK CPU_STAT: EVENT0 (Bitfield-Mask: 0x01)  */
#define MDR_RST_CLK_STAT_EVENT1_Pos (17UL)                    /*!< MDR_RST_CLOCK CPU_STAT: EVENT1 (Bit 17)               */
#define MDR_RST_CLK_STAT_EVENT1_Msk (0x20000UL)               /*!< MDR_RST_CLOCK CPU_STAT: EVENT1 (Bitfield-Mask: 0x01)  */
#define MDR_RST_CLK_STAT_EVENT2_Pos (18UL)                    /*!< MDR_RST_CLOCK CPU_STAT: EVENT2 (Bit 18)               */
#define MDR_RST_CLK_STAT_EVENT2_Msk (0x40000UL)               /*!< MDR_RST_CLOCK CPU_STAT: EVENT2 (Bitfield-Mask: 0x01)  */
#define MDR_RST_CLK_STAT_EVENT3_Pos (19UL)                    /*!< MDR_RST_CLOCK CPU_STAT: EVENT3 (Bit 19)               */
#define MDR_RST_CLK_STAT_EVENT3_Msk (0x80000UL)               /*!< MDR_RST_CLOCK CPU_STAT: EVENT3 (Bitfield-Mask: 0x01)  */
#define MDR_RST_CLK_STAT_READY_Pos  (20UL)                    /*!< MDR_RST_CLOCK CPU_STAT: EVENT3 (Bit 19)               */
#define MDR_RST_CLK_STAT_READY_Msk  (0x100000UL)              /*!< MDR_RST_CLOCK CPU_STAT: EVENT3 (Bitfield-Mask: 0x01)  */


//--------------- HSI Bits  ------------------  
typedef struct {
      __IM  uint32_t                : 20;
      __IOM MDR_OnOff   READY       : 1;            /*!< [20..20] Clock Ready                                                         */
      __IM  uint32_t                : 11;
} MDR_RST_HSI_STAT_Bits;

#define MDR_RST_HSI_STAT_READY_Pos  (20UL)                    /*!< MDR_RST_CLOCK HSE_STAT: READY (Bit 20)                */
#define MDR_RST_HSI_STAT_READY_Msk  (0x100000UL)              /*!< MDR_RST_CLOCK HSE_STAT: READY (Bitfield-Mask: 0x01)   */

//--------------- PLL Bits  ------------------  

typedef enum {               /*!< MDR_RST_CLOCK_PLL0_CLK_PLL_Q                                              */
  MDR_PLL_Q_div1    = 0,     /*!< div1 : Divider                                                            */
  MDR_PLL_Q_div2    = 1,     /*!< div2 : Divider                                                            */
  MDR_PLL_Q_div3    = 2,     /*!< div3 : Divider                                                            */
  MDR_PLL_Q_div4    = 3,     /*!< div4 : Divider                                                            */
  MDR_PLL_Q_div5    = 4,     /*!< div5 : Divider                                                            */
  MDR_PLL_Q_div6    = 5,     /*!< div6 : Divider                                                            */
  MDR_PLL_Q_div7    = 6,     /*!< div7 : Divider                                                            */
  MDR_PLL_Q_div8    = 7,     /*!< div8 : Divider                                                            */
  MDR_PLL_Q_div9    = 8,     /*!< div9 : Divider                                                            */
  MDR_PLL_Q_div10   = 9,     /*!< div10 : Divider                                                           */
  MDR_PLL_Q_div11   = 10,    /*!< div11 : Divider                                                           */
  MDR_PLL_Q_div12   = 11,    /*!< div12 : Divider                                                           */
  MDR_PLL_Q_div13   = 12,    /*!< div13 : Divider                                                           */
  MDR_PLL_Q_div14   = 13,    /*!< div14 : Divider                                                           */
  MDR_PLL_Q_div15   = 14,    /*!< div15 : Divider                                                           */
  MDR_PLL_Q_div16   = 15,    /*!< div16 : Divider                                                           */
  MDR_PLL_Q_div17   = 16,    /*!< div17 : Divider                                                           */
  MDR_PLL_Q_div18   = 17,    /*!< div18 : Divider                                                           */
  MDR_PLL_Q_div19   = 18,    /*!< div19 : Divider                                                           */
  MDR_PLL_Q_div20   = 19,    /*!< div20 : Divider                                                           */
  MDR_PLL_Q_div21   = 20,    /*!< div21 : Divider                                                           */
  MDR_PLL_Q_div22   = 21,    /*!< div22 : Divider                                                           */
  MDR_PLL_Q_div23   = 22,    /*!< div23 : Divider                                                           */
  MDR_PLL_Q_div24   = 23,    /*!< div24 : Divider                                                           */
  MDR_PLL_Q_div25   = 24,    /*!< div25 : Divider                                                           */
  MDR_PLL_Q_div26   = 25,    /*!< div26 : Divider                                                           */
  MDR_PLL_Q_div27   = 26,    /*!< div27 : Divider                                                           */  
  MDR_PLL_Q_div28   = 27,    /*!< div28 : Divider                                                           */
  MDR_PLL_Q_div29   = 28,    /*!< div29 : Divider                                                           */
  MDR_PLL_Q_div30   = 29,    /*!< div30 : Divider                                                           */
  MDR_PLL_Q_div31   = 31,    /*!< div31 : Divider                                                           */  
} MDR_PLL_DivQ;

typedef enum {                /*!< MDR_RST_CLOCK_PLL0_CLK_SELECT                                             */
  MDR_PLL_IN_HSI       = 0,   /*!< HSI : HSI signal                                                          */
  MDR_PLL_IN_HSIdiv2   = 1,   /*!< HSI_div2 : HSI/2 signal                                                   */
  MDR_PLL_IN_HSE0      = 2,   /*!< HSE0 : HSE0 signal                                                        */
  MDR_PLL_IN_HSE0div2  = 3,   /*!< HSE0_div2 : HSE0/2 signal                                                 */
  MDR_PLL_IN_HSE1      = 4,   /*!< HSE1 : HSE1 signal                                                        */
  MDR_PLL_IN_HSE1div2  = 5,   /*!< HSE1_div2 : HSE1/2 signal                                                 */
} MDR_PLL_IN_SEL;

typedef enum {                                  /*!< MDR_RST_CLOCK_PLL0_CLK_DV                                                 */
  MDR_RST_PLL_DV_div1       = 0,     /*!< div1 : Divider                                                            */
  MDR_RST_PLL_DV_div2       = 1,     /*!< div2 : Divider                                                            */
  MDR_RST_PLL_DV_div4       = 2,     /*!< div4 : Divider                                                            */
  MDR_RST_PLL_DV_div8       = 3,     /*!< div8 : Divider                                                            */
} MDR_RST_PLL0_DV;

typedef struct {
      __IOM MDR_PLL_DivQ    PLL_Q         : 5;         /*!< [4..0] PLL Freq divider                                                   */
      __IOM uint32_t        PLL_N         : 9;         /*!< [13..5] PLL Freq multiplier                                               */
      __IOM MDR_RST_PLL0_DV DV            : 2;         /*!< [15..14] PLL Output Divider                                               */
      __IOM MDR_OnOff       PLL_ReadyMode : 1;         /*!< [16..16] Enable output after ready only                                   */
      __IOM MDR_OnOff       PLL_ON        : 1;         /*!< [17..17] PLL Enable                                                       */
      __IOM MDR_PLL_IN_SEL  SELECT        : 3;         /*!< [20..18] Select PLL Input                                                 */
      __IOM MDR_OnOff       EN_CHK_EVENT0 : 1;         /*!< [21..21] Go to HSI on lose active clock                                   */
      __IOM MDR_OnOff       EN_CHK_EVENT1 : 1;         /*!< [22..22] Go to HSI if active clock is low                                 */
      __IOM MDR_OnOff       EN_CHK_EVENT2 : 1;         /*!< [23..23] Go to HSI if active clock is High                                */
      __IOM MDR_OnOff       EN_CHK_EVENT3 : 1;         /*!< [24..24] Go to HSI if active clock is Highest                             */
      __IOM MDR_OnOff       EN_CHK        : 1;         /*!< [25..25] Clock Checker enable                                             */
      __IOM MDR_OnOff       CLR_CHK_SHIFT_REG0 : 1;    /*!< [26..26] Clear Min Freq level                                             */
      __IOM MDR_OnOff       CLR_CHK_SHIFT_REG1 : 1;    /*!< [27..27] Clear Max Freq level                                             */
      __IOM MDR_OnOff       CLR_CHK_EVENT0 : 1;        /*!< [28..28] Clear no freq event                                              */
      __IOM MDR_OnOff       CLR_CHK_EVENT1 : 1;        /*!< [29..29] Clear low freq event                                             */
      __IOM MDR_OnOff       CLR_CHK_EVENT2 : 1;        /*!< [30..30] Clear high freq event                                            */
      __IOM MDR_OnOff       CLR_CHK_EVENT3 : 1;        /*!< [31..31] Clear highest freq event                                         */
} MDR_RST_PLL_CLK_Bits;

#define MDR_RST_PLL_PLL_Q_Pos  (0UL)                     /*!< MDR_RST_CLOCK PLL0_CLK: PLL_Q (Bit 0)                 */
#define MDR_RST_PLL_PLL_Q_Msk  (0x1fUL)                  /*!< MDR_RST_CLOCK PLL0_CLK: PLL_Q (Bitfield-Mask: 0x1f)   */
#define MDR_RST_PLL_PLL_N_Pos  (5UL)                     /*!< MDR_RST_CLOCK PLL0_CLK: PLL_N (Bit 5)                 */
#define MDR_RST_PLL_PLL_N_Msk  (0x3fe0UL)                /*!< MDR_RST_CLOCK PLL0_CLK: PLL_N (Bitfield-Mask: 0x1ff)  */
#define MDR_RST_PLL_DV_Pos     (14UL)                    /*!< MDR_RST_CLOCK PLL0_CLK: DV (Bit 14)                   */
#define MDR_RST_PLL_DV_Msk     (0xc000UL)                /*!< MDR_RST_CLOCK PLL0_CLK: DV (Bitfield-Mask: 0x03)      */
#define MDR_RST_PLL_PLL_ReadyMode_Pos (16UL)             /*!< MDR_RST_CLOCK PLL0_CLK: PLL_ReadyMode (Bit 16)        */
#define MDR_RST_PLL_PLL_ReadyMode_Msk (0x10000UL)        /*!< MDR_RST_CLOCK PLL0_CLK: PLL_ReadyMode (Bitfield-Mask: 0x01) */
#define MDR_RST_PLL_PLL_ON_Pos (17UL)                    /*!< MDR_RST_CLOCK PLL0_CLK: PLL_ON (Bit 17)               */
#define MDR_RST_PLL_PLL_ON_Msk (0x20000UL)               /*!< MDR_RST_CLOCK PLL0_CLK: PLL_ON (Bitfield-Mask: 0x01)  */
#define MDR_RST_PLL_SELECT_Pos (18UL)                    /*!< MDR_RST_CLOCK PLL0_CLK: SELECT (Bit 18)               */
#define MDR_RST_PLL_SELECT_Msk (0x1c0000UL)              /*!< MDR_RST_CLOCK PLL0_CLK: SELECT (Bitfield-Mask: 0x07)  */
#define MDR_RST_PLL_EN_CHK_EVENT0_Pos (21UL)             /*!< MDR_RST_CLOCK PLL0_CLK: EN_CHK_EVENT0 (Bit 21)        */
#define MDR_RST_PLL_EN_CHK_EVENT0_Msk (0x200000UL)       /*!< MDR_RST_CLOCK PLL0_CLK: EN_CHK_EVENT0 (Bitfield-Mask: 0x01) */
#define MDR_RST_PLL_EN_CHK_EVENT1_Pos (22UL)             /*!< MDR_RST_CLOCK PLL0_CLK: EN_CHK_EVENT1 (Bit 22)        */
#define MDR_RST_PLL_EN_CHK_EVENT1_Msk (0x400000UL)       /*!< MDR_RST_CLOCK PLL0_CLK: EN_CHK_EVENT1 (Bitfield-Mask: 0x01) */
#define MDR_RST_PLL_EN_CHK_EVENT2_Pos (23UL)             /*!< MDR_RST_CLOCK PLL0_CLK: EN_CHK_EVENT2 (Bit 23)        */
#define MDR_RST_PLL_EN_CHK_EVENT2_Msk (0x800000UL)       /*!< MDR_RST_CLOCK PLL0_CLK: EN_CHK_EVENT2 (Bitfield-Mask: 0x01) */
#define MDR_RST_PLL_EN_CHK_EVENT3_Pos (24UL)             /*!< MDR_RST_CLOCK PLL0_CLK: EN_CHK_EVENT3 (Bit 24)        */
#define MDR_RST_PLL_EN_CHK_EVENT3_Msk (0x1000000UL)      /*!< MDR_RST_CLOCK PLL0_CLK: EN_CHK_EVENT3 (Bitfield-Mask: 0x01) */
#define MDR_RST_PLL_EN_CHK_Pos (25UL)                    /*!< MDR_RST_CLOCK PLL0_CLK: EN_CHK (Bit 25)               */
#define MDR_RST_PLL_EN_CHK_Msk (0x2000000UL)             /*!< MDR_RST_CLOCK PLL0_CLK: EN_CHK (Bitfield-Mask: 0x01)  */
#define MDR_RST_PLL_CLR_CHK_SHIFT_REG0_Pos (26UL)        /*!< MDR_RST_CLOCK PLL0_CLK: CLR_CHK_SHIFT_REG0 (Bit 26)   */
#define MDR_RST_PLL_CLR_CHK_SHIFT_REG0_Msk (0x4000000UL) /*!< MDR_RST_CLOCK PLL0_CLK: CLR_CHK_SHIFT_REG0 (Bitfield-Mask: 0x01) */
#define MDR_RST_PLL_CLR_CHK_SHIFT_REG1_Pos (27UL)        /*!< MDR_RST_CLOCK PLL0_CLK: CLR_CHK_SHIFT_REG1 (Bit 27)   */
#define MDR_RST_PLL_CLR_CHK_SHIFT_REG1_Msk (0x8000000UL) /*!< MDR_RST_CLOCK PLL0_CLK: CLR_CHK_SHIFT_REG1 (Bitfield-Mask: 0x01) */
#define MDR_RST_PLL_CLR_CHK_EVENT0_Pos (28UL)            /*!< MDR_RST_CLOCK PLL0_CLK: CLR_CHK_EVENT0 (Bit 28)       */
#define MDR_RST_PLL_CLR_CHK_EVENT0_Msk (0x10000000UL)    /*!< MDR_RST_CLOCK PLL0_CLK: CLR_CHK_EVENT0 (Bitfield-Mask: 0x01) */
#define MDR_RST_PLL_CLR_CHK_EVENT1_Pos (29UL)            /*!< MDR_RST_CLOCK PLL0_CLK: CLR_CHK_EVENT1 (Bit 29)       */
#define MDR_RST_PLL_CLR_CHK_EVENT1_Msk (0x20000000UL)    /*!< MDR_RST_CLOCK PLL0_CLK: CLR_CHK_EVENT1 (Bitfield-Mask: 0x01) */
#define MDR_RST_PLL_CLR_CHK_EVENT2_Pos (30UL)            /*!< MDR_RST_CLOCK PLL0_CLK: CLR_CHK_EVENT2 (Bit 30)       */
#define MDR_RST_PLL_CLR_CHK_EVENT2_Msk (0x40000000UL)    /*!< MDR_RST_CLOCK PLL0_CLK: CLR_CHK_EVENT2 (Bitfield-Mask: 0x01) */
#define MDR_RST_PLL_CLR_CHK_EVENT3_Pos (31UL)            /*!< MDR_RST_CLOCK PLL0_CLK: CLR_CHK_EVENT3 (Bit 31)       */
#define MDR_RST_PLL_CLR_CHK_EVENT3_Msk (0x80000000UL)    /*!< MDR_RST_CLOCK PLL0_CLK: CLR_CHK_EVENT3 (Bitfield-Mask: 0x01) */

#define MDR_RST_PLL_LIKE_ESILA


/* =========================================================================================================================== */
/* ================                                       MDR_RST_CLOCK                                       ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40000000) MDR_RST_CLOCK Structure                                    */ 
  __IOM uint32_t KEY;                           /*!< (@ 0x00000000) Clock Unlock Register                                      */  
  union {
    __IOM uint32_t        MAX_CLK;              /*!< (@ 0x00000004) MAX_CLK Select Register                                    */
    MDR_RST_MAX_CLK_Bits  MAX_CLK_b;
  } ;
  //  CPU Control and PER Clock enable
  union {
    __IOM uint32_t        CPU_CLK;              /*!< (@ 0x00000008) CPU_CLK Register                                           */
    MDR_RST_CLK_CPU_Bits  CPU_CLK_b;
  } ;  
  union {
    __IOM uint32_t        PER0_CLK;             /*!< (@ 0x0000000C) Periph0 Clock Enable Register                              */
    MDR_RST_PER0_Bits     PER0_CLK_b;
  } ;  
  union {
    __IOM uint32_t        PER1_CLK;             /*!< (@ 0x00000010) Periph1 Clock Enable Register                              */
    MDR_RST_PER1_Bits     PER1_CLK_b;
  } ;  
  MDR_RST_CLK_CHECKER     CPU_CHKR;
  union {
    __IOM uint32_t        CPU_STAT;             /*!< (@ 0x00000020) Clock Status Register                                      */
    MDR_RST_CPU_STAT_Bits CPU_STAT_b;
  } ;
  //  LSI Control
  union {
    __IOM uint32_t        LSI_CLK;              /*!< (@ 0x00000024) Clock Contorl Register                                     */
    MDR_RST_CLK_LSIE_Bits LSI_CLK_b;
  } ;
  MDR_RST_CLK_CHECKER     LSI_CHKR; 
  union {
    __IOM uint32_t        LSI_STAT;             /*!< (@ 0x00000034) Clock Status Register                                      */
    MDR_RST_CLK_STAT_Bits LSI_STAT_b;
  } ;
  __IM  uint32_t          RESERVED;                           //  HSI Control
  //  LSE Control
  union {
    __IOM uint32_t        LSE_CLK;                     /*!< (@ 0x0000003C) Clock Contorl Register                                     */
    MDR_RST_CLK_LSIE_Bits LSE_CLK_b;
  } ;
  MDR_RST_CLK_CHECKER     LSE_CHKR; 
  union {
    __IOM uint32_t        LSE_STAT;                    /*!< (@ 0x0000004C) Clock Status Register                                      */
    MDR_RST_CLK_STAT_Bits LSE_STAT_b;
  } ;
  //  HSE0 Control
  union {
    __IOM uint32_t        HSE0_CLK;                    /*!< (@ 0x00000050) Clock Contorl Register                                     */    
    MDR_RST_HSE_CLK_Bits  HSE0_CLK_b;
  } ;
  MDR_RST_CLK_CHECKER     HSE0_CHKR; 
  union {
    __IOM uint32_t        HSE0_STAT;                   /*!< (@ 0x00000060) Clock Status Register                                      */
    MDR_RST_CLK_STAT_Bits HSE0_STAT_b;
  } ;
  //  HSE1 Control
  union {
    __IOM uint32_t        HSE1_CLK;                    /*!< (@ 0x00000064) Clock Contorl Register                                     */
    MDR_RST_HSE_CLK_Bits  HSE1_CLK_b;
  } ;
  MDR_RST_CLK_CHECKER     HSE1_CHKR;
  union {
    __IOM uint32_t        HSE1_STAT;                   /*!< (@ 0x00000060) Clock Status Register                                      */
    MDR_RST_CLK_STAT_Bits HSE1_STAT_b;
  } ;
  //  PLL0  
  union {
    __IOM uint32_t        PLL0_CLK;                    /*!< (@ 0x00000078) PLL0 Control                                               */
    MDR_RST_PLL_CLK_Bits  PLL0_CLK_b;
  } ;
  MDR_RST_CLK_CHECKER     PLL0_CHKR;
  union {
    __IOM uint32_t        PLL0_STAT;                   /*!< (@ 0x00000088) Clock Status Register                                      */
    MDR_RST_CLK_STAT_Bits PLL0_STAT_b;
  } ;
  //  PLL1
  union {
    __IOM uint32_t        PLL1_CLK;                    /*!< (@ 0x0000008C) PLL0 Control                                               */
    MDR_RST_PLL_CLK_Bits  PLL1_CLK_b;
  } ;
  MDR_RST_CLK_CHECKER     PLL1_CHKR;  
  union {
    __IOM uint32_t        PLL1_STAT;                   /*!< (@ 0x0000009C) Clock Status Register                                      */
    MDR_RST_CLK_STAT_Bits PLL1_STAT_b;
  } ;
  //  PLL2
  union {
    __IOM uint32_t        PLL2_CLK;                    /*!< (@ 0x0000008C) PLL0 Control                                               */
    MDR_RST_PLL_CLK_Bits  PLL2_CLK_b;
  } ;
  MDR_RST_CLK_CHECKER     PLL2_CHKR;  
  union {
    __IOM uint32_t        PLL2_STAT;                   /*!< (@ 0x0000009C) Clock Status Register                                      */
    MDR_RST_CLK_STAT_Bits PLL2_STAT_b;
  } ;
  //  PLL3
  union {
    __IOM uint32_t        PLL3_CLK;                    /*!< (@ 0x0000008C) PLL0 Control                                               */
    MDR_RST_PLL_CLK_Bits  PLL3_CLK_b;
  } ;
  MDR_RST_CLK_CHECKER     PLL3_CHKR;  
  union {
    __IOM uint32_t        PLL3_STAT;                   /*!< (@ 0x0000009C) Clock Status Register                                      */
    MDR_RST_CLK_STAT_Bits PLL3_STAT_b;
  } ;
  //  PERIPHERIAL Clock Control
  union {
    __IOM uint32_t          ETH_CLK;                     /*!< (@ 0x000000C8) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  ETH_CLK_b; 
  } ;
  
  union {
    __IOM uint32_t          USB_CLK;                     /*!< (@ 0x000000CC) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  USB_CLK_b;
  } ;
  __IM  uint32_t  RESERVED1;  
  union {
    __IOM uint32_t          RTC_CLK;                     /*!< (@ 0x000000D4) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  RTC_CLK_b;
  } ;  
  union {
    __IOM uint32_t          SSP1_CLK;                    /*!< (@ 0x000000D8) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  SSP1_CLK_b;
  } ; 
  union {
    __IOM uint32_t          SSP2_CLK;                    /*!< (@ 0x000000DC) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  SSP2_CLK_b;
  } ;
  union {
    __IOM uint32_t          CAN1_CLK;                    /*!< (@ 0x000000E0) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   CAN1_CLK_b;
  } ;
  union {
    __IOM uint32_t          CAN2_CLK;                    /*!< (@ 0x000000E4) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   CAN2_CLK_b;
  } ;
  union {
    __IOM uint32_t          UART1_CLK;                   /*!< (@ 0x000000E8) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  UART1_CLK_b;
  } ;  
  union {
    __IOM uint32_t          UART2_CLK;                   /*!< (@ 0x000000EC) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  UART2_CLK_b;
  } ;  
  union {
    __IOM uint32_t          UART3_CLK;                   /*!< (@ 0x000000F0) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  UART3_CLK_b;
  } ;
  union {
    __IOM uint32_t          UART4_CLK;                   /*!< (@ 0x000000F4) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  UART4_CLK_b; 
  } ;
  union {
    __IOM uint32_t          MIL_CLK;                     /*!< (@ 0x000000F8) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   MIL_CLK_b; 
  } ;  
  union {
    __IOM uint32_t          TIM1_CLK;                    /*!< (@ 0x000000FC) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   TIM1_CLK_b;
  } ;
  union {
    __IOM uint32_t          TIM2_CLK;                    /*!< (@ 0x00000100) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   TIM2_CLK_b;
  } ;  
  union {
    __IOM uint32_t          TIM3_CLK;                    /*!< (@ 0x00000104) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   TIM3_CLK_b;
  } ;
  __IM  uint32_t  RESERVED2;  
  union {
    __IOM uint32_t          TIM4_CLK;                    /*!< (@ 0x0000010C) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   TIM4_CLK_b;
  } ;  
  union {
    __IOM uint32_t          CAP1_CLK;                    /*!< (@ 0x00000110) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   CAP1_CLK_b;
  } ;  
  union {
    __IOM uint32_t          CAP2_CLK;                    /*!< (@ 0x00000114) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   CAP2_CLK_b;
  } ;  
  union {
    __IOM uint32_t          CAP3_CLK;                    /*!< (@ 0x00000118) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   CAP3_CLK_b;
  } ;  
  union {
    __IOM uint32_t          CAP4_CLK;                    /*!< (@ 0x0000011C) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   CAP4_CLK_b;
  } ;  
  union {
    __IOM uint32_t          QEP1_CLK;                    /*!< (@ 0x00000120) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   QEP1_CLK_b;
  } ;
  union {
    __IOM uint32_t          QEP2_CLK;                    /*!< (@ 0x00000124) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   QEP2_CLK_b;    
  } ;  
  union {
    __IOM uint32_t          PWM1_CLK;                    /*!< (@ 0x00000128) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   PWM1_CLK_b;
  } ;  
  union {
    __IOM uint32_t          PWM2_CLK;                    /*!< (@ 0x0000012C) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   PWM2_CLK_b;
  } ;  
  union {
    __IOM uint32_t          PWM3_CLK;                    /*!< (@ 0x00000130) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   PWM3_CLK_b;
  } ;  
  union {
    __IOM uint32_t          PWM4_CLK;                    /*!< (@ 0x00000134) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   PWM4_CLK_b;
  } ;  
  union {
    __IOM uint32_t          PWM5_CLK;                    /*!< (@ 0x00000138) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   PWM5_CLK_b;
  } ;  
  union {
    __IOM uint32_t          PWM6_CLK;                    /*!< (@ 0x0000013C) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   PWM6_CLK_b;
  } ;  
  union {
    __IOM uint32_t          PWM7_CLK;                    /*!< (@ 0x00000140) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   PWM7_CLK_b;
  } ;
  
  union {
    __IOM uint32_t          PWM8_CLK;                    /*!< (@ 0x00000144) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   PWM8_CLK_b;    
  } ;  
  union {
    __IOM uint32_t          PWM9_CLK;                    /*!< (@ 0x00000148) Sync Clock Control                                         */
    MDR_RST_SYNC_CLK_Bits   PWM9_CLK_b;
  } ;
  
  union {
    __IOM uint32_t          ADC1_CLK;                    /*!< (@ 0x0000014C) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  ADC1_CLK_b;
  } ;
  __IM  uint32_t            RESERVED3[32];  
  union {
    __IOM uint32_t          ADC2_CLK;                    /*!< (@ 0x000001D0) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  ADC2_CLK_b;    
  } ;  
  union {
    __IOM uint32_t          ADC3_CLK;                    /*!< (@ 0x000001D4) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  ADC3_CLK_b;
  } ;  
  union {
    __IOM uint32_t          CORDIC_CLK;                  /*!< (@ 0x000001D8) Async Clock Control                                        */
    MDR_RST_ASYNC_CLK_Bits  CORDIC_CLK_b;
  } ;
} MDR_RST_CLOCK_Type;                           /*!< Size = 464 (0x1d0)                                                        */


typedef struct {
  union {
    __IOM uint32_t        HSE_CLK;                    /*!< (@ 0x00000050) Clock Contorl Register                                     */    
    MDR_RST_HSE_CLK_Bits  HSE_CLK_b;
  } ;
  MDR_RST_CLK_CHECKER     HSE_CHKR; 
  union {
    __IOM uint32_t        HSE_STAT;                   /*!< (@ 0x00000060) Clock Status Register                                      */
    MDR_RST_CLK_STAT_Bits HSE_STAT_b;
  } ;  
} MDR_RST_HSE_Type;


typedef struct {
  union {
    __IOM uint32_t        PLL_CLK;                    /*!< (@ 0x00000078) PLL0 Control                                               */
    MDR_RST_PLL_CLK_Bits  PLL_CLK_b;
  } ;
  MDR_RST_CLK_CHECKER     PLL_CHKR;
  union {
    __IOM uint32_t        PLL_STAT;                   /*!< (@ 0x00000088) Clock Status Register                                      */
    MDR_RST_CLK_STAT_Bits PLL_STAT_b;
  } ; 
} MDR_RST_PLL_Type;


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

#endif  //_MDR_RST_ESila_DEFS_H
