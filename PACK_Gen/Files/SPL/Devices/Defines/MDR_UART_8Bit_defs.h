#ifndef _MDR_UART_8BIT_DEFS_H
#define _MDR_UART_8BIT_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <MDR_UART_defs.h>
#include <MDR_Types.h>


#define MDR_UART_FIFO_LEN   16  
  
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


/* ====================================================  DR  ==================================================== */
typedef struct {
  __IOM uint8_t   DATA       : 8;            /*!< [7..0] Data FIFO access                                                   */
  __IOM MDR_OnOff FE         : 1;            /*!< [8..8] Stop Bit Error                                                     */
  __IOM MDR_OnOff PE         : 1;            /*!< [9..9] Parity Error                                                       */
  __IOM MDR_OnOff BE         : 1;            /*!< [10..10] Break Error - Line RX is LOW for 2 words long                    */
  __IOM MDR_OnOff OE         : 1;            /*!< [11..11] Overrun FIFO_RX                                                  */
  __IM  uint32_t             : 20;
} MDR_UART_DR_Bits;

#define MDR_UART_DR_DATA_Pos             (0UL)                     /*!< MDR_UART1 DR: DATA (Bit 0)                            */
#define MDR_UART_DR_DATA_Msk             (0xffUL)                  /*!< MDR_UART1 DR: DATA (Bitfield-Mask: 0xff)              */
#define MDR_UART_DR_FE_Pos               (8UL)                     /*!< MDR_UART1 DR: FE (Bit 8)                              */
#define MDR_UART_DR_FE_Msk               (0x100UL)                 /*!< MDR_UART1 DR: FE (Bitfield-Mask: 0x01)                */
#define MDR_UART_DR_PE_Pos               (9UL)                     /*!< MDR_UART1 DR: PE (Bit 9)                              */
#define MDR_UART_DR_PE_Msk               (0x200UL)                 /*!< MDR_UART1 DR: PE (Bitfield-Mask: 0x01)                */
#define MDR_UART_DR_BE_Pos               (10UL)                    /*!< MDR_UART1 DR: BE (Bit 10)                             */
#define MDR_UART_DR_BE_Msk               (0x400UL)                 /*!< MDR_UART1 DR: BE (Bitfield-Mask: 0x01)                */
#define MDR_UART_DR_OE_Pos               (11UL)                    /*!< MDR_UART1 DR: OE (Bit 11)                             */
#define MDR_UART_DR_OE_Msk               (0x800UL)                 /*!< MDR_UART1 DR: OE (Bitfield-Mask: 0x01)                */

#define MDR_UART_DATA_MASK        MDR_UART_DR_DATA_Msk

/* ===============================================  LCR_H - Line Control Register =========================================== */
typedef enum {
  UART_BITS_5,
  UART_BITS_6,
  UART_BITS_7,
  UART_BITS_8
} MDR_UART_WLEN;

typedef struct {
  __IOM MDR_OnOff     BRK        : 1;            /*!< [0..0] Send Break - TX LOW for 2 words                               */
  __IOM MDR_OnOff     PEN        : 1;            /*!< [1..1] Parity Enable                                                 */
  __IOM MDR_OnOff     EPS        : 1;            /*!< [2..2] Even Parity Select                                            */
  __IOM MDR_OnOff     STP2       : 1;            /*!< [3..3] Double Stop Bits Enable                                       */
  __IOM MDR_OnOff     FEN        : 1;            /*!< [4..4] FIFOs Enable                                                  */
  __IOM MDR_UART_WLEN WLEN       : 2;            /*!< [6..5] Word Length                                                   */
  __IOM MDR_OnOff     SPS        : 1;            /*!< [7..7] Stick Parity Select                                           */
  __IM  uint32_t                 : 24;
} MDR_UART_LCRH_Bits;

#define MDR_UART_LCR_H_BRK_Pos           (0UL)                     /*!< MDR_UART1 LCR_H: BRK (Bit 0)                       */
#define MDR_UART_LCR_H_BRK_Msk           (0x1UL)                   /*!< MDR_UART1 LCR_H: BRK (Bitfield-Mask: 0x01)         */
#define MDR_UART_LCR_H_PEN_Pos           (1UL)                     /*!< MDR_UART1 LCR_H: PEN (Bit 1)                       */
#define MDR_UART_LCR_H_PEN_Msk           (0x2UL)                   /*!< MDR_UART1 LCR_H: PEN (Bitfield-Mask: 0x01)         */
#define MDR_UART_LCR_H_EPS_Pos           (2UL)                     /*!< MDR_UART1 LCR_H: EPS (Bit 2)                       */
#define MDR_UART_LCR_H_EPS_Msk           (0x4UL)                   /*!< MDR_UART1 LCR_H: EPS (Bitfield-Mask: 0x01)         */
#define MDR_UART_LCR_H_STP2_Pos          (3UL)                     /*!< MDR_UART1 LCR_H: STP2 (Bit 3)                      */
#define MDR_UART_LCR_H_STP2_Msk          (0x8UL)                   /*!< MDR_UART1 LCR_H: STP2 (Bitfield-Mask: 0x01)        */
#define MDR_UART_LCR_H_FEN_Pos           (4UL)                     /*!< MDR_UART1 LCR_H: FEN (Bit 4)                       */
#define MDR_UART_LCR_H_FEN_Msk           (0x10UL)                  /*!< MDR_UART1 LCR_H: FEN (Bitfield-Mask: 0x01)         */
#define MDR_UART_LCR_H_WLEN_Pos          (5UL)                     /*!< MDR_UART1 LCR_H: WLEN (Bit 5)                      */
#define MDR_UART_LCR_H_WLEN_Msk          (0x60UL)                  /*!< MDR_UART1 LCR_H: WLEN (Bitfield-Mask: 0x03)        */
#define MDR_UART_LCR_H_SPS_Pos           (7UL)                     /*!< MDR_UART1 LCR_H: SPS (Bit 7)                       */
#define MDR_UART_LCR_H_SPS_Msk           (0x80UL)                  /*!< MDR_UART1 LCR_H: SPS (Bitfield-Mask: 0x01)         */


