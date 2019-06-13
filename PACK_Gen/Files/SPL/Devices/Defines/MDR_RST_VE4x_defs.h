#ifndef _MDR_RST_VE4X_DEFS_H
#define _MDR_RST_VE4X_DEFS_H

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
      __IM  uint32_t               : 1;
      __IM  MDR_OnOff  PLL_CPU_RDY : 1;           /*!< [1..1] PLL CPU ready                                                    */
      __IM  MDR_OnOff  HSE_RDY     : 1;           /*!< [2..2] HSE generator ready                                              */
      __IM  uint32_t               : 29;          /*!< [31..3] UNUSED                                                          */
} MDR_RST_STATUS_Bits;

#define MDR_RST_STATUS__PLL_CPU_RDY_Pos (1UL)            /*!< MDR_RST_CLOCK CLOCK_STATUS: PLL_CPU_RDY (Bit 1)                  */
#define MDR_RST_STATUS__PLL_CPU_RDY_Msk (0x2UL)          /*!< MDR_RST_CLOCK CLOCK_STATUS: PLL_CPU_RDY (Bitfield-Mask: 0x01)    */
#define MDR_RST_STATUS__HSE_RDY_Pos     (2UL)            /*!< MDR_RST_CLOCK CLOCK_STATUS: HSE_RDY (Bit 2)                      */
#define MDR_RST_STATUS__HSE_RDY_Msk     (0x4UL)          /*!< MDR_RST_CLOCK CLOCK_STATUS: HSE_RDY (Bitfield-Mask: 0x01)        */

/* ======================================================  PLL_CONTROL  ====================================================== */
typedef struct {
      __IM  uint32_t                : 2;
      __IOM MDR_OnOff   PLL_CPU_ON  : 1;           /*!< [2..2] PLL Enable                                                      */
      __IOM MDR_OnOff   PLL_CPU_PLD : 1;           /*!< [3..3] PLL Restart                                                     */
      __IM  uint32_t                : 4;
      __IOM MDR_MUL_x16 PLL_CPU_MUL : 4;           /*!< [11..8] PLL Mul, [x2 .. x16]                                           */
      __IM  uint32_t                : 20;
} MDR_RST_PLL_Bits;

#define MDR_RST_PLL__CPU_ON_Pos  (2UL)             /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_CPU_ON (Bit 2)                          */
#define MDR_RST_PLL__CPU_ON_Msk  (0x4UL)           /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_CPU_ON (Bitfield-Mask: 0x01)            */
#define MDR_RST_PLL__CPU_RLD_Pos (3UL)             /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_CPU_PLD (Bit 3)                         */
#define MDR_RST_PLL__CPU_RLD_Msk (0x8UL)           /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_CPU_PLD (Bitfield-Mask: 0x01)           */
#define MDR_RST_PLL__CPU_MUL_Pos (8UL)             /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_CPU_MUL (Bit 8)                         */
#define MDR_RST_PLL__CPU_MUL_Msk (0xf00UL)         /*!< MDR_RST_CLOCK PLL_CONTROL: PLL_CPU_MUL (Bitfield-Mask: 0x0f)           */


/* ======================================================  HS_CONTROL  ======================================================= */

typedef struct {
      __IOM MDR_OnOff  HSE_ON     : 1;            /*!< [0..0] HSE Enable                                                       */  
      __IOM MDR_OnOff  HSE_BYP    : 1;            /*!< [1..1] HSE Bypass Mode                                                  */
      __IM  uint32_t              : 30;
} MDR_RST_HS_Bits;

#define MDR_RST_HS__HSE_ON_Pos   (0UL)                 /*!< MDR_RST_CLOCK HS_CONTROL: HSE_ON (Bit 0)                           */
#define MDR_RST_HS__HSE_ON_Msk   (0x1UL)               /*!< MDR_RST_CLOCK HS_CONTROL: HSE_ON (Bitfield-Mask: 0x01)             */
#define MDR_RST_HS__HSE_BYP_Pos  (1UL)                 /*!< MDR_RST_CLOCK HS_CONTROL: HSE_BYP (Bit 1)                          */
#define MDR_RST_HS__HSE_BYP_Msk  (0x2UL)               /*!< MDR_RST_CLOCK HS_CONTROL: HSE_BYP (Bitfield-Mask: 0x01)            */

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


