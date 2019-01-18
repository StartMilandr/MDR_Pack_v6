//#include <MDRB_LCD_XT13468PSPA.h>
#include <MDRB_LCD.h>
#include <MDRB_LCD_Font_XT13468PSPA.h>

// -------------------- Инициализация выводов GPIO ----------------------
#define MDR_LCD_PortCount    3
static const MDR_GPIO_Port* _LCD_Port[MDR_LCD_PortCount] = {MDRB_LCD_PORT, MDRB_LCD_PORT_EX1, MDRB_LCD_PORT_EX2};
static const uint32_t       _LCD_Pins[MDR_LCD_PortCount] = {MDRB_LCD_PINs, MDRB_LCD_PINs_EX1, MDRB_LCD_PINs_EX2};

//  Маски для применения настроек пинов экрана LCD
static MDR_Port_ApplyMask  applyGPIO_Pins[MDR_LCD_PortCount];
  //  Настройки пинов, до перенастройки на использование под LCD - Captured Temp
static MDR_GPIO_CfgRegs  _TempPins[MDR_LCD_PortCount];

static void LCD_InitPins(void)
{
  uint32_t i;
  
  //  Обнуление настроечный масок
  for (i = 0; i < MDR_LCD_PortCount; ++i)
    MDR_Port_MaskClear(&applyGPIO_Pins[i]);

  //  Сбор настроек пинов в маски
  for (i = 0; i < MDR_LCD_PortCount; ++i)
  {
    MDR_GPIO_MaskAddAnalog(_LCD_Pins[i], &applyGPIO_Pins[i]);

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

// -------------------- Вывод в LCD контроллер ----------------------
void MDRB_XT_DataApply(LCD_XT_DATA *lcdData, MDR_OnOff toAlterMem)
{
  if (toAlterMem == MDR_Off)
  {
    MDR_LCD->ROW1 = lcdData->LCD_ROW1;
    MDR_LCD->ROW2 = lcdData->LCD_ROW2;
    MDR_LCD->ROW3 = lcdData->LCD_ROW3;
    MDR_LCD->ROW4 = lcdData->LCD_ROW4;
  }
  else
  {
    MDR_LCD->AROW1 = lcdData->LCD_ROW1;
    MDR_LCD->AROW2 = lcdData->LCD_ROW2;
    MDR_LCD->AROW3 = lcdData->LCD_ROW3;
    MDR_LCD->AROW4 = lcdData->LCD_ROW4;    
  }
}


// -------------------- Управление LCD через входную переменную типа LCD_HTD_REG128 ----------------------
void MDRB_XT_DataClear(LCD_XT_DATA *lcdData)
{
  lcdData->LCD_ROW1 = 0;
  lcdData->LCD_ROW2 = 0;
  lcdData->LCD_ROW3 = 0;
  lcdData->LCD_ROW4 = 0;
}

void MDRB_XT_DataClearNUM(LCD_XT_DATA *lcdData, MDRB_XT_NUM_Item numItem)
{
  lcdData->LCD_ROW1 &= ~(LCD_NUM_CLEAR[0] << ((uint32_t)numItem << 1));
  lcdData->LCD_ROW2 &= ~(LCD_NUM_CLEAR[1] << ((uint32_t)numItem << 1));
  lcdData->LCD_ROW3 &= ~(LCD_NUM_CLEAR[2] << ((uint32_t)numItem << 1));
  lcdData->LCD_ROW4 &= ~(LCD_NUM_CLEAR[3] << ((uint32_t)numItem << 1));
}

void MDRB_XT_DataClearStr(LCD_XT_DATA *lcdData)
{
  lcdData->LCD_ROW1 &= LCD_NUMS_CLEAR_MASK_R123;
  lcdData->LCD_ROW2 &= LCD_NUMS_CLEAR_MASK_R123;
  lcdData->LCD_ROW3 &= LCD_NUMS_CLEAR_MASK_R123;
  lcdData->LCD_ROW4 &= LCD_NUMS_CLEAR_MASK_R4;
}

static int CharToFontIndex(uint8_t symbol)
{
  if ((symbol >= CHAR_0) && (symbol <= CHAR_9))
    return symbol - CHAR_0;
  else if ((symbol >= CHAR_A) && (symbol <= CHAR_F))
    return symbol - CHAR_A + 10;
  else if ((symbol >= CHAR_a) && (symbol <= CHAR_f))
    return symbol - CHAR_a + 10;  
  else
    return -1;
}

//#define NUM_OFFSET(n) (((uint32_t)n << 2) + 2)
#define NUM_OFFSET(n) ((uint32_t)n << 1)

static void MDRB_XT_AddChar(LCD_XT_DATA *lcdData, MDRB_XT_NUM_Item numItem, uint8_t symbol)
{
  int32_t fntIndex = CharToFontIndex(symbol);
  if (fntIndex < 0)
    return;
  
//  const uint32_t *pNum = &LCD_XT_Font[4 * fntIndex];
//  
//  lcdData->LCD_ROW1 |= (pNum[0] << (uint32_t)numItem);
//  lcdData->LCD_ROW2 |= (pNum[1] << (uint32_t)numItem);
//  lcdData->LCD_ROW3 |= (pNum[2] << (uint32_t)numItem);
//  lcdData->LCD_ROW4 |= (pNum[3] << (uint32_t)numItem);  
  
  lcdData->LCD_ROW1 |= (LCD_XT_Font[4 * fntIndex] << NUM_OFFSET(numItem));
  lcdData->LCD_ROW2 |= (LCD_XT_Font[4 * fntIndex + 1] << NUM_OFFSET(numItem));
  lcdData->LCD_ROW3 |= (LCD_XT_Font[4 * fntIndex + 2] << NUM_OFFSET(numItem));
  lcdData->LCD_ROW4 |= (LCD_XT_Font[4 * fntIndex + 3] << NUM_OFFSET(numItem)); 
}

void MDRB_XT_DataWriteStr(LCD_XT_DATA *lcdData, const char* string)
{
  uint32_t i;
  MDRB_XT_DataClearStr(lcdData);

  for (i = 0; i < LCD_XT_NUM_COUNT; ++i)
  {
    if (string[i] == 0)
      break;
    MDRB_XT_AddChar(lcdData, (MDRB_XT_NUM_Item)i, string[i]);
  }  
}

// -------------------- Вывод на экран ----------------------
void MDRB_XT_DataPring(LCD_XT_DATA *lcdData, const char* string, MDR_OnOff toAlterMem)
{
  MDRB_XT_DataWriteStr(lcdData, string);  
  MDRB_XT_DataApply(lcdData, toAlterMem);
}


// -------------------- Управление LCD через глобальную переменную LCD_HTD_REG128 ----------------------
static MDR_LCD_CfgMux cfgLCD_Mux = {
  .multPlex = MDR_LCD_MultPlex_4,
  .multBias = MDR_LCD_MultBias_3
};

static MDR_LCD_Cfg _cfgLCD_def = {
  //  Основные настройки
  .useExternalPower = MDR_Off,
  .clockSource      = MDR_LCD_CLK_LSI,
  .frameDIV         = 256,
  
  //  Настройки опции мигания дисплея, если NULL - мигание выключено
  .pBlinkCfg = NULL,
  //  Настройки мультиплексирования, если NULL - статический контроль (без мультиплексирования)
  .pMuxCfg = &cfgLCD_Mux
};

LCD_XT_DATA _MDR_LCD_Data;

void MDRB_LCD_Init(uint32_t CPU_FreqHz)
{ 
  UNUSED(CPU_FreqHz);

  MDR_LCD_Init(&_cfgLCD_def);  
  LCD_InitPins(); 
  MDRB_LCD_Clear();
}  

void MDRB_LCD_Print(const char* string)
{
  MDRB_XT_DataWriteStr(&_MDR_LCD_Data, string);  
  MDRB_XT_DataApply(&_MDR_LCD_Data, MDR_Off);
}

void MDRB_LCD_Clear(void)
{  
  MDRB_XT_DataClear(&_MDR_LCD_Data);  
  MDRB_XT_DataApply(&_MDR_LCD_Data, MDR_Off);
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

