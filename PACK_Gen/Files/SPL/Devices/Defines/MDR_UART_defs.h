#ifndef _MDR_UART_DEFS_H
#define _MDR_UART_DEFS_H

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

/* =========================================================================================================================== */
/* ================                                         MDR_UART                                         ================ */
/* =========================================================================================================================== */


/* ====================================== RSR_ECR - Receive Status and Error Clear ========================================== */
typedef struct {
  __IOM MDR_OnOff FE         : 1;            /*!< [0..0] Stop Bit Error                                                     */
  __IOM MDR_OnOff PE         : 1;            /*!< [1..1] Parity Error                                                       */
  __IOM MDR_OnOff BE         : 1;            /*!< [2..2] Break Error - Line RX is LOW for 2 words long                    */
  __IOM MDR_OnOff OE         : 1;            /*!< [3..3] Overrun FIFO_RX                                                  */
  __IM  uint32_t             : 28;
} MDR_UART_Error_Bits;

#define MDR_UART_RSR_ECR_FE_Pos          (0UL)                     /*!< MDR_UART1 RSR_ECR: FE (Bit 0)                         */
#define MDR_UART_RSR_ECR_FE_Msk          (0x1UL)                   /*!< MDR_UART1 RSR_ECR: FE (Bitfield-Mask: 0x01)           */
#define MDR_UART_RSR_ECR_PE_Pos          (1UL)                     /*!< MDR_UART1 RSR_ECR: PE (Bit 1)                         */
#define MDR_UART_RSR_ECR_PE_Msk          (0x2UL)                   /*!< MDR_UART1 RSR_ECR: PE (Bitfield-Mask: 0x01)           */
#define MDR_UART_RSR_ECR_BE_Pos          (2UL)                     /*!< MDR_UART1 RSR_ECR: BE (Bit 2)                         */
#define MDR_UART_RSR_ECR_BE_Msk          (0x4UL)                   /*!< MDR_UART1 RSR_ECR: BE (Bitfield-Mask: 0x01)           */
#define MDR_UART_RSR_ECR_OE_Pos          (3UL)                     /*!< MDR_UART1 RSR_ECR: OE (Bit 3)                         */
#define MDR_UART_RSR_ECR_OE_Msk          (0x8UL)                   /*!< MDR_UART1 RSR_ECR: OE (Bitfield-Mask: 0x01)           */


/* ===============================================  FR - Flag Register  ================================================= */
typedef struct {
  __IM  MDR_OnOff CTS        : 1;            /*!< [0..0] Modem Clear To Send                                                */
  __IM  MDR_OnOff DSR        : 1;            /*!< [1..1] Modem Data Set Ready                                               */
  __IM  MDR_OnOff DCD        : 1;            /*!< [2..2] Modem Data Carrier Detect                                          */
  __IM  MDR_OnOff BUSY       : 1;            /*!< [3..3] Transmitting data                                                  */
  __IM  MDR_OnOff RXFE       : 1;            /*!< [4..4] FIFO_RX Empty status                                               */
  __IM  MDR_OnOff TXFF       : 1;            /*!< [5..5] FIFO_TX Full Status                                                */
  __IM  MDR_OnOff RXFF       : 1;            /*!< [6..6] FIFO_RX Full Status                                                */
  __IM  MDR_OnOff TXFE       : 1;            /*!< [7..7] FIFO_RX Empty status                                               */
  __IM  MDR_OnOff RI         : 1;            /*!< [8..8] Modem Ring Indicator                                               */
  __IM  uint32_t             : 23;
} MDR_UART_FR_Bits;

