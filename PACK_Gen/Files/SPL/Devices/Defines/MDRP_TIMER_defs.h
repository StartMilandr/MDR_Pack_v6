#ifndef _MDRP_TIMER_DEFS_H
#define _MDRP_TIMER_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

//=======================   TIMER  =======================
typedef struct {
	__IO uint32_t	CNT;                    /*!<Timer Counter Register */
	__IO uint32_t	PSG;                    /*!<Timer Clock Prescaler Register */
	__IO uint32_t	ARR;                    /*!<Timer Auto-Reload Register */
	__IO uint32_t	CNTRL;                  /*!<Timer Control Register */
	__IO uint32_t	CCR1;                   /*!<Timer Capture/Compare Register 1 */
	__IO uint32_t	CCR2;                   /*!<Timer Capture/Compare Register 2 */
	__IO uint32_t	CCR3;                   /*!<Timer Capture/Compare Register 3 */
	__IO uint32_t	CCR4;                   /*!<Timer Capture/Compare Register 4 */
	__IO uint32_t	CH1_CNTRL;              /*!<Timer Channel Control Register 1 */
	__IO uint32_t	CH2_CNTRL;              /*!<Timer Channel Control Register 2 */
	__IO uint32_t	CH3_CNTRL;              /*!<Timer Channel Control Register 3 */
	__IO uint32_t	CH4_CNTRL;              /*!<Timer Channel Control Register 4 */
	__IO uint32_t	CH1_CNTRL1;             /*!<Timer Channel Control1 Register 1 */
	__IO uint32_t	CH2_CNTRL1;             /*!<Timer Channel Control1 Register 2 */
	__IO uint32_t	CH3_CNTRL1;             /*!<Timer Channel Control1 Register 3 */
	__IO uint32_t	CH4_CNTRL1;             /*!<Timer Channel Control1 Register 4 */
	__IO uint32_t	CH1_DTG;                /*!<Timer Channel DTG Register 1 */
	__IO uint32_t	CH2_DTG;                /*!<Timer Channel DTG Register 2 */
	__IO uint32_t	CH3_DTG;                /*!<Timer Channel DTG Register 3 */
	__IO uint32_t	CH4_DTG;                /*!<Timer Channel DTG Register 4 */
	__IO uint32_t	BRKETR_CNTRL;           /*!<Timer BRK/ETR Control Register */
	__IO uint32_t	STATUS;                 /*!<Timer Status Register */
	__IO uint32_t	IE;                     /*!<Timer Interrupt Enable Register */
	__IO uint32_t	DMA_RE;                 /*!<Timer DMA Request Enable Register */
	__IO uint32_t	CH1_CNTRL2;             /*!<Timer Channel Control2 Register 1 */
	__IO uint32_t	CH2_CNTRL2;             /*!<Timer Channel Control2 Register 2 */
	__IO uint32_t	CH3_CNTRL2;             /*!<Timer Channel Control2 Register 3 */
	__IO uint32_t	CH4_CNTRL2;             /*!<Timer Channel Control2 Register 4 */
	__IO uint32_t	CCR11;                  /*!<Timer Capture/Compare1 Register 1 */
	__IO uint32_t	CCR21;                  /*!<Timer Capture/Compare1 Register 2 */
	__IO uint32_t	CCR31;                  /*!<Timer Capture/Compare1 Register 3 */
	__IO uint32_t	CCR41;                  /*!<Timer Capture/Compare1 Register 4 */
}MDR_TIMER_TypeDef;

/* Bit field positions: */
#define TIMER_CNT_CNT_Pos                                  0
/* Bit field masks: */
#define TIMER_CNT_CNT_Msk                                  ((uint32_t)0x0000FFFF)

/* Bit field positions: */
#define TIMER_PSG_PSG_Pos                                  0
/* Bit field masks: */
#define TIMER_PSG_PSG_Msk                                  ((uint32_t)0x0000FFFF)

/* Bit field positions: */
#define TIMER_ARR_ARR_Pos                                  0
/* Bit field masks: */
#define TIMER_ARR_ARR_Msk                                  ((uint32_t)0x0000FFFF)

