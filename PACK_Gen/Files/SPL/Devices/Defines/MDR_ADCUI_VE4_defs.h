#ifndef _MDR_ADCUI_VE4_DEFS_H
#define _MDR_ADCUI_VE4_DEFS_H

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

/* =========================================================  CTRL1  ========================================================= */
typedef struct {
  __IOM MDR_OnOff ADC1_EN    : 1;            /*!< [0..0] Channel enable                                                     */
  __IOM MDR_OnOff ADC2_EN    : 1;            /*!< [1..1] Channel enable                                                     */
  __IOM MDR_OnOff ADC3_EN    : 1;            /*!< [2..2] Channel enable                                                     */
  __IOM MDR_OnOff ADC4_EN    : 1;            /*!< [3..3] Channel enable                                                     */
  __IOM MDR_OnOff ADC5_EN    : 1;            /*!< [4..4] Channel enable                                                     */
  __IOM MDR_OnOff ADC6_EN    : 1;            /*!< [5..5] Channel enable                                                     */
  __IOM MDR_OnOff ADC7_EN    : 1;            /*!< [6..6] Channel enable                                                     */
  __IOM MDR_OnOff ADC8_EN    : 1;            /*!< [7..7] Channel enable                                                     */
  __IOM MDR_OnOff REF_EX     : 1;            /*!< [8..8] Select VRef                                                        */
  __IOM MDR_OnOff CHP1_EN    : 1;            /*!< [9..9] Exclude constant component                                         */
  __IOM MDR_OnOff CHP2_EN    : 1;            /*!< [10..10] Exclude constant component                                       */
  __IOM MDR_OnOff CHP3_EN    : 1;            /*!< [11..11] Exclude constant component                                       */
  __IOM MDR_OnOff CHP4_EN    : 1;            /*!< [12..12] Exclude constant component                                       */
  __IOM MDR_OnOff CHP5_EN    : 1;            /*!< [13..13] Exclude constant component                                       */
  __IOM MDR_OnOff CHP6_EN    : 1;            /*!< [14..14] Exclude constant component                                       */
  __IOM MDR_OnOff CHP7_EN    : 1;            /*!< [15..15] Exclude constant component                                       */
  __IOM MDR_OnOff CHP8_EN    : 1;            /*!< [16..16] Exclude constant component                                       */
  __IM  uint32_t             : 15;
} MDR_ADCUI_CTRL1_Bits;

