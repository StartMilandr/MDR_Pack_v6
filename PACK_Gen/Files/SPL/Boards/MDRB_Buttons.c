#include <MDRB_Buttons.h>
	
  
//==================    Привязка кнопок к портам ==============  
//  Порты, к которым подключены кнопки
#if defined (MDRB_BTN_GPIO_Ex2)
  #define KEY_PORT_COUNT  3
  static const MDR_GPIO_Port* _KEY_PortUpdate[KEY_PORT_COUNT] = {MDRB_BTN_GPIO, MDRB_BTN_GPIO_Ex1, MDRB_BTN_GPIO_Ex2};
#elif defined (MDRB_BTN_GPIO)
  #define KEY_PORT_COUNT  1
  static const MDR_GPIO_Port* _KEY_PortUpdate[KEY_PORT_COUNT] = {MDRB_BTN_GPIO};
#else
  #define MDRB_HAS_NO_BUTTONS
#endif

#ifdef MDRB_HAS_NO_BUTTONS
  //==========================    Кнопок нет. Пустые функции, чтобы изежать проверок на наличие кнопок в проектах  ==============
  // Если подключить внешние кнопки и задефайнить в MDRB_... файле, то код соберется без исправлений.
  void MDRB_Buttons_InitTick(uint32_t debounce_tick) {}
  bool MDRB_IsKeyPushed(MDRB_Keys key, bool use_debounce) { return false; }
  bool MDRB_IsKeyPushedEx(const MDR_GPIO_Port *GPIO_Port, uint32_t pinSel, uint32_t debounceTicks) { return false;}

  void MDRB_Buttons_ChangeDebounceTick(uint32_t debounce_tick) {}

  //  Вернет True если кнопка была нажата и отпущена, 
  //  Содержит бесконечный цикл ожидания отжатия кнопки!
  bool MDRB_IsKeyClicked(MDRB_Keys key, bool use_debounce) { return false; }


