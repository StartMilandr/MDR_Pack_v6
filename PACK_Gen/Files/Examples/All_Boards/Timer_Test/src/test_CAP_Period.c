#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include <math.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"


//  ОПИСАНИЕ:
//    Timer1 генерирует импульсы на выходе CH1 и мигает светодиодом LED1 каждый период.
//    Timer3 захватывает события переднего и заднего фронтов сигнала от Timer1_CH1.
//    В прерывании по спаду, эти значения сохраняются в массивы до накопления AVER_COUNT измерений.
//    После этого прерывания по захвату отключаются, высчитываются средний период и длительность импульса,
//    результаты выводятся на LCD панель.
//    При нажатии на кнопку Down повторяется цикл измерений AVER_COUNT с выводом результатов.
//    При нажатии на кнопку Right уменьшается период ШИМ, и повторяется цикл измерений.
//    При периоде ШИМ порядка 172 периодов TIM_CLOCK начинает не хватает быстродействия на исполнение обработчика прерывания.
//    При считывании значений фронтов, данные переднего фронта обгоняют данные от заднего. Алгоритм выдает неправильные данные - RMS растет, а период увеличивается вместо уменьшения.
//    Для захвата значений на высоких частота необходимо использовать DMA!


//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Change(void);
static void  Test_Exec(void);
static void  Test_MainLoop(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTimIRQ_CAP(void);


TestInterface TI_CAP_Period = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Change,
  .funcExec       = Test_Exec,
  .funcMainLoop   = Test_MainLoop,
  .funcHandlerTim1 = Test_HandleTim1IRQ,
  .funcHandlerTim2 = Test_HandleTimIRQ_CAP,
  .funcHandlerTim3 = Test_HandleTimIRQ_CAP,
  .funcHandlerTim4 = Test_HandleTimIRQ_CAP,
};

#define TIM_BRG       MDR_BRG_div1
#define TIM_PSC       0
uint_tim  pulsePeriod = 200;

#define  AVER_COUNT    50
uint32_t averInd;
uint_tim valRE[AVER_COUNT + 1],   valFE[AVER_COUNT + 1];  //  RiseEdge and FallEdge
uint32_t periods[AVER_COUNT], widthes[AVER_COUNT];


//  Конфигурация аналогична test_CAP_Simlpest, где вместо структуры задается NULL
static const MDR_TimerCH_CfgCAP cfgCAP = {
  .Filter   = MDR_TIM_FLTR_TIM_CLK, 
  .EventPSC = MDR_PSC_div1,
  .EventCAP = MDR_TIM_CAP_RiseOnPin,
  .enableCAP1 = true,
  .EventCAP1  = MDR_TIM_CAP1_FallOnPin
};

#define CAP_TIMERex       MDR_TIMER3ex
#define CAP_TIMER         MDR_TIMER3
#define CAP_TIMER_CH      MDR_TIMER3_CH2
#define CAP_PIN_CH        _pinTim3_CH2
#define CAP_TIMER_START   TIM3_StartMsk
#define CAP_TIMER_EVENT   TIM_FL_CCR1_CAP_CH2

void WaitAndShowResult(void);

static void LCD_ShowName(uint32_t period)
{
  static char message[64];
  sprintf(message , "CAP Per=%d", period);
  MDRB_LCD_Print (message, 3);  
}

