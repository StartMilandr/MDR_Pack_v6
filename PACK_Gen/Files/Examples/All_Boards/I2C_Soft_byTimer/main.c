#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_LEDs.h>
#include <MDR_Timer.h>
#include <MDR_SoftI2C_byTimer.h>

#define BTN_DEBOUNCE_MS 10

#define I2C_MASTER_BY_PWM    0

// MASTER: Timer and pins select
#define I2C_TIMER_M     MDR_TIMER1ex
#define I2C_TIMER_M_CH  MDR_TIMER1_CH1

#if I2C_MASTER_BY_PWM
  static const MDR_I2C_CfgPinGPIO  mstCLK_pinTimCH = {MDR_GPIO_E,  3, MDR_PIN_MAIN};
  static const MDR_I2C_CfgPinGPIO  mstSDA_pinPort  = {MDR_GPIO_E,  4, MDR_PIN_PORT};  
  #define I2C_TO_TIM_HZ  2
#else
  static const MDR_I2C_CfgPinGPIO  mstCLK_pinTimCH = {MDR_GPIO_E,  3, MDR_PIN_PORT};
  static const MDR_I2C_CfgPinGPIO  mstSDA_pinPort  = {MDR_GPIO_E,  4, MDR_PIN_PORT};  
  #define I2C_TO_TIM_HZ  4
#endif

static const MDR_I2C_CfgPinsGPIO pinsGPIO_I2C_M = {
    .pPinSCL = &mstCLK_pinTimCH,
    .pPinSDA = &mstSDA_pinPort,
};  


// SLAVE: Timer and pins select
#define I2C_TIMER_S         MDR_TIMER2ex
#define I2C_TIMER_S_CH_CLK  MDR_TIMER2_CH1
#define I2C_TIMER_S_CH_SDA  MDR_TIMER2_CH3
static const MDR_I2C_CfgPinGPIO  slvCLK_pinTim2CH1  = {MDR_GPIO_E,  7, MDR_PIN_MAIN};
static const MDR_I2C_CfgPinGPIO  slvSDA_pinTim2CH3  = {MDR_GPIO_E,  9, MDR_PIN_MAIN};

static const MDR_I2C_CfgPinsGPIO pinsGPIO_I2C_S = {
    .pPinSCL = &slvCLK_pinTim2CH1,
    .pPinSDA = &slvSDA_pinTim2CH3,
};  

#define I2C_CLK_RISE_FL_CCR   TIM_FL_CCR_CAP_CH1
#define I2C_CLK_FALL_FL_CCR1  TIM_FL_CCR1_CAP_CH1
#define I2C_SDA_RISE_FL_CCR   TIM_FL_CCR_CAP_CH3
#define I2C_SDA_FALL_FL_CCR1  TIM_FL_CCR1_CAP_CH3


// LEDs
#define LED_TIM_OK        MDRB_LED_1
#define LED_TIM_STARTED   MDRB_LED_2
#define LED_TIM_FAULT     MDRB_LED_3
#define LED_TIM_ALL      (LED_TIM_OK | LED_TIM_STARTED | LED_TIM_FAULT)

//  I2C
#define I2C_ADDR      0x55
#define I2C_FREQ_HZ   1000
MDR_I2Cst_MasterObj   masterI2C;
MDR_I2Cst_SlaveObj    slaveI2C;

//  Data
#define DATA_LEN 5
uint8_t rdDataMaster[DATA_LEN];
uint8_t wrDataMaster[DATA_LEN];
uint8_t regDataMaster[DATA_LEN];

#define TEST_REG_LEN    2

uint8_t retDataSlave[DATA_LEN];
#define SLAVE_REG_LEN    4
#define SLAVE_REG_ITEMS  5
#define SLAVE_REGS_LEN   (SLAVE_REG_LEN  * SLAVE_REG_ITEMS)
uint8_t retRegsSlave[SLAVE_REGS_LEN];
// Slave "RegAddr" - index of retRegsSlave
#define SLAVE_REG_ADDR   3
uint8_t *SlaveRetRegData;

typedef enum {transfWrite, transfRead, transfWriteReg, transfReadReg} Transf_e;
Transf_e activeTransf;

void PrepareStart(Transf_e transf);
bool SlaveCheckAddr(uint8_t addr_7bit, bool isWriteMode, bool restarted, uintI2C_t  **buff,  uint8_t *buffLen);
void SlaveCompleted(void *obj);
void MasterCheckResult(void);


