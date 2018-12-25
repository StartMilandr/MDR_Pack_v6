#ifndef _MDRP_DMA_DEFS_H
#define _MDRP_DMA_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

//=======================   DMA  =======================

typedef struct {
	__IO uint32_t	STATUS;                 /*!<DMA Status Register */
	__IO uint32_t	CFG;                    /*!<DMA Configuration Register */
	__IO uint32_t	CTRL_BASE_PTR;          /*!< */
	__IO uint32_t	ALT_CTRL_BASE_PTR;      /*!< */
	__IO uint32_t	WAITONREQ_STATUS;       /*!< */
	__IO uint32_t	CHNL_SW_REQUEST;        /*!< */
	__IO uint32_t	CHNL_USEBURST_SET;      /*!< */
	__IO uint32_t	CHNL_USEBURST_CLR;      /*!< */
	__IO uint32_t	CHNL_REQ_MASK_SET;      /*!< */
	__IO uint32_t	CHNL_REQ_MASK_CLR;      /*!< */
	__IO uint32_t	CHNL_ENABLE_SET;        /*!< */
	__IO uint32_t	CHNL_ENABLE_CLR;        /*!< */
	__IO uint32_t	CHNL_PRI_ALT_SET;       /*!< */
	__IO uint32_t	CHNL_PRI_ALT_CLR;       /*!< */
	__IO uint32_t	CHNL_PRIORITY_SET;      /*!< */
	__IO uint32_t	CHNL_PRIORITY_CLR;      /*!< */
	__I  uint32_t	RESERVED0[3];
	__IO uint32_t	ERR_CLR;                /*!< */
}MDR_DMA_TypeDef;

//	reg STATUS
/* Bit field positions: */
#define DMA_STATUS_MASTER_ENABLE_Pos                       0
#define DMA_STATUS_STATE_Pos                               4
#define DMA_STATUS_CHNLS_MINUS1_Pos                        16
#define DMA_STATUS_TEST_STATUS_Pos                         28
/* Bit field masks: */
#define DMA_STATUS_MASTER_ENABLE                           ((uint32_t)0x00000001)
#define DMA_STATUS_STATE_Msk                               ((uint32_t)0x000000F0)
#define DMA_STATUS_CHNLS_MINUS1_Msk                        ((uint32_t)0x001F0000)
#define DMA_STATUS_TEST_STATUS_Msk                         ((uint32_t)0xF0000000)


//	reg CFG
/* Bit field positions: */
#define DMA_CFG_MASTER_ENABLE_Pos                          0
#define DMA_CFG_CHNL_PROT_CTRL_Pos                         5
/* Bit field masks: */
#define DMA_CFG_MASTER_ENABLE                              ((uint32_t)0x00000001)
#define DMA_CFG_CHNL_PROT_CTRL_Msk                         ((uint32_t)0x000000E0)

//	reg ERR_CLR
/* Bit field positions: */
#define DMA_ERR_CLR_ERR_CLR_Pos                            0
/* Bit field masks: */
#define DMA_ERR_CLR_ERR_CLR                                ((uint32_t)0x00000001)



#ifdef __cplusplus
}
#endif

#endif  //  _MDRP_DMA_DEFS_H
