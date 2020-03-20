#ifndef _MDR_BKP_DEFS_H
#define _MDR_BKP_DEFS_H


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

#define MDR_CAN_BUF_COUNT   32


/* =========================================================================================================================== */
/* ================                                         MDR_CAN1                                          ================ */
/* =========================================================================================================================== */

/* ========================================================  CONTROL  ======================================================== */

typedef struct {
  __IOM MDR_OnOff CAN_EN     : 1;            /*!< [0..0] Enable CAN                                                         */
  __IOM MDR_OnOff ROM        : 1;            /*!< [1..1] Read Only Mode                                                     */
  __IOM MDR_OnOff STM        : 1;            /*!< [2..2] Self Test Mode                                                     */
  __IOM MDR_OnOff SAP        : 1;            /*!< [3..3] Send Ack for Own Packets                                           */
  __IOM MDR_OnOff ROP        : 1;            /*!< [4..4] Receive Own Packets                                                */
  __IM  uint32_t             : 27;
} MDR_CAN_CONTROL_Bits;

#define MDR_CAN_CONTROL_CAN_EN_Pos       (0UL)                     /*!< MDR_CAN1 CONTROL: CAN_EN (Bit 0)                      */
#define MDR_CAN_CONTROL_CAN_EN_Msk       (0x1UL)                   /*!< MDR_CAN1 CONTROL: CAN_EN (Bitfield-Mask: 0x01)        */
#define MDR_CAN_CONTROL_ROM_Pos          (1UL)                     /*!< MDR_CAN1 CONTROL: ROM (Bit 1)                         */
#define MDR_CAN_CONTROL_ROM_Msk          (0x2UL)                   /*!< MDR_CAN1 CONTROL: ROM (Bitfield-Mask: 0x01)           */
#define MDR_CAN_CONTROL_STM_Pos          (2UL)                     /*!< MDR_CAN1 CONTROL: STM (Bit 2)                         */
#define MDR_CAN_CONTROL_STM_Msk          (0x4UL)                   /*!< MDR_CAN1 CONTROL: STM (Bitfield-Mask: 0x01)           */
#define MDR_CAN_CONTROL_SAP_Pos          (3UL)                     /*!< MDR_CAN1 CONTROL: SAP (Bit 3)                         */
#define MDR_CAN_CONTROL_SAP_Msk          (0x8UL)                   /*!< MDR_CAN1 CONTROL: SAP (Bitfield-Mask: 0x01)           */
#define MDR_CAN_CONTROL_ROP_Pos          (4UL)                     /*!< MDR_CAN1 CONTROL: ROP (Bit 4)                         */
#define MDR_CAN_CONTROL_ROP_Msk          (0x10UL)                  /*!< MDR_CAN1 CONTROL: ROP (Bitfield-Mask: 0x01)           */

/* ========================================================  STATUS  ========================================================= */

typedef enum {                                  /*!< MDR_CAN1_STATUS_ERR_Status                                                */
  MDR_CAN_ERR_Active    = 0,     /*!< Active : Active mode                                                      */
  MDR_CAN_ERR_Passive   = 1,     /*!< Passive : Pasiive error mode                                              */
  MDR_CAN_ERR_BusOff    = 2,     /*!< BusOff : Bus Disable                                                      */
} MDR_CAN_ERR_STATUS;

typedef struct {
  __IOM MDR_OnOff             RX_Ready    : 1;            /*!< [0..0] Some Buff Data received                                            */
  __IOM MDR_OnOff             TX_Ready    : 1;            /*!< [1..1] Some buff has data to send                                         */
  __IOM MDR_OnOff             ERR_Over    : 1;            /*!< [2..2] TEC o REC exceeds ERROR_MAX                                        */
  __IOM MDR_OnOff             ERR_Bit     : 1;            /*!< [3..3] Error while TX some bit                                            */
  __IOM MDR_OnOff             ERR_StuffBit : 1;          /*!< [4..4] Error in Staff Bit                                                 */
  __IOM MDR_OnOff             ERR_CRC     : 1;            /*!< [5..5] CRC Error                                                          */
  __IOM MDR_OnOff             ERR_FRAME   : 1;            /*!< [6..6] Wrong Frame structure                                              */
  __IOM MDR_OnOff             ERR_ACK     : 1;            /*!< [7..7] Acknowledge error                                                  */
  __IOM MDR_OnOff             ID_Lower    : 1;            /*!< [8..8] Arbitrage failure                                                  */
  __IOM MDR_CAN_ERR_STATUS    ERR_Status  : 2;            /*!< [10..9] Eror status                                                       */
  __IOM MDR_OnOff             RX_ERR_CNT8 : 1;           /*!< [11..11] REC > 255, BusOff                                                */
  __IOM MDR_OnOff             TX_ERR_CNT8 : 1;           /*!< [12..12] TEC > 255, BusOff                                                */
  __IM  uint32_t                          : 3;
  __IOM uint8_t               RX_ERR_CNT  : 8;            /*!< [23..16] Rx Error Counter                                                 */
  __IOM uint8_t               TX_ERR_CNT  : 8;            /*!< [31..24] Tx Error Counter                                                 */
} MDR_CAN_STATUS_Bits;


