#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDR_ADCUI_VE4.h>
#include <MDR_SysTimer.h>

#include <MDRB_Buttons.h>
#include <MDRB_LCD.h>
#include <MDRB_UART_Debug.h>
#include <stdio.h>

#define ADCUI_CH          MDR_ADCUI_CH2
#define CLOCK_BY_PLL      1
#define BTN_DEBOUNCE_MS   20

//  Прием команд из РС (ПОКА не используются)
void UART1_IRQHandler(void);

typedef enum {
  COM_1 = 0,
  COM_2 = 1,
  COM_3 = 2,
  //  Not for use
  _COM_CNT
} MDRB_UART_Commands;

static bool doActCommand[_COM_CNT] = {false, false, false};

//  Реальная Функция обработчик прерывания от ADCUI
void ADCUI_CHx_IRQHandler(void);
//  Обработчики из таблицы векторов, вызывает ADCUI_CHx_IRQHandler
void ADCUI_CH1_IRQHandler(void);
void ADCUI_CH2_IRQHandler(void);
void ADCUI_CH3_IRQHandler(void);

//  Buff for datas from ADCUI
#define DATA_BUFF_LEN   100
static int32_t ADCUI_DataBuff[DATA_BUFF_LEN];
static uint32_t buffDataCnt = 0;
//  Last Value ADCUI
static int32_t ADCUI_DataLast = 0;
//  Sent DataCount from ADCUI_DataBuff to UART
static uint32_t sentDataCnt = DATA_BUFF_LEN;

static bool doSendToUART = false;
static bool doShowToLED = false;

#define LCD_UPDATE_PERIOD_MS   500
void SysTick_Handler(void);
void ShowToLCD(uint32_t data);

static MDR_ADCUI_PGA ADCUI_Gain = MDR_ADCUI_PGA_x1;
static const uint32_t GainValues[4] = {1, 4, 2, 16};

static bool isDivMax = false;

int main(void)
{   
  MDR_CLK_Enable_RST_BPK();
  
#if CLOCK_BY_PLL  
  //MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;  MDR_CPU_CFG_PLL_HSE_RES_DEF  
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDR_CPU_CFG_PLL_HSE_DIV2_RES_DEF(MDR_x8, EEPROM_Delay_le36MHz, MDR_LOWRI_le40MHz);
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);  
#else
  MDR_CPU_SetClock_HSE_def(MDR_CLK_Resonator, false);
#endif
  
  //  Инициализация LCD дисплея, кнопок и UART_DEBUG
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  MDRB_LCD_Init(freqCPU_Hz);
  MDR_UART_DBG_InitIrqRT(UART_DEBUG_BAUD_DEF, true);  
  
  //  Разрешение NVIC обрабатывать запросы от ADCUI
  MDR_ADCUI_NVIC_EnableIRQ(ADCUI_CH, 0);
  //  Подача рабочей частоты на ADCUI - HSE
  MDR_ADCUI_SetClock_CPU_C1(MDR_Div256P_div1);
  //  Инициализация ADCUI и запуск
  MDR_ADCUI_InitDefAndStart(MDR_ADCUI_ChanToSelCH(ADCUI_CH), true, true, false);
  
  
  printf("Gain: %d\n", GainValues[ADCUI_Gain]);
  printf("SFF_SFC = 0\n");
  
  //  Update LCD to show ADCUI last Value
  MDR_SysTimerStart_ms(LCD_UPDATE_PERIOD_MS, freqCPU_Hz);
  
  while(1)
  {
    //  ----    Start Measure and printf data ---
    if (MDRB_BntClicked_Up(true))
    {
      //  Start collect data to ADCUI_DataBuff
      buffDataCnt = 0;
      //  Start send ADCUI_DataBuff to UART
      sentDataCnt = 0;
      doSendToUART = true;
    }
   
    //  Send DataBuff To UART
    if (doSendToUART)
    {  
      doSendToUART = sentDataCnt < DATA_BUFF_LEN;
      if (doSendToUART && (sentDataCnt < buffDataCnt))
        printf("%d\n", ADCUI_DataBuff[sentDataCnt++]);
    }
    
    if (doShowToLED)
    {
      ShowToLCD(ADCUI_DataLast);
      doShowToLED = false;
    }
    
    //  ----------  UART Options -------------
    //  Send to Uart active Point
    if (MDRB_BntClicked_Right(true))
    {
      //printf("%d   0x%x\n", ADCUI_DataLast, ADCUI_DataLast);
      printf("%d\n", ADCUI_DataLast);
    }
    
    //  Change Gain
    if (MDRB_BntClicked_Down(true))
    {
      if (ADCUI_Gain == MDR_ADCUI_PGA_x16)
        ADCUI_Gain = MDR_ADCUI_PGA_x1;
      else
        ++ADCUI_Gain;
      MDR_ADCUI_SetGain(ADCUI_CH, ADCUI_Gain);
      
      printf("Gain: %d\n", GainValues[ADCUI_Gain]);
    }
    
    //  Change SampleRate
    if (MDRB_BntClicked_Left(true))
    {
      isDivMax = !isDivMax;
      
      if (isDivMax)
      {
        MDR_ADCUI->CTRL2 |= (MDR_ADCUI_CTRL2_SFC_Msk | MDR_ADCUI_CTRL2_SFF_Msk);
        printf("SFF_SFC = 0x3FF\n");        
      }
      else
      {
        MDR_ADCUI->CTRL2 &= ~(MDR_ADCUI_CTRL2_SFC_Msk | MDR_ADCUI_CTRL2_SFF_Msk);
        printf("SFF_SFC = 0\n");
      }
    }        
    
  }
}

void SysTick_Handler(void)
{
  doShowToLED = true;
}

void ADCUI_CHx_IRQHandler(void)
{
  while (MDR_ADCUI_CanReadData(ADCUI_CH))
    ADCUI_DataLast = MDR_ADCUI_ReadData(ADCUI_CH);
  
  if (buffDataCnt < DATA_BUFF_LEN)
    ADCUI_DataBuff[buffDataCnt++] = ADCUI_DataLast;
}

void UART1_IRQHandler(void)
{
  uint16_t command;
  while (MDR_UART_CanRead(UART_DBG->UARTx))
  {
    command = MDR_UART_ReadData(UART_DBG->UARTx);
    switch (command & 0x00FF) {
    case 'N': { doActCommand[COM_1] = true; break; }
    case 'C': { doActCommand[COM_2] = true; break; }
    case 'E': { doActCommand[COM_3] = true; break; }
    }
    //  Ack
    printf("%c\n", (char)command);
  }  
}

void ADCUI_CH1_IRQHandler(void)
{
  ADCUI_CHx_IRQHandler();
}

void ADCUI_CH2_IRQHandler(void)
{
  ADCUI_CHx_IRQHandler();
}

void ADCUI_CH3_IRQHandler(void)
{
  ADCUI_CHx_IRQHandler();
}

void ShowToLCD(uint32_t data)
{
  char message[20];
  sprintf(message , "%x", data);
  MDRB_LCD_Print(message);
}



