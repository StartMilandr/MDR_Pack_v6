#include <MDR_GPIO.h>

#include <MDR_Funcs.h>
#include <MDR_Config.h>
#include "MDR_SysTimer.h"
#include <MDRB_LEDs.h>
#include <MDRB_Buttons.h>
#include <MDR_RST_Clock.h>

#define   LED_TEST_ACTIVE    1

void TestCompile_RST(void);
void TestCompile_GPIO(void);

//  Вывод кнопок только на один светодиод, если светодиодов меньше трех
#ifndef MDRB_LED_2
  #define MDRB_LED_2  MDRB_LED_1
  #define ONLY_OneLED
#endif

#ifndef MDRB_LED_3
  #define ONLY_OneLED
#endif

#define PERIOD_MS     1000
#define LED_CYCLE     MDRB_LED_1
#define LED_TIMER     MDRB_LED_2
#define DEBOUNCE_MS   10

void SysTick_Handler(void);

void LedTestRoutine(void);
void KeyTestRoutine(void);
void LED_Flash(uint32_t LedSel);

int main(void)
{ 
  //CPU_SetClock_HSI_def();
  
  MDRB_LED_InitALL();
  MDRB_Buttons_InitEx(DEBOUNCE_MS, HSI_FREQ_HZ);
  
  MDRB_LED_Set(MDRB_LED_PinAll, true);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
  MDRB_LED_Set(MDRB_LED_PinAll, false);
  
  
#if LED_TEST_ACTIVE
  MDR_SysTimerStart_ms(PERIOD_MS, HSI_FREQ_HZ);
#endif    
  
  while (1)
  {    
#if LED_TEST_ACTIVE    
    LedTestRoutine();
    
#else
    KeyTestRoutine();
#endif    
  }
}

void LedTestRoutine(void)
{
  MDRB_LED_Switch(LED_CYCLE);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
}

void LED_Flash(uint32_t LedSel)
{
#ifndef ONLY_OneLED
  LED_SetOut(LedSel);
#else
  LED_SetOut(1);
#endif
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
  LED_SetOut(0);
}

void KeyTestRoutine(void)
{
  // Опрос нажатия кнопок
  if (MDRB_BntClicked_Up(false))
    LED_Flash(1);
  if (MDRB_BntClicked_Right(false))
    LED_Flash(2);
  if (MDRB_BntClicked_Down(false))
    LED_Flash(3);
  if (MDRB_BntClicked_Left(false))
    LED_Flash(4);

#if defined (MDRB_BTN_PIN_KEY5) 
  if (MDRB_BntClicked_Select(false))
    LED_Flash(5);
#endif
  
#if defined (MDRB_BTN_PIN_KEY6)  
  if (MDRB_BntClicked_Back(false))
    LED_Flash(6);
#endif
}

void SysTick_Handler(void)
{
  MDRB_LED_Switch(LED_TIMER);
}


void TestCompile_GPIO(void)
{
#define PORT_X      MDR_GPIO_A
#define PIN_SEL     MDR_Pin_0
#define PIN_IND     1
#define PIN_IO      MDR_Pin_Out 
#define PIN_FUNC    MDR_PIN_PORT
  
  
  MDR_GPIO_CfgRegs cfgRegs;
  MDR_PinDig_PermRegs  permRegs;
  MDR_Port_ApplyMask mskApply;  

  //  Structs Init
  MDR_GPIO_InitDigPermRegs(MDR_PIN_PullPush, MDR_PIN_FAST, MDR_Off, MDR_Off, &permRegs);
  MDR_GPIO_ToCfgRegs(PIN_IO, PIN_FUNC, &permRegs, &cfgRegs);
  
  
// === GPIO Function call ===
  MDR_GPIO_ClockOn(PORT_X);  
  MDR_GPIO_Reset(PORT_X);

  MDR_GPIO_Init(PORT_X, PIN_SEL, &cfgRegs);
  MDR_GPIO_InitAnalog(PORT_X, PIN_SEL);

  MDR_GPIO_InitDig(PORT_X, PIN_SEL, MDR_Pin_Out, MDR_PIN_PORT, &permRegs);
  MDR_GPIO_InitDigPin(PORT_X, PIN_IND, PIN_IO, PIN_FUNC, &permRegs);

  MDR_GPIO_MaskClear(&mskApply);
  MDR_GPIO_MaskAdd(PIN_SEL, PIN_IO, PIN_FUNC, &permRegs, &mskApply);
  MDR_GPIO_MaskAddPin(PIN_IND, PIN_IO, PIN_FUNC, &permRegs, &mskApply);
  MDR_GPIO_MaskApply(PORT_X, &mskApply);


  MDR_GPIO_ReadRegs(PORT_X, &cfgRegs);
  MDR_GPIO_WriteRegs(PORT_X, &cfgRegs);
  
  MDR_GPIO_SetPins(PORT_X, PIN_SEL);
  MDR_GPIO_ClearPins(PORT_X, PIN_SEL);
  MDR_GPIO_Get(PORT_X);
  
  MDR_GPIO_ClockOff(PORT_X);
}

void TestCompile_RST(void)
{
//  RST_ResetBlock_def();

//  CPU_SetClock_LSI_def();    

//  CPU_SetClock_HSI_def();
//  CPU_SetClock_HSI_PLL_def(MDR_x4);
//  CPU_SetClock_HSI_div2_PLL_def(MDR_x4);

//  CPU_SetClock_HSE_def();
//  CPU_SetClock_HSE_PLL_def(MDR_x4, MDR_Off);
//  CPU_SetClock_HSE_div2_PLL_def(MDR_x4, MDR_Off);
//  
//  CPU_SetClock_LSE_def(MDR_Off); 
}