#define MDR_CAN_STATUS_RX_Ready_Pos      (0UL)                     /*!< MDR_CAN1 STATUS: RX_Ready (Bit 0)                     */
#define MDR_CAN_STATUS_RX_Ready_Msk      (0x1UL)                   /*!< MDR_CAN1 STATUS: RX_Ready (Bitfield-Mask: 0x01)       */
#define MDR_CAN_STATUS_TX_Ready_Pos      (1UL)                     /*!< MDR_CAN1 STATUS: TX_Ready (Bit 1)                     */
#define MDR_CAN_STATUS_TX_Ready_Msk      (0x2UL)                   /*!< MDR_CAN1 STATUS: TX_Ready (Bitfield-Mask: 0x01)       */
#define MDR_CAN_STATUS_ERR_Over_Pos      (2UL)                     /*!< MDR_CAN1 STATUS: ERR_Over (Bit 2)                     */
#define MDR_CAN_STATUS_ERR_Over_Msk      (0x4UL)                   /*!< MDR_CAN1 STATUS: ERR_Over (Bitfield-Mask: 0x01)       */
#define MDR_CAN_STATUS_ERR_Bit_Pos       (3UL)                     /*!< MDR_CAN1 STATUS: ERR_Bit (Bit 3)                      */
#define MDR_CAN_STATUS_ERR_Bit_Msk       (0x8UL)                   /*!< MDR_CAN1 STATUS: ERR_Bit (Bitfield-Mask: 0x01)        */
#define MDR_CAN_STATUS_ERR_StuffBit_Pos  (4UL)                     /*!< MDR_CAN1 STATUS: ERR_StuffBit (Bit 4)                 */
#define MDR_CAN_STATUS_ERR_StuffBit_Msk  (0x10UL)                  /*!< MDR_CAN1 STATUS: ERR_StuffBit (Bitfield-Mask: 0x01)   */
#define MDR_CAN_STATUS_ERR_CRC_Pos       (5UL)                     /*!< MDR_CAN1 STATUS: ERR_CRC (Bit 5)                      */
#define MDR_CAN_STATUS_ERR_CRC_Msk       (0x20UL)                  /*!< MDR_CAN1 STATUS: ERR_CRC (Bitfield-Mask: 0x01)        */
#define MDR_CAN_STATUS_ERR_FRAME_Pos     (6UL)                     /*!< MDR_CAN1 STATUS: ERR_FRAME (Bit 6)                    */
#define MDR_CAN_STATUS_ERR_FRAME_Msk     (0x40UL)                  /*!< MDR_CAN1 STATUS: ERR_FRAME (Bitfield-Mask: 0x01)      */
#define MDR_CAN_STATUS_ERR_ACK_Pos       (7UL)                     /*!< MDR_CAN1 STATUS: ERR_ACK (Bit 7)                      */
#define MDR_CAN_STATUS_ERR_ACK_Msk       (0x80UL)                  /*!< MDR_CAN1 STATUS: ERR_ACK (Bitfield-Mask: 0x01)        */
#define MDR_CAN_STATUS_ID_Lower_Pos      (8UL)                     /*!< MDR_CAN1 STATUS: ID_Lower (Bit 8)                     */
#define MDR_CAN_STATUS_ID_Lower_Msk      (0x100UL)                 /*!< MDR_CAN1 STATUS: ID_Lower (Bitfield-Mask: 0x01)       */
#define MDR_CAN_STATUS_ERR_Status_Pos    (9UL)                     /*!< MDR_CAN1 STATUS: ERR_Status (Bit 9)                   */
#define MDR_CAN_STATUS_ERR_Status_Msk    (0x600UL)                 /*!< MDR_CAN1 STATUS: ERR_Status (Bitfield-Mask: 0x03)     */
#define MDR_CAN_STATUS_RX_ERR_CNT8_Pos   (11UL)                    /*!< MDR_CAN1 STATUS: RX_ERR_CNT8 (Bit 11)                 */
#define MDR_CAN_STATUS_RX_ERR_CNT8_Msk   (0x800UL)                 /*!< MDR_CAN1 STATUS: RX_ERR_CNT8 (Bitfield-Mask: 0x01)    */
#define MDR_CAN_STATUS_TX_ERR_CNT8_Pos   (12UL)                    /*!< MDR_CAN1 STATUS: TX_ERR_CNT8 (Bit 12)                 */
#define MDR_CAN_STATUS_TX_ERR_CNT8_Msk   (0x1000UL)                /*!< MDR_CAN1 STATUS: TX_ERR_CNT8 (Bitfield-Mask: 0x01)    */
#define MDR_CAN_STATUS_RX_ERR_CNT_Pos    (16UL)                    /*!< MDR_CAN1 STATUS: RX_ERR_CNT (Bit 16)                  */
#define MDR_CAN_STATUS_RX_ERR_CNT_Msk    (0xff0000UL)              /*!< MDR_CAN1 STATUS: RX_ERR_CNT (Bitfield-Mask: 0xff)     */
#define MDR_CAN_STATUS_TX_ERR_CNT_Pos    (24UL)                    /*!< MDR_CAN1 STATUS: TX_ERR_CNT (Bit 24)                  */
#define MDR_CAN_STATUS_TX_ERR_CNT_Msk    (0xff000000UL)            /*!< MDR_CAN1 STATUS: TX_ERR_CNT (Bitfield-Mask: 0xff)     */

