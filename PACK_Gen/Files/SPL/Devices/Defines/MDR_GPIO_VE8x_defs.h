#ifndef _MDR_GPIO_VE8x_DEFS_H
#define _MDR_GPIO_VE8x_DEFS_H

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

#define MDR_GPIO_Pin_Count      32
#define MDR_GPIO_HAS_KEY
#define MDR_GPIO_HAS_SET_CLEAR
#define MDR_GPIO_HAS_CfgIRQ
#define MDR_GPIO_CFG_SET_CLEAR

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
      __IOM uint32_t Pin_16     : 1;            /*!< [16..16] Pin data value                                                   */
      __IOM uint32_t Pin_17     : 1;            /*!< [17..17] Pin data value                                                   */
      __IOM uint32_t Pin_18     : 1;            /*!< [18..18] Pin data value                                                   */
      __IOM uint32_t Pin_19     : 1;            /*!< [19..19] Pin data value                                                   */
      __IOM uint32_t Pin_20     : 1;            /*!< [20..20] Pin data value                                                   */
      __IOM uint32_t Pin_21     : 1;            /*!< [21..21] Pin data value                                                   */
      __IOM uint32_t Pin_22     : 1;            /*!< [22..22] Pin data value                                                   */
      __IOM uint32_t Pin_23     : 1;            /*!< [23..23] Pin data value                                                   */
      __IOM uint32_t Pin_24     : 1;            /*!< [24..24] Pin data value                                                   */
      __IOM uint32_t Pin_25     : 1;            /*!< [25..25] Pin data value                                                   */
      __IOM uint32_t Pin_26     : 1;            /*!< [26..26] Pin data value                                                   */
      __IOM uint32_t Pin_27     : 1;            /*!< [27..27] Pin data value                                                   */
      __IOM uint32_t Pin_28     : 1;            /*!< [28..28] Pin data value                                                   */
      __IOM uint32_t Pin_29     : 1;            /*!< [29..29] Pin data value                                                   */
      __IOM uint32_t Pin_30     : 1;            /*!< [30..30] Pin data value                                                   */
      __IOM uint32_t Pin_31     : 1;            /*!< [31..31] Pin data value                                                   */
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
      __IOM MDR_PIN_OE  Pin_16     : 1;            /*!< [16..16] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_17     : 1;            /*!< [17..17] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_18     : 1;            /*!< [18..18] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_19     : 1;            /*!< [19..19] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_20     : 1;            /*!< [20..20] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_21     : 1;            /*!< [21..21] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_22     : 1;            /*!< [22..22] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_23     : 1;            /*!< [23..23] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_24     : 1;            /*!< [24..24] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_25     : 1;            /*!< [25..25] Pin data direction                                               */  
      __IOM MDR_PIN_OE  Pin_26     : 1;            /*!< [26..26] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_27     : 1;            /*!< [27..27] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_28     : 1;            /*!< [28..28] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_29     : 1;            /*!< [29..29] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_30     : 1;            /*!< [30..30] Pin data direction                                               */
      __IOM MDR_PIN_OE  Pin_31     : 1;            /*!< [31..31] Pin data direction                                               */
} MDR_GPIO_IO_Bits;

#define MDR_GPIO_OE__Pin_Pos             (0UL)
#define MDR_GPIO_OE__Pin_Msk             (0x1UL)


/* ===================================================== reg  FUNC  ========================================================== */
typedef enum {
      MDR_PIN_PORT                 = 0,
      MDR_PIN_FUNC_1               = 1,
      MDR_PIN_FUNC_2               = 2,
      MDR_PIN_FUNC_3               = 3,
      MDR_PIN_FUNC_4               = 4,
      MDR_PIN_FUNC_5               = 5,
      MDR_PIN_FUNC_6               = 6,
      MDR_PIN_FUNC_7               = 7,
      MDR_PIN_FUNC_8               = 8,
      MDR_PIN_FUNC_9               = 9,
      MDR_PIN_FUNC_10              = 10,
      MDR_PIN_FUNC_11              = 11,
      MDR_PIN_FUNC_12              = 12,
      MDR_PIN_FUNC_13              = 13,
      MDR_PIN_FUNC_14              = 14,
      MDR_PIN_FUNC_15              = 15,      
} MDR_PIN_FUNC;