/* Bit field positions: */
#define TIMER_CNTRL_CNT_EN_Pos                             0
#define TIMER_CNTRL_ARRB_EN_Pos                            1
#define TIMER_CNTRL_WR_CMPL_Pos                            2
#define TIMER_CNTRL_DIR_Pos                                3
#define TIMER_CNTRL_FDTS_Pos                               4
#define TIMER_CNTRL_CNT_MODE_Pos                           6
#define TIMER_CNTRL_EVENT_SEL_Pos                          8
/* Bit field masks: */
#define TIMER_CNTRL_CNT_EN                                 ((uint32_t)0x00000001)
#define TIMER_CNTRL_ARRB_EN                                ((uint32_t)0x00000002)
#define TIMER_CNTRL_WR_CMPL                                ((uint32_t)0x00000004)
#define TIMER_CNTRL_DIR                                    ((uint32_t)0x00000008)
#define TIMER_CNTRL_FDTS_Msk                               ((uint32_t)0x00000030)
#define TIMER_CNTRL_CNT_MODE_Msk                           ((uint32_t)0x000000C0)
#define TIMER_CNTRL_EVENT_SEL_Msk                          ((uint32_t)0x00000F00)

/* Bit field positions: */
#define TIMER_CCR_CCR_Pos                                  0
/* Bit field masks: */
#define TIMER_CCR_CCR_Msk                                  ((uint32_t)0x0000FFFF)

/* Bit field positions: */
#define TIMER_CH_CNTRL_CHFLTR_Pos                          0
#define TIMER_CH_CNTRL_CHSEL_Pos                           4
#define TIMER_CH_CNTRL_CHPSC_Pos                           6
#define TIMER_CH_CNTRL_OCCE_Pos                            8
#define TIMER_CH_CNTRL_OCCM_Pos                            9
#define TIMER_CH_CNTRL_BRKEN_Pos                           12
#define TIMER_CH_CNTRL_ETREN_Pos                           13
#define TIMER_CH_CNTRL_WR_CMPL_Pos                         14
#define TIMER_CH_CNTRL_CAP_NPWM_Pos                        15
/* Bit field masks: */
#define TIMER_CH_CNTRL_CHFLTR_Msk                          ((uint32_t)0x0000000F)
#define TIMER_CH_CNTRL_CHSEL_Msk                           ((uint32_t)0x00000030)
#define TIMER_CH_CNTRL_CHPSC_Msk                           ((uint32_t)0x000000C0)
#define TIMER_CH_CNTRL_OCCE                                ((uint32_t)0x00000100)
#define TIMER_CH_CNTRL_OCCM_Msk                            ((uint32_t)0x00000E00)
#define TIMER_CH_CNTRL_BRKEN                               ((uint32_t)0x00001000)
#define TIMER_CH_CNTRL_ETREN                               ((uint32_t)0x00002000)
#define TIMER_CH_CNTRL_WR_CMPL                             ((uint32_t)0x00004000)
#define TIMER_CH_CNTRL_CAP_NPWM                            ((uint32_t)0x00008000)

/* Bit field positions: */
#define TIMER_CH_CNTRL1_SELOE_Pos                          0
#define TIMER_CH_CNTRL1_SELO_Pos                           2
#define TIMER_CH_CNTRL1_INV_Pos                            4
#define TIMER_CH_CNTRL1_NSELOE_Pos                         8
#define TIMER_CH_CNTRL1_NSELO_Pos                          10
#define TIMER_CH_CNTRL1_NINV_Pos                           12
/* Bit field masks: */
#define TIMER_CH_CNTRL1_SELOE_Msk                          ((uint32_t)0x00000003)
#define TIMER_CH_CNTRL1_SELO_Msk                           ((uint32_t)0x0000000C)
#define TIMER_CH_CNTRL1_INV                                ((uint32_t)0x00000010)
#define TIMER_CH_CNTRL1_NSELOE_Msk                         ((uint32_t)0x00000300)
#define TIMER_CH_CNTRL1_NSELO_Msk                          ((uint32_t)0x00000C00)
#define TIMER_CH_CNTRL1_NINV                               ((uint32_t)0x00001000)

