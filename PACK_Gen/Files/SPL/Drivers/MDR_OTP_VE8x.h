#ifndef MDR_OTP_VE8x_H
#define MDR_OTP_VE8x_H

#include <MDR_Config.h>
#include <stdint.h>

#ifdef USE_MDR1986VE81
  //  Реализация от Vasili с форума - http://forum.milandr.ru/viewtopic.php?p=20531#p20531
  void MDR_OTPSRAM_ProgWordWord(uint32_t addr, uint32_t value);
  
#elif defined (USE_MDR1986VE81)

  //void MDR_OTP_ProgWordWord(uint32_t addr, uint32_t value);

#endif

__STATIC_INLINE void MDR_OTP_Enable(void) { MDR_OTP->KEY = MDR_KEY_UNLOCK; }
__STATIC_INLINE void MDR_OTP_Disable(void) { MDR_OTP->KEY = 0; }

#endif // MDR_OTP_VE8x_H

