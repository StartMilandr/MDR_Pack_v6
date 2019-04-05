#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_UART_Debug.h>

#include <MDR_I2C.h>
#include <stdio.h>

#define BTN_DEBOUNCE_MS 10
#define I2C_FREQ_HZ     30000

#define DEBUG_MODE_FOR_OSCIL   0

#ifdef USE_MDR1986VK214
  //  MDRB_1986VK214.h
  static const MDR_I2C_CfgPinGPIO _pinSCL_I2C = {MDRB_I2C_SCL_PC14_Port, MDRB_I2C_SCL_PC14_Ind, MDRB_I2C_SCL_PC14_Func};
  static const MDR_I2C_CfgPinGPIO _pinSDA_I2C = {MDRB_I2C_SDA_PC15_Port, MDRB_I2C_SDA_PC15_Ind, MDRB_I2C_SDA_PC15_Func};
  
#elif defined (USE_MDR1986VE92) || defined (USE_MDR1986VE91)
  //  MDRB_1986VE92.h
  static const MDR_I2C_CfgPinGPIO _pinSCL_I2C = {MDRB_I2C_SCL_PC0_Port, MDRB_I2C_SCL_PC0_Ind, MDRB_I2C_SCL_PC0_Func}; //  VE91: XP11_10  VE92: XP26_24
  static const MDR_I2C_CfgPinGPIO _pinSDA_I2C = {MDRB_I2C_SDA_PC1_Port, MDRB_I2C_SDA_PC1_Ind, MDRB_I2C_SDA_PC1_Func}; //  VE91: XP11_11  VE92: XP26_25
  
#elif defined (USE_MDR1901VC1)
  //  MDRB_1986VE92.h
  static const MDR_I2C_CfgPinGPIO _pinSCL_I2C = {MDRB_I2C_SCL_PC14_Port, MDRB_I2C_SCL_PC14_Ind, MDRB_I2C_SCL_PC14_Func};  //XP 33.2:1_28
  static const MDR_I2C_CfgPinGPIO _pinSDA_I2C = {MDRB_I2C_SDA_PC15_Port, MDRB_I2C_SDA_PC15_Ind, MDRB_I2C_SDA_PC15_Func};  //XP 33.2:1_24
#endif

static const MDR_I2C_CfgPinsGPIO pinsGPIO_I2C = {
    .pPinSCL = &_pinSCL_I2C,
    .pPinSDA = &_pinSDA_I2C,
};  
  
// Адрес микросхемы DS1307
#define RTC_I2C_ADDRESS 0x68

// Регистры микросхемы DS1307
#define RTC_REGISTER_SECONDS  0x00
#define RTC_REGISTER_MINUTES  0x01
#define RTC_REGISTER_HOURS    0x02
#define RTC_REGISTER_DAY      0x03
#define RTC_REGISTER_DATE     0x04
#define RTC_REGISTER_MONTH    0x05
#define RTC_REGISTER_YEAR     0x06
#define RTC_REGISTER_CONTROL  0x07


void ReadSensorI2C(void);
void ReadSensorI2C_IRQ(void);

uint8_t seconds;
bool    ready_WriteReg;
bool    ready_ReadReg;

bool I2C_GetStatus(void);
bool I2C_GetResultAndStatus(uint8_t *dataRX);

bool I2C_SetRegister(uint8_t addr, uint8_t regAddr, uint8_t regData);
bool I2C_GetRegister(uint8_t addr, uint8_t regAddr, uint8_t *regData);

bool I2C_IRQ_SetRegisterStart(uint8_t addr, uint8_t regAddr, uint8_t regData);
bool I2C_IRQ_GetRegisterStart(uint8_t addr, uint8_t regAddr);