/* ===============================================  IFLS - IRQ Flags Level Select =========================================== */
typedef enum {
  UART_FIFO_2,
  UART_FIFO_4,
  UART_FIFO_8,
  UART_FIFO_12,
  UART_FIFO_14
} MDR_UART_EventFIFO;

#define   MDR_UART_FIFO_1p8     UART_FIFO_2
#define   MDR_UART_FIFO_1p4     UART_FIFO_4
#define   MDR_UART_FIFO_1p2     UART_FIFO_8
#define   MDR_UART_FIFO_3p4     UART_FIFO_12
#define   MDR_UART_FIFO_7p8     UART_FIFO_14

typedef struct {
  __IOM MDR_UART_EventFIFO  TXIFLSES   : 3;            /*!< [2..0] IRQ FIFO_TX level                                         */
  __IOM MDR_UART_EventFIFO  RXIFLSES   : 3;            /*!< [5..3] IRQ FIFO_RX level                                         */
  __IM  uint32_t                       : 26;
} MDR_UART_IFLS_Bits;

#define MDR_UART_IFLS_TXIFLSES_Pos       (0UL)                     /*!< MDR_UART1 IFLS: TXIFLSES (Bit 0)                      */
#define MDR_UART_IFLS_TXIFLSES_Msk       (0x7UL)                   /*!< MDR_UART1 IFLS: TXIFLSES (Bitfield-Mask: 0x07)        */
#define MDR_UART_IFLS_RXIFLSES_Pos       (3UL)                     /*!< MDR_UART1 IFLS: RXIFLSES (Bit 3)                      */
#define MDR_UART_IFLS_RXIFLSES_Msk       (0x38UL)                  /*!< MDR_UART1 IFLS: RXIFLSES (Bitfield-Mask: 0x07)        */




/* ==========================================  IMSC - IRQ Mask Set/Clear register ======================================== */
/* ==========================================  RIS  - Raw Interrupt Status register  ===================================== */
/* ==========================================  MIS  - Masked Interrupt Status register =================================== */

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
} MDR_UART_Event_Bits;

#define MDR_UART_EVENT_RIM_Pos         (0UL)                     /*!< MDR_UART1 IMSC: RIM_IM (Bit 0)                        */
#define MDR_UART_EVENT_RIM_Msk         (0x1UL)                   /*!< MDR_UART1 IMSC: RIM_IM (Bitfield-Mask: 0x01)          */
#define MDR_UART_EVENT_STCM_Pos        (1UL)                     /*!< MDR_UART1 IMSC: STCM_IM (Bit 1)                       */
#define MDR_UART_EVENT_STCM_Msk        (0x2UL)                   /*!< MDR_UART1 IMSC: STCM_IM (Bitfield-Mask: 0x01)         */
#define MDR_UART_EVENT_DCDM_Pos        (2UL)                     /*!< MDR_UART1 IMSC: DCDM_IM (Bit 2)                       */
#define MDR_UART_EVENT_DCDM_Msk        (0x4UL)                   /*!< MDR_UART1 IMSC: DCDM_IM (Bitfield-Mask: 0x01)         */
#define MDR_UART_EVENT_DSRM_Pos        (3UL)                     /*!< MDR_UART1 IMSC: DSRM_IM (Bit 3)                       */
#define MDR_UART_EVENT_DSRM_Msk        (0x8UL)                   /*!< MDR_UART1 IMSC: DSRM_IM (Bitfield-Mask: 0x01)         */
#define MDR_UART_EVENT_RX_Pos          (4UL)                     /*!< MDR_UART1 IMSC: RX_IM (Bit 4)                         */
#define MDR_UART_EVENT_RX_Msk          (0x10UL)                  /*!< MDR_UART1 IMSC: RX_IM (Bitfield-Mask: 0x01)           */
#define MDR_UART_EVENT_TX_Pos          (5UL)                     /*!< MDR_UART1 IMSC: TX_IM (Bit 5)                         */
#define MDR_UART_EVENT_TX_Msk          (0x20UL)                  /*!< MDR_UART1 IMSC: TX_IM (Bitfield-Mask: 0x01)           */
#define MDR_UART_EVENT_RT_Pos          (6UL)                     /*!< MDR_UART1 IMSC: RT_IM (Bit 6)                         */
#define MDR_UART_EVENT_RT_Msk          (0x40UL)                  /*!< MDR_UART1 IMSC: RT_IM (Bitfield-Mask: 0x01)           */
#define MDR_UART_EVENT_FE_Pos          (7UL)                     /*!< MDR_UART1 IMSC: FE_IM (Bit 7)                         */
#define MDR_UART_EVENT_FE_Msk          (0x80UL)                  /*!< MDR_UART1 IMSC: FE_IM (Bitfield-Mask: 0x01)           */
#define MDR_UART_EVENT_PE_Pos          (8UL)                     /*!< MDR_UART1 IMSC: PE_IM (Bit 8)                         */
#define MDR_UART_EVENT_PE_Msk          (0x100UL)                 /*!< MDR_UART1 IMSC: PE_IM (Bitfield-Mask: 0x01)           */
#define MDR_UART_EVENT_BE_Pos          (9UL)                     /*!< MDR_UART1 IMSC: BE_IM (Bit 9)                         */
#define MDR_UART_EVENT_BE_Msk          (0x200UL)                 /*!< MDR_UART1 IMSC: BE_IM (Bitfield-Mask: 0x01)           */
#define MDR_UART_EVENT_OE_Pos          (10UL)                    /*!< MDR_UART1 IMSC: OE_IM (Bit 10)                        */
#define MDR_UART_EVENT_OE_Msk          (0x400UL)                 /*!< MDR_UART1 IMSC: OE_IM (Bitfield-Mask: 0x01)           */


