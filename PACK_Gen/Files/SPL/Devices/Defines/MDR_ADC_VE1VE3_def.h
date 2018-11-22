#ifndef _MDR_ADC_VE1VE3_DEF_H
#define _MDR_ADC_VE1VE3_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <MDR_Types.h>
#include <MDR_ADC_defs.h>

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

/* =========================================================  ADC1_Cfg  ======================================================== */

typedef enum {
  MDR_ADC_Ch0 = 0,                             /*!< Channel_0/Ref+ : Signal on PD7, Ref+                                      */
  MDR_ADC_Ch1 = 1,                             /*!< Channel_1/Ref- : Signal on PD8, Ref-                                      */
  MDR_ADC_Ch2 = 2,                             /*!< Channel_2 : Signal on PD9                                                 */
  MDR_ADC_Ch3 = 3,                             /*!< Channel_3 : Signal on PD10                                                */
  MDR_ADC_Ch4 = 4,                             /*!< Channel_4 : Signal on PD11                                                */
  MDR_ADC_Ch5 = 5,                             /*!< Channel_5 : Signal on PD12                                                */
  MDR_ADC_Ch6 = 6,                             /*!< Channel_6 : Signal on PD13                                                */
  MDR_ADC_Ch7 = 7,                             /*!< Channel_7 : Signal on PD14                                                */
  MDR_ADC_ChTS_Vref = 30,                      /*!< TS_VRef_1.23 : Signal from Thermosensor                                   */
  MDR_ADC_ChTS_Temper = 31                     /*!< TS_Temperature : Signal from Thermosensor                                 */
} MDR_ADC_CHSEL;

#define MDR_ADC_CH_REF_MAX    MDR_ADC_Ch0
#define MDR_ADC_CH_REF_MIN    MDR_ADC_Ch1
#define MDR_ADC_PIN_CHANNEL_COUNT   8


typedef enum {
  ADC_Ch0 = 0,                             /*!< Channel_0/Ref+ : Signal on PD7, Ref+                                 */
  ADC_Ch1 = 1,                             /*!< Channel_1/Ref- : Signal on PD8, Ref-                                 */
  ADC_Ch2 = 2,                             /*!< Channel_2  : Signal on PD9                                           */
  ADC_Ch3 = 3,                             /*!< Channel_3  : Signal on PD10                                           */
  ADC_Ch4 = 4,                             /*!< Channel_4  : Signal on PD11                                           */
  ADC_Ch5 = 5,                             /*!< Channel_5  : Signal on PD12                                           */
  ADC_Ch6 = 6,                             /*!< Channel_6  : Signal on PD13                                           */
  ADC_Ch7 = 7                              /*!< Channel_7  : Signal on PD14                                           */
} MDR_ADC_PinChannel;

#define MDR_ADC_PinChannel_Last  ADC_Ch7

typedef struct {
  __IOM MDR_OnOff           ADON       : 1;            /*!< [0..0] Enable ADC                                                     */
  __IOM MDR_OnOff           GO         : 1;            /*!< [1..1] Start single ADC mesurement                                    */
  __IOM MDR_ADC_CLK_SEL     CLKS       : 1;            /*!< [2..2] Select Clock                                                   */
  __IOM MDR_ADC_SAMPLE      SAMPLE     : 1;            /*!< [3..3] Single or Continuous measurement                               */
  __IOM MDR_ADC_CHSEL       CHS        : 5;            /*!< [8..4] Active channel select                                          */ 
  __IOM MDR_OnOff           CHCH       : 1;            /*!< [9..9] Channel switching enable                                       */
  __IOM MDR_OnOff           RGNC       : 1;            /*!< [10..10] Signal limiters enable                                       */
  __IOM MDR_ADC_MAGREF_SRC  M_REF      : 1;            /*!< [11..11] Signal amplitude reference                                   */
  __IOM MDR_ADC_CPU_DIV     DIV_CLK    : 4;            /*!< [15..12] Divider for CPU_Clock usage                                  */
  __IM  uint32_t                    : 1;
  __IOM MDR_OnOff           TS_EN      : 1;            /*!< [17..17] Thermosensor enable                                          */
  __IOM MDR_OnOff           TS_BUFF_EN : 1;            /*!< [18..18] Thermosensor buffer enable                                   */
  __IOM MDR_OnOff           SEL_TS     : 1;            /*!< [19..19] Output temperature from Thermosensor                         */
  __IOM MDR_OnOff           SEL_VREF   : 1;            /*!< [20..20] Output Vref=1.23 from Thermosensor                           */
  __IM  uint32_t                       : 4;
  __IOM MDR_ADC_DelayGO     Delay_GO   : 3;            /*!< [27..25] Delay after channels switching in CPU_CLK                    */
  __IM  uint32_t                       : 4;
} MDR_ADC1_Cfg_Bits;

