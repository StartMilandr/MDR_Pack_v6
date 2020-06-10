#ifndef _MDR_RST_VE1X_DEFS_H
#define _MDR_RST_VE1X_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include "MDR_Types.h"
#include "MDR_TypesVEx.h"


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

/* =====================================================  CLOCK_STATUS  ====================================================== */
typedef struct {
      __IM  MDR_OnOff  PLL_USB_RDY : 1;           /*!< [0..0] PLL USP ready                                                    */
      __IM  MDR_OnOff  PLL_CPU_RDY : 1;           /*!< [1..1] PLL CPU ready                                                    */
      __IM  MDR_OnOff  HSE_RDY     : 1;           /*!< [2..2] HSE generator ready                                              */
      __IM  MDR_OnOff  HSE2_RDY    : 1;           /*!< [3..3] HSE2 generator ready                                             */ 
      __IM  uint32_t               : 28;          /*!< [31..3] UNUSED                                                          */
} MDR_RST_STATUS_Bits;

#define MDR_RST_STATUS__PLL_USB_RDY_Pos (0UL)            /*!< MDR_RST_CLOCK CLOCK_STATUS: PLL_USB_RDY (Bit 0)                  */
#define MDR_RST_STATUS__PLL_USB_RDY_Msk (0x1UL)          /*!< MDR_RST_CLOCK CLOCK_STATUS: PLL_USB_RDY (Bitfield-Mask: 0x01)    */
#define MDR_RST_STATUS__PLL_CPU_RDY_Pos (1UL)            /*!< MDR_RST_CLOCK CLOCK_STATUS: PLL_CPU_RDY (Bit 1)                  */
#define MDR_RST_STATUS__PLL_CPU_RDY_Msk (0x2UL)          /*!< MDR_RST_CLOCK CLOCK_STATUS: PLL_CPU_RDY (Bitfield-Mask: 0x01)    */
#define MDR_RST_STATUS__HSE_RDY_Pos     (2UL)            /*!< MDR_RST_CLOCK CLOCK_STATUS: HSE_RDY (Bit 2)                      */
#define MDR_RST_STATUS__HSE_RDY_Msk     (0x4UL)          /*!< MDR_RST_CLOCK CLOCK_STATUS: HSE_RDY (Bitfield-Mask: 0x01)        */
#define MDR_RST_STATUS__HSE2_RDY_Pos    (3UL)            /*!< MDR_RST_CLOCK CLOCK_STATUS: HSE2_RDY (Bit 3)                     */
#define MDR_RST_STATUS__HSE2_RDY_Msk    (0x8UL)          /*!< MDR_RST_CLOCK CLOCK_STATUS: HSE2_RDY (Bitfield-Mask: 0x01)       */

/* ======================================================  PLL_CONTROL  ====================================================== */
typedef struct {
      __IOM MDR_OnOff   PLL_USB_ON  : 1;           /*!< [0..0] PLL USB Enable                                                  */
      __IOM MDR_OnOff   PLL_USB_RLD : 1;           /*!< [1..1] PLL USB Restart                                                 */  
      __IOM MDR_OnOff   PLL_CPU_ON  : 1;           /*!< [2..2] PLL Enable                                                      */
      __IOM MDR_OnOff   PLL_CPU_RLD : 1;           /*!< [3..3] PLL Restart                                                     */
      __IOM MDR_MUL_x16 PLL_USB_MUL : 4;           /*!< [7..4] PLL USB Mul, [x2 .. x16]                                        */
      __IOM MDR_MUL_x16 PLL_CPU_MUL : 4;           /*!< [11..8] PLL Mul, [x2 .. x16]                                           */
      __IM  uint32_t                : 20;
} MDR_RST_PLL_Bits;

#define MDR_RST_PLL__USB_ON_Pos  (0UL)             /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_USB_ON (Bit 0)                          */
#define MDR_RST_PLL__USB_ON_Msk  (0x1UL)           /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_USB_ON (Bitfield-Mask: 0x01)            */
#define MDR_RST_PLL__USB_RLD_Pos (1UL)             /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_USB_PLD (Bit 1)                         */
#define MDR_RST_PLL__USB_RLD_Msk (0x2UL)           /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_USB_PLD (Bitfield-Mask: 0x01)           */
#define MDR_RST_PLL__CPU_ON_Pos  (2UL)             /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_CPU_ON (Bit 2)                          */
#define MDR_RST_PLL__CPU_ON_Msk  (0x4UL)           /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_CPU_ON (Bitfield-Mask: 0x01)            */
#define MDR_RST_PLL__CPU_RLD_Pos (3UL)             /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_CPU_PLD (Bit 3)                         */
#define MDR_RST_PLL__CPU_RLD_Msk (0x8UL)           /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_CPU_PLD (Bitfield-Mask: 0x01)           */
#define MDR_RST_PLL__USB_MUL_Pos (4UL)             /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_USB_MUL (Bit 4)                         */
#define MDR_RST_PLL__USB_MUL_Msk (0xf0UL)          /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_USB_MUL (Bitfield-Mask: 0x0f)           */
#define MDR_RST_PLL__CPU_MUL_Pos (8UL)             /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_CPU_MUL (Bit 8)                         */
#define MDR_RST_PLL__CPU_MUL_Msk (0xf00UL)         /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_CPU_MUL (Bitfield-Mask: 0x0f)           */


/* ======================================================  HS_CONTROL  ======================================================= */