/* ========================================================  BITTMNG  ======================================================== */

typedef enum {                             /*!< MDR_CAN1_BITTMNG_PSEG                                                     */
  MDR_CAN_BITTMNG_1TQ             = 0,     /*!< 1TQ : Delay                                                               */
  MDR_CAN_BITTMNG_2TQ             = 1,     /*!< 2TQ : Delay                                                               */
  MDR_CAN_BITTMNG_3TQ             = 2,     /*!< 3TQ : Delay                                                               */
  MDR_CAN_BITTMNG_4TQ             = 3,     /*!< 4TQ : Delay                                                               */
  MDR_CAN_BITTMNG_5TQ             = 4,     /*!< 5TQ : Delay                                                               */
  MDR_CAN_BITTMNG_6TQ             = 5,     /*!< 6TQ : Delay                                                               */
  MDR_CAN_BITTMNG_7TQ             = 6,     /*!< 7TQ : Delay                                                               */
  MDR_CAN_BITTMNG_8TQ             = 7,     /*!< 8TQ : Delay                                                               */
} MDR_CAN_BITTMNG_TQ;

typedef enum {                             /*!< MDR_CAN1_BITTMNG_SJW                                                      */
  MDR_CAN_BITTMNG_SJW_1TQ         = 0,     /*!< 1TQ : Delay                                                               */
  MDR_CAN_BITTMNG_SJW_2TQ         = 1,     /*!< 2TQ : Delay                                                               */
  MDR_CAN_BITTMNG_SJW_3TQ         = 2,     /*!< 3TQ : Delay                                                               */
  MDR_CAN_BITTMNG_SJW_4TQ         = 3,     /*!< 4TQ : Delay                                                               */
} MDR_CAN_BITTMNG_SJW;

typedef struct {
  __IOM uint16_t                  BRP        : 16;           /*!< [15..0] Boud Rate Prescaler to TQ                                         */
  __IOM MDR_CAN_BITTMNG_TQ        PSEG       : 3;            /*!< [18..16] Propagation time in TQ                                           */
  __IOM MDR_CAN_BITTMNG_TQ        SEG1       : 3;            /*!< [21..19] Delay before line sampling                                       */
  __IOM MDR_CAN_BITTMNG_TQ        SEG2       : 3;            /*!< [24..22] Delay after line sampling                                        */
  __IOM MDR_CAN_BITTMNG_SJW       SJW        : 2;            /*!< [26..25] Sync phase deviation                                             */
  __IOM MDR_OnOff                 SB_Triple  : 1;            /*!< [27..27] Line Sampling Count                                              */
  __IM  uint32_t                             : 4;
} MDR_CAN_BITTMNG_Bits;

#define MDR_CAN_BITTMNG_BRP_Pos          (0UL)                     /*!< MDR_CAN1 BITTMNG: BRP (Bit 0)                         */
#define MDR_CAN_BITTMNG_BRP_Msk          (0xffffUL)                /*!< MDR_CAN1 BITTMNG: BRP (Bitfield-Mask: 0xffff)         */
#define MDR_CAN_BITTMNG_PSEG_Pos         (16UL)                    /*!< MDR_CAN1 BITTMNG: PSEG (Bit 16)                       */
#define MDR_CAN_BITTMNG_PSEG_Msk         (0x70000UL)               /*!< MDR_CAN1 BITTMNG: PSEG (Bitfield-Mask: 0x07)          */
#define MDR_CAN_BITTMNG_SEG1_Pos         (19UL)                    /*!< MDR_CAN1 BITTMNG: SEG1 (Bit 19)                       */
#define MDR_CAN_BITTMNG_SEG1_Msk         (0x380000UL)              /*!< MDR_CAN1 BITTMNG: SEG1 (Bitfield-Mask: 0x07)          */
#define MDR_CAN_BITTMNG_SEG2_Pos         (22UL)                    /*!< MDR_CAN1 BITTMNG: SEG2 (Bit 22)                       */
#define MDR_CAN_BITTMNG_SEG2_Msk         (0x1c00000UL)             /*!< MDR_CAN1 BITTMNG: SEG2 (Bitfield-Mask: 0x07)          */
#define MDR_CAN_BITTMNG_SJW_Pos          (25UL)                    /*!< MDR_CAN1 BITTMNG: SJW (Bit 25)                        */
#define MDR_CAN_BITTMNG_SJW_Msk          (0x6000000UL)             /*!< MDR_CAN1 BITTMNG: SJW (Bitfield-Mask: 0x03)           */
#define MDR_CAN_BITTMNG_SB_Pos           (27UL)                    /*!< MDR_CAN1 BITTMNG: SB (Bit 27)                         */
#define MDR_CAN_BITTMNG_SB_Msk           (0x8000000UL)             /*!< MDR_CAN1 BITTMNG: SB (Bitfield-Mask: 0x01)            */

