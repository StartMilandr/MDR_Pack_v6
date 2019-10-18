#ifndef _MDR_GPIO_DEFS_H
#define _MDR_GPIO_DEFS_H

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

#define MDR_GPIO_Pin_Count        16
#define MDR_GPIO_HAS_GFEN_SCHMT

/* ===================================================== reg  RXTX  ========================================================== */
typedef struct {
      __IOM uint32_t Pin_0      : 1;            /*!< [0..0] Pin data value                                                     */
      __IOM uint32_t Pin_1      : 1;            /*!< [1..1] Pin data value                                                     */
      __IOM uint32_t Pin_2      : 1;            /*!< [2..2] Pin data value                                                     */
      __IOM uint32_t Pin_3      : 1;            /*!< [3..3] Pin data value                                                     */
      __IOM uint32_t Pin_4      : 1;            /*!< [4..4] Pin data value                                                     */
      __IOM uint32_t Pin_5      : 1;            /*!< [5..5] Pin data value                                                     */
      __IOM uint32_t Pin_6      : 1;            /*!< [6..6] Pin data value                                                     */
      __IOM uint32_t Pin_7      : 1;            /*!< [7..7] Pin data value                                                     */
      __IOM uint32_t Pin_8      : 1;            /*!< [8..8] Pin data value                                                     */
      __IOM uint32_t Pin_9      : 1;            /*!< [9..9] Pin data value                                                     */
      __IOM uint32_t Pin_10     : 1;            /*!< [10..10] Pin data value                                                   */
      __IOM uint32_t Pin_11     : 1;            /*!< [11..11] Pin data value                                                   */
      __IOM uint32_t Pin_12     : 1;            /*!< [12..12] Pin data value                                                   */
      __IOM uint32_t Pin_13     : 1;            /*!< [13..13] Pin data value                                                   */
      __IOM uint32_t Pin_14     : 1;            /*!< [14..14] Pin data value                                                   */
      __IOM uint32_t Pin_15     : 1;            /*!< [15..15] Pin data value                                                   */
      __IM  uint32_t            : 16;
} MDR_GPIO_DATA_Bits;

#define MDR_GPIO_RXTX__Pin_Pos           (0UL)
#define MDR_GPIO_RXTX__Pin_Msk           (0x1UL)

typedef enum {
      MDR_PIN_Low                  = 0,
      MDR_RIN_High                 = 1
} MDR_PIN_RXTX;

/* ====================================================== reg  OE  =========================================================== */
typedef enum {
      MDR_PIN_IN                  = 0,
      MDR_PIN_OUT                 = 1
} MDR_PIN_OE;

typedef struct {
      __IOM MDR_PIN_OE  Pin_0      : 1;            /*!< [0..0] Pin data direction                                                 */
      __IOM MDR_PIN_OE  Pin_1      : 1;            /*!< [1..1] Pin data direction                                                 */
      __IOM MDR_PIN_OE  Pin_2      : 1;            /*!< [2..2] Pin data direction                                                 */
      __IOM MDR_PIN_OE  Pin_3      : 1;            /*!< [3..3] Pin data direction                                                 */
      __IOM MDR_PIN_OE  Pin_4      : 1;            /*!< [4..4] Pin data direction                                                 */
      __IOM MDR_PIN_OE  Pin_5      : 1;            /*!< [5..5] Pin data direction                                                 */
      __IOM MDR_PIN_OE  Pin_6      : 1;            /*!< [6..6] Pin data direction                                                 */
      __IOM MDR_PIN_OE  Pin_7      : 1;            /*!< [7..7] Pin data direction                                                 */
      __IOM MDR_PIN_OE  Pin_8      : 1;            /*!< [8..8] Pin data direction                                                 */
      __IOM MDR_PIN_OE  Pin_9      : 1;            /*!< [9..9] Pin data direction                                                 */
      __IOM MDR_PIN_OE  Pin_10     : 1;            /*!< [10..10] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_11     : 1;            /*!< [11..11] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_12     : 1;            /*!< [12..12] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_13     : 1;            /*!< [13..13] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_14     : 1;            /*!< [14..14] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_15     : 1;            /*!< [15..15] Pin data direction                                               */
      __IM  uint32_t               : 16;
} MDR_GPIO_IO_Bits;

