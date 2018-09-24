#ifndef MDR_RST_CLOCK_H
#define MDR_RST_CLOCK_H

#include "MDR_Config.h"
#include <MDR_Types.h>
#include "MDR_Funcs.h"

#if defined (USE_MDR1986VE4) || defined (USE_MDR1986VK214) || defined (USE_MDR1986VK234)
  #define REG_PER_CLOCK_ENA_b       MDR_CLOCK->PER2_CLOCK_b
#else
  #define REG_PER_CLOCK_ENA_b       MDR_CLOCK->PER_CLOCK_b
#endif

//  Сброс блока тактирования RST_CLOCK в начальное состояние
bool RST_ResetBlock(uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim);

//=============   Включение генераторов ==============
                bool RST_LSE_GetReady(void);
                bool RST_LSE_Enable(uint32_t timeoutCycles, MDR_OnOff byPass);
__STATIC_INLINE void RST_LSE_Disable(void)  {MDR_BKP->REG_0F_b.LSE_ON = MDR_On;}


                bool RST_HSE_GetReady(void);
                bool RST_HSE_Enable(uint32_t timeoutCycles, MDR_OnOff byPass);
__STATIC_INLINE void RST_HSE_Disable(void)  {MDR_CLOCK->HS_CONTROL_b.HSE_ON = MDR_Off;}


                bool RST_PLL_GetReady(void);
                bool RST_PLL_Enable(MDR_MUL_x16 pllMul, uint32_t timeoutCycles);
__STATIC_INLINE void RST_PLL_Disable(void)  {MDR_CLOCK->PLL_CONTROL_b.PLL_CPU_ON = MDR_Off;}


__STATIC_INLINE void RST_LSI_Open(void)     {REG_PER_CLOCK_ENA_b.BKP_CLK_EN  = MDR_On;}
                bool RST_LSI_GetReady(void);
                bool RST_LSI_Enable(uint32_t timeoutCycles, MDR_BKP_LSI_TRIM freqTrim);
__STATIC_INLINE void RST_LSI_Disable(void)  {MDR_BKP->REG_0F_b.LSI_ON        = MDR_Off;}
__STATIC_INLINE void RST_LSI_Close(void)    {REG_PER_CLOCK_ENA_b.BKP_CLK_EN  = MDR_Off;}


__STATIC_INLINE void RST_HSI_Open(void)     {REG_PER_CLOCK_ENA_b.BKP_CLK_EN  = MDR_On;}
                bool RST_HSI_GetReady(void);
                bool RST_HSI_Enable(uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim);
__STATIC_INLINE void RST_HSI_Disable(void)  {MDR_BKP->REG_0F_b.HSI_ON        = MDR_Off;}
__STATIC_INLINE void RST_HSI_Close(void)    {REG_PER_CLOCK_ENA_b.BKP_CLK_EN  = MDR_Off;}


#ifdef MDR_EXIST_HSE2
                bool RST_HSE2_GetReady(void);
                bool RST_HSE2_Enable(uint32_t timeoutCycles, MDR_OnOff byPass);
__STATIC_INLINE void RST_HSE2_Disable(void) {MDR_CLOCK->HS_CONTROL_b.HSE2_ON = MDR_Off;}
#endif


//=============   Выбор тактирования для CPU ==============
// CPU должен переключаться на уже сформированную частоту!
// Все предварительные настройки и переключения должны быть сделаны заранее.
// При настройках необходимо следить за сохранностью текущей частоты ядра, 
// чтобы не выключить настоту на которой происходит текущее исполнение инструкций.
//



//  Тактирование ядра от внутреннего генератора LSI, ~40КГц
bool CPU_SetClock_LSI(uint32_t timeoutCycles, MDR_BKP_LSI_TRIM freqTrim);

//  Тактирование ядра от внешнего генератора LSE, частота задается в MDR_Config LSE_FREQ_HZ
bool CPU_SetClock_LSE(MDR_OnOff byPass, uint32_t timeoutCycles);

//  Тактирование ядра от внутреннего генератора HSI, ~8МГц
bool CPU_SetClock_HSI(uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim);
bool CPU_SetClock_HSI_PLL(MDR_MUL_x16 pllMul, uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim);
bool CPU_SetClock_HSI_div2_PLL(MDR_MUL_x16 pllMul, uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim);

//  Тактирование ядра от внешнего генератора HSE, частота задается в MDR_Config HSE_FREQ_HZ
bool CPU_SetClock_HSE(uint32_t timeoutCycles);
bool CPU_SetClock_HSE_PLL(MDR_MUL_x16 pllMul, MDR_OnOff byPass, uint32_t timeoutCycles);
bool CPU_SetClock_HSE_div2_PLL(MDR_MUL_x16 pllMul, MDR_OnOff byPass, uint32_t timeoutCycles);


//===============  Функции с параметрами по умолчанию из MDR_Config.h,  ===============
//===============  который юстируется пользователем под проект и плату  ===============

#define RST_ResetBlock_def()                          RST_ResetBlock(HSI_TIMEOUT, HSI_FREQ_TRIM)

#define CPU_SetClock_LSI_def()                        CPU_SetClock_LSI(LSI_TIMEOUT, LSI_FREQ_TRIM)

#define CPU_SetClock_LSE_def(bypass)                  CPU_SetClock_LSE((bypass), LSE_TIMEOUT);

#define CPU_SetClock_HSI_def()                        CPU_SetClock_HSI(HSI_TIMEOUT, HSI_FREQ_TRIM)
#define CPU_SetClock_HSI_PLL_def(mul)                 CPU_SetClock_HSI_PLL     ((mul), LSI_TIMEOUT, HSI_FREQ_TRIM)
#define CPU_SetClock_HSI_div2_PLL_def(mul)            CPU_SetClock_HSI_div2_PLL((mul), LSI_TIMEOUT, HSI_FREQ_TRIM)

#define CPU_SetClock_HSE_def()                        CPU_SetClock_HSE         (HSE_TIMEOUT)
#define CPU_SetClock_HSE_PLL_def(mul, bypass)         CPU_SetClock_HSE_PLL     ((mul), (bypass), HSE_TIMEOUT)
#define CPU_SetClock_HSE_div2_PLL_def(mul, bypass)    CPU_SetClock_HSE_div2_PLL((mul), (bypass), HSE_TIMEOUT)

#endif //MDR_RST_CLOCK_H