typedef struct {
      __IOM MDR_OnOff  HSE_ON     : 1;            /*!< [0..0] HSE Enable                                                       */  
      __IOM MDR_OnOff  HSE_BYP    : 1;            /*!< [1..1] HSE Bypass Mode                                                  */
      __IOM MDR_OnOff  HSE2_ON    : 1;            /*!< [2..2] HSE2 Enable                                                      */
      __IOM MDR_OnOff  HSE2_BYP   : 1;            /*!< [3..3] HSE2 Bypass Mode                                                 */  
      __IM  uint32_t             : 28;
} MDR_RST_HS_Bits;

#define MDR_RST_HS__HSE_ON_Pos   (0UL)                 /*!< MDR_RST_CLOCK HS_CONTROL: HSE_ON (Bit 0)                           */
#define MDR_RST_HS__HSE_ON_Msk   (0x1UL)               /*!< MDR_RST_CLOCK HS_CONTROL: HSE_ON (Bitfield-Mask: 0x01)             */
#define MDR_RST_HS__HSE_BYP_Pos  (1UL)                 /*!< MDR_RST_CLOCK HS_CONTROL: HSE_BYP (Bit 1)                          */
#define MDR_RST_HS__HSE_BYP_Msk  (0x2UL)               /*!< MDR_RST_CLOCK HS_CONTROL: HSE_BYP (Bitfield-Mask: 0x01)            */
#define MDR_RST_HS__HSE2_ON_Pos  (2UL)                 /*!< MDR_RST_CLOCK HS_CONTROL: HSE2_ON (Bit 2)                          */
#define MDR_RST_HS__HSE2_ON_Msk  (0x4UL)               /*!< MDR_RST_CLOCK HS_CONTROL: HSE2_ON (Bitfield-Mask: 0x01)            */
#define MDR_RST_HS__HSE2_BYP_Pos (3UL)                 /*!< MDR_RST_CLOCK HS_CONTROL: HSE2_BYP (Bit 3)                         */
#define MDR_RST_HS__HSE2_BYP_Msk (0x8UL)               /*!< MDR_RST_CLOCK HS_CONTROL: HSE2_BYP (Bitfield-Mask: 0x01)           */

/* =======================================================  CPU_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_CLK_SEL_HSIE2 CPU_C1_SEL : 2;            /*!< [1..0] CPU_C1 mux freq select                                    */
      __IOM MDR_CLK_SEL_CPU   CPU_C2_SEL : 1;            /*!< [2..2] CPU_C2 mux freq select                                    */
      __IM  uint32_t                     : 1;
      __IOM MDR_Div256P   CPU_C3_SEL : 4;            /*!< [7..4] CPU_C2 mux output freq devider, [/1, /2, /4 .. /256]      */
      __IOM MDR_CLK_SEL_HCLK  HCLK_SEL   : 2;            /*!< [9..8] Select Clock for CPU                                      */
      __IM  uint32_t                     : 22;
} MDR_RST_CPU_Bits;

#define MDR_RST_CPU__C1_SEL_Pos     (0UL)                /*!< MDR_RST_CLOCK CPU_CLOCK: CPU_C1_SEL (Bit 0)                      */
#define MDR_RST_CPU__C1_SEL_Msk     (0x3UL)              /*!< MDR_RST_CLOCK CPU_CLOCK: CPU_C1_SEL (Bitfield-Mask: 0x03)        */
#define MDR_RST_CPU__C2_SEL_Pos     (2UL)                /*!< MDR_RST_CLOCK CPU_CLOCK: CPU_C2_SEL (Bit 2)                      */
#define MDR_RST_CPU__C2_SEL_Msk     (0x4UL)              /*!< MDR_RST_CLOCK CPU_CLOCK: CPU_C2_SEL (Bitfield-Mask: 0x01)        */
#define MDR_RST_CPU__C3_SEL_Pos     (4UL)                /*!< MDR_RST_CLOCK CPU_CLOCK: CPU_C3_SEL (Bit 4)                      */
#define MDR_RST_CPU__C3_SEL_Msk     (0xf0UL)             /*!< MDR_RST_CLOCK CPU_CLOCK: CPU_C3_SEL (Bitfield-Mask: 0x0f)        */
#define MDR_RST_CPU__HCLK_SEL_Pos   (8UL)                /*!< MDR_RST_CLOCK CPU_CLOCK: HCLK_SEL (Bit 8)                        */
#define MDR_RST_CPU__HCLK_SEL_Msk   (0x300UL)            /*!< MDR_RST_CLOCK CPU_CLOCK: HCLK_SEL (Bitfield-Mask: 0x03)          */

/* =======================================================  USB_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_CLK_SEL_HSIE2 USB_C1_SEL : 2;            /*!< [1..0] USB_C1 mux freq select                                    */
      __IOM MDR_CLK_SEL_USB   USB_C2_SEL : 1;            /*!< [2..2] USB_C2 mux freq select                                    */
      __IM  uint32_t                     : 1;
      __IOM MDR_DIV_2         USB_C3_SEL : 1;            /*!< [4..4] USB_C3 Input Select                                       */
      __IM  uint32_t                     : 3;
      __IOM MDR_OnOff         USB_EN     : 1;            /*!< [8..8] USB Clock Enable                                          */
      __IM  uint32_t                     : 23;
} MDR_RST_USB_Bits;