int main(void)
{
  MDR_DebugerProtectDelay();
  
  uint32_t freqCPU_Hz;
  bool started = false;
 
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация LCD дисплея и кнопок
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  MDRB_LED_Init(LED_TIM_ALL);
  
  
  // ====  Инициализация I2C - Master  ====
  MDR_I2Cs_MasterInitCfg cfgI2C_Mst;
  //  Timer
  cfgI2C_Mst.timerEx = I2C_TIMER_M;
  cfgI2C_Mst.timerCh_PWM = I2C_TIMER_M_CH;
  cfgI2C_Mst.timClockBRG = MDR_Div128P_div1;
  if (!MDR_Timer_CalcPeriodAndPSG_F(I2C_FREQ_HZ * I2C_TO_TIM_HZ, freqCPU_Hz, &cfgI2C_Mst.timPeriod, &cfgI2C_Mst.timClockPSG))
  {
    MDRB_LED_Set(LED_TIM_FAULT, true);
    while (1);
  };
  //  Pins
  cfgI2C_Mst.pinsCfg = &pinsGPIO_I2C_M;
  cfgI2C_Mst.pinsPower = MDR_PIN_FAST;
  cfgI2C_Mst.pullUpPins = true;
  
#if I2C_MASTER_BY_PWM
  masterI2C = MDR_I2Cst_InitMasterPWM(&cfgI2C_Mst);  
#else  
  masterI2C = MDR_I2Cst_InitMasterSoft(&cfgI2C_Mst);
#endif
  
  
  // ====  Инициализация I2C - Slave  ====
  MDR_I2Cs_InitSlaveCfg cfgI2C_Slv;
  //  Timer
  cfgI2C_Slv.timerEx = I2C_TIMER_S;
  //  Timer Capture
  cfgI2C_Slv.timCapCh_CLK.timerCh           = I2C_TIMER_S_CH_CLK;
  cfgI2C_Slv.timCapCh_CLK.selIRQ_CCR_Rise   = I2C_CLK_RISE_FL_CCR;
  cfgI2C_Slv.timCapCh_CLK.selIRQ_CCR1_Fall  = I2C_CLK_FALL_FL_CCR1;
  cfgI2C_Slv.timCapCh_CLK.filter            = MDR_TIM_FLTR_2_TIM_CLK;
  
  cfgI2C_Slv.timCapCh_SDA.timerCh           = I2C_TIMER_S_CH_SDA;
  cfgI2C_Slv.timCapCh_SDA.selIRQ_CCR_Rise   = I2C_SDA_RISE_FL_CCR;
  cfgI2C_Slv.timCapCh_SDA.selIRQ_CCR1_Fall  = I2C_SDA_FALL_FL_CCR1;
  cfgI2C_Slv.timCapCh_SDA.filter            = MDR_TIM_FLTR_2_TIM_CLK;

  //  Timer "SampleRate"
  cfgI2C_Slv.timClockBRG = MDR_Div128P_div1;
  cfgI2C_Slv.timClockPSG = cfgI2C_Mst.timClockPSG;
  //  Pins
  cfgI2C_Slv.pinsCfg = &pinsGPIO_I2C_S;
  cfgI2C_Slv.pinsPower = MDR_PIN_FAST;
  cfgI2C_Slv.pullUpPins = true;
  //  callbasks
  cfgI2C_Slv.OnCheckAddr = SlaveCheckAddr;
  cfgI2C_Slv.OnCompleted = SlaveCompleted;
  
  slaveI2C = MDR_I2Cst_InitSlave(&cfgI2C_Slv);
  MDR_I2Cst_StartSlave(&slaveI2C);
  
  
  while (1)
  {
    if (MDRB_BntClicked_Up(true))
    {
      PrepareStart(transfWrite);
      MDR_I2Cst_MasterStartWrite(&masterI2C, I2C_ADDR, wrDataMaster, DATA_LEN);
      started = true;
    }
    
    if (MDRB_BntClicked_Right(true))
    {
      PrepareStart(transfRead);      
      MDR_I2Cst_MasterStartRead(&masterI2C, I2C_ADDR, rdDataMaster, DATA_LEN);    
      started = true;
    }
    
    if (MDRB_BntClicked_Down(true))
    {
      PrepareStart(transfWriteReg);      
      MDR_I2Cst_MasterStartWrite(&masterI2C, I2C_ADDR, wrDataMaster, TEST_REG_LEN + 1);
      started = true;
    }
    
    if (MDRB_BntClicked_Left(true))
    {
      PrepareStart(transfReadReg);
      MDR_I2Cst_MasterStartReadRegs(&masterI2C, I2C_ADDR, wrDataMaster, 1, regDataMaster, TEST_REG_LEN, true);
      started = true;
    }    
    
    if (started)
      if (!MDR_I2Cst_MasterGetStarted(&masterI2C))
      {
        started = false;
        MasterCheckResult();
      }
  }
}

void TIMER1_IRQHandler(void)
{
#if I2C_MASTER_BY_PWM  
  MDR_I2Cst_MasterHandlerIRQ_PWM(&masterI2C);
#else  
  MDR_I2Cst_MasterHandlerIRQ_Soft(&masterI2C);
#endif  
}

