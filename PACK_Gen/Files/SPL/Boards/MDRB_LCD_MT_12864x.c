#include <MDRB_LCD.h>

#include <MDRB_LCD_Font.h>


static void LCD_Initialize (void);

// =================    Заставка ====================
// Строка, выводимая на индикатор при инициализации
static const char* header = "   \xC0\xCE \"\xCC\xE8\xEB\xE0\xED\xE4\xF0\"";  // АО "Миландр"

// Изображение, выводимое на индикатор при инициализации (эмблема "Миландр")
static const uint8_t logo[32] =
{
  0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x7E, 0x1E, 0x06,
  0x06, 0x1E, 0x7E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
  0x7F, 0x5F, 0x47, 0x41, 0x7C, 0x78, 0x70, 0x60,
  0x60, 0x70, 0x78, 0x7C, 0x41, 0x47, 0x5F, 0x7F
};

//  Задержки
#define DELAY_DEF_10ns      1

static uint32_t _delay_RES_On    = (DELAY_DEF_10ns * 100);   // 1000ns =  1us
static uint32_t _delay_RES_Off   = (DELAY_DEF_10ns * 1000);  //          10us

static uint32_t _delay_Tas       = (DELAY_DEF_10ns * 14);   //  140ns  Начало цикла, задержка между выставлением RW,A0,E1,E2 и выставлением Е
static uint32_t _delay_Tpwen     = (DELAY_DEF_10ns * 45);   //  450ns  Длительность строба чтения/записи
static uint32_t _delay_Tdsw      = (DELAY_DEF_10ns * 20);   //  200us  Задержка перед сбросом Е, после записи данных
static uint32_t _delay_Tddr      = (DELAY_DEF_10ns * 32);   //  320us  Задержка перед чтеним данных, после выставления Е
static uint32_t _delay_Tah       = (DELAY_DEF_10ns     );   //   10ns  Окончание цикла, после сброса E до сброса RW,A0,E1,E2
static uint32_t _delay_Tw        = (DELAY_DEF_10ns * 8000); //   8ns   Пауза между подачей команд или данных

// =================    Директивы для работы с выводами дисплея ====================
// Вывод E1 (выбор кристалла 1)
#define LCD_ClearBit_E1     MDR_GPIO_ClearPins(MDRB_LCD_E1_PORT, MDRB_LCD_E1_PIN)
#define LCD_SetBit_E1       MDR_GPIO_SetPins  (MDRB_LCD_E1_PORT, MDRB_LCD_E1_PIN)

// Вывод E2 (выбор кристалла 2)
#define LCD_ClearBit_E2     MDR_GPIO_ClearPins(MDRB_LCD_E2_PORT, MDRB_LCD_E2_PIN)
#define LCD_SetBit_E2       MDR_GPIO_SetPins  (MDRB_LCD_E2_PORT, MDRB_LCD_E2_PIN)

// Вывод RES (сброс)
#ifdef MDRB_LCD_RES_PORT
  #define LCD_ClearBit_RES  MDR_GPIO_ClearPins(MDRB_LCD_RES_PORT, MDRB_LCD_RES_PIN)
  #define LCD_SetBit_RES    MDR_GPIO_SetPins  (MDRB_LCD_RES_PORT, MDRB_LCD_RES_PIN)
#else
  #define LCD_ClearBit_RES  //__nop()
  #define LCD_SetBit_RES    //__nop()
#endif

// Вывод R/W (чтение/запись)
#define LCD_ClearBit_RW     MDR_GPIO_ClearPins(MDRB_LCD_RW_PORT, MDRB_LCD_RW_PIN)
#define LCD_SetBit_RW       MDR_GPIO_SetPins  (MDRB_LCD_RW_PORT, MDRB_LCD_RW_PIN)

// Вывод A0 (команды/данные)
#define LCD_ClearBit_A0     MDR_GPIO_ClearPins(MDRB_LCD_A0_PORT, MDRB_LCD_A0_PIN)
#define LCD_SetBit_A0       MDR_GPIO_SetPins  (MDRB_LCD_A0_PORT, MDRB_LCD_A0_PIN)

