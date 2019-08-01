#include <MDR_RST_Clock.h>
#include <MDRB_Buttons.h>
#include <MDR_PER_Clock.h>
#include <MDRB_UART_Debug.h>
#include <stdio.h>

#include <MDR_CRC.h>
#include "MDR_CRC16_Soft.h"

#define BTN_DEBOUNCE_MS   20

//  Подавление warnings компилятора V6 о добавлении  "пустот" в структуры
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wpadded"
#endif

typedef struct {
  uint16_t          Poly;
  uint16_t          Init;
  MDT_CRC_FirstBit  FirstBit;
  uint16_t          XorOut;
  uint16_t          checkCRC;   //  for string "123456789"
  char              name[20];
} MDR_CRC_PolyCfg;

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop  
#endif

uint16_t CalcHardCRC(uint32_t indPoly);

// Таблица из Википедии
//   https://ru.wikipedia.org/wiki/%D0%A6%D0%B8%D0%BA%D0%BB%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B9_%D0%B8%D0%B7%D0%B1%D1%8B%D1%82%D0%BE%D1%87%D0%BD%D1%8B%D0%B9_%D0%BA%D0%BE%D0%B4

#define CRC_MODBUS_IND      20
static const MDR_CRC_PolyCfg CRC_TABLE[] = {
  // Poly     Init      RefIn,Out     XorOut   Check    Name
    {0x8005,	0x0,	  CRC_FIRST_LSB,	   0x0,  0xBB3D,	"CRC-16/ARC"},
    {0x1021,	0x1D0F,	CRC_FIRST_MSB,	   0x0,  0xE5CC,	"CRC-16/AUG-CCITT"},
    {0x8005,	0x0,	  CRC_FIRST_MSB,	   0x0,  0xFEE8,	"CRC-16/BUYPASS"},
    {0x1021,	0xFFFF,	CRC_FIRST_MSB,	   0x0,  0x29B1,	"CRC-16/CCITT-FALSE"},
    {0xC867,	0xFFFF,	CRC_FIRST_MSB,	   0x0,  0x4C06,	"CRC-16/CDMA2000"},
    {0x8005,	0x800D,	CRC_FIRST_MSB,	   0x0,  0x9ECF,	"CRC-16/DDS-110"},
    {0x589,	  0x0,	  CRC_FIRST_MSB,	   0x1,    0x7E,	"CRC-16/DECT-R"},
    {0x589,	  0x0,	  CRC_FIRST_MSB,	   0x0,    0x7F,	"CRC-16/DECT-X"},
    {0x3D65,	0x0,	  CRC_FIRST_LSB,  0xFFFF,  0xEA82,	"CRC-16/DNP"},
    {0x3D65,	0x0,	  CRC_FIRST_MSB,	0xFFFF,  0xC2B7,  "CRC-16/EN-13757"},
    {0x1021,	0xFFFF,	CRC_FIRST_MSB,	0xFFFF,  0xD64E,	"CRC-16/GENIBUS"},
    {0x8005,	0x0,	  CRC_FIRST_LSB,	0xFFFF,  0x44C2,	"CRC-16/MAXIM"},
    {0x1021,	0xFFFF,	CRC_FIRST_LSB,	   0x0,  0x6F91,	"CRC-16/MCRF4XX"},
    {0x1021,	0xB2AA,	CRC_FIRST_LSB,	   0x0,  0x63D0,	"CRC-16/RIELLO"},
    {0x8BB7,	0x0,	  CRC_FIRST_MSB,	   0x0,  0xD0DB,	"CRC-16/T10-DIF"},
    {0xA097,	0x0,	  CRC_FIRST_MSB,	   0x0,   0xFB3,	"CRC-16/TELEDISK"},
    {0x1021,	0x89EC,	CRC_FIRST_LSB,	   0x0,  0x26B1,	"CRC-16/TMS37157"},
    {0x8005,	0xFFFF,	CRC_FIRST_LSB,	0xFFFF,  0xB4C8,	"CRC-16/USB"},
    {0x1021,	0xC6C6,	CRC_FIRST_LSB,	   0x0,  0xBF05,	"CRC-A"},
    {0x1021,	0x0,	  CRC_FIRST_LSB,	   0x0,  0x2189,	"CRC-16/KERMIT"},
    {0x8005,	0xFFFF,	CRC_FIRST_LSB,	   0x0,  0x4B37,	"CRC-16/MODBUS"},   //  CRC_MODBUS_IND
    {0x1021,	0xFFFF,	CRC_FIRST_LSB,	0xFFFF,  0x906E,	"CRC-16/X-25"},
    {0x1021,	0x0,	  CRC_FIRST_MSB,	   0x0,  0x31C3,	"CRC-16/XMODEM"},
};

