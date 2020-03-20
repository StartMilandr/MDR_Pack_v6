#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_LEDs.h>
#include <MDR_CPU_ClockSelect.h>

#include <MDR_CAN.h>



// !!! ДРАЙВЕР CAN И ПРИМЕР НЕ РАБОЧИЕ, ЕЩЕ НИ РАЗУ НЕ ЗАПУСКАЛСЯ И НЕ ОТЛАЖИВАЛСЯ !!!




#define HSE_PLL_40MHz     MDR_CLK_PLL_HSE_RES_DEF(MDRB_PLL_10MHz_TO_40MHz, MDRB_CPU_FREQ_SUPP_40MHz) 
#define BTN_DEBOUNCE_MS   20

#define LED_CYCLIC      MDRB_LED_1
#define LED_STARTED_TX  MDRB_LED_2
#define LED_STARTED_RX  MDRB_LED_3
#define LED_OK          MDRB_LED_4
#define LED_FAULT       MDRB_LED_5

#define LED_USED_ALL    (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4)

#define CANex_TST   MDR_CAN1ex
#define CAN_TST     MDR_CAN1ex->CANx

//  ----- CAN Buffers -----
//  Распределение буферов
#define COM_RX_BufInd         0
#define DATA1_RX_BufInd       1
#define DATA2_RX_BufInd       2
#define DATA_ANY_RX_BufInd    3
#define RTR1_RX_BufInd        4
#define RTR2_RX_BufInd        5

#define COM_TX_BufInd         6
#define DATA1_TX_BufInd       7
#define DATA2_TX_BufInd       8
#define DATA_ANY_TX_BufInd    9
#define RTR1_TX_BufInd        10
//#define RTRcust_TX_BufInd     11


//  Настройки для буферов передающих-принимающих команды 
// (передаваемые данные рассматриваются как команды для данного примера)
#define COM_RX_MASK           0
#define COM_ID                0
#define COM_DATA_CNT          0
#define COM_FRAME_EXT         false

//  Настройки для буферов передающих-принимающих данные по своему ID
#define DATAx_RX_MASK         0

#define DATA1_ID              0
#define DATA1_CNT             0
#define DATA1_FRAME_EXT       false

#define DATA2_ID              0
#define DATA2_CNT             0
#define DATA2_FRAME_EXT       false

//  Буфер принимает любые данные
#define DATA_ANY_ID_Start     0
#define DATA_ANY_ID_End       0
#define DATA_ANY_CNT          0
#define DATA_ANY_FRAME_EXT    false

//  Буферы c ответом на RTR
#define RTR1_RX_MASK          0
#define RTR1_ID               0
#define RTR1_FRAME_EXT        false
#define RTR1_DATA_CNT         8

#define RTR2_RX_MASK          0
#define RTR2_ID               0
#define RTR2_FRAME_EXT        false
#define RTR2_DATA_CNT         8


//  Указатели на аппаратные буферы
static MDR_CAN_BufType *bufComRX;
static MDR_CAN_BufType *bufDataRX1;
static MDR_CAN_BufType *bufDataRX2;
static MDR_CAN_BufType *bufDataAnyRX;
static MDR_CAN_BufType *bufDataRX_RTR1;
static MDR_CAN_BufType *bufDataRX_RTR2;

static MDR_CAN_BufType *bufComTX;
static MDR_CAN_BufType *bufDataTX1;
static MDR_CAN_BufType *bufDataTX2;
static MDR_CAN_BufType *bufDataAnyTX;
static MDR_CAN_BufType *bufDataTX_RTR1;
//static MDR_CAN_BufType *bufDataTX_RTRcust;


typedef struct {
  uint32_t    countTX;                  //  Количество байт в посылке, 1 - 8.
  uint8_t     refValue;                 //  В данных передаются индексы, начиная с refValue и далее + 1. refValue обнуляется при посылке команде COM_ID
} TaskStructTX;

