#ifndef _MDR_SSP_DEF_H
#define _MDR_SSP_DEF_H

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

/*                                          SSP - Synchronous Serial Port                                                       */

/* ========================================  CR0 - Control Register 0  ======================================================= */
typedef enum {
  SSP_DataBits_4  = 3,
  SSP_DataBits_5  = 4,
  SSP_DataBits_6  = 5,
  SSP_DataBits_7  = 6,
  SSP_DataBits_8  = 7,
  SSP_DataBits_9  = 8,
  SSP_DataBits_10 = 9,
  SSP_DataBits_11 = 10,
  SSP_DataBits_12 = 11,
  SSP_DataBits_13 = 12,
  SSP_DataBits_14 = 13,
  SSP_DataBits_15 = 14,
  SSP_DataBits_16 = 15,
} MDR_SSP_DataBits;

#define MDR_SSP_DATABITS_MIN    SSP_DataBits_4
#define MDR_SSP_DATABITS_MAX    SSP_DataBits_16

typedef enum {
  SSP_Frame_SPI = 0,
  SSP_Frame_SSI = 1,
  SSP_Frame_Microwire = 2
} MDR_SSP_FrameFormat;

typedef enum {
  SSP_CLK_PO_IdleLo   = 0,
  SSP_CLK_PO_IdleHigh = 1
} MDR_SPI_CLK_Polarity;

typedef enum {
  SSP_CLK_PH_CapOnRise  = 0,
  SSP_CLK_PH_CapOnFall  = 1
} MDR_SPI_CLK_Phase;


/* ========================================  SR - StatusRegister   =========================================================== */
typedef struct {
      __IM  MDR_OnOff TFE        : 1;            /*!< [0..0] FIFO_TX is Empty                                                   */
      __IM  MDR_OnOff TNF        : 1;            /*!< [1..1] FIFO_TX is Not Full                                                */
      __IM  MDR_OnOff RNE        : 1;            /*!< [2..2] FIFO_RX is Not Empty                                               */
      __IM  MDR_OnOff RFF        : 1;            /*!< [3..3] FIFO_RX is Full                                                    */
      __IM  MDR_OnOff BSY        : 1;            /*!< [4..4] Transfer in progress                                               */
      __IM  uint32_t             : 27;
} MDR_SSP_SR_Bits;

#define MDR_SSP_SR_TFE_Pos               (0UL)                     /*!< MDR_SSP1 SR: TFE (Bit 0)                              */
#define MDR_SSP_SR_TFE_Msk               (0x1UL)                   /*!< MDR_SSP1 SR: TFE (Bitfield-Mask: 0x01)                */
#define MDR_SSP_SR_TNF_Pos               (1UL)                     /*!< MDR_SSP1 SR: TNF (Bit 1)                              */
#define MDR_SSP_SR_TNF_Msk               (0x2UL)                   /*!< MDR_SSP1 SR: TNF (Bitfield-Mask: 0x01)                */
#define MDR_SSP_SR_RNE_Pos               (2UL)                     /*!< MDR_SSP1 SR: RNE (Bit 2)                              */
#define MDR_SSP_SR_RNE_Msk               (0x4UL)                   /*!< MDR_SSP1 SR: RNE (Bitfield-Mask: 0x01)                */
#define MDR_SSP_SR_RFF_Pos               (3UL)                     /*!< MDR_SSP1 SR: RFF (Bit 3)                              */
#define MDR_SSP_SR_RFF_Msk               (0x8UL)                   /*!< MDR_SSP1 SR: RFF (Bitfield-Mask: 0x01)                */
#define MDR_SSP_SR_BSY_Pos               (4UL)                     /*!< MDR_SSP1 SR: BSY (Bit 4)                              */
#define MDR_SSP_SR_BSY_Msk               (0x10UL)                  /*!< MDR_SSP1 SR: BSY (Bitfield-Mask: 0x01)                */

