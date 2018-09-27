#include "MDRB_LEDs.h"

void MDRB_LED_Init(uint32_t LEDs_Sel)
{	
  // Clock Enable	
  MDR_GPIO_ClockOn(MDRB_LED_GPIO);
  
  // Pins Init
  MDR_GPIO_InitOutDef(MDRB_LED_GPIO, LEDs_Sel & MDRB_LED_PinAll);
}

#ifdef LED_ON_TO_GND
  #define Func_LED_On    MDR_GPIO_ClearPins
  #define Func_LED_Off   MDR_GPIO_SetPins
#else
  #define Func_LED_On    MDR_GPIO_SetPins
  #define Func_LED_Off   MDR_GPIO_ClearPins
#endif

void MDRB_LED_Set(uint32_t LEDs_Sel, bool isOn)
{
	if (isOn)
		Func_LED_On(MDRB_LED_GPIO, LEDs_Sel);
	else
		Func_LED_Off(MDRB_LED_GPIO, LEDs_Sel);
}

void MDRB_LED_Switch(uint32_t LEDs_Sel)
{
  MDR_GPIO_SwitchPins(MDRB_LED_GPIO, LEDs_Sel);
}	


//  ==========================    Keil LED API ==========================
#if defined (MDRB_LED_8)
  #define MDRB_LED_COUNT  8
  static const uint32_t _LED_Pins[MDRB_LED_COUNT] = {MDRB_LED_1, MDRB_LED_2, MDRB_LED_3, MDRB_LED_4, MDRB_LED_5, MDRB_LED_6, MDRB_LED_7, MDRB_LED_8};

#elif defined (MDRB_LED_5)
  #define MDRB_LED_COUNT  5
  static const uint32_t _LED_Pins[MDRB_LED_COUNT] = {MDRB_LED_1, MDRB_LED_2, MDRB_LED_3, MDRB_LED_4, MDRB_LED_5};
  
#elif defined (MDRB_LED_2)
  #define MDRB_LED_COUNT  2
  static const uint32_t _LED_Pins[MDRB_LED_COUNT] = {MDRB_LED_1, MDRB_LED_2};
  
#elif defined (MDRB_LED_1)
  #define MDRB_LED_COUNT  1
  static const uint32_t _LED_Pins[MDRB_LED_COUNT] = {MDRB_LED_1};
  
#endif


int32_t 	LED_Initialize (void)
{ 
  MDRB_LED_Init(MDRB_LED_PinAll);
  return 0;
}

int32_t 	LED_Uninitialize (void)
{
  MDR_GPIO_InitAnalog(MDRB_LED_GPIO, MDRB_LED_PinAll);
  return 0;
}

int32_t 	LED_On (uint32_t num)
{
  Func_LED_On(MDRB_LED_GPIO, _LED_Pins[num]);
  return 0;
}

int32_t 	LED_Off (uint32_t num)
{
  Func_LED_Off(MDRB_LED_GPIO, _LED_Pins[num]);
  return 0;
}

int32_t 	LED_SetOut (uint32_t val)
{
  uint32_t i;
  uint32_t pinSet = 0;
  uint32_t pinClr = 0;
  
  for (i = 0; i < MDRB_LED_COUNT; ++i)
    if ((val & (1 << i)) != 0)
      pinSet |= _LED_Pins[i];
    else
      pinClr |= _LED_Pins[i];

  if (pinSet)
    Func_LED_On(MDRB_LED_GPIO, pinSet);
  if (pinClr)
    Func_LED_Off(MDRB_LED_GPIO, pinClr);
    
  return 0;
}

uint32_t 	LED_GetCount (void)
{
  return MDRB_LED_COUNT;
}