// Вывод E (стробирование данных)
#define LCD_ClearBit_E      MDR_GPIO_ClearPins(MDRB_LCD_E_PORT, MDRB_LCD_E_PIN)
#define LCD_SetBit_E        MDR_GPIO_SetPins  (MDRB_LCD_E_PORT, MDRB_LCD_E_PIN)


// =================    Определения ресурсов - используемых Портов и пинов ====================
//  IN Pins
#ifdef MDRB_LCD_IN_PORT_EX1
  #define MDR_LCD_PortCountIN     2
  static const MDR_GPIO_Port* _LCD_PortIN[MDR_LCD_PortCountIN] = {MDRB_LCD_IN_PORT, MDRB_LCD_IN_PORT_EX1};
  static const uint32_t       _LCD_PinsIN[MDR_LCD_PortCountIN] = {MDRB_LCD_IN_PINS, MDRB_LCD_IN_PINS_EX1};
#else
  #define MDR_LCD_PortCountIN     1
  static const MDR_GPIO_Port* _LCD_PortIN[MDR_LCD_PortCountIN] = {MDRB_LCD_IN_PORT};
  static const uint32_t       _LCD_PinsIN[MDR_LCD_PortCountIN] = {MDRB_LCD_IN_PINS};
#endif

//  OUT Pins
#ifdef MDRB_LCD_OUT_PORT_EX2
  #define MDR_LCD_PortCountOUT    3
  static const MDR_GPIO_Port* _LCD_PortOUT[MDR_LCD_PortCountOUT] = {MDRB_LCD_OUT_PORT, MDRB_LCD_OUT_PORT_EX1, MDRB_LCD_OUT_PORT_EX2};
  static const uint32_t       _LCD_PinsOUT[MDR_LCD_PortCountOUT] = {MDRB_LCD_OUT_PINS, MDRB_LCD_OUT_PINS_EX1, MDRB_LCD_OUT_PINS_EX2};  
  
#elif defined (MDRB_LCD_OUT_PORT_EX1)
  #define MDR_LCD_PortCountOUT    2
  static const MDR_GPIO_Port* _LCD_PortOUT[MDR_LCD_PortCountOUT] = {MDRB_LCD_OUT_PORT, MDRB_LCD_OUT_PORT_EX1};
  static const uint32_t       _LCD_PinsOUT[MDR_LCD_PortCountOUT] = {MDRB_LCD_OUT_PINS, MDRB_LCD_OUT_PINS_EX1};  
  
#else
  #define MDR_LCD_PortCountOUT    1
  static const MDR_GPIO_Port* _LCD_PortOUT[MDR_LCD_PortCountOUT] = {MDRB_LCD_OUT_PORT};
  static const uint32_t       _LCD_PinsOUT[MDR_LCD_PortCountOUT] = {MDRB_LCD_OUT_PINS};
#endif

//  Маски для применения настроек пинов экрана LCD
static MDR_Port_ApplyMask  applyGPIO_PinsIN[MDR_LCD_PortCountIN];
static MDR_Port_ApplyMask  applyGPIO_PinsOUT[MDR_LCD_PortCountOUT];

  //  Настройки пинов, до перенастройки на использование под LCD - Captured Temp
static MDR_GPIO_SetCfg  _TempPinsIN[MDR_LCD_PortCountIN];
static MDR_GPIO_SetCfg  _TempPinsOUT[MDR_LCD_PortCountOUT];