#define MDR_UART_FR_CTS_Pos              (0UL)                     /*!< MDR_UART1 FR: CTS (Bit 0)                             */
#define MDR_UART_FR_CTS_Msk              (0x1UL)                   /*!< MDR_UART1 FR: CTS (Bitfield-Mask: 0x01)               */
#define MDR_UART_FR_DSR_Pos              (1UL)                     /*!< MDR_UART1 FR: DSR (Bit 1)                             */
#define MDR_UART_FR_DSR_Msk              (0x2UL)                   /*!< MDR_UART1 FR: DSR (Bitfield-Mask: 0x01)               */
#define MDR_UART_FR_DCD_Pos              (2UL)                     /*!< MDR_UART1 FR: DCD (Bit 2)                             */
#define MDR_UART_FR_DCD_Msk              (0x4UL)                   /*!< MDR_UART1 FR: DCD (Bitfield-Mask: 0x01)               */
#define MDR_UART_FR_BUSY_Pos             (3UL)                     /*!< MDR_UART1 FR: BUSY (Bit 3)                            */
#define MDR_UART_FR_BUSY_Msk             (0x8UL)                   /*!< MDR_UART1 FR: BUSY (Bitfield-Mask: 0x01)              */
#define MDR_UART_FR_RXFE_Pos             (4UL)                     /*!< MDR_UART1 FR: RXFE (Bit 4)                            */
#define MDR_UART_FR_RXFE_Msk             (0x10UL)                  /*!< MDR_UART1 FR: RXFE (Bitfield-Mask: 0x01)              */
#define MDR_UART_FR_TXFF_Pos             (5UL)                     /*!< MDR_UART1 FR: TXFF (Bit 5)                            */
#define MDR_UART_FR_TXFF_Msk             (0x20UL)                  /*!< MDR_UART1 FR: TXFF (Bitfield-Mask: 0x01)              */
#define MDR_UART_FR_RXFF_Pos             (6UL)                     /*!< MDR_UART1 FR: RXFF (Bit 6)                            */
#define MDR_UART_FR_RXFF_Msk             (0x40UL)                  /*!< MDR_UART1 FR: RXFF (Bitfield-Mask: 0x01)              */
#define MDR_UART_FR_TXFE_Pos             (7UL)                     /*!< MDR_UART1 FR: TXFE (Bit 7)                            */
#define MDR_UART_FR_TXFE_Msk             (0x80UL)                  /*!< MDR_UART1 FR: TXFE (Bitfield-Mask: 0x01)              */
#define MDR_UART_FR_RI_Pos               (8UL)                     /*!< MDR_UART1 FR: RI (Bit 8)                              */
#define MDR_UART_FR_RI_Msk               (0x100UL)                 /*!< MDR_UART1 FR: RI (Bitfield-Mask: 0x01)                */


/* ===============================================  ILPR - IrDA Low Power  ================================================= */
typedef struct {
  __IOM uint32_t DVSR       : 8;            /*!< [7..0] Div of SampleRate                                                  */
  __IM  uint32_t            : 24;
} MDR_UART_ILPR_Bits;

#define MDR_UART_ILPR_DVSR_Pos           (0UL)                     /*!< MDR_UART1 ILPR: DVSR (Bit 0)                          */
#define MDR_UART_ILPR_DVSR_Msk           (0xffUL)                  /*!< MDR_UART1 ILPR: DVSR (Bitfield-Mask: 0xff)            */


/* ===============================================  IBRD - Integer Baud Rate Divider =========================================== */
typedef struct {
  __IOM uint32_t Baud_DivInt : 16;          /*!< [15..0] Integer part of Rate divisor                                      */
  __IM  uint32_t             : 16;
} MDR_UART_IBRD_Bits;

#define MDR_UART_IBRD_Baud_DivInt_Pos    (0UL)                     /*!< MDR_UART1 IBRD: Baud_DivInt (Bit 0)                   */
#define MDR_UART_IBRD_Baud_DivInt_Msk    (0xffffUL)                /*!< MDR_UART1 IBRD: Baud_DivInt (Bitfield-Mask: 0xffff)   */


/* ===============================================  FBRD - Fractional Baud Rate Divider =========================================== */
typedef struct {
  __IOM uint32_t Baud_DivFrac : 6;          /*!< [5..0] Fractional part of Rate divisor                                    */
  __IM  uint32_t              : 26;
} MDR_UART_FBRD_Bits;

