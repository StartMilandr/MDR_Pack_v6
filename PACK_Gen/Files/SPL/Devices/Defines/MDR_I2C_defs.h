#ifndef _MDR_I2C_DEF_H
#define _MDR_I2C_DEF_H

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

typedef struct {
  __IOM uint8_t PRL         : 8;            /*!< [7..0] Div[7:0] of HCLK                                                   */
  __IM  uint32_t            : 24;
} MDR_I2C_PRL_Bits;

#define MDR_I2C_PRL_PRL_Pos               (0UL)                     /*!< MDR_I2C PRL: PRL (Bit 0)                              */
#define MDR_I2C_PRL_PRL_Msk               (0xffUL)                  /*!< MDR_I2C PRL: PRL (Bitfield-Mask: 0xff)                */

typedef struct {
  __IOM uint8_t PRH         : 8;            /*!< [7..0] Div[15:8] of HCLK                                                  */
  __IM  uint32_t            : 24;
} MDR_I2C_PRH_Bits;

#define MDR_I2C_PRH_PRH_Pos               (0UL)                     /*!< MDR_I2C PRH: PRH (Bit 0)                              */
#define MDR_I2C_PRH_PRH_Msk               (0xffUL)                  /*!< MDR_I2C PRH: PRH (Bitfield-Mask: 0xff)                */

typedef enum {
  I2C_Speed_upto400KHz = 0,
  I2C_Speed_upto1MHz   = 1,
} MDR_I2C_Speed;

typedef struct {
  __IM  uint32_t                : 5;
  __IOM MDR_I2C_Speed S_I2C     : 1;            /*!< [5..5] Speed range of I2C                                                 */
  __IOM MDR_OnOff     En_INT    : 1;            /*!< [6..6] Enable IRQ                                                         */
  __IOM MDR_OnOff     En_I2C    : 1;            /*!< [7..7] Enable                                                             */
  __IM  uint32_t                : 24;
} MDR_I2C_CTR_Bits;

#define MDR_I2C_CTR_S_I2C_Pos             (5UL)                     /*!< MDR_I2C CTR: S_I2C (Bit 5)                            */
#define MDR_I2C_CTR_S_I2C_Msk             (0x20UL)                  /*!< MDR_I2C CTR: S_I2C (Bitfield-Mask: 0x01)              */
#define MDR_I2C_CTR_EN_INT_Pos            (6UL)                     /*!< MDR_I2C CTR: EN_INT (Bit 6)                           */
#define MDR_I2C_CTR_EN_INT_Msk            (0x40UL)                  /*!< MDR_I2C CTR: EN_INT (Bitfield-Mask: 0x01)             */
#define MDR_I2C_CTR_EN_I2C_Pos            (7UL)                     /*!< MDR_I2C CTR: EN_I2C (Bit 7)                           */
#define MDR_I2C_CTR_EN_I2C_Msk            (0x80UL)                  /*!< MDR_I2C CTR: EN_I2C (Bitfield-Mask: 0x01)             */

#define MDR_I2C_CTR_ExistBits_Mask  (MDR_I2C_CTR_S_I2C_Msk | MDR_I2C_CTR_EN_INT_Msk | MDR_I2C_CTR_EN_I2C_Msk)

typedef struct {
  __IOM uint8_t  DATA       : 8;            /*!< [7..0] Received Byte                                                      */
  __IM  uint32_t            : 24;
} MDR_I2C_DATA_Bits;

#define MDR_I2C_RXD_DATA_Pos              (0UL)                     /*!< MDR_I2C RXD: DATA (Bit 0)                             */
#define MDR_I2C_RXD_DATA_Msk              (0xffUL)                  /*!< MDR_I2C RXD: DATA (Bitfield-Mask: 0xff)               */


