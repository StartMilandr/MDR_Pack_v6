#ifndef _MDR_ADCIU_VK234_DEFS_H
#define _MDR_ADCIU_VK234_DEFS_H

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
  //  Channel F1
  __IO uint32_t	F1CTR;
  __IO uint32_t	F1WC;
  __IO uint32_t	F1WATTP;
  __IO uint32_t	F1WATTN;
  __IO uint32_t	F1VC;
  __IO uint32_t	F1VARP;
  __IO uint32_t	F1VARN;
  __IO uint32_t	F1AC;
  __IO uint32_t	F1VR;
  __IO uint32_t	F1MD0;
  __IO uint32_t	F1MD1;
  __IO uint32_t	F1MD2;
  __IO uint32_t	F1VPEAK;
  __IO uint32_t	F1IPEAK;
  __IO uint32_t	F1VDAT;
  __IO uint32_t	F1IDAT;
  __IO uint32_t	F1VRMS;
  __IO uint32_t	F1VRMS2;
  __IO uint32_t	F1IRMS;
  __IO uint32_t	F1IRMS2;
  __IO uint32_t	F1STAT;
  __IO uint32_t	F1MASK;  
  //  Channel F2
  __IO uint32_t	F2CTR;
  __IO uint32_t	F2WC;
  __IO uint32_t	F2WATTP;
  __IO uint32_t	F2WATTN;
  __IO uint32_t	F2VC;
  __IO uint32_t	F2VARP;
  __IO uint32_t	F2VARN;
  __IO uint32_t	F2AC;
  __IO uint32_t	F2VR;
  __IO uint32_t	F2MD0;
  __IO uint32_t	F2MD1;
  __IO uint32_t	F2MD2;
  __IO uint32_t	F2VPEAK;
  __IO uint32_t	F2IPEAK;
  __IO uint32_t	F2VDAT;
  __IO uint32_t	F2IDAT;
  __IO uint32_t	F2VRMS;
  __IO uint32_t	F2VRMS2;
  __IO uint32_t	F2IRMS;
  __IO uint32_t	F2IRMS2;
  __IO uint32_t	F2STAT;
  __IO uint32_t	F2MASK;  
  //  Calibrate
  __IO uint32_t	CCAL1;
  __IO uint32_t	CCAL2;
  __IO uint32_t	CCAL3;
  __IO uint32_t	CCAL4;
} MDR_ADCIU_TypeDef;





#ifdef __cplusplus
}
#endif

#endif  //  _MDR_ADCIU_VK234_DEFS_H