//  Принимаемые данные
typedef struct {
  uint8_t     dataRX[MDR_CAN_BYTES_MAX]; //  Принятые данные
  uint32_t    countRX;                   //  Количество принятых данных
  uint8_t     refValue;                  //  data[0] должен начинаться с refValue, далее + 1. refValue обнуляется по приему COM_ID
  uint32_t    errCount;                  //  количество байт не совпавших с refValue и далее +1.
} TaskStructRX;

//  Структуры определяющая данные для приемо-передачи
typedef struct {
  TaskStructTX  TX;
  TaskStructRX  RX;
} TaskStruct;

#define TASK_INIT(cnt)     {.TX.countTX = cnt,  \
                            .TX.refValue = 0,   \
                            .RX.countRX  = 0,   \
                            .RX.refValue = 0,   \
                            .RX.errCount = 0    \
                            };                  \
                            
TaskStruct TaskData1   = TASK_INIT(DATA1_CNT);
TaskStruct TaskData2   = TASK_INIT(DATA2_CNT);
TaskStruct TaskDataAny = TASK_INIT(DATA_ANY_CNT);
TaskStruct TaskRTR1    = TASK_INIT(RTR1_DATA_CNT);
TaskStruct TaskRTR2    = TASK_INIT(RTR2_DATA_CNT);

#define SEL_TASK_DATA1       1UL
#define SEL_TASK_DATA2       2UL
#define SEL_TASK_DATA_ANY    4UL
#define SEL_TASK_RTR1        8UL
#define SEL_TASK_RTR2       10UL

//  Select Start TX by Up button
#define KEY1_TASKS_SEL   SEL_TASK_DATA1
//  Select Start TX by Up button
#define KEY2_TASKS_SEL   SEL_TASK_DATA_ANY
//  Select Start TX by Up button                            
#define KEY3_TASKS_SEL   (SEL_TASK_DATA1 | SEL_TASK_DATA2 | SEL_TASK_DATA_ANY)
                            
uint32_t ActiveTasksTX = 0;
uint32_t ActiveTasksRX = 0;
uint32_t DoStartTastRX_Select = 0;
uint32_t DoStartTastTX_Select = 0;
                            
//  Передаваемые данные
#define  TRANSF_DATA_COUNT    255
                            
//  Заполнение данных задачи для отправки, 
//  Возвращает TRUE если передано всё количество данных - TRANSF_DATA_COUNT
bool TaskTX_FillData(TaskStructTX  *TX, MDR_CAN_Data *bufData);
//  Подсчет ошибок в принятых данных
//  Возвращает TRUE если принято всё количество данных - TRANSF_DATA_COUNT
bool TaskRX_CheckData(TaskStructRX  *RX, MDR_CAN_Data *bufData);

