#ifndef _MDRP_CRC_DEFS_H
#define _MDRP_CRC_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

//=======================   CRC  =======================
typedef struct {
	__IO uint32_t	CTRL;                   /*!< */
	__IO uint32_t	STAT;                   /*!< */
	__IO uint32_t	DATAI;                  /*!< */
	__IO uint32_t	VAL;                    /*!< */
	__IO uint32_t	POL;                    /*!< */
}MDR_CRC_TypeDef;

/* Bit field positions: */
#define CRC_CTRL_CRCEN_Pos                                 0
#define CRC_CTRL_DATAINV_Pos                               1
#define CRC_CTRL_DMAEN_Pos                                 2
#define CRC_CTRL_DLSIZE_Pos                                3
#define CRC_CTRL_DCSIZE_Pos                                5
/* Bit field masks: */
#define CRC_CTRL_CRCEN                                     ((uint32_t)0x00000001)
#define CRC_CTRL_DATAINV                                   ((uint32_t)0x00000002)
#define CRC_CTRL_DMAEN                                     ((uint32_t)0x00000004)
#define CRC_CTRL_DLSIZE_Msk                                ((uint32_t)0x00000018)
#define CRC_CTRL_DCSIZE_Msk                                ((uint32_t)0x00000060)

/* Bit field positions: */
#define CRC_STAT_CONVCOMP_Pos                              0
#define CRC_STAT_FIFOFULL_Pos                              1
#define CRC_STAT_FIFOEMPTY_Pos                             2
#define CRC_STAT_FIFOOVER_Pos                              3
/* Bit field masks: */
#define CRC_STAT_CONVCOMP                                  ((uint32_t)0x00000001)
#define CRC_STAT_FIFOFULL                                  ((uint32_t)0x00000002)
#define CRC_STAT_FIFOEMPTY                                 ((uint32_t)0x00000004)
#define CRC_STAT_FIFOOVER                                  ((uint32_t)0x00000008)

/* Bit field positions: */
#define CRC_DATAI_DATA_IN_Pos                              0
/* Bit field masks: */
#define CRC_DATAI_DATA_IN_Msk                              ((uint32_t)0xFFFFFFFF)

/* Bit field positions: */
#define CRC_VAL_CRCOUT_Pos                                 0
/* Bit field masks: */
#define CRC_VAL_CRCOUT_Msk                                 ((uint32_t)0x0000FFFF)

/* Bit field positions: */
#define CRC_POL_CRC_POL_Pos                                0
/* Bit field masks: */
#define CRC_POL_CRC_POL_Msk                                ((uint32_t)0x0001FFFF)



#ifdef __cplusplus
}
#endif

#endif  //  _MDRP_CRC_DEFS_H
