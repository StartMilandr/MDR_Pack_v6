#ifndef _MDR_RST_VK234_DEFS_H
#define _MDR_RST_VK234_DEFS_H

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

#include "MDR_RST_VE4x_defs.h"


/* =======================================================  PER1_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_CLK_SEL_LSIE2  PER1_C1_SEL : 2;           /*!< [1..0] PER1_C1 mux freq select                                   */
      __IOM MDR_CLK_SEL_PER    PER1_C2_SEL : 2;           /*!< [3..2] PER1_C2 mux freq select                                   */
      __IOM MDR_OnOff          DEBUG_CLK_EN: 1;           /*!< [4..4] Debug clock enable                                        */
      __IOM MDR_OnOff          DMA_CLK_EN  : 1;           /*!< [5..5] DMA clock enable                                          */
      __IM  uint32_t                       : 26;
} MDR_RST_PER1_Bits;

#define MDR_RST_PER1__PER1_C1_SEL_Pos  (0UL)              /*!< MDR_RST_CLOCK PER1_CLOCK: PER1_C1_SEL (Bit 0)                    */
#define MDR_RST_PER1__PER1_C1_SEL_Msk  (0x3UL)            /*!< MDR_RST_CLOCK PER1_CLOCK: PER1_C1_SEL (Bitfield-Mask: 0x03)      */
#define MDR_RST_PER1__PER1_C2_SEL_Pos  (2UL)              /*!< MDR_RST_CLOCK PER1_CLOCK: PER1_C2_SEL (Bit 2)                    */
#define MDR_RST_PER1__PER1_C2_SEL_Msk  (0xcUL)            /*!< MDR_RST_CLOCK PER1_CLOCK: PER1_C2_SEL (Bitfield-Mask: 0x03)      */
#define MDR_RST_PER1__DEBUG_EN_Pos     (4UL)              /*!< MDR_RST_CLOCK PER1_CLOCK: DEBUG_EN (Bit 4)                       */
#define MDR_RST_PER1__DEBUG_EN_Msk     (0x10UL)           /*!< MDR_RST_CLOCK PER1_CLOCK: DEBUG_EN (Bitfield-Mask: 0x01)         */
#define MDR_RST_PER1__DMA_EN_Pos       (5UL)              /*!< MDR_RST_CLOCK PER1_CLOCK: DMA_EN (Bit 5)                         */
#define MDR_RST_PER1__DMA_EN_Msk       (0x20UL)           /*!< MDR_RST_CLOCK PER1_CLOCK: DMA_EN (Bitfield-Mask: 0x01)           */


/* =======================================================  PER2_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_OnOff  SPI1_CLK_EN   : 1;         /*!< [0..0] SPI1 Clock Enable                                                  */
      __IOM MDR_OnOff  UART1_CLK_EN  : 1;         /*!< [1..1] UART1 Clock Enable                                                 */
      __IOM MDR_OnOff  UART2_CLK_EN  : 1;         /*!< [2..2] UART2 Clock Enable                                                 */
      __IOM MDR_OnOff  EEPROM_CLK_EN : 1;         /*!< [3..3] EEPROM Clock Enable                                                */
      __IOM MDR_OnOff  RST_CLK_EN    : 1;         /*!< [4..4] RST Clock Enable                                                   */
      __IM  uint32_t                 : 3;         /*!< [7..6]                                                                    */
      __IOM MDR_OnOff  ADC_CLK_EN    : 1;         /*!< [8..8] ADC Clock Enable                                                   */
      __IOM MDR_OnOff  WWDT_CLK_EN   : 1;         /*!< [9..9] WWDT Clock Enable                                                  */
      __IOM MDR_OnOff  IWDT_CLK_EN   : 1;         /*!< [10..10] IWDT Clock Enable                                                */
      __IOM MDR_OnOff  PWR_CLK_EN    : 1;         /*!< [11..11] Power Clock Enable                                               */
      __IOM MDR_OnOff  BKP_CLK_EN    : 1;         /*!< [12..12] Backup Clock Enable                                              */
      __IOM MDR_OnOff  ADCIU_CLK_EN  : 1;         /*!< [13..13] ADCIU Clock Enable                                               */
      __IOM MDR_OnOff  TIMER1_CLK_EN : 1;         /*!< [14..14] TIMER1 Clock Enable                                              */
      __IOM MDR_OnOff  TIMER2_CLK_EN : 1;         /*!< [15..15] TIMER2 Clock Enable                                              */
      __IOM MDR_OnOff  PORTA_CLK_EN  : 1;         /*!< [16..16] GPIO PORT_A Clock Enable                                         */
      __IOM MDR_OnOff  PORTB_CLK_EN  : 1;         /*!< [17..17] GPIO PORT_B Clock Enable                                         */
      __IOM MDR_OnOff  PORTC_CLK_EN  : 1;         /*!< [18..18] GPIO PORT_C Clock Enable                                         */
      __IOM MDR_OnOff  CRC_CLK_EN    : 1;         /*!< [19..19] CRC Clock Enable                                                 */
      __IM  uint32_t                : 12;
} MDR_RST_PER2_Bits;

