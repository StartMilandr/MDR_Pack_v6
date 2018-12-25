#ifndef _MDRP_UART_DEFS_H
#define _MDRP_UART_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

//=======================   UART  =======================
typedef struct {
	__IO uint32_t	DR;                     /*!<UART Data Register */
	__IO uint32_t	RSR_ECR;                /*!<UART RSR Register */
	__I  uint32_t	RESERVED0[4];
	__IO uint32_t	FR;                     /*!<UART Flag Register */
	__I  uint32_t	RESERVED1;
	__IO uint32_t	ILPR;                   /*!< */
	__IO uint32_t	IBRD;                   /*!< */
	__IO uint32_t	FBRD;                   /*!< */
	__IO uint32_t	LCR_H;                  /*!<UART LCR_H Register */
	__IO uint32_t	CR;                     /*!<UART Command Register */
	__IO uint32_t	IFLS;                   /*!<UART IFLS Register */
	__IO uint32_t	IMSC;                   /*!<UART Interrupt Mask Register */
	__IO uint32_t	RIS;                    /*!<UART Interrupt Pending Register */
	__IO uint32_t	MIS;                    /*!<UART Masked Interrupt Pending Register */
	__IO uint32_t	ICR;                    /*!<UART Interrupt Clear Register */
	__IO uint32_t	DMACR;                  /*!<UART DMA Control Register */
}MDR_UART_TypeDef;

//  reg DR
/* Bit field positions: */
#define UART_DR_DATA_Pos                                   0
#define UART_DR_FE_Pos                                     8
#define UART_DR_PE_Pos                                     9
#define UART_DR_BE_Pos                                     10
#define UART_DR_OE_Pos                                     11
/* Bit field masks: */
#define UART_DR_DATA_Msk                                   ((uint32_t)0x000000FF)
#define UART_DR_FE                                         ((uint32_t)0x00000100)
#define UART_DR_PE                                         ((uint32_t)0x00000200)
#define UART_DR_BE                                         ((uint32_t)0x00000400)
#define UART_DR_OE                                         ((uint32_t)0x00000800)

//  reg RSR
/* Bit field positions: */
#define UART_RSR_ECR_FE_Pos                                0
#define UART_RSR_ECR_PE_Pos                                1
#define UART_RSR_ECR_BE_Pos                                2
#define UART_RSR_ECR_OE_Pos                                3
/* Bit field masks: */
#define UART_RSR_ECR_FE                                    ((uint32_t)0x00000001)
#define UART_RSR_ECR_PE                                    ((uint32_t)0x00000002)
#define UART_RSR_ECR_BE                                    ((uint32_t)0x00000004)
#define UART_RSR_ECR_OE                                    ((uint32_t)0x00000008)

//  reg FR
/* Bit field positions: */
#define UART_FR_CTS_Pos                                    0
#define UART_FR_DSR_Pos                                    1
#define UART_FR_DCD_Pos                                    2
#define UART_FR_BUSY_Pos                                   3
#define UART_FR_RXFE_Pos                                   4
#define UART_FR_TXFF_Pos                                   5
#define UART_FR_RXFF_Pos                                   6
#define UART_FR_TXFE_Pos                                   7
#define UART_FR_RI_Pos                                     8
/* Bit field masks: */
#define UART_FR_CTS                                        ((uint32_t)0x00000001)
#define UART_FR_DSR                                        ((uint32_t)0x00000002)
#define UART_FR_DCD                                        ((uint32_t)0x00000004)
#define UART_FR_BUSY                                       ((uint32_t)0x00000008)
#define UART_FR_RXFE                                       ((uint32_t)0x00000010)
#define UART_FR_TXFF                                       ((uint32_t)0x00000020)
#define UART_FR_RXFF                                       ((uint32_t)0x00000040)
#define UART_FR_TXFE                                       ((uint32_t)0x00000080)
#define UART_FR_RI                                         ((uint32_t)0x00000100)

//  reg ILPR
/* Bit field positions: */
#define UART_ILPR_ILPDVSR_Pos                              0
/* Bit field masks: */
#define UART_ILPR_ILPDVSR_Msk                              ((uint32_t)0x000000FF)

//  reg IBRD
/* Bit field positions: */
#define UART_IBRD_BAUD_DIVINT_Pos                          0
/* Bit field masks: */
#define UART_IBRD_BAUD_DIVINT_Msk                          ((uint32_t)0x0000FFFF)

//  reg FBRD
/* Bit field positions: */
#define UART_FBRD_BAUD_DIVFRAC_Pos                         0
/* Bit field masks: */
#define UART_FBRD_BAUD_DIVFRAC_Msk                         ((uint32_t)0x0000003F)