#else
//==========================    Обработка кнопок  ==============

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
                                                             MDRB_BTN_PORT_KEY4, MDRB_BTN_PORT_KEY5}; //, MDRB_BTN_PORT_KEY_P1};
    static const uint32_t       _KEY_Pins[KEY_COUNT]  = {MDRB_BTN_PIN_KEY1,  MDRB_BTN_PIN_KEY2,  MDRB_BTN_PIN_KEY3, 
                                                             MDRB_BTN_PIN_KEY4,  MDRB_BTN_PIN_KEY5}; //,  MDRB_BTN_PIN_KEY_P1};
  #elif defined (MDRB_BTN_PIN_KEY4)
    // ========== 4 кнопки на плате=============
    #define KEY_COUNT  4
    #define KEY_MASK   0x000FUL
    static const MDR_GPIO_Port* _KEY_Ports[KEY_COUNT] = {MDRB_BTN_PORT_KEY1, MDRB_BTN_PORT_KEY2,   MDRB_BTN_PORT_KEY3, 
                                                             MDRB_BTN_PORT_KEY4}; //, MDRB_BTN_PORT_KEY_P1, MDRB_BTN_PORT_KEY_P2};
    static const uint32_t       _KEY_Pins[KEY_COUNT]  = {MDRB_BTN_PIN_KEY1,  MDRB_BTN_PIN_KEY2,    MDRB_BTN_PIN_KEY3, 
                                                             MDRB_BTN_PIN_KEY4}; //,  MDRB_BTN_PIN_KEY_P1,  MDRB_BTN_PIN_KEY_P2};
  #elif defined (MDRB_BTN_PIN_KEY3)
    // ========== 4 кнопки на плате=============
    #define KEY_COUNT  3
    #define KEY_MASK   0x0007UL
    static const MDR_GPIO_Port* _KEY_Ports[KEY_COUNT] = {MDRB_BTN_PORT_KEY1, MDRB_BTN_PORT_KEY2,   MDRB_BTN_PORT_KEY3};
    static const uint32_t       _KEY_Pins[KEY_COUNT]  = {MDRB_BTN_PIN_KEY1,  MDRB_BTN_PIN_KEY2,    MDRB_BTN_PIN_KEY3};
                                                             
  #elif defined (MDRB_BTN_PIN_KEY2)
    // ========== 2 кнопки на плате=============
    #define KEY_COUNT  2
    #define KEY_MASK   0x0003UL
    static const MDR_GPIO_Port* _KEY_Ports[KEY_COUNT] = {MDRB_BTN_PORT_KEY1, MDRB_BTN_PORT_KEY2}; //,   MDRB_BTN_PORT_KEY_P1};
    static const uint32_t       _KEY_Pins[KEY_COUNT]  = {MDRB_BTN_PIN_KEY1,  MDRB_BTN_PIN_KEY2}; //,    MDRB_BTN_PIN_KEY_P1};
                                                             
  #else
    Buttons configuration need to be added!
  #endif

                                                     
  //=================   Инициализация кнопок =================
  #define DEBOUNCE_DELAY_MS_DEF     1
  static uint32_t _debounceTicks  = MS_TO_CLOCKS(DEBOUNCE_DELAY_MS_DEF, HSI_FREQ_HZ);
                                                     
  void MDRB_Buttons_ChangeDebounceTick(uint32_t debounce_tick)
  {
    _debounceTicks = debounce_tick;
  }
                                                         
  void MDRB_Buttons_InitTick(uint32_t debounce_tick)
  {
    _debounceTicks = debounce_tick;
    
    MDR_GPIO_Enable(MDRB_BTN_GPIO);
    MDR_GPIO_Init_PortIN(MDRB_BTN_GPIO, MDRB_BTN_PinSel);

  #ifdef MDRB_BTN_GPIO_Ex1
    MDR_GPIO_Enable(MDRB_BTN_GPIO_Ex1);
    MDR_GPIO_Init_PortIN(MDRB_BTN_GPIO_Ex1, MDRB_BTN_PinSel_Ex1);
  #endif
    
  #ifdef MDRB_BTN_GPIO_Ex2
    MDR_GPIO_Enable(MDRB_BTN_GPIO_Ex2);
    MDR_GPIO_Init_PortIN(MDRB_BTN_GPIO_Ex2, MDRB_BTN_PinSel_Ex2);
  #endif  
  }


  // =============    Проверка нажатия кнопки ===================
  #ifdef MDRB_BTNs_PUSH_TO_GND
    #define KEY_PUSHED    MDR_GPIO_GetMaskClr
  #else
    #define KEY_PUSHED    MDR_GPIO_GetMaskSet
  #endif

  bool MDRB_IsKeyPushedEx(const MDR_GPIO_Port *GPIO_Port, uint32_t pinSel, uint32_t debounceTicks)
  {
    bool result = KEY_PUSHED(GPIO_Port, pinSel);
    if ((debounceTicks == 0) || (result == false))
      return result;
    
    MDR_Delay(debounceTicks);
    
    if (KEY_PUSHED(GPIO_Port, pinSel) == result)
      return result;
    else
      return false;
  }

  bool MDRB_IsKeyPushed(MDRB_Keys key, bool use_debounce)
  {
    if (use_debounce)
      return MDRB_IsKeyPushedEx(_KEY_Ports[key], _KEY_Pins[key], _debounceTicks);
    else
      return MDRB_IsKeyPushedEx(_KEY_Ports[key], _KEY_Pins[key], 0);
  }

  bool MDRB_IsKeyClicked(MDRB_Keys key, bool use_debounce)
  {
    if (!(MDRB_IsKeyPushed(key, use_debounce)))
      return false;
    
    while (MDRB_IsKeyPushed(key, 0));
    return true;
  }

  //  ================    Keil Buttons API ===============
  int32_t 	Buttons_Initialize (void)
  {
    MDRB_Buttons_InitTick(0);
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

#endif