#define MDR_RST_USB__C1_SEL_Pos (0UL)                /*!< MDR_RST_CLOCK USB_CLOCK: USB_C1_SEL (Bit 0)                          */
#define MDR_RST_USB__C1_SEL_Msk (0x3UL)              /*!< MDR_RST_CLOCK USB_CLOCK: USB_C1_SEL (Bitfield-Mask: 0x03)            */
#define MDR_RST_USB__C2_SEL_Pos (2UL)                /*!< MDR_RST_CLOCK USB_CLOCK: USB_C2_SEL (Bit 2)                          */
#define MDR_RST_USB__C2_SEL_Msk (0x4UL)              /*!< MDR_RST_CLOCK USB_CLOCK: USB_C2_SEL (Bitfield-Mask: 0x01)            */
#define MDR_RST_USB__C3_SEL_Pos (4UL)                /*!< MDR_RST_CLOCK USB_CLOCK: USB_C3_SEL (Bit 4)                          */
#define MDR_RST_USB__C3_SEL_Msk (0x10UL)             /*!< MDR_RST_CLOCK USB_CLOCK: USB_C3_SEL (Bitfield-Mask: 0x01)            */
#define MDR_RST_USB__EN_Pos (8UL)                    /*!< MDR_RST_CLOCK USB_CLOCK: USB_EN (Bit 8)                              */
#define MDR_RST_USB__EN_Msk (0x100UL)                /*!< MDR_RST_CLOCK USB_CLOCK: USB_EN (Bitfield-Mask: 0x01)                */


/* =======================================================  RTC_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_Div256P  HSE_SEL    : 4;            /*!< [3..0] RTC HSE freq devider, [/1, /2, /4 .. /256]                 */
      __IOM MDR_Div256P  HSI_SEL    : 4;            /*!< [7..4] RTC HSI freq devider, [/1, /2, /4 .. /256]                 */
      __IOM MDR_OnOff    HSE_RTC_EN : 1;            /*!< [8..8] RTC HSE Clock enable                                       */
      __IOM MDR_OnOff    HSI_RTC_EN : 1;            /*!< [9..9] RTC HSI Clock enable                                       */
      __IM  uint32_t     : 22;
} MDR_RST_RTC_Bits;

#define MDR_RST_RTC__HSE_SEL_Pos    (0UL)                /*!< MDR_RST_CLOCK RTC_CLOCK: HSE_SEL (Bit 0)                         */
#define MDR_RST_RTC__HSE_SEL_Msk    (0xfUL)              /*!< MDR_RST_CLOCK RTC_CLOCK: HSE_SEL (Bitfield-Mask: 0x0f)           */
#define MDR_RST_RTC__HSI_SEL_Pos    (4UL)                /*!< MDR_RST_CLOCK RTC_CLOCK: HSI_SEL (Bit 4)                         */
#define MDR_RST_RTC__HSI_SEL_Msk    (0xf0UL)             /*!< MDR_RST_CLOCK RTC_CLOCK: HSI_SEL (Bitfield-Mask: 0x0f)           */
#define MDR_RST_RTC__HSE_RTC_EN_Pos (8UL)                /*!< MDR_RST_CLOCK RTC_CLOCK: HSE_RTC_EN (Bit 8)                      */
#define MDR_RST_RTC__HSE_RTC_EN_Msk (0x100UL)            /*!< MDR_RST_CLOCK RTC_CLOCK: HSE_RTC_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_RTC__HSI_RTC_EN_Pos (9UL)                /*!< MDR_RST_CLOCK RTC_CLOCK: HSI_RTC_EN (Bit 9)                      */
#define MDR_RST_RTC__HSI_RTC_EN_Msk (0x200UL)            /*!< MDR_RST_CLOCK RTC_CLOCK: HSI_RTC_EN (Bitfield-Mask: 0x01)        */

/* =======================================================  PER_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_OnOff  CAN1_CLK_EN     : 1;         /*!< [0..0] CAN1 Clock Enable                                              */
      __IOM MDR_OnOff  CAN2_CLK_EN     : 1;         /*!< [1..1] CAN2 Clock Enable                                              */
      __IOM MDR_OnOff  USB_CLK_EN      : 1;         /*!< [2..2] USB Clock Enable                                               */
      __IOM MDR_OnOff  EEPROM_CLK_EN   : 1;         /*!< [3..3] EEPROM Controller Clock Enable                                 */
      __IOM MDR_OnOff  RST_CLK_EN      : 1;         /*!< [4..4] RST Clock Enable                                               */
      __IOM MDR_OnOff  DMA_CLK_EN      : 1;         /*!< [5..5] DMA Clock Enable                                               */
      __IOM MDR_OnOff  UART1_CLK_EN    : 1;         /*!< [6..6] UART1 Clock Enable                                             */
      __IOM MDR_OnOff  UART2_CLK_EN    : 1;         /*!< [7..7] UART2 Clock Enable                                             */
      __IOM MDR_OnOff  SPI1_CLK_EN     : 1;         /*!< [8..8] SPI1 Clock Enable                                              */
      __IOM MDR_OnOff  MIL1_CLK_EN     : 1;         /*!< [9..9] MIL1 Clock Enable                                              */
      __IOM MDR_OnOff  MIL2_CLK_EN     : 1;         /*!< [10..10] MIL2 Clock Enable                                            */
      __IOM MDR_OnOff  PWR_CLK_EN      : 1;         /*!< [11..11] Power Clock Enable                                           */
      __IOM MDR_OnOff  WWDT_CLK_EN     : 1;         /*!< [12..12] WWDT Clock Enable                                            */
      __IOM MDR_OnOff  IWDT_CLK_EN     : 1;         /*!< [13..13] IWDT Clock Enable                                            */
      __IOM MDR_OnOff  TIMER1_CLK_EN   : 1;         /*!< [14..14] TIMER1 Clock Enable                                          */
      __IOM MDR_OnOff  TIMER2_CLK_EN   : 1;         /*!< [15..15] TIMER2 Clock Enable                                          */
      __IOM MDR_OnOff  TIMER3_CLK_EN   : 1;         /*!< [16..16] TIMER3 Clock Enable                                          */
      __IOM MDR_OnOff  ADC_CLK_EN      : 1;         /*!< [17..17] ADC Clock Enable                                             */
      __IOM MDR_OnOff  DAC_CLK_EN      : 1;         /*!< [18..18] DAC Clock Enable                                             */
      __IOM MDR_OnOff  TIMER4_CLK_EN   : 1;         /*!< [19..19] TIMER4 Clock Enable                                          */
      __IOM MDR_OnOff  SPI2_CLK_EN     : 1;         /*!< [20..20] SPI2 Clock Enable                                            */
      __IOM MDR_OnOff  PORTA_CLK_EN    : 1;         /*!< [21..21] GPIO PORT_A Clock Enable                                     */
      __IOM MDR_OnOff  PORTB_CLK_EN    : 1;         /*!< [22..22] GPIO PORT_B Clock Enable                                     */
      __IOM MDR_OnOff  PORTC_CLK_EN    : 1;         /*!< [23..23] GPIO PORT_C Clock Enable                                     */
      __IOM MDR_OnOff  PORTD_CLK_EN    : 1;         /*!< [24..24] GPIO PORT_D Clock Enable                                     */
      __IOM MDR_OnOff  PORTE_CLK_EN    : 1;         /*!< [25..25] GPIO PORT_E Clock Enable                                     */
      __IOM MDR_OnOff  ARINC_RX_CLK_EN : 1;         /*!< [26..26] ARINC_RX Clock Enable                                        */
      __IOM MDR_OnOff  BKP_CLK_EN      : 1;         /*!< [27..27] Backup Clock Enable                                          */
      __IOM MDR_OnOff  ARINC_TX_CLK_EN : 1;         /*!< [28..28] ARINC_TX Clock Enable                                        */
      __IOM MDR_OnOff  PORTF_CLK_EN    : 1;         /*!< [29..29] GPIO PORT_F Clock Enable                                     */
      __IOM MDR_OnOff  EBC_CLK_EN      : 1;         /*!< [30..30] External Bus Clock Enable                                    */
      __IOM MDR_OnOff  SPI3_CLK_EN     : 1;         /*!< [31..31] SPI3 Clock Enable                                            */
} MDR_RST_PER_Bits;