//  reg LCR
/* Bit field positions: */
#define UART_LCR_H_BRK_Pos                                 0
#define UART_LCR_H_PEN_Pos                                 1
#define UART_LCR_H_EPS_Pos                                 2
#define UART_LCR_H_STP2_Pos                                3
#define UART_LCR_H_FEN_Pos                                 4
#define UART_LCR_H_WLEN_Pos                                5
#define UART_LCR_H_SPS_Pos                                 7
/* Bit field masks: */
#define UART_LCR_H_BRK                                     ((uint32_t)0x00000001)
#define UART_LCR_H_PEN                                     ((uint32_t)0x00000002)
#define UART_LCR_H_EPS                                     ((uint32_t)0x00000004)
#define UART_LCR_H_STP2                                    ((uint32_t)0x00000008)
#define UART_LCR_H_FEN                                     ((uint32_t)0x00000010)
#define UART_LCR_H_WLEN_Msk                                ((uint32_t)0x00000060)
#define UART_LCR_H_SPS                                     ((uint32_t)0x00000080)

//  reg CR
/* Bit field positions: */
#define UART_CR_UARTEN_Pos                                 0
#define UART_CR_SIREN_Pos                                  1
#define UART_CR_SIRLP_Pos                                  2
#define UART_CR_LBE_Pos                                    7
#define UART_CR_TXE_Pos                                    8
#define UART_CR_RXE_Pos                                    9
#define UART_CR_DTR_Pos                                    10
#define UART_CR_RTS_Pos                                    11
#define UART_CR_OUT1_Pos                                   12
#define UART_CR_OUT2_Pos                                   13
#define UART_CR_RTSEN_Pos                                  14
#define UART_CR_CTSEN_Pos                                  15
/* Bit field masks: */
#define UART_CR_UARTEN                                     ((uint32_t)0x00000001)
#define UART_CR_SIREN                                      ((uint32_t)0x00000002)
#define UART_CR_SIRLP                                      ((uint32_t)0x00000004)
#define UART_CR_LBE                                        ((uint32_t)0x00000080)
#define UART_CR_TXE                                        ((uint32_t)0x00000100)
#define UART_CR_RXE                                        ((uint32_t)0x00000200)
#define UART_CR_DTR                                        ((uint32_t)0x00000400)
#define UART_CR_RTS                                        ((uint32_t)0x00000800)
#define UART_CR_OUT1                                       ((uint32_t)0x00001000)
#define UART_CR_OUT2                                       ((uint32_t)0x00002000)
#define UART_CR_RTSEN                                      ((uint32_t)0x00004000)
#define UART_CR_CTSEN                                      ((uint32_t)0x00008000)

//  reg IFLS
/* Bit field positions: */
#define UART_IFLS_TXIFLSEL_Pos                             0
#define UART_IFLS_RXIFLSEL_Pos                             3
/* Bit field masks: */
#define UART_IFLS_TXIFLSEL_Msk                             ((uint32_t)0x00000007)
#define UART_IFLS_RXIFLSEL_Msk                             ((uint32_t)0x00000038)

//  reg IMSC
/* Bit field positions: */
#define UART_IMSC_RIMIM_Pos                                0
#define UART_IMSC_CTSMIM_Pos                               1
#define UART_IMSC_DCDMIM_Pos                               2
#define UART_IMSC_DSRMIM_Pos                               3
#define UART_IMSC_RXIM_Pos                                 4
#define UART_IMSC_TXIM_Pos                                 5
#define UART_IMSC_RTIM_Pos                                 6
#define UART_IMSC_FEIM_Pos                                 7
#define UART_IMSC_PEIM_Pos                                 8
#define UART_IMSC_BEIM_Pos                                 9
#define UART_IMSC_OEIM_Pos                                 10
/* Bit field masks: */
#define UART_IMSC_RIMIM                                    ((uint32_t)0x00000001)
#define UART_IMSC_CTSMIM                                   ((uint32_t)0x00000002)
#define UART_IMSC_DCDMIM                                   ((uint32_t)0x00000004)
#define UART_IMSC_DSRMIM                                   ((uint32_t)0x00000008)
#define UART_IMSC_RXIM                                     ((uint32_t)0x00000010)
#define UART_IMSC_TXIM                                     ((uint32_t)0x00000020)
#define UART_IMSC_RTIM                                     ((uint32_t)0x00000040)
#define UART_IMSC_FEIM                                     ((uint32_t)0x00000080)
#define UART_IMSC_PEIM                                     ((uint32_t)0x00000100)
#define UART_IMSC_BEIM                                     ((uint32_t)0x00000200)
#define UART_IMSC_OEIM                                     ((uint32_t)0x00000400)