#define MDR_GPIO_OE__Pin_Pos             (0UL)
#define MDR_GPIO_OE__Pin_Msk             (0x1UL)


/* ===================================================== reg  FUNC  ========================================================== */
typedef enum {
      MDR_PIN_PORT                 = 0,
      MDR_PIN_MAIN                 = 1,
      MDR_PIN_ALT                  = 2,
      MDR_PIN_OVER                 = 3
} MDR_PIN_FUNC;

typedef struct {
      __IOM MDR_PIN_FUNC  Pin_0      : 2;            /*!< [1..0] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_1      : 2;            /*!< [3..2] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_2      : 2;            /*!< [5..4] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_3      : 2;            /*!< [7..6] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_4      : 2;            /*!< [9..8] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_5      : 2;            /*!< [11..10] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_6      : 2;            /*!< [13..12] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_7      : 2;            /*!< [15..14] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_8      : 2;            /*!< [17..16] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_9      : 2;            /*!< [19..18] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_10     : 2;            /*!< [21..20] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_11     : 2;            /*!< [23..22] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_12     : 2;            /*!< [25..24] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_13     : 2;            /*!< [27..26] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_14     : 2;            /*!< [29..28] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_15     : 2;            /*!< [31..30] Pin Digital Function                                             */
} MDR_GPIO_FUNC_Bits;

#define MDR_GPIO_FUNC__Pin_Pos           (0UL)
#define MDR_GPIO_FUNC__Pin_Msk           (0x3UL)


/* ====================================================  reg  ANALOG  ========================================================= */
typedef enum {
      MDR_PIN_ANALOG                = 0,
      MDR_PIN_DIGIT                 = 1
} MDR_PIN_AD;

typedef struct {
      __IOM MDR_PIN_AD  Pin_0      : 1;            /*!< [0..0] Enable Digital mode                                                */
      __IOM MDR_PIN_AD  Pin_1      : 1;            /*!< [1..1] Enable Digital mode                                                */
      __IOM MDR_PIN_AD  Pin_2      : 1;            /*!< [2..2] Enable Digital mode                                                */
      __IOM MDR_PIN_AD  Pin_3      : 1;            /*!< [3..3] Enable Digital mode                                                */
      __IOM MDR_PIN_AD  Pin_4      : 1;            /*!< [4..4] Enable Digital mode                                                */
      __IOM MDR_PIN_AD  Pin_5      : 1;            /*!< [5..5] Enable Digital mode                                                */
      __IOM MDR_PIN_AD  Pin_6      : 1;            /*!< [6..6] Enable Digital mode                                                */
      __IOM MDR_PIN_AD  Pin_7      : 1;            /*!< [7..7] Enable Digital mode                                                */
      __IOM MDR_PIN_AD  Pin_8      : 1;            /*!< [8..8] Enable Digital mode                                                */
      __IOM MDR_PIN_AD  Pin_9      : 1;            /*!< [9..9] Enable Digital mode                                                */
      __IOM MDR_PIN_AD  Pin_10     : 1;            /*!< [10..10] Enable Digital mode                                              */
      __IOM MDR_PIN_AD  Pin_11     : 1;            /*!< [11..11] Enable Digital mode                                              */
      __IOM MDR_PIN_AD  Pin_12     : 1;            /*!< [12..12] Enable Digital mode                                              */
      __IOM MDR_PIN_AD  Pin_13     : 1;            /*!< [13..13] Enable Digital mode                                              */
      __IOM MDR_PIN_AD  Pin_14     : 1;            /*!< [14..14] Enable Digital mode                                              */
      __IOM MDR_PIN_AD  Pin_15     : 1;            /*!< [15..15] Enable Digital mode                                              */
      __IM  uint32_t               : 16;
} MDR_GPIO_ANALOG_Bits;

#define MDR_GPIO_ANALOG__Pin_Pos         (0UL)
#define MDR_GPIO_ANALOG__Pin_Msk         (0x1UL)