void CAN1_IRQHandler(void);

                            
int main(void)
{ 
  //uint8_t dataCnt;
  MDR_CAN_Data bufData;
  uint32_t TX_ID_Any = DATA_ANY_ID_Start;
  
  //  CPU_Clock 40MHz
  MDR_CLK_Enable_RST_BPK();
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = HSE_PLL_40MHz; 
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);  

  //  Инициализация кнопок и светодиодов
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  MDRB_LED_Init(LED_USED_ALL);
  
  //----------    Настройка CAN -------------
  //  Set CAN_Clock 40MHz
  MDR_CANex_SetCANClock(CANex_TST, MDR_Div128P_div1);
  
  //  CAN_SampleRate 1MHz
  MDR_CAN_TimingCfg canTimeCfg = {
      .Delay_PSEG = MDR_CAN_BITTMNG_2TQ,
      .Delay_SEG1 = MDR_CAN_BITTMNG_4TQ,
      .Delay_SEG2 = MDR_CAN_BITTMNG_3TQ,          // SEG2 <= PSEG + SEG1 !
      .SyncJumpWidth = MDR_CAN_BITTMNG_SJW_2TQ,   // SJW < SEG2 !
      .BaudRatePresc = 3,                         // BRP = [CAN_Clock_Hz / ((1 + PSEG + SEG1 + SEG2) * SampleRate_Hz)] - 1 = 40M/(10*1M) - 1
      .TrimpleSampling = MDR_On    
  };
    
  //  Init CAN with Clock
  MDR_CAN_InitDef(CAN_TST, &canTimeCfg);    
  
  //----------    Настройка Буферов CAN -------------
  //  Command TX->RX buffers
  MDR_CAN_BuffCfgTX cfgTX = {
    .dataCount  = COM_DATA_CNT,
    .isExtended = COM_FRAME_EXT,
    .lowPrioity = false
  };
  bufComTX = MDR_CAN_BuffInitTX(CAN_TST, COM_TX_BufInd, COM_ID, &cfgTX);  
  bufComRX = MDR_CAN_BuffInitRX(CAN_TST, COM_RX_BufInd, false, COM_RX_MASK, COM_ID);
  
  //  DATA1 TX->RX buffers
  cfgTX.dataCount  = DATA1_CNT;
  cfgTX.isExtended = DATA1_FRAME_EXT;
  bufDataTX1 = MDR_CAN_BuffInitTX(CAN_TST, DATA1_TX_BufInd, DATA1_ID, &cfgTX);  
  bufDataRX1 = MDR_CAN_BuffInitRX(CAN_TST, DATA1_RX_BufInd, true, DATAx_RX_MASK, DATA1_ID);
  
  //  DATA2 TX->RX buffers
  cfgTX.dataCount  = DATA1_CNT;
  cfgTX.isExtended = DATA1_FRAME_EXT;
  bufDataTX2 = MDR_CAN_BuffInitTX(CAN_TST, DATA2_TX_BufInd, DATA2_ID, &cfgTX);  
  bufDataRX2 = MDR_CAN_BuffInitRX(CAN_TST, DATA2_RX_BufInd, true, DATAx_RX_MASK, DATA2_ID);
    
  //  DATA_ANY TX->RX buffers
  cfgTX.dataCount  = DATA_ANY_CNT;
  cfgTX.isExtended = DATA_ANY_FRAME_EXT;
  bufDataAnyTX = MDR_CAN_BuffInitTX      (CAN_TST, DATA_ANY_TX_BufInd, DATA_ANY_ID_Start, &cfgTX);       
  bufDataAnyRX = MDR_CAN_BuffInitRX_AnyID(CAN_TST, DATA_ANY_RX_BufInd, true);

  //  RTR1_RX Answer buffer
  MDR_CAN_BuffCfgRTR cfgRTR = {
    .ID         = RTR1_ID,
    .filterMask = RTR1_RX_MASK,
    .answerCfg.dataCount  = RTR1_DATA_CNT,
    .answerCfg.isExtended = RTR1_FRAME_EXT,
    .answerCfg.lowPrioity = false
  };  
  bufDataRX_RTR1 = MDR_CAN_BuffInit_AnswerRTR(CAN_TST, RTR1_RX_BufInd, &cfgRTR, &bufData); 
  bufDataTX_RTR1 = MDR_CAN_BuffInit_RequestRTR(CAN_TST, RTR1_TX_BufInd, RTR1_ID, cfgRTR.answerCfg.isExtended, true);
  
  //  RTR1_RX Answer buffer
  cfgRTR.answerCfg.dataCount  = RTR2_DATA_CNT;
  cfgRTR.answerCfg.isExtended = RTR2_FRAME_EXT;
  bufDataRX_RTR2 = MDR_CAN_BuffInit_AnswerRTR(CAN_TST, RTR2_RX_BufInd, &cfgRTR, &bufData);

  //  RTR for send any request
