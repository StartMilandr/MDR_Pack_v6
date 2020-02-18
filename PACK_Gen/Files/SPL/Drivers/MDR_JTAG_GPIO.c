#include <MDR_JTAG_GPIO.h>
#include <MDR_JTAG_Config.h>

//  Локальные переменные, чтобы не тратилось время на выборку из структуры.
static MDR_PORT_Type *      _PORT_TCK;
static MDR_PORT_Type *      _PORT_TMS;
static MDR_PORT_Type *      _PORT_TDI;
static MDR_PORT_Type *      _PORT_TDO;
static MDR_PORT_Type *      _PORT_TRST;

static uint32_t             _PIN_TCK;
static uint32_t             _PIN_TMS;
static uint32_t             _PIN_TDI;
static uint32_t             _PIN_TDO;
static uint32_t             _PIN_TRST;

static pWaitTicksFunc       _funcWaitTicks;
static uint32_t             _widthTCK_Ticks;


void MDR_JTAG_Init(const MDR_JTAG_Cfg *cfgJTAG)
{
  //  Save struct to local vars
  _PORT_TCK = cfgJTAG->cfgTCK.portGPIO->PORTx;
  _PORT_TMS = cfgJTAG->cfgTMS.portGPIO->PORTx;
  _PORT_TDI = cfgJTAG->cfgTDI.portGPIO->PORTx;
  _PORT_TDO = cfgJTAG->cfgTDO.portGPIO->PORTx;
  _PORT_TRST = NULL;

  _PIN_TCK = cfgJTAG->cfgTCK.selPins;
  _PIN_TMS = cfgJTAG->cfgTMS.selPins;
  _PIN_TDI = cfgJTAG->cfgTDI.selPins;
  _PIN_TDO = cfgJTAG->cfgTDO.selPins;
  _PIN_TRST = 0;
  
  _funcWaitTicks = cfgJTAG->funcWaitTicks;
  _widthTCK_Ticks = cfgJTAG->widthTCK_Ticks;
  
  //  Init Pins    
  MDR_GPIO_Enable(cfgJTAG->cfgTCK.portGPIO);
  MDR_GPIO_Enable(cfgJTAG->cfgTMS.portGPIO);
  MDR_GPIO_Enable(cfgJTAG->cfgTDO.portGPIO);
  MDR_GPIO_Enable(cfgJTAG->cfgTDI.portGPIO);
  
  MDR_Port_Init_PortOUT(_PORT_TCK, _PIN_TCK, JTAG_PIN_PWR);
  MDR_Port_Init_PortOUT(_PORT_TMS, _PIN_TMS, JTAG_PIN_PWR);  
  MDR_Port_Init_PortOUT(_PORT_TDI, _PIN_TDI, JTAG_PIN_PWR);
  MDR_Port_Init_PortIN(_PORT_TDO, _PIN_TDO);  
  if (cfgJTAG->pCfgTRST != NULL)
  {
    _PIN_TRST = cfgJTAG->pCfgTRST->selPins;
    _PORT_TRST = cfgJTAG->pCfgTRST->portGPIO->PORTx;
    
    MDR_GPIO_Enable(cfgJTAG->pCfgTRST->portGPIO);
    MDR_Port_Init_PortOUT(_PORT_TRST, _PIN_TRST, JTAG_PIN_PWR);
    MDR_Port_SetPins(_PORT_TRST, _PIN_TRST);    
  }
}  

void MDR_JTAG_Finit(void)
{
  MDR_Port_InitAnalog(_PORT_TCK, _PIN_TCK);
  MDR_Port_InitAnalog(_PORT_TMS, _PIN_TMS);
  MDR_Port_InitAnalog(_PORT_TDI, _PIN_TDI);
  MDR_Port_InitAnalog(_PORT_TDO, _PIN_TDO);
  if (_PORT_TRST != NULL)
    MDR_Port_InitAnalog(_PORT_TRST, _PIN_TRST);
}

void MDR_JTAG_ResetTarget(uint32_t reselTicks)
{
  if (_PIN_TRST != NULL)
  {
    MDR_Port_ClearPins(_PORT_TRST, _PIN_TRST);
    _funcWaitTicks(reselTicks);
    MDR_Port_SetPins(_PORT_TRST, _PIN_TRST);
  }
}

//==================    JTAG State Machine Move ================

#define Set_TCK_0   MDR_Port_ClearPins(_PORT_TCK, _PIN_TCK)
#define Set_TCK_1   MDR_Port_SetPins  (_PORT_TCK, _PIN_TCK)