static void LCD_InitPins(void)
{
  uint32_t i;
  MDR_PinDig_GroupPinCfg groupPinCfg;
  
  //  Обнуление настроечный масок
  for (i = 0; i < MDR_LCD_PortCountIN; ++i)
    MDR_Port_MaskClear(&applyGPIO_PinsIN[i]);
  for (i = 0; i < MDR_LCD_PortCountOUT; ++i)
    MDR_Port_MaskClear(&applyGPIO_PinsOUT[i]);
  
  //  Базовые настройки пинов
#ifdef MDR_GPIO_HAS_GFEN_SCHMT  
  MDR_Port_InitDigGroupPinCfg(MDR_Off, MDR_PIN_MAXFAST, MDR_Off, MDR_Off, &groupPinCfg);
#else
  MDR_Port_InitDigGroupPinCfg(MDR_Off, MDR_PIN_MAXFAST, &groupPinCfg);
#endif  

  //  Сбор настроек пинов в маски
  for (i = 0; i < MDR_LCD_PortCountIN; ++i)
  {
    MDR_GPIO_MaskAdd(_LCD_PinsIN[i], MDR_Pin_In, MDR_PIN_PORT, &groupPinCfg, &applyGPIO_PinsIN[i]);
    
    MDR_GPIO_Enable(_LCD_PortIN[i]);
    MDR_GPIO_MaskApply(_LCD_PortIN[i], &applyGPIO_PinsIN[i]);
  }
  for (i = 0; i < MDR_LCD_PortCountOUT; ++i)
  {
    MDR_GPIO_MaskAdd(_LCD_PinsOUT[i], MDR_Pin_Out, MDR_PIN_PORT, &groupPinCfg, &applyGPIO_PinsOUT[i]);
    
#ifdef MDRB_LCD_RES_PORT
    //  Не сбрасывать пин Reset, экран отрубается в 1986ВЕ3У
    if (_LCD_PortOUT[i] == MDRB_LCD_RES_PORT)
      applyGPIO_PinsOUT[i].MaskSET.RXTX |= MDRB_LCD_RES_PIN;
#endif

#ifdef MDRB_LCD_CONFLICT_PORT
    //  Не сбрасывать пин Reset, экран отрубается в 1986ВЕ3У
    if (_LCD_PortOUT[i] == MDRB_LCD_CONFLICT_PORT)
      applyGPIO_PinsOUT[i].MaskSET.RXTX |= MDRB_LCD_CONFLICT_PIN;
#endif
    
    MDR_GPIO_Enable(_LCD_PortOUT[i]);
    MDR_GPIO_MaskApply(_LCD_PortOUT[i], &applyGPIO_PinsOUT[i]);
  }
}	

void MDRB_LCD_CapturePins(void)
{
  uint32_t i;
  
  for (i = 0; i < MDR_LCD_PortCountIN; ++i)
  {
    //  Сохраняем текущие настройки порта, для восстановления в MDRB_LCD_ReleasePins
    MDR_GPIO_ReadRegs(_LCD_PortIN[i], &_TempPinsIN[i]);
    //  Применяем маски Clear и Set, для переключения в новые настройки
    MDR_GPIO_MaskApplyEx(_LCD_PortIN[i], &applyGPIO_PinsIN[i], &_TempPinsIN[i]);
  }
  for (i = 0; i < MDR_LCD_PortCountOUT; ++i)
  {
    MDR_GPIO_ReadRegs(_LCD_PortOUT[i], &_TempPinsOUT[i]);
    MDR_GPIO_MaskApplyEx(_LCD_PortOUT[i], &applyGPIO_PinsOUT[i], &_TempPinsOUT[i]);
  } 
}

#ifdef MDR_GPIO_CFG_SET_CLEAR    
  void MDRB_LCD_ReleasePins(void)
  {
    uint32_t i;
    
    //  Возвращаем сохраненные настройки в качестве Set маски, 
    //  Маска стирания таже что и при MDRB_LCD_CapturePins
    for (i = 0; i < MDR_LCD_PortCountIN; ++i)
      MDR_GPIO_WriteRegs(_LCD_PortIN[i], &_TempPinsIN[i], &applyGPIO_PinsIN[i].MaskCLR);
    
    for (i = 0; i < MDR_LCD_PortCountOUT; ++i)
      MDR_GPIO_WriteRegs(_LCD_PortOUT[i], &_TempPinsOUT[i], &applyGPIO_PinsIN[i].MaskCLR);
  }

#else
  void MDRB_LCD_ReleasePins(void)
  {
    uint32_t i;
    
    //  Возвращаем сохраненные настройки
    for (i = 0; i < MDR_LCD_PortCountIN; ++i)
      MDR_GPIO_WriteRegs(_LCD_PortIN[i], &_TempPinsIN[i]);
    
    for (i = 0; i < MDR_LCD_PortCountOUT; ++i)
      MDR_GPIO_WriteRegs(_LCD_PortIN[i], &_TempPinsIN[i]);
  }
