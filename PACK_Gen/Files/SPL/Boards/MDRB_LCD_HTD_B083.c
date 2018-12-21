#include <MDR_GPIO.h>
#include <MDRB_LCD.h>
#include <MDR_Funcs.h>

static const uint8_t LCD_Font[] = {0x6F,0x28,0x5D,0x7C,0x3A,0x76,0x77,0x2C,0x7F, 0x7E,0x3F,0x73,0x47,0x79,0x57,0x17}; // 0-9, A,B,C,D,E,F

#define CHAR_0    0x30
#define CHAR_9    0x39
#define CHAR_A    0x41
#define CHAR_F    0x46
#define CHAR_a    0x61
#define CHAR_f    0x66

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

// -------------------- Инициализация выводов GPIO ----------------------
#define MDR_LCD_PortCount    2
static const MDR_GPIO_Port* _LCD_Port[MDR_LCD_PortCount] = {MDRB_LCD_PORT, MDRB_LCD_PORT_LD};
static const uint32_t       _LCD_Pins[MDR_LCD_PortCount] = {MDRB_LCD_PINS, MDRB_LCD_PINS_LD};

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

// -------------------- Вывод в регистр LCD ----------------------
static const MDR_GPIO_Port *LED_GPIO_CD = MDRB_LCD_PORT;
static const MDR_GPIO_Port *LED_GPIO_LD = MDRB_LCD_PORT_LD;
static uint32_t _delayTicks = _LCD_DELAY_TICK_DEF;

static void MDRB_HTD_ApplyRegBits(uint32_t data32, uint32_t bitCount, uint32_t regValue)
{
  uint32_t i, bitSel;
  MDR_PORT_Type *PORTx = LED_GPIO_CD->PORTx;
    
  //  Serial output
  bitSel = (uint32_t)1UL << (bitCount - 1);
  for (i = 0; i < bitCount; ++i)
  {
    if (data32 & bitSel)
      regValue |= MDRB_LCD_DIN;
    else
      regValue &= ~MDRB_LCD_DIN;
    
    //  DATA_SET   
    PORTx->RXTX = (regValue) & MDRB_Jtag_ClrPinsPA;
    MDR_Delay(_delayTicks);

    //  CLK_ON
    PORTx->RXTX = (regValue | MDRB_LCD_DCLK) & MDRB_Jtag_ClrPinsPA;
    MDR_Delay(_delayTicks << 1);
    
    //  CLK_OFF
    PORTx->RXTX = regValue & MDRB_Jtag_ClrPinsPA;
    MDR_Delay(_delayTicks);
    
    bitSel >>= 1;
  }
}

#define LOAD_ENA  LED_GPIO_LD->PORTx->RXTX &= ~(MDRB_LCD_PINS_LD)
#define LOAD_DIS  LED_GPIO_LD->PORTx->RXTX |= MDRB_LCD_PINS_LD

void MDRB_HTD_RegApply(LCD_HTD_REG128 *lcdReg)
{
  uint32_t regValue;
  MDR_PORT_Type *PORTx = LED_GPIO_CD->PORTx;
  
  //  Load enable
  LOAD_ENA;
  MDR_Delay(_delayTicks);
  
  //  Serial output
  regValue = PORTx->RXTX;
  regValue &= ~(MDRB_LCD_DIN | MDRB_LCD_DCLK);
  PORTx->RXTX = regValue & MDRB_Jtag_ClrPinsPA;
   
  MDRB_HTD_ApplyRegBits(lcdReg->LCD_REG4, 23, regValue);
  MDRB_HTD_ApplyRegBits(lcdReg->LCD_REG3, 32, regValue);
  MDRB_HTD_ApplyRegBits(lcdReg->LCD_REG2, 32, regValue);
  MDRB_HTD_ApplyRegBits(lcdReg->LCD_REG1, 32, regValue);  
  
  PORTx->RXTX = regValue & MDRB_Jtag_ClrPinsPA;
  
  //  Load disable
  LOAD_DIS;
}