#define Set_TMS_0   MDR_Port_ClearPins(_PORT_TMS, _PIN_TMS)
#define Set_TMS_1   MDR_Port_SetPins  (_PORT_TMS, _PIN_TMS)

#define Set_TDI_0   MDR_Port_ClearPins(_PORT_TDI, _PIN_TDI)
#define Set_TDI_1   MDR_Port_SetPins  (_PORT_TDI, _PIN_TDI)

#define Get_TDO     MDR_Port_Get(_PORT_TDO) & _PIN_TDO

#if JTAG_REMOVE_DELAYS
  #define WIDTH_DELAY    //_funcWaitTicks(_widthTCK_Ticks)
#else
  #define WIDTH_DELAY    _funcWaitTicks(_widthTCK_Ticks)
#endif

static inline void MDR_JTAG_MOVE_TMS_0(void)
{
  //Set_TCK_0;    //  Line already in Low
  WIDTH_DELAY; 
  Set_TCK_1;
  WIDTH_DELAY;
  Set_TCK_0;
}

static inline void MDR_JTAG_MOVE_TMS_1(void)
{
  Set_TCK_0;
    Set_TMS_1;
  WIDTH_DELAY; 
  Set_TCK_1;
  WIDTH_DELAY;
  Set_TCK_0;
    Set_TMS_0;
}

static inline void MDR_JTAG_SendBit_TDI(uint32_t boolHigh)
{
  //Set_TCK_0;    //  Line already in Low
    if (boolHigh)
      Set_TDI_1;
    else
      Set_TDI_0;
  WIDTH_DELAY; 
  Set_TCK_1;
  WIDTH_DELAY;
  Set_TCK_0;
    Set_TDI_0;
}

static inline void MDR_JTAG_SendLastBit_TDI_ToExit1(uint32_t boolHigh)
{
  //Set_TCK_0;    //  Line already in Low
  Set_TMS_1;
    if (boolHigh)
      Set_TDI_1;
    else
      Set_TDI_0;
  WIDTH_DELAY; 
  Set_TCK_1;
  WIDTH_DELAY;
  Set_TCK_0;
    Set_TDI_0;
    Set_TMS_0;
}

static inline uint32_t MDR_JTAG_ReadBit_TDO(void)
{ 
  //Set_TCK_0;    //  Line already in Low  
  WIDTH_DELAY; 
  Set_TCK_1;
    uint32_t result = Get_TDO;
  WIDTH_DELAY;
  Set_TCK_0;
    return result;
}

static inline uint32_t MDR_JTAG_ReadLastBit_TDO_ToExit1(void)
{
  //Set_TCK_0;    //  Line already in Low
    Set_TMS_1;
  WIDTH_DELAY; 
  Set_TCK_1;
    uint32_t result = Get_TDO;
  WIDTH_DELAY;
  Set_TCK_0;
    Set_TMS_0;
    return result;
}


//  Forced exit to Reset - (5 times TMS)
void MDR_JTAG_ToReset(void) 
{
  MDR_JTAG_MOVE_TMS_1();
  MDR_JTAG_MOVE_TMS_1();
  MDR_JTAG_MOVE_TMS_1();
  MDR_JTAG_MOVE_TMS_1();
  MDR_JTAG_MOVE_TMS_1();
  //  Extra Reset -!?
  //MDR_JTAG_MOVE_TMS_1();
}

void MDR_JTAG_SendCyclesTCK(uint32_t cntCycles)
{
  Set_TDI_1;
  while(cntCycles--)
    MDR_JTAG_MOVE_TMS_0();
}

//  To Idle
#define MDR_JTAG_Reset_ToIdle         MDR_JTAG_MOVE_TMS_0
//  To SelDRScan
#define MDR_JTAG_Idle_ToSelDRScan     MDR_JTAG_MOVE_TMS_1

//  To Capture DR / IR
#define MDR_JTAG_Idle_ToCapIR()       MDR_JTAG_MOVE_TMS_1();  \
                                      MDR_JTAG_MOVE_TMS_1();  \
                                      MDR_JTAG_MOVE_TMS_0()

#define MDR_JTAG_Idle_ToCapDR()       MDR_JTAG_MOVE_TMS_1();  \
                                      MDR_JTAG_MOVE_TMS_0()

#define MDR_JTAG_SelDRScan_ToCapIR()  MDR_JTAG_MOVE_TMS_1();  \
                                      MDR_JTAG_MOVE_TMS_0()

#define MDR_JTAG_SelDRScan_ToCapDR    MDR_JTAG_MOVE_TMS_0