//  Masks for ADC1_Cfg
#define MDR_ADCx_Cfg_ADON_Pos         (0UL)                     /*!< MDR_ADC ADC1_Cfg: ADON (Bit 0)                        */
#define MDR_ADCx_Cfg_ADON_Msk         (0x1UL)                   /*!< MDR_ADC ADC1_Cfg: ADON (Bitfield-Mask: 0x01)          */
#define MDR_ADCx_Cfg_GO_Pos           (1UL)                     /*!< MDR_ADC ADC1_Cfg: GO (Bit 1)                          */
#define MDR_ADCx_Cfg_GO_Msk           (0x2UL)                   /*!< MDR_ADC ADC1_Cfg: GO (Bitfield-Mask: 0x01)            */
#define MDR_ADCx_Cfg_CLKS_Pos         (2UL)                     /*!< MDR_ADC ADC1_Cfg: CLKS (Bit 2)                        */
#define MDR_ADCx_Cfg_CLKS_Msk         (0x4UL)                   /*!< MDR_ADC ADC1_Cfg: CLKS (Bitfield-Mask: 0x01)          */
#define MDR_ADCx_Cfg_SAMPLE_Pos       (3UL)                     /*!< MDR_ADC ADC1_Cfg: SAMPLE (Bit 3)                      */
#define MDR_ADCx_Cfg_SAMPLE_Msk       (0x8UL)                   /*!< MDR_ADC ADC1_Cfg: SAMPLE (Bitfield-Mask: 0x01)        */
#define MDR_ADCx_Cfg_CHS_Pos          (4UL)                     /*!< MDR_ADC ADC1_Cfg: CHS (Bit 4)                         */
#define MDR_ADCx_Cfg_CHS_Msk          (0x1f0UL)                 /*!< MDR_ADC ADC1_Cfg: CHS (Bitfield-Mask: 0x1f)           */
#define MDR_ADCx_Cfg_CHCH_Pos         (9UL)                     /*!< MDR_ADC ADC1_Cfg: CHCH (Bit 9)                        */
#define MDR_ADCx_Cfg_CHCH_Msk         (0x200UL)                 /*!< MDR_ADC ADC1_Cfg: CHCH (Bitfield-Mask: 0x01)          */
#define MDR_ADCx_Cfg_RGNC_Pos         (10UL)                    /*!< MDR_ADC ADC1_Cfg: RGNC (Bit 10)                       */
#define MDR_ADCx_Cfg_RGNC_Msk         (0x400UL)                 /*!< MDR_ADC ADC1_Cfg: RGNC (Bitfield-Mask: 0x01)          */
#define MDR_ADCx_Cfg_M_REF_Pos        (11UL)                    /*!< MDR_ADC ADC1_Cfg: M_REF (Bit 11)                      */
#define MDR_ADCx_Cfg_M_REF_Msk        (0x800UL)                 /*!< MDR_ADC ADC1_Cfg: M_REF (Bitfield-Mask: 0x01)         */
#define MDR_ADCx_Cfg_DIV_CLK_Pos      (12UL)                    /*!< MDR_ADC ADC1_Cfg: DIV_CLK (Bit 12)                    */
#define MDR_ADCx_Cfg_DIV_CLK_Msk      (0xf000UL)                /*!< MDR_ADC ADC1_Cfg: DIV_CLK (Bitfield-Mask: 0x0f)       */