/* =======================================================  ADC_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_CLK_SEL_PER  ADC_C1_SEL   : 2;          /*!< [1..0] ADC_C1 mux freq select                                     */
      __IOM MDR_CLK_SEL_PER  ADCUI_C1_SEL : 2;          /*!< [3..2] ADCUI_C1 mux freq select                                   */
      __IOM MDR_Div256P      ADCUI_C3_SEL : 4;          /*!< [7..4] ADCUI_C1 mux output freq devider, [/1, /2, /4 .. /256]     */
      __IOM MDR_Div256P      ADC_C3_SEL   : 4;          /*!< [11..8] ADC_C1 mux output freq devider, [/1, /2, /4 .. /256]      */
      __IOM MDR_OnOff        ADCUI_CLK_EN : 1;          /*!< [12..12] ADCUI Clock Enable                                       */
      __IOM MDR_OnOff        ADC_CLK_EN   : 1;          /*!< [13..13] ADC Clock Enable                                         */
      __IM  uint32_t                      : 18;
} MDR_RST_ADC_Bits;

#define MDR_RST_ADC__ADC_C1_SEL_Pos   (0UL)              /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C1_SEL (Bit 0)                      */
#define MDR_RST_ADC__ADC_C1_SEL_Msk   (0x3UL)            /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C1_SEL (Bitfield-Mask: 0x03)        */
#define MDR_RST_ADC__ADCUI_C1_SEL_Pos (2UL)              /*!< MDR_RST_CLOCK ADC_CLOCK: ADCUI_C1_SEL (Bit 2)                    */
#define MDR_RST_ADC__ADCUI_C1_SEL_Msk (0xcUL)            /*!< MDR_RST_CLOCK ADC_CLOCK: ADCUI_C1_SEL (Bitfield-Mask: 0x03)      */
#define MDR_RST_ADC__ADCUI_C3_SEL_Pos (4UL)              /*!< MDR_RST_CLOCK ADC_CLOCK: ADCUI_C3_SEL (Bit 4)                    */
#define MDR_RST_ADC__ADCUI_C3_SEL_Msk (0xf0UL)           /*!< MDR_RST_CLOCK ADC_CLOCK: ADCUI_C3_SEL (Bitfield-Mask: 0x0f)      */
#define MDR_RST_ADC__ADC_C3_SEL_Pos   (8UL)              /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C3_SEL (Bit 8)                      */
#define MDR_RST_ADC__ADC_C3_SEL_Msk   (0xf00UL)          /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_C3_SEL (Bitfield-Mask: 0x0f)        */
#define MDR_RST_ADC__ADCUI_CLK_EN_Pos (12UL)             /*!< MDR_RST_CLOCK ADC_CLOCK: ADCUI_CLK_EN (Bit 12)                   */
#define MDR_RST_ADC__ADCUI_CLK_EN_Msk (0x1000UL)         /*!< MDR_RST_CLOCK ADC_CLOCK: ADCUI_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_ADC__ADC_CLK_EN_Pos   (13UL)             /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_CLK_EN (Bit 13)                     */
#define MDR_RST_ADC__ADC_CLK_EN_Msk   (0x2000UL)         /*!< MDR_RST_CLOCK ADC_CLOCK: ADC_CLK_EN (Bitfield-Mask: 0x01)        */

/* =======================================================  RTC_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_Div256P  HSE_SEL    : 4;            /*!< [3..0] RTC HSE freq devider, [/1, /2, /4 .. /256]                 */
      __IOM MDR_Div256P  HSI_SEL    : 4;            /*!< [7..4] RTC HSI freq devider, [/1, /2, /4 .. /256]                 */
      __IOM MDR_OnOff        HSE_RTC_EN : 1;            /*!< [8..8] RTC HSE Clock enable                                       */
      __IOM MDR_OnOff        HSI_RTC_EN : 1;            /*!< [9..9] RTC HSI Clock enable                                       */
      __IM  uint32_t                    : 22;
} MDR_RST_RTC_Bits;