#define MDR_ADCUI_CTRL1_ADC1_EN_Pos       (0UL)                     /*!< MDR_ADCUI CTRL1: ADC1_EN (Bit 0)                      */
#define MDR_ADCUI_CTRL1_ADC1_EN_Msk       (0x1UL)                   /*!< MDR_ADCUI CTRL1: ADC1_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_ADC2_EN_Pos       (1UL)                     /*!< MDR_ADCUI CTRL1: ADC2_EN (Bit 1)                      */
#define MDR_ADCUI_CTRL1_ADC2_EN_Msk       (0x2UL)                   /*!< MDR_ADCUI CTRL1: ADC2_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_ADC3_EN_Pos       (2UL)                     /*!< MDR_ADCUI CTRL1: ADC3_EN (Bit 2)                      */
#define MDR_ADCUI_CTRL1_ADC3_EN_Msk       (0x4UL)                   /*!< MDR_ADCUI CTRL1: ADC3_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_ADC4_EN_Pos       (3UL)                     /*!< MDR_ADCUI CTRL1: ADC4_EN (Bit 3)                      */
#define MDR_ADCUI_CTRL1_ADC4_EN_Msk       (0x8UL)                   /*!< MDR_ADCUI CTRL1: ADC4_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_ADC5_EN_Pos       (4UL)                     /*!< MDR_ADCUI CTRL1: ADC5_EN (Bit 4)                      */
#define MDR_ADCUI_CTRL1_ADC5_EN_Msk       (0x10UL)                  /*!< MDR_ADCUI CTRL1: ADC5_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_ADC6_EN_Pos       (5UL)                     /*!< MDR_ADCUI CTRL1: ADC6_EN (Bit 5)                      */
#define MDR_ADCUI_CTRL1_ADC6_EN_Msk       (0x20UL)                  /*!< MDR_ADCUI CTRL1: ADC6_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_ADC7_EN_Pos       (6UL)                     /*!< MDR_ADCUI CTRL1: ADC7_EN (Bit 6)                      */
#define MDR_ADCUI_CTRL1_ADC7_EN_Msk       (0x40UL)                  /*!< MDR_ADCUI CTRL1: ADC7_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_ADC8_EN_Pos       (7UL)                     /*!< MDR_ADCUI CTRL1: ADC8_EN (Bit 7)                      */
#define MDR_ADCUI_CTRL1_ADC8_EN_Msk       (0x80UL)                  /*!< MDR_ADCUI CTRL1: ADC8_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_REF_EX_Pos        (8UL)                     /*!< MDR_ADCUI CTRL1: REF_EX (Bit 8)                       */
#define MDR_ADCUI_CTRL1_REF_EX_Msk        (0x100UL)                 /*!< MDR_ADCUI CTRL1: REF_EX (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_CTRL1_CHP1_EN_Pos       (9UL)                     /*!< MDR_ADCUI CTRL1: CHP1_EN (Bit 9)                      */
#define MDR_ADCUI_CTRL1_CHP1_EN_Msk       (0x200UL)                 /*!< MDR_ADCUI CTRL1: CHP1_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_CHP2_EN_Pos       (10UL)                    /*!< MDR_ADCUI CTRL1: CHP2_EN (Bit 10)                     */
#define MDR_ADCUI_CTRL1_CHP2_EN_Msk       (0x400UL)                 /*!< MDR_ADCUI CTRL1: CHP2_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_CHP3_EN_Pos       (11UL)                    /*!< MDR_ADCUI CTRL1: CHP3_EN (Bit 11)                     */
#define MDR_ADCUI_CTRL1_CHP3_EN_Msk       (0x800UL)                 /*!< MDR_ADCUI CTRL1: CHP3_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_CHP4_EN_Pos       (12UL)                    /*!< MDR_ADCUI CTRL1: CHP4_EN (Bit 12)                     */
#define MDR_ADCUI_CTRL1_CHP4_EN_Msk       (0x1000UL)                /*!< MDR_ADCUI CTRL1: CHP4_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_CHP5_EN_Pos       (13UL)                    /*!< MDR_ADCUI CTRL1: CHP5_EN (Bit 13)                     */
#define MDR_ADCUI_CTRL1_CHP5_EN_Msk       (0x2000UL)                /*!< MDR_ADCUI CTRL1: CHP5_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_CHP6_EN_Pos       (14UL)                    /*!< MDR_ADCUI CTRL1: CHP6_EN (Bit 14)                     */
#define MDR_ADCUI_CTRL1_CHP6_EN_Msk       (0x4000UL)                /*!< MDR_ADCUI CTRL1: CHP6_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_CHP7_EN_Pos       (15UL)                    /*!< MDR_ADCUI CTRL1: CHP7_EN (Bit 15)                     */
#define MDR_ADCUI_CTRL1_CHP7_EN_Msk       (0x8000UL)                /*!< MDR_ADCUI CTRL1: CHP7_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_CHP8_EN_Pos       (16UL)                    /*!< MDR_ADCUI CTRL1: CHP8_EN (Bit 16)                     */
#define MDR_ADCUI_CTRL1_CHP8_EN_Msk       (0x10000UL)               /*!< MDR_ADCUI CTRL1: CHP8_EN (Bitfield-Mask: 0x01)        */

#define MDR_ADCUI_CTRL1_ADC_EN_ALL    0xFFUL

/* ========================================================  ANGAIN  ========================================================= */
typedef enum {                      /*!< MDR_ADCUI_ANGAIN_ADC1_PGA                                                 */
  MDR_ADCUI_PGA_x1         = 0,     /*!< x1 : Gain 0dB                                                             */
  MDR_ADCUI_PGA_x4         = 1,     /*!< x4 : Gain 12dB                                                            */
  MDR_ADCUI_PGA_x2         = 2,     /*!< x2 : Gain 6dB                                                             */  
  MDR_ADCUI_PGA_x16        = 3,     /*!< x16 : Gain 24dB                                                           */
} MDR_ADCUI_PGA;