#define MDR_RST_PER__CAN1_CLK_EN_Pos    (0UL)             /*!< MDR_RST_CLOCK PER_CLOCK: CAN1_CLK_EN (Bit 0)                   */
#define MDR_RST_PER__CAN1_CLK_EN_Msk    (0x1UL)           /*!< MDR_RST_CLOCK PER_CLOCK: CAN1_CLK_EN (Bitfield-Mask: 0x01)     */
#define MDR_RST_PER__CAN2_CLK_EN_Pos    (1UL)             /*!< MDR_RST_CLOCK PER_CLOCK: CAN2_CLK_EN (Bit 1)                   */
#define MDR_RST_PER__CAN2_CLK_EN_Msk    (0x2UL)           /*!< MDR_RST_CLOCK PER_CLOCK: CAN2_CLK_EN (Bitfield-Mask: 0x01)     */
#define MDR_RST_PER__USB_CLK_EN_Pos     (2UL)             /*!< MDR_RST_CLOCK PER_CLOCK: USB_CLK_EN (Bit 2)                    */
#define MDR_RST_PER__USB_CLK_EN_Msk     (0x4UL)           /*!< MDR_RST_CLOCK PER_CLOCK: USB_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_PER__EEPROM_CLK_EN_Pos  (3UL)             /*!< MDR_RST_CLOCK PER_CLOCK: EEPROM_CLK_EN (Bit 3)                 */
#define MDR_RST_PER__EEPROM_CLK_EN_Msk  (0x8UL)           /*!< MDR_RST_CLOCK PER_CLOCK: EEPROM_CLK_EN (Bitfield-Mask: 0x01)   */
#define MDR_RST_PER__RST_CLK_EN_Pos     (4UL)             /*!< MDR_RST_CLOCK PER_CLOCK: RST_CLK_EN (Bit 4)                    */
#define MDR_RST_PER__RST_CLK_EN_Msk     (0x10UL)          /*!< MDR_RST_CLOCK PER_CLOCK: RST_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_PER__DMA_CLK_EN_Pos     (5UL)             /*!< MDR_RST_CLOCK PER_CLOCK: DMA_CLK_EN (Bit 5)                    */
#define MDR_RST_PER__DMA_CLK_EN_Msk     (0x20UL)          /*!< MDR_RST_CLOCK PER_CLOCK: DMA_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_PER__UART1_CLK_EN_Pos   (6UL)             /*!< MDR_RST_CLOCK PER_CLOCK: UART1_CLK_EN (Bit 6)                  */
#define MDR_RST_PER__UART1_CLK_EN_Msk   (0x40UL)          /*!< MDR_RST_CLOCK PER_CLOCK: UART1_CLK_EN (Bitfield-Mask: 0x01)    */
#define MDR_RST_PER__UART2_CLK_EN_Pos   (7UL)             /*!< MDR_RST_CLOCK PER_CLOCK: UART2_CLK_EN (Bit 7)                  */
#define MDR_RST_PER__UART2_CLK_EN_Msk   (0x80UL)          /*!< MDR_RST_CLOCK PER_CLOCK: UART2_CLK_EN (Bitfield-Mask: 0x01)    */
#define MDR_RST_PER__SSP1_CLK_EN_Pos    (8UL)             /*!< MDR_RST_CLOCK PER_CLOCK: SPI1_CLK_EN (Bit 8)                   */
#define MDR_RST_PER__SSP1_CLK_EN_Msk    (0x100UL)         /*!< MDR_RST_CLOCK PER_CLOCK: SPI1_CLK_EN (Bitfield-Mask: 0x01)     */
#define MDR_RST_PER__MIL1_CLK_EN_Pos    (9UL)             /*!< MDR_RST_CLOCK PER_CLOCK: MIL1_CLK_EN (Bit 9)                   */
#define MDR_RST_PER__MIL1_CLK_EN_Msk    (0x200UL)         /*!< MDR_RST_CLOCK PER_CLOCK: MIL1_CLK_EN (Bitfield-Mask: 0x01)     */
#define MDR_RST_PER__MIL2_CLK_EN_Pos    (10UL)            /*!< MDR_RST_CLOCK PER_CLOCK: MIL2_CLK_EN (Bit 10)                  */
#define MDR_RST_PER__MIL2_CLK_EN_Msk    (0x400UL)         /*!< MDR_RST_CLOCK PER_CLOCK: MIL2_CLK_EN (Bitfield-Mask: 0x01)     */
#define MDR_RST_PER__PWR_CLK_EN_Pos     (11UL)            /*!< MDR_RST_CLOCK PER_CLOCK: PWR_CLK_EN (Bit 11)                   */
#define MDR_RST_PER__PWR_CLK_EN_Msk     (0x800UL)         /*!< MDR_RST_CLOCK PER_CLOCK: PWR_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_PER__WWDT_CLK_EN_Pos    (12UL)            /*!< MDR_RST_CLOCK PER_CLOCK: WWDT_CLK_EN (Bit 12)                  */
#define MDR_RST_PER__WWDT_CLK_EN_Msk    (0x1000UL)        /*!< MDR_RST_CLOCK PER_CLOCK: WWDT_CLK_EN (Bitfield-Mask: 0x01)     */
#define MDR_RST_PER__IWDT_CLK_EN_Pos    (13UL)            /*!< MDR_RST_CLOCK PER_CLOCK: IWDT_CLK_EN (Bit 13)                  */
#define MDR_RST_PER__IWDT_CLK_EN_Msk    (0x2000UL)        /*!< MDR_RST_CLOCK PER_CLOCK: IWDT_CLK_EN (Bitfield-Mask: 0x01)     */
#define MDR_RST_PER__TIMER1_CLK_EN_Pos  (14UL)            /*!< MDR_RST_CLOCK PER_CLOCK: TIMER1_CLK_EN (Bit 14)                */
#define MDR_RST_PER__TIMER1_CLK_EN_Msk  (0x4000UL)        /*!< MDR_RST_CLOCK PER_CLOCK: TIMER1_CLK_EN (Bitfield-Mask: 0x01)   */
#define MDR_RST_PER__TIMER2_CLK_EN_Pos  (15UL)            /*!< MDR_RST_CLOCK PER_CLOCK: TIMER2_CLK_EN (Bit 15)                */
#define MDR_RST_PER__TIMER2_CLK_EN_Msk  (0x8000UL)        /*!< MDR_RST_CLOCK PER_CLOCK: TIMER2_CLK_EN (Bitfield-Mask: 0x01)   */
#define MDR_RST_PER__TIMER3_CLK_EN_Pos  (16UL)            /*!< MDR_RST_CLOCK PER_CLOCK: TIMER3_CLK_EN (Bit 16)                */
#define MDR_RST_PER__TIMER3_CLK_EN_Msk  (0x10000UL)       /*!< MDR_RST_CLOCK PER_CLOCK: TIMER3_CLK_EN (Bitfield-Mask: 0x01)   */
#define MDR_RST_PER__ADC_CLK_EN_Pos     (17UL)            /*!< MDR_RST_CLOCK PER_CLOCK: ADC_CLK_EN (Bit 17)                   */
#define MDR_RST_PER__ADC_CLK_EN_Msk     (0x20000UL)       /*!< MDR_RST_CLOCK PER_CLOCK: ADC_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_PER__DAC_CLK_EN_Pos     (18UL)            /*!< MDR_RST_CLOCK PER_CLOCK: DAC_CLK_EN (Bit 18)                   */
#define MDR_RST_PER__DAC_CLK_EN_Msk     (0x40000UL)       /*!< MDR_RST_CLOCK PER_CLOCK: DAC_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_PER__TIMER4_CLK_EN_Pos  (19UL)            /*!< MDR_RST_CLOCK PER_CLOCK: TIMER4_CLK_EN (Bit 19)                */
#define MDR_RST_PER__TIMER4_CLK_EN_Msk  (0x80000UL)       /*!< MDR_RST_CLOCK PER_CLOCK: TIMER4_CLK_EN (Bitfield-Mask: 0x01)   */
#define MDR_RST_PER__SSP2_CLK_EN_Pos    (20UL)            /*!< MDR_RST_CLOCK PER_CLOCK: SPI2_CLK_EN (Bit 20)                  */
#define MDR_RST_PER__SSP2_CLK_EN_Msk    (0x100000UL)      /*!< MDR_RST_CLOCK PER_CLOCK: SPI2_CLK_EN (Bitfield-Mask: 0x01)     */
#define MDR_RST_PER__PORTA_CLK_EN_Pos   (21UL)            /*!< MDR_RST_CLOCK PER_CLOCK: PORTA_CLK_EN (Bit 21)                 */
#define MDR_RST_PER__PORTA_CLK_EN_Msk   (0x200000UL)      /*!< MDR_RST_CLOCK PER_CLOCK: PORTA_CLK_EN (Bitfield-Mask: 0x01)    */
#define MDR_RST_PER__PORTB_CLK_EN_Pos   (22UL)            /*!< MDR_RST_CLOCK PER_CLOCK: PORTB_CLK_EN (Bit 22)                 */
#define MDR_RST_PER__PORTB_CLK_EN_Msk   (0x400000UL)      /*!< MDR_RST_CLOCK PER_CLOCK: PORTB_CLK_EN (Bitfield-Mask: 0x01)    */
#define MDR_RST_PER__PORTC_CLK_EN_Pos   (23UL)            /*!< MDR_RST_CLOCK PER_CLOCK: PORTC_CLK_EN (Bit 23)                 */
#define MDR_RST_PER__PORTC_CLK_EN_Msk   (0x800000UL)      /*!< MDR_RST_CLOCK PER_CLOCK: PORTC_CLK_EN (Bitfield-Mask: 0x01)    */
#define MDR_RST_PER__PORTD_CLK_EN_Pos   (24UL)            /*!< MDR_RST_CLOCK PER_CLOCK: PORTD_CLK_EN (Bit 24)                 */
#define MDR_RST_PER__PORTD_CLK_EN_Msk   (0x1000000UL)     /*!< MDR_RST_CLOCK PER_CLOCK: PORTD_CLK_EN (Bitfield-Mask: 0x01)    */
#define MDR_RST_PER__PORTE_CLK_EN_Pos   (25UL)            /*!< MDR_RST_CLOCK PER_CLOCK: PORTE_CLK_EN (Bit 25)                 */
#define MDR_RST_PER__PORTE_CLK_EN_Msk   (0x2000000UL)     /*!< MDR_RST_CLOCK PER_CLOCK: PORTE_CLK_EN (Bitfield-Mask: 0x01)    */
#define MDR_RST_PER__ARINC_RX_CLK_EN_Pos (26UL)           /*!< MDR_RST_CLOCK PER_CLOCK: ARINC_RX_CLK_EN (Bit 26)              */
#define MDR_RST_PER__ARINC_RX_CLK_EN_Msk (0x4000000UL)    /*!< MDR_RST_CLOCK PER_CLOCK: ARINC_RX_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER__BKP_CLK_EN_Pos     (27UL)            /*!< MDR_RST_CLOCK PER_CLOCK: BKP_CLK_EN (Bit 27)                   */
#define MDR_RST_PER__BKP_CLK_EN_Msk     (0x8000000UL)     /*!< MDR_RST_CLOCK PER_CLOCK: BKP_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_PER__ARINC_TX_CLK_EN_Pos (28UL)           /*!< MDR_RST_CLOCK PER_CLOCK: ARINC_TX_CLK_EN (Bit 28)              */
#define MDR_RST_PER__ARINC_TX_CLK_EN_Msk (0x10000000UL)   /*!< MDR_RST_CLOCK PER_CLOCK: ARINC_TX_CLK_EN (Bitfield-Mask: 0x01) */
#define MDR_RST_PER__PORTF_CLK_EN_Pos   (29UL)            /*!< MDR_RST_CLOCK PER_CLOCK: PORTF_CLK_EN (Bit 29)                 */
#define MDR_RST_PER__PORTF_CLK_EN_Msk   (0x20000000UL)    /*!< MDR_RST_CLOCK PER_CLOCK: PORTF_CLK_EN (Bitfield-Mask: 0x01)    */
#define MDR_RST_PER__EBC_CLK_EN_Pos     (30UL)            /*!< MDR_RST_CLOCK PER_CLOCK: EBC_CLK_EN (Bit 30)                   */
#define MDR_RST_PER__EBC_CLK_EN_Msk     (0x40000000UL)    /*!< MDR_RST_CLOCK PER_CLOCK: EBC_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_PER__SSP3_CLK_EN_Pos    (31UL)            /*!< MDR_RST_CLOCK PER_CLOCK: SPI3_CLK_EN (Bit 31)                  */
#define MDR_RST_PER__SSP3_CLK_EN_Msk    (0x80000000UL)    /*!< MDR_RST_CLOCK PER_CLOCK: SPI3_CLK_EN (Bitfield-Mask: 0x01)     */