typedef struct {
  __IOM MDR_OnOff INT_Active : 1;            /*!< [0..0] IRQ Event Flag                                                     */
  __IOM MDR_OnOff TR_Prog    : 1;            /*!< [1..1] Transfering status                                                 */
  __IM  uint32_t             : 3;
  __IOM MDR_OnOff Lost_ARB   : 1;            /*!< [5..5] Lost arbitrage                                                     */
  __IOM MDR_OnOff BUSY       : 1;            /*!< [6..6] Line Busy                                                          */
  __IOM MDR_OnOff RX_ACK     : 1;            /*!< [7..7] ACK Status                                                         */
  __IM  uint32_t             : 24;
} MDR_I2C_STA_Bits;

#define MDR_I2C_STA_INT_Pos               (0UL)                     /*!< MDR_I2C STA: INT (Bit 0)                              */
#define MDR_I2C_STA_INT_Msk               (0x1UL)                   /*!< MDR_I2C STA: INT (Bitfield-Mask: 0x01)                */
#define MDR_I2C_STA_TR_Prog_Pos           (1UL)                     /*!< MDR_I2C STA: TR_Prog (Bit 1)                          */
#define MDR_I2C_STA_TR_Prog_Msk           (0x2UL)                   /*!< MDR_I2C STA: TR_Prog (Bitfield-Mask: 0x01)            */
#define MDR_I2C_STA_Lost_ARB_Pos          (5UL)                     /*!< MDR_I2C STA: Lost_ARB (Bit 5)                         */
#define MDR_I2C_STA_Lost_ARB_Msk          (0x20UL)                  /*!< MDR_I2C STA: Lost_ARB (Bitfield-Mask: 0x01)           */
#define MDR_I2C_STA_BUSY_Pos              (6UL)                     /*!< MDR_I2C STA: BUSY (Bit 6)                             */
#define MDR_I2C_STA_BUSY_Msk              (0x40UL)                  /*!< MDR_I2C STA: BUSY (Bitfield-Mask: 0x01)               */
#define MDR_I2C_STA_RX_ACK_Pos            (7UL)                     /*!< MDR_I2C STA: RX_ACK (Bit 7)                           */
#define MDR_I2C_STA_RX_ACK_Msk            (0x80UL)                  /*!< MDR_I2C STA: RX_ACK (Bitfield-Mask: 0x01)             */


typedef struct {
  __IOM MDR_OnOff Clr_INT     : 1;            /*!< [0..0] Clear IRQ Event                                                    */
  __IM  uint32_t              : 2;
  __IOM MDR_OnOff Send_ACK    : 1;            /*!< [3..3] Send ACK command                                                   */
  __IOM MDR_OnOff Start_Write : 1;            /*!< [4..4] Start Writing transfer                                             */
  __IOM MDR_OnOff Start_Read  : 1;            /*!< [5..5] Start Reading transfer                                             */
  __IOM MDR_OnOff Send_Stop   : 1;            /*!< [6..6] Send Stop command                                                  */
  __IOM MDR_OnOff Send_Start  : 1;            /*!< [7..7] Send Start command                                                 */
  __IM  uint32_t              : 24;
} MDR_I2C_CMD_Bits;