//  bufDataTX_RTRcust = MDR_CAN_BuffInitTX_RTR_Custom(CAN_TST, RTRcust_TX_BufInd);
  
  while (1)
  {
    //  Task to Send
    if (ActiveTasksTX != 0)
    {
      if (ActiveTasksTX & SEL_TASK_DATA1)
      {
        if (TaskTX_FillData(&TaskData1.TX, &bufData))
          ActiveTasksTX &= ~SEL_TASK_DATA1;
        MDR_CAN_BuffSendEx(bufDataTX1, &bufData);
      }
      if (ActiveTasksTX & SEL_TASK_DATA2)
      {
        if (TaskTX_FillData(&TaskData2.TX, &bufData))
          ActiveTasksTX &= ~SEL_TASK_DATA2;
        MDR_CAN_BuffSendEx(bufDataTX2, &bufData);
      }
      //  Посылка с разными ID
      if (ActiveTasksTX & SEL_TASK_DATA_ANY)
      {
        if (TaskTX_FillData(&TaskDataAny.TX, &bufData))
          ActiveTasksTX &= ~SEL_TASK_DATA_ANY;
        MDR_CAN_BuffSendEx_ID(bufDataAnyTX, &bufData, TX_ID_Any);
        if (TX_ID_Any == DATA_ANY_ID_End)
          TX_ID_Any = DATA_ANY_ID_Start;
      }
      
      if (ActiveTasksTX == 0)
        MDRB_LED_Set(LED_STARTED_TX, false);
    }
    
    //  Task to Check Read data
    if (ActiveTasksRX != 0)
    {
      if (ActiveTasksRX & SEL_TASK_DATA1)
      {
        if (TaskRX_CheckData(&TaskData1.RX, &bufData))
          ActiveTasksRX &= ~SEL_TASK_DATA1;
      }
      if (ActiveTasksRX & SEL_TASK_DATA2)
      {
        if (TaskRX_CheckData(&TaskData2.RX, &bufData))
          ActiveTasksRX &= ~SEL_TASK_DATA2;
      }
      if (ActiveTasksRX & SEL_TASK_DATA_ANY)
      {
        if (TaskRX_CheckData(&TaskDataAny.RX, &bufData))
          ActiveTasksRX &= ~SEL_TASK_DATA_ANY;
      }
      
      if (ActiveTasksRX == 0)
      {
        MDRB_LED_Set(LED_STARTED_RX, false);
        
        uint32_t errCnt = TaskData1.RX.errCount + TaskData2.RX.errCount + 
          TaskDataAny.RX.errCount + TaskRTR1.RX.errCount + TaskRTR2.RX.errCount;
        if (errCnt != 0)
          MDRB_LED_Set(LED_FAULT, true);
        else
          MDRB_LED_Set(LED_OK, true);
      }
    }
    
    //  Read Tasks Start
    if (DoStartTastRX_Select != 0)
    {
      MDRB_LED_Set(LED_FAULT | LED_OK, false);
      MDRB_LED_Set(LED_STARTED_RX, true);
      ActiveTasksRX = DoStartTastRX_Select;
      DoStartTastRX_Select = 0;
    }
    
    //  Send Tasks Start
    if (MDRB_BntClicked_Up(true))
      DoStartTastTX_Select = KEY1_TASKS_SEL;
    if (MDRB_BntClicked_Right(true))
      DoStartTastTX_Select = KEY2_TASKS_SEL;
    if (MDRB_BntClicked_Down(true))
      DoStartTastTX_Select = KEY2_TASKS_SEL;
    
    if (DoStartTastTX_Select != 0)
    {
      MDRB_LED_Set(LED_STARTED_TX, true);
      
      MDR_CAN_BuffSend(bufComTX, ActiveTasksTX, 0);
      
      ActiveTasksTX = DoStartTastTX_Select;
      DoStartTastTX_Select = 0;
    }
    
  }
}

bool TaskTX_FillData(TaskStructTX  *TX, MDR_CAN_Data *bufData)
{
  uint32_t i;
  uint8_t *pBytesTX = (uint8_t *)bufData;
  uint32_t cnt = TRANSF_DATA_COUNT - TX->refValue;
  
  bool completed = (cnt <= TX->countTX);
  if (!completed)
    cnt = TX->countTX;
  
  for (i = 0; i < cnt; ++i)
    pBytesTX[i] = TX->refValue++;
  
  return completed;
}

bool TaskRX_CheckData(TaskStructRX  *RX, MDR_CAN_Data *bufData)
{
  uint32_t i;
  uint8_t *pBytesRX = (uint8_t *)bufData;
   
  for (i = 0; i < RX->countRX; ++i)
  {
    if (pBytesRX[i] != RX->refValue)
      RX->errCount++;
    RX->refValue++;
  }
  
  return RX->refValue >= TRANSF_DATA_COUNT;
}

void CAN1_IRQHandler(void)
{
  
}

  