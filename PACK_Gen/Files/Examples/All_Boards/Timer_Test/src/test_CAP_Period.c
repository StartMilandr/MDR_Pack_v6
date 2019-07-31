#include <MDR_Timer.h>
#include <MDRB_LCD.h>
#include <MDRB_UART_Debug.h>

#include <math.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"


//  ОПИСАНИЕ:
//    Timer1 генерирует импульсы на выходе CH1 и мигает светодиодом LED1 каждый период.
//    Timer3 захватывает события переднего и заднего фронтов сигнала от Timer1_CH1.
//    В прерывании по спаду, эти значения сохраняются в массивы до накопления AVER_COUNT измерений.
//    После этого прерывания по захвату отключаются, высчитываются средний период и длительность импульса,
//    результаты выводятся на LCD панель.
//    При нажатии на кнопку DOWN повторяется цикл измерений AVER_COUNT с выводом результатов.
//    При нажатии на кнопку RIGHT уменьшается период ШИМ, и повторяется цикл измерений.
//    При периоде ШИМ порядка 172 периодов TIM_CLOCK начинает не хватает быстродействия на исполнение обработчика прерывания.
//    При считывании значений фронтов, данные переднего фронта обгоняют данные от заднего. Алгоритм выдает неправильные данные - RMS растет, а период увеличивается вместо уменьшения.
//    Для захвата значений на высоких частота необходимо использовать DMA!
//
//    В 1986ВК214 сбой начинается с периодом ШИМ в 248 тактов, результат выводится в UART_Debug.
//    В 1986ВК234 сбой начинается с периодом ШИМ в 272 тактов.
//    Для наблюдения необходимо подключить переходник от UART через USB к РС.
//    Лог получать в программах типа, Terminal или Putty.


//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Change(void);
static void  Test_Exec(void);
static void  Test_MainLoop(void);
static void  Test_HandleTimIRQ_CAP(void);

extern TestInterface TI_CAP_Period;

TestInterface TI_CAP_Period = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Change,
  .funcExec       = Test_Exec,
  .funcMainLoop   = Test_MainLoop,  
  .funcHandlerTim1 = Test_HandleTimIRQ_CAP,
  .funcHandlerTim2 = Test_HandleTimIRQ_CAP,
  .funcHandlerTim3 = Test_HandleTimIRQ_CAP,
  .funcHandlerTim4 = Test_HandleTimIRQ_CAP,
};

#define   TIM_BRG       MDR_Div128P_div1
#define   TIM_PSC       0

#define  AVER_COUNT    50
static uint32_t averInd;
static uint_tim valRE[AVER_COUNT + 1], valFE[AVER_COUNT + 1];  //  RiseEdge and FallEdge
static uint32_t periods[AVER_COUNT], widthes[AVER_COUNT];

static bool doProcessResult = false;

void CalcAndShowResult(void);

//  Конфигурация аналогична test_CAP_Simlpest, где вместо структуры задается NULL
static const MDR_TimerCh_CfgCAP cfgCAP = {
  .Filter   = MDR_TIM_FLTR_TIM_CLK, 
  .EventPSC = MDR_Div8P_div1,
  .EventCAP = MDR_TIM_CAP_RiseOnPin,
  .enableCAP1 = true,
  .EventCAP1  = MDR_TIM_CAP1_FallOnPin
};

#if defined (USE_MDR1986VK214) 
  #define OUT_TO_UART
  static uint_tim  pulsePeriod = 250;

#elif defined (USE_MDR1986VK234)
  #define OUT_TO_UART
  static uint_tim  pulsePeriod = 290;

#elif defined (USE_MDR1986VE91)
  #define OUT_TO_LCD
  static uint_tim  pulsePeriod = 200;

#elif defined (USE_MDR1986VE93)
  #define OUT_TO_UART
  static uint_tim  pulsePeriod = 200;

#elif defined (USE_MDR1986VE1) || defined (USE_MDR1986VE3)
  #define OUT_TO_LCD
  static uint_tim  pulsePeriod = 300;