/* ========================================================  INT_EN  ========================================================= */
typedef struct {
  __IOM MDR_OnOff                    GLB_IntEn    : 1;            /*!< [0..0] IRQ Enable Global                                                  */
  __IOM MDR_OnOff                    RX_IntEn     : 1;            /*!< [1..1] Enable IRQ on RX                                                   */
  __IOM MDR_OnOff                    TX_IntEn     : 1;            /*!< [2..2] Enable IRQ on TX                                                   */
  __IOM MDR_OnOff                    ERR_IntEn    : 1;            /*!< [3..3] Enable IRQ on Error                                                */
  __IOM MDR_OnOff                    ErrOV_IntEn  : 1;            /*!< [4..4] Enable IRQ of Error Over                                           */
  __IM  uint32_t                                  : 27;
} MDR_CAN_INT_EN_Bits;

#define MDR_CAN_INT_EN_GLB_IntEn_Pos     (0UL)                     /*!< MDR_CAN1 INT_EN: GLB_IntEn (Bit 0)                    */
#define MDR_CAN_INT_EN_GLB_IntEn_Msk     (0x1UL)                   /*!< MDR_CAN1 INT_EN: GLB_IntEn (Bitfield-Mask: 0x01)      */
#define MDR_CAN_INT_EN_RX_IntEn_Pos      (1UL)                     /*!< MDR_CAN1 INT_EN: RX_IntEn (Bit 1)                     */
#define MDR_CAN_INT_EN_RX_IntEn_Msk      (0x2UL)                   /*!< MDR_CAN1 INT_EN: RX_IntEn (Bitfield-Mask: 0x01)       */
#define MDR_CAN_INT_EN_TX_IntEn_Pos      (2UL)                     /*!< MDR_CAN1 INT_EN: TX_IntEn (Bit 2)                     */
#define MDR_CAN_INT_EN_TX_IntEn_Msk      (0x4UL)                   /*!< MDR_CAN1 INT_EN: TX_IntEn (Bitfield-Mask: 0x01)       */
#define MDR_CAN_INT_EN_ERR_IntEn_Pos     (3UL)                     /*!< MDR_CAN1 INT_EN: ERR_IntEn (Bit 3)                    */
#define MDR_CAN_INT_EN_ERR_IntEn_Msk     (0x8UL)                   /*!< MDR_CAN1 INT_EN: ERR_IntEn (Bitfield-Mask: 0x01)      */
#define MDR_CAN_INT_EN_ErrOV_IntEn_Pos   (4UL)                     /*!< MDR_CAN1 INT_EN: ErrOV_IntEn (Bit 4)                  */
#define MDR_CAN_INT_EN_ErrOV_IntEn_Msk   (0x10UL)                  /*!< MDR_CAN1 INT_EN: ErrOV_IntEn (Bitfield-Mask: 0x01)    */

/* =========================================================  OVER  ========================================================== */
typedef struct {
  __IOM uint32_t ERROR_MAX  : 8;            /*!< [7..0] Level of TEC or REC errors to OverIRQ                              */
  __IM  uint32_t            : 24;
} MDR_CAN_OVER_Bits;


#define MDR_CAN_OVER_ERROR_MAX_Pos       (0UL)                     /*!< MDR_CAN1 OVER: ERROR_MAX (Bit 0)                      */
#define MDR_CAN_OVER_ERROR_MAX_Msk       (0xffUL)                  /*!< MDR_CAN1 OVER: ERROR_MAX (Bitfield-Mask: 0xff)        */

/* =========================================================  RX_ID, TX_ID  ========================================================= */

typedef struct {
  __IOM uint32_t EID        : 18;           /*!< [17..0] Extended frame ID                                                 */
  __IOM uint32_t SID        : 11;           /*!< [28..18] Standard frame ID                                                */
  __IM  uint32_t            : 3; 
} MDR_CAN_ID_Bits;

#define MDR_CAN_ID_EID_Pos            (0UL)                     /*!< MDR_CAN1 RX_ID: EID (Bit 0)                           */
#define MDR_CAN_ID_EID_Msk            (0x3ffffUL)               /*!< MDR_CAN1 RX_ID: EID (Bitfield-Mask: 0x3ffff)          */
#define MDR_CAN_ID_SID_Pos            (18UL)                    /*!< MDR_CAN1 RX_ID: SID (Bit 18)                          */
#define MDR_CAN_ID_SID_Msk            (0x1ffc0000UL)            /*!< MDR_CAN1 RX_ID: SID (Bitfield-Mask: 0x7ff)            */

/* ========================================================  RX_DLC, TX_DLC  ========================================================= */

typedef enum {                         /*!< MDR_CAN1_BUF_DLC_IDE                                                      */
  MDR_CAN_IDE_Standard        = 0,     /*!< Standard : Standard frame                                                 */
  MDR_CAN_IDE_Extended        = 1,     /*!< Extended : Extended frame                                                 */
} MDR_CAN_IDE;