/* =====================================================   reg PULL  ========================================================== */
typedef struct {
      __IOM MDR_OnOff  Down_Pin_0 : 1;            /*!< [0..0] Pull Down Enable                                                   */
      __IOM MDR_OnOff  Down_Pin_1 : 1;            /*!< [1..1] Pull Down Enable                                                   */
      __IOM MDR_OnOff  Down_Pin_2 : 1;            /*!< [2..2] Pull Down Enable                                                   */
      __IOM MDR_OnOff  Down_Pin_3 : 1;            /*!< [3..3] Pull Down Enable                                                   */
      __IOM MDR_OnOff  Down_Pin_4 : 1;            /*!< [4..4] Pull Down Enable                                                   */
      __IOM MDR_OnOff  Down_Pin_5 : 1;            /*!< [5..5] Pull Down Enable                                                   */
      __IOM MDR_OnOff  Down_Pin_6 : 1;            /*!< [6..6] Pull Down Enable                                                   */
      __IOM MDR_OnOff  Down_Pin_7 : 1;            /*!< [7..7] Pull Down Enable                                                   */
      __IOM MDR_OnOff  Down_Pin_8 : 1;            /*!< [8..8] Pull Down Enable                                                   */
      __IOM MDR_OnOff  Down_Pin_9 : 1;            /*!< [9..9] Pull Down Enable                                                   */
      __IOM MDR_OnOff  Down_Pin_10 : 1;           /*!< [10..10] Pull Down Enable                                                 */
      __IOM MDR_OnOff  Down_Pin_11 : 1;           /*!< [11..11] Pull Down Enable                                                 */
      __IOM MDR_OnOff  Down_Pin_12 : 1;           /*!< [12..12] Pull Down Enable                                                 */
      __IOM MDR_OnOff  Down_Pin_13 : 1;           /*!< [13..13] Pull Down Enable                                                 */
      __IOM MDR_OnOff  Down_Pin_14 : 1;           /*!< [14..14] Pull Down Enable                                                 */
      __IOM MDR_OnOff  Down_Pin_15 : 1;           /*!< [15..15] Pull Down Enable                                                 */
      // PullUp Enable Bits
      __IOM MDR_OnOff  Up_Pin_0   : 1;            /*!< [16..16] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_1   : 1;            /*!< [17..17] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_2   : 1;            /*!< [18..18] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_3   : 1;            /*!< [19..19] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_4   : 1;            /*!< [20..20] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_5   : 1;            /*!< [21..21] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_6   : 1;            /*!< [22..22] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_7   : 1;            /*!< [23..23] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_8   : 1;            /*!< [24..24] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_9   : 1;            /*!< [25..25] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_10  : 1;            /*!< [26..26] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_11  : 1;            /*!< [27..27] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_12  : 1;            /*!< [28..28] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_13  : 1;            /*!< [29..29] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_14  : 1;            /*!< [30..30] Pull Up Enable                                                   */
      __IOM MDR_OnOff  Up_Pin_15  : 1;            /*!< [31..31] Pull Up Enable                                                   */
} MDR_GPIO_PULL_Bits;

#define MDR_GPIO_PULL_Down__Pin_Pos      (0UL)
#define MDR_GPIO_PULL_Down__Pin_Msk      (0x1UL)
#define MDR_GPIO_PULL_UP__Pin_Pos        (16UL)
#define MDR_GPIO_PULL_UP__Pin_Msk        (0x10000UL)


/* ==========================================================  PD  =========================================================== */
typedef enum {
      MDR_PIN_PullPush             = 0,
      MDR_PIN_OpenDrain            = 1
} MDR_PIN_PD;