/* ====================================== MDR_UART_Type =================================================== */
#define MDR_UART_EventIE_Bits   MDR_UART_Event_Bits

typedef struct {                                /*!< (@ 0x40030000) MDR_UART1 Structure                     */
  union {
    __IOM uint32_t        DR;                   /*!< (@ 0x00000000) Data Register                           */
    MDR_UART_DR_Bits      DR_b;
  } ;  
  union {
    __IOM uint32_t        RSR_ECR;              /*!< (@ 0x00000004) Receive Status and Error Clear Register */
    MDR_UART_Error_Bits   RSR_ECR_b;
  } ;
  __IM  uint32_t          RESERVED[4];  
  union {
    __IM  uint32_t        FR;                   /*!< (@ 0x00000018) Flag Register                           */
    MDR_UART_FR_Bits      FR_b;
  } ;
  __IM  uint32_t          RESERVED1;
  union {
    __IOM uint32_t        ILPR;                 /*!< (@ 0x00000020) IrDA Low-Power Counter                  */
    MDR_UART_ILPR_Bits    ILPR_b;
  } ;
  union {
    __IOM uint32_t        IBRD;                 /*!< (@ 0x00000024) Integer BaudRate Divisor                */
    MDR_UART_IBRD_Bits    IBRD_b;
  } ; 
  union {
    __IOM uint32_t        FBRD;                 /*!< (@ 0x00000028) Fractional BaudRate Divisor             */
    MDR_UART_FBRD_Bits    FBRD_b;
  } ;  
  union {
    __IOM uint32_t        LCR_H;                /*!< (@ 0x0000002C) Line Control Register                   */
    MDR_UART_LCRH_Bits    LCR_H_b;
  } ;  
  union {
    __IOM uint32_t        CR;                   /*!< (@ 0x00000030) Control Register                        */
    MDR_UART_CR_Bits      CR_b;
  } ;  
  union {
    __IOM uint32_t        IFLS;                 /*!< (@ 0x00000034) IRQ FIFO Level                          */
    MDR_UART_IFLS_Bits    IFLS_b;
  } ;
  union {
    __IOM uint32_t        IMSC;                 /*!< (@ 0x00000038) IRQ Mask Set Clear                      */
    MDR_UART_Event_Bits   IMSC_b;    
  } ;  
  union {
    __IM  uint32_t        RIS;                  /*!< (@ 0x0000003C) Raw IQR Status Register                 */
    MDR_UART_EventIE_Bits RIS_b;
  } ;  
  union {
    __IM  uint32_t        MIS;                  /*!< (@ 0x00000040) Masked IQR Status Register              */
    MDR_UART_EventIE_Bits MIS_b;
  } ;
  union {
    __OM  uint32_t          ICR;                  /*!< (@ 0x00000044) IRQ Clear Register                      */
    MDR_UART_EventClr_Bits  ICR_b;
  } ;
  union {
    __IOM uint32_t        DMACR;                /*!< (@ 0x00000048) DMA Control Register                    */
    MDR_UART_DMACR_Bits   DMACR_b;
  } ;
  __IM  uint32_t          RESERVED2[13]; 
  union {
    __IOM uint32_t        TCR;                    /*!< (@ 0x00000080) Test Control Register                   */
    MDR_UART_TCR_Bits     TCR_b;
  } ;
} MDR_UART_Type;                               /*!< Size = 132 (0x84) */


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

#endif  //_MDR_UART_8BIT_DEFS_H