#define MDR_UART_FBRD_Baud_DivFrac_Pos   (0UL)                     /*!< MDR_UART1 FBRD: Baud_DivFrac (Bit 0)                  */
#define MDR_UART_FBRD_Baud_DivFrac_Msk   (0x3fUL)                  /*!< MDR_UART1 FBRD: Baud_DivFrac (Bitfield-Mask: 0x3f)    */


/* ===============================================  CR - Control Register =========================================== */
typedef struct {
  __IOM MDR_OnOff EN         : 1;            /*!< [0..0] Enable UART                                                        */
  __IOM MDR_OnOff SIREN      : 1;            /*!< [1..1] IrDA Enable                                                        */
  __IOM MDR_OnOff SIRLP      : 1;            /*!< [2..2] IrDA Low-Power Enable                                              */
  __IM  uint32_t             : 4;
  __IOM MDR_OnOff LBE        : 1;            /*!< [7..7] LoopBack Enable                                                    */
  __IOM MDR_OnOff TXE        : 1;            /*!< [8..8] Transmitter Enable                                                 */
  __IOM MDR_OnOff RXE        : 1;            /*!< [9..9] Receiver Enable                                                    */
  __IOM MDR_OnOff DTR        : 1;            /*!< [10..10] Data Transmit Ready                                              */
  __IOM MDR_OnOff RTS        : 1;            /*!< [11..11] Request To Send                                                  */
  __IOM MDR_OnOff Out1       : 1;            /*!< [12..12] Custom Modem Output1 - DCD                                       */
  __IOM MDR_OnOff Out2       : 1;            /*!< [13..13] Custom Modem Output2 - RI                                        */
  __IOM MDR_OnOff RTSEn      : 1;            /*!< [14..14] Hardware RTS Control                                             */
  __IOM MDR_OnOff CTSEn      : 1;            /*!< [15..15] Hardware CTS Control                                             */
  __IM  uint32_t             : 16;
} MDR_UART_CR_Bits;

#define MDR_UART_CR_EN_Pos               (0UL)                     /*!< MDR_UART1 CR: EN (Bit 0)                              */
#define MDR_UART_CR_EN_Msk               (0x1UL)                   /*!< MDR_UART1 CR: EN (Bitfield-Mask: 0x01)                */
#define MDR_UART_CR_SIREN_Pos            (1UL)                     /*!< MDR_UART1 CR: SIREN (Bit 1)                           */
#define MDR_UART_CR_SIREN_Msk            (0x2UL)                   /*!< MDR_UART1 CR: SIREN (Bitfield-Mask: 0x01)             */
#define MDR_UART_CR_SIRLP_Pos            (2UL)                     /*!< MDR_UART1 CR: SIRLP (Bit 2)                           */
#define MDR_UART_CR_SIRLP_Msk            (0x4UL)                   /*!< MDR_UART1 CR: SIRLP (Bitfield-Mask: 0x01)             */
#define MDR_UART_CR_LBE_Pos              (7UL)                     /*!< MDR_UART1 CR: LBE (Bit 7)                             */
#define MDR_UART_CR_LBE_Msk              (0x80UL)                  /*!< MDR_UART1 CR: LBE (Bitfield-Mask: 0x01)               */
#define MDR_UART_CR_TXE_Pos              (8UL)                     /*!< MDR_UART1 CR: TXE (Bit 8)                             */
#define MDR_UART_CR_TXE_Msk              (0x100UL)                 /*!< MDR_UART1 CR: TXE (Bitfield-Mask: 0x01)               */
#define MDR_UART_CR_RXE_Pos              (9UL)                     /*!< MDR_UART1 CR: RXE (Bit 9)                             */
#define MDR_UART_CR_RXE_Msk              (0x200UL)                 /*!< MDR_UART1 CR: RXE (Bitfield-Mask: 0x01)               */
#define MDR_UART_CR_DTR_Pos              (10UL)                    /*!< MDR_UART1 CR: DTR (Bit 10)                            */
#define MDR_UART_CR_DTR_Msk              (0x400UL)                 /*!< MDR_UART1 CR: DTR (Bitfield-Mask: 0x01)               */
#define MDR_UART_CR_RTS_Pos              (11UL)                    /*!< MDR_UART1 CR: RTS (Bit 11)                            */
#define MDR_UART_CR_RTS_Msk              (0x800UL)                 /*!< MDR_UART1 CR: RTS (Bitfield-Mask: 0x01)               */
#define MDR_UART_CR_Out1_Pos             (12UL)                    /*!< MDR_UART1 CR: Out1 (Bit 12)                           */
#define MDR_UART_CR_Out1_Msk             (0x1000UL)                /*!< MDR_UART1 CR: Out1 (Bitfield-Mask: 0x01)              */
#define MDR_UART_CR_Out2_Pos             (13UL)                    /*!< MDR_UART1 CR: Out2 (Bit 13)                           */
#define MDR_UART_CR_Out2_Msk             (0x2000UL)                /*!< MDR_UART1 CR: Out2 (Bitfield-Mask: 0x01)              */
#define MDR_UART_CR_RTSEn_Pos            (14UL)                    /*!< MDR_UART1 CR: RTSEn (Bit 14)                          */
#define MDR_UART_CR_RTSEn_Msk            (0x4000UL)                /*!< MDR_UART1 CR: RTSEn (Bitfield-Mask: 0x01)             */
#define MDR_UART_CR_CTSEn_Pos            (15UL)                    /*!< MDR_UART1 CR: CTSEn (Bit 15)                          */
#define MDR_UART_CR_CTSEn_Msk            (0x8000UL)                /*!< MDR_UART1 CR: CTSEn (Bitfield-Mask: 0x01)             */