//  Masks for ADC1_Cfg
#define MDR_ADC1_Cfg_TS_EN_Pos        (17UL)                    /*!< MDR_ADC ADC1_Cfg: TS_EN (Bit 17)                      */
#define MDR_ADC1_Cfg_TS_EN_Msk        (0x20000UL)               /*!< MDR_ADC ADC1_Cfg: TS_EN (Bitfield-Mask: 0x01)         */
#define MDR_ADC1_Cfg_TS_BUFF_EN_Pos   (18UL)                    /*!< MDR_ADC ADC1_Cfg: TS_BUFF_EN (Bit 18)                 */
#define MDR_ADC1_Cfg_TS_BUFF_EN_Msk   (0x40000UL)               /*!< MDR_ADC ADC1_Cfg: TS_BUFF_EN (Bitfield-Mask: 0x01)    */
#define MDR_ADC1_Cfg_SEL_TS_Pos       (19UL)                    /*!< MDR_ADC ADC1_Cfg: SEL_TS (Bit 19)                     */
#define MDR_ADC1_Cfg_SEL_TS_Msk       (0x80000UL)               /*!< MDR_ADC ADC1_Cfg: SEL_TS (Bitfield-Mask: 0x01)        */
#define MDR_ADC1_Cfg_SEL_VREF_Pos     (20UL)                    /*!< MDR_ADC ADC1_Cfg: SEL_VREF (Bit 20)                   */
#define MDR_ADC1_Cfg_SEL_VREF_Msk     (0x100000UL)              /*!< MDR_ADC ADC1_Cfg: SEL_VREF (Bitfield-Mask: 0x01)      */
#define MDR_ADC1_Cfg_Delay_GO_Pos     (25UL)                    /*!< MDR_ADC ADC1_Cfg: Delay_GO (Bit 25)                   */
#define MDR_ADC1_Cfg_Delay_GO_Msk     (0xe000000UL)             /*!< MDR_ADC ADC1_Cfg: Delay_GO (Bitfield-Mask: 0x07)      */


/* =========================================================  ADC2_Cfg  ======================================================== */
typedef struct {
  __IM  uint32_t            : 17;
  __IOM uint32_t ADC1_OP    : 1;                    /*!< [17..17] ADC1 Setpoint Vref source                                    */
  __IM  uint32_t            : 14;
} MDR_ADC2_Cfg_Bits;

#define MDR_ADC2_Cfg_ADC1_OP_Pos      (17UL)                    /*!< MDR_ADC ADC2_Cfg: ADC1_OP (Bit 17)                    */
#define MDR_ADC2_Cfg_ADC1_OP_Msk      (0x20000UL)               /*!< MDR_ADC ADC2_Cfg: ADC1_OP (Bitfield-Mask: 0x01)       */

#define MDR_ADC2_AVALABLE_BITS  MDR_ADC2_Cfg_ADC1_OP_Msk

/* =========================================================  ADC_CHSEL  ================================================= */
typedef struct {
  __IOM MDR_OnOff MDR_ADC_SwCh0  : 1;            /*!< [0..0] Signal on PD7, Ref+                                            */
  __IOM MDR_OnOff MDR_ADC_SwCh1  : 1;            /*!< [1..1] Signal on PD8, Ref-                                            */
  __IOM MDR_OnOff MDR_ADC_SwCh2  : 1;            /*!< [2..2] Signal on PD9                                                  */
  __IOM MDR_OnOff MDR_ADC_SwCh3  : 1;            /*!< [3..3] Signal on PD10                                                 */
  __IOM MDR_OnOff MDR_ADC_SwCh4  : 1;            /*!< [4..4] Signal on PD11                                                 */
  __IOM MDR_OnOff MDR_ADC_SwCh5  : 1;            /*!< [5..5] Signal on PD12                                                 */
  __IOM MDR_OnOff MDR_ADC_SwCh6  : 1;            /*!< [6..6] Signal on PD13                                                 */
  __IOM MDR_OnOff MDR_ADC_SwCh7  : 1;            /*!< [7..7] Signal on PD14                                                 */
  __IM  uint32_t                 : 22;
  __IOM MDR_OnOff MDR_ADC_SwTS_Vref   : 1;      /*!< [30..30] VRef from Thermosensor                                        */
  __IOM MDR_OnOff MDR_ADC_SwTS_Temper : 1;      /*!< [31..31] Temperature from Thermosensor                                 */
} MDR_ADC_CHSEL_Bits;