typedef enum {                         /*!< MDR_CAN1_BUF_DLC_DLC                                                      */
  MDR_CAN_DLC_NoData         = 0,      /*!< NoData : Normal Operation                                                 */
  MDR_CAN_DLC_Bytes1         = 1,      /*!< Bytes_1 : Byte Count                                                      */
  MDR_CAN_DLC_Bytes2         = 2,      /*!< Bytes_2 : Byte Count                                                      */
  MDR_CAN_DLC_Bytes3         = 3,      /*!< Bytes_3 : Byte Count                                                      */
  MDR_CAN_DLC_Bytes4         = 4,      /*!< Bytes_4 : Byte Count                                                      */
  MDR_CAN_DLC_Bytes5         = 5,      /*!< Bytes_5 : Byte Count                                                      */
  MDR_CAN_DLC_Bytes6         = 6,      /*!< Bytes_6 : Byte Count                                                      */
  MDR_CAN_DLC_Bytes7         = 7,      /*!< Bytes_7 : Byte Count                                                      */
  MDR_CAN_DLC_Bytes8         = 8,      /*!< Bytes_8 : Byte Count                                                      */
} MDR_CAN_DLC;                         


typedef struct {
  __IOM MDR_CAN_DLC         DLC : 4;            /*!< [3..0] Data Length Code                                                   */
  __IM  uint32_t                : 4;
  __IOM MDR_OnOff           RTR : 1;            /*!< [8..8] Remote transmission Request                                        */
  __IOM uint32_t            R1  : 1;            /*!< [9..9] Reserved bit R1                                                    */
  __IOM uint32_t            R0  : 1;            /*!< [10..10] Reserved bit R0                                                  */
  __IOM uint32_t            SRR : 1;            /*!< [11..11] Substitute Remote Request                                        */
  __IOM MDR_CAN_IDE         IDE : 1;            /*!< [12..12] Frame format                                                     */
  __IM  uint32_t                : 19; 
} MDR_CAN_DLC_Bits;

#define MDR_CAN_DLC_DLC_Pos           (0UL)                     /*!< MDR_CAN1 RX_DLC: DLC (Bit 0)                          */
#define MDR_CAN_DLC_DLC_Msk           (0xfUL)                   /*!< MDR_CAN1 RX_DLC: DLC (Bitfield-Mask: 0x0f)            */
#define MDR_CAN_DLC_RTR_Pos           (8UL)                     /*!< MDR_CAN1 RX_DLC: RTR (Bit 8)                          */
#define MDR_CAN_DLC_RTR_Msk           (0x100UL)                 /*!< MDR_CAN1 RX_DLC: RTR (Bitfield-Mask: 0x01)            */
#define MDR_CAN_DLC_R1_Pos            (9UL)                     /*!< MDR_CAN1 RX_DLC: R1 (Bit 9)                           */
#define MDR_CAN_DLC_R1_Msk            (0x200UL)                 /*!< MDR_CAN1 RX_DLC: R1 (Bitfield-Mask: 0x01)             */
#define MDR_CAN_DLC_R0_Pos            (10UL)                    /*!< MDR_CAN1 RX_DLC: R0 (Bit 10)                          */
#define MDR_CAN_DLC_R0_Msk            (0x400UL)                 /*!< MDR_CAN1 RX_DLC: R0 (Bitfield-Mask: 0x01)             */
#define MDR_CAN_DLC_SRR_Pos           (11UL)                    /*!< MDR_CAN1 RX_DLC: SRR (Bit 11)                         */
#define MDR_CAN_DLC_SRR_Msk           (0x800UL)                 /*!< MDR_CAN1 RX_DLC: SRR (Bitfield-Mask: 0x01)            */
#define MDR_CAN_DLC_IDE_Pos           (12UL)                    /*!< MDR_CAN1 RX_DLC: IDE (Bit 12)                         */
#define MDR_CAN_DLC_IDE_Msk           (0x1000UL)                /*!< MDR_CAN1 RX_DLC: IDE (Bitfield-Mask: 0x01)            */


#define MDR_CAN_DLC_STD_SEL      (MDR_CAN_DLC_R1_Msk | MDR_CAN_DLC_SRR_Msk)
#define MDR_CAN_DLC_EXT_SEL      (MDR_CAN_DLC_R1_Msk | MDR_CAN_DLC_SRR_Msk | MDR_CAN_DLC_IDE_Msk)


/* ======================================================= RX_DATAL, TX_DATAL  ======================================================== */

typedef struct {
      __IOM uint32_t DB0        : 8;            /*!< [7..0] Byte 0                                                             */
      __IOM uint32_t DB1        : 8;            /*!< [15..8] Byte 1                                                            */
      __IOM uint32_t DB2        : 8;            /*!< [23..16] Byte 2                                                           */
      __IOM uint32_t DB3        : 8;            /*!< [31..24] Byte 3                                                           */
} MDR_CAN_DATAL_Bits;