typedef struct {
      __IOM MDR_PIN_PD  Driver_Pin_0 : 1;          /*!< [0..0] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  Driver_Pin_1 : 1;          /*!< [1..1] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  Driver_Pin_2 : 1;          /*!< [2..2] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  Driver_Pin_3 : 1;          /*!< [3..3] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  Driver_Pin_4 : 1;          /*!< [4..4] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  Driver_Pin_5 : 1;          /*!< [5..5] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  Driver_Pin_6 : 1;          /*!< [6..6] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  Driver_Pin_7 : 1;          /*!< [7..7] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  Driver_Pin_8 : 1;          /*!< [8..8] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  Driver_Pin_9 : 1;          /*!< [9..9] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  Driver_Pin_10 : 1;         /*!< [10..10] Driver mode for pin                                              */
      __IOM MDR_PIN_PD  Driver_Pin_11 : 1;         /*!< [11..11] Driver mode for pin                                              */
      __IOM MDR_PIN_PD  Driver_Pin_12 : 1;         /*!< [12..12] Driver mode for pin                                              */
      __IOM MDR_PIN_PD  Driver_Pin_13 : 1;         /*!< [13..13] Driver mode for pin                                              */
      __IOM MDR_PIN_PD  Driver_Pin_14 : 1;         /*!< [14..14] Driver mode for pin                                              */
      __IOM MDR_PIN_PD  Driver_Pin_15 : 1;         /*!< [15..15] Driver mode for pin                                              */
      // Schmitt Trigger enable
      __IOM MDR_OnOff  Schmitt_Pin_0 : 1;         /*!< [16..16] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_1 : 1;         /*!< [17..17] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_2 : 1;         /*!< [18..18] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_3 : 1;         /*!< [19..19] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_4 : 1;         /*!< [20..20] Schmitt trigger Enable                                           */      
      __IOM MDR_OnOff  Schmitt_Pin_5 : 1;         /*!< [21..21] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_6 : 1;         /*!< [22..22] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_7 : 1;         /*!< [23..23] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_8 : 1;         /*!< [24..24] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_9 : 1;         /*!< [25..25] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_10 : 1;        /*!< [26..26] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_11 : 1;        /*!< [27..27] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_12 : 1;        /*!< [28..28] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_13 : 1;        /*!< [29..29] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_14 : 1;        /*!< [30..30] Schmitt trigger Enable                                           */
      __IOM MDR_OnOff  Schmitt_Pin_15 : 1;        /*!< [31..31] Schmitt trigger Enable                                           */
} MDR_GPIO_PD_Bits;

#define MDR_GPIO_PD_Driver__Pin_Pos      (0UL)
#define MDR_GPIO_PD_Driver__Pin_Msk      (0x1UL)
#define MDR_GPIO_PD_Schmitt__Pin_Pos     (16UL)
#define MDR_GPIO_PD_Schmitt__Pin_Msk     (0x10000UL)


/* ====================================================== reg  PWR  ========================================================== */
typedef enum {
      MDR_PIN_PWR_OFF         = 0,
      MDR_PIN_SLOW            = 1,
      MDR_PIN_FAST            = 2,
      MDR_PIN_MAXFAST         = 3
} MDR_PIN_PWR;

typedef struct {
      __IOM MDR_PIN_PWR  Pin_0      : 2;            /*!< [1..0] Voltage levels switch rate                                               */
      __IOM MDR_PIN_PWR  Pin_1      : 2;            /*!< [3..2] Voltage levels switch rate                                               */
      __IOM MDR_PIN_PWR  Pin_2      : 2;            /*!< [5..4] Voltage levels switch rate                                               */
      __IOM MDR_PIN_PWR  Pin_3      : 2;            /*!< [7..6] Voltage levels switch rate                                               */
      __IOM MDR_PIN_PWR  Pin_4      : 2;            /*!< [9..8] Voltage levels switch rate                                               */
      __IOM MDR_PIN_PWR  Pin_5      : 2;            /*!< [11..10] Voltage levels switch rate                                             */
      __IOM MDR_PIN_PWR  Pin_6      : 2;            /*!< [13..12] Voltage levels switch rate                                             */
      __IOM MDR_PIN_PWR  Pin_7      : 2;            /*!< [15..14] Voltage levels switch rate                                             */
      __IOM MDR_PIN_PWR  Pin_8      : 2;            /*!< [17..16] Voltage levels switch rate                                             */
      __IOM MDR_PIN_PWR  Pin_9      : 2;            /*!< [19..18] Voltage levels switch rate                                             */
      __IOM MDR_PIN_PWR  Pin_10     : 2;            /*!< [21..20] Voltage levels switch rate                                             */
      __IOM MDR_PIN_PWR  Pin_11     : 2;            /*!< [23..22] Voltage levels switch rate                                             */
      __IOM MDR_PIN_PWR  Pin_12     : 2;            /*!< [25..24] Voltage levels switch rate                                             */
      __IOM MDR_PIN_PWR  Pin_13     : 2;            /*!< [27..26] Voltage levels switch rate                                             */
      __IOM MDR_PIN_PWR  Pin_14     : 2;            /*!< [29..28] Voltage levels switch rate                                             */
      __IOM MDR_PIN_PWR  Pin_15     : 2;            /*!< [31..30] Voltage levels switch rate                                             */
} MDR_GPIO_PWR_Bits;


#define MDR_GPIO_PWR__Pin_Pos            (0UL)
#define MDR_GPIO_PWR__Pin_Msk            (0x3UL)