typedef __PACKED_STRUCT {
  __IOM MDR_ADCUI_PGA   ADC1_PGA   : 2;            /*!< [1..0] Gain Select                                                        */
  __IOM MDR_ADCUI_PGA   ADC2_PGA   : 2;            /*!< [3..2] Gain Select                                                        */
  __IOM MDR_ADCUI_PGA   ADC3_PGA   : 2;            /*!< [5..4] Gain Select                                                        */
  __IOM MDR_ADCUI_PGA   ADC4_PGA   : 2;            /*!< [7..6] Gain Select                                                        */
  __IOM MDR_ADCUI_PGA   ADC5_PGA   : 2;            /*!< [9..8] Gain Select                                                        */
  __IOM MDR_ADCUI_PGA   ADC6_PGA   : 2;            /*!< [11..10] Gain Select                                                      */
  __IOM MDR_ADCUI_PGA   ADC7_PGA   : 2;            /*!< [13..12] Gain Select                                                      */
  __IOM MDR_ADCUI_PGA   ADC8_PGA   : 2;            /*!< [16..14] Gain Select                                                      */
  __IM  uint32_t                   : 16;
} MDR_ADCUI_ANGAIN_Bits;

#define MDR_ADCUI_ANGAIN_ADC1_PGA_Pos     (0UL)                     /*!< MDR_ADCUI ANGAIN: ADC1_PGA (Bit 0)                    */
#define MDR_ADCUI_ANGAIN_ADC1_PGA_Msk     (0x3UL)                   /*!< MDR_ADCUI ANGAIN: ADC1_PGA (Bitfield-Mask: 0x03)      */
#define MDR_ADCUI_ANGAIN_ADC2_PGA_Pos     (2UL)                     /*!< MDR_ADCUI ANGAIN: ADC2_PGA (Bit 2)                    */
#define MDR_ADCUI_ANGAIN_ADC2_PGA_Msk     (0xcUL)                   /*!< MDR_ADCUI ANGAIN: ADC2_PGA (Bitfield-Mask: 0x03)      */
#define MDR_ADCUI_ANGAIN_ADC3_PGA_Pos     (4UL)                     /*!< MDR_ADCUI ANGAIN: ADC3_PGA (Bit 4)                    */
#define MDR_ADCUI_ANGAIN_ADC3_PGA_Msk     (0x30UL)                  /*!< MDR_ADCUI ANGAIN: ADC3_PGA (Bitfield-Mask: 0x03)      */
#define MDR_ADCUI_ANGAIN_ADC4_PGA_Pos     (6UL)                     /*!< MDR_ADCUI ANGAIN: ADC4_PGA (Bit 6)                    */
#define MDR_ADCUI_ANGAIN_ADC4_PGA_Msk     (0xc0UL)                  /*!< MDR_ADCUI ANGAIN: ADC4_PGA (Bitfield-Mask: 0x03)      */
#define MDR_ADCUI_ANGAIN_ADC5_PGA_Pos     (8UL)                     /*!< MDR_ADCUI ANGAIN: ADC5_PGA (Bit 8)                    */
#define MDR_ADCUI_ANGAIN_ADC5_PGA_Msk     (0x300UL)                 /*!< MDR_ADCUI ANGAIN: ADC5_PGA (Bitfield-Mask: 0x03)      */
#define MDR_ADCUI_ANGAIN_ADC6_PGA_Pos     (10UL)                    /*!< MDR_ADCUI ANGAIN: ADC6_PGA (Bit 10)                   */
#define MDR_ADCUI_ANGAIN_ADC6_PGA_Msk     (0xc00UL)                 /*!< MDR_ADCUI ANGAIN: ADC6_PGA (Bitfield-Mask: 0x03)      */
#define MDR_ADCUI_ANGAIN_ADC7_PGA_Pos     (12UL)                    /*!< MDR_ADCUI ANGAIN: ADC7_PGA (Bit 12)                   */
#define MDR_ADCUI_ANGAIN_ADC7_PGA_Msk     (0x3000UL)                /*!< MDR_ADCUI ANGAIN: ADC7_PGA (Bitfield-Mask: 0x03)      */
#define MDR_ADCUI_ANGAIN_ADC8_PGA_Pos     (14UL)                    /*!< MDR_ADCUI ANGAIN: ADC8_PGA (Bit 14)                   */
#define MDR_ADCUI_ANGAIN_ADC8_PGA_Msk     (0x1c000UL)               /*!< MDR_ADCUI ANGAIN: ADC8_PGA (Bitfield-Mask: 0x07)      */

#define MDR_ADCUI_ANGAIN_CH_OFFS(ch)     (ch << 1)
#define MDR_ADCUI_ANGAIN_CH_CLR(ch)      (MDR_ADCUI_ANGAIN_ADC1_PGA_Msk << MDR_ADCUI_ANGAIN_CH_OFFS(ch))


/* ========================================================  DIGGAIN  ========================================================= */
//  Всегда устанавливать это значение
#define MDR_ADCUI_DIGGAIN_CONST_ONLY           0x2AAUL