#endif


void MDRB_LCD_ChangeFreqCPU(uint32_t CPU_FreqHz)
{ 
  _delay_RES_On    = NS_TO_DELAY_LOOPS(1000, CPU_FreqHz);   // 1000ns =  1us
  _delay_RES_Off   = _delay_RES_On * 10;                    //           10us

  _delay_Tas       = NS_TO_DELAY_LOOPS(140, CPU_FreqHz);    //  140ns  Начало цикла, задержка между выставлением RW,A0,E1,E2 и выставлением Е
  _delay_Tddr      = NS_TO_DELAY_LOOPS(320, CPU_FreqHz);    //  320ns  Задержка перед чтеним данных, после выставления Е  
  _delay_Tpwen     = NS_TO_DELAY_LOOPS(450, CPU_FreqHz);    //  450ns  Длительность строба чтения/записи  
  _delay_Tdsw      = NS_TO_DELAY_LOOPS(200, CPU_FreqHz);    //  200ns  Задержка перед сбросом Е, после записи данных
  _delay_Tah       = NS_TO_DELAY_LOOPS(10,  CPU_FreqHz);    //   10ns  Окончание цикла, после сброса E до сброса RW,A0,E1,E2    
  _delay_Tw        = US_TO_DELAY_LOOPS(8,  CPU_FreqHz);     //   8ns   Пауза между подачей команд или данных  
}

void MDRB_LCD_Init(uint32_t CPU_FreqHz)
{
  MDRB_LCD_ChangeFreqCPU(CPU_FreqHz);
  LCD_Initialize();
}

//  ====================  Служебные функции =======================
// Возврат выводов в исходное состояние
static void LCD_CycleEnd (uint8_t chip)
{
  // Сброс вывода E
  LCD_ClearBit_E;
  MDR_Delay(_delay_Tah);

  // Сброс вывода A0
  LCD_ClearBit_A0;
  // Сброс вывода R/W
  LCD_ClearBit_RW;
  // Восстановление конфигурации шины данных
  MDRB_LCD_BusSetIN();

  // Отмена выбора кристалла (сброса вывода E1 или E2)
  if (chip != 1)
    LCD_ClearBit_E1;
  else
    LCD_ClearBit_E2;
}

#define LCD_CHIP_1    1
#define LCD_A0_DATA   2

// Чтение из LCD
static uint8_t LCD_Read(uint8_t code)
{
  uint8_t data;

  // Выбор кристалла (установка вывода E1 или E2)
  if (code & LCD_CHIP_1)
    LCD_SetBit_E2;    //  Right half
  else
    LCD_SetBit_E1;    //  Left half
  
  // Выбор команда / данные
  if (code & LCD_A0_DATA)
    LCD_SetBit_A0;    // адрес данных
  else
    LCD_ClearBit_A0;  // служебные сигналы
  
  // Режим Чтения
  LCD_SetBit_RW;      // чтение данных
  
  //  Задержка и выставление строба E
  MDR_Delay(_delay_Tas);  
  LCD_SetBit_E;
  
  // Задержка на выставление данных
  MDR_Delay(_delay_Tddr);

  // Чтение данных
  data = MDRB_LCD_BusRead();
  
  // Задержка на удержание минимального времени строба Е
  MDR_Delay(_delay_Tpwen - _delay_Tddr);
  
  // Возврат в исходное состояние
  LCD_CycleEnd(code & LCD_CHIP_1);

  return data;
}

// Запись в LCD
static void LCD_Write(uint8_t code, uint8_t command)
{
  // Выбор кристалла (установка вывода E1 или E2)
  if (code & LCD_CHIP_1)
    LCD_SetBit_E2;    //  Right half
  else
    LCD_SetBit_E1;    //  Left half

  // Выбор команда / данные
  if (code & LCD_A0_DATA)
    LCD_SetBit_A0;    // адрес данных
  else
    LCD_ClearBit_A0;  // служебные сигналы
 
  // Режим записи
  LCD_ClearBit_RW;

  // Конфигурация шины данных для передачи
  MDRB_LCD_BusSetOUT();  
  
  //  Задержка и выставление строба E
  MDR_Delay(_delay_Tas);
  LCD_SetBit_E;
  
  // Задержка на удержание минимального времени строба Е
  MDR_Delay(_delay_Tpwen - _delay_Tdsw);
  // Передача данных
  MDRB_LCD_BusWrite(command);
  MDR_Delay(_delay_Tdsw);

  // Возврат в исходное состояние, сброс строба
  LCD_CycleEnd(code & LCD_CHIP_1);
  
  //  Пауза до следующей команды или данных
  MDR_Delay(_delay_Tw);   
}


