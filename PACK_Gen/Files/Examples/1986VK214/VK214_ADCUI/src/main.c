#include <MDR_RST_Clock.h>
#include <MDRB_LCD.h>
#include <MDRB_Buttons.h>
#include <MDR_SysTimer.h>
#include <MDR_PER_Clock.h>

#include "test_Defs.h"

//  Непрерывное обновление данных, без нажатия на кнопку
#define USE_SYS_TIMER_UPDATE    1

#define SHOW_PERIOD_MS    500
#define BTN_DEBOUNCE_MS   20

extern TestInterface TI_ADTUI_InitReg;
extern TestInterface TI_ADTUI_InitCfg;
extern TestInterface TI_ADTUI_InitCfgReg;

static  TestInterface *testStack[] = {&TI_ADTUI_InitReg, &TI_ADTUI_InitCfg, &TI_ADTUI_InitCfgReg};
static  uint32_t activeTest;
static  uint32_t testCount = sizeof(testStack)/sizeof(testStack[0]);

void SysTick_Handler(void);
void SetNextTest(void);

int main(void)
{
  uint32_t freqCPU_Hz;
   
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);  
  
  //  Инициализация LCD дисплея и кнопок
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_LCD_Init(freqCPU_Hz);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  
  // Clock from HSE
  MDR_ADCUI_SetClock_CPU_C1(MDR_Div256P_div16);
   
  //  Активный тест
  activeTest = 0;  
  testStack[activeTest]->funcInit();
  
#if USE_SYS_TIMER_UPDATE  
  MDR_SysTimerStart_ms(SHOW_PERIOD_MS, freqCPU_Hz);
#endif   
  
  while (1)
  {
    //  Изменение режима теста
    if (MDRB_BntClicked_Up(true))
    {
    #if USE_SYS_TIMER_UPDATE
      SetNextTest();
    #else
      testStack[activeTest]->funcChangeData();
    #endif
    }
    
    //  Запуск
    if (MDRB_BntClicked_Right(true))
    {
    #if USE_SYS_TIMER_UPDATE
      testStack[activeTest]->funcChangeData();
    #else
      testStack[activeTest]->funcExec();
    #endif
    }
  }
}

void SysTick_Handler(void)
{
  testStack[activeTest]->funcExec();
}


void SetNextTest(void)
{
  testStack[activeTest]->funcFinit();

  ++activeTest;
  if (activeTest >= testCount)
    activeTest = 0;

  testStack[activeTest]->funcInit();
}
