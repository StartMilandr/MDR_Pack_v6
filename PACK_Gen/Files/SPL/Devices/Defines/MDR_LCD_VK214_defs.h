#ifndef _MDR_LCD_VK214_H
#define _MDR_LCD_VK214_H

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

/* ========================================  CR - Control Register  ======================================== */
typedef enum {                      /*!< MDR_LCD_VK214_CR_Mux                                                      */
  LCD_CR_Mux_Static        = 0,     /*!< Static : Static control                                                   */
  LCD_CR_Mux_2             = 1,     /*!< MUX_2 : Muxtiplexing 1:2                                                  */
  LCD_CR_Mux_3             = 2,     /*!< MUX_3 : Muxtiplexing 1:3                                                  */
  LCD_CR_Mux_4             = 3,     /*!< MUX_4 : Muxtiplexing 1:4                                                  */
} MDR_LCD_CR_Mux;

typedef enum {                      /*!< MDR_LCD_VK214_CR_Bias                                                     */
  LCD_CR_Bias_div3         = 0,     /*!< div3 : Bias 1/3                                                           */
  LCD_CR_Bias_div2         = 1,     /*!< div2 : Bias 1/2                                                           */
} MDR_LCD_CR_Bias;

typedef enum {                      /*!< MDR_LCD_VK214_CR_BF                                                       */
  LCD_CR_BF_Off            = 0,     /*!< Off : Flicker Disabled                                                    */
  LCD_CR_BF_2Hz            = 1,     /*!< 2Hz : Flicker with 2 Hz                                                   */
  LCD_CR_BF_1Hz            = 2,     /*!< 1Hz : Flicker with 1 Hz                                                   */
  LCD_CR_BF_0Hz5           = 3,     /*!< 0Hz5 : Flicker with 0.5 Hz                                                */
} MDR_LCD_CR_BF;

typedef enum {                      /*!< MDR_LCD_VK214_CR_AltFlicker                                               */
  LCD_CR_AF_Off            = 0,     /*!< byRegBF : Flicker according to BF                                         */
  LCD_CR_AF_AltMem         = 1,     /*!< byAlterMemory : Flicker according to alter memory                         */
} MDR_LCD_CR_AF;

typedef enum {                      /*!< MDR_LCD_VK214_CR_VLCDOn                                                   */
  LCD_CR_VLCD_Int          = 0,     /*!< Internal : Internal source                                                */
  LCD_CR_VLCD_Ext          = 1,     /*!< External : External source from pin PC2                                   */
} MDR_LCD_CR_VLCD;

typedef enum {                      /*!< MDR_LCD_VK214_CR_CLK_SEL                                                  */
  LCD_CR_CLK_LSE           = 0,     /*!< LSE : Clock from LSE                                                      */
  LCD_CR_CLK_LSI           = 1,     /*!< LSI : Clock from LSI                                                      */
} MDR_LCD_CR_CLK;

typedef struct {
  __IOM MDR_LCD_CR_Mux    Mux        : 2;            /*!< [1..0] Multiplex select                                                   */
  __IOM MDR_LCD_CR_Bias   Bias       : 1;            /*!< [2..2] Bias                                                               */
  __IOM MDR_OnOff         EN         : 1;            /*!< [3..3] Enable                                                             */
  __IOM MDR_LCD_CR_BF     BaseFliker : 2;            /*!< [5..4] Flicker                                                            */
  __IOM MDR_LCD_CR_AF     AltFlicker : 1;            /*!< [6..6] AlterFlicker                                                       */
  __IOM MDR_LCD_CR_VLCD   VLCDOn     : 1;            /*!< [7..7] Select Vlcd power                                                  */
  __IOM uint32_t          DIV        : 16;           /*!< [23..8] Clock div                                                         */
  __IOM MDR_LCD_CR_CLK    CLK_SEL    : 1;            /*!< [24..24] Clock Select                                                     */
  __IM  uint32_t                     : 7;
} MDR_LCD_CR_Bits;