//  Переименование флагов для читабельности
typedef struct {
      MDR_OnOff TX_Empty    : 1;            /*!< [0..0] FIFO_TX is Empty                                                   */
      MDR_OnOff TX_NotFull  : 1;            /*!< [1..1] FIFO_TX is Not Full                                                */
      MDR_OnOff RX_NotEmpty : 1;            /*!< [2..2] FIFO_RX is Not Empty                                               */
      MDR_OnOff RX_Full     : 1;            /*!< [3..3] FIFO_RX is Full                                                    */
      MDR_OnOff Busy        : 1;            /*!< [4..4] Transfer in progress                                               */
      uint32_t              : 27;
} MDR_SSP_StatusFlags;

/* =====================================  CPSR - Clock prescaller register  ================================================== */
typedef struct {
      __IOM uint8_t  CPSDVSR    : 8;            /*!< [7..0] Clock Prescaller - ONLY EVEN NUMBER (bit0 - always set to 0)       */
      __IM uint32_t             : 24;
} MDR_SSP_CPSR_Bits;

#define MDR_SSP_CPSR_CPSDVSR_Pos         (0UL)                     /*!< MDR_SSP1 CPSR: CPSDVSR (Bit 0)                        */
#define MDR_SSP_CPSR_CPSDVSR_Msk         (0xffUL)                  /*!< MDR_SSP1 CPSR: CPSDVSR (Bitfield-Mask: 0xff)          */

#define MDR_SSP_CPSDVSR_MIN   2
#define MDR_SSP_CPSDVSR_MAX   254


/* ====================================== ICR - Interrupt Clear Register  =================================================== */
typedef struct {
      __OM  MDR_OnOff RORIC     : 1;            /*!< [0..0] Clear FIFO_RX overrun flag                               */
      __OM  MDR_OnOff RTIC      : 1;            /*!< [1..1] Clear RX timeout flag                                    */
      __IM  uint32_t            : 30;
} MDR_SSP_IC_Bits;

#define MDR_SSP_ICR_RORIC_Pos            (0UL)                     /*!< MDR_SSP1 ICR: RORIC (Bit 0)                           */
#define MDR_SSP_ICR_RORIC_Msk            (0x1UL)                   /*!< MDR_SSP1 ICR: RORIC (Bitfield-Mask: 0x01)             */
#define MDR_SSP_ICR_RTIC_Pos             (1UL)                     /*!< MDR_SSP1 ICR: RTIC (Bit 1)                            */
#define MDR_SSP_ICR_RTIC_Msk             (0x2UL)                   /*!< MDR_SSP1 ICR: RTIC (Bitfield-Mask: 0x01)              */

/* ====================================== DMACR - Control Register    ======================================================== */
typedef struct {
      __IOM MDR_OnOff RXDMAE     : 1;                /*!< [0..0] Enable DMA by FIFO_RX has data                                */
      __IOM MDR_OnOff TXDMAE     : 1;                /*!< [1..1] Enable DMA by FIFO_TX not Full                                */
      __IM  uint32_t             : 30;
} MDR_SSP_DMACR_Bits;

#define MDR_SSP_DMACR_RXDMAE_Pos         (0UL)                     /*!< MDR_SSP1 DMACR: RXDMAE (Bit 0)                        */
#define MDR_SSP_DMACR_RXDMAE_Msk         (0x1UL)                   /*!< MDR_SSP1 DMACR: RXDMAE (Bitfield-Mask: 0x01)          */
#define MDR_SSP_DMACR_TXDMAE_Pos         (1UL)                     /*!< MDR_SSP1 DMACR: TXDMAE (Bit 1)                        */
#define MDR_SSP_DMACR_TXDMAE_Msk         (0x2UL)                   /*!< MDR_SSP1 DMACR: TXDMAE (Bitfield-Mask: 0x01)          */




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

#endif  //  _MDR_SSP_DEF_H
