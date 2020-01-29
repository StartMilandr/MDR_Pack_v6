#ifndef _MDR_ETH_DEFS_H
#define _MDR_ETH_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <MDR_Types.h>
#include <stdint.h>


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


/* =========================================================================================================================== */
/* ================                                         MDR_ETH1                                          ================ */
/* =========================================================================================================================== */


/* =========================================================  R_CFG  ========================================================= */

typedef enum {                                   /*!< MDR_ETH1_R_CFG_EVNT_MODE                                                  */
  MDR_ETH_RCFG_EVENT_FIFO_Empty  = 0,            /*!< FIFO_Empty : FIFO is empty                                                */
  MDR_ETH_RCFG_EVENT_FIFO_AEmpty = 1,            /*!< FIFO_AEmpty : FIFO is 1/32 full                                           */
  MDR_ETH_RCFG_EVENT_FIFO_Half   = 2,            /*!< FIFO_Half : FIFO is 1/2 full                                              */
  MDR_ETH_RCFG_EVENT_FIFO_AFull  = 3,            /*!< FIFO_AFull : FIFO is 31/32 full                                           */
  MDR_ETH_RCFG_EVENT_FIFO_Full   = 4,            /*!< FIFO_Full : FIFO Full                                                     */
  MDR_ETH_RCFG_EVENT_Received    = 5,            /*!< Received : Frame received                                                 */
  MDR_ETH_RCFG_EVENT_Saved       = 6,            /*!< Saved : Frame saved to buff                                               */
  MDR_ETH_RCFG_EVENT_Fault       = 7,            /*!< Fault : Frame in wrong                                                    */
} MDR_ETH_RCFG_EVENT;

typedef enum {                                   /*!< MDR_ETH1_R_CFG_BE                                                         */
  MDR_ETH_CFG_BE_LittleEndian       = 0,         /*!< LittleEndian : Little Endian                                              */
  MDR_ETH_CFG_BE_BigEndian          = 1,         /*!< BigEndian : Big Endian                                                    */
} MDR_ETH_CFG_BE;

typedef struct {
  __IOM MDR_OnOff           MCA_En      : 1;            /*!< [0..0] Accept Multycast frames                                            */
  __IOM MDR_OnOff           BCA_En      : 1;            /*!< [1..1] Accept Broadcast frames                                            */
  __IOM MDR_OnOff           UCA_En      : 1;            /*!< [2..2] Accept Unicast frames                                              */
  __IOM MDR_OnOff           AC_En       : 1;            /*!< [3..3] Accept Any MAC                                                     */
  __IOM MDR_OnOff           EF_En       : 1;            /*!< [4..4] Accept frames with errors                                          */
  __IOM MDR_OnOff           CF_En       : 1;            /*!< [5..5] Accept Control frames                                              */
  __IOM MDR_OnOff           LF_En       : 1;            /*!< [6..6] Accept Long frames                                                 */
  __IOM MDR_OnOff           SF_En       : 1;            /*!< [7..7] Accept Short frames                                                */
  __IOM MDR_ETH_RCFG_EVENT  EVNT_MODE   : 3;            /*!< [10..8] Select signal EVNT1 events                                        */
  __IM  uint16_t                        : 1;
  __IOM MDR_OnOff           MSB_1st     : 1;            /*!< [12..12] Bit order                                                        */
  __IOM MDR_ETH_CFG_BE      BE          : 1;            /*!< [13..13] Byte order                                                       */
  __IM  uint16_t                        : 1;
  __IOM MDR_OnOff           EN          : 1;            /*!< [15..15] Enable Receiver                                                  */
} MDR_ETH_RCfg_Bits;