#define MDR_RST_RTC__HSE_SEL_Pos    (0UL)                /*!< MDR_RST_CLOCK RTC_CLOCK: HSE_SEL (Bit 0)                         */
#define MDR_RST_RTC__HSE_SEL_Msk    (0xfUL)              /*!< MDR_RST_CLOCK RTC_CLOCK: HSE_SEL (Bitfield-Mask: 0x0f)           */
#define MDR_RST_RTC__HSI_SEL_Pos    (4UL)                /*!< MDR_RST_CLOCK RTC_CLOCK: HSI_SEL (Bit 4)                         */
#define MDR_RST_RTC__HSI_SEL_Msk    (0xf0UL)             /*!< MDR_RST_CLOCK RTC_CLOCK: HSI_SEL (Bitfield-Mask: 0x0f)           */
#define MDR_RST_RTC__HSE_RTC_EN_Pos (8UL)                /*!< MDR_RST_CLOCK RTC_CLOCK: HSE_RTC_EN (Bit 8)                      */
#define MDR_RST_RTC__HSE_RTC_EN_Msk (0x100UL)            /*!< MDR_RST_CLOCK RTC_CLOCK: HSE_RTC_EN (Bitfield-Mask: 0x01)        */
#define MDR_RST_RTC__HSI_RTC_EN_Pos (9UL)                /*!< MDR_RST_CLOCK RTC_CLOCK: HSI_RTC_EN (Bit 9)                      */
#define MDR_RST_RTC__HSI_RTC_EN_Msk (0x200UL)            /*!< MDR_RST_CLOCK RTC_CLOCK: HSI_RTC_EN (Bitfield-Mask: 0x01)        */


/* =======================================================  TIM_CLOCK  =======================================================    */
typedef struct {
      __IOM MDR_Div128P  TIM1_BRG    : 3;           /*!< [2..0] PER1_C2 freq divider to get TIM1_CLOCK, [/1, /2, /4 ../128]   */
      __IM  uint32_t                     : 5;
      __IOM MDR_Div128P  TIM2_BRG    : 3;           /*!< [10..8] PER1_C2 freq divider to get TIM2_CLOCK, [/1, /2, /4.. /128]  */
      __IM  uint32_t                     : 13;
      __IOM MDR_OnOff        TIM1_CLK_EN : 1;           /*!< [24..24] TIM1_CLOCK enable                                           */
      __IOM MDR_OnOff        TIM2_CLK_EN : 1;           /*!< [25..25] TIM2_CLOCK enable                                           */
      __IM  uint32_t                     : 6;
} MDR_RST_TIM_Bits;

#define MDR_RST_TIM__TIM1_BRG_Pos    (0UL)               /*!< MDR_RST_CLOCK TIM_CLOCK: TIM1_BRG (Bit 0)                       */
#define MDR_RST_TIM__TIM1_BRG_Msk    (0x7UL)             /*!< MDR_RST_CLOCK TIM_CLOCK: TIM1_BRG (Bitfield-Mask: 0x07)         */
#define MDR_RST_TIM__TIM2_BRG_Pos    (8UL)               /*!< MDR_RST_CLOCK TIM_CLOCK: TIM2_BRG (Bit 8)                       */
#define MDR_RST_TIM__TIM2_BRG_Msk    (0x700UL)           /*!< MDR_RST_CLOCK TIM_CLOCK: TIM2_BRG (Bitfield-Mask: 0x07)         */
#define MDR_RST_TIM__TIM1_CLK_EN_Pos (24UL)              /*!< MDR_RST_CLOCK TIM_CLOCK: TIM1_CLK_EN (Bit 24)                   */
#define MDR_RST_TIM__TIM1_CLK_EN_Msk (0x1000000UL)       /*!< MDR_RST_CLOCK TIM_CLOCK: TIM1_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_TIM__TIM2_CLK_EN_Pos (25UL)              /*!< MDR_RST_CLOCK TIM_CLOCK: TIM2_CLK_EN (Bit 25)                   */
#define MDR_RST_TIM__TIM2_CLK_EN_Msk (0x2000000UL)       /*!< MDR_RST_CLOCK TIM_CLOCK: TIM2_CLK_EN (Bitfield-Mask: 0x01)      */