/* =======================================================  CAN_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_Div128P  CAN1_BRG    : 3;     /*!< [2..0] HCLK divider to get CAN1_CLOCK, [/1, /2, /4 .. /128]            */
      __IM  uint32_t                     : 5;
      __IOM MDR_Div128P  CAN2_BRG    : 3;     /*!< [10..8] HCLK freq divider to get CAN2_CLOCK, [/1, /2, /4 ../128]       */
      __IM  uint32_t                     : 13;
      __IOM MDR_OnOff        CAN1_CLK_EN : 1;     /*!< [24..24] CAN1_CLOCK enable                                             */
      __IOM MDR_OnOff        CAN2_CLK_EN : 1;     /*!< [25..25] CAN2_CLOCK enable                                             */
      __IM  uint32_t                     : 6;
} MDR_RST_CAN_Bits;

#define MDR_RST_CAN__CAN1_BRG_Pos    (0UL)               /*!< MDR_RST_CLOCK CAN_CLOCK: CAN1_BRG (Bit 0)                       */
#define MDR_RST_CAN__CAN1_BRG_Msk    (0x7UL)             /*!< MDR_RST_CLOCK CAN_CLOCK: CAN1_BRG (Bitfield-Mask: 0x07)         */
#define MDR_RST_CAN__CAN2_BRG_Pos    (8UL)               /*!< MDR_RST_CLOCK CAN_CLOCK: CAN2_BRG (Bit 8)                       */
#define MDR_RST_CAN__CAN2_BRG_Msk    (0x700UL)           /*!< MDR_RST_CLOCK CAN_CLOCK: CAN2_BRG (Bitfield-Mask: 0x07)         */
#define MDR_RST_CAN__CAN1_CLK_EN_Pos (24UL)              /*!< MDR_RST_CLOCK CAN_CLOCK: CAN1_CLK_EN (Bit 24)                   */
#define MDR_RST_CAN__CAN1_CLK_EN_Msk (0x1000000UL)       /*!< MDR_RST_CLOCK CAN_CLOCK: CAN1_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_CAN__CAN2_CLK_EN_Pos (25UL)              /*!< MDR_RST_CLOCK CAN_CLOCK: CAN2_CLK_EN (Bit 25)                   */
#define MDR_RST_CAN__CAN2_CLK_EN_Msk (0x2000000UL)       /*!< MDR_RST_CLOCK CAN_CLOCK: CAN2_CLK_EN (Bitfield-Mask: 0x01)      */