/* =========================================================  DMAEN  ========================================================= */
typedef struct {
  __IOM MDR_OnOff DMA1_EN    : 1;            /*!< [0..0] DMA Request Enable                                                 */
  __IOM MDR_OnOff DMA2_EN    : 1;            /*!< [1..1] DMA Request Enable                                                 */
  __IOM MDR_OnOff DMA3_EN    : 1;            /*!< [2..2] DMA Request Enable                                                 */
  __IOM MDR_OnOff DMA4_EN    : 1;            /*!< [3..3] DMA Request Enable                                                 */
  __IOM MDR_OnOff DMA5_EN    : 1;            /*!< [4..4] DMA Request Enable                                                 */
  __IOM MDR_OnOff DMA6_EN    : 1;            /*!< [5..5] DMA Request Enable                                                 */
  __IOM MDR_OnOff DMA7_EN    : 1;            /*!< [6..6] DMA Request Enable                                                 */
  __IOM MDR_OnOff DMA8_EN    : 1;            /*!< [7..7] DMA Request Enable                                                 */
  __IM  uint32_t             : 24;
} MDR_ADCUI_DMAEN_Bits;

#define MDR_ADCUI_DMAEN_DMA1_EN_Pos       (0UL)                     /*!< MDR_ADCUI DMAEN: DMA1_EN (Bit 0)                      */
#define MDR_ADCUI_DMAEN_DMA1_EN_Msk       (0x1UL)                   /*!< MDR_ADCUI DMAEN: DMA1_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_DMAEN_DMA2_EN_Pos       (1UL)                     /*!< MDR_ADCUI DMAEN: DMA2_EN (Bit 1)                      */
#define MDR_ADCUI_DMAEN_DMA2_EN_Msk       (0x2UL)                   /*!< MDR_ADCUI DMAEN: DMA2_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_DMAEN_DMA3_EN_Pos       (2UL)                     /*!< MDR_ADCUI DMAEN: DMA3_EN (Bit 2)                      */
#define MDR_ADCUI_DMAEN_DMA3_EN_Msk       (0x4UL)                   /*!< MDR_ADCUI DMAEN: DMA3_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_DMAEN_DMA4_EN_Pos       (3UL)                     /*!< MDR_ADCUI DMAEN: DMA4_EN (Bit 3)                      */
#define MDR_ADCUI_DMAEN_DMA4_EN_Msk       (0x8UL)                   /*!< MDR_ADCUI DMAEN: DMA4_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_DMAEN_DMA5_EN_Pos       (4UL)                     /*!< MDR_ADCUI DMAEN: DMA5_EN (Bit 4)                      */
#define MDR_ADCUI_DMAEN_DMA5_EN_Msk       (0x10UL)                  /*!< MDR_ADCUI DMAEN: DMA5_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_DMAEN_DMA6_EN_Pos       (5UL)                     /*!< MDR_ADCUI DMAEN: DMA6_EN (Bit 5)                      */
#define MDR_ADCUI_DMAEN_DMA6_EN_Msk       (0x20UL)                  /*!< MDR_ADCUI DMAEN: DMA6_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_DMAEN_DMA7_EN_Pos       (6UL)                     /*!< MDR_ADCUI DMAEN: DMA7_EN (Bit 6)                      */
#define MDR_ADCUI_DMAEN_DMA7_EN_Msk       (0x40UL)                  /*!< MDR_ADCUI DMAEN: DMA7_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_DMAEN_DMA8_EN_Pos       (7UL)                     /*!< MDR_ADCUI DMAEN: DMA8_EN (Bit 7)                      */
#define MDR_ADCUI_DMAEN_DMA8_EN_Msk       (0x80UL)                  /*!< MDR_ADCUI DMAEN: DMA8_EN (Bitfield-Mask: 0x01)        */

/* =========================================================  CTRL2  ========================================================= */

typedef enum {
  MDR_ADCUI_Decim1   = 0,
  MDR_ADCUI_Decim2   = 1,
  MDR_ADCUI_Decim4   = 2,
  MDR_ADCUI_Decim8   = 3,
  MDR_ADCUI_Decim16  = 4,
  MDR_ADCUI_Decim32  = 5,
  MDR_ADCUI_Decim64  = 6,
  MDR_ADCUI_Decim128 = 7,
} MDR_ADCUI_Decim;