#define MDR_ADC_SwCh0_Pos  (0UL)                     /*!< MDR_ADC ADC1_CHSEL: Channel_0 (Bit 0)                 */
#define MDR_ADC_SwCh0_Msk  (0x1UL)                   /*!< MDR_ADC ADC1_CHSEL: Channel_0 (Bitfield-Mask: 0x01)   */
#define MDR_ADC_SwCh1_Pos  (1UL)                     /*!< MDR_ADC ADC1_CHSEL: Channel_1 (Bit 1)                 */
#define MDR_ADC_SwCh1_Msk  (0x2UL)                   /*!< MDR_ADC ADC1_CHSEL: Channel_1 (Bitfield-Mask: 0x01)   */
#define MDR_ADC_SwCh2_Pos  (2UL)                     /*!< MDR_ADC ADC1_CHSEL: Channel_2 (Bit 2)                 */
#define MDR_ADC_SwCh2_Msk  (0x4UL)                   /*!< MDR_ADC ADC1_CHSEL: Channel_2 (Bitfield-Mask: 0x01)   */
#define MDR_ADC_SwCh3_Pos  (3UL)                     /*!< MDR_ADC ADC1_CHSEL: Channel_3 (Bit 3)                 */
#define MDR_ADC_SwCh3_Msk  (0x8UL)                   /*!< MDR_ADC ADC1_CHSEL: Channel_3 (Bitfield-Mask: 0x01)   */
#define MDR_ADC_SwCh4_Pos  (4UL)                     /*!< MDR_ADC ADC1_CHSEL: Channel_4 (Bit 4)                 */
#define MDR_ADC_SwCh4_Msk  (0x10UL)                  /*!< MDR_ADC ADC1_CHSEL: Channel_4 (Bitfield-Mask: 0x01)   */
#define MDR_ADC_SwCh5_Pos  (5UL)                     /*!< MDR_ADC ADC1_CHSEL: Channel_5 (Bit 5)                 */
#define MDR_ADC_SwCh5_Msk  (0x20UL)                  /*!< MDR_ADC ADC1_CHSEL: Channel_5 (Bitfield-Mask: 0x01)   */
#define MDR_ADC_SwCh6_Pos  (6UL)                     /*!< MDR_ADC ADC1_CHSEL: Channel_6 (Bit 6)                 */
#define MDR_ADC_SwCh6_Msk  (0x40UL)                  /*!< MDR_ADC ADC1_CHSEL: Channel_6 (Bitfield-Mask: 0x01)   */
#define MDR_ADC_SwCh7_Pos  (7UL)                     /*!< MDR_ADC ADC1_CHSEL: Channel_7 (Bit 7)                 */
#define MDR_ADC_SwCh7_Msk  (0x80UL)                  /*!< MDR_ADC ADC1_CHSEL: Channel_7 (Bitfield-Mask: 0x01)   */

#define MDR_ADC_SwCh30_Pos (30UL)                    /*!< MDR_ADC ADC1_CHSEL: Channel_30 (Bit 30)               */
#define MDR_ADC_SwCh30_Msk (0x40000000UL)            /*!< MDR_ADC ADC1_CHSEL: Channel_30 (Bitfield-Mask: 0x01)  */
#define MDR_ADC_SwCh31_Pos (31UL)                    /*!< MDR_ADC ADC1_CHSEL: Channel_31 (Bit 31)               */
#define MDR_ADC_SwCh31_Msk (0x80000000UL)            /*!< MDR_ADC ADC1_CHSEL: Channel_31 (Bitfield-Mask: 0x01)  */


typedef struct {
  MDR_OnOff ADC_SelCh0  : 1;            /*!< Channel_0/Ref+ : Signal on PD7, Ref+                                 */
  MDR_OnOff ADC_SelCh1  : 1;            /*!< Channel_1/Ref- : Signal on PD8, Ref-                                 */
  MDR_OnOff ADC_SelCh2  : 1;            /*!< Channel_2  : Signal on PD9                                           */
  MDR_OnOff ADC_SelCh3  : 1;            /*!< Channel_3  : Signal on PD10                                          */
  MDR_OnOff ADC_SelCh4  : 1;            /*!< Channel_4  : Signal on PD11                                          */
  MDR_OnOff ADC_SelCh5  : 1;            /*!< Channel_5  : Signal on PD12                                          */
  MDR_OnOff ADC_SelCh6  : 1;            /*!< Channel_6  : Signal on PD13                                          */
  MDR_OnOff ADC_SelCh7  : 1;            /*!< Channel_7  : Signal on PD14                                          */
  uint32_t              : 24;
} MDR_ADC_PinChannel_Flags;

/* ======================================================  ADC_TRIM  ===================================================== */
typedef struct {
  __IM  uint32_t                           : 1;
  __IOM MDR_ADC_TRIM_TS_Vref  TS_Trim      : 5;             /*!< [5..1] Trim Vref from Thermosensor                   */
  __IOM MDR_OnOff             SEL_VREF_BUF : 1;             /*!< [6..6] Output Vref_Buf=1.23 from Thermosensor        */
  __IM  uint32_t                           : 25;
} MD_ADC_TRIM_TS_Bits;