/* Bit field positions: */
#define TIMER_CH_DTG_DTGX_Pos                              0
#define TIMER_CH_DTG_EDTS_Pos                              4
#define TIMER_CH_DTG_DTG_Pos                               8
/* Bit field masks: */
#define TIMER_CH_DTG_DTGX_Msk                              ((uint32_t)0x0000000F)
#define TIMER_CH_DTG_EDTS                                  ((uint32_t)0x00000010)
#define TIMER_CH_DTG_DTG_Msk                               ((uint32_t)0x0000FF00)

/* Bit field positions: */
#define TIMER_BRKETR_CNTRL_BRK_INV_Pos                     0
#define TIMER_BRKETR_CNTRL_ETR_INV_Pos                     1
#define TIMER_BRKETR_CNTRL_ETR_PSC_Pos                     2
#define TIMER_BRKETR_CNTRL_ETR_FILTER_Pos                  4
/* Bit field positions: */
#define TIMER_BRKETR_CNTRL_BRK_INV_Pos                     0
#define TIMER_BRKETR_CNTRL_ETR_INV_Pos                     1
#define TIMER_BRKETR_CNTRL_ETR_PSC_Pos                     2
#define TIMER_BRKETR_CNTRL_ETR_FILTER_Pos                  4

/* Bit field masks: */
#define TIMER_BRKETR_CNTRL_BRK_INV                         ((uint32_t)0x00000001)
#define TIMER_BRKETR_CNTRL_ETR_INV                         ((uint32_t)0x00000002)
#define TIMER_BRKETR_CNTRL_ETR_PSC_Msk                     ((uint32_t)0x0000000C)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_Msk                  ((uint32_t)0x000000F0)
/* Bit field masks: */
#define TIMER_BRKETR_CNTRL_BRK_INV                         ((uint32_t)0x00000001)
#define TIMER_BRKETR_CNTRL_ETR_INV                         ((uint32_t)0x00000002)
#define TIMER_BRKETR_CNTRL_ETR_PSC_Msk                     ((uint32_t)0x0000000C)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_Msk                  ((uint32_t)0x000000F0)

/* Bit field positions: */
#define TIMER_STATUS_CNT_ZERO_EVENT_Pos                    0
#define TIMER_STATUS_CNT_ARR_EVENT_Pos                     1
#define TIMER_STATUS_ETR_RE_EVENT_Pos                      2
#define TIMER_STATUS_ETR_FE_EVENT_Pos                      3
#define TIMER_STATUS_BRK_EVENT_Pos                         4
#define TIMER_STATUS_CCR_CAP_EVENT_Pos                     5
#define TIMER_STATUS_CCR_REF_EVENT_Pos                     9
#define TIMER_STATUS_CCR1_CAP_EVENT_Pos                    13
/* Bit field masks: */
#define TIMER_STATUS_CNT_ZERO_EVENT                        ((uint32_t)0x00000001)
#define TIMER_STATUS_CNT_ARR_EVENT                         ((uint32_t)0x00000002)
#define TIMER_STATUS_ETR_RE_EVENT                          ((uint32_t)0x00000004)
#define TIMER_STATUS_ETR_FE_EVENT                          ((uint32_t)0x00000008)
#define TIMER_STATUS_BRK_EVENT                             ((uint32_t)0x00000010)
#define TIMER_STATUS_CCR_CAP_EVENT_Msk                     ((uint32_t)0x000001E0)
#define TIMER_STATUS_CCR_REF_EVENT_Msk                     ((uint32_t)0x00001E00)
#define TIMER_STATUS_CCR1_CAP_EVENT_Msk                    ((uint32_t)0x0001E000)