typedef struct {
  __IOM uint32_t          SFF        : 7;            /*!< [6..0] Sinc Filter Fine correction                                        */
  __IOM uint32_t          SFC        : 3;            /*!< [9..7] Sinc Filter Rough correction                                       */
  __IOM MDR_OnOff         Reset      : 1;            /*!< [10..10] Digital part reset                                               */
  __IOM MDR_OnOff         BF_bp      : 1;            /*!< [11..11] Avoid Vref buffer                                                */
  __IOM uint32_t          CHOP_Freq  : 2;            /*!< [13..12] Chopper frequency                                                */
  __IM  uint32_t                     : 18;
} MDR_ADCUI_CTRL2_Bits;

#define MDR_ADCUI_CTRL2_SFF_Pos           (0UL)                     /*!< MDR_ADCUI CTRL2: SFF (Bit 0)                          */
#define MDR_ADCUI_CTRL2_SFF_Msk           (0x7fUL)                  /*!< MDR_ADCUI CTRL2: SFF (Bitfield-Mask: 0x7f)            */
#define MDR_ADCUI_CTRL2_SFC_Pos           (7UL)                     /*!< MDR_ADCUI CTRL2: SFC (Bit 7)                          */
#define MDR_ADCUI_CTRL2_SFC_Msk           (0x380UL)                 /*!< MDR_ADCUI CTRL2: SFC (Bitfield-Mask: 0x07)            */
#define MDR_ADCUI_CTRL2_Reset_Pos         (10UL)                    /*!< MDR_ADCUI CTRL2: Reset (Bit 10)                       */
#define MDR_ADCUI_CTRL2_Reset_Msk         (0x400UL)                 /*!< MDR_ADCUI CTRL2: Reset (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_CTRL2_BF_bp_Pos         (11UL)                    /*!< MDR_ADCUI CTRL2: BF_bp (Bit 11)                       */
#define MDR_ADCUI_CTRL2_BF_bp_Msk         (0x800UL)                 /*!< MDR_ADCUI CTRL2: BF_bp (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_CTRL2_CHOP_Freq_Pos     (12UL)                    /*!< MDR_ADCUI CTRL2: CHOP_Freq (Bit 12)                   */
#define MDR_ADCUI_CTRL2_CHOP_Freq_Msk     (0x3000UL)                /*!< MDR_ADCUI CTRL2: CHOP_Freq (Bitfield-Mask: 0x03)      */

//  Только это значение можно задавать в CHOP_Freq!
#define MDR_ADCUI_CTRL2_CHOP_Freq_CONST    MDR_ADCUI_CTRL2_CHOP_Freq_Msk


/* ===================================================  INTEN, STATUS  ======================================================= */
typedef struct {
  __IOM MDR_OnOff   NS1     : 1;            /*!< [0..0] IRQ by ADC ready                                                   */
  __IOM MDR_OnOff   NS2     : 1;            /*!< [1..1] IRQ by ADC ready                                                   */
  __IOM MDR_OnOff   NS3     : 1;            /*!< [2..2] IRQ by ADC ready                                                   */
  __IOM MDR_OnOff   NS4     : 1;            /*!< [3..3] IRQ by ADC ready                                                   */
  __IOM MDR_OnOff   NS5     : 1;            /*!< [4..4] IRQ by ADC ready                                                   */
  __IOM MDR_OnOff   NS6     : 1;            /*!< [5..5] IRQ by ADC ready                                                   */
  __IOM MDR_OnOff   NS7     : 1;            /*!< [6..6] IRQ by ADC ready                                                   */
  __IOM MDR_OnOff   NS8     : 1;            /*!< [7..7] IRQ by ADC ready                                                   */
  __IOM MDR_OnOff   OV1     : 1;            /*!< [8..8] IRQ by Override ready                                              */
  __IOM MDR_OnOff   OV2     : 1;            /*!< [9..9] IRQ by Override ready                                              */
  __IOM MDR_OnOff   OV3     : 1;            /*!< [10..10] IRQ by Override ready                                            */
  __IOM MDR_OnOff   OV4     : 1;            /*!< [11..11] IRQ by Override ready                                            */
  __IOM MDR_OnOff   OV5     : 1;            /*!< [12..12] IRQ by Override ready                                            */
  __IOM MDR_OnOff   OV6     : 1;            /*!< [13..13] IRQ by Override ready                                            */
  __IOM MDR_OnOff   OV7     : 1;            /*!< [14..14] IRQ by Override ready                                            */
  __IOM MDR_OnOff   OV8     : 1;            /*!< [15..15] IRQ by Override ready                                            */
  __IM  uint32_t             : 16;
} MDR_ADCUI_EVENT_Bits;