#define MDR_ETH_RCFG_MCA_En_Pos         (0UL)                     /*!< MDR_ETH1 R_CFG: MCA_En (Bit 0)                        */
#define MDR_ETH_RCFG_MCA_En_Msk         (0x1UL)                   /*!< MDR_ETH1 R_CFG: MCA_En (Bitfield-Mask: 0x01)          */
#define MDR_ETH_RCFG_BCA_En_Pos         (1UL)                     /*!< MDR_ETH1 R_CFG: BCA_En (Bit 1)                        */
#define MDR_ETH_RCFG_BCA_En_Msk         (0x2UL)                   /*!< MDR_ETH1 R_CFG: BCA_En (Bitfield-Mask: 0x01)          */
#define MDR_ETH_RCFG_UCA_En_Pos         (2UL)                     /*!< MDR_ETH1 R_CFG: UCA_En (Bit 2)                        */
#define MDR_ETH_RCFG_UCA_En_Msk         (0x4UL)                   /*!< MDR_ETH1 R_CFG: UCA_En (Bitfield-Mask: 0x01)          */
#define MDR_ETH_RCFG_AC_En_Pos          (3UL)                     /*!< MDR_ETH1 R_CFG: AC_En (Bit 3)                         */
#define MDR_ETH_RCFG_AC_En_Msk          (0x8UL)                   /*!< MDR_ETH1 R_CFG: AC_En (Bitfield-Mask: 0x01)           */
#define MDR_ETH_RCFG_EF_En_Pos          (4UL)                     /*!< MDR_ETH1 R_CFG: EF_En (Bit 4)                         */
#define MDR_ETH_RCFG_EF_En_Msk          (0x10UL)                  /*!< MDR_ETH1 R_CFG: EF_En (Bitfield-Mask: 0x01)           */
#define MDR_ETH_RCFG_CF_En_Pos          (5UL)                     /*!< MDR_ETH1 R_CFG: CF_En (Bit 5)                         */
#define MDR_ETH_RCFG_CF_En_Msk          (0x20UL)                  /*!< MDR_ETH1 R_CFG: CF_En (Bitfield-Mask: 0x01)           */
#define MDR_ETH_RCFG_LF_En_Pos          (6UL)                     /*!< MDR_ETH1 R_CFG: LF_En (Bit 6)                         */
#define MDR_ETH_RCFG_LF_En_Msk          (0x40UL)                  /*!< MDR_ETH1 R_CFG: LF_En (Bitfield-Mask: 0x01)           */
#define MDR_ETH_RCFG_SF_En_Pos          (7UL)                     /*!< MDR_ETH1 R_CFG: SF_En (Bit 7)                         */
#define MDR_ETH_RCFG_SF_En_Msk          (0x80UL)                  /*!< MDR_ETH1 R_CFG: SF_En (Bitfield-Mask: 0x01)           */
#define MDR_ETH_RCFG_EVNT_MODE_Pos      (8UL)                     /*!< MDR_ETH1 R_CFG: EVNT_MODE (Bit 8)                     */
#define MDR_ETH_RCFG_EVNT_MODE_Msk      (0x700UL)                 /*!< MDR_ETH1 R_CFG: EVNT_MODE (Bitfield-Mask: 0x07)       */
#define MDR_ETH_RCFG_MSB_1st_Pos        (12UL)                    /*!< MDR_ETH1 R_CFG: MSB_1st (Bit 12)                      */
#define MDR_ETH_RCFG_MSB_1st_Msk        (0x1000UL)                /*!< MDR_ETH1 R_CFG: MSB_1st (Bitfield-Mask: 0x01)         */
#define MDR_ETH_RCFG_BE_Pos             (13UL)                    /*!< MDR_ETH1 R_CFG: BE (Bit 13)                           */
#define MDR_ETH_RCFG_BE_Msk             (0x2000UL)                /*!< MDR_ETH1 R_CFG: BE (Bitfield-Mask: 0x01)              */
#define MDR_ETH_RCFG_EN_Pos             (15UL)                    /*!< MDR_ETH1 R_CFG: EN (Bit 15)                           */
#define MDR_ETH_RCFG_EN_Msk             (0x8000UL)                /*!< MDR_ETH1 R_CFG: EN (Bitfield-Mask: 0x01)              */


/* =========================================================  X_CFG  ========================================================= */
typedef enum {                                  /*!< MDR_ETH1_X_CFG_EVNT_MODE                                                  */
  MDR_ETH_XCFG_Rtry_Off  = 0,
  MDR_ETH_XCFG_Rtry_1  = 1,
  MDR_ETH_XCFG_Rtry_2  = 2,
  MDR_ETH_XCFG_Rtry_3  = 3,
  MDR_ETH_XCFG_Rtry_4  = 4,
  MDR_ETH_XCFG_Rtry_5  = 5,
  MDR_ETH_XCFG_Rtry_6  = 6,
  MDR_ETH_XCFG_Rtry_7  = 7,
  MDR_ETH_XCFG_Rtry_8  = 8,
  MDR_ETH_XCFG_Rtry_9  = 9,
  MDR_ETH_XCFG_Rtry_10  = 10,
  MDR_ETH_XCFG_Rtry_11  = 11,
  MDR_ETH_XCFG_Rtry_12  = 12,
  MDR_ETH_XCFG_Rtry_13  = 13,
  MDR_ETH_XCFG_Rtry_14  = 14,
  MDR_ETH_XCFG_Rtry_15  = 15,
} MDR_ETH_XCFG_RTry;

typedef enum {                                  /*!< MDR_ETH1_X_CFG_EVNT_MODE                                                  */
  MDR_ETH_XCFG_EVENT_FIFO_Empty  = 0,     /*!< FIFO_Empty : FIFO is empty                                                */
  MDR_ETH_XCFG_EVENT_FIFO_AEmpty = 1,     /*!< FIFO_AEmpty : FIFO is 1/32 full                                           */
  MDR_ETH_XCFG_EVENT_FIFO_Half   = 2,     /*!< FIFO_Half : FIFO is 1/2 full                                              */
  MDR_ETH_XCFG_EVENT_FIFO_AFull  = 3,     /*!< FIFO_AFull : FIFO is 31/32 full                                           */
  MDR_ETH_XCFG_EVENT_FIFO_Full   = 4,     /*!< FIFO_Full : FIFO Full                                                     */
  MDR_ETH_XCFG_EVENT_Sent        = 5,     /*!< Sent : Frame sent                                                         */
  MDR_ETH_XCFG_EVENT_Read        = 6,     /*!< Read : Frame read from buff                                               */
  MDR_ETH_XCFG_EVENT_TryStarted  = 7,     /*!< TryStarted : Start sending                                                */
} MDR_ETH_XCFG_EVENT;

typedef struct {
  __IOM MDR_ETH_XCFG_RTry   RtryCnt    : 4;            /*!< [3..0] Try send count                                                     */
  __IOM MDR_OnOff           IPG_En     : 1;            /*!< [4..4] IPG enable                                                         */
  __IOM MDR_OnOff           CRC_En     : 1;            /*!< [5..5] Add CRC to frame                                                   */
  __IOM MDR_OnOff           PRE_En     : 1;            /*!< [6..6] Add Preamble to frame                                              */
  __IOM MDR_OnOff           PAD_En     : 1;            /*!< [7..7] Fill with PAD to minimum length                                    */
  __IOM MDR_ETH_XCFG_EVENT  EVNT_MODE  : 3;            /*!< [10..8] Select signal EVNT1 events                                        */
  __IM  uint16_t                       : 1;
  __IOM MDR_OnOff           MSB_1st    : 1;            /*!< [12..12] Bit order                                                        */
  __IOM MDR_ETH_CFG_BE      BE         : 1;            /*!< [13..13] Byte order                                                       */
  __IM  uint16_t                       : 1;
  __IOM uint16_t            EN         : 1;            /*!< [15..15] Enable Transmitter                                               */
} MDR_ETH_XCfg_Bits;