/* ======================================================  UART_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_Div128P  UART1_BRG    : 3;          /*!< [2..0] PER1_C2 freq divider to get UART1_CLOCK, [/1, /2, /4 .. /128]   */
      __IM  uint32_t                      : 5;
      __IOM MDR_Div128P  UART2_BRG    : 3;          /*!< [10..8] PER1_C2 freq divider to get UART2_CLOCK, [/1, /2, /4 .. /128]  */
      __IM  uint32_t                      : 13;
      __IOM MDR_OnOff        UART1_CLK_EN : 1;          /*!< [24..24] UART1_CLOCK enable                                            */
      __IOM MDR_OnOff        UART2_CLK_EN : 1;          /*!< [25..25] UART2_CLOCK enable                                            */
      __IOM uint32_t                      : 6;
} MDR_RST_UART_Bits;

#define MDR_RST_UART__UART1_BRG_Pos    (0UL)             /*!< MDR_RST_CLOCK UART_CLOCK: UART1_BRG (Bit 0)                       */
#define MDR_RST_UART__UART1_BRG_Msk    (0x7UL)           /*!< MDR_RST_CLOCK UART_CLOCK: UART1_BRG (Bitfield-Mask: 0x07)         */
#define MDR_RST_UART__UART2_BRG_Pos    (8UL)             /*!< MDR_RST_CLOCK UART_CLOCK: UART2_BRG (Bit 8)                       */
#define MDR_RST_UART__UART2_BRG_Msk    (0x700UL)         /*!< MDR_RST_CLOCK UART_CLOCK: UART2_BRG (Bitfield-Mask: 0x07)         */
#define MDR_RST_UART__UART1_CLK_EN_Pos (24UL)            /*!< MDR_RST_CLOCK UART_CLOCK: UART1_CLK_EN (Bit 24)                   */
#define MDR_RST_UART__UART1_CLK_EN_Msk (0x1000000UL)     /*!< MDR_RST_CLOCK UART_CLOCK: UART1_CLK_EN (Bitfield-Mask: 0x01)      */
#define MDR_RST_UART__UART2_CLK_EN_Pos (25UL)            /*!< MDR_RST_CLOCK UART_CLOCK: UART2_CLK_EN (Bit 25)                   */
#define MDR_RST_UART__UART2_CLK_EN_Msk (0x2000000UL)     /*!< MDR_RST_CLOCK UART_CLOCK: UART2_CLK_EN (Bitfield-Mask: 0x01)      */


/* =======================================================  SSP_CLOCK  ======================================================= */
typedef struct {
      __IOM MDR_Div128P   SSP1_BRG    : 3;           /*!< [3..0] PER1_C2 freq divider to get SSP1_CLOCK, [/1, /2, /4 .. /128]  */
      __IM  uint32_t                      : 21;
      __IOM MDR_OnOff         SSP1_CLK_EN : 1;           /*!< [24..24] SSP1_CLOCK Enable                                           */
      __IM  uint32_t                      : 7;
} MDR_RST_SSP_Bits;

#define MDR_RST_SSP__SSP1_BRG_Pos    (0UL)               /*!< MDR_RST_CLOCK SSP_CLOCK: SSP1_BRG (Bit 0)                         */
#define MDR_RST_SSP__SSP1_BRG_Msk    (0x7UL)             /*!< MDR_RST_CLOCK SSP_CLOCK: SSP1_BRG (Bitfield-Mask: 0x07)           */
#define MDR_RST_SSP__SSP1_CLK_EN_Pos (24UL)              /*!< MDR_RST_CLOCK SSP_CLOCK: SSP1_CLK_EN (Bit 24)                     */
#define MDR_RST_SSP__SSP1_CLK_EN_Msk (0x1000000UL)       /*!< MDR_RST_CLOCK SSP_CLOCK: SSP1_CLK_EN (Bitfield-Mask: 0x01)        */



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

#endif  //_MDR_RST_VE4X_DEFS_H