void TIMER2_IRQHandler(void)
{
  MDR_I2Cst_SlaveHandlerIRQ(&slaveI2C);
}

void PrepareStart(Transf_e transf)
{
  activeTransf = transf;
  
  MDRB_LED_Set(LED_TIM_ALL, false);
  MDRB_LED_Set(LED_TIM_STARTED, true);
  
  uint8_t i;
  switch (activeTransf){
    case transfWrite:
    { // wrDataMaster -> retDataSlave
      for (i = 0; i < DATA_LEN; ++i )
      {
        if (i & 1)
          wrDataMaster[i] = 0xCC;
        else
          wrDataMaster[i] = 0x33;
        retDataSlave[i] = 0;
      }
      break;    
    }
    case transfRead:
    { // retDataSlave -> rdDataMaster
      for (i = 0; i < DATA_LEN; ++i )
      {
        if (i & 1)
          retDataSlave[i] = 0x55;
        else
          retDataSlave[i] = 0xAA;
        rdDataMaster[i] = 0;    
      }
      break;  
    }
    case transfWriteReg:
    { //  wrDataMaster[1..x] -> retRegsSlave[SLAVE_REG_ADDR][0..]
      wrDataMaster[0] = SLAVE_REG_ADDR;
      for (i = 1; i < DATA_LEN; ++i )
      {
        if (i & 1)
          wrDataMaster[i] = 0x55;
        else
          wrDataMaster[i] = 0xAA;      
      }
      for (i = 0; i < SLAVE_REGS_LEN; ++i)
        retRegsSlave[i] = 0;    
      break; 
    }
    case transfReadReg:
    { // retRegsSlave[SLAVE_REG_ADDR] -> regDataMaster
      for (i = 0; i < DATA_LEN; ++i )
        regDataMaster[i] = 0; 
      
      wrDataMaster[0] = SLAVE_REG_ADDR;
      break;
    }
  }
}

bool SlaveCheckAddr(uint8_t addr_7bit, bool isWriteMode, bool restarted, uintI2C_t  **buff,  uint8_t *buffLen)
{
  if (!restarted)
  {
    *buff = retDataSlave;
    *buffLen = DATA_LEN;  
  }
  else
  {
    uint8_t ind = retDataSlave[0];
    if (ind < SLAVE_REG_ITEMS)
    {
      *buff = &retRegsSlave[ind * SLAVE_REG_LEN];
      *buffLen = SLAVE_REG_LEN;    
      //  Addr of slave retData to check transfer OK
      SlaveRetRegData = *buff;
    }
    else
    {
      *buff = retDataSlave;
      *buffLen = DATA_LEN;      
    }
  }
 
  bool result = addr_7bit == I2C_ADDR;
  return result;
}

void MasterCheckResult(void)
{
  uint32_t i, errCnt;  
  
  errCnt = 0;
  if (activeTransf == transfRead)
  {
    for (i = 0; i < DATA_LEN; ++i)
      if (rdDataMaster[i] != retDataSlave[i])
        errCnt++;
  }
  else if (activeTransf == transfReadReg)
  {
    for (i = 0; i < masterI2C.dataInd; ++i)
      if (regDataMaster[i] != SlaveRetRegData[i])
        errCnt++;
  }
  else
    return;
  
  if (errCnt > 0)
    MDRB_LED_Set(LED_TIM_FAULT, true);
  else
    MDRB_LED_Set(LED_TIM_OK, true);  
}

bool ChechWriteTransferData(void)
{
  uint32_t i, errCnt;
  
  errCnt = 0;
  for (i = 0; i < DATA_LEN; ++i)
    if (wrDataMaster[i] != retDataSlave[i])
      errCnt++;
  if (errCnt > 0)
    MDRB_LED_Set(LED_TIM_FAULT, true);
  else
    MDRB_LED_Set(LED_TIM_OK, true);      
  
  return errCnt == 0;
}

void SlaveCompleted(void *obj)
{
  uint32_t i;
  
  MDRB_LED_Set(LED_TIM_ALL, false);
  switch (activeTransf){
  case transfWrite:
  {
    ChechWriteTransferData();
    break;
  }
  case transfRead:
  {
    //processed in MasterCheckResult
    break;  
  }
  case transfWriteReg:
  {
    if (ChechWriteTransferData())
    {    
      // Copy master data to "register" buff
      uint8_t regInd = retDataSlave[0];
      if (regInd < SLAVE_REG_ITEMS)
      {
        uint8_t *pRegData = &retRegsSlave[regInd * SLAVE_REG_LEN];
        MDR_I2Cst_SlaveObj *i2cObj = obj;
        for (i = 0; i < i2cObj->dataInd; ++i)
          pRegData[i] = retDataSlave[i + 1];
      }
    }      
    break;
  }
  case transfReadReg:
    //processed in MasterCheckResult
    break;
  }
}