#define MDR_ETH_XCFG_RtryCnt_Pos        (0UL)                     /*!< MDR_ETH1 X_CFG: RtryCnt (Bit 0)                       */
#define MDR_ETH_XCFG_RtryCnt_Msk        (0xfUL)                   /*!< MDR_ETH1 X_CFG: RtryCnt (Bitfield-Mask: 0x0f)         */
#define MDR_ETH_XCFG_IPG_En_Pos         (4UL)                     /*!< MDR_ETH1 X_CFG: IPG_En (Bit 4)                        */
#define MDR_ETH_XCFG_IPG_En_Msk         (0x10UL)                  /*!< MDR_ETH1 X_CFG: IPG_En (Bitfield-Mask: 0x01)          */
#define MDR_ETH_XCFG_CRC_En_Pos         (5UL)                     /*!< MDR_ETH1 X_CFG: CRC_En (Bit 5)                        */
#define MDR_ETH_XCFG_CRC_En_Msk         (0x20UL)                  /*!< MDR_ETH1 X_CFG: CRC_En (Bitfield-Mask: 0x01)          */
#define MDR_ETH_XCFG_PRE_En_Pos         (6UL)                     /*!< MDR_ETH1 X_CFG: PRE_En (Bit 6)                        */
#define MDR_ETH_XCFG_PRE_En_Msk         (0x40UL)                  /*!< MDR_ETH1 X_CFG: PRE_En (Bitfield-Mask: 0x01)          */
#define MDR_ETH_XCFG_PAD_En_Pos         (7UL)                     /*!< MDR_ETH1 X_CFG: PAD_En (Bit 7)                        */
#define MDR_ETH_XCFG_PAD_En_Msk         (0x80UL)                  /*!< MDR_ETH1 X_CFG: PAD_En (Bitfield-Mask: 0x01)          */
#define MDR_ETH_XCFG_EVNT_MODE_Pos      (8UL)                     /*!< MDR_ETH1 X_CFG: EVNT_MODE (Bit 8)                     */
#define MDR_ETH_XCFG_EVNT_MODE_Msk      (0x700UL)                 /*!< MDR_ETH1 X_CFG: EVNT_MODE (Bitfield-Mask: 0x07)       */
#define MDR_ETH_XCFG_MSB_1st_Pos        (12UL)                    /*!< MDR_ETH1 X_CFG: MSB_1st (Bit 12)                      */
#define MDR_ETH_XCFG_MSB_1st_Msk        (0x1000UL)                /*!< MDR_ETH1 X_CFG: MSB_1st (Bitfield-Mask: 0x01)         */
#define MDR_ETH_XCFG_BE_Pos             (13UL)                    /*!< MDR_ETH1 X_CFG: BE (Bit 13)                           */
#define MDR_ETH_XCFG_BE_Msk             (0x2000UL)                /*!< MDR_ETH1 X_CFG: BE (Bitfield-Mask: 0x01)              */
#define MDR_ETH_XCFG_EN_Pos             (15UL)                    /*!< MDR_ETH1 X_CFG: EN (Bit 15)                           */
#define MDR_ETH_XCFG_EN_Msk             (0x8000UL)                /*!< MDR_ETH1 X_CFG: EN (Bitfield-Mask: 0x01)              */


/* ========================================================  G_CFGL  ========================================================= */

typedef enum {                                             /*!< MDR_ETH1_G_CFGL_BUFF_Mode                                                 */
  MDR_ETH_BuffMode_Linear     = 0,                   /*!< Linear : User PTR Control                                                 */
  MDR_ETH_BuffMode_AutoPTR    = 1,                   /*!< AutoPTR : Auto PTR Control                                                */
  MDR_ETH_BuffMode_FIFO       = 2,                   /*!< FIFO : FIFO Buff Control                                                  */
} MDR_ETH_BuffMode;

typedef struct {
  __IOM uint16_t                ColWnd     : 8;            /*!< [7..0] Collision window in bits mul 4                                     */
  __IOM MDR_OnOff               Pause_En   : 1;            /*!< [8..8] Accept Pause frame                                                 */
  __IOM MDR_OnOff               DTRM_En    : 1;            /*!< [9..9] DetermMode                                                         */
  __IOM MDR_OnOff               HD_En      : 1;            /*!< [10..10] Enable Half duplex                                               */
  __IOM MDR_OnOff               EXT_En     : 1;            /*!< [11..11] Fill frame to slot time                                          */
  __IOM MDR_ETH_BuffMode        BUFF_Mode  : 2;            /*!< [13..12] Buffer control                                                   */
  __IOM MDR_OnOff               IFR_CLR_En : 1;            /*!< [14..14] Clear IFR status on Read                                         */
} MDR_ETH_GCfgL_Bits;