//  From Capture to Exis1 or Shift IR/DR
#define MDR_JTAG_CapIDR_ToExit1       MDR_JTAG_MOVE_TMS_1
#define MDR_JTAG_CapIDR_ToShiftIDR    MDR_JTAG_MOVE_TMS_0

//  From Exit1 IR/DR to Update IR/DR
#define MDR_JTAG_Exit1_ToUpdIDR       MDR_JTAG_MOVE_TMS_1

//  From Exit2 return to Shift IR/DR or to Update IR/DR
#define MDR_JTAG_Exit2_ToShiftIDR     MDR_JTAG_MOVE_TMS_0
#define MDR_JTAG_Exit2_ToUpdIDR       MDR_JTAG_MOVE_TMS_1

//  Return to SelDRScan or Idle
#define MDR_JTAG_UpdIDR_ToSelDRScan   MDR_JTAG_MOVE_TMS_1
#define MDR_JTAG_UpdIDR_ToIdle        MDR_JTAG_MOVE_TMS_0


void MDR_JTAG_ShiftReadIDR_ToExit1(uint32_t bitCnt, uint32_t *data)
{
  uint32_t i;
  *data = 0;
  for (i = 0; i < bitCnt - 0; ++i)
  {
    if (MDR_JTAG_ReadBit_TDO())
      *data |= (1 << i);
  } 
  if (MDR_JTAG_ReadLastBit_TDO_ToExit1())
    *data |= bitCnt - 1;
}

void MDR_JTAG_ShiftWriteIDR_ToExit1(uint32_t bitCnt, uint32_t data)
{
  uint32_t lbit = 1;
  while (--bitCnt)
  {    
    MDR_JTAG_SendBit_TDI(data & lbit);
    lbit <<= 1;
  }
  MDR_JTAG_SendLastBit_TDI_ToExit1(data & lbit);
}

//==================    JTAG Read-Write Regs ================

void MDR_JTAG_ResetAndParking(void)
{
  MDR_JTAG_ToReset();
  MDR_JTAG_Reset_ToIdle();  
}

//  Call MDR_JTAG_ToReset() to reset active IR!
void MDR_JTAG_WriteIR(uint32_t bitLenIR, uint32_t instr)
{
  //  Idle - Parking
  MDR_JTAG_Idle_ToCapIR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Write IR
  MDR_JTAG_ShiftWriteIDR_ToExit1(bitLenIR, instr);
  MDR_JTAG_Exit1_ToUpdIDR();
  MDR_JTAG_UpdIDR_ToIdle();  
}

void MDR_JTAG_WriteDR(uint32_t bitLenDR, uint32_t data)
{
  //  Idle - Parking
  MDR_JTAG_Idle_ToCapDR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Write DR
  MDR_JTAG_ShiftWriteIDR_ToExit1(bitLenDR, data);
  MDR_JTAG_Exit1_ToUpdIDR();
  MDR_JTAG_UpdIDR_ToIdle();
}

uint32_t MDR_JTAG_ReadDR(uint32_t bitLenDR)
{
  //  Idle - Parking
  MDR_JTAG_Idle_ToCapDR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Read DR
  uint32_t data;
  MDR_JTAG_ShiftReadIDR_ToExit1(bitLenDR, &data);
  MDR_JTAG_Exit1_ToUpdIDR();
  MDR_JTAG_UpdIDR_ToIdle();  
  return data;
}
  
void MDR_JTAG_IR_WriteDR(uint32_t bitLenIR, uint32_t instr, uint32_t bitLenDR, uint32_t data)
{
  //  Idle - Parking
  MDR_JTAG_Idle_ToCapIR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Write IR
  MDR_JTAG_ShiftWriteIDR_ToExit1(bitLenIR, instr);
  MDR_JTAG_Exit1_ToUpdIDR();
  
  //  Go to DR-bush
  MDR_JTAG_UpdIDR_ToSelDRScan();
  MDR_JTAG_SelDRScan_ToCapDR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Write DR
  MDR_JTAG_ShiftWriteIDR_ToExit1(bitLenDR, data);
  MDR_JTAG_Exit1_ToUpdIDR();
  MDR_JTAG_UpdIDR_ToIdle();      
}

uint32_t MDR_JTAG_IR_ReadDR(uint32_t bitLenIR, uint32_t instr, uint32_t bitLenDR)
{
  //  Idle - Parking
  MDR_JTAG_Idle_ToCapIR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Write IR
  MDR_JTAG_ShiftWriteIDR_ToExit1(bitLenIR, instr);
  MDR_JTAG_Exit1_ToUpdIDR();
  
  //  Go to DR-bush
  MDR_JTAG_UpdIDR_ToSelDRScan();
  MDR_JTAG_SelDRScan_ToCapDR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Read DR
  uint32_t data;
  MDR_JTAG_ShiftReadIDR_ToExit1(bitLenDR, &data);
  MDR_JTAG_Exit1_ToUpdIDR();
  MDR_JTAG_UpdIDR_ToIdle();
  return data;
}