#define MDR_ADC_TRIM_TS_Trim_Pos     (1UL)                  /*!< MDR_ADC ADC1_TRIM: TS_Trim (Bit 1)                    */
#define MDR_ADC_TRIM_TS_Trim_Msk     (0x3eUL)               /*!< MDR_ADC ADC1_TRIM: TS_Trim (Bitfield-Mask: 0x1f)      */
#define MDR_ADC_TRIM_SEL_VREF_BUF_Pos (6UL)                 /*!< MDR_ADC ADC1_TRIM: SEL_VREF_BUF (Bit 6)               */
#define MDR_ADC_TRIM_SEL_VREF_BUF_Msk (0x40UL)              /*!< MDR_ADC ADC1_TRIM: SEL_VREF_BUF (Bitfield-Mask: 0x01) */


/* =========================================================  ADC_TYPE  ================================================= */

typedef struct {                                /*!< (@ 0x40088000) MDR_ADC Structure                                          */
 
  union {
    __IOM uint32_t      ADC1_Cfg;               /*!< (@ 0x00000000) ADC1 config register                                       */
    MDR_ADC1_Cfg_Bits   ADC1_Cfg_b;
  } ;
  union {
    __IOM uint32_t      ADC2_Cfg;               /*!< (@ 0x00000004) ADC2 config register                                       */
    MDR_ADC2_Cfg_Bits   ADC2_Cfg_b;    
  } ;
  union {
    __IOM uint32_t      ADC1_H_Level;           /*!< (@ 0x00000008) ADC High limit                                             */
    MDR_ADC_Level_Bits  ADC1_H_Level_b;
  } ;
  __IM  uint32_t  RESERVED0;
  union {
    __IOM uint32_t      ADC1_L_Level;           /*!< (@ 0x00000010) ADC Low limit                                              */
    MDR_ADC_Level_Bits  ADC1_L_Level_b;
  } ;
  __IM  uint32_t  RESERVED1;
  union {
    __IM  uint32_t      ADC1_Result;            /*!< (@ 0x00000018) ADC result register                                        */
    MDR_ADC_Result_Bits ADC1_Result_b;
  } ;
  __IM  uint32_t  RESERVED2;
  union {
    __IOM uint32_t      ADC1_Status;            /*!< (@ 0x00000020) ADC status register                                        */
    MDR_ADC_STATUS_Bits ADC1_Status_b;
  } ;
  __IM  uint32_t  RESERVED3;
  union {
    __IOM uint32_t      ADC1_CHSEL;             /*!< (@ 0x00000028) ADC channels select register                               */
    MDR_ADC_CHSEL_Bits  ADC1_CHSEL_b;
  } ;
  __IM  uint32_t  RESERVED4;
  union {
    __IOM uint32_t      ADC1_Trim;              /*!< (@ 0x00000030) ADC TS_Vref trim register                                  */
    MD_ADC_TRIM_TS_Bits ADC1_Trim_b;
  } ;
  
} MDR_ADC_Type;                                 /*!< Size = 52 (0x34)                                                          */

typedef struct {                                /*!< (@ 0x40088000) MDR_ADC Structure                                          */ 
  __IOM uint32_t      ADCx_Cfg;               /*!< (@ 0x00000000) ADC1 config register                                       */
  __IM  uint32_t        RESERVED0;
  __IOM uint32_t      ADCx_H_Level;           /*!< (@ 0x00000008) ADC High limit                                             */
  __IM  uint32_t        RESERVED1;
  __IOM uint32_t      ADCx_L_Level;           /*!< (@ 0x00000010) ADC Low limit                                              */
  __IM  uint32_t        RESERVED2;
  __IM  uint32_t      ADCx_Result;            /*!< (@ 0x00000018) ADC result register                                        */
  __IM  uint32_t        RESERVED3;
  __IOM uint32_t      ADCx_Status;            /*!< (@ 0x00000020) ADC status register                                        */
  __IM  uint32_t        RESERVED4;
  __IOM uint32_t      ADCx_CHSEL;             /*!< (@ 0x00000028) ADC channels select register                               */
} MDR_ADCx_ItemType;


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

#endif  //_MDR_ADC_VE1VE3_DEF_H
