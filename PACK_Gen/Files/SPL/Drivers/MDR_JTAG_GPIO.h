#ifndef _JTAG_GPIO_H
#define _JTAG_GPIO_H

#include <MDR_GPIO.h>

typedef struct {
  //  Pins defs
  MDR_GPIO_CfgPinPort cfgTCK;
  MDR_GPIO_CfgPinPort cfgTMS;
  MDR_GPIO_CfgPinPort cfgTDI;
  MDR_GPIO_CfgPinPort cfgTDO;
  MDR_GPIO_CfgPinPort *pCfgTRST;
  //  Clock width delay for MDR_Delay
  uint32_t            widthTCK_Ticks;
  pWaitTicksFunc      funcWaitTicks;
} MDR_JTAG_Cfg;

void MDR_JTAG_Init(const MDR_JTAG_Cfg *cfgJTAG);
void MDR_JTAG_ResetTarget(uint32_t reselTicks);
void MDR_JTAG_Finit(void);


#define MDR_JTAG_INSTR_BIT_LEN    10

//  JTAG IEEE 1149 instructions
#define MDR_JTAG_IR__BYPASS             0x3FF   //b11_1111_1111
#define MDR_JTAG_IR__EXTEST             0x000   //b00_0000_0000
#define MDR_JTAG_IR__SAMPLE             0x055   //b00_0101_0101
#define MDR_JTAG_IR__IDCODE             0x059   //b00_0101_1001
#define MDR_JTAG_IR__USERCODE           0x079   //b00_0111_1001
#define MDR_JTAG_IR__INIT_CONF          0x061   //b00_0110_0001
#define MDR_JTAG_IR__PENDCFG            0x065   //b00_0110_0101

//  BSDL EPC4Q100: Following 10 instructions are IEEE 1532 instructions
#define MDR_JTAG_IR__ISC_ENABLE	        0x044   //b00_0100_0100
#define MDR_JTAG_IR__ISC_DISABLE	      0x04A   //b00_0100_1010
#define MDR_JTAG_IR__ISC_PROGRAM	      0x196   //b01_1001_0110
#define MDR_JTAG_IR__ISC_ERASE	        0x192   //b01_1001_0010
#define MDR_JTAG_IR__ISC_ADDRESS_SHIFT  0x10E   //b01_0000_1110
#define MDR_JTAG_IR__ISC_READ_INFO      0x042   //b00_0100_0010
#define MDR_JTAG_IR__ISC_READ	          0x1A6   //b01_1010_0110
#define MDR_JTAG_IR__ISC_NOOP	          0x0FF   //b00_1111_1111
#define MDR_JTAG_IR__ISC_STAT	          0x03E   //b00_0011_1110


//  Forced exit to Reset - (5 times TMS). Reset clears active IR to default (ByPass or IDCODE)
void MDR_JTAG_ToReset(void);

//  IDLE uses as Parking State
void MDR_JTAG_ResetAndParking(void);


//  Call MDR_JTAG_ToReset() to reset active IR!
void MDR_JTAG_WriteIR(uint32_t bitLenIR, uint32_t instr);

void MDR_JTAG_WriteDR(uint32_t bitLenDR, uint32_t data);
uint32_t MDR_JTAG_ReadDR(uint32_t bitLenDR);
  
void MDR_JTAG_IR_WriteDR(uint32_t bitLenIR, uint32_t instr, uint32_t bitLenDR, uint32_t data);
uint32_t MDR_JTAG_IR_ReadDR(uint32_t bitLenIR, uint32_t instr, uint32_t bitLenDR);

//  implementation for "WAIT TCK 1"
void MDR_JTAG_SendCyclesTCK(uint32_t cntCycles);


static inline void MDR_JTAG_ISC_WriteIR_TCK1(uint32_t bitLenIR, uint32_t instr)
{
  MDR_JTAG_WriteIR(bitLenIR, instr);
  MDR_JTAG_SendCyclesTCK(1);
}

//  The same funcs with PAUSE cycles
//  "The Pause-DR state is included to provide a wait time during shifting to allow for example a test pattern generator to fetch/prepare test data"
//  Пауза используется для временной приостановки сдвига DR или IR, (чтобы подкачать данные) - данные функции не нужны
void MDR_JTAG_WriteIR_Paused(uint32_t bitLenIR, uint32_t instr, uint32_t instPauseCnt);

void MDR_JTAG_WriteDR_Paused(uint32_t bitLenDR, uint32_t data, uint32_t dataPauseCnt);
void MDR_JTAG_ReadDR_Paused(uint32_t bitLenDR, uint32_t *data, uint32_t dataPauseCnt);
  
void MDR_JTAG_IR_WriteDR_Paused(uint32_t bitLenIR, uint32_t instr, uint32_t bitLenDR, uint32_t data, uint32_t instPauseCnt, uint32_t dataPauseCnt);
void MDR_JTAG_IR_ReadDR_Paused(uint32_t bitLenIR, uint32_t instr, uint32_t bitLenDR, uint32_t *data, uint32_t instPauseCnt, uint32_t dataPauseCnt);


//  ================    For 1986VE1 ===============

#define MDR_JTAG_VE1_IR_LEN            8
#define MDR_JTAG_VE1_IR_IDCODE      0x02
#define MDR_JTAG_VE1_DR_IDCODE_LEN    32


static inline uint32_t MDR_JTAG_1986VE1_Read_IDCODE(void)
{    
  return MDR_JTAG_IR_ReadDR(MDR_JTAG_VE1_IR_LEN, MDR_JTAG_VE1_IR_IDCODE, MDR_JTAG_VE1_DR_IDCODE_LEN);
}

#endif  //  _JTAG_GPIO_H
