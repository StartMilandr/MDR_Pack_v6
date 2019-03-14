#ifndef MDR_LCD_VK214_H
#define MDR_LCD_VK214_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <MDR_Types.h>


//  ===================== Настраиваемые параметры LCD экрана ======================

//  Multiplexing parameters
typedef enum {
  MDR_LCD_MultPlex_2   = LCD_CR_Mux_2,
  MDR_LCD_MultPlex_3   = LCD_CR_Mux_3,
  MDR_LCD_MultPlex_4   = LCD_CR_Mux_4
} MDR_LCD_MultPlex;

typedef enum {
  MDR_LCD_MultBias_3   = LCD_CR_Bias_div3,
  MDR_LCD_MultBias_2   = LCD_CR_Bias_div2,
} MDR_LCD_MultBias;

typedef struct {
  MDR_LCD_MultPlex  multPlex;
  MDR_LCD_MultBias  multBias;
} MDR_LCD_CfgMux;

//  Blink parameters
typedef enum {
  MDR_LCD_Blink_2Hz   = LCD_CR_BF_2Hz,
  MDR_LCD_Blink_1Hz   = LCD_CR_BF_1Hz,
  MDR_LCD_Blink_0Hz5  = LCD_CR_BF_0Hz5
} MDR_LCD_BlinkFreq;

typedef struct {
  MDR_LCD_BlinkFreq  blinkFreq;
  //  Экран может мигать (включать-выключать сегменты), либо вместо выключения переключаться на альтернативные данные
  MDR_OnOff          blinkToAlterData;
} MDR_LCD_CfgBlinky;

//  Clock 
typedef enum {
  MDR_LCD_CLK_LSE = LCD_CR_CLK_LSE,
  MDR_LCD_CLK_LSI = LCD_CR_CLK_LSI
} MDR_LCD_SelCLK;

//  Frame DIV
//  Минимальное значение делителя, при котором у меня заработал вывод в статическом режиме.
#define MDR_LCD_DIV_MIN       3


//  ===================== Инициализация экрана ======================
typedef struct {
  //  Основные настройки
  MDR_OnOff       useExternalPower;
  MDR_LCD_SelCLK  clockSource;
  uint16_t        frameDIV;       //  >= MDR_LCD_DIV_MIN  
  uint16_t        reserved;       // for padding warning clear
  //  Настройки опции мигания дисплея, если NULL - мигание выключено
  MDR_LCD_CfgBlinky  *pBlinkCfg;
  //  Настройки мультиплексирования, если NULL - статический контроль (без мультиплексирования)
  MDR_LCD_CfgMux     *pMuxCfg;
} MDR_LCD_Cfg;


void MDR_LCD_Init(const MDR_LCD_Cfg *pCfg);

void MDR_LCD_DeInit(void);


//  ===================== Вывод информации на экран ======================
typedef struct {
  uint32_t SegmCom0;
  uint32_t SegmCom1;
  uint32_t SegmCom2;
  uint32_t SegmCom3;
} MDR_LCD_SreenData;

void MDR_LCD_ClearRegs(void);
void MDR_LCD_SetScreen(MDR_LCD_SreenData *pData);
void MDR_LCD_SetScreenAlt(MDR_LCD_SreenData *pData);

//  Мигание экраном
void MDR_LCD_BlinkyStart(MDR_LCD_BlinkFreq  blinkFreq, MDR_OnOff blinkToAlterData);
void MDR_LCD_BlinkyStop(void);

#endif // MDR_LCD_VK214_H