/* =======================================================  TIM_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_Div128P  TIM1_BRG   : 3;            /*!< [2..0] freq divider to get TIM1_CLOCK, [/1, /2, /4 .. /128]      */
      __IM  uint32_t                    : 5;
      __IOM MDR_Div128P  TIM2_BRG   : 3;            /*!< [10..8] freq divider to get TIM2_CLOCK, [/1, /2, /4 ../128]      */
      __IM  uint32_t                    : 5;
      __IOM MDR_Div128P  TIM3_BRG   : 3;            /*!< [18..16] freq divider to get TIM3_CLOCK, [/1, /2, /4 ../128]     */
      __IM  uint32_t                    : 5;
      __IOM MDR_OnOff       TIM1_CLK_EN : 1;            /*!< [24..24] TIM1_CLOCK enable                                       */
      __IOM MDR_OnOff       TIM2_CLK_EN : 1;            /*!< [25..25] TIM2_CLOCK enable                                       */
      __IOM MDR_OnOff       TIM3_CLK_EN : 1;            /*!< [26..26] TIM3_CLOCK enable                                       */
      __IM  uint32_t                    : 5;
} MDR_RST_TIM_Bits;

#define MDR_RST_TIM__TIM1_BRG_Pos    (0UL)               /*!< MDR_RST_CLOCK TIM_CLOCK: TIM1_BRG (Bit 0)                       */
#define MDR_RST_TIM__TIM1_BRG_Msk    (0x7UL)             /*!< MDR_RST_CLOCK TIM_CLOCK: TIM1_BRG (Bitfield-Mask: 0x07)         */
#define MDR_RST_TIM__TIM2_BRG_Pos    (8UL)               /*!< MDR_RST_CLOCK TIM_CLOCK: TIM2_BRG (Bit 8)                       */
#define MDR_RST_TIM__TIM2_BRG_Msk    (0x700UL)           /*!< MDR_RST_CLOCK TIM_CLOCK: TIM2_BRG (Bitfield-Mask: 0x07)         */
#define MDR_RST_TIM__TIM3_BRG_Pos    (16UL)              /*!< MDR_RST_CLOCK TIM_CLOCK: TIM3_BRG (Bit 16)                      */
#define MDR_RST_TIM__TIM3_BRG_Msk    (0x70000UL)         /*!< MDR_RST_CLOCK TIM_CLOCK: TIM3_BRG (Bitfield-Mask: 0x07)         */
#define MDR_RST_TIM__TIM1_CLK_EN_Pos (24UL)              /*!< MDR_RST_CLOCK TIM_CLOCK: TIM1_CLK_EN (Bit 24)                   */
#define MDR_RST_TIM__TIM1_CLK_EN_Msk (0x1000000UL)       /*!< MDR_RST_CLOCK TIM_CLOCK: TIM1_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_TIM__TIM2_CLK_EN_Pos (25UL)              /*!< MDR_RST_CLOCK TIM_CLOCK: TIM2_CLK_EN (Bit 25)                   */
#define MDR_RST_TIM__TIM2_CLK_EN_Msk (0x2000000UL)       /*!< MDR_RST_CLOCK TIM_CLOCK: TIM2_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_TIM__TIM3_CLK_EN_Pos (26UL)              /*!< MDR_RST_CLOCK TIM_CLOCK: TIM3_CLK_EN (Bit 26)                   */
#define MDR_RST_TIM__TIM3_CLK_EN_Msk (0x4000000UL)       /*!< MDR_RST_CLOCK TIM_CLOCK: TIM3_CLK_EN (Bitfield-Mask: 0x01)      */