#define MDR_ADCUI_EVENT_NS1_Pos        (0UL)                     /*!< MDR_ADCUI INTEN: NS1_EN (Bit 0)                       */
#define MDR_ADCUI_EVENT_NS1_Msk        (0x1UL)                   /*!< MDR_ADCUI INTEN: NS1_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_NS2_Pos        (1UL)                     /*!< MDR_ADCUI INTEN: NS2_EN (Bit 1)                       */
#define MDR_ADCUI_EVENT_NS2_Msk        (0x2UL)                   /*!< MDR_ADCUI INTEN: NS2_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_NS3_Pos        (2UL)                     /*!< MDR_ADCUI INTEN: NS3_EN (Bit 2)                       */
#define MDR_ADCUI_EVENT_NS3_Msk        (0x4UL)                   /*!< MDR_ADCUI INTEN: NS3_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_NS4_Pos        (3UL)                     /*!< MDR_ADCUI INTEN: NS4_EN (Bit 3)                       */
#define MDR_ADCUI_EVENT_NS4_Msk        (0x8UL)                   /*!< MDR_ADCUI INTEN: NS4_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_NS5_Pos        (4UL)                     /*!< MDR_ADCUI INTEN: NS5_EN (Bit 4)                       */
#define MDR_ADCUI_EVENT_NS5_Msk        (0x10UL)                  /*!< MDR_ADCUI INTEN: NS5_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_NS6_Pos        (5UL)                     /*!< MDR_ADCUI INTEN: NS6_EN (Bit 5)                       */
#define MDR_ADCUI_EVENT_NS6_Msk        (0x20UL)                  /*!< MDR_ADCUI INTEN: NS6_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_NS7_Pos        (6UL)                     /*!< MDR_ADCUI INTEN: NS7_EN (Bit 6)                       */
#define MDR_ADCUI_EVENT_NS7_Msk        (0x40UL)                  /*!< MDR_ADCUI INTEN: NS7_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_NS8_Pos        (7UL)                     /*!< MDR_ADCUI INTEN: NS8_EN (Bit 7)                       */
#define MDR_ADCUI_EVENT_NS8_Msk        (0x80UL)                  /*!< MDR_ADCUI INTEN: NS8_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_OV1_Pos        (8UL)                     /*!< MDR_ADCUI INTEN: OV1_EN (Bit 8)                       */
#define MDR_ADCUI_EVENT_OV1_Msk        (0x100UL)                 /*!< MDR_ADCUI INTEN: OV1_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_OV2_Pos        (9UL)                     /*!< MDR_ADCUI INTEN: OV2_EN (Bit 9)                       */
#define MDR_ADCUI_EVENT_OV2_Msk        (0x200UL)                 /*!< MDR_ADCUI INTEN: OV2_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_OV3_Pos        (10UL)                    /*!< MDR_ADCUI INTEN: OV3_EN (Bit 10)                      */
#define MDR_ADCUI_EVENT_OV3_Msk        (0x400UL)                 /*!< MDR_ADCUI INTEN: OV3_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_OV4_Pos        (11UL)                    /*!< MDR_ADCUI INTEN: OV4_EN (Bit 11)                      */
#define MDR_ADCUI_EVENT_OV4_Msk        (0x800UL)                 /*!< MDR_ADCUI INTEN: OV4_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_OV5_Pos        (12UL)                    /*!< MDR_ADCUI INTEN: OV5_EN (Bit 12)                      */
#define MDR_ADCUI_EVENT_OV5_Msk        (0x1000UL)                /*!< MDR_ADCUI INTEN: OV5_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_OV6_Pos        (13UL)                    /*!< MDR_ADCUI INTEN: OV6_EN (Bit 13)                      */
#define MDR_ADCUI_EVENT_OV6_Msk        (0x2000UL)                /*!< MDR_ADCUI INTEN: OV6_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_OV7_Pos        (14UL)                    /*!< MDR_ADCUI INTEN: OV7_EN (Bit 14)                      */
#define MDR_ADCUI_EVENT_OV7_Msk        (0x4000UL)                /*!< MDR_ADCUI INTEN: OV7_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_EVENT_OV8_Pos        (15UL)                    /*!< MDR_ADCUI INTEN: OV8_EN (Bit 15)                      */
#define MDR_ADCUI_EVENT_OV8_Msk        (0x8000UL)                /*!< MDR_ADCUI INTEN: OV8_EN (Bitfield-Mask: 0x01)         */