#define MDR_RST_PER2__SPI1_CLK_EN_Pos   (0UL)            /*!< MDR_RST_CLOCK PER2_CLOCK: SPI1_CLK_EN (Bit 0)                       */
#define MDR_RST_PER2__SPI1_CLK_EN_Msk   (0x1UL)          /*!< MDR_RST_CLOCK PER2_CLOCK: SPI1_CLK_EN (Bitfield-Mask: 0x01)         */
#define MDR_RST_PER2__UART1_CLK_EN_Pos  (1UL)            /*!< MDR_RST_CLOCK PER2_CLOCK: UART1_CLK_EN (Bit 1)                      */
#define MDR_RST_PER2__UART1_CLK_EN_Msk  (0x2UL)          /*!< MDR_RST_CLOCK PER2_CLOCK: UART1_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_PER2__UART2_CLK_EN_Pos  (2UL)            /*!< MDR_RST_CLOCK PER2_CLOCK: UART2_CLK_EN (Bit 2)                      */
#define MDR_RST_PER2__UART2_CLK_EN_Msk  (0x4UL)          /*!< MDR_RST_CLOCK PER2_CLOCK: UART2_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_PER2__EEPROM_CLK_EN_Pos (3UL)            /*!< MDR_RST_CLOCK PER2_CLOCK: EEPROM_CLK_EN (Bit 3)                     */
#define MDR_RST_PER2__EEPROM_CLK_EN_Msk (0x8UL)          /*!< MDR_RST_CLOCK PER2_CLOCK: EEPROM_CLK_EN (Bitfield-Mask: 0x01)       */
#define MDR_RST_PER2__RST_CLK_EN_Pos    (4UL)            /*!< MDR_RST_CLOCK PER2_CLOCK: RST_CLK_EN (Bit 4)                        */
#define MDR_RST_PER2__RST_CLK_EN_Msk    (0x10UL)         /*!< MDR_RST_CLOCK PER2_CLOCK: RST_CLK_EN (Bitfield-Mask: 0x01)          */
#define MDR_RST_PER2__ADC_CLK_EN_Pos    (8UL)            /*!< MDR_RST_CLOCK PER2_CLOCK: ADC_CLK_EN (Bit 8)                        */
#define MDR_RST_PER2__ADC_CLK_EN_Msk    (0x100UL)        /*!< MDR_RST_CLOCK PER2_CLOCK: ADC_CLK_EN (Bitfield-Mask: 0x01)          */
#define MDR_RST_PER2__WWDT_CLK_EN_Pos   (9UL)            /*!< MDR_RST_CLOCK PER2_CLOCK: WWDT_CLK_EN (Bit 9)                       */
#define MDR_RST_PER2__WWDT_CLK_EN_Msk   (0x200UL)        /*!< MDR_RST_CLOCK PER2_CLOCK: WWDT_CLK_EN (Bitfield-Mask: 0x01)         */
#define MDR_RST_PER2__IWDT_CLK_EN_Pos   (10UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: IWDT_CLK_EN (Bit 10)                      */
#define MDR_RST_PER2__IWDT_CLK_EN_Msk   (0x400UL)        /*!< MDR_RST_CLOCK PER2_CLOCK: IWDT_CLK_EN (Bitfield-Mask: 0x01)         */
#define MDR_RST_PER2__PWR_CLK_EN_Pos    (11UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: PWR_CLK_EN (Bit 11)                       */
#define MDR_RST_PER2__PWR_CLK_EN_Msk    (0x800UL)        /*!< MDR_RST_CLOCK PER2_CLOCK: PWR_CLK_EN (Bitfield-Mask: 0x01)          */
#define MDR_RST_PER2__BKP_CLK_EN_Pos    (12UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: BKP_CLK_EN (Bit 12)                       */
#define MDR_RST_PER2__BKP_CLK_EN_Msk    (0x1000UL)       /*!< MDR_RST_CLOCK PER2_CLOCK: BKP_CLK_EN (Bitfield-Mask: 0x01)          */
#define MDR_RST_PER2__ADCIU_CLK_EN_Pos  (13UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: ADCIU_CLK_EN (Bit 13)                     */
#define MDR_RST_PER2__ADCIU_CLK_EN_Msk  (0x2000UL)       /*!< MDR_RST_CLOCK PER2_CLOCK: ADCIU_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_PER2__TIMER1_CLK_EN_Pos (14UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: TIMER1_CLK_EN (Bit 14)                    */
#define MDR_RST_PER2__TIMER1_CLK_EN_Msk (0x4000UL)       /*!< MDR_RST_CLOCK PER2_CLOCK: TIMER1_CLK_EN (Bitfield-Mask: 0x01)       */
#define MDR_RST_PER2__TIMER2_CLK_EN_Pos (15UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: TIMER2_CLK_EN (Bit 15)                    */
#define MDR_RST_PER2__TIMER2_CLK_EN_Msk (0x8000UL)       /*!< MDR_RST_CLOCK PER2_CLOCK: TIMER2_CLK_EN (Bitfield-Mask: 0x01)       */
#define MDR_RST_PER2__PORTA_CLK_EN_Pos  (16UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: PORTA_CLK_EN (Bit 16)                     */
#define MDR_RST_PER2__PORTA_CLK_EN_Msk  (0x10000UL)      /*!< MDR_RST_CLOCK PER2_CLOCK: PORTA_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_PER2__PORTB_CLK_EN_Pos  (17UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: PORTB_CLK_EN (Bit 17)                     */
#define MDR_RST_PER2__PORTB_CLK_EN_Msk  (0x20000UL)      /*!< MDR_RST_CLOCK PER2_CLOCK: PORTB_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_PER2__PORTC_CLK_EN_Pos  (18UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: PORTC_CLK_EN (Bit 18)                     */
#define MDR_RST_PER2__PORTC_CLK_EN_Msk  (0x40000UL)      /*!< MDR_RST_CLOCK PER2_CLOCK: PORTC_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_PER2__CRC_CLK_EN_Pos    (19UL)           /*!< MDR_RST_CLOCK PER2_CLOCK: CRC_CLK_EN (Bit 19)                       */
#define MDR_RST_PER2__CRC_CLK_EN_Msk    (0x80000UL)      /*!< MDR_RST_CLOCK PER2_CLOCK: CRC_CLK_EN (Bitfield-Mask: 0x01)          */



/* =============================================  RST CLOCK Block  ========================================================= */

typedef struct {                                /*!< (@ 0x40020000) MDR_RST_CLOCK Structure                                    */
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
    __IOM uint32_t       PER1_CLOCK;                  /*!< (@ 0x00000010) Peripherials Clock Control1                                */
    MDR_RST_PER1_Bits    PER1_CLOCK_b;
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
    __IOM uint32_t       PER2_CLOCK;                  /*!< (@ 0x0000001C) Peripherials Clock Control2                                */
    MDR_RST_PER2_Bits    PER2_CLOCK_b;
  };  
  
  __IM  uint32_t         RESERVED;                   /*!< (@ 0x00000020) RESERVED                                                    */
  
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

} MDR_RST_CLOCK_Type;                                /*!< Size = 48 (0x30)                                                           */


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

#endif  //_MDR_RST_VK234_DEFS_H
