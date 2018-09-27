#include "MDRB_Buttons.h"
	
  
//==================    Привязка кнопок к портам ==============  
//  Порты, к которым подключены кнопки
//#if defined (MDRB_BTN_GPIO_Ex1)
//  #define KEY_PORT_COUNT  2
//  static const MDR_GPIO_Port* _KEY_PortUpdate[KEY_PORT_COUNT] = {MDRB_BTN_GPIO, MDRB_BTN_GPIO_Ex1};
#if defined (MDRB_BTN_GPIO_Ex2)
  #define KEY_PORT_COUNT  3
  static const MDR_GPIO_Port* _KEY_PortUpdate[KEY_PORT_COUNT] = {MDRB_BTN_GPIO, MDRB_BTN_GPIO_Ex1, MDRB_BTN_GPIO_Ex2};
#else
  #define KEY_PORT_COUNT  1
  static const MDR_GPIO_Port* _KEY_PortUpdate[KEY_PORT_COUNT] = {MDRB_BTN_GPIO};
#endif

//  Привязка кнопок к портам
#if defined (MDRB_BTN_PIN_KEY6)
  // ========== 6 кнопок на плате=============
  #define KEY_COUNT  6
  #define KEY_MASK   0x003FUL
  static const MDR_GPIO_Port* _KEY_Ports[KEY_COUNT] = {MDRB_BTN_PORT_KEY1, MDRB_BTN_PORT_KEY2, MDRB_BTN_PORT_KEY3, 
                                                       MDRB_BTN_PORT_KEY4, MDRB_BTN_PORT_KEY5, MDRB_BTN_PORT_KEY6};
  static const uint32_t       _KEY_Pins[KEY_COUNT]  = {MDRB_BTN_PIN_KEY1,  MDRB_BTN_PIN_KEY2,  MDRB_BTN_PIN_KEY3, 
                                                       MDRB_BTN_PIN_KEY4,  MDRB_BTN_PIN_KEY5,  MDRB_BTN_PIN_KEY6};
#elif defined (MDRB_BTN_PIN_KEY5)                                                       
  // ========== 5 кнопок на плате=============
  #define KEY_COUNT  5
  #define KEY_MASK   0x001FUL
  static const MDR_GPIO_Port* _KEY_Ports[KEY_COUNT] = {MDRB_BTN_PORT_KEY1, MDRB_BTN_PORT_KEY2, MDRB_BTN_PORT_KEY3, 
                                                       MDRB_BTN_PORT_KEY4, MDRB_BTN_PORT_KEY5};
  static const uint32_t       _KEY_Pins[KEY_COUNT]  = {MDRB_BTN_PIN_KEY1,  MDRB_BTN_PIN_KEY2,  MDRB_BTN_PIN_KEY3, 
                                                       MDRB_BTN_PIN_KEY4,  MDRB_BTN_PIN_KEY5};
#elif defined (MDRB_BTN_PIN_KEY4)
  // ========== 4 кнопки на плате=============
  #define KEY_COUNT  4
  #define KEY_MASK   0x000FUL
  static const MDR_GPIO_Port* _KEY_Ports[KEY_COUNT] = {MDRB_BTN_PORT_KEY1, MDRB_BTN_PORT_KEY2, MDRB_BTN_PORT_KEY3, 
                                                       MDRB_BTN_PORT_KEY4};
  static const uint32_t       _KEY_Pins[KEY_COUNT]  = {MDRB_BTN_PIN_KEY1,  MDRB_BTN_PIN_KEY2,  MDRB_BTN_PIN_KEY3, 
                                                       MDRB_BTN_PIN_KEY4};
#else
  Buttons configuration need to be added!
#endif

                                                   
//=================   Инициализация кнопок =================
static uint32_t _debounceTicks  = MS_TO_TIKS(10, 8000000);
                                                   
void MDRB_Buttons_Init(uint32_t debounce_tick)
{
  _debounceTicks = debounce_tick;
  
  MDR_GPIO_ClockOn(MDRB_BTN_GPIO);
  MDR_GPIO_InitInDef(MDRB_BTN_GPIO, MDRB_BTN_PinSel);

#ifdef MDRB_BTN_GPIO_Ex1
  MDR_GPIO_ClockOn(MDRB_BTN_GPIO_Ex1);
  MDR_GPIO_InitInDef(MDRB_BTN_GPIO_Ex1, MDRB_BTN_PinSel_Ex1);
#endif
  
#ifdef MDRB_BTN_GPIO_Ex2
  MDR_GPIO_ClockOn(MDRB_BTN_GPIO_Ex2);
  MDR_GPIO_InitInDef(MDRB_BTN_GPIO_Ex2, MDRB_BTN_PinSel_Ex2);
#endif  
}