#define MDR_I2C_CMD_CLR_INT_Pos           (0UL)                     /*!< MDR_I2C CMD: CLR_INT (Bit 0)                          */
#define MDR_I2C_CMD_CLR_INT_Msk           (0x1UL)                   /*!< MDR_I2C CMD: CLR_INT (Bitfield-Mask: 0x01)            */
#define MDR_I2C_CMD_Send_ACK_Pos          (3UL)                     /*!< MDR_I2C CMD: Send_ACK (Bit 3)                         */
#define MDR_I2C_CMD_Send_ACK_Msk          (0x8UL)                   /*!< MDR_I2C CMD: Send_ACK (Bitfield-Mask: 0x01)           */
#define MDR_I2C_CMD_Start_Write_Pos       (4UL)                     /*!< MDR_I2C CMD: Start_Write (Bit 4)                      */
#define MDR_I2C_CMD_Start_Write_Msk       (0x10UL)                  /*!< MDR_I2C CMD: Start_Write (Bitfield-Mask: 0x01)        */
#define MDR_I2C_CMD_Start_Read_Pos        (5UL)                     /*!< MDR_I2C CMD: Start_Read (Bit 5)                       */
#define MDR_I2C_CMD_Start_Read_Msk        (0x20UL)                  /*!< MDR_I2C CMD: Start_Read (Bitfield-Mask: 0x01)         */
#define MDR_I2C_CMD_Send_Stop_Pos         (6UL)                     /*!< MDR_I2C CMD: Send_Stop (Bit 6)                        */
#define MDR_I2C_CMD_Send_Stop_Msk         (0x40UL)                  /*!< MDR_I2C CMD: Send_Stop (Bitfield-Mask: 0x01)          */
#define MDR_I2C_CMD_Send_Start_Pos        (7UL)                     /*!< MDR_I2C CMD: Send_Start (Bit 7)                       */
#define MDR_I2C_CMD_Send_Start_Msk        (0x80UL)                  /*!< MDR_I2C CMD: Send_Start (Bitfield-Mask: 0x01)         */


#define MDR_I2C_ADDR_WR_BIT   (0x0UL)
#define MDR_I2C_ADDR_RD_BIT   (0x1UL)

#define MDR_I2C_Send_ACK       0
#define MDR_I2C_Send_NACK      MDR_I2C_CMD_Send_ACK_Msk




typedef struct {                            /*!< (@ 0x40030000) MDR_I2C Structure                                          */
  union {
    __IOM uint32_t    PRL;                  /*!< (@ 0x00000000) BitRate Div[7:0] of HCLK                                   */
    MDR_I2C_PRL_Bits  PRL_b;
  } ;  
  union {
    __IOM uint32_t    PRH;                  /*!< (@ 0x00000004) BitRate Div[15:8] of HCLK                                  */
    MDR_I2C_PRH_Bits  PRH_b;
  } ;  
  union {
    __IOM uint32_t    CTR;                  /*!< (@ 0x00000008) Control Register                                           */
    MDR_I2C_CTR_Bits  CTR_b;
  } ;
  union {
    __IOM uint32_t    RXD;                  /*!< (@ 0x0000000C) Received Data                                              */
    MDR_I2C_DATA_Bits RXD_b;
  } ;
  union {
    __IOM uint32_t    STA;                  /*!< (@ 0x00000010) Status register                                            */
    MDR_I2C_STA_Bits  STA_b;
  } ;  
  union {
    __IOM uint32_t    TXD;                  /*!< (@ 0x00000014) Data to Send                                               */
    MDR_I2C_DATA_Bits TXD_b;
  } ;  
  union {
    __IOM uint32_t    CMD;                  /*!< (@ 0x00000018) Command Register                                           */
    MDR_I2C_CMD_Bits  CMD_b;
  } ;
} MDR_I2C_Type;                             /*!< Size = 28 (0x1c)                                                          */


//  Унифицированный регистр со всеми настройками блока
typedef struct {
  uint32_t                  : 5;
  MDR_I2C_Speed speedRange  : 1;            /*!< [5..5] Speed range of I2C                                                 */
  MDR_OnOff     enableIRQ   : 1;            /*!< [6..6] Enable IRQ                                                         */
  MDR_OnOff     enable      : 1;            /*!< [7..7] Enable                                                             */
  uint32_t                  : 8;
  uint16_t      Clk_Div     : 16;
} MDR_I2C_CfgReg_Bits;

#define MDR_I2C_CfgReg_DIV_LO_Pos    16
#define MDR_I2C_CfgReg_DIV_HI_Pos    24

typedef  union {
  uint32_t       Value;
  MDR_I2C_CfgReg_Bits  Bits;
} MDR_I2C_CfgReg;

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

#endif  //  _MDR_I2C_DEF_H