#elif defined (USE_MDR1986VE4)
  #define OUT_TO_UART
  static uint_tim  pulsePeriod = 280;

#else
  #define OUT_TO_LCD
  static uint_tim  pulsePeriod = 200;
#endif

#define CAP_IRQ_byFALL       CAP_EVENT_FALL


//#if !(defined(LCD_CONFLICT_TIM) || defined(LCD_IS_7SEG_DISPLAY))
#if !defined(LCD_IS_7SEG_DISPLAY)
static void LCD_ShowName(uint32_t period)
{
  static char message[64];
  sprintf(message , "CAP Per=%d", period);
  MDRB_LCD_Print (message, 3);  
}
#endif


static void Test_Init(void)
{   
  //  To LCD
#ifndef LCD_IS_7SEG_DISPLAY
  LCD_ShowName(pulsePeriod);
  MDRB_LCD_ClearLine(5);
  MDRB_LCD_ClearLine(7);
  
#elif defined (LCD_CONFLICT_TIM)
  MDRB_LCD_Print(TEST_ID__CAP_PERIOD);
  
  #ifdef LCD_BLINKY_ENA  
    MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
    MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));
    MDR_LCD_DeInit();
  #endif  
  
#else
  MDRB_LCD_Print(TEST_ID__CAP_PERIOD);
#endif  

#ifdef OUT_TO_UART
  MDR_UART_DBG_Init();
#endif
  
  //  PWM - Output pulses for Capture
  MDR_Timer_InitPeriod(PWM1_TIMex, TIM_BRG, TIM_PSC, pulsePeriod, false);
  MDR_TimerPulse_InitPulse(PWM1_TIM_CH, pulsePeriod, 50);  
  MDR_TimerCh_InitPinGPIO(&PWM1_PIN_CH,  MDR_PIN_FAST);
     
  //  Timer2_CH1 - Capture Rise and Fall fronts from Timer1_CH1
  MDR_Timer_InitPeriodDirIRQ(CAP_TIMex, TIM_BRG, TIM_PSC, TIM_MAX_VALUE, CAP_IRQ_byFALL, TIM_CountUp);
  MDR_TimerCh_InitCAP(CAP_TIM_CH, &cfgCAP);  
  MDR_TimerCh_InitPinGPIO(&CAP_PIN_CH, MDR_PIN_FAST); 
 
  // Start
  averInd = 0;
  
#ifndef SYNC_START_UNAVALABLE  
  MDR_Timer_StartSync(PWM1_START_SEL_MSK | CAP_START_SEL_MSK);
#else
  MDR_Timer_Start(CAP_TIMex);
  MDR_Timer_Start(PWM1_TIMex);
#endif  
}  

static void Test_Finit(void)
{
  //  Stop
#ifndef SYNC_START_UNAVALABLE  
  MDR_Timer_StopSync(PWM1_START_SEL_MSK | CAP_START_SEL_MSK);
#else
  MDR_Timer_Stop(PWM1_TIMex);
  MDR_Timer_Stop(CAP_TIMex);  
#endif    
  
  //  Pins to third state
  MDR_TimerCh_DeInitPinGPIO(&PWM1_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&CAP_PIN_CH);

 //  Finit Timers
  MDR_Timer_DeInit(CAP_TIMex);
  MDR_Timer_DeInit(PWM1_TIMex);
    
#ifdef OUT_TO_UART
  MDR_UART_DBG_Finit();
#endif  
  
#ifdef LCD_CONFLICT_TIM   
  // Restore LCD  
  MDRB_LCD_Init(MDR_CPU_GetFreqHz(false));
  
#elif !defined(LCD_IS_7SEG_DISPLAY)
  MDRB_LCD_ClearLine(5);
  MDRB_LCD_ClearLine(7);  
#endif
}