#define MDR_ADCUI_EVENT_CLR_OV1        MDR_ADCUI_EVENT_OV1_Msk
#define MDR_ADCUI_EVENT_CLR_OV2        MDR_ADCUI_EVENT_OV2_Msk
#define MDR_ADCUI_EVENT_CLR_OV3        MDR_ADCUI_EVENT_OV3_Msk
#define MDR_ADCUI_EVENT_CLR_OV4        MDR_ADCUI_EVENT_OV4_Msk
#define MDR_ADCUI_EVENT_CLR_OV5        MDR_ADCUI_EVENT_OV5_Msk
#define MDR_ADCUI_EVENT_CLR_OV6        MDR_ADCUI_EVENT_OV6_Msk
#define MDR_ADCUI_EVENT_CLR_OV7        MDR_ADCUI_EVENT_OV7_Msk
#define MDR_ADCUI_EVENT_CLR_OV8        MDR_ADCUI_EVENT_OV8_Msk

#define MDR_ADCUI_EVENT_CLR_OV_ALL     (0xFFUL << MDR_ADCUI_EVENT_OV1_Pos)        


/* ==========================================================  DAT  ========================================================== */
#define MDR_ADCUI_DAT_Pos      (1UL)
#define MDR_ADCUI_DAT_Msk      (0x00FFFFFFUL)

#define MDR_ADCUI_SIGN_OFFS     8


/* ==========================================================  TST  ========================================================== */
typedef struct {
  __IM  uint32_t            : 1;
  __IOM uint32_t TST2       : 1;            /*!< [1..1] Vref to pin VR_1V                                                  */
  __IM  uint32_t            : 30;
} MDR_ADCUI_TST_Bits;

#define MDR_ADCUI_TST_TST2_Pos            (1UL)                     /*!< MDR_ADCUI TST: TST2 (Bit 1)                           */
#define MDR_ADCUI_TST_TST2_Msk            (0x2UL)                   /*!< MDR_ADCUI TST: TST2 (Bitfield-Mask: 0x01)             */

#define MDR_ADCUI_TST_CONST_ONLY       MDR_ADCUI_TST_TST2_Msk 

/* ===================================================  MDR_ADCUI_Type  ====================================================== */
#define MDR_ADCUI_CHANNEL_COUNT  8

typedef struct {                                /*!< (@ 0x40068000) MDR_ADCUI Structure                                        */
  union {
    __IOM uint32_t              CTRL1;          /*!< (@ 0x00000000) ADCUI Control1 Register                                    */
    __IOM MDR_ADCUI_CTRL1_Bits  CTRL1_b;
  } ;
  union {
    __IOM uint32_t              ANGAIN;         /*!< (@ 0x00000004) Analog Amplifier Control                                   */
    __IOM MDR_ADCUI_ANGAIN_Bits ANGAIN_b;
  } ;
  __IOM   uint32_t              DIGGAIN;        /*!< (@ 0x00000008) Digital Amplifier Control                                  */  
  union {
    __IOM uint32_t              DMAEN;          /*!< (@ 0x0000000C) DMA Request Control                                        */
    __IOM MDR_ADCUI_DMAEN_Bits  DMAEN_b;
  } ; 
  union {
    __IOM uint32_t              CTRL2;          /*!< (@ 0x00000010) ADCUI Control2 Register                                    */
    __IOM MDR_ADCUI_CTRL2_Bits  CTRL2_b;
  } ;
  union {
    __IOM uint32_t              INTEN;          /*!< (@ 0x00000014) Irq Enable Control                                         */
    __IOM MDR_ADCUI_EVENT_Bits  INTEN_b;
  } ;
  union {
    __IOM uint32_t              STAT;           /*!< (@ 0x00000018) Status Register                                            */
    __IOM MDR_ADCUI_EVENT_Bits  STAT_b;    
  } ;
  __IM  uint32_t                DAT[MDR_ADCUI_CHANNEL_COUNT];       /*!< (@ 0x0000001C) ADC FIFO read                      */
  union {
    __IOM uint32_t              TST;            /*!< (@ 0x0000003C) Test register                                              */    
    __IOM MDR_ADCUI_TST_Bits    TST_b;
  } ;
} MDR_ADCUI_Type;                               /*!< Size = 64 (0x40)                                                          */


