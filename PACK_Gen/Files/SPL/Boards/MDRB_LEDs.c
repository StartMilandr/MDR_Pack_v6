#include "MDRB_LEDs.h"

//  ===============   Boards LED Control  ============
void MDRB_LED_Init(uint32_t LEDs_Sel)
{	
  // Clock Enable	
  MDR_GPIO_Enable(MDRB_LED_GPIO);
  
  // Pins Init
  MDR_GPIO_Init_PortOUT(MDRB_LED_GPIO, LEDs_Sel & MDRB_LED_PinAll, MDR_PIN_SLOW);
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

void MDRB_LED_Toggle(uint32_t LEDs_Sel)
{
  MDR_GPIO_TogglePins(MDRB_LED_GPIO, LEDs_Sel);
}	


//  ==========================    Led Index To Mask ==========================
#if defined (MDRB_LED_8)
  #define MDRB_LED_COUNT  8
  static const uint32_t _LED_Pins[MDRB_LED_COUNT] = {MDRB_LED_1, MDRB_LED_2, MDRB_LED_3, MDRB_LED_4, MDRB_LED_5, MDRB_LED_6, MDRB_LED_7, MDRB_LED_8};

#elif defined (MDRB_LED_5)
  #define MDRB_LED_COUNT  5
  static const uint32_t _LED_Pins[MDRB_LED_COUNT] = {MDRB_LED_1, MDRB_LED_2, MDRB_LED_3, MDRB_LED_4, MDRB_LED_5};
  
#elif defined (MDRB_LED_4)
  #define MDRB_LED_COUNT  4
  static const uint32_t _LED_Pins[MDRB_LED_COUNT] = {MDRB_LED_1, MDRB_LED_2, MDRB_LED_3, MDRB_LED_4};  
  
#elif defined (MDRB_LED_3)
  #define MDRB_LED_COUNT  3
  static const uint32_t _LED_Pins[MDRB_LED_COUNT] = {MDRB_LED_1, MDRB_LED_2, MDRB_LED_3};
  
#elif defined (MDRB_LED_2)
  #define MDRB_LED_COUNT  2
  static const uint32_t _LED_Pins[MDRB_LED_COUNT] = {MDRB_LED_1, MDRB_LED_2};
  
#elif defined (MDRB_LED_1)
  #define MDRB_LED_COUNT  1
  static const uint32_t _LED_Pins[MDRB_LED_COUNT] = {MDRB_LED_1};
  
#endif

uint32_t MDRB_LED_SelIndToMask(uint32_t ledSelByInd)
{
  uint32_t i;
  uint32_t result = 0;  
  for (i = 0; i < MDRB_LED_COUNT; ++i)
    if ((ledSelByInd & (1 << i)) != 0)
      result |= _LED_Pins[i];
  
  return result & MDRB_LED_PinAll;    
}
  

//  ==========================    Keil LED API ==========================  
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

void 			LED_Toggle (uint32_t index)
{
  if (index < MDRB_LED_COUNT)
		MDRB_LED_Toggle(_LED_Pins[index]);
}


uint32_t MDRB_LED_NumToSel(uint32_t num)
{
  uint32_t i;
  uint32_t LEDs_Sel = 0;
  
  for (i = 0; i < MDRB_LED_COUNT; ++i)
    if ((num & (1 << i)) != 0)
      LEDs_Sel |= _LED_Pins[i];
    
  return LEDs_Sel;
}


#ifdef USE_BOARD_VE1 
  //  ===============   Ethernet Boards LED Control  ============
  void MDRB_LED_ETH1_Init(uint32_t LEDs_Sel)
  {	
    // Clock Enable	
    MDR_GPIO_Enable(MDRB_LED_ETH1_GPIO);
    
    // Pins Init
    MDR_GPIO_Init_PortOUT(MDRB_LED_ETH1_GPIO, LEDs_Sel & MDRB_LED_ETH1_PinAll, MDR_PIN_SLOW);
  }

  void MDRB_LED_ETH1_Set(uint32_t LEDs_Sel, bool isOn)
  {
    if (isOn)
      MDR_GPIO_SetPins(MDRB_LED_ETH1_GPIO, LEDs_Sel);
    else
      MDR_GPIO_ClearPins(MDRB_LED_ETH1_GPIO, LEDs_Sel);
  }

  void MDRB_LED_ETH1_Toggle(uint32_t LEDs_Sel)
  {
    MDR_GPIO_TogglePins(MDRB_LED_ETH1_GPIO, LEDs_Sel);
  }	
#endif