int main(void)
{
  bool     selMode_IRQ = true;
  uint32_t freqCPU_Hz;
 
  //  Максимальная скорость тактирования
  MDR_CPU_SetClock_HSE_Max(MDR_Off);
  
  //  Инициализация LCD дисплея и кнопок
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  //  Результат на UART
  MDR_UART_DBG_Init();
  
  // Инициализация I2C
  MDR_I2C_InitPinsGPIO(&pinsGPIO_I2C, MDR_PIN_FAST, true);
  MDR_I2C_InitWithIRQ(I2C_FREQ_HZ, freqCPU_Hz, true, 0);
  
  while (1)
  {
    if (MDRB_BntClicked_Up(true))
    {
      //  Обнуление секунд
      if (!selMode_IRQ)
      {
        if (!I2C_SetRegister(RTC_I2C_ADDRESS, RTC_REGISTER_SECONDS, 0x00))
          printf("Key1: WriteReg Fault\n");
        else
          printf("Key1: Seconds Cleared\n");
      }
      else
        if (!I2C_IRQ_SetRegisterStart(RTC_I2C_ADDRESS, RTC_REGISTER_SECONDS, 0x00))
          printf("Key1 IRQ: WriteReg Start Fault\n");
        else
          printf("Key1 IRQ: WriteReg Start OK\n");
      
      //selMode_IRQ = !selMode_IRQ;
    }
    
    //  Чтение секунд 
    if (MDRB_BntClicked_Right(true))
    {
      if (!selMode_IRQ)
      {        
        if (I2C_GetRegister(RTC_I2C_ADDRESS, RTC_REGISTER_SECONDS, &seconds))
          printf("Key2: seconds = %d\n", seconds);
        else
          printf("Key2: ReadReg Fault\n");
      }
      else
      {
        if (!I2C_IRQ_GetRegisterStart(RTC_I2C_ADDRESS, RTC_REGISTER_SECONDS))
          printf("Key2 IRQ: ReadReg Start Fault\n");
        else
          printf("Key2 IRQ: ReadReg Start OK\n");
      }
    }
    
    //  Окончание обнуления секунд в варианте через IRQ
    if (ready_WriteReg)
    {
      if (I2C_GetStatus())
        printf("IRQ: WriteReg Fault\n");
      else
        printf("IRQ: Seconds Cleared\n");
      
      ready_WriteReg = false;
    }
    
    //  Окончание чтения секунд в варианте через IRQ
    if (ready_ReadReg)
    {
      if (I2C_GetResultAndStatus(&seconds))
      {          
        printf("IRQ: seconds = %d\n", seconds);
      }
      else
        printf("IRQ: ReadReg Fault\n");
      ready_ReadReg = false;
    }
   

//  Для наблюдения на осциллографе
#if DEBUG_MODE_FOR_OSCIL
//    //  Транзакция записи
//    seconds = 0xCA;
//    MDR_I2C_TransferWrite(RTC_I2C_ADDRESS, 1, &seconds);    
//    //  Транзакция чтения
//    MDR_I2C_TransferRead(RTC_I2C_ADDRESS, 1, &seconds);    
    
    //  Этапы при записи и чтения
    MDR_I2C_StartTransfer(RTC_I2C_ADDRESS, true);    
    MDR_Delay(300);
    MDR_I2C_SendByte(seconds);
    MDR_Delay(300);
    MDR_I2C_ReadByte(&seconds, true);    
    MDR_Delay(300);
    MDR_I2C_StopTransfer();
    MDR_Delay(600);
#endif
    
  }
}

bool I2C_SetRegister(uint8_t addr, uint8_t regAddr, uint8_t regData)
{
  uint8_t arr[2];
  arr[0] = regAddr;
  arr[1] = regData;
  
  // Запись в регистр
  return (MDR_I2C_TransferWrite(addr, 2, arr) == 2);
}

bool I2C_GetRegister(uint8_t addr, uint8_t regAddr, uint8_t *regData)
{  
  //  Выбор регистра
  if (MDR_I2C_TransferWrite(addr, 1, &regAddr) == 1)
  {
    //  Чтение регистра
    return (MDR_I2C_TransferRead(addr, 1, regData) == 1);
  }
  else
    return false;
}


//===============  Реализация черезIRQ  ===============
uint8_t _activeI2C_addr;
uint8_t _activeI2C_data;
bool    _successI2C;
bool    _startedI2C;

void I2C_OnWriteReg_Completed(void);
void I2C_IRQ_OnSelectReg_Completed(void);
void I2C_IRQ_OnReadReg_Completed(void);

bool I2C_GetStatus(void)
{
  return _successI2C;
}

bool I2C_GetResultAndStatus(uint8_t *dataRX)
{
  *dataRX = _activeI2C_data;
  return _successI2C;
}

//  Запись
bool I2C_IRQ_SetRegisterStart(uint8_t addr, uint8_t regAddr, uint8_t regData)
{
  uint8_t arr[2];
  arr[0] = regAddr;
  arr[1] = regData;
  _startedI2C = true;
  ready_WriteReg = false;
  
  // Запись в регистр
  return MDR_I2C_IRQ_TryStartTransfer(addr, 2, arr, true, I2C_OnWriteReg_Completed);
}

void I2C_OnWriteReg_Completed(void)
{
  MDR_I2C_IRQ_GetCompleted(&_successI2C);
  _startedI2C = false;
  ready_WriteReg = true;
}

//  Чтение
bool I2C_IRQ_GetRegisterStart(uint8_t addr, uint8_t regAddr)
{  
  //  Выбор регистра
  if (MDR_I2C_IRQ_TryStartTransfer(addr, 1, &regAddr, false, I2C_IRQ_OnSelectReg_Completed))
  {
    _activeI2C_addr = addr;
    _activeI2C_data = 0;
    _startedI2C = true;
    ready_ReadReg = false;
    return true;
  }
  else
    return false;
}

void I2C_IRQHandler(void)
{
  MDR_I2C_IRQ_HandlerProcess();
  NVIC_ClearPendingIRQ(I2C_IRQn);
}

void I2C_IRQ_OnSelectReg_Completed(void)
{
  //  Статуст от команды выбора регистра
  MDR_I2C_IRQ_GetCompleted(&_successI2C);
  //  Запуск чтения регистра
  if (_successI2C)
    _successI2C = MDR_I2C_IRQ_TryStartTransfer(_activeI2C_addr, 1, &_activeI2C_data, true, I2C_IRQ_OnReadReg_Completed);
  //  Запуск не удался - выход
  if (!_successI2C)
    I2C_IRQ_OnReadReg_Completed();
}

void I2C_IRQ_OnReadReg_Completed(void)
{
  MDR_I2C_IRQ_GetCompleted(&_successI2C);
  _startedI2C = false; 
  ready_ReadReg = true;
}





