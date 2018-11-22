#include "MDRB_LCD.h"


static const uint8_t LCD_Font[] = {0xEE,0x60,0x2F,0x6D,0xE1,0xCD,0xCF,0x68,0xEF,0xED,0xEB,0xC7,0x8E,0x67,0x8F,0x8B}; // 0-9, A,B,C,D,E,F

#define CHAR_0    0x30
#define CHAR_9    0x39
#define CHAR_A    0x41
#define CHAR_F    0x46
#define CHAR_a    0x61
#define CHAR_f    0x66

//  Задержка
static uint32_t _Delay_100ns = 15;
static uint32_t _Delay_200ns = 30;

static void LCD_Initialize (void);


// =================    Директивы для работы с выводами дисплея ====================
// Вывод E1 (выбор кристалла 1)
__STATIC_INLINE void LCD_ClearBit_WR1(void) 
{  
  MDR_GPIO_ClearPins(MDRB_LCD_WR1_PORT, MDRB_LCD_WR1_PIN);
}

__STATIC_INLINE void LCD_SetBit_WR1(void) 
{  
  MDR_GPIO_SetPins(MDRB_LCD_WR1_PORT, MDRB_LCD_WR1_PIN);
}

__STATIC_INLINE void LCD_ClearBit_WR2(void) 
{  
  MDR_GPIO_ClearPins(MDRB_LCD_WR2_PORT, MDRB_LCD_WR2_PIN);
}

//__STATIC_INLINE void LCD_SetBit_WR2(void) 
//{  
//  MDR_GPIO_SetPins  (MDRB_LCD_WR2_PORT, MDRB_LCD_WR2_PIN);
//  MDR_Delay(_delay_10us);
//}

__STATIC_INLINE void LCD_ClearBit_A0(void) 
{  
  MDR_GPIO_ClearPins(MDRB_LCD_A0_PORT, MDRB_LCD_A0_PIN);
}

__STATIC_INLINE void LCD_SetBit_A0(void) 
{  
  MDR_GPIO_SetPins  (MDRB_LCD_A0_PORT, MDRB_LCD_A0_PIN);
}


// =================    Определения ресурсов - используемых Портов и пинов ==================== 
#ifdef MDRB_LCD_PORT_EX1
  #define MDR_LCD_PortCount    2
  static const MDR_GPIO_Port* _LCD_Port[MDR_LCD_PortCount] = {MDRB_LCD_PORT, MDRB_LCD_PORT_EX1};
  static const uint32_t       _LCD_Pins[MDR_LCD_PortCount] = {MDRB_LCD_PINS, MDRB_LCD_PINS_EX1};  
  
#else
  #define MDR_LCD_PortCount    1
  static const MDR_GPIO_Port* _LCD_Port[MDR_LCD_PortCount] = {MDRB_LCD_PORT};
  static const uint32_t       _LCD_Pins[MDR_LCD_PortCount] = {MDRB_LCD_PINS};
#endif

//  Маски для применения настроек пинов экрана LCD
static MDR_Port_ApplyMask  applyGPIO_Pins[MDR_LCD_PortCount];

  //  Настройки пинов, до перенастройки на использование под LCD - Captured Temp
static MDR_GPIO_CfgRegs  _TempPins[MDR_LCD_PortCount];

  
static void LCD_InitPins(void)
{
  uint32_t i;
  MDR_PinDig_PermRegs pinsPermRegs;
  
  //  Обнуление настроечный масок
  for (i = 0; i < MDR_LCD_PortCount; ++i)
    MDR_Port_MaskClear(&applyGPIO_Pins[i]);
  
  //  Базовые настройки пинов
  MDR_GPIO_InitDigPermRegs(MDR_PIN_PullPush, MDR_PIN_MAXFAST, MDR_Off, MDR_Off, &pinsPermRegs);
  
  //  Сбор настроек пинов в маски
  for (i = 0; i < MDR_LCD_PortCount; ++i)
  {
    MDR_GPIO_MaskAdd(_LCD_Pins[i], MDR_Pin_Out, MDR_PIN_PORT, &pinsPermRegs, &applyGPIO_Pins[i]);
    
    MDR_GPIO_ClockOn(_LCD_Port[i]);
    MDR_GPIO_MaskApply(_LCD_Port[i], &applyGPIO_Pins[i]);
  }  
}
  
void MDRB_LCD_CapturePins(void)
{
  uint32_t i;
  
  for (i = 0; i < MDR_LCD_PortCount; ++i)
  {
    MDR_GPIO_ReadRegs(_LCD_Port[i], &_TempPins[i]);
    MDR_GPIO_MaskApplyEx(_LCD_Port[i], &applyGPIO_Pins[i], &_TempPins[i]);
  } 
}