/* Bit field positions: */
#define TIMER_IE_CNT_ZERO_EVENT_IE_Pos                     0
#define TIMER_IE_CNT_ARR_EVENT_IE_Pos                      1
#define TIMER_IE_ETR_RE_EVENT_IE_Pos                       2
#define TIMER_IE_ETR_FE_EVENT_IE_Pos                       3
#define TIMER_IE_BRK_EVENT_IE_Pos                          4
#define TIMER_IE_CCR_CAP_EVENT_IE_Pos                      5
#define TIMER_IE_CCR_REF_EVENT_IE_Pos                      9
#define TIMER_IE_CCR1_CAP_EVENT_IE_Pos                     13
/* Bit field masks: */
#define TIMER_IE_CNT_ZERO_EVENT_IE                         ((uint32_t)0x00000001)
#define TIMER_IE_CNT_ARR_EVENT_IE                          ((uint32_t)0x00000002)
#define TIMER_IE_ETR_RE_EVENT_IE                           ((uint32_t)0x00000004)
#define TIMER_IE_ETR_FE_EVENT_IE                           ((uint32_t)0x00000008)
#define TIMER_IE_BRK_EVENT_IE                              ((uint32_t)0x00000010)
#define TIMER_IE_CCR_CAP_EVENT_IE_Msk                      ((uint32_t)0x000001E0)
#define TIMER_IE_CCR_REF_EVENT_IE_Msk                      ((uint32_t)0x00001E00)
#define TIMER_IE_CCR1_CAP_EVENT_IE_Msk                     ((uint32_t)0x0001E000)

/* Bit field positions: */
#define TIMER_DMA_RE_CNT_ZERO_EVENT_RE_Pos                 0
#define TIMER_DMA_RE_CNT_ARR_EVENT_RE_Pos                  1
#define TIMER_DMA_RE_ETR_RE_EVENT_RE_Pos                   2
#define TIMER_DMA_RE_ETR_FE_EVENT_RE_Pos                   3
#define TIMER_DMA_RE_BRK_EVENT_RE_Pos                      4
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_Pos                  5
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_Pos                  9
#define TIMER_DMA_RE_CCR1_CAP_EVENT_RE_Pos                 13
/* Bit field masks: */
#define TIMER_DMA_RE_CNT_ZERO_EVENT_RE                     ((uint32_t)0x00000001)
#define TIMER_DMA_RE_CNT_ARR_EVENT_RE                      ((uint32_t)0x00000002)
#define TIMER_DMA_RE_ETR_RE_EVENT_RE                       ((uint32_t)0x00000004)
#define TIMER_DMA_RE_ETR_FE_EVENT_RE                       ((uint32_t)0x00000008)
#define TIMER_DMA_RE_BRK_EVENT_RE                          ((uint32_t)0x00000010)
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_Msk                  ((uint32_t)0x000001E0)
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_Msk                  ((uint32_t)0x00001E00)
#define TIMER_DMA_RE_CCR1_CAP_EVENT_RE_Msk                 ((uint32_t)0x0001E000)

/* Bit field positions: */
#define TIMER_CH_CNTRL2_CHSEL1_Pos                         0
#define TIMER_CH_CNTRL2_CCR1_EN_Pos                        2
#define TIMER_CH_CNTRL2_CCRRLD_Pos                         3
/* Bit field masks: */
#define TIMER_CH_CNTRL2_CHSEL1_Msk                         ((uint32_t)0x00000003)
#define TIMER_CH_CNTRL2_CCR1_EN                            ((uint32_t)0x00000004)
#define TIMER_CH_CNTRL2_CCRRLD                             ((uint32_t)0x00000008)

/* Bit field positions: */
#define TIMER_CCR1_CCR_Pos                                 0
/* Bit field masks: */
#define TIMER_CCR1_CCR_Msk                                 ((uint32_t)0x0000FFFF)

/* Bit field positions: */
#define TIMER_CH_DTGX_Pos                       0
#define TIMER_CH_DTG_EDTS_Pos                   4
#define TIMER_CH_DTG_Pos                        8
/* Bit field masks: */
#define TIMER_CH_DTGX_Msk                       ((uint32_t)0x0000000F)
#define TIMER_CH_DTG_EDTS                       ((uint32_t)0x00000010)
#define TIMER_CH_DTG_Msk                        ((uint32_t)0x0000FF00)


#ifdef __cplusplus
}
#endif

#endif  //  _MDRP_TIMER_DEFS_H