#define MDR_PIN_FUNC_CLR      MDR_PIN_FUNC_15

typedef struct {
      __IOM MDR_PIN_FUNC  Pin_0      : 4;            /*!< [1..0] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_1      : 4;            /*!< [3..2] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_2      : 4;            /*!< [5..4] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_3      : 4;            /*!< [7..6] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_4      : 4;            /*!< [9..8] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_5      : 4;            /*!< [11..10] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_6      : 4;            /*!< [13..12] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_7      : 4;            /*!< [15..14] Pin Digital Function                                             */
} MDR_GPIO_FUNC0_Bits;

typedef struct {
      __IOM MDR_PIN_FUNC  Pin_8      : 4;            /*!< [1..0] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_9      : 4;            /*!< [3..2] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_10     : 4;            /*!< [5..4] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_11     : 4;            /*!< [7..6] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_12     : 4;            /*!< [9..8] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_13     : 4;            /*!< [11..10] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_14     : 4;            /*!< [13..12] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_15     : 4;            /*!< [15..14] Pin Digital Function                                             */
} MDR_GPIO_FUNC1_Bits;

typedef struct {
      __IOM MDR_PIN_FUNC  Pin_16      : 4;            /*!< [1..0] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_17      : 4;            /*!< [3..2] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_18      : 4;            /*!< [5..4] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_19      : 4;            /*!< [7..6] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_20      : 4;            /*!< [9..8] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_21      : 4;            /*!< [11..10] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_22      : 4;            /*!< [13..12] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_23      : 4;            /*!< [15..14] Pin Digital Function                                             */
} MDR_GPIO_FUNC2_Bits;

typedef struct {
      __IOM MDR_PIN_FUNC  Pin_24      : 4;            /*!< [1..0] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_25      : 4;            /*!< [3..2] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_26      : 4;            /*!< [5..4] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_27      : 4;            /*!< [7..6] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_28      : 4;            /*!< [9..8] Pin Digital Function                                               */
      __IOM MDR_PIN_FUNC  Pin_29      : 4;            /*!< [11..10] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_30      : 4;            /*!< [13..12] Pin Digital Function                                             */
      __IOM MDR_PIN_FUNC  Pin_31      : 4;            /*!< [15..14] Pin Digital Function                                             */
} MDR_GPIO_FUNC3_Bits;

#define MDR_GPIO_FUNC__Pin_Pos           (0UL)
#define MDR_GPIO_FUNC__Pin_Msk           (0xFUL)


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
      __IOM MDR_PIN_AD  Pin_16     : 1;
      __IOM MDR_PIN_AD  Pin_17     : 1;
      __IOM MDR_PIN_AD  Pin_18     : 1;
      __IOM MDR_PIN_AD  Pin_19     : 1;
      __IOM MDR_PIN_AD  Pin_20     : 1; 
      __IOM MDR_PIN_AD  Pin_21     : 1; 
      __IOM MDR_PIN_AD  Pin_22     : 1; 
      __IOM MDR_PIN_AD  Pin_23     : 1; 
      __IOM MDR_PIN_AD  Pin_24     : 1; 
      __IOM MDR_PIN_AD  Pin_25     : 1; 
      __IOM MDR_PIN_AD  Pin_26     : 1;
      __IOM MDR_PIN_AD  Pin_27     : 1;
      __IOM MDR_PIN_AD  Pin_28     : 1;
      __IOM MDR_PIN_AD  Pin_29     : 1;
      __IOM MDR_PIN_AD  Pin_30     : 1; 
      __IOM MDR_PIN_AD  Pin_31     : 1; 
} MDR_GPIO_ANALOG_Bits;

#define MDR_GPIO_ANALOG__Pin_Pos         (0UL)
#define MDR_GPIO_ANALOG__Pin_Msk         (0x1UL)


/* =====================================================   reg PULL  ========================================================== */
#define MDR_GPIO_PULL__Pin_Pos      (0UL)
#define MDR_GPIO_PULL__Pin_Msk      (0x1UL)