#define MDR_ETH_GCFGL_ColWnd_Pos        (0UL)                     /*!< MDR_ETH1 G_CFGL: ColWnd (Bit 0)                       */
#define MDR_ETH_GCFGL_ColWnd_Msk        (0xffUL)                  /*!< MDR_ETH1 G_CFGL: ColWnd (Bitfield-Mask: 0xff)         */
#define MDR_ETH_GCFGL_Pause_En_Pos      (8UL)                     /*!< MDR_ETH1 G_CFGL: Pause_En (Bit 8)                     */
#define MDR_ETH_GCFGL_Pause_En_Msk      (0x100UL)                 /*!< MDR_ETH1 G_CFGL: Pause_En (Bitfield-Mask: 0x01)       */
#define MDR_ETH_GCFGL_DTRM_En_Pos       (9UL)                     /*!< MDR_ETH1 G_CFGL: DTRM_En (Bit 9)                      */
#define MDR_ETH_GCFGL_DTRM_En_Msk       (0x200UL)                 /*!< MDR_ETH1 G_CFGL: DTRM_En (Bitfield-Mask: 0x01)        */
#define MDR_ETH_GCFGL_HD_En_Pos         (10UL)                    /*!< MDR_ETH1 G_CFGL: HD_En (Bit 10)                       */
#define MDR_ETH_GCFGL_HD_En_Msk         (0x400UL)                 /*!< MDR_ETH1 G_CFGL: HD_En (Bitfield-Mask: 0x01)          */
#define MDR_ETH_GCFGL_EXT_En_Pos        (11UL)                    /*!< MDR_ETH1 G_CFGL: EXT_En (Bit 11)                      */
#define MDR_ETH_GCFGL_EXT_En_Msk        (0x800UL)                 /*!< MDR_ETH1 G_CFGL: EXT_En (Bitfield-Mask: 0x01)         */
#define MDR_ETH_GCFGL_BUFF_Mode_Pos     (12UL)                    /*!< MDR_ETH1 G_CFGL: BUFF_Mode (Bit 12)                   */
#define MDR_ETH_GCFGL_BUFF_Mode_Msk     (0x3000UL)                /*!< MDR_ETH1 G_CFGL: BUFF_Mode (Bitfield-Mask: 0x03)      */
#define MDR_ETH_GCFGL_IFR_CLR_En_Pos    (14UL)                    /*!< MDR_ETH1 G_CFGL: IFR_CLR_En (Bit 14)                  */
#define MDR_ETH_GCFGL_IFR_CLR_En_Msk    (0x4000UL)                /*!< MDR_ETH1 G_CFGL: IFR_CLR_En (Bitfield-Mask: 0x01)     */


/* ==========================================================  IMR/IFR  ========================================================== */

typedef struct {
  __IOM MDR_OnOff RF_OK      : 1;            /*!< [0..0] Received OK                                                        */
  __IOM MDR_OnOff MISSED_F   : 1;            /*!< [1..1] Not enough space in buff RX                                        */
  __IOM MDR_OnOff OVF        : 1;            /*!< [2..2] Buff RX overflow                                                   */
  __IOM MDR_OnOff SMB_Err    : 1;            /*!< [3..3] Receiving error                                                    */
  __IOM MDR_OnOff CRC_Err    : 1;            /*!< [4..4] CRC error                                                          */
  __IOM MDR_OnOff CF         : 1;            /*!< [5..5] Control frame received                                             */
  __IOM MDR_OnOff LF         : 1;            /*!< [6..6] Long frame received                                                */
  __IOM MDR_OnOff SF         : 1;            /*!< [7..7] Short frame received                                               */
  __IOM MDR_OnOff XF_Ok      : 1;            /*!< [8..8] Sent successful                                                    */
  __IOM MDR_OnOff XF_Err     : 1;            /*!< [9..9] Error on sending                                                   */
  __IOM MDR_OnOff UNDEF      : 1;            /*!< [10..10] Tx buff empty                                                    */
  __IOM MDR_OnOff LC         : 1;            /*!< [11..11] Late Collision                                                   */
  __IOM MDR_OnOff CRS_Lost   : 1;            /*!< [12..12] Carrier sense lost                                               */
  __IM  uint16_t             : 1;
  __IOM MDR_OnOff MDIO_INT   : 1;            /*!< [14..14] IRQ from MDIO                                                    */
  __IOM MDR_OnOff MDIO_RDY   : 1;            /*!< [15..15] MDIO transfer completed                                          */
} MDR_ETH_EVENT_Bits;