// -------------------- Управление LCD через входную переменную типа LCD_HTD_REG128 ----------------------
void MDRB_HTD_RegClear(LCD_HTD_REG128 *lcdReg)
{
  lcdReg->LCD_REG1 = 0;
  lcdReg->LCD_REG2 = 0;
  lcdReg->LCD_REG3 = 0;
  lcdReg->LCD_REG4 = 0;
}

void MDRB_HTD_RegClearStr(LCD_HTD_REG128 *lcdReg)
{
  lcdReg->LCD_REG1_b.NUM_8 = 0;
  lcdReg->LCD_REG1_b.NUM_7 = 0;
  lcdReg->LCD_REG1_b.NUM_6 = 0;
  lcdReg->LCD_REG2_b.NUM_5 = 0;
  lcdReg->LCD_REG2_b.NUM_4 = 0;
  lcdReg->LCD_REG2_b.NUM_3 = 0;
  lcdReg->LCD_REG3_b.NUM_2 = 0;
  lcdReg->LCD_REG3_b.NUM_1 = 0;
  lcdReg->LCD_REG3_b.NUM_0 = 0;
  lcdReg->LCD_REG3_b.NUM_9L = 0;
  lcdReg->LCD_REG4_b.NUM_9H = 0;
  lcdReg->LCD_REG4_b.NUM_10 = 0;
}

void MDRB_HTD_RegWriteStr(LCD_HTD_REG128 *lcdReg, const char* string)
{
  MDRB_HTD_RegClearStr(lcdReg);
  
  if (string[0] == 0) return;
  lcdReg->LCD_REG1_b.NUM_8 = LCD_CharToCode(string[0]);
  
  if (string[1] == 0) return;
  lcdReg->LCD_REG1_b.NUM_7 = LCD_CharToCode(string[1]);  
  
  if (string[2] == 0) return;
  lcdReg->LCD_REG1_b.NUM_6 = LCD_CharToCode(string[2]);    
  
  if (string[3] == 0) return;
  lcdReg->LCD_REG2_b.NUM_5 = LCD_CharToCode(string[3]);    
  
  if (string[4] == 0) return;
  lcdReg->LCD_REG2_b.NUM_4 = LCD_CharToCode(string[4]);    
  
  if (string[5] == 0) return;
  lcdReg->LCD_REG2_b.NUM_3 = LCD_CharToCode(string[5]);    
  
  if (string[6] == 0) return;
  lcdReg->LCD_REG3_b.NUM_2 = LCD_CharToCode(string[6]);    
  
  if (string[7] == 0) return;
  lcdReg->LCD_REG3_b.NUM_1 = LCD_CharToCode(string[7]);    
  
  if (string[8] == 0) return;
  lcdReg->LCD_REG3_b.NUM_0 = LCD_CharToCode(string[8]);
  
  if (string[9] == 0) return; 
  {
    uint8_t ch = LCD_CharToCode(string[9]);
    lcdReg->LCD_REG3_b.NUM_9L = ch & 0x3F;
    lcdReg->LCD_REG4_b.NUM_9H = (ch >> 6) & 0x01;
  }

  if (string[10] == 0) return;
  lcdReg->LCD_REG4_b.NUM_10 = LCD_CharToCode(string[10]);
}

void MDRB_HTD_RegPring(LCD_HTD_REG128 *lcdReg, const char* string)
{
  MDRB_HTD_RegWriteStr(lcdReg, string);  
  MDRB_HTD_RegApply(lcdReg);
}

// -------------------- Управление LCD через глобальную переменную LCD_HTD_REG128 ----------------------
LCD_HTD_REG128 _MDR_LCD_Reg128;

void MDRB_LCD_Init(uint32_t CPU_FreqHz)
{ 
  UNUSED(CPU_FreqHz);

  LCD_InitPins(); 
  MDRB_LCD_Clear();
}  

void MDRB_LCD_Print(const char* string)
{
  MDRB_HTD_RegWriteStr(&_MDR_LCD_Reg128, string);  
  MDRB_HTD_RegApply(&_MDR_LCD_Reg128);
}

void MDRB_LCD_Clear(void)
{  
  MDRB_HTD_RegClear(&_MDR_LCD_Reg128);  
  MDRB_HTD_RegApply(&_MDR_LCD_Reg128);
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