static MDR_CRC_CfgReg cfgCRC = {
  .Cfg_b.Enable       = MDR_On,
  .Cfg_b.FirstBit     = CRC_FIRST_LSB,  
  .Cfg_b.DMA_En       = MDR_Off,
  .Cfg_b.WordSizeFIFO = CRC_FIFO_8Bit,
  .Cfg_b.WordSize     = CRC_Word_8Bit  
};

void TestPolyCRC(void);
void CalcSoftCRC(void);

int main(void)
{
  uint32_t freqCPU_Hz;
 
//MDR_DebugerProtectDelay();
  
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация кнопок
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  
  //  Включение UART_DBG для printf
  MDR_UART_DBG_Init();
  
  //  Начальная инициализация модуля CRC.
  MDR_CRC_Init(cfgCRC, 0);
  
  while (1)
  {
    if (MDRB_BntClicked_Up(true))
    {      
      TestPolyCRC();
    }  
    
    if (MDRB_BntClicked_Right(true))
    {      
      CalcSoftCRC();
    }      
    
  }  
}

static uint8_t testStr[] = "123456789";

uint16_t CalcHardCRC(uint32_t indPoly)
{
  uint16_t resCRC;
  
  //  Задание полинома и порядка бит
  cfgCRC.Cfg_b.FirstBit = CRC_TABLE[indPoly].FirstBit;
  MDR_CRC_ReInit(cfgCRC, CRC_TABLE[indPoly].Poly);  
  
  //  Рассчет CRC для массива байт
  resCRC = MDR_CRC_Calc(CRC_TABLE[indPoly].Init, 9, testStr);
  
  //  Если блок считал младшим битом вперед, то делаем реверсию бит результата, чтобы вернуть MSB.
  if (CRC_TABLE[indPoly].FirstBit == CRC_FIRST_LSB)
    resCRC = (uint16_t)(__RBIT(resCRC) >> 16);
  
  //  XOR результата
  resCRC ^= CRC_TABLE[indPoly].XorOut;

 return resCRC;
}

void TestPolyCRC(void)
{
  uint32_t i;
  uint32_t resCRC;
  
  for (i = 0; i < ARR_LEN(CRC_TABLE); ++i)
  {   
    // Подсчет CRC с выбраным полиномом
    resCRC = CalcHardCRC(i);
    
    //  Вывод результата в UART
    if (resCRC == CRC_TABLE[i].checkCRC)
      printf("%s OK: - %s\n", CRC_TABLE[i].FirstBit==CRC_FIRST_LSB?"LSB":"MSB", CRC_TABLE[i].name);
    else
      printf("%s FAULT: - %s  :  %x (right: %x)\n", CRC_TABLE[i].FirstBit==CRC_FIRST_LSB?"LSB":"MSB", CRC_TABLE[i].name, resCRC, CRC_TABLE[i].checkCRC);
  }
}

void CalcSoftCRC(void)
{
  uint16_t softCRC;
  uint16_t hardCRC;

  //  Программный рассчет
  softCRC = MDR_CRC16_SoftModbus(9, testStr);  
  //  Аппаратный рассчет
  hardCRC = CalcHardCRC(CRC_MODBUS_IND);
  
  printf("SoftCRC MODBUS %s: Soft %x = %x Hard\n", softCRC==hardCRC?"OK":"FAULT", softCRC, hardCRC);
}