#define MDR_ETH_EVENT_RF_OK_Pos            (0UL)                     /*!< MDR_ETH1 IMR: RF_OK (Bit 0)                           */
#define MDR_ETH_EVENT_RF_OK_Msk            (0x1UL)                   /*!< MDR_ETH1 IMR: RF_OK (Bitfield-Mask: 0x01)             */
#define MDR_ETH_EVENT_MISSED_F_Pos         (1UL)                     /*!< MDR_ETH1 IMR: MISSED_F (Bit 1)                        */
#define MDR_ETH_EVENT_MISSED_F_Msk         (0x2UL)                   /*!< MDR_ETH1 IMR: MISSED_F (Bitfield-Mask: 0x01)          */
#define MDR_ETH_EVENT_OVF_Pos              (2UL)                     /*!< MDR_ETH1 IMR: OVF (Bit 2)                             */
#define MDR_ETH_EVENT_OVF_Msk              (0x4UL)                   /*!< MDR_ETH1 IMR: OVF (Bitfield-Mask: 0x01)               */
#define MDR_ETH_EVENT_SMB_Err_Pos          (3UL)                     /*!< MDR_ETH1 IMR: SMB_Err (Bit 3)                         */
#define MDR_ETH_EVENT_SMB_Err_Msk          (0x8UL)                   /*!< MDR_ETH1 IMR: SMB_Err (Bitfield-Mask: 0x01)           */
#define MDR_ETH_EVENT_CRC_Err_Pos          (4UL)                     /*!< MDR_ETH1 IMR: CRC_Err (Bit 4)                         */
#define MDR_ETH_EVENT_CRC_Err_Msk          (0x10UL)                  /*!< MDR_ETH1 IMR: CRC_Err (Bitfield-Mask: 0x01)           */
#define MDR_ETH_EVENT_CF_Pos               (5UL)                     /*!< MDR_ETH1 IMR: CF (Bit 5)                              */
#define MDR_ETH_EVENT_CF_Msk               (0x20UL)                  /*!< MDR_ETH1 IMR: CF (Bitfield-Mask: 0x01)                */
#define MDR_ETH_EVENT_LF_Pos               (6UL)                     /*!< MDR_ETH1 IMR: LF (Bit 6)                              */
#define MDR_ETH_EVENT_LF_Msk               (0x40UL)                  /*!< MDR_ETH1 IMR: LF (Bitfield-Mask: 0x01)                */
#define MDR_ETH_EVENT_SF_Pos               (7UL)                     /*!< MDR_ETH1 IMR: SF (Bit 7)                              */
#define MDR_ETH_EVENT_SF_Msk               (0x80UL)                  /*!< MDR_ETH1 IMR: SF (Bitfield-Mask: 0x01)                */
#define MDR_ETH_EVENT_XF_Ok_Pos            (8UL)                     /*!< MDR_ETH1 IMR: XF_Ok (Bit 8)                           */
#define MDR_ETH_EVENT_XF_Ok_Msk            (0x100UL)                 /*!< MDR_ETH1 IMR: XF_Ok (Bitfield-Mask: 0x01)             */
#define MDR_ETH_EVENT_XF_Err_Pos           (9UL)                     /*!< MDR_ETH1 IMR: XF_Err (Bit 9)                          */
#define MDR_ETH_EVENT_XF_Err_Msk           (0x200UL)                 /*!< MDR_ETH1 IMR: XF_Err (Bitfield-Mask: 0x01)            */
#define MDR_ETH_EVENT_UNDEF_Pos            (10UL)                    /*!< MDR_ETH1 IMR: UNDEF (Bit 10)                          */
#define MDR_ETH_EVENT_UNDEF_Msk            (0x400UL)                 /*!< MDR_ETH1 IMR: UNDEF (Bitfield-Mask: 0x01)             */
#define MDR_ETH_EVENT_LC_Pos               (11UL)                    /*!< MDR_ETH1 IMR: LC (Bit 11)                             */
#define MDR_ETH_EVENT_LC_Msk               (0x800UL)                 /*!< MDR_ETH1 IMR: LC (Bitfield-Mask: 0x01)                */
#define MDR_ETH_EVENT_CRS_Lost_Pos         (12UL)                    /*!< MDR_ETH1 IMR: CRC_Lost (Bit 12)                       */
#define MDR_ETH_EVENT_CRS_Lost_Msk         (0x1000UL)                /*!< MDR_ETH1 IMR: CRC_Lost (Bitfield-Mask: 0x01)          */
#define MDR_ETH_EVENT_MDIO_INT_Pos         (14UL)                    /*!< MDR_ETH1 IMR: MDIO_INT (Bit 14)                       */
#define MDR_ETH_EVENT_MDIO_INT_Msk         (0x4000UL)                /*!< MDR_ETH1 IMR: MDIO_INT (Bitfield-Mask: 0x01)          */
#define MDR_ETH_EVENT_MDIO_RDY_Pos         (15UL)                    /*!< MDR_ETH1 IMR: MDIO_RDY (Bit 15)                       */
#define MDR_ETH_EVENT_MDIO_RDY_Msk         (0x8000UL)                /*!< MDR_ETH1 IMR: MDIO_RDY (Bitfield-Mask: 0x01)          */

#define MDR_ETH_EVENT_CLEAR_ALL             0xDFFF

/* =======================================================  MDIO_CTRL  ======================================================= */
typedef enum {                                  /*!< MDR_ETH1_MDIO_CTRL_OP                                                     */
  MDR_ETH_MDIO_CTRL_OP_WR             = 0,      /*!< WR : MDIO Write                                                           */  
  MDR_ETH_MDIO_CTRL_OP_RD             = 1,      /*!< RD : MDIO Read                                                            */
} MDR_ETH_MDIO_CTRL_OP;

typedef struct {
  __IOM uint16_t              REG_Addr   : 5;            /*!< [4..0] PHY_Reg address address at MDIO Bus                                */
  __IOM uint16_t              DIV        : 3;            /*!< [7..5] MDIO_f = ETH_CLK/((DIV + 1) * 16)                                  */
  __IOM uint16_t              PHY_Addr   : 5;            /*!< [12..8] PHY address at MDIO Bus                                           */
  __IOM MDR_ETH_MDIO_CTRL_OP  OP         : 1;            /*!< [13..13] Operation RD or WR                                               */
  __IOM MDR_OnOff             PRE_En     : 1;            /*!< [14..14] Send preamble of 0xFFFF_FFFF                                     */
  __IOM MDR_OnOff             CTRL_RDY   : 1;            /*!< [15..15] Command and Status flag                                          */
} MDR_ETH_MDIO_CTRL_Bits;