// Чтение статуса
__STATIC_INLINE uint8_t LCD_ReadStatus (uint8_t chip) {return LCD_Read(chip);}
// Включение дисплея
__STATIC_INLINE void LCD_Enable (uint8_t chip) {LCD_Write(chip, 0x3F);}
// Выбор страницы
__STATIC_INLINE void LCD_SetPage(uint8_t chip, uint8_t page) {LCD_Write(chip, 0xB8 | page);}
// Выбор адреса колонки
__STATIC_INLINE void LCD_SetAddress (uint8_t chip, uint8_t address) {LCD_Write(chip, 0x40 | address);}

// Запись данных в ОЗУ дисплея
__STATIC_INLINE void LCD_WriteData (uint8_t chip, uint8_t data) {LCD_Write(chip | LCD_A0_DATA, data);}

//    Неиспольземые функции
// Выключение дисплея
//__STATIC_INLINE void LCD_Disable(uint8_t chip) {LCD_Write(chip, 0x3E);}
// Чтение данных из ОЗУ дисплея
//__STATIC_INLINE uint8_t LCD_ReadData (uint8_t chip) {return LCD_Read(chip | LCD_A0_DATA);}

// Очистка страницы
static void LCD_ClearPage (uint8_t chip, uint8_t page)
{
  uint8_t i;

  // Выбор страницы
  LCD_SetPage (chip, page);

  // Выбор адреса
  LCD_SetAddress (chip, 0x00);

  // Цикл очистки
  for (i = 0; i < 64; i++)
  {
    // Ожидание завершения операций с дисплеем
    while (LCD_ReadStatus (chip) & 0x80);

    // Сброс битов
    LCD_WriteData (chip, 0x00);
  }
}

// Очистка дисплея
static void LCD_ClearScreen (uint8_t chip)
{
  uint8_t i;

  // Очистка всех страниц
  for (i = 0; i < 8; i++)
    LCD_ClearPage (chip, i);
}


//  ====================  Управление экраном   =======================

// Инициализация дисплея
static void LCD_Initialize (void)
{
	LCD_InitPins();

  // Инициализация драйвера дисплея
  // Сброс вывода RES
  LCD_ClearBit_RES;
  MDR_Delay(_delay_RES_On);

  // Установка вывода RES
  LCD_SetBit_RES;  
  MDR_Delay(_delay_RES_Off);

  // Ожидание завершения инициализации
  while ((LCD_ReadStatus(0) & 0x90) && (LCD_ReadStatus(1) & 0x90));

  // Ожидание завершения операций и включение кристалла 1
  while (LCD_ReadStatus(0) & 0x80);
  LCD_Enable(0);

  // Ожидание завершения операций и включение кристалла 2
  while (LCD_ReadStatus(1) & 0x80);
  LCD_Enable(1);

  // Очистка памяти дисплея
  LCD_ClearScreen(0);
  LCD_ClearScreen(1);

  // Отображение заголовочных элементов
  MDRB_LCD_Print(header, 1);
  MDRB_LCD_PutImage(logo, 0, 0, 1, 1);
}

void MDRB_LCD_Clear (void)
{
  LCD_ClearScreen(0);
  LCD_ClearScreen(1);
}

