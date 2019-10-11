#ifndef MDR_OTP_VE8x_H
#define MDR_OTP_VE8x_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <stdint.h>

//  Рассчет ЕСС, Реализация от Vasili с форума - http://forum.milandr.ru/viewtopic.php?p=20531#p20531
uint8_t MDR_GetECC(uint32_t data,  uint32_t adr);

//  Разрешение работы блока
__STATIC_INLINE void MDR_OTP_Enable(void)  { MDR_OTP->KEY = MDR_KEY_UNLOCK; }
__STATIC_INLINE void MDR_OTP_Disable(void) { MDR_OTP->KEY = 0; }


#ifdef USE_MDR1986VE81
  //  Реализация от Vasili с форума - http://forum.milandr.ru/viewtopic.php?p=20531#p20531
  void MDR_OTPSRAM_ProgWord(uint32_t addr, uint32_t value);
  
#elif defined (USE_MDR1986VE8)

  #include <MDR_BKP_RTC_VE8x.h>

  #define MDR_OTP_DELAY_US_HV_PE   10000
  #define MDR_OTP_DELAY_US_A_D       300
  #define MDR_OTP_DELAY_US_PROG     3000


  typedef struct {
  //                                              8MHz        24MHz
  //                                             125ns      ~41,6ns - Период
    uint32_t delay_HV_PE;  //10000 us            80000      240000
    uint32_t delay_A_D;    //  300 us             2400        7200    
    uint32_t delay_Prog;   // 3000 us            24000       75000
    
  //  НЕ ИСПОЛЬЗУЮТСЯ:
  //uint32_t delay_PE_D;   //  300 us             2400        7200   - т.к. (delay_PE_D == delay_A_D)
  //uint32_t delay_Bits;   //    5 us               40         120   - 5-кратное чтение бита перекрывает задержку
  //uint32_t delay_D_A;    //    5 us               40         120   - 5-кратное чтение бита перекрывает задержку
  //uint32_t delay_A_SE;   //    0,005 us (ns)       -           -   - меньше периода частоты
  //uint32_t delay_SE_A;   //    0 us                -           -
  //uint32_t delay_SE;     //    0,010 us (ns)       -           -
  } MDR_OTP_ProgDelays;

  MDR_OTP_ProgDelays MDR_OTP_GetProgDelays(uint32_t freqCPU_Hz);

  //  Подготовка к программированию и финализация после его окончания - переключение DUcc и Tuning
  void MDR_OTP_ProgBegin(const MDR_OTP_ProgDelays *progDelays);
  void MDR_OTP_ProgEnd(void);

  __STATIC_INLINE void MDR_OTP_ProgBegin_ByClockCPU_Hz(uint32_t freqCPU_Hz) 
  { 
    MDR_OTP_ProgDelays delays = MDR_OTP_GetProgDelays(freqCPU_Hz);
    MDR_OTP_ProgBegin(&delays); 
  }

  //  Функции программирования, с рассчетом ЕСС внутри или от пользователя
  //    true  - алгоритм отработал полностью
  //    false - брак
  bool MDR_OTP_ProgWordAndEccEx(uint32_t addr, uint32_t data, uint8_t ecc, uint32_t cycleCount);
  bool MDR_OTP_ProgWordEx(uint32_t addr, uint32_t data, uint32_t cycleCount);

  //  Программирование слова - 1 цикл
  __STATIC_INLINE void MDR_OTP_ProgWord(uint32_t addr, uint32_t value)                    { MDR_OTP_ProgWordEx(addr, value, 1); }
  __STATIC_INLINE void MDR_OTP_ProgWordAndEcc(uint32_t addr, uint32_t value, uint8_t ecc) { MDR_OTP_ProgWordAndEccEx(addr, value, ecc, 1); }
  
  //  Допрограммирование слова - 40 циклов
  #define  MDR_OTP_REPROG_CNT   40
  __STATIC_INLINE void MDR_OTP_RepProgWord(uint32_t addr, uint32_t value)                    { MDR_OTP_ProgWordEx(addr, value, MDR_OTP_REPROG_CNT); }
  __STATIC_INLINE void MDR_OTP_RepProgWordAndEcc(uint32_t addr, uint32_t value, uint8_t ecc) { MDR_OTP_ProgWordAndEccEx(addr, value, ecc, MDR_OTP_REPROG_CNT); }  

  //  Регистровое чтение слова
  uint32_t MDR_OTP_ReadWord(uint32_t addr);

#endif

__STATIC_INLINE void MDR_OTP_ErrClearCounter(void) { MDR_OTP->ECCCS = MDR_OTP_ECCCS_FIX_DECC_Msk | MDR_OTP_ECCCS_FIX_SECC_Msk | MDR_OTP_ECCCS_CLR_SECNT_Msk | MDR_OTP_ECCCS_CLR_DECNT_Msk; }

__STATIC_INLINE void MDR_OTP_ErrFixEna(void) { MDR_OTP->ECCCS |=   MDR_OTP_ECCCS_FIX_DECC_Msk | MDR_OTP_ECCCS_FIX_SECC_Msk; }
__STATIC_INLINE void MDR_OTP_ErrFixDis(void) { MDR_OTP->ECCCS &= ~(MDR_OTP_ECCCS_FIX_DECC_Msk | MDR_OTP_ECCCS_FIX_SECC_Msk); }

#endif // MDR_OTP_VE8x_H

