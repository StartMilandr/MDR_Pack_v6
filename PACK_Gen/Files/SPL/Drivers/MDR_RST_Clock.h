#ifndef MDR_RST_CLOCK_H
#define MDR_RST_CLOCK_H

#include "MDR_Config.h"
#include <MDR_Types.h>
#include <MDR_Funcs.h>


//==========   Вспомогательные функции стабилизации потребления и доступа к EEPROM ==============
// Стабилизация потребления в зависимости от частоты
#define MDR_RST_BKP_LowRI     MDR_BKP_LOW_RI

//  Такты паузы ядра для доступа к данным EEPROM. 
//  EEPROM не работает быстрее чем 25МГц. Считывается за раз четыре 32-разрядных слова.
#define MDR_RST_EEPROM_Delay  MDR_EEPROM_DELAY

//  Функции пересчета частоты в параметры SelectRI, LOW  и DelayEEPROM
MDR_RST_EEPROM_Delay MDR_FreqCPU_ToDelayEEPROM(uint32_t CPU_FregHz);
MDR_RST_BKP_LowRI    MDR_FreqCPU_ToLowRI      (uint32_t CPU_FregHz);

//  Применение параметров в микроконтроллер
void MDR_RST_SetLowRI(MDR_RST_BKP_LowRI lowRI);
void MDR_RST_SetDelayEEPROM(MDR_RST_EEPROM_Delay delayEEPROM);


//  Получение частоты CPU
//  Желательно обновить после смены частоты, тогда впоследствии можно вызывать без флага обновления
uint32_t MDR_CPU_GetFreqHz(bool doUpdate);

//  Сброс блока тактирования RST_CLOCK в начальное состояние
bool MDR_RST_ResetBlock(uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim);

//=============   Включение генераторов ==============
                bool MDR_RST_LSE_GetReady(void);
                bool MDR_RST_LSE_Enable(uint32_t timeoutCycles, MDR_OnOff byPass);
__STATIC_INLINE void MDR_RST_LSE_Disable(void)  {MDR_BKP->REG_0F_b.LSE_ON = MDR_On;}


                bool MDR_RST_HSE_GetReady(void);
                bool MDR_RST_HSE_Enable(uint32_t timeoutCycles, MDR_OnOff byPass);
__STATIC_INLINE void MDR_RST_HSE_Disable(void)  {MDR_CLOCK->HS_CONTROL_b.HSE_ON = MDR_Off;}


                bool MDR_RST_PLL_GetReady(void);
                bool MDR_RST_PLL_Enable(MDR_MUL_x16 pllMul, uint32_t timeoutCycles);
__STATIC_INLINE void MDR_RST_PLL_Disable(void)  {MDR_CLOCK->PLL_CONTROL_b.PLL_CPU_ON = MDR_Off;}


__STATIC_INLINE void MDR_RST_LSI_Open(void)     {MDR_CLOCK->MDR_CLK_EN_REG_BKP_b.BKP_CLK_EN  = MDR_On;}
                bool MDR_RST_LSI_GetReady(void);
                bool MDR_RST_LSI_Enable(uint32_t timeoutCycles, MDR_BKP_LSI_TRIM freqTrim);
__STATIC_INLINE void MDR_RST_LSI_Disable(void)  {MDR_BKP->REG_0F_b.LSI_ON        = MDR_Off;}
__STATIC_INLINE void MDR_RST_LSI_Close(void)    {MDR_CLOCK->MDR_CLK_EN_REG_BKP_b.BKP_CLK_EN  = MDR_Off;}


__STATIC_INLINE void MDR_RST_HSI_Open(void)     {MDR_CLOCK->MDR_CLK_EN_REG_BKP_b.BKP_CLK_EN = MDR_On;}
                bool MDR_RST_HSI_GetReady(void);
                bool MDR_RST_HSI_Enable(uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim);
__STATIC_INLINE void MDR_RST_HSI_Disable(void)  {MDR_BKP->REG_0F_b.HSI_ON        = MDR_Off;}
__STATIC_INLINE void MDR_RST_HSI_Close(void)    {MDR_CLOCK->MDR_CLK_EN_REG_BKP_b.BKP_CLK_EN  = MDR_Off;}


#ifdef MDR_EXIST_HSE2
                bool MDR_RST_HSE2_GetReady(void);
                bool MDR_RST_HSE2_Enable(uint32_t timeoutCycles, MDR_OnOff byPass);
__STATIC_INLINE void MDR_RST_HSE2_Disable(void) {MDR_CLOCK->HS_CONTROL_b.HSE2_ON = MDR_Off;}
#endif


//=============   Выбор тактирования для CPU ==============
// CPU должен переключаться на уже сформированную частоту!
// Все предварительные настройки и переключения должны быть сделаны заранее.
// При настройках необходимо следить за сохранностью текущей частоты ядра, 
// чтобы не выключить настоту на которой происходит текущее исполнение инструкций.
//



//  Тактирование ядра от внутреннего генератора LSI, ~40КГц
bool MDR_CPU_SetClock_LSI(uint32_t timeoutCycles, MDR_BKP_LSI_TRIM freqTrim);

//  Тактирование ядра от внешнего генератора LSE, частота задается в MDR_Config LSE_FREQ_HZ
bool MDR_CPU_SetClock_LSE(MDR_OnOff byPass, uint32_t timeoutCycles);

//  Тактирование ядра от внутреннего генератора HSI, ~8МГц
bool MDR_CPU_SetClock_HSI     (uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim);
bool MDR_CPU_SetClock_HSI_C1  (MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim);
bool MDR_CPU_SetClock_HSI_div2(MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim);