static void Test_Init(void)
{  
  LCD_ShowName(pulsePeriod);
  
  MDRB_LCD_ClearLine(5);
  MDRB_LCD_ClearLine(7);
     
  //  Timer1_CH1 - Pulse output for Capture
  MDR_Timer_InitPeriod(MDR_TIMER1ex, TIM_BRG, TIM_PSC, pulsePeriod, false);
  MDR_TimerPulse_InitPulse(MDR_TIMER1_CH1, pulsePeriod, 50);
  
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH1,  MDR_PIN_FAST);
     
  //  Timer2_CH1 - Capture Rise and Fall fronts from Timer1_CH1
  MDR_Timer_InitPeriodDirIRQ(CAP_TIMERex, TIM_BRG, TIM_PSC, TIM_MAX_VALUE, CAP_TIMER_EVENT, TIM_CountUp);
  MDR_TimerCh_InitCAP(CAP_TIMER_CH, &cfgCAP);
  
  MDR_TimerCh_InitPinGPIO(&CAP_PIN_CH, MDR_PIN_FAST);
    
  // Sync Start
  averInd = 0;
  MDR_Timer_StartSync(TIM1_StartMsk | CAP_TIMER_START);
  //  Show Result
  WaitAndShowResult();
}  

static void Test_Finit(void)
{
  MDRB_LCD_ClearLine(5);
  MDRB_LCD_ClearLine(7);
  
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH1);
  MDR_TimerCh_DeInitPinGPIO(&CAP_PIN_CH);

  MDR_Timer_StopSync(TIM1_StartMsk | CAP_TIMER_START);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(CAP_TIMERex);
  
  LED_Uninitialize();  
}

static void Test_Change(void)
{ 
  if (pulsePeriod > 2)
    --pulsePeriod;
  MDR_TimerPulse_ChangePeriod(MDR_TIMER1, pulsePeriod, MDR_TIMER1_CH1, 50);
  LCD_ShowName(pulsePeriod);
  
  Test_Exec();
}

static void Test_Exec(void)
{  
  MDRB_LCD_ClearLine(5);
  MDRB_LCD_ClearLine(7);
  // Restart Measure
  averInd = 0;
  MDR_Timer_EnableEventIQR(CAP_TIMER, CAP_TIMER_EVENT);
  
  WaitAndShowResult();
}

static void  Test_MainLoop(void)
{
}


static void Test_HandleTim1IRQ(void)
{
}

static void Test_HandleTimIRQ_CAP(void)
{
  //  Irq by Fall front
  if (MDR_Timer_GetStatus(CAP_TIMER) & CAP_TIMER_EVENT)
  {
    valRE[averInd] = MDR_TimerCh_GetCCR(CAP_TIMER_CH);
    valFE[averInd] = MDR_TimerCh_GetCCR1(CAP_TIMER_CH);
    
    ++averInd;
    if (averInd > AVER_COUNT + 1)
      MDR_Timer_DisableEventIQR(CAP_TIMER, CAP_TIMER_EVENT);   //  StopMeasure
        
    MDR_Timer_ClearEvent(CAP_TIMER, CAP_TIMER_EVENT);
  }
  
  NVIC_ClearPendingIRQ(CAP_TIMERex->TIMERx_IRQn);
}

static uint32_t calcRMS(uint32_t *pData, uint32_t count, uint32_t *pAver)
{
  uint32_t i;
  uint32_t sum = 0;
  uint32_t aver = 0;
  int32_t disp;
  
  //  Calc Aver
  for (i = 0; i < count; ++i)
    sum += pData[i];
  aver = sum / count;
  *pAver = aver;
  
  //  RMS
  sum = 0;
  for (i = 0; i < count; ++i)
  {
    disp = pData[i] - aver;
    sum += disp * disp;
  }
  sum = sum / count;
  sum = sqrt(sum); 
  
  return sum;
}

void WaitAndShowResult(void)
{
  uint32_t i;
  uint32_t RMS, aver;
  static char message[64];  
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
  
  //  Period
  RMS = calcRMS(periods, AVER_COUNT-2, &aver);
  sprintf(message , "Per=%d  RMS=%d", aver, RMS);
  MDRB_LCD_Print (message, 5);
  //  Width
  RMS = calcRMS(widthes, AVER_COUNT-2, &aver);
  sprintf(message , "Wid=%d  RMS=%d", aver, RMS);
  MDRB_LCD_Print (message, 7);
}