/* ===================================================== reg  GFEN  ========================================================== */
typedef struct {
      __IOM MDR_OnOff  Pin_0      : 1;            /*!< [0..0] Filter for pin                                                     */
      __IOM MDR_OnOff  Pin_1      : 1;            /*!< [1..1] Filter for pin                                                     */
      __IOM MDR_OnOff  Pin_2      : 1;            /*!< [2..2] Filter for pin                                                     */
      __IOM MDR_OnOff  Pin_3      : 1;            /*!< [3..3] Filter for pin                                                     */
      __IOM MDR_OnOff  Pin_4      : 1;            /*!< [4..4] Filter for pin                                                     */
      __IOM MDR_OnOff  Pin_5      : 1;            /*!< [5..5] Filter for pin                                                     */
      __IOM MDR_OnOff  Pin_6      : 1;            /*!< [6..6] Filter for pin                                                     */
      __IOM MDR_OnOff  Pin_7      : 1;            /*!< [7..7] Filter for pin                                                     */
      __IOM MDR_OnOff  Pin_8      : 1;            /*!< [8..8] Filter for pin                                                     */
      __IOM MDR_OnOff  Pin_9      : 1;            /*!< [9..9] Filter for pin                                                     */
      __IOM MDR_OnOff  Pin_10     : 1;            /*!< [10..10] Filter for pin                                                   */
      __IOM MDR_OnOff  Pin_11     : 1;            /*!< [11..11] Filter for pin                                                   */
      __IOM MDR_OnOff  Pin_12     : 1;            /*!< [12..12] Filter for pin                                                   */
      __IOM MDR_OnOff  Pin_13     : 1;            /*!< [13..13] Filter for pin                                                   */
      __IOM MDR_OnOff  Pin_14     : 1;            /*!< [14..14] Filter for pin                                                   */
      __IOM MDR_OnOff  Pin_15     : 1;            /*!< [15..15] Filter for pin                                                   */
      __IM  uint32_t              : 16;
} MDR_PIN_GFEN_Bits;


#define MDR_GPIO_GFEN_Pin__Pos           (0UL)
#define MDR_GPIO_GFEN_Pin__Msk           (0x1UL)

/* =========================================================  SETTX  ========================================================= */
typedef struct {
      __IOM uint32_t Pin_0      : 1;            /*!< [0..0] Set 1 to pin                                                       */
      __IOM uint32_t Pin_1      : 1;            /*!< [1..1] Set 1 to pin                                                       */
      __IOM uint32_t Pin_2      : 1;            /*!< [2..2] Set 1 to pin                                                       */
      __IOM uint32_t Pin_3      : 1;            /*!< [3..3] Set 1 to pin                                                       */
      __IOM uint32_t Pin_4      : 1;            /*!< [4..4] Set 1 to pin                                                       */
      __IOM uint32_t Pin_5      : 1;            /*!< [5..5] Set 1 to pin                                                       */
      __IOM uint32_t Pin_6      : 1;            /*!< [6..6] Set 1 to pin                                                       */
      __IOM uint32_t Pin_7      : 1;            /*!< [7..7] Set 1 to pin                                                       */
      __IOM uint32_t Pin_8      : 1;            /*!< [8..8] Set 1 to pin                                                       */
      __IOM uint32_t Pin_9      : 1;            /*!< [9..9] Set 1 to pin                                                       */
      __IOM uint32_t Pin_10     : 1;            /*!< [10..10] Set 1 to pin                                                     */
      __IOM uint32_t Pin_11     : 1;            /*!< [11..11] Set 1 to pin                                                     */
      __IOM uint32_t Pin_12     : 1;            /*!< [12..12] Set 1 to pin                                                     */
      __IOM uint32_t Pin_13     : 1;            /*!< [13..13] Set 1 to pin                                                     */
      __IOM uint32_t Pin_14     : 1;            /*!< [14..14] Set 1 to pin                                                     */
      __IOM uint32_t Pin_15     : 1;            /*!< [15..15] Set 1 to pin                                                     */
      __IM  uint32_t            : 16;
} MDR_PIN_SETTX_Bits;