#define MDR_ETH_MDIO_CTRL_REG_Addr_Pos   (0UL)                     /*!< MDR_ETH1 MDIO_CTRL: REG_Addr (Bit 0)                  */
#define MDR_ETH_MDIO_CTRL_REG_Addr_Msk   (0x1fUL)                  /*!< MDR_ETH1 MDIO_CTRL: REG_Addr (Bitfield-Mask: 0x1f)    */
#define MDR_ETH_MDIO_CTRL_DIV_Pos        (5UL)                     /*!< MDR_ETH1 MDIO_CTRL: DIV (Bit 5)                       */
#define MDR_ETH_MDIO_CTRL_DIV_Msk        (0xe0UL)                  /*!< MDR_ETH1 MDIO_CTRL: DIV (Bitfield-Mask: 0x07)         */
#define MDR_ETH_MDIO_CTRL_PHY_Addr_Pos   (8UL)                     /*!< MDR_ETH1 MDIO_CTRL: PHY_Addr (Bit 8)                  */
#define MDR_ETH_MDIO_CTRL_PHY_Addr_Msk   (0x1f00UL)                /*!< MDR_ETH1 MDIO_CTRL: PHY_Addr (Bitfield-Mask: 0x1f)    */
#define MDR_ETH_MDIO_CTRL_OP_Pos         (13UL)                    /*!< MDR_ETH1 MDIO_CTRL: OP (Bit 13)                       */
#define MDR_ETH_MDIO_CTRL_OP_Msk         (0x2000UL)                /*!< MDR_ETH1 MDIO_CTRL: OP (Bitfield-Mask: 0x01)          */
#define MDR_ETH_MDIO_CTRL_PRE_En_Pos     (14UL)                    /*!< MDR_ETH1 MDIO_CTRL: PRE_En (Bit 14)                   */
#define MDR_ETH_MDIO_CTRL_PRE_En_Msk     (0x4000UL)                /*!< MDR_ETH1 MDIO_CTRL: PRE_En (Bitfield-Mask: 0x01)      */
#define MDR_ETH_MDIO_CTRL_CTRL_RDY_Pos   (15UL)                    /*!< MDR_ETH1 MDIO_CTRL: CTRL_RDY (Bit 15)                 */
#define MDR_ETH_MDIO_CTRL_CTRL_RDY_Msk   (0x8000UL)                /*!< MDR_ETH1 MDIO_CTRL: CTRL_RDY (Bitfield-Mask: 0x01)    */


//  F_MDC < 2.5MHz (400ns)
//  F_MDC = ETH_CLK_MHz / ((clkDiv + 1) * 16) < 2.5MHz
//          ETH_CLK_MHz  < 2.5MHz * 16 * (clkDiv + 1)
//            ETH_CLK_MHz  <  40 (clkDiv = 0)
//            ETH_CLK_MHz  <  80 (clkDiv = 1)
//            ETH_CLK_MHz  < 120 (clkDiv = 2)
//            ETH_CLK_MHz  < 160 (clkDiv = 3)
#define MDC_DIV_le40MHz      0
#define MDC_DIV_le80MHz      1
#define MDC_DIV_le120MHz     2
#define MDC_DIV_le160MHz     3
#define MDC_DIV_le200MHz     4
#define MDC_DIV_le240MHz     5

/* =========================================================  STAT  ========================================================== */
typedef struct {
  __IOM MDR_OnOff         RX_Empty   : 1;            /*!< [0..0] RX_FIFO empty                                                      */
  __IOM MDR_OnOff         RX_AEmpty  : 1;            /*!< [1..1] RX_FIFO is 1/32 full                                               */
  __IOM MDR_OnOff         RX_Hald    : 1;            /*!< [2..2] RX_FIFO is 1/2 full                                                */
  __IOM MDR_OnOff         RX_AFull   : 1;            /*!< [3..3] RX_FIFO is 31/32 full                                              */
  __IOM MDR_OnOff         RX_Full    : 1;            /*!< [4..4] RX_FIFO is full                                                    */
  __IOM uint16_t          RX_Count   : 3;            /*!< [7..5] Frames in FIFO                                                     */
  __IOM MDR_OnOff         TX_Empty   : 1;            /*!< [8..8] TX_FIFO is Empty                                                   */
  __IOM MDR_OnOff         TX_AEmpty  : 1;            /*!< [9..9] TX_FIFO is 1/32 full                                               */
  __IOM MDR_OnOff         TX_Hald    : 1;            /*!< [10..10] TX_FIFO is 1/2 full                                              */
  __IOM MDR_OnOff         TX_AFull   : 1;            /*!< [11..11] TX_FIFO is 31/32 full                                            */
  __IOM MDR_OnOff         TX_Full    : 1;            /*!< [12..12] TX_FIFO is full                                                  */
} MDR_ETH_STAT_Bits;