/* ======================================================  UART_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_Div128P   UART1_BRG    : 3;        /*!< [2..0] HCLK freq divider to get UART1_CLOCK, [/1, /2, /4 .. /128]  */
      __IM  uint32_t                       : 5;
      __IOM MDR_Div128P   UART2_BRG    : 3;        /*!< [10..8] HCLK freq divider to get UART2_CLOCK, [/1, /2, /4 .. /128] */
      __IM  uint32_t                       : 5;
      __IOM MDR_Div128P   TIM4_BRG     : 3;        /*!< [18..16] HCLK freq divider to get TIM4_CLOCK, [/1, /2, /4 .. /128] */
      __IM  uint32_t                       : 5;
      __IOM MDR_OnOff         UART1_CLK_EN : 1;        /*!< [24..24] UART1_CLOCK enable                                        */
      __IOM MDR_OnOff         UART2_CLK_EN : 1;        /*!< [25..25] UART2_CLOCK enable                                        */
      __IOM MDR_OnOff          TIM4_CLK_EN : 1;        /*!< [26..26] TIM4_CLOCK enable                                         */
      __IM uint32_t                        : 5;
} MDR_RST_UART_Bits;

#define MDR_RST_UART__UART1_BRG_Pos    (0UL)             /*!< MDR_RST_CLOCK UART_CLOCK: UART1_BRG (Bit 0)                       */
#define MDR_RST_UART__UART1_BRG_Msk    (0x7UL)           /*!< MDR_RST_CLOCK UART_CLOCK: UART1_BRG (Bitfield-Mask: 0x07)         */
#define MDR_RST_UART__UART2_BRG_Pos    (8UL)             /*!< MDR_RST_CLOCK UART_CLOCK: UART2_BRG (Bit 8)                       */
#define MDR_RST_UART__UART2_BRG_Msk    (0x700UL)         /*!< MDR_RST_CLOCK UART_CLOCK: UART2_BRG (Bitfield-Mask: 0x07)         */
#define MDR_RST_UART__TIM4_BRG_Pos     (16UL)            /*!< MDR_RST_CLOCK UART_CLOCK: TIM4_BRG (Bit 16)                       */
#define MDR_RST_UART__TIM4_BRG_Msk     (0x70000UL)       /*!< MDR_RST_CLOCK UART_CLOCK: TIM4_BRG (Bitfield-Mask: 0x07)          */
#define MDR_RST_UART__UART1_CLK_EN_Pos (24UL)            /*!< MDR_RST_CLOCK UART_CLOCK: UART1_CLK_EN (Bit 24)                   */
#define MDR_RST_UART__UART1_CLK_EN_Msk (0x1000000UL)     /*!< MDR_RST_CLOCK UART_CLOCK: UART1_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_UART__UART2_CLK_EN_Pos (25UL)            /*!< MDR_RST_CLOCK UART_CLOCK: UART2_CLK_EN (Bit 25)                   */
#define MDR_RST_UART__UART2_CLK_EN_Msk (0x2000000UL)     /*!< MDR_RST_CLOCK UART_CLOCK: UART2_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_UART__TIM4_CLK_EN_Pos  (26UL)            /*!< MDR_RST_CLOCK UART_CLOCK: TIM4_CLK_EN (Bit 26)                    */
#define MDR_RST_UART__TIM4_CLK_EN_Msk  (0x4000000UL)     /*!< MDR_RST_CLOCK UART_CLOCK: TIM4_CLK_EN (Bitfield-Mask: 0x01)       */