typedef struct {
      __IOM MDR_OnOff  Pin_0      : 1;            /*!< [0..0] Enable Digital mode                                                */
      __IOM MDR_OnOff  Pin_1      : 1;            /*!< [1..1] Enable Digital mode                                                */
      __IOM MDR_OnOff  Pin_2      : 1;            /*!< [2..2] Enable Digital mode                                                */
      __IOM MDR_OnOff  Pin_3      : 1;            /*!< [3..3] Enable Digital mode                                                */
      __IOM MDR_OnOff  Pin_4      : 1;            /*!< [4..4] Enable Digital mode                                                */
      __IOM MDR_OnOff  Pin_5      : 1;            /*!< [5..5] Enable Digital mode                                                */
      __IOM MDR_OnOff  Pin_6      : 1;            /*!< [6..6] Enable Digital mode                                                */
      __IOM MDR_OnOff  Pin_7      : 1;            /*!< [7..7] Enable Digital mode                                                */
      __IOM MDR_OnOff  Pin_8      : 1;            /*!< [8..8] Enable Digital mode                                                */
      __IOM MDR_OnOff  Pin_9      : 1;            /*!< [9..9] Enable Digital mode                                                */
      __IOM MDR_OnOff  Pin_10     : 1;            /*!< [10..10] Enable Digital mode                                              */
      __IOM MDR_OnOff  Pin_11     : 1;            /*!< [11..11] Enable Digital mode                                              */
      __IOM MDR_OnOff  Pin_12     : 1;            /*!< [12..12] Enable Digital mode                                              */
      __IOM MDR_OnOff  Pin_13     : 1;            /*!< [13..13] Enable Digital mode                                              */
      __IOM MDR_OnOff  Pin_14     : 1;            /*!< [14..14] Enable Digital mode                                              */
      __IOM MDR_OnOff  Pin_15     : 1;            /*!< [15..15] Enable Digital mode                                              */
      __IOM MDR_OnOff  Pin_16     : 1;
      __IOM MDR_OnOff  Pin_17     : 1;
      __IOM MDR_OnOff  Pin_18     : 1;
      __IOM MDR_OnOff  Pin_19     : 1;
      __IOM MDR_OnOff  Pin_20     : 1; 
      __IOM MDR_OnOff  Pin_21     : 1; 
      __IOM MDR_OnOff  Pin_22     : 1; 
      __IOM MDR_OnOff  Pin_23     : 1; 
      __IOM MDR_OnOff  Pin_24     : 1; 
      __IOM MDR_OnOff  Pin_25     : 1; 
      __IOM MDR_OnOff  Pin_26     : 1;
      __IOM MDR_OnOff  Pin_27     : 1;
      __IOM MDR_OnOff  Pin_28     : 1;
      __IOM MDR_OnOff  Pin_29     : 1;
      __IOM MDR_OnOff  Pin_30     : 1; 
      __IOM MDR_OnOff  Pin_31     : 1; 
} MDR_GPIO_SEL_Bits;


/* ==========================================================  PD  =========================================================== */
typedef enum {
      MDR_PIN_PullPush             = 0,
      MDR_PIN_OpenDrain            = 1
} MDR_PIN_PD;