///* ===============================================  IFLS - IRQ Flags Level Select =========================================== */
//typedef enum {
//  UART_FIFO_2,
//  UART_FIFO_4,
//  UART_FIFO_8,
//  UART_FIFO_12,
//  UART_FIFO_14
//} MDR_UART_EventFIFO;

//typedef struct {
//  __IOM MDR_UART_EventFIFO  TXIFLSES   : 3;            /*!< [2..0] IRQ FIFO_TX level                                         */
//  __IOM MDR_UART_EventFIFO  RXIFLSES   : 3;            /*!< [5..3] IRQ FIFO_RX level                                         */
//  __IM  uint32_t                       : 26;
//} MDR_UART_IFLS_Bits;

//#define MDR_UART_IFLS_TXIFLSES_Pos       (0UL)                     /*!< MDR_UART1 IFLS: TXIFLSES (Bit 0)                      */
//#define MDR_UART_IFLS_TXIFLSES_Msk       (0x7UL)                   /*!< MDR_UART1 IFLS: TXIFLSES (Bitfield-Mask: 0x07)        */
//#define MDR_UART_IFLS_RXIFLSES_Pos       (3UL)                     /*!< MDR_UART1 IFLS: RXIFLSES (Bit 3)                      */
//#define MDR_UART_IFLS_RXIFLSES_Msk       (0x38UL)                  /*!< MDR_UART1 IFLS: RXIFLSES (Bitfield-Mask: 0x07)        */


/* ==========================================  IMSC - IRQ Mask Set/Clear register ======================================== */
/* ==========================================  RIS  - Raw Interrupt Status register  ===================================== */
/* ==========================================  MIS  - Masked Interrupt Status register =================================== */
/* ==========================================  IC   - Interrupt Clear register =========================================== */

