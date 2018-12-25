#ifndef _MDRP_POWER_DEFS_H
#define _MDRP_POWER_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

//=======================   POWER  =======================
typedef struct {
	__IO uint32_t	PVDCS;                  /*!<POWER Power Detector Control/Status Register */
}MDR_POWER_TypeDef;

//	reg PVDCS
/* Bit field positions: */
#define POWER_PVDCS_PVDEN_Pos                              0
#define POWER_PVDCS_PBLS_Pos                               1
#define POWER_PVDCS_PLS_Pos                                3
#define POWER_PVDCS_PVBD_Pos                               6
#define POWER_PVDCS_PVD_Pos                                7
#define POWER_PVDCS_IEPVBD_Pos                             8
#define POWER_PVDCS_IEPVD_Pos                              9
#define POWER_PVDCS_INVB_Pos                               10
#define POWER_PVDCS_INV_Pos                                11
#define POWER_PVDCS_PVDBEN_Pos                             12
/* Bit field masks: */
#define POWER_PVDCS_PVDEN                                  ((uint32_t)0x00000001)
#define POWER_PVDCS_PBLS_Msk                               ((uint32_t)0x00000006)
#define POWER_PVDCS_PLS_Msk                                ((uint32_t)0x00000038)
#define POWER_PVDCS_PVBD                                   ((uint32_t)0x00000040)
#define POWER_PVDCS_PVD                                    ((uint32_t)0x00000080)
#define POWER_PVDCS_IEPVBD                                 ((uint32_t)0x00000100)
#define POWER_PVDCS_IEPVD                                  ((uint32_t)0x00000200)
#define POWER_PVDCS_INVB                                   ((uint32_t)0x00000400)
#define POWER_PVDCS_INV                                    ((uint32_t)0x00000800)
#define POWER_PVDCS_PVDBEN                                 ((uint32_t)0x00001000)


#ifdef __cplusplus
}
#endif

#endif  //  _MDRP_POWER_DEFS_H