bool MDR_CPU_SetClock_HSI_PLL     (MDR_MUL_x16 pllMul, MDR_RST_BKP_LowRI lowRI, MDR_RST_EEPROM_Delay delayEEPROM, MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim);
bool MDR_CPU_SetClock_HSI_div2_PLL(MDR_MUL_x16 pllMul, MDR_RST_BKP_LowRI lowRI, MDR_RST_EEPROM_Delay delayEEPROM, MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim);

//  Тактирование ядра от внешнего генератора HSE, частота задается в MDR_Config HSE_FREQ_HZ
bool MDR_CPU_SetClock_HSE     (MDR_OnOff byPass, MDR_RST_BKP_LowRI lowRI, MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles);
bool MDR_CPU_SetClock_HSE_div2(MDR_OnOff byPass, MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles);

bool MDR_CPU_SetClock_HSE_PLL     (MDR_OnOff byPass, MDR_MUL_x16 pllMul, MDR_RST_BKP_LowRI lowRI, MDR_RST_EEPROM_Delay delayEEPROM, MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles);
bool MDR_CPU_SetClock_HSE_div2_PLL(MDR_OnOff byPass, MDR_MUL_x16 pllMul, MDR_RST_BKP_LowRI lowRI, MDR_RST_EEPROM_Delay delayEEPROM, MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles);


//===============  Функции с параметрами по умолчанию из MDR_Config.h,  ===============
//===============  Этот файл модифицируется пользователем под проект и плату  =========

#define MDR_RST_ResetBlock_def()                          MDR_RST_ResetBlock(HSI_TIMEOUT, HSI_FREQ_TRIM)

#define MDR_CPU_SetClock_LSI_def()                        MDR_CPU_SetClock_LSI(LSI_TIMEOUT, LSI_FREQ_TRIM)

#define MDR_CPU_SetClock_LSE_def(bypass)                  MDR_CPU_SetClock_LSE((bypass), LSE_TIMEOUT)

#define MDR_CPU_SetClock_HSI_def()                        MDR_CPU_SetClock_HSI(HSI_TIMEOUT, HSI_FREQ_TRIM)
#define MDR_CPU_SetClock_HSI_C1_def()                     MDR_CPU_SetClock_HSI_C1(MDR_CLK_div1, HSI_TIMEOUT, HSI_FREQ_TRIM)
#define MDR_CPU_SetClock_HSI_div2_def()                   MDR_CPU_SetClock_HSI_div2(MDR_CLK_div1, HSI_TIMEOUT, HSI_FREQ_TRIM)

#define MDR_CPU_SetClock_HSE_def(bypass, lowRI)           MDR_CPU_SetClock_HSE((bypass), (lowRI), MDR_CLK_div1, HSE_TIMEOUT)
#define MDR_CPU_SetClock_HSE_div2_def(bypass)             MDR_CPU_SetClock_HSE_div2((bypass), MDR_CLK_div1, HSE_TIMEOUT)


#define MDR_CPU_SetClock_HSI_PLL_def(mul, lowRI, dEE)                  MDR_CPU_SetClock_HSI_PLL     ((mul), (lowRI), (dEE), MDR_CLK_div1, HSI_TIMEOUT, HSI_FREQ_TRIM)
#define MDR_CPU_SetClock_HSI_div2_PLL_def(mul, lowRI, dEE)             MDR_CPU_SetClock_HSI_div2_PLL((mul), (lowRI), (dEE), MDR_CLK_div1, HSI_TIMEOUT, HSI_FREQ_TRIM)

#define MDR_CPU_SetClock_HSE_PLL_def(bypass, mul, lowRI, dEE)          MDR_CPU_SetClock_HSE_PLL     ((bypass), (mul), (lowRI), (dEE), MDR_CLK_div1, HSE_TIMEOUT)
#define MDR_CPU_SetClock_HSE_div2_PLL_def(bypass, mul, lowRI, dEE)     MDR_CPU_SetClock_HSE_div2_PLL((bypass), (mul), (lowRI), (dEE), MDR_CLK_div1, HSE_TIMEOUT)


//===============  Функции включения тактирования и подачи тактирования для блоков с BRG  ===============
typedef struct {
  // Clock Enable reg: PER_CLock
  volatile uint32_t* ClockEna_Addr;
  uint32_t           ClockEna_Mask;
  //  Clock On and BRG regs: Uart_Clock, SSP_Clock, Timer_Clock
  volatile uint32_t* ClockGate_Addr;
  uint32_t           ClockGate_ClockOn_Msk;
  uint32_t           ClockGate_BRG_Pos;
} MDR_PerClock_Cfg;

//  Включение тактирования на блок для доступа к регистрам
__STATIC_INLINE void MDR_PerClock_Enable(const MDR_PerClock_Cfg *pCfgClock)  {REG32(pCfgClock->ClockEna_Addr) |= pCfgClock->ClockEna_Mask;};
__STATIC_INLINE void MDR_PerClock_Disable(const MDR_PerClock_Cfg *pCfgClock) {REG32(pCfgClock->ClockEna_Addr) &= ~pCfgClock->ClockEna_Mask;};

//  Подача рабочей частоты Uart_Clock, SSP_Clock, Timer_Clock
                void MDR_PerClock_GateOpen (const MDR_PerClock_Cfg *pCfgClock, MDR_BRG_DIV_128 clockBRG);
__STATIC_INLINE void MDR_PerClock_GateClose(const MDR_PerClock_Cfg *pCfgClock) {REG32(pCfgClock->ClockGate_Addr) &= ~pCfgClock->ClockGate_ClockOn_Msk;};


#endif //MDR_RST_CLOCK_H