typedef struct {
  __IOM MDR_OnOff RIM     : 1;            /*!< [0..0] RI Modem IRQ Mask                                                  */
  __IOM MDR_OnOff STCM    : 1;            /*!< [1..1] STC Modem IRQ Mask                                                 */
  __IOM MDR_OnOff DCDM    : 1;            /*!< [2..2] DCD Modem IRQ Mask                                                 */
  __IOM MDR_OnOff DSRM    : 1;            /*!< [3..3] DSR Modem IRQ Mask                                                 */
  __IOM MDR_OnOff RX      : 1;            /*!< [4..4] RX IRQ Mask                                                        */
  __IOM MDR_OnOff TX      : 1;            /*!< [5..5] TX IRQ Mask                                                        */
  __IOM MDR_OnOff RT      : 1;            /*!< [6..6] RX Timeout IRQ Mask                                                */
  __IOM MDR_OnOff FE      : 1;            /*!< [7..7] Frame Error IRQ Mask                                               */
  __IOM MDR_OnOff PE      : 1;            /*!< [8..8] Parity Error IRQ Mask                                              */
  __IOM MDR_OnOff BE      : 1;            /*!< [9..9] BreakLine IRQ Mask                                                 */
  __IOM MDR_OnOff OE      : 1;            /*!< [10..10] Overrun FIFO_RX IRQ Mask                                         */
  __IM  uint32_t          : 21;
} MDR_UART_EventClr_Bits;

#define MDR_UART_EVENT_CLR_RIM_Pos         (0UL)                     /*!< MDR_UART1 IMSC: RIM_IM (Bit 0)                        */
#define MDR_UART_EVENT_CLR_RIM_Msk         (0x1UL)                   /*!< MDR_UART1 IMSC: RIM_IM (Bitfield-Mask: 0x01)          */
#define MDR_UART_EVENT_CLR_STCM_Pos        (1UL)                     /*!< MDR_UART1 IMSC: STCM_IM (Bit 1)                       */
#define MDR_UART_EVENT_CLR_STCM_Msk        (0x2UL)                   /*!< MDR_UART1 IMSC: STCM_IM (Bitfield-Mask: 0x01)         */
#define MDR_UART_EVENT_CLR_DCDM_Pos        (2UL)                     /*!< MDR_UART1 IMSC: DCDM_IM (Bit 2)                       */
#define MDR_UART_EVENT_CLR_DCDM_Msk        (0x4UL)                   /*!< MDR_UART1 IMSC: DCDM_IM (Bitfield-Mask: 0x01)         */
#define MDR_UART_EVENT_CLR_DSRM_Pos        (3UL)                     /*!< MDR_UART1 IMSC: DSRM_IM (Bit 3)                       */
#define MDR_UART_EVENT_CLR_DSRM_Msk        (0x8UL)                   /*!< MDR_UART1 IMSC: DSRM_IM (Bitfield-Mask: 0x01)         */
#define MDR_UART_EVENT_CLR_RX_Pos          (4UL)                     /*!< MDR_UART1 IMSC: RX_IM (Bit 4)                         */
#define MDR_UART_EVENT_CLR_RX_Msk          (0x10UL)                  /*!< MDR_UART1 IMSC: RX_IM (Bitfield-Mask: 0x01)           */
#define MDR_UART_EVENT_CLR_TX_Pos          (5UL)                     /*!< MDR_UART1 IMSC: TX_IM (Bit 5)                         */
#define MDR_UART_EVENT_CLR_TX_Msk          (0x20UL)                  /*!< MDR_UART1 IMSC: TX_IM (Bitfield-Mask: 0x01)           */
#define MDR_UART_EVENT_CLR_RT_Pos          (6UL)                     /*!< MDR_UART1 IMSC: RT_IM (Bit 6)                         */
#define MDR_UART_EVENT_CLR_RT_Msk          (0x40UL)                  /*!< MDR_UART1 IMSC: RT_IM (Bitfield-Mask: 0x01)           */
#define MDR_UART_EVENT_CLR_FE_Pos          (7UL)                     /*!< MDR_UART1 IMSC: FE_IM (Bit 7)                         */
#define MDR_UART_EVENT_CLR_FE_Msk          (0x80UL)                  /*!< MDR_UART1 IMSC: FE_IM (Bitfield-Mask: 0x01)           */
#define MDR_UART_EVENT_CLR_PE_Pos          (8UL)                     /*!< MDR_UART1 IMSC: PE_IM (Bit 8)                         */
#define MDR_UART_EVENT_CLR_PE_Msk          (0x100UL)                 /*!< MDR_UART1 IMSC: PE_IM (Bitfield-Mask: 0x01)           */
#define MDR_UART_EVENT_CLR_BE_Pos          (9UL)                     /*!< MDR_UART1 IMSC: BE_IM (Bit 9)                         */
#define MDR_UART_EVENT_CLR_BE_Msk          (0x200UL)                 /*!< MDR_UART1 IMSC: BE_IM (Bitfield-Mask: 0x01)           */
#define MDR_UART_EVENT_CLR_OE_Pos          (10UL)                    /*!< MDR_UART1 IMSC: OE_IM (Bit 10)                        */
#define MDR_UART_EVENT_CLR_OE_Msk          (0x400UL)                 /*!< MDR_UART1 IMSC: OE_IM (Bitfield-Mask: 0x01)           */