/* =========================================================  CLRTX  ========================================================= */
typedef struct {
      __IOM uint32_t Pin_0      : 1;            /*!< [0..0] Clear pin to 0                                                     */
      __IOM uint32_t Pin_1      : 1;            /*!< [1..1] Clear pin to 0                                                     */
      __IOM uint32_t Pin_2      : 1;            /*!< [2..2] Clear pin to 0                                                     */
      __IOM uint32_t Pin_3      : 1;            /*!< [3..3] Clear pin to 0                                                     */
      __IOM uint32_t Pin_4      : 1;            /*!< [4..4] Clear pin to 0                                                     */
      __IOM uint32_t Pin_5      : 1;            /*!< [5..5] Clear pin to 0                                                     */
      __IOM uint32_t Pin_6      : 1;            /*!< [6..6] Clear pin to 0                                                     */
      __IOM uint32_t Pin_7      : 1;            /*!< [7..7] Clear pin to 0                                                     */
      __IOM uint32_t Pin_8      : 1;            /*!< [8..8] Clear pin to 0                                                     */
      __IOM uint32_t Pin_9      : 1;            /*!< [9..9] Clear pin to 0                                                     */
      __IOM uint32_t Pin_10     : 1;            /*!< [10..10] Clear pin to 0                                                   */
      __IOM uint32_t Pin_11     : 1;            /*!< [11..11] Clear pin to 0                                                   */
      __IOM uint32_t Pin_12     : 1;            /*!< [12..12] Clear pin to 0                                                   */
      __IOM uint32_t Pin_13     : 1;            /*!< [13..13] Clear pin to 0                                                   */
      __IOM uint32_t Pin_14     : 1;            /*!< [14..14] Clear pin to 0                                                   */
      __IOM uint32_t Pin_15     : 1;            /*!< [15..15] Clear pin to 0                                                   */
      __IM  uint32_t            : 16;
} MDR_PIN_CLRTX_Bits;

/* =========================================================  RDTX  ========================================================== */
typedef struct {
      __IM  uint32_t Pin_0      : 1;            /*!< [0..0] Pin data in Port Func                                              */
      __IM  uint32_t Pin_1      : 1;            /*!< [1..1] Pin data in Port Func                                              */
      __IM  uint32_t Pin_2      : 1;            /*!< [2..2] Pin data in Port Func                                              */
      __IM  uint32_t Pin_3      : 1;            /*!< [3..3] Pin data in Port Func                                              */
      __IM  uint32_t Pin_4      : 1;            /*!< [4..4] Pin data in Port Func                                              */
      __IM  uint32_t Pin_5      : 1;            /*!< [5..5] Pin data in Port Func                                              */
      __IM  uint32_t Pin_6      : 1;            /*!< [6..6] Pin data in Port Func                                              */
      __IM  uint32_t Pin_7      : 1;            /*!< [7..7] Pin data in Port Func                                              */
      __IM  uint32_t Pin_8      : 1;            /*!< [8..8] Pin data in Port Func                                              */
      __IM  uint32_t Pin_9      : 1;            /*!< [9..9] Pin data in Port Func                                              */
      __IM  uint32_t Pin_10     : 1;            /*!< [10..10] Pin data in Port Func                                              */
      __IM  uint32_t Pin_11     : 1;            /*!< [11..11] Pin data in Port Func                                              */
      __IM  uint32_t Pin_12     : 1;            /*!< [12..12] Pin data in Port Func                                              */
      __IM  uint32_t Pin_13     : 1;            /*!< [13..13] Pin data in Port Func                                              */
      __IM  uint32_t Pin_14     : 1;            /*!< [14..14] Pin data in Port Func                                              */
      __IM  uint32_t Pin_15     : 1;            /*!< [15..15] Pin data in Port Func                                              */
      __IM  uint32_t            : 16;
} MDR_PIN_RDTX_Bits;