/* =======================================================  SSP_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_Div128P  SSP1_BRG     : 3;          /*!< [2..0] HCLK freq divider to get SSP1_CLOCK, [/1, /2, /4 .. /128]   */
      __IM  uint32_t                      : 5;
      __IOM MDR_Div128P  SSP2_BRG     : 3;          /*!< [10..8] HCLK freq divider to get SSP2_CLOCK, [/1, /2, /4 .. /128]  */
      __IM  uint32_t                      : 5;
      __IOM MDR_Div128P  SSP3_BRG     : 3;          /*!< [18..16] HCLK freq divider to get SSP3_CLOCK, [/1, /2, /4 .. /128] */
      __IM  uint32_t                      : 5;
      __IOM MDR_OnOff     SSP1_CLK_EN     : 1;         /*!< [24..24] SSP1_CLOCK Enable                                          */
      __IOM MDR_OnOff     SSP2_CLK_EN     : 1;         /*!< [25..25] SSP2_CLOCK Enable                                          */
      __IOM MDR_OnOff     SSP3_CLK_EN     : 1;         /*!< [26..26] SSP3_CLOCK Enable                                          */
      __IM  uint32_t                      : 5;
} MDR_RST_SSP_Bits;

#define MDR_RST_SSP__SSP1_BRG_Pos    (0UL)               /*!< MDR_RST_CLOCK SSP_CLOCK: SSP1_BRG (Bit 0)                         */
#define MDR_RST_SSP__SSP1_BRG_Msk    (0x7UL)             /*!< MDR_RST_CLOCK SSP_CLOCK: SSP1_BRG (Bitfield-Mask: 0x07)           */
#define MDR_RST_SSP__SSP2_BRG_Pos    (8UL)               /*!< MDR_RST_CLOCK SSP_CLOCK: SSP2_BRG (Bit 8)                         */
#define MDR_RST_SSP__SSP2_BRG_Msk    (0x700UL)           /*!< MDR_RST_CLOCK SSP_CLOCK: SSP2_BRG (Bitfield-Mask: 0x07)           */
#define MDR_RST_SSP__SSP3_BRG_Pos    (16UL)              /*!< MDR_RST_CLOCK SSP_CLOCK: SSP3_BRG (Bit 16)                        */
#define MDR_RST_SSP__SSP3_BRG_Msk    (0x70000UL)         /*!< MDR_RST_CLOCK SSP_CLOCK: SSP3_BRG (Bitfield-Mask: 0x07)           */
#define MDR_RST_SSP__SSP1_CLK_EN_Pos (24UL)              /*!< MDR_RST_CLOCK SSP_CLOCK: SSP1_CLK_EN (Bit 24)                     */
#define MDR_RST_SSP__SSP1_CLK_EN_Msk (0x1000000UL)       /*!< MDR_RST_CLOCK SSP_CLOCK: SSP1_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_SSP__SSP2_CLK_EN_Pos (25UL)              /*!< MDR_RST_CLOCK SSP_CLOCK: SSP2_CLK_EN (Bit 25)                     */
#define MDR_RST_SSP__SSP2_CLK_EN_Msk (0x2000000UL)       /*!< MDR_RST_CLOCK SSP_CLOCK: SSP2_CLK_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_SSP__SSP3_CLK_EN_Pos (26UL)              /*!< MDR_RST_CLOCK SSP_CLOCK: SSP3_CLK_EN (Bit 26)                     */
#define MDR_RST_SSP__SSP3_CLK_EN_Msk (0x4000000UL)       /*!< MDR_RST_CLOCK SSP_CLOCK: SSP3_CLK_EN (Bitfield-Mask: 0x01)        */


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

#endif  //_MDR_RST_VE1X_DEFS_H
