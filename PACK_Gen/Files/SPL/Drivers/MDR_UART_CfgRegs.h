#ifndef _MDR_UART_CFGREGS_H
#define _MDR_UART_CFGREGS_H


#ifdef __cplusplus
extern "C" {
#endif

#include <MDR_UART_defs.h>


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


//==================    CfgRegs - выборка только конфигурационных регистров ===============


typedef struct {
  uint8_t   DATA       : 8;            /*!< [7..0] Data FIFO access                                                   */
  MDR_OnOff FE         : 1;            /*!< [8..8] Stop Bit Error                                                     */
  MDR_OnOff PE         : 1;            /*!< [9..9] Parity Error                                                       */
  MDR_OnOff BE         : 1;            /*!< [10..10] Break Error - Line RX is LOW for 2 words long                    */
  MDR_OnOff OE         : 1;            /*!< [11..11] Overrun FIFO_RX                                                  */
  uint16_t             : 4;
} MDR_UART_DataBits;

//  Status Flags
typedef struct {
  MDR_OnOff CTS        : 1;            /*!< [0..0] Modem Clear To Send                                                */
  MDR_OnOff DSR        : 1;            /*!< [1..1] Modem Data Set Ready                                               */
  MDR_OnOff DCD        : 1;            /*!< [2..2] Modem Data Carrier Detect                                          */
  MDR_OnOff Busy       : 1;            /*!< [3..3] Transmitting data                                                  */
  MDR_OnOff RxEmpty    : 1;            /*!< [4..4] FIFO_RX Empty status                                               */
  MDR_OnOff TxFull     : 1;            /*!< [5..5] FIFO_TX Full Status                                                */
  MDR_OnOff RxFull     : 1;            /*!< [6..6] FIFO_RX Full Status                                                */
  MDR_OnOff TxEmpty    : 1;            /*!< [7..7] FIFO_RX Empty status                                               */
  MDR_OnOff RI         : 1;            /*!< [8..8] Modem Ring Indicator                                               */
  uint32_t             : 23;
} MDR_UART_StatusBits;

#define MDR_UART_SFL_CTS              MDR_UART_FR_CTS_Msk
#define MDR_UART_SFL_DSR              MDR_UART_FR_DSR_Msk
#define MDR_UART_SFL_DCD              MDR_UART_FR_DCD_Msk
#define MDR_UART_SFL_Busy             MDR_UART_FR_BUSY_Msk
#define MDR_UART_SFL_RxEmpty          MDR_UART_FR_RXFE_Msk
#define MDR_UART_SFL_TxFull           MDR_UART_FR_TXFF_Msk
#define MDR_UART_SFL_RxFull           MDR_UART_FR_RXFF_Msk
#define MDR_UART_SFL_TxEmpty          MDR_UART_FR_TXFE_Msk
#define MDR_UART_SFL_RI               MDR_UART_FR_RI_Msk


//  Event Flags
typedef struct {
  MDR_OnOff RIM     : 1;            /*!< [0..0] RI Modem IRQ Mask                                                  */
  MDR_OnOff STCM    : 1;            /*!< [1..1] STC Modem IRQ Mask                                                 */
  MDR_OnOff DCDM    : 1;            /*!< [2..2] DCD Modem IRQ Mask                                                 */
  MDR_OnOff DSRM    : 1;            /*!< [3..3] DSR Modem IRQ Mask                                                 */
  MDR_OnOff RX      : 1;            /*!< [4..4] RX IRQ Mask                                                        */
  MDR_OnOff TX      : 1;            /*!< [5..5] TX IRQ Mask                                                        */
  MDR_OnOff RT      : 1;            /*!< [6..6] RX Timeout IRQ Mask                                                */
  MDR_OnOff FE      : 1;            /*!< [7..7] Frame Error IRQ Mask                                               */
  MDR_OnOff PE      : 1;            /*!< [8..8] Parity Error IRQ Mask                                              */
  MDR_OnOff BE      : 1;            /*!< [9..9] BreakLine IRQ Mask                                                 */
  MDR_OnOff OE      : 1;            /*!< [10..10] Overrun FIFO_RX IRQ Mask                                         */
  uint32_t          : 21;
} MDR_UART_EventBits;

#define MDR_UART_EFL_RIM         MDR_UART_EVENT_RIM_Msk
#define MDR_UART_EFL_STCM        MDR_UART_EVENT_STCM_Msk
#define MDR_UART_EFL_DCDM        MDR_UART_EVENT_DCDM_Msk
#define MDR_UART_EFL_DSRM        MDR_UART_EVENT_DSRM_Msk
#define MDR_UART_EFL_RX          MDR_UART_EVENT_RX_Msk
#define MDR_UART_EFL_TX          MDR_UART_EVENT_TX_Msk
#define MDR_UART_EFL_RT          MDR_UART_EVENT_RT_Msk
#define MDR_UART_EFL_FE          MDR_UART_EVENT_FE_Msk
#define MDR_UART_EFL_PE          MDR_UART_EVENT_PE_Msk
#define MDR_UART_EFL_BE          MDR_UART_EVENT_BE_Msk
#define MDR_UART_EFL_OE          MDR_UART_EVENT_OE_Msk


typedef struct {
  uint32_t DVSR       : 8;
  uint32_t reserved   : 24;
} MDR_UART_ILPR_CfgBits;

typedef struct {
  uint32_t Baud_DivInt : 16;
  uint32_t reserved    : 16;
} MDR_UART_IBRD_CfgBits;

typedef struct {
  uint32_t Baud_DivFrac : 6;
  uint32_t reserved     : 26;
} MDR_UART_FBRD_CfgBits;

typedef struct {
  MDR_OnOff     BRK        : 1;            /*!< [0..0] Send Break - TX LOW for 2 words                               */
  MDR_OnOff     PEN        : 1;            /*!< [1..1] Parity Enable                                                 */
  MDR_OnOff     EPS        : 1;            /*!< [2..2] Even Parity Select                                            */
  MDR_OnOff     STP2       : 1;            /*!< [3..3] Double Stop Bits Enable                                       */
  MDR_OnOff     FEN        : 1;            /*!< [4..4] FIFOs Enable                                                  */
  MDR_UART_WLEN WLEN       : 2;            /*!< [6..5] Word Length                                                   */
  MDR_OnOff     SPS        : 1;            /*!< [7..7] Stick Parity Select                                           */
  uint32_t      reserved   : 24;
} MDR_UART_LCRH_CfgBits;

typedef struct {
  MDR_OnOff EN         : 1;            /*!< [0..0] Enable UART                                                        */
  MDR_OnOff SIREN      : 1;            /*!< [1..1] IrDA Enable                                                        */
  MDR_OnOff SIRLP      : 1;            /*!< [2..2] IrDA Low-Power Enable                                              */
  uint32_t  reserved1  : 4;
  MDR_OnOff LBE        : 1;            /*!< [7..7] LoopBack Enable                                                    */
  MDR_OnOff TXE        : 1;            /*!< [8..8] Transmitter Enable                                                 */
  MDR_OnOff RXE        : 1;            /*!< [9..9] Receiver Enable                                                    */
  MDR_OnOff DTR        : 1;            /*!< [10..10] Data Transmit Ready                                              */
  MDR_OnOff RTS        : 1;            /*!< [11..11] Request To Send                                                  */
  MDR_OnOff Out1       : 1;            /*!< [12..12] Custom Modem Output1 - DCD                                       */
  MDR_OnOff Out2       : 1;            /*!< [13..13] Custom Modem Output2 - RI                                        */
  MDR_OnOff RTSEn      : 1;            /*!< [14..14] Hardware RTS Control                                             */
  MDR_OnOff CTSEn      : 1;            /*!< [15..15] Hardware CTS Control                                             */
  uint32_t  reserved2  : 16;
} MDR_UART_CR_CfgBits;

typedef struct {
  MDR_UART_EventFIFO  TXIFLSES   : 3;            /*!< [2..0] IRQ FIFO_TX level                                         */
  MDR_UART_EventFIFO  RXIFLSES   : 3;            /*!< [5..3] IRQ FIFO_RX level                                         */
  uint32_t            reserved   : 26;
} MDR_UART_IFLS_CfgBits;

typedef struct {
  MDR_OnOff DMA_RX_En     : 1;
  MDR_OnOff DMA_TX_En     : 1;
  MDR_OnOff DMA_StopOnErr : 1;
  uint32_t  reserved      : 29;
} MDR_UART_DMAFlags;

#define MDR_UART_DMA_RX_EN          MDR_UART_DMACR_RXDMAE_Msk
#define MDR_UART_DMA_TX_EN          MDR_UART_DMACR_RXDMAE_Msk
#define MDR_UART_DMA_StopOnErr_EN   MDR_UART_DMACR_DMAonErr_Msk

typedef struct {
  union {
    uint32_t                ILPR;
    MDR_UART_ILPR_CfgBits   ILPR_b;
  } ;  
  union {
    uint32_t                IBRD;
    MDR_UART_IBRD_CfgBits   IBRD_b;
  } ; 
  union {
    uint32_t                FBRD;
    MDR_UART_FBRD_CfgBits   FBRD_b;
  } ;  
  union {
    uint32_t                LCR_H;
    MDR_UART_LCRH_CfgBits   LCR_H_b;
  } ;  
  union {
    uint32_t                CR;
    MDR_UART_CR_CfgBits     CR_b;
  } ;  
  union {
    uint32_t                IFLS;
    MDR_UART_IFLS_CfgBits   IFLS_b;
  } ;
  union {
    uint32_t                IMSC;
    MDR_UART_EventBits      IMSC_b;    
  } ;  
  union {
    uint32_t                DMACR;
    MDR_UART_DMAFlags       DMACR_b;
  } ;
} MDR_UART_CfgRegs;


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


#endif  // _MDR_UART_CFGREGS_H