/* ============================================  GPIO Port Basic  ======================================================== */
typedef struct {                                       /*!<     MDR_PORT Structure                                        */
  
  union {
    __IOM uint32_t        RXTX;                        /*!< (@ 0x00000000) GPIO Pin Data                                              */    
    MDR_GPIO_DATA_Bits    RXTX_b;
  } ;  
  union {
    __IOM uint32_t        OE;                          /*!< (@ 0x00000004) Output Enable Control                                      */    
    MDR_GPIO_IO_Bits      OE_b;
  } ;  
  union {
    __IOM uint32_t        FUNC;                        /*!< (@ 0x00000008) Pin Functions in Digital mode                              */
    MDR_GPIO_FUNC_Bits    FUNC_b;
  } ;  
  union {
    __IOM uint32_t        ANALOG;                      /*!< (@ 0x0000000C) Enable Digital Mode Control                                */
    MDR_GPIO_ANALOG_Bits  ANALOG_b;
  } ;  
  union {
    __IOM uint32_t        PULL;                        /*!< (@ 0x00000010) PULL Up and Down Control                                   */
    MDR_GPIO_PULL_Bits    PULL_b;
  } ;  
  union {
    __IOM uint32_t        PD;                          /*!< (@ 0x00000014) Otput Driver Mode                                          */
    MDR_GPIO_PD_Bits      PD_b;
  } ;  
  union {
    __IOM uint32_t        PWR;                         /*!< (@ 0x00000018) Output voltage switch rate                                 */
    MDR_GPIO_PWR_Bits     PWR_b;
  } ;  
  union {
    __IOM uint32_t        GFEN;                        /*!< (@ 0x0000001C) Input pulses filter                                        */
    MDR_PIN_GFEN_Bits     GFEN_b;
  } ;

} MDR_PORT_Type__Base;


/* ========================================  GPIO Port with Set, Get and RD regs  ==================================================== */

typedef struct {                                       /*!<     MDR_PORT Structure                                        */
  
  union {
    __IOM uint32_t        RXTX;                        /*!< (@ 0x00000000) GPIO Pin Data                                              */    
    MDR_GPIO_DATA_Bits    RXTX_b;
  } ;  
  union {
    __IOM uint32_t        OE;                          /*!< (@ 0x00000004) Output Enable Control                                      */    
    MDR_GPIO_IO_Bits      OE_b;
  } ;  
  union {
    __IOM uint32_t        FUNC;                        /*!< (@ 0x00000008) Pin Functions in Digital mode                              */
    MDR_GPIO_FUNC_Bits    FUNC_b;
  } ;  
  union {
    __IOM uint32_t        ANALOG;                      /*!< (@ 0x0000000C) Enable Digital Mode Control                                */
    MDR_GPIO_ANALOG_Bits  ANALOG_b;
  } ;  
  union {
    __IOM uint32_t        PULL;                        /*!< (@ 0x00000010) PULL Up and Down Control                                   */
    MDR_GPIO_PULL_Bits    PULL_b;
  } ;  
  union {
    __IOM uint32_t        PD;                          /*!< (@ 0x00000014) Otput Driver Mode                                          */
    MDR_GPIO_PD_Bits      PD_b;
  } ;  
  union {
    __IOM uint32_t        PWR;                         /*!< (@ 0x00000018) Output voltage switch rate                                 */
    MDR_GPIO_PWR_Bits     PWR_b;
  } ;  
  union {
    __IOM uint32_t        GFEN;                        /*!< (@ 0x0000001C) Input pulses filter                                        */
    MDR_PIN_GFEN_Bits     GFEN_b;
  } ;
  union {
    __IOM uint32_t        SETTX;                       /*!< (@ 0x00000020) Set RXTX by MASK                                           */
    MDR_PIN_SETTX_Bits    SETTX_b;
  } ;  
  union {
    __IOM uint32_t        CLRTX;                       /*!< (@ 0x00000024) CLR RXTX by MASK                                           */
    MDR_PIN_CLRTX_Bits    CLRTX_b;
  } ;  
  union {
    __IM  uint32_t        RDTX;                        /*!< (@ 0x00000028) Value of RXTX in Port mode                                 */
    MDR_PIN_RDTX_Bits     RDTX_b;
  } ;

} MDR_PORT_Type__Ext;


typedef struct {
    uint32_t        RXTX;     
    uint32_t        OE;       
    uint32_t        FUNC;  
    uint32_t        ANALOG;
    uint32_t        PULL;  
    uint32_t        PD;    
    uint32_t        PWR;   
    uint32_t        GFEN;
} MDR_GPIO_SetCfg;

typedef struct {
    uint32_t        clrPins;  // RXTX, OE, ANALOG, FGEN
    uint32_t        clrFUNC;  
    uint32_t        clrHiLo;  // PD, PULL 
    uint32_t        clrPWR;   
} MDR_GPIO_ClearCfg;


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

#endif  //_MDR_GPIO_DEFS_H