typedef struct {
      __IOM MDR_PIN_PD  DrvPin_0 : 1;          /*!< [0..0] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  DrvPin_1 : 1;          /*!< [1..1] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  DrvPin_2 : 1;          /*!< [2..2] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  DrvPin_3 : 1;          /*!< [3..3] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  DrvPin_4 : 1;          /*!< [4..4] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  DrvPin_5 : 1;          /*!< [5..5] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  DrvPin_6 : 1;          /*!< [6..6] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  DrvPin_7 : 1;          /*!< [7..7] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  DrvPin_8 : 1;          /*!< [8..8] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  DrvPin_9 : 1;          /*!< [9..9] Driver mode for pin                                                */
      __IOM MDR_PIN_PD  DrvPin_10 : 1;         /*!< [10..10] Driver mode for pin                                              */
      __IOM MDR_PIN_PD  DrvPin_11 : 1;         /*!< [11..11] Driver mode for pin                                              */
      __IOM MDR_PIN_PD  DrvPin_12 : 1;         /*!< [12..12] Driver mode for pin                                              */
      __IOM MDR_PIN_PD  DrvPin_13 : 1;         /*!< [13..13] Driver mode for pin                                              */
      __IOM MDR_PIN_PD  DrvPin_14 : 1;         /*!< [14..14] Driver mode for pin                                              */
      __IOM MDR_PIN_PD  DrvPin_15 : 1;         /*!< [15..15] Driver mode for pin                                              */
      __IOM MDR_PIN_PD  DrvPin_16 : 1;
      __IOM MDR_PIN_PD  DrvPin_17 : 1;
      __IOM MDR_PIN_PD  DrvPin_18 : 1;
      __IOM MDR_PIN_PD  DrvPin_19 : 1;
      __IOM MDR_PIN_PD  DrvPin_20 : 1;
      __IOM MDR_PIN_PD  DrvPin_21 : 1;
      __IOM MDR_PIN_PD  DrvPin_22 : 1;
      __IOM MDR_PIN_PD  DrvPin_23 : 1;
      __IOM MDR_PIN_PD  DrvPin_24 : 1;
      __IOM MDR_PIN_PD  DrvPin_25 : 1;
      __IOM MDR_PIN_PD  DrvPin_26 : 1;
      __IOM MDR_PIN_PD  DrvPin_27 : 1;
      __IOM MDR_PIN_PD  DrvPin_28 : 1;
      __IOM MDR_PIN_PD  DrvPin_29 : 1;
      __IOM MDR_PIN_PD  DrvPin_30 : 1;
      __IOM MDR_PIN_PD  DrvPin_31 : 1;
} MDR_GPIO_PD_Bits;

#define MDR_GPIO_PD__Pin_Pos         (0UL)
#define MDR_GPIO_PD__Pin_Msk         (0x1UL)


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
} MDR_GPIO_PWR0_Bits;

typedef struct {
      __IOM MDR_PIN_PWR  Pin_16     : 2;
      __IOM MDR_PIN_PWR  Pin_17     : 2;
      __IOM MDR_PIN_PWR  Pin_18     : 2;
      __IOM MDR_PIN_PWR  Pin_19     : 2;
      __IOM MDR_PIN_PWR  Pin_20     : 2;
      __IOM MDR_PIN_PWR  Pin_21     : 2;
      __IOM MDR_PIN_PWR  Pin_22     : 2;
      __IOM MDR_PIN_PWR  Pin_23     : 2;
      __IOM MDR_PIN_PWR  Pin_24     : 2;
      __IOM MDR_PIN_PWR  Pin_25     : 2;
      __IOM MDR_PIN_PWR  Pin_26     : 2;
      __IOM MDR_PIN_PWR  Pin_27     : 2;
      __IOM MDR_PIN_PWR  Pin_28     : 2;
      __IOM MDR_PIN_PWR  Pin_29     : 2;
      __IOM MDR_PIN_PWR  Pin_30     : 2;
      __IOM MDR_PIN_PWR  Pin_31     : 2;
} MDR_GPIO_PWR1_Bits;