#define MDR_ETH_STAT_RX_Empty_Pos        (0UL)                     /*!< MDR_ETH1 STAT: RX_Empty (Bit 0)                       */
#define MDR_ETH_STAT_RX_Empty_Msk        (0x1UL)                   /*!< MDR_ETH1 STAT: RX_Empty (Bitfield-Mask: 0x01)         */
#define MDR_ETH_STAT_RX_AEmpty_Pos       (1UL)                     /*!< MDR_ETH1 STAT: RX_AEmpty (Bit 1)                      */
#define MDR_ETH_STAT_RX_AEmpty_Msk       (0x2UL)                   /*!< MDR_ETH1 STAT: RX_AEmpty (Bitfield-Mask: 0x01)        */
#define MDR_ETH_STAT_RX_Halt_Pos         (2UL)                     /*!< MDR_ETH1 STAT: RX_Hald (Bit 2)                        */
#define MDR_ETH_STAT_RX_Halt_Msk         (0x4UL)                   /*!< MDR_ETH1 STAT: RX_Hald (Bitfield-Mask: 0x01)          */
#define MDR_ETH_STAT_RX_AFull_Pos        (3UL)                     /*!< MDR_ETH1 STAT: RX_AFull (Bit 3)                       */
#define MDR_ETH_STAT_RX_AFull_Msk        (0x8UL)                   /*!< MDR_ETH1 STAT: RX_AFull (Bitfield-Mask: 0x01)         */
#define MDR_ETH_STAT_RX_Full_Pos         (4UL)                     /*!< MDR_ETH1 STAT: RX_Full (Bit 4)                        */
#define MDR_ETH_STAT_RX_Full_Msk         (0x10UL)                  /*!< MDR_ETH1 STAT: RX_Full (Bitfield-Mask: 0x01)          */
#define MDR_ETH_STAT_RX_Count_Pos        (5UL)                     /*!< MDR_ETH1 STAT: RX_Count (Bit 5)                       */
#define MDR_ETH_STAT_RX_Count_Msk        (0xe0UL)                  /*!< MDR_ETH1 STAT: RX_Count (Bitfield-Mask: 0x07)         */
#define MDR_ETH_STAT_TX_Empty_Pos        (8UL)                     /*!< MDR_ETH1 STAT: TX_Empty (Bit 8)                       */
#define MDR_ETH_STAT_TX_Empty_Msk        (0x100UL)                 /*!< MDR_ETH1 STAT: TX_Empty (Bitfield-Mask: 0x01)         */
#define MDR_ETH_STAT_TX_AEmpty_Pos       (9UL)                     /*!< MDR_ETH1 STAT: TX_AEmpty (Bit 9)                      */
#define MDR_ETH_STAT_TX_AEmpty_Msk       (0x200UL)                 /*!< MDR_ETH1 STAT: TX_AEmpty (Bitfield-Mask: 0x01)        */
#define MDR_ETH_STAT_TX_Hald_Pos         (10UL)                    /*!< MDR_ETH1 STAT: TX_Hald (Bit 10)                       */
#define MDR_ETH_STAT_TX_Hald_Msk         (0x400UL)                 /*!< MDR_ETH1 STAT: TX_Hald (Bitfield-Mask: 0x01)          */
#define MDR_ETH_STAT_TX_AFull_Pos        (11UL)                    /*!< MDR_ETH1 STAT: TX_AFull (Bit 11)                      */
#define MDR_ETH_STAT_TX_AFull_Msk        (0x800UL)                 /*!< MDR_ETH1 STAT: TX_AFull (Bitfield-Mask: 0x01)         */
#define MDR_ETH_STAT_TX_Full_Pos         (12UL)                    /*!< MDR_ETH1 STAT: TX_Full (Bit 12)                       */
#define MDR_ETH_STAT_TX_Full_Msk         (0x1000UL)                /*!< MDR_ETH1 STAT: TX_Full (Bitfield-Mask: 0x01)          */


/* ======================================  Registers set to configure MAC block  ============================================= */
//  Registers to configure MAC block
typedef struct {
  uint16_t  DELIMETER;
  uint16_t  MAC_L;    
  uint16_t  MAC_M;    
  uint16_t  MAC_H;    
  uint16_t  HASH0;    
  uint16_t  HASH1;    
  uint16_t  HASH2;    
  uint16_t  HASH3;    
  uint16_t  IPG;      
  uint16_t  PSC;      
  uint16_t  BAG;      
  uint16_t  JitterWnd;
  uint16_t  R_CFG;    
  uint16_t  X_CFG;    
  uint16_t  G_CFGL;   
  uint16_t  G_CFGH;   
  uint16_t  IMR;      
  uint16_t  MDIO_CTRL;
} MDR_ETH_MAC_CfgRegs;


/* ==================================================  BUFF Frame RX_STATUS ================================================== */

typedef struct{
	uint16_t Length			    : 16;     // The number of bytes in the packet including header and CRC.
	uint32_t IsPauseFrame   : 1;			// A sign package PAUSE.
	uint32_t IsContorlFrame	: 1;			// A sign Management Pack (filtering by MAC and special tags in the field length - 13.14 - octets).
	uint32_t IsLongFrame		: 1;			// A sign excess packet length 1518 octets.
	uint32_t IsShortFrame		: 1;			// A sign of lack of packet length 64 octets.
	uint32_t IsErrLength	  : 1;			// A sign mismatch between the actual length and the length specified in the length field - 13.14 octets.
	uint32_t IsErr8Bits   	: 1;			// A sign bit of the packet is not a multiple of 8.
	uint32_t IsErrCRC		    : 1;			// A sign mismatch packet CRC.
	uint32_t IsErrNibbles		: 1;			// A sign of the presence in the packet error nibbles.
	uint32_t IsFrameMCA			: 1;			// A sign group package (MAC matches HASH).
	uint32_t IsFrameBCA			: 1;			// A sign of the broadcast packet (MAC = FF:FF:FF:FF:FF:FF)
	uint32_t IsFrameUCA			: 1;			// A sign individual package (MAC corresponds to the set).
} MDR_ETH_FrameStatusRX_Bits;

/**
 * @brief The state of the packet reception	Unioun definition
 */
typedef union {
	uint32_t                   Status;
	MDR_ETH_FrameStatusRX_Bits Fields;
} MDR_ETH_FrameStatusRX;

#define MDR_ETH_BUF_FIFO_RX_OFFS    0
#define MDR_ETH_BUF_FIFO_TX_OFFS    4

//  Control Words in TX buffer
#define MDR_ETH_BUFF_TX_LEN_SIZE     4
#define MDR_ETH_BUFF_TX_STATUS_SIZE   4


/* ================================================  Standard Internal PHY Registers  ============================================== */
//  Register R0 - RW Base Control
#define MDR_ETH_PHY_R0                        0

