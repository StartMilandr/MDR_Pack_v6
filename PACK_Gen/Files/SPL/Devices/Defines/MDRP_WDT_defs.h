#ifndef _MDRP_WDT_DEFS_H
#define _MDRP_WDT_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

//=======================   IWDT  =======================
typedef struct {
	__IO uint32_t	KR;                     /*!<IWDG Key Register */
	__IO uint32_t	PR;                     /*!<IWDG Clock Prescaler Register */
	__IO uint32_t	RLR;                    /*!<IWDG Reload Register */
	__IO uint32_t	SR;                     /*!<IWDG Status Register */
}MDR_IWDG_TypeDef;

//	reg KR
/* Bit field positions: */
#define IWDG_KR_KEY_Pos                                    0
/* Bit field masks: */
#define IWDG_KR_KEY_Msk                                    ((uint32_t)0x0000FFFF)

//	reg PRSR
/* Bit field positions: */
#define IWDG_PR_PR_Pos                                     0
/* Bit field masks: */
#define IWDG_PR_PR_Msk                                     ((uint32_t)0x00000007)

//	reg RLR
/* Bit field positions: */
#define IWDG_RLR_RLR_Pos                                   0
/* Bit field masks: */
#define IWDG_RLR_RLR_Msk                                   ((uint32_t)0x00000FFF)

//	reg SR
/* Bit field positions: */
#define IWDG_SR_PVU_Pos                                    0
#define IWDG_SR_RVU_Pos                                    1
/* Bit field masks: */
#define IWDG_SR_PVU                                        ((uint32_t)0x00000001)
#define IWDG_SR_RVU                                        ((uint32_t)0x00000002)


//=======================   WWDT  =======================
typedef struct {
	__IO uint32_t	CR;                     /*!<WWDG Command Register */
	__IO uint32_t	CFR;                    /*!<WWDG Configuration Register */
	__IO uint32_t	SR;                     /*!<WWDG Status Register */
}MDR_WWDG_TypeDef;

//	reg CR
/* Bit field positions: */
#define WWDG_CR_T_Pos                                      0
#define WWDG_CR_WDGA_Pos                                   7
/* Bit field masks: */
#define WWDG_CR_T_Msk                                      ((uint32_t)0x0000007F)
#define WWDG_CR_WDGA  

//	reg CFR
/* Bit field positions: */
#define WWDG_CFR_W_Pos                                     0
#define WWDG_CFR_WGTB_Pos                                  7
#define WWDG_CFR_EWI_Pos                                   9
/* Bit field masks: */
#define WWDG_CFR_W_Msk                                     ((uint32_t)0x0000007F)
#define WWDG_CFR_WGTB_Msk                                  ((uint32_t)0x00000180)
#define WWDG_CFR_EWI                                       ((uint32_t)0x00000200)

//	reg SR
/* Bit field positions: */
#define WWDG_SR_EWIF_Pos                                   0
/* Bit field masks: */
#define WWDG_SR_EWIF                                       ((uint32_t)0x00000001)


#ifdef __cplusplus
}
#endif

#endif  //  _MDRP_WDT_DEFS_H