/* ===================================================  For SPL  ====================================================== */
typedef enum {     
  MDR_ADCUI_CH1    = 0,
  MDR_ADCUI_CH2    = 1,
  MDR_ADCUI_CH3    = 2,
  MDR_ADCUI_CH4    = 3,
  MDR_ADCUI_CH5    = 4,
  MDR_ADCUI_CH6    = 5,
  MDR_ADCUI_CH7    = 6,
  MDR_ADCUI_CH8    = 7,
} MDR_ADCUI_CH;

#define MDR_ADCUI_SEL_CH1     0x01UL
#define MDR_ADCUI_SEL_CH2     0x02UL
#define MDR_ADCUI_SEL_CH3     0x04UL
#define MDR_ADCUI_SEL_CH4     0x08UL
#define MDR_ADCUI_SEL_CH5     0x10UL
#define MDR_ADCUI_SEL_CH6     0x20UL
#define MDR_ADCUI_SEL_CH7     0x40UL
#define MDR_ADCUI_SEL_CH8     0x80UL
#define MDR_ADCUI_SEL_CH_ALL  0xFFUL

typedef struct {
  MDR_OnOff CH1    : 1;
  MDR_OnOff CH2    : 1;
  MDR_OnOff CH3    : 1;
  MDR_OnOff CH4    : 1;
  MDR_OnOff CH5    : 1;
  MDR_OnOff CH6    : 1;
  MDR_OnOff CH7    : 1;
  MDR_OnOff CH8    : 1;
  uint32_t         : 24;
} MDR_ADCUI_SelCH_Bits;

typedef union {
  uint32_t              Value;
  MDR_ADCUI_SelCH_Bits  Flags;
} MDR_ADCUI_SelCH;


typedef struct {
  MDR_ADCUI_PGA   CH1_PGA   : 2;
  MDR_ADCUI_PGA   CH2_PGA   : 2;
  MDR_ADCUI_PGA   CH3_PGA   : 2;
  MDR_ADCUI_PGA   CH4_PGA   : 2;
  MDR_ADCUI_PGA   CH5_PGA   : 2;
  MDR_ADCUI_PGA   CH6_PGA   : 2;
  MDR_ADCUI_PGA   CH7_PGA   : 2;
  MDR_ADCUI_PGA   CH8_PGA   : 2;
  uint32_t                  : 16;
} MDR_ADCUI_GainCH_Bits;

typedef union {
  uint32_t              Value;         /*!< (@ 0x00000004) Analog Amplifier Control                                   */
  MDR_ADCUI_GainCH_Bits Flags;
} MDR_ADCUI_GainCH;

#define MDR_ADCUI_GAIN(g1, g2, g3, g4, g5, g6, g7, g8)  ( ((g1 & MDR_ADCUI_ANGAIN_ADC1_PGA_Msk) << MDR_ADCUI_ANGAIN_ADC1_PGA_Pos) \
                                                    | ((g2 & MDR_ADCUI_ANGAIN_ADC2_PGA_Msk) << MDR_ADCUI_ANGAIN_ADC2_PGA_Pos) \
                                                    | ((g3 & MDR_ADCUI_ANGAIN_ADC3_PGA_Msk) << MDR_ADCUI_ANGAIN_ADC3_PGA_Pos) \
                                                    | ((g4 & MDR_ADCUI_ANGAIN_ADC4_PGA_Msk) << MDR_ADCUI_ANGAIN_ADC4_PGA_Pos) \
                                                    | ((g5 & MDR_ADCUI_ANGAIN_ADC5_PGA_Msk) << MDR_ADCUI_ANGAIN_ADC5_PGA_Pos) \
                                                    | ((g6 & MDR_ADCUI_ANGAIN_ADC6_PGA_Msk) << MDR_ADCUI_ANGAIN_ADC6_PGA_Pos) \
                                                    | ((g7 & MDR_ADCUI_ANGAIN_ADC7_PGA_Msk) << MDR_ADCUI_ANGAIN_ADC7_PGA_Pos) \
                                                    | ((g8 & MDR_ADCUI_ANGAIN_ADC8_PGA_Msk) << MDR_ADCUI_ANGAIN_ADC8_PGA_Pos) )

#define MDR_ADCUI_GAIN_ALL(g)   MDR_ADCUI_GAIN(g, g, g, g, g, g, g, g)
#define MDR_ADCUI_GAIN_OFF      0

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

#endif  //  _MDR_ADCUI_VE4_DEFS_H