#define MDR_ETH_PHY_R0_FULL_DUPLEX_Pos         8
#define MDR_ETH_PHY_R0_FULL_DUPLEX_Msk        (1 << MDR_ETH_PHY_R0_FULL_DUPLEX_Pos)
#define MDR_ETH_PHY_R0_RESTART_AUTONEG_Pos     9
#define MDR_ETH_PHY_R0_RESTART_AUTONEG_Msk    (1 << MDR_ETH_PHY_R0_RESTART_AUTONEG_Pos)
#define MDR_ETH_PHY_R0_ISOL_Pos                10
#define MDR_ETH_PHY_R0_ISOL_Msk               (1 << MDR_ETH_PHY_R0_ISOL_Pos)
#define MDR_ETH_PHY_R0_PWR_DOWN_Pos            11
#define MDR_ETH_PHY_R0_PWR_DOWN_Msk           (1 << MDR_ETH_PHY_R0_ISOL_Pos)
#define MDR_ETH_PHY_R0_AUTONEG_ENA_Pos         12
#define MDR_ETH_PHY_R0_AUTONEG_ENA_Msk        (1 << MDR_ETH_PHY_R0_AUTONEG_ENA_Pos)
#define MDR_ETH_PHY_R0_100Mbps_Pos             13
#define MDR_ETH_PHY_R0_100Mbps_Msk            (1 << MDR_ETH_PHY_R0_100Mbps_Pos)
#define MDR_ETH_PHY_R0_Loopback_Pos            14
#define MDR_ETH_PHY_R0_Loopback_Msk           (1 << MDR_ETH_PHY_R0_Loopback_Pos)
#define MDR_ETH_PHY_R0_RESET_Pos               15
#define MDR_ETH_PHY_R0_RESET_Msk              (1 << MDR_ETH_PHY_R0_RESET_Pos)

#define MDR_ETH_PHY_R0_Reserved_Msk           0x00FF


//  Register R1 - RO Base Status
#define MDR_ETH_PHY_R1                        1

#define MDR_ETH_PHY_R1_ExtEna_Pos             0
#define MDR_ETH_PHY_R1_ExtEna_Msk            (1 << MDR_ETH_PHY_R1_ExtEna_Pos)
#define MDR_ETH_PHY_R1_Jabber_Pos             1
#define MDR_ETH_PHY_R1_Jabber_Msk            (1 << MDR_ETH_PHY_R1_Jabber_Pos)
#define MDR_ETH_PHY_R1_Link_Pos               2
#define MDR_ETH_PHY_R1_Link_Msk              (1 << MDR_ETH_PHY_R1_Link_Pos)
#define MDR_ETH_PHY_R1_OptAutoneg_Pos         3
#define MDR_ETH_PHY_R1_OptAutoneg_Msk        (1 << MDR_ETH_PHY_R1_OptAutoneg_Pos)
#define MDR_ETH_PHY_R1_RemoteFault_Pos        4
#define MDR_ETH_PHY_R1_RemoteFault_Msk       (1 << MDR_ETH_PHY_R1_RemoteFault_Pos)
#define MDR_ETH_PHY_R1_AutonegReady_Pos       5
#define MDR_ETH_PHY_R1_AutonegReady_Msk      (1 << MDR_ETH_PHY_R1_AutonegReady_Pos)
#define MDR_ETH_PHY_R1_Opt10BaseHD_Pos        11
#define MDR_ETH_PHY_R1_Opt10BaseHD_Msk       ( 1 << MDR_ETH_PHY_R1_Opt10BaseHD_Pos)
#define MDR_ETH_PHY_R1_Opt10BaseFD_Pos        12
#define MDR_ETH_PHY_R1_Opt10BaseFD_Msk       ( 1 << MDR_ETH_PHY_R1_Opt10BaseFD_Pos)
#define MDR_ETH_PHY_R1_Opt100BaseHD_Pos       13
#define MDR_ETH_PHY_R1_Opt100BaseHD_Msk      ( 1 << MDR_ETH_PHY_R1_Opt100BaseHD_Pos)
#define MDR_ETH_PHY_R1_Opt100BaseFD_Pos       14
#define MDR_ETH_PHY_R1_Opt100BaseFD_Msk      ( 1 << MDR_ETH_PHY_R1_Opt100BaseFD_Pos)
#define MDR_ETH_PHY_R1_Opt100BaseT4_Pos       16
#define MDR_ETH_PHY_R1_Opt100BaseT4_Msk      ( 1 << MDR_ETH_PHY_R1_Opt100BaseT4_Pos)


//  Register R4 - Autonegotiation 
#define MDR_ETH_PHY_R4                        4

#define MDR_ETH_PHY_R4_10BaseHD_Ena_Pos        5
#define MDR_ETH_PHY_R4_10BaseHD_Ena_Msk       (1 << MDR_ETH_PHY_R1_ExtEna_Pos)
#define MDR_ETH_PHY_R4_10BaseFD_Ena_Pos        6
#define MDR_ETH_PHY_R4_10BaseFD_Ena_Msk       (1 << MDR_ETH_PHY_R4_10BaseFD_Ena_Pos)
#define MDR_ETH_PHY_R4_100BaseHD_Ena_Pos       7
#define MDR_ETH_PHY_R4_100BaseHD_Ena_Msk      (1 << MDR_ETH_PHY_R4_100BaseHD_Ena_Pos)
#define MDR_ETH_PHY_R4_100BaseFD_Ena_Pos       8
#define MDR_ETH_PHY_R4_100BaseFD_Ena_Msk      (1 << MDR_ETH_PHY_R4_100BaseFD_Ena_Pos)
#define MDR_ETH_PHY_R4_100BaseT4_Ena_Pos       9
#define MDR_ETH_PHY_R4_100BaseT4_Ena_Msk      (1 << MDR_ETH_PHY_R4_100BaseT4_Ena_Pos)

#define MDR_ETH_PHY_R4_SEL_100Mbps      (MDR_ETH_PHY_R4_100BaseHD_Ena_Msk | MDR_ETH_PHY_R4_100BaseFD_Ena_Msk | MDR_ETH_PHY_R4_100BaseT4_Ena_Msk)


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


#endif  //_MDR_ETH_DEFS_H