void MDRB_LCD_ReleasePins(void)
{
  uint32_t i;
  
  for (i = 0; i < MDR_LCD_PortCount; ++i)
  {
    MDR_GPIO_WriteRegs(_LCD_Port[i], &_TempPins[i]);
  } 
}  
  
void MDRB_LCD_ChangeFreqCPU(uint32_t CPU_FreqHz)
{
  _Delay_100ns = NS_TO_DELAY_LOOPS(100, CPU_FreqHz);
  if (_Delay_100ns == 0)
    _Delay_100ns = 1;
  _Delay_200ns = _Delay_100ns << 1;  
}

void MDRB_LCD_Init(uint32_t CPU_FreqHz)
{
  MDRB_LCD_ChangeFreqCPU(CPU_FreqHz);
  
  LCD_Initialize();
}

// =================    Управление дисплеем ==================== 
 
static void LCD_WriteAddr(uint8_t addr)
{
  // Addr
  MDRB_LCD_BusWrite(addr);
  LCD_ClearBit_A0();
  LCD_SetBit_WR1();
  LCD_ClearBit_WR2();
  MDR_Delay(_Delay_100ns); // t_WR  = 100us
  LCD_ClearBit_WR1();
  MDR_Delay(_Delay_100ns); // t_HAD = 100us
  LCD_SetBit_A0();
  MDR_Delay(_Delay_100ns); // t_P   = 200us (between WR1 pulses)
}

static void LCD_WriteData(uint8_t data, uint8_t dot)
{
  if (dot) 
    data |= 0x10;
  
  // DataLo
  MDRB_LCD_BusWrite(data);
  LCD_SetBit_WR1();
  MDR_Delay(_Delay_100ns); // t_WR  = 100us
  LCD_ClearBit_WR1();
  MDR_Delay(_Delay_200ns); // t_P   = 200us (between WR1 pulses)

  //  DataHi
  MDRB_LCD_BusWrite(data >> 4);
  LCD_SetBit_WR1();
  MDR_Delay(_Delay_100ns); // t_WR  = 100us
  LCD_ClearBit_WR1();
  MDR_Delay(_Delay_200ns); // t_P   = 200us (between WR1 pulses)
}

//запись по адресу addr символа simbol, dot-признак точки, если 0 - точки нет
static void LCD_WriteCode(uint8_t addr, uint8_t code, uint8_t dot)
{
  // Addr
  LCD_WriteAddr(addr);
  // Data
  LCD_WriteData(code, dot);
}

// Инициализация дисплея
static void LCD_Initialize (void)
{
	LCD_InitPins();
  
  LCD_SetBit_A0();
  
  LCD_ClearBit_WR2();
  LCD_ClearBit_WR1();
  MDRB_LCD_BusWrite(9);
	
  //разблокировка ЖКИ  
  LCD_WriteCode(0x0F, 0x10, 0);
}  
  
static uint8_t LCD_CharToCode(uint8_t symbol)
{
  if ((symbol >= CHAR_0) && (symbol <= CHAR_9))
    return LCD_Font[symbol - CHAR_0];
  else if ((symbol >= CHAR_A) && (symbol <= CHAR_F))
    return LCD_Font[symbol - CHAR_A + 10];
  else if ((symbol >= CHAR_a) && (symbol <= CHAR_f))
    return LCD_Font[symbol - CHAR_a + 10];  
  else
    return 0;
}

void MDRB_LCD_Print(const char* string)
{
  uint8_t i;
  uint8_t fillSpaces = 0;

  // Start Writing
  LCD_WriteAddr(0);
 
  //  Write Chars
  for (i = 0; i < LCD_SCREEN_WIDTH; i++)
  {
    if (!string[i])
      fillSpaces = 1;

    if (!fillSpaces)
      LCD_WriteData(LCD_CharToCode(string[i]), 0);
    else
      LCD_WriteData(0, 0);
  }
}

void MDRB_LCD_Clear (void)
{
  unsigned char i;

  for(i = 0; i < LCD_SCREEN_WIDTH; ++i)
  	LCD_WriteCode(i, 0, 0);
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

void MDRB_LCD_ScrollString (const char* string, uint8_t shift)
{
  char scroll[LCD_SCREEN_WIDTH + 1];  // Строка, получаемая в результате сдвига

  MDRB_LCD_ShiftString(string, shift, LCD_SCREEN_WIDTH, scroll);
  MDRB_LCD_Print(scroll);
}

void MDRB_LCD_ScrollStringLeft(const char* inpString, uint8_t strLength)
{
  static uint8_t shift = 0;   
 
  MDRB_LCD_ScrollString(inpString, shift); 
    
  ++shift;
  if (shift >= strLength)
    shift = 0;
}