#define MDR_UART_EVENT_ClearAll         0x07FFUL

/* ==========================================  DMACR  - DMA Control register ========================================== */
typedef struct {
  __IOM MDR_OnOff RXDMAE   : 1;            /*!< [0..0] RX DMA Enable                                                      */
  __IOM MDR_OnOff TXDMAE   : 1;            /*!< [1..1] TX DMA Enable                                                      */
  __IOM MDR_OnOff DMAonErr : 1;            /*!< [2..2] Disable DMA req on Error                                           */
  __IM  uint32_t           : 29;
} MDR_UART_DMACR_Bits;

#define MDR_UART_DMACR_RXDMAE_Pos        (0UL)                     /*!< MDR_UART1 DMACR: RXDMAE (Bit 0)                   */
#define MDR_UART_DMACR_RXDMAE_Msk        (0x1UL)                   /*!< MDR_UART1 DMACR: RXDMAE (Bitfield-Mask: 0x01)     */
#define MDR_UART_DMACR_TXDMAE_Pos        (1UL)                     /*!< MDR_UART1 DMACR: TXDMAE (Bit 1)                   */
#define MDR_UART_DMACR_TXDMAE_Msk        (0x2UL)                   /*!< MDR_UART1 DMACR: TXDMAE (Bitfield-Mask: 0x01)     */
#define MDR_UART_DMACR_DMAonErr_Pos      (2UL)                     /*!< MDR_UART1 DMACR: DMAonErr (Bit 2)                 */
#define MDR_UART_DMACR_DMAonErr_Msk      (0x4UL)                   /*!< MDR_UART1 DMACR: DMAonErr (Bitfield-Mask: 0x01)   */


/* ==========================================  TCR  - Test Control register ========================================== */
typedef struct {
  __IOM MDR_OnOff ITEN       : 1;            /*!< [0..0] Test Mode Enable                                                   */
  __IOM MDR_OnOff TestFIFO   : 1;            /*!< [1..1] FIFO test mode                                                     */
  __IOM MDR_OnOff SIRTest    : 1;            /*!< [2..2] IrDA test mode                                                     */
  __IM  uint32_t             : 29;
} MDR_UART_TCR_Bits;

#define MDR_UART_TCR_ITEN_Pos            (0UL)                     /*!< MDR_UART1 TCR: ITEN (Bit 0)                         */
#define MDR_UART_TCR_ITEN_Msk            (0x1UL)                   /*!< MDR_UART1 TCR: ITEN (Bitfield-Mask: 0x01)           */
#define MDR_UART_TCR_TestFIFO_Pos        (1UL)                     /*!< MDR_UART1 TCR: TestFIFO (Bit 1)                     */
#define MDR_UART_TCR_TestFIFO_Msk        (0x2UL)                   /*!< MDR_UART1 TCR: TestFIFO (Bitfield-Mask: 0x01)       */
#define MDR_UART_TCR_SIRTest_Pos         (2UL)                     /*!< MDR_UART1 TCR: SIRTest (Bit 2)                      */
#define MDR_UART_TCR_SIRTest_Msk         (0x4UL)                   /*!< MDR_UART1 TCR: SIRTest (Bitfield-Mask: 0x01)        */



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

#endif  //_MDR_UART_DEFS_H