#define MDR_CAN_DATAL_DB0_Pos         (0UL)                     /*!< MDR_CAN1 TX_DATAL: DB0 (Bit 0)                        */
#define MDR_CAN_DATAL_DB0_Msk         (0xffUL)                  /*!< MDR_CAN1 TX_DATAL: DB0 (Bitfield-Mask: 0xff)          */
#define MDR_CAN_DATAL_DB1_Pos         (8UL)                     /*!< MDR_CAN1 TX_DATAL: DB1 (Bit 8)                        */
#define MDR_CAN_DATAL_DB1_Msk         (0xff00UL)                /*!< MDR_CAN1 TX_DATAL: DB1 (Bitfield-Mask: 0xff)          */
#define MDR_CAN_DATAL_DB2_Pos         (16UL)                    /*!< MDR_CAN1 TX_DATAL: DB2 (Bit 16)                       */
#define MDR_CAN_DATAL_DB2_Msk         (0xff0000UL)              /*!< MDR_CAN1 TX_DATAL: DB2 (Bitfield-Mask: 0xff)          */
#define MDR_CAN_DATAL_DB3_Pos         (24UL)                    /*!< MDR_CAN1 TX_DATAL: DB3 (Bit 24)                       */
#define MDR_CAN_DATAL_DB3_Msk         (0xff000000UL)            /*!< MDR_CAN1 TX_DATAL: DB3 (Bitfield-Mask: 0xff)          */

/* ====================================================== RX_DATAH, TX_DATAH  ======================================================== */
typedef struct {
      __IOM uint32_t DB4        : 8;            /*!< [7..0] Byte 0                                                             */
      __IOM uint32_t DB5        : 8;            /*!< [15..8] Byte 1                                                            */
      __IOM uint32_t DB6        : 8;            /*!< [23..16] Byte 2                                                           */
      __IOM uint32_t DB7        : 8;            /*!< [31..24] Byte 3                                                           */
} MDR_CAN_DATAH_Bits;

#define MDR_CAN_DATAH_DB4_Pos         (0UL)                     /*!< MDR_CAN1 TX_DATAH: DB4 (Bit 0)                        */
#define MDR_CAN_DATAH_DB4_Msk         (0xffUL)                  /*!< MDR_CAN1 TX_DATAH: DB4 (Bitfield-Mask: 0xff)          */
#define MDR_CAN_DATAH_DB5_Pos         (8UL)                     /*!< MDR_CAN1 TX_DATAH: DB5 (Bit 8)                        */
#define MDR_CAN_DATAH_DB5_Msk         (0xff00UL)                /*!< MDR_CAN1 TX_DATAH: DB5 (Bitfield-Mask: 0xff)          */
#define MDR_CAN_DATAH_DB6_Pos         (16UL)                    /*!< MDR_CAN1 TX_DATAH: DB6 (Bit 16)                       */
#define MDR_CAN_DATAH_DB6_Msk         (0xff0000UL)              /*!< MDR_CAN1 TX_DATAH: DB6 (Bitfield-Mask: 0xff)          */
#define MDR_CAN_DATAH_DB7_Pos         (24UL)                    /*!< MDR_CAN1 TX_DATAH: DB7 (Bit 24)                       */
#define MDR_CAN_DATAH_DB7_Msk         (0xff000000UL)            /*!< MDR_CAN1 TX_DATAH: DB7 (Bitfield-Mask: 0xff)          */


/* =======================================================  BUF_CON  ======================================================== */
typedef enum {                                  /*!< MDR_CAN1_BUF_CON_BUF_CON_BUF_CON0_RX_TX                                   */
  MDR_CAN_BUF_DIR_TX = 0,                        /*!< TX : Output buffer                                                       */
  MDR_CAN_BUF_DIR_RX = 1,                        /*!< RX : Input buffer                                                        */
} MDR_CAN_BUF_DIR;

typedef struct {
  __IOM MDR_OnOff         EN         : 1;            /*!< [0..0] Buffer enable                                                      */
  __IOM MDR_CAN_BUF_DIR   RX_TX      : 1;            /*!< [1..1] Buffer Direction                                                   */
  __IOM MDR_OnOff         OVER_EN    : 1;            /*!< [2..2] Overwrite enable                                                   */
  __IOM MDR_OnOff         RTR_EN     : 1;            /*!< [3..3] RTR ACK enable                                                     */
  __IOM MDR_OnOff         PRIOR_OFF  : 1;            /*!< [4..4] Send priority Off                                                  */
  __IOM MDR_OnOff         TX_REQ     : 1;            /*!< [5..5] Request to send                                                    */
  __IOM MDR_OnOff         RX_FULL    : 1;            /*!< [6..6] Has new data                                                       */
  __IOM MDR_OnOff         OVER_WR    : 1;            /*!< [7..7] Data overwritten                                                   */
  __IM  uint32_t                     : 24;
} MDR_CAN_BUF_CON_Bits;

typedef union { //MDR_CAN_BUF_COUNT
  __IOM uint32_t              CTRL;                    /*!< (@ 0x00000040) Buffer control                                             */
  MDR_CAN_BUF_CON_Bits        CTRL_b;    
} MDR_CAN_BUF_CON;