// =============    Проверка нажатия кнопки ===================
#ifdef MDRB_BTNs_PUSH_TO_GND
  #define KEY_PUSHED(port, pin)  (!(MDR_GPIO_GetMaskSet (port, pin)))  
#else
  #define KEY_PUSHED(port, pin)    (MDR_GPIO_GetMaskSet (port, pin))
#endif

bool MDRB_IsKeyPushedEx(MDRB_Keys key, uint32_t debounceTicks)
{
  bool result = KEY_PUSHED(_KEY_Ports[key], _KEY_Pins[key]);
  if (debounceTicks == 0)
    return result;
  
  MDR_Delay(debounceTicks);
  
  if (KEY_PUSHED(_KEY_Ports[key], _KEY_Pins[key]) == result)
    return result;
  else
    return false;
}

bool MDRB_IsKeyPushed(MDRB_Keys key, bool use_debounce)
{
  if (use_debounce)
    return MDRB_IsKeyPushedEx(key, _debounceTicks);
  else
    return MDRB_IsKeyPushedEx(key, 0);
}

bool MDRB_IsKeyClicked(MDRB_Keys key, bool use_debounce)
{
  if (!(MDRB_IsKeyPushed(key, use_debounce)))
    return false;
  
  while (MDRB_IsKeyPushed(key, 0));
  return true;
}

//uint32_t BRD_Is_BntAct_Select (void)
//{
//	return PORT_READ_PIN(BRD_BTN_PORT_SEL, BRD_BTN_PIN_SEL);
//}

//uint32_t BRD_Is_BntAct_Up (void)
//{
//	return PORT_READ_PIN(BRD_BTN_PORT_UP, BRD_BTN_PIN_UP);
//}

//#ifdef BRD_BTN_PIN_DOWN
//uint32_t BRD_Is_BntAct_Down (void)
//{
//	return PORT_READ_PIN(BRD_BTN_PORT_DOWN, BRD_BTN_PIN_DOWN);
//}
//#endif

//#ifdef BRD_BTN_PIN_LEFT
//uint32_t BRD_Is_BntAct_Left (void)
//{
//	return PORT_READ_PIN(BRD_BTN_PORT_LEFT, BRD_BTN_PIN_LEFT);
//}
//#endif

//#ifdef BRD_BTN_PIN_RIGHT
//uint32_t BRD_Is_BntAct_Right (void)
//{
//	return PORT_READ_PIN(BRD_BTN_PORT_RIGHT, BRD_BTN_PIN_RIGHT);
//}
//#endif

//#ifdef BRD_BTN_PIN_BACK
//uint32_t BRD_Is_BntAct_Back (void)
//{
//	return PORT_READ_PIN(BRD_BTN_PORT_BACK, BRD_BTN_PIN_BACK);
//}
//#endif


//  ================    Keil Buttons API ===============
int32_t 	Buttons_Initialize (void)
{
  MDRB_Buttons_Init(0);
  return 0;
}
  
int32_t 	Buttons_Uninitialize (void)
{
  MDR_GPIO_InitAnalog(MDRB_BTN_GPIO, MDRB_BTN_PinSel);
  return 0;
}

uint32_t 	Buttons_GetState (void)
{
  uint32_t i, j;
  uint32_t PortPins;
  uint32_t result = 0;
  
  //  Keys State Update
  for (i = 0; i < KEY_PORT_COUNT; ++i)
  {
    PortPins = MDR_GPIO_Get(_KEY_PortUpdate[i]);
    // Update Key status of the same port
    for (j = 0; j < KEY_COUNT; ++j)
      if (_KEY_Ports[j] == _KEY_PortUpdate[i])
        result |= PortPins & _KEY_Pins[j];
  }

#ifdef MDRB_BTNs_PUSH_TO_GND
  result ^= KEY_MASK;
#endif
  
  return result;
}

uint32_t 	Buttons_GetCount (void)
{
  return KEY_PORT_COUNT;
}