static void Test_Change(void)
{ 
  if (pulsePeriod > 2)
    --pulsePeriod;
  MDR_TimerPulse_ChangePeriod(PWM1_TIM, pulsePeriod, PWM1_TIM_CH, 50);
  
#ifdef OUT_TO_LCD  
  LCD_ShowName(pulsePeriod); 
#endif
  
  Test_Exec();
}

static void Test_Exec(void)
{  
#ifdef OUT_TO_LCD
  MDRB_LCD_ClearLine(5);
  MDRB_LCD_ClearLine(7);
#endif
  
  // Restart Measure
  averInd = 0;
  MDR_Timer_EnableEventIQR(CAP_TIM, CAP_IRQ_byFALL);
}


static void Test_HandleTimIRQ_CAP(void)
{
  //  Irq by Fall front
  if (MDR_Timer_GetStatus(CAP_TIM) & CAP_IRQ_byFALL)
  {
    valRE[averInd] = MDR_TimerCh_GetCCR(CAP_TIM_CH);
    valFE[averInd] = MDR_TimerCh_GetCCR1(CAP_TIM_CH);
    
    ++averInd;
    if (averInd > AVER_COUNT + 1)
    {
      MDR_Timer_DisableEventIQR(CAP_TIM, CAP_IRQ_byFALL);   //  StopMeasure
      doProcessResult = true;
    }
        
    MDR_Timer_ClearEvent(CAP_TIM, CAP_IRQ_byFALL);
  }
  
  NVIC_ClearPendingIRQ(CAP_TIMex->TIMERx_IRQn);
}

static void Test_MainLoop(void)
{
  if (doProcessResult)
  {
    CalcAndShowResult();
    doProcessResult = false;
  }
}

static uint32_t calcRMS(uint32_t *pData, uint32_t count, uint32_t *pAver)
{
  uint32_t i;
  double sum = 0;
  double aver = 0;
  int32_t disp;
  
  //  Calc Aver
  for (i = 0; i < count; ++i)
    sum += pData[i];
  aver = sum / count;
  *pAver = (uint32_t)aver;
  
  //  RMS
  sum = 0;
  for (i = 0; i < count; ++i)
  {
    disp = (int32_t)pData[i] - (int32_t)aver;
    sum += (disp * disp);
  }
  sum = sum / count;
  sum = sqrt(sum); 
  
  return (uint32_t)sum;
}

void CalcAndShowResult(void)
{
  uint32_t i;
  uint32_t RMS, aver;

  //  Pass first value - no valid after restart by Test_Exec
  uint_tim *DataRE = valRE + 1;
  uint_tim *DataFE = valFE + 1;  
  
  while (averInd <= AVER_COUNT + 1) {};
  
  for (i = 0; i < AVER_COUNT-1; ++i)
  {
    if (DataRE[i + 1] > DataRE[i])
      periods[i] = DataRE[i + 1] - DataRE[i];
    else
      periods[i] = (TIM_MAX_VALUE - DataRE[i]) + DataRE[i + 1];

    if (DataFE[i] > DataRE[i])
      widthes[i] = DataFE[i] - DataRE[i];
    else
      widthes[i] = (TIM_MAX_VALUE - DataRE[i]) + DataFE[i];
  }

#ifdef OUT_TO_LCD
  static char message[64];  
  //  Period
  RMS = calcRMS(periods, AVER_COUNT-2, &aver);
  sprintf(message , "Per=%d  RMS=%d", aver, RMS);
  MDRB_LCD_Print (message, 5);
  //  Width
  RMS = calcRMS(widthes, AVER_COUNT-2, &aver);
  sprintf(message , "Wid=%d  RMS=%d", aver, RMS);
  MDRB_LCD_Print (message, 7);
  
#elif defined (OUT_TO_UART)
  printf("PWM=%d\n", pulsePeriod); 
  //  Period
  RMS = calcRMS(periods, AVER_COUNT-2, &aver);
  printf("Per=%d  RMS=%d\n", aver, RMS);
  //  Width
  RMS = calcRMS(widthes, AVER_COUNT-2, &aver);
  printf("Wid=%d  RMS=%d\n", aver, RMS);
  
#endif
}