#define MDR_CAN_BUF_CON_EN_Pos           (0UL)                     /*!< MDR_CAN1 BUF_CON: EN (Bit 0)                          */
#define MDR_CAN_BUF_CON_EN_Msk           (0x1UL)                   /*!< MDR_CAN1 BUF_CON: EN (Bitfield-Mask: 0x01)            */
#define MDR_CAN_BUF_CON_RX_Pos           (1UL)                     /*!< MDR_CAN1 BUF_CON: RX_TX (Bit 1)                       */
#define MDR_CAN_BUF_CON_RX_Msk           (0x2UL)                   /*!< MDR_CAN1 BUF_CON: RX_TX (Bitfield-Mask: 0x01)         */
#define MDR_CAN_BUF_CON_OVER_EN_Pos      (2UL)                     /*!< MDR_CAN1 BUF_CON: OVER_EN (Bit 2)                     */
#define MDR_CAN_BUF_CON_OVER_EN_Msk      (0x4UL)                   /*!< MDR_CAN1 BUF_CON: OVER_EN (Bitfield-Mask: 0x01)       */
#define MDR_CAN_BUF_CON_RTR_EN_Pos       (3UL)                     /*!< MDR_CAN1 BUF_CON: RTR_EN (Bit 3)                      */
#define MDR_CAN_BUF_CON_RTR_EN_Msk       (0x8UL)                   /*!< MDR_CAN1 BUF_CON: RTR_EN (Bitfield-Mask: 0x01)        */
#define MDR_CAN_BUF_CON_PRIOR_OFF_Pos    (4UL)                     /*!< MDR_CAN1 BUF_CON: PRIOR_OFF (Bit 4)                   */
#define MDR_CAN_BUF_CON_PRIOR_OFF_Msk    (0x10UL)                  /*!< MDR_CAN1 BUF_CON: PRIOR_OFF (Bitfield-Mask: 0x01)     */
#define MDR_CAN_BUF_CON_TX_REQ_Pos       (5UL)                     /*!< MDR_CAN1 BUF_CON: TX_REQ (Bit 5)                      */
#define MDR_CAN_BUF_CON_TX_REQ_Msk       (0x20UL)                  /*!< MDR_CAN1 BUF_CON: TX_REQ (Bitfield-Mask: 0x01)        */
#define MDR_CAN_BUF_CON_RX_FULL_Pos      (6UL)                     /*!< MDR_CAN1 BUF_CON: RX_FULL (Bit 6)                     */
#define MDR_CAN_BUF_CON_RX_FULL_Msk      (0x40UL)                  /*!< MDR_CAN1 BUF_CON: RX_FULL (Bitfield-Mask: 0x01)       */
#define MDR_CAN_BUF_CON_OVER_WR_Pos      (7UL)                     /*!< MDR_CAN1 BUF_CON: OVER_WR (Bit 7)                     */
#define MDR_CAN_BUF_CON_OVER_WR_Msk      (0x80UL)                  /*!< MDR_CAN1 BUF_CON: OVER_WR (Bitfield-Mask: 0x01)       */

#define MDR_CAN_BUF_CON_TX_Msk           (0x0UL)

/* ==============================================  INT_RX, RX, INT_TX, TX,  ==================================================== */
typedef struct {
  __IOM uint32_t SEL_BUF0 : 1;            /*!< [0..0] Enable Buffs' RX IRQ                                               */
  __IOM uint32_t SEL_BUF1 : 1;            /*!< [1..1] Enable Buffs' RX IRQ                                               */
  __IOM uint32_t SEL_BUF2 : 1;            /*!< [2..2] Enable Buffs' RX IRQ                                               */
  __IOM uint32_t SEL_BUF3 : 1;            /*!< [3..3] Enable Buffs' RX IRQ                                               */
  __IOM uint32_t SEL_BUF4 : 1;            /*!< [4..4] Enable Buffs' RX IRQ                                               */
  __IOM uint32_t SEL_BUF5 : 1;            /*!< [5..5] Enable Buffs' RX IRQ                                               */
  __IOM uint32_t SEL_BUF6 : 1;            /*!< [6..6] Enable Buffs' RX IRQ                                               */
  __IOM uint32_t SEL_BUF7 : 1;            /*!< [7..7] Enable Buffs' RX IRQ                                               */
  __IOM uint32_t SEL_BUF8 : 1;            /*!< [8..8] Enable Buffs' RX IRQ                                               */
  __IOM uint32_t SEL_BUF9 : 1;            /*!< [9..9] Enable Buffs' RX IRQ                                               */
  __IOM uint32_t SEL_BUF10 : 1;           /*!< [10..10] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF11 : 1;           /*!< [11..11] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF12 : 1;           /*!< [12..12] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF13 : 1;           /*!< [13..13] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF14 : 1;           /*!< [14..14] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF15 : 1;           /*!< [15..15] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF16 : 1;           /*!< [16..16] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF17 : 1;           /*!< [17..17] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF18 : 1;           /*!< [18..18] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF19 : 1;           /*!< [19..19] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF20 : 1;           /*!< [20..20] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF21 : 1;           /*!< [21..21] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF22 : 1;           /*!< [22..22] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF23 : 1;           /*!< [23..23] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF24 : 1;           /*!< [24..24] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF25 : 1;           /*!< [25..25] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF26 : 1;           /*!< [26..26] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF27 : 1;           /*!< [27..27] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF28 : 1;           /*!< [28..28] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF29 : 1;           /*!< [29..29] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF30 : 1;           /*!< [30..30] Enable Buffs' RX IRQ                                             */
  __IOM uint32_t SEL_BUF31 : 1;           /*!< [31..31] Enable Buffs' RX IRQ                                             */
} MDR_CAN_SEL_BUF_Bits;