// Вывод символа
void MDRB_LCD_PutSymbol (uint8_t symbol, uint8_t x, uint8_t y)
{
  uint8_t chip, page, address;
  uint32_t i;
  uint32_t index;  // Индекс первого элемента символа в массиве шрифта

  chip    = (uint8_t)(x / 8);        // Выражение номера кристалла через координату символа по оси абсцисс
  page    = y;                       // Выражение номера страницы через координату символа по оси ординат
  address = (uint8_t)((x % 8) * 8);  // Выражение номера колонки через координату символа по оси абсцисс

  // Выбор страницы
  LCD_SetPage (chip, page);

  // Выбора адреса колонки
  LCD_SetAddress (chip, address);

  // Проверка пренадлежности символа к заданному диапазону кодировок
  if (symbol >= FONT_MIN_CODE && symbol <= FONT_MAX_CODE)
    index = (((uint32_t) symbol) - FONT_MIN_CODE) * 8;
  // Если заданный код находится вне диапазона, то выбирается первый символ массива (пробел)
  else
    index = 0;

  // Вывод символа
  for (i = index; i < (index + 8); i++)
  {
    // Ожидание завершения операций с дисплеем
    while (LCD_ReadStatus (chip) & 0x80);

    // Запись символа в память дисплея
    LCD_WriteData (chip, Font[i]);
  }
}

// Вывод строки
void MDRB_LCD_Print(const char* string, uint8_t y)
{
  uint8_t i;

  // Цикл формирования строки
  for (i = 0; i < LCD_SCREEN_WIDTH; i++)
  {
    // Остановка цикла, если достигнут конец строки
    if (!string[i])
      break;

    // Вывод символа
    MDRB_LCD_PutSymbol (string[i], i, y);
  }

  // Заполнение оставшейся части массива пустыми символами
  for (; i < LCD_SCREEN_WIDTH; i++)
    MDRB_LCD_PutSymbol (0x20, i, y);
}

void MDRB_LCD_ClearLine(uint8_t y)
{
  uint8_t i;
  
  // Заполнение массива пустыми символами
  for (i = 0; i < LCD_SCREEN_WIDTH; i++)
    MDRB_LCD_PutSymbol (0x20, i, y);
}


// Вывод изображения
void MDRB_LCD_PutImage (const uint8_t* image, uint8_t top, uint8_t left, uint8_t bottom, uint8_t right)
{
  uint8_t i, x, y;
  uint8_t chip, page, address;
  uint8_t count = 0;

  // Циклы формирования изображения
  for (y = top; y <= bottom; y++)
    for (x = left; x <= right; x++)
    {
      chip    = (uint8_t)(x / 8);        // Выражение номера кристалла через координату символа по оси абсцисс
      page    = y;                       // Выражение номера страницы через координату символа по оси ординат
      address = (uint8_t)((x % 8) * 8);  // Выражение номера колонки через координату символа по оси абсцисс

      // Выбор страницы
      LCD_SetPage (chip, page);

      // Выбора адреса колонки
      LCD_SetAddress (chip, address);

      // Цикл формирования элемента изображения
      for (i = 0; i < 8; i++)
      {
        // Ожидание завершения операций с дисплеем
        while (LCD_ReadStatus (chip) & 0x80);

        // Запись элемента изображения размером 8x8 в память дисплея
        LCD_WriteData (chip, image[count + i]);
      }

      // Сдвиг на следующую строку
      count += 8;
    }
}

void MDRB_LCD_ShiftString (const char* inpString, uint8_t shift, uint8_t screenWidth, char* outString)
{
  uint8_t i, j;

  // Пропуск пустой строки
  if (!strlen(inpString))
    return;

  j = shift;
  for (i = 0; i < screenWidth; i++)
  {
    if (inpString[j] == 0)
      j = 0;

    outString[i] = inpString[j];
    ++j;
  }
  outString[screenWidth] = 0;
}

void MDRB_LCD_ScrollString (const char* string, uint8_t y, uint8_t shift)
{
  char scroll[LCD_SCREEN_WIDTH + 1];  // Строка, получаемая в результате сдвига

  MDRB_LCD_ShiftString(string, shift, LCD_SCREEN_WIDTH, scroll);
  MDRB_LCD_Print(scroll, y);
}

void MDRB_LCD_ScrollStringLeft(const char* inpString, uint8_t y, uint8_t strLength)
{
  static uint8_t shift = 0;   
 
  MDRB_LCD_ScrollString(inpString, y, shift); 
    
  ++shift;
  if (shift >= strLength)
    shift = 0;
}


