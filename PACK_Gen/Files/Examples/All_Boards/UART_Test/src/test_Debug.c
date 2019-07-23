#include <MDR_UART.h>

#include "test_Defs.h"
#include "MDRB_UART_Debug.h"

#include <stdio.h>

//  Test Interface functions
static void  Test_Init(void);
static void  Test_InitRX(void);

static void  Test_Finit(void);
static void  Test_Change(void);
static void  Test_Exec(void);
static void  Test_HandleIRQ(void);
static void  Test_HandleIRQ_Empty(void);

extern TestInterface TI_Uart_Debug;
extern TestInterface TI_Uart_DebugRate;

TestInterface TI_Uart_Debug = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Change,
  .funcExec       = Test_Exec,
  .funcHandlerIrqMaster = Test_HandleIRQ_Empty,
  .funcHandlerIrqSlave  = Test_HandleIRQ_Empty
};

TestInterface TI_Uart_DebugRate = {
  .funcInit       = Test_InitRX,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Change,
  .funcExec       = Test_Exec,
  .funcHandlerIrqMaster = Test_HandleIRQ,
  .funcHandlerIrqSlave  = Test_HandleIRQ
};

static void Test_Init(void)
{
  MDR_UART_DBG_Init();
  printf("Debug print test!\n");
}  

static void Test_InitRX(void)
{
  MDR_UART_DBG_InitEx(UART_BAUD_9600, true); 
  MDR_UART_ChangeEventIRQ(UART_DBG->UARTx, MDR_UART_EFL_RX);
  
  NVIC_EnableIRQ(UART_DBG->UARTx_IRQn);
  
  printf("Debug change rate test!\n");
  printf("To change baudRate send:\n");
  printf("  R0: - 9600\n");
  printf("  R1: - 19200\n");
  printf("  R2: - 38400\n");
  printf("  R3: - 57600\n");
  printf("  R4: - 115200\n");
  printf("  R5: - 230400\n");
}  

static void Test_Finit(void)
{
  MDR_UART_DBG_Finit();
}

static void Test_Change(void)
{

}

static void Test_Exec(void)
{
  printf("Hello! I'm Fine! \n");
}

#define  TEST_BAUDS_COUNT   6
static uint32_t baudsUART[TEST_BAUDS_COUNT] = {UART_BAUD_9600, UART_BAUD_19200, UART_BAUD_38400, UART_BAUD_57600, UART_BAUD_115200, UART_BAUD_230400};
  

static void Test_HandleIRQ(void)
{
  char command;
  char rateInd = 0;
  uint32_t cntOK = 0;
  
  //  Прерывание приходит при заполнении FIFO_RX двумя значениями!
  //  В режиме FIFO, который включается в UART_DBG, меньше выставить нельзя.
  if (MDR_UART_CanRead(UART_DBG->UARTx))
  {
    //  Команда - R: смена скорости
    command = MDR_UART_ReadData(UART_DBG->UARTx) & 0x00FF;
    if (command != 'R')
      printf("Undefined Command: %c\n", command);
    else
      ++cntOK;
    // Индекс скорости
    if (MDR_UART_CanRead(UART_DBG->UARTx))
    {
      rateInd = MDR_UART_ReadData(UART_DBG->UARTx) & 0x00FF;
      rateInd = rateInd - '0';
      if (rateInd >= TEST_BAUDS_COUNT)
        printf("Undefined RateIndex: %d\n", rateInd);
      else
        ++cntOK;
    }
    else
      printf("Send two chars!\n");
    
    if (cntOK == 2)
    {
      MDR_UART_DBG_ChangeRate(baudsUART[(uint32_t)rateInd]);
    }    
  }
  
  // Clear RX event  
  MDR_UART_ClearEventsIRQ(UART_DBG->UARTx, MDR_UART_EFL_RX);
}

static void Test_HandleIRQ_Empty(void)
{
}