#define MDR_GPIO_PWR__Pin_Pos            (0UL)
#define MDR_GPIO_PWR__Pin_Msk            (0x3UL)


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
  __IOM uint32_t  KEY;                                 /*!< (@ 0x00000000) Key lock Register                                          */
  union {
    __IOM uint32_t        RXTX;                        /*!< (@ 0x00000004) GPIO Pin Data Register                                     */
    MDR_GPIO_DATA_Bits    RXTX_b;
  } ;  
  union {
    __IOM uint32_t        RXTX_Set;                    /*!< (@ 0x00000008) Set RXTX Bits                                              */
    MDR_GPIO_DATA_Bits    RXTX_Set_b;
  } ;
  union {
    __IOM uint32_t        RXTX_Clr;                    /*!< (@ 0x0000000C) Clear RXTX Bits                                            */
    MDR_GPIO_DATA_Bits    RXTX_Clr_b;
  } ;    
  union {
    __IOM uint32_t        OE_Set;                      /*!< (@ 0x00000010) Set OE Pins                                                */
    MDR_GPIO_IO_Bits      OE_Set_b;
  } ;  
  union {
    __IOM uint32_t        OE_Clr;                      /*!< (@ 0x00000014) Clear OE Pins                                              */
    MDR_GPIO_IO_Bits      OE_Clr_b;
  } ;   
  union {
    __IOM  uint32_t       FUNC0_Set;                   /*!< (@ 0x00000018) Set FUNC0 bits  0..7                                       */
    MDR_GPIO_FUNC0_Bits   FUNC0_Set_b;
  } ;  
  union {
    __IOM  uint32_t       FUNC1_Set;                   /*!< (@ 0x0000001C) Set FUNC1 bits  8..15                                      */
    MDR_GPIO_FUNC1_Bits   FUNC1_Set_b;
  } ;    
  union {
    __IOM  uint32_t       FUNC2_Set;                   /*!< (@ 0x00000020) Set FUNC2 bits  16..23                                     */
    MDR_GPIO_FUNC2_Bits   FUNC2_Set_b;
  } ;  
  union {
    __IOM  uint32_t       FUNC3_Set;                   /*!< (@ 0x00000024) Set FUNC3 bits  24..31                                     */
    MDR_GPIO_FUNC3_Bits   FUNC3_Set_b;
  } ;      
  
  union {
    __IOM  uint32_t       FUNC0_Clr;                   /*!< (@ 0x00000028) Clr FUNC0 bits  0..7                                       */
    MDR_GPIO_FUNC0_Bits   FUNC0_Clr_b;
  } ;  
  union {
    __IOM  uint32_t       FUNC1_Clr;                   /*!< (@ 0x0000002C) Clr FUNC1 bits  8..15                                      */
    MDR_GPIO_FUNC1_Bits   FUNC1_Clr_b;
  } ;    
  union {
    __IOM  uint32_t       FUNC2_Clr;                   /*!< (@ 0x00000030) Clr FUNC2 bits  16..23                                     */
    MDR_GPIO_FUNC2_Bits   FUNC2_Clr_b;
  } ;  
  union {
    __IOM  uint32_t       FUNC3_Clr;                   /*!< (@ 0x00000034) Clr FUNC3 bits  24..31                                     */
    MDR_GPIO_FUNC3_Bits   FUNC3_Clr_b;
  } ;        
  union {
    __IOM uint32_t        ANALOG_Set;                  /*!< (@ 0x00000038) Set to DIGITAL mode                                        */
    MDR_GPIO_ANALOG_Bits  ANALOG_Set_b;
  } ;  
  union {
    __IOM uint32_t        ANALOG_Clr;                  /*!< (@ 0x0000003C) Clear to ANALOG mode                                        */
    MDR_GPIO_ANALOG_Bits  ANALOG_Clr_b;
  } ;      
  union {
    __IOM uint32_t        PULLUP_Set;                  /*!< (@ 0x00000040) Set PULLUP bits                                            */
    MDR_GPIO_SEL_Bits     PULLUP_Set_b;
  } ;  
  union {
    __IOM uint32_t        PULLUP_Clr;                  /*!< (@ 0x00000044) Clear PULLUP bits                                          */
    MDR_GPIO_SEL_Bits     PULLUP_Clr_b;
  } ;    
  union {
    __IOM uint32_t        PULLDOWN_Set;                /*!< (@ 0x00000048) Set PullDOWN bits                                        */
    MDR_GPIO_SEL_Bits     PULLDOWN_Set_b;
  } ;    
  union {
    __IOM uint32_t        PULLDOWN_Clr;                /*!< (@ 0x0000004C) Clear PULLDOWN bits                                        */
    MDR_GPIO_SEL_Bits     PULLDOWN_Clr_b;
  } ;      
  union {
    __IOM uint32_t        PD_Set;                      /*!< (@ 0x00000050) Set PD bits                                                */
    MDR_GPIO_PD_Bits      PD_Set_b;
  } ;  
  union {
    __IOM uint32_t        PD_Clr;                      /*!< (@ 0x00000054) Clear PD bits                                              */
    MDR_GPIO_PD_Bits      PD_Clr_b;
  } ;     
  union {
    __IOM uint32_t        PWR0_Set;                    /*!< (@ 0x00000058) Set PWR0 bits                                              */
    MDR_GPIO_PWR0_Bits    PWR0_Set_b;
  } ;  
  union {
    __IOM uint32_t        PWR1_Set;                    /*!< (@ 0x0000005C) Set PWR1 bits                                              */
    MDR_GPIO_PWR1_Bits    PWR1_Set_b;
  } ;
  union {
    __IOM uint32_t        PWR0_Clr;                    /*!< (@ 0x00000060) Clear PWR0 bits                                            */
    MDR_GPIO_PWR0_Bits    PWR0_Clr_b;
  } ;  
  union {
    __IOM uint32_t        PWR1_Clr;                    /*!< (@ 0x00000064) Clear PWR1 bits                                            */
    MDR_GPIO_PWR1_Bits    PWR1_Clr_b;
  } ;  
  union {
    __IOM uint32_t        CL_Set;                      /*!< (@ 0x00000068) Set CurrentLim bits                                        */
    MDR_GPIO_SEL_Bits     CL_Set_b;
  } ;
  union {
    __IOM uint32_t        CL_Clr;                      /*!< (@ 0x0000006C) Clear CurrentLim bits                                      */
    MDR_GPIO_SEL_Bits     CL_Clr_b;
  } ;  
  union {
    __IOM uint32_t        IE_Set;                      /*!< (@ 0x00000070) Set IRQ Enable bits                                        */
    MDR_GPIO_SEL_Bits     IE_Set_b;
  } ;
  union {
    __IOM uint32_t        IE_Clr;                      /*!< (@ 0x00000074) Clear IRQ Enable bits                                      */
    MDR_GPIO_SEL_Bits     IE_Clr_b;
  } ;
  union {
    __IOM uint32_t        IT_Set;                      /*!< (@ 0x00000070) Set IRQ Acive Pin Level to High                            */
    MDR_GPIO_SEL_Bits     IT_Set_b;
  } ;
  union {
    __IOM uint32_t        IT_Clr;                      /*!< (@ 0x00000074) Set IRQ Acive Pin Level to Low                             */
    MDR_GPIO_SEL_Bits     IT_Clr_b;
  } ;
  union {
    __IOM uint32_t        IR_Set;                      /*!< (@ 0x00000070) Activate IRQ Request                                       */
    MDR_GPIO_SEL_Bits     IR_Set_b;
  } ;
  union {
    __IOM uint32_t        IR_Clr;                      /*!< (@ 0x00000074) Deactivate IRQ Request                                     */
    MDR_GPIO_SEL_Bits     IR_Clr_b;
  } ;
  union {
    __IOM uint32_t        HCUR;                        /*!< (@ 0x00000088) Pins' Overcurrent Status                                   */
    MDR_GPIO_SEL_Bits     HCUR_b;
  } ; 
} MDR_PORT_Type;


typedef struct {
    uint32_t        clrPins;
    uint32_t        clrFUNC_0_7;
    uint32_t        clrFUNC_8_15;
    uint32_t        clrFUNC_16_23;
    uint32_t        clrFUNC_24_31;
    uint32_t        clrPWR_0_15;
    uint32_t        clrPWR_16_31;
} MDR_GPIO_ClearCfg;

typedef struct {               
    uint32_t        RXTX;        
    uint32_t        OE;          
    uint32_t        FUNC_0_7;  
    uint32_t        FUNC_8_15; 
    uint32_t        FUNC_16_23;
    uint32_t        FUNC_24_31;
    uint32_t        ANALOG;    
    uint32_t        PULL_Up;   
    uint32_t        PULL_Down; 
    uint32_t        PD;        
    uint32_t        PWR_0_15;  
    uint32_t        PWR_16_31; 
} MDR_GPIO_SetCfg;


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

#endif  //_MDR_GPIO_VE8x_DEFS_H