#define MDR_LCD_CR_Mux_Pos          (0UL)                     /*!< MDR_LCD_VK214 CR: Mux (Bit 0)                         */
#define MDR_LCD_CR_Mux_Msk          (0x3UL)                   /*!< MDR_LCD_VK214 CR: Mux (Bitfield-Mask: 0x03)           */
#define MDR_LCD_CR_Bias_Pos         (2UL)                     /*!< MDR_LCD_VK214 CR: Bias (Bit 2)                        */
#define MDR_LCD_CR_Bias_Msk         (0x4UL)                   /*!< MDR_LCD_VK214 CR: Bias (Bitfield-Mask: 0x01)          */
#define MDR_LCD_CR_EN_Pos           (3UL)                     /*!< MDR_LCD_VK214 CR: EN (Bit 3)                          */
#define MDR_LCD_CR_EN_Msk           (0x8UL)                   /*!< MDR_LCD_VK214 CR: EN (Bitfield-Mask: 0x01)            */
#define MDR_LCD_CR_BF_Pos           (4UL)                     /*!< MDR_LCD_VK214 CR: BF (Bit 4)                          */
#define MDR_LCD_CR_BF_Msk           (0x30UL)                  /*!< MDR_LCD_VK214 CR: BF (Bitfield-Mask: 0x03)            */
#define MDR_LCD_CR_AltFlicker_Pos   (6UL)                     /*!< MDR_LCD_VK214 CR: AltFlicker (Bit 6)                  */
#define MDR_LCD_CR_AltFlicker_Msk   (0x40UL)                  /*!< MDR_LCD_VK214 CR: AltFlicker (Bitfield-Mask: 0x01)    */
#define MDR_LCD_CR_VLCDOn_Pos       (7UL)                     /*!< MDR_LCD_VK214 CR: VLCDOn (Bit 7)                      */
#define MDR_LCD_CR_VLCDOn_Msk       (0x80UL)                  /*!< MDR_LCD_VK214 CR: VLCDOn (Bitfield-Mask: 0x01)        */
#define MDR_LCD_CR_DIV_Pos          (8UL)                     /*!< MDR_LCD_VK214 CR: DIV (Bit 8)                         */
#define MDR_LCD_CR_DIV_Msk          (0xffff00UL)              /*!< MDR_LCD_VK214 CR: DIV (Bitfield-Mask: 0xffff)         */
#define MDR_LCD_CR_CLK_SEL_Pos      (24UL)                    /*!< MDR_LCD_VK214 CR: CLK_SEL (Bit 24)                    */
#define MDR_LCD_CR_CLK_SEL_Msk      (0x1000000UL)             /*!< MDR_LCD_VK214 CR: CLK_SEL (Bitfield-Mask: 0x01)       */


/* ========================================  LCD Struct  ======================================== */
typedef struct {                                /*!< (@ 0x40038000) MDR_LCD_VK214 Structure                                    */
  union {
    __IOM uint32_t    CR;                       /*!< (@ 0x00000000) LCD Control register                                       */
    MDR_LCD_CR_Bits   CR_b;
  } ;
  __IOM uint32_t  ROW1;                         /*!< (@ 0x00000004) Base memory data string                                    */
  __IOM uint32_t  ROW2;                         /*!< (@ 0x00000008) Base memory data string                                    */
  __IOM uint32_t  ROW3;                         /*!< (@ 0x0000000C) Base memory data string                                    */
  __IOM uint32_t  ROW4;                         /*!< (@ 0x00000010) Base memory data string                                    */
  __IOM uint32_t  AROW1;                        /*!< (@ 0x00000014) Alter memory data string                                   */
  __IOM uint32_t  AROW2;                        /*!< (@ 0x00000018) Alter memory data string                                   */
  __IOM uint32_t  AROW3;                        /*!< (@ 0x0000001C) Alter memory data string                                   */
  __IOM uint32_t  AROW4;                        /*!< (@ 0x00000020) Alter memory data string                                   */
} MDR_LCD_Type;                           /*!< Size = 36 (0x24)                                                          */



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

#endif  //_MDR_LCD_VK214_H