#define MDR_CAN_INT_RX_RX_IRQ_En_Pos     (0UL)                     /*!< MDR_CAN1 INT_RX: RX_IRQ_En (Bit 0)                    */
#define MDR_CAN_INT_RX_RX_IRQ_En_Msk     (0x1UL)                   /*!< MDR_CAN1 INT_RX: RX_IRQ_En (Bitfield-Mask: 0x01)      */


typedef struct {
  union {
    __IOM uint32_t              ID;                       /*!< (@ 0x00000020) Last Received ID                                           */
    MDR_CAN_ID_Bits             ID_b;
  } ;  
  union {
    __IOM uint32_t              DLC;                      /*!< (@ 0x00000024) Last Received ControlField                                 */
    MDR_CAN_DLC_Bits            DLC_b;
  } ;
  union {
    __IOM uint32_t              DATAL;                    /*!< (@ 0x00000028) Received Byte[0]..Byte[3]                                  */
    MDR_CAN_DATAH_Bits          DATAL_b;
  } ;
  union {
    __IOM uint32_t              DATAH;                    /*!< (@ 0x0000002C) Received Byte[4]..Byte[7]                                  */
    MDR_CAN_DATAH_Bits          DATAH_b;
  } ;
} MDR_CAN_BUFFER;                            /*!< Size = 16 (0x10)                                                          */


typedef struct {
  __IOM uint32_t  MASK;                         /*!< (@ 0x00000000) MASK for receiver ID                                       */
  __IOM uint32_t  FILTER;                       /*!< (@ 0x00000004) FILTER for receiver ID                                     */
} MDR_CAN_FILTER_Type;  

    
typedef struct {                                /*!< (@ 0x40090000) MDR_CAN1 Structure                                         */  
  union {
    __IOM uint32_t              CONTROL;                     /*!< (@ 0x00000000) Control register                                           */
    MDR_CAN_CONTROL_Bits        CONTROL_b;
  } ;
  union {
    __IOM uint32_t              STATUS;                      /*!< (@ 0x00000004) STATUS register                                            */
    MDR_CAN_STATUS_Bits         STATUS_b;
  };  
  union {
    __IOM uint32_t              BITTMNG;                     /*!< (@ 0x00000008) Bit Timing register                                        */
    MDR_CAN_BITTMNG_Bits        BITTMNG_b;    
  } ;
  __IM  uint32_t                reserved1;
  union {
    __IOM uint32_t              INT_EN;                      /*!< (@ 0x00000010) IRQ Enable                                                 */
    MDR_CAN_INT_EN_Bits         INT_EN_b;
  } ;
  __IM  uint32_t                reserved2[2];
  union {
    __IOM uint32_t              OVER;                        /*!< (@ 0x0000001C) ERROR_MAX level                                            */
    MDR_CAN_OVER_Bits           OVER_b;
  } ;
  
  MDR_CAN_BUFFER                RX_BUF;
  MDR_CAN_BUFFER                TX_BUF;
  
  MDR_CAN_BUF_CON               BUF_CON[MDR_CAN_BUF_COUNT];  /*!< (@ 0x00000040) Buffer control                                             */
  union {
    __IOM uint32_t              INT_RX;                      /*!< (@ 0x000000C0) Enable Buffs' RX IRQ                                       */
    MDR_CAN_SEL_BUF_Bits        INT_RX_b;
  } ;
  union {
    __IOM uint32_t              RX;                          /*!< (@ 0x000000C4) Buffs' RX_FIFO Full                                        */
    MDR_CAN_SEL_BUF_Bits        RX_b;
  } ;
  union {
    __IOM uint32_t              INT_TX;                      /*!< (@ 0x000000C8) Enable Buffs' TX IRQ                                       */
    MDR_CAN_SEL_BUF_Bits        INT_TX_b;
  } ;
  union {
    __IOM uint32_t              TX;                          /*!< (@ 0x000000CC) TX_nReq buffs' state                                       */
    MDR_CAN_SEL_BUF_Bits        TX_b;
  } ;
  __IM  uint32_t                reserved3[76];
  __IOM MDR_CAN_BUFFER          BUF[MDR_CAN_BUF_COUNT];       /*!< (@ 0x00000200) TX or RX buffer control                                    */
  __IM  uint32_t                reserved4[64];
  __IOM MDR_CAN_FILTER_Type     FILTER[MDR_CAN_BUF_COUNT];    /*!< (@ 0x00000500) Buffer Receive Filters                                     */
} MDR_CAN_Type;                                              /*!< Size = 1536 (0x600)                                                       */


typedef struct {
  MDR_CAN_BUF_CON               CON;
  uint32_t                      reserved1[0x70];   //  (0x200-0x40) / 4
  MDR_CAN_BUFFER                BUF;
  uint32_t                      reserved2[0x80];   //  (0x500-0x300) / 4
  __IOM MDR_CAN_FILTER_Type     FILTER;
} MDR_CAN_BUF_Type;


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

#endif  //_MDR_BKP_DEFS_H