//  reg RIS
/* Bit field positions: */
#define UART_RIS_RIRMIS_Pos                                0
#define UART_RIS_CTSRMIS_Pos                               1
#define UART_RIS_DCDRMIS_Pos                               2
#define UART_RIS_DSRRMIS_Pos                               3
#define UART_RIS_RXRIS_Pos                                 4
#define UART_RIS_TXRIS_Pos                                 5
#define UART_RIS_RTRIS_Pos                                 6
#define UART_RIS_FERIS_Pos                                 7
#define UART_RIS_PERIS_Pos                                 8
#define UART_RIS_BERIS_Pos                                 9
#define UART_RIS_OERIS_Pos                                 10
/* Bit field masks: */
#define UART_RIS_RIRMIS                                    ((uint32_t)0x00000001)
#define UART_RIS_CTSRMIS                                   ((uint32_t)0x00000002)
#define UART_RIS_DCDRMIS                                   ((uint32_t)0x00000004)
#define UART_RIS_DSRRMIS                                   ((uint32_t)0x00000008)
#define UART_RIS_RXRIS                                     ((uint32_t)0x00000010)
#define UART_RIS_TXRIS                                     ((uint32_t)0x00000020)
#define UART_RIS_RTRIS                                     ((uint32_t)0x00000040)
#define UART_RIS_FERIS                                     ((uint32_t)0x00000080)
#define UART_RIS_PERIS                                     ((uint32_t)0x00000100)
#define UART_RIS_BERIS                                     ((uint32_t)0x00000200)
#define UART_RIS_OERIS                                     ((uint32_t)0x00000400)

//  reg MIS
/* Bit field positions: */
#define UART_MIS_RIMMIS_Pos                                0
#define UART_MIS_CTSMMIS_Pos                               1
#define UART_MIS_DCDMMIS_Pos                               2
#define UART_MIS_DSRMMIS_Pos                               3
#define UART_MIS_RXMIS_Pos                                 4
#define UART_MIS_TXMIS_Pos                                 5
#define UART_MIS_RTMIS_Pos                                 6
#define UART_MIS_FEMIS_Pos                                 7
#define UART_MIS_PEMIS_Pos                                 8
#define UART_MIS_BEMIS_Pos                                 9
#define UART_MIS_OEMIS_Pos                                 10
/* Bit field masks: */
#define UART_MIS_RIMMIS                                    ((uint32_t)0x00000001)
#define UART_MIS_CTSMMIS                                   ((uint32_t)0x00000002)
#define UART_MIS_DCDMMIS                                   ((uint32_t)0x00000004)
#define UART_MIS_DSRMMIS                                   ((uint32_t)0x00000008)
#define UART_MIS_RXMIS                                     ((uint32_t)0x00000010)
#define UART_MIS_TXMIS                                     ((uint32_t)0x00000020)
#define UART_MIS_RTMIS                                     ((uint32_t)0x00000040)
#define UART_MIS_FEMIS                                     ((uint32_t)0x00000080)
#define UART_MIS_PEMIS                                     ((uint32_t)0x00000100)
#define UART_MIS_BEMIS                                     ((uint32_t)0x00000200)
#define UART_MIS_OEMIS                                     ((uint32_t)0x00000400)

//  reg ICR
/* Bit field positions: */
#define UART_ICR_RIMIC_Pos                                 0
#define UART_ICR_CTSMIC_Pos                                1
#define UART_ICR_DCDMIC_Pos                                2
#define UART_ICR_DSRMIC_Pos                                3
#define UART_ICR_RXIC_Pos                                  4
#define UART_ICR_TXIC_Pos                                  5
#define UART_ICR_RTIC_Pos                                  6
#define UART_ICR_FEIC_Pos                                  7
#define UART_ICR_PEIC_Pos                                  8
#define UART_ICR_BEIC_Pos                                  9
#define UART_ICR_OEIC_Pos                                  10
/* Bit field masks: */
#define UART_ICR_RIMIC                                     ((uint32_t)0x00000001)
#define UART_ICR_CTSMIC                                    ((uint32_t)0x00000002)
#define UART_ICR_DCDMIC                                    ((uint32_t)0x00000004)
#define UART_ICR_DSRMIC                                    ((uint32_t)0x00000008)
#define UART_ICR_RXIC                                      ((uint32_t)0x00000010)
#define UART_ICR_TXIC                                      ((uint32_t)0x00000020)
#define UART_ICR_RTIC                                      ((uint32_t)0x00000040)
#define UART_ICR_FEIC                                      ((uint32_t)0x00000080)
#define UART_ICR_PEIC                                      ((uint32_t)0x00000100)
#define UART_ICR_BEIC                                      ((uint32_t)0x00000200)
#define UART_ICR_OEIC                                      ((uint32_t)0x00000400)

//  reg DMACR
/* Bit field positions: */
#define UART_DMACR_RXDMAE_Pos                              0
#define UART_DMACR_TXDMAE_Pos                              1
#define UART_DMACR_DMAONERR_Pos                            2
/* Bit field masks: */
#define UART_DMACR_RXDMAE                                  ((uint32_t)0x00000001)
#define UART_DMACR_TXDMAE                                  ((uint32_t)0x00000002)
#define UART_DMACR_DMAONERR                                ((uint32_t)0x00000004)




#ifdef __cplusplus
}
#endif

#endif  //  _MDRP_UART_DEFS_H
