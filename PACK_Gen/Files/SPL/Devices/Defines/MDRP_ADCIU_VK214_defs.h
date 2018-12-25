#ifndef _MDRP_ADCIU_VK214_DEFS_H
#define _MDRP_ADCIU_VK214_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

//=======================   ADCIU  =======================
typedef struct {
	__IO uint32_t	CTRL1;
  __IO uint32_t	CTRL2;
  __IO uint32_t	CTRL3;
  //  Channel F0
  __IO uint32_t	F0CTR;
  __IO uint32_t	F0WC;
  __IO uint32_t	F0WATTP;
  __IO uint32_t	F0WATTN;
  __IO uint32_t	F0VC;
  __IO uint32_t	F0VARP;
  __IO uint32_t	F0VARN;
  __IO uint32_t	F0AC;
  __IO uint32_t	F0VR;
  __IO uint32_t	F0MD0;
  __IO uint32_t	F0MD1;  
  __IO uint32_t	F0VPEAK;
  __IO uint32_t	F0IPEAK;
  __IO uint32_t	F0V0DAT;
  __IO uint32_t	F0I0DAT;
  __IO uint32_t	F0I3DAT;
  __IO uint32_t	F0VRMS;
  __IO uint32_t	F0VRMS2;
  __IO uint32_t	F0IRMS;
  __IO uint32_t	F0IRMS2;
  __IO uint32_t	F0STAT;
  __IO uint32_t	F0MASK;
  __IO uint32_t reserved1[43]; 
  //  Calibrate
  __IO uint32_t	CCAL1;
  __IO uint32_t reserved2[2]; 
  __IO uint32_t	CCAL4;
} MDR_ADCIU_TypeDef;





#ifdef __cplusplus
}
#endif

#endif  //  _MDRP_ADCIU_VK214_DEFS_H