//==================    JTAG Read-Write Regs with PAUSE cycles ================

//  The same funcs with PAUSE cycles

//  From Exit1 IR / DR to Exit2 with pause
static inline void MDR_JTAG_Exit1_ToPauseToExit2(uint32_t pauseBitCnt)
{
  while (pauseBitCnt--)
    MDR_JTAG_MOVE_TMS_0();
}


void MDR_JTAG_WriteIR_Paused(uint32_t bitLenIR, uint32_t instr, uint32_t instPauseCnt)
{
  //  Idle - Parking
  MDR_JTAG_Idle_ToCapIR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Write IR
  MDR_JTAG_ShiftWriteIDR_ToExit1(bitLenIR, instr);
  MDR_JTAG_Exit1_ToPauseToExit2(instPauseCnt);
  MDR_JTAG_Exit2_ToUpdIDR();
  MDR_JTAG_UpdIDR_ToIdle();
}

void MDR_JTAG_WriteDR_Paused(uint32_t bitLenDR, uint32_t data, uint32_t dataPauseCnt)
{
  //  Idle - Parking
  MDR_JTAG_Idle_ToCapDR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Write DR
  MDR_JTAG_ShiftWriteIDR_ToExit1(bitLenDR, data);
  MDR_JTAG_Exit1_ToPauseToExit2(dataPauseCnt);
  MDR_JTAG_Exit2_ToUpdIDR();
  MDR_JTAG_UpdIDR_ToIdle();  
}

void MDR_JTAG_ReadDR_Paused(uint32_t bitLenDR, uint32_t *data, uint32_t dataPauseCnt)
{
  //  Idle - Parking
  MDR_JTAG_Idle_ToCapDR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Read DR
  MDR_JTAG_ShiftReadIDR_ToExit1(bitLenDR, data);
  MDR_JTAG_Exit1_ToPauseToExit2(dataPauseCnt);
  MDR_JTAG_Exit2_ToUpdIDR();  
  MDR_JTAG_UpdIDR_ToIdle();  
}
  
void MDR_JTAG_IR_WriteDR_Paused(uint32_t bitLenIR, uint32_t instr, uint32_t bitLenDR, uint32_t data, uint32_t instPauseCnt, uint32_t dataPauseCnt)
{
  //  Idle - Parking
  MDR_JTAG_Idle_ToCapIR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Write IR
  MDR_JTAG_ShiftWriteIDR_ToExit1(bitLenIR, instr);
  MDR_JTAG_Exit1_ToPauseToExit2(instPauseCnt);
  MDR_JTAG_Exit2_ToUpdIDR();
  
  //  Go to DR-bush
  MDR_JTAG_UpdIDR_ToSelDRScan();
  MDR_JTAG_SelDRScan_ToCapDR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Write DR
  MDR_JTAG_ShiftWriteIDR_ToExit1(bitLenDR, data);
  MDR_JTAG_Exit1_ToPauseToExit2(dataPauseCnt);
  MDR_JTAG_Exit2_ToUpdIDR();  
  MDR_JTAG_UpdIDR_ToIdle(); 
}  

void MDR_JTAG_IR_ReadDR_Paused(uint32_t bitLenIR, uint32_t instr, uint32_t bitLenDR, uint32_t *data, uint32_t instPauseCnt, uint32_t dataPauseCnt)
{
  //  Idle - Parking
  MDR_JTAG_Idle_ToCapIR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Write IR
  MDR_JTAG_ShiftWriteIDR_ToExit1(bitLenIR, instr);
  MDR_JTAG_Exit1_ToPauseToExit2(instPauseCnt);
  MDR_JTAG_Exit2_ToUpdIDR();
  
  //  Go to DR-bush
  MDR_JTAG_UpdIDR_ToSelDRScan();
  MDR_JTAG_SelDRScan_ToCapDR();
  MDR_JTAG_CapIDR_ToShiftIDR();
  //  Read DR
  MDR_JTAG_ShiftReadIDR_ToExit1(bitLenDR, data);
  MDR_JTAG_Exit1_ToPauseToExit2(dataPauseCnt);
  MDR_JTAG_Exit2_ToUpdIDR();
  MDR_JTAG_UpdIDR_ToIdle();
}

