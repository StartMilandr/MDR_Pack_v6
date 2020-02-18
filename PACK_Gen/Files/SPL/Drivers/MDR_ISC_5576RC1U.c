#include <MDR_ISC_5576RC1U.h>


MDR_5576RC_Delays _5576RC_Delays;

#define  _5576RC1U_CfgBits_Len   12
uint16_t _5576RC1U_CfgBits[_5576RC1U_CfgBits_Len] = {0x0070, 0x7007, 0x7FE0, 0x1234, 0x5678, 0x7654, 0x0201, 0x0403, 0xFFF0, 0x5200, 0x0000, 0x0000};


void MDR_5576RC_Init(const MDR_JTAG_Cfg *cfgJTAG, MDR_5576RC_Delays *delays)
{
  _5576RC_Delays = *delays;
  
  MDR_JTAG_Init(cfgJTAG);
  MDR_JTAG_ResetAndParking();
}


//static inline void MDR_ISC_WriteIR_Delay(uint32_t instr, uint32_t delayTicks)
//{
//  MDR_JTAG_WriteIR(MDR_JTAG_INSTR_BIT_LEN, instr);
//  MDR_Delay(delayTicks);
//}

////  "PROC_ENABLE  = (FLOW_ENABLE)," & 
////  "FLOW_ENABLE " & 
////    "INITIALIZE " &
////      "(ISC_ENABLE        WAIT 1.0e-3)," &
//void MDR_5576RC_FlowEnable(void) 
//{
//  MDR_ISC_WriteIR_Delay(MDR_JTAG_IR__ISC_ENABLE, _5576RC_Delays.ticks_1ms);
//}


////  "PROC_DISABLE    = (FLOW_DISABLE)," &
////  "PROC_ERROR_EXIT = (FLOW_DISABLE)," &
////  "FLOW_DISABLE " &
////    "INITIALIZE " &
////      "(ISC_DISABLE                 WAIT  1.0e-3)," &
//void MDR_5576RC_FlowDisable(void)
//{
//  MDR_ISC_WriteIR_Delay(MDR_JTAG_IR__ISC_DISABLE, _5576RC_Delays.ticks_1ms);
//}


////--------------------------

//static inline void MDR_ISC_AddrShift(uint32_t addr)
//{
//  MDR_JTAG_IR_WriteDR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_ADDRESS_SHIFT, MDR_5576RC_ADDR_LEN, addr);
//  MDR_JTAG_SendCyclesTCK(1);
//}

//static inline uint32_t MDR_ISC_ReadDR18(void)
//{
//  MDR_JTAG_ISC_WriteIR_TCK1(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_READ);
//  return MDR_JTAG_ReadDR(MDR_5576RC_RD_DATA_CRC_LEN);  
//}


////  "PROC_PROGRAM(array) = (FLOW_PROGRAM(array))," &
////  "FLOW_PROGRAM (array) " &
////    "INITIALIZE " &
////      "(ISC_ADDRESS_SHIFT 23:000000 WAIT TCK 1)" &
////      "(ISC_PROGRAM       16:?      WAIT 3.0e-4 )" &
////    "REPEAT 249999 " &
////      "(ISC_PROGRAM       16:?      WAIT 3.0e-4 )";

////static inline void MDR_ISC_ProgData_Delay(uint32_t data, uint32_t delayTicks)
////{
////  MDR_JTAG_IR_WriteDR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_PROGRAM, MDR_5576RC_PROG_DATA_LEN, data);
////  MDR_JTAG_SendCyclesTCK(2000);
////  MDR_Delay(delayTicks);
////}

////static inline void MDR_5576RC_ProgramNext(uint16_t data)
////{
////  //MDR_5576RC_FlowEnableX();
////  MDR_ISC_ProgData_Delay(data, _5576RC_Delays.ticks_300ns);
////}

////void MDR_5576RC_FlowProgram(uint32_t addr, uint16_t data)
////{
////  MDR_ISC_AddrShift(addr);
////  MDR_5576RC_ProgramNext(data);
////}

////void MDR_5576RC_FlowProgramBuff(uint32_t startAddr, uint32_t bufLen, uint16_t *pData)
////{
////  MDR_ISC_AddrShift(startAddr);
////  while (bufLen--)
////  {
////    MDR_5576RC_ProgramNext(*pData);
////    ++pData;
////  }
////}

////void MDR_5576RC_FlowProgramFill(uint32_t startAddr, uint32_t fillLen, uint16_t fillData)
////{
////  MDR_ISC_AddrShift(startAddr);
////  while (fillLen--)
////    MDR_5576RC_ProgramNext(fillData);
////}


//static inline void MDR_ISC_ProgData_Start(void)
//{
//  MDR_JTAG_WriteIR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_PROGRAM);
//  MDR_JTAG_SendCyclesTCK(2000);
//  MDR_Delay(_5576RC_Delays.ticks_300ns);
//}

//static inline void MDR_5576RC_ProgData_Next(uint16_t data)
//{
//  MDR_JTAG_WriteDR(MDR_5576RC_PROG_DATA_LEN, data);
//  MDR_JTAG_SendCyclesTCK(2000);
//  MDR_Delay(_5576RC_Delays.ticks_300ns);
//}

//void MDR_5576RC_FlowProgram(uint32_t addr, uint16_t data)
//{
////  MDR_5576RC_FlowEnableX();

//  //MDR_ISC_ReadDR18(); //  Dummy read
//  
//  MDR_ISC_AddrShift(addr);
//  MDR_ISC_ProgData_Start();
//  MDR_5576RC_ProgData_Next(data);
//}

//void MDR_5576RC_FlowProgramBuff(uint32_t startAddr, uint32_t bufLen, uint16_t *pData)
//{
//  MDR_ISC_AddrShift(startAddr);
//  MDR_ISC_ProgData_Start();
//  while (bufLen--)
//  {
//    MDR_5576RC_ProgData_Next(*pData);
//    ++pData;
//  }
//}

//void MDR_5576RC_FlowProgramFill(uint32_t startAddr, uint32_t fillLen, uint16_t fillData)
//{
//  MDR_ISC_AddrShift(startAddr);
//  MDR_ISC_ProgData_Start();
//  while (fillLen--)
//    MDR_5576RC_ProgData_Next(fillData);
//}


////  "PROC_VERIFY(array) = (FLOW_VERIFY(array))," &
////  "FLOW_VERIFY (array) " &
////    "INITIALIZE" &
////      "(ISC_READ                    WAIT TCK 1  16:DFFF*0000, 2:2*0)  "&  
////      "(ISC_ADDRESS_SHIFT 23:000000 WAIT TCK 1)" &
////      "(ISC_READ                    WAIT TCK 1 16:?*FFFF, 2:2*3:CRC)" &
////    "REPEAT 249999 " &
////      "(ISC_READ                    WAIT TCK 1 16:?*FFFF, 2:2*3:CRC)" &
////    "TERMINATE " &
////      "(ISC_STAT	      18:3FFFF    WAIT TCK 1 18:00002*00003)," &


//uint32_t MDR_5576RC_ISC_FlowGetStat(void)
//{ 
//  MDR_JTAG_IR_WriteDR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_STAT, MDR_5576RC_RD_STAT_LEN, MDR_5576RC_RD_STAT_MSK);
//  MDR_JTAG_SendCyclesTCK(1); 
//  return MDR_JTAG_ReadDR(MDR_5576RC_RD_STAT_LEN);
//}

//uint32_t MDR_5576RC_FlowRead(uint32_t addr)
//{
//  MDR_ISC_ReadDR18(); //  Dummy read
//  MDR_ISC_AddrShift(addr);
//  return MDR_ISC_ReadDR18();
//  
//  //MDR_5576RC_ISC_FlowGetStat();
//}

//void MDR_5576RC_FlowReadBuff(uint32_t startAddr, uint32_t bufLen, uint16_t *pBuff)
//{
//  MDR_ISC_ReadDR18(); //  Dummy read
//  MDR_ISC_AddrShift(startAddr);
//  while (bufLen--)
//  {
//    *pBuff = (MDR_ISC_ReadDR18() >> MDR_5576RC_RD_CRC_POS);
//    pBuff++;
//  }  
//}

//void MDR_5576RC_FlowReadBuff_CRC(uint32_t startAddr, uint32_t bufLen, uint32_t *pBuff)
//{
//  MDR_ISC_ReadDR18(); //  Dummy read
//  MDR_ISC_AddrShift(startAddr);
//  while (bufLen--)
//  {
//    *pBuff = MDR_ISC_ReadDR18();
//    pBuff++;
//  } 
//}  


////  "PROC_PROGRAM_DONE  = (FLOW_PROGRAM_DONEBIT)," &
////  "FLOW_PROGRAM_DONEBIT " &
////    "INITIALIZE " &
////      "(ISC_READ                    WAIT TCK 1  16:DFFF*0000, 2:2*0)  "&  
////      "(ISC_ADDRESS_SHIFT 23:008000 WAIT TCK 1)" &
////      "(ISC_PROGRAM       16:DFFF   WAIT 20.0e-3)," &
//void MDR_5576RC_FlowProgramDoneBit(void)
//{
//  MDR_ISC_ReadDR18(); //  Dummy read  
//  MDR_5576RC_FlowProgram(MDR_5576RC_DONE_BIT_ADDR, MDR_5576RC_DONE_BIT_DATA);
//  
////  MDR_ISC_AddrShift(MDR_5576RC_DONE_BIT_ADDR);
////  MDR_ISC_ProgData_Delay(MDR_5576RC_DONE_BIT_DATA, _5576RC_Delays.ticks_20ms);
//}


////  "PROC_VERIFY(donebit) = (FLOW_VERIFY_PROGRAM_DONEBIT)," &   
////  "FLOW_VERIFY_PROGRAM_DONEBIT "&
////    "INITIALIZE "&
////      "(ISC_READ                    WAIT TCK 1  16:DFFF*0000, 2:2*0)  "& 
////      "(ISC_ADDRESS_SHIFT 23:008000 WAIT TCK 1) "&
////      "(ISC_READ                    WAIT TCK 1  16:DFFF*0000, 2:2*3), "&  
//bool MDR_5576RC_FlowVerifyDoneBit(void)
//{
//  MDR_ISC_ReadDR18(); //  Dummy read  
//  MDR_ISC_AddrShift(MDR_5576RC_DONE_BIT_ADDR);
//  uint32_t data = MDR_ISC_ReadDR18() >> MDR_5576RC_RD_CRC_POS;
//  
//  return data & MDR_5576RC_DONE_BIT_OK;
//}


////  "PROC_BLANK_CHECK = (FLOW_BLANK_CHECK)," &
//// "FLOW_BLANK_CHECK " &
////    "INITIALIZE" &
////      "(ISC_READ                    WAIT TCK 1  16:DFFF*0000, 2:2*0)  "&  
////      "(ISC_ADDRESS_SHIFT 23:000000 WAIT TCK 1)" &
////      "(ISC_READ	                  WAIT TCK 1 18:3FFFE*FFFFF)" &
////      "REPEAT 249999 " &
////      "(ISC_READ                    WAIT TCK 1 18:3FFFE*FFFFF)," &
//bool MDR_5576RC_FlowCheckMemBlank(uint32_t sectAddress, uint32_t sectLen)
//{
//  MDR_ISC_ReadDR18(); //  Dummy read  
//  MDR_ISC_AddrShift(MDR_5576RC_DONE_BIT_ADDR);
//  
//  uint32_t i;
//  for (i = 0; i < MDR_5576RC_DATA_LEN; ++i)
//    if (MDR_ISC_ReadDR18() != MDR_5576RC_DATA_CRC_BLANK)
//      return false;
//    
//  return true;  
//}


////  "TEST_VERIFY_IDCODE = (FLOW_VERIFY_IDCODE)"
////  "FLOW_VERIFY_IDCODE " &
////    "INITIALIZE " &
////      "(IDCODE          32:0        WAIT TCK 1 32:0100A0DD)," &
//uint32_t MDR_5576RC_FlowRead_IDCODE(void)
//{  
//  MDR_JTAG_IR_WriteDR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__IDCODE, MDR_5576RC_IDCODE_LEN, 0);
//  //MDR_JTAG_SendCyclesTCK(1);  
//  return MDR_JTAG_ReadDR(MDR_5576RC_IDCODE_LEN);  
//}


////  "PROC_ERASE = (FLOW_ERASE)," &
////  "FLOW_ERASE " &
////    "INITIALIZE " &
////      "(ISC_ERASE         23:000000 WAIT 25.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE    	2:1	    WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:001000 WAIT 25.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE    	2:1	    WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:002000 WAIT 15.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE      2:1 	    WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:003000 WAIT 15.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE      2:1  	    WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:004000 WAIT 45.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE      2:1         WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:005000 WAIT 45.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE      2:1         WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:006000 WAIT 45.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE      2:1         WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:007000 WAIT 45.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE      2:1         WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:008000 WAIT 45.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE      2:1         WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:010000 WAIT 45.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE      2:1         WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:018000 WAIT 45.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE      2:1         WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:020000 WAIT 45.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE      2:1         WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:028000 WAIT 45.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE      2:1         WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:030000 WAIT 45.0e-1)" &
////      "(ISC_DISABLE                 WAIT  1.0e-3)" &
////      "(ISC_ENABLE      2:1         WAIT 1.0e-3)" &
////      "(ISC_ERASE         23:038000 WAIT 30.0e-1)," &
//void MDR_5576RC_FlowEraseFull(void)
//{  
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_0,  _5576RC_Delays.ticks_500ms * 5);  //25.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_1,  _5576RC_Delays.ticks_500ms * 5);  //25.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_2,  _5576RC_Delays.ticks_500ms * 3);  //15.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_3,  _5576RC_Delays.ticks_500ms * 3);  //15.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_4,  _5576RC_Delays.ticks_500ms * 9);  //45.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_5,  _5576RC_Delays.ticks_500ms * 9);  //45.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_6,  _5576RC_Delays.ticks_500ms * 9);  //45.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_7,  _5576RC_Delays.ticks_500ms * 9);  //45.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_8,  _5576RC_Delays.ticks_500ms * 9);  //45.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_9,  _5576RC_Delays.ticks_500ms * 9);  //45.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_10, _5576RC_Delays.ticks_500ms * 9);  //45.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_11, _5576RC_Delays.ticks_500ms * 9);  //45.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_12, _5576RC_Delays.ticks_500ms * 9);  //45.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_13, _5576RC_Delays.ticks_500ms * 9);  //45.0e-1
//  MDR_5576RC_FlowEraseSector(MDR_5576RC_ADDR_SECT_14, _5576RC_Delays.ticks_500ms * 6);  //30.0e-1    
//}




//void MDR_5576RC_FlowEraseSector(uint32_t sectAddress, uint32_t delayTicks)
//{
//  MDR_JTAG_IR_WriteDR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_ERASE, MDR_5576RC_ADDR_LEN, sectAddress);
//  MDR_Delay(delayTicks);
//  
//  MDR_5576RC_FlowDisable();
//  MDR_5576RC_FlowEnableX();
//}



//=========================     NEW API ===========================
static inline void MDR_5576RC1U_Enable(void)
{
//  MDR_JTAG_IR_WriteDR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_ENABLE, MDR_5576RC_ENA_LEN, MDR_5576RC_ENA_MSK);
//  MDR_JTAG_SendCyclesTCK(1);
//  MDR_Delay(_5576RC_Delays.ticks_1ms);
  
  MDR_JTAG_WriteIR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_ENABLE);  //59sir (10, 0x44);//ISC_ENABLE
  MDR_JTAG_SendCyclesTCK(2);                                          //srun(2);
  MDR_Delay(_5576RC_Delays.ticks_ena_RD_1ms);                         //delay_dwt(1000);  
}

static inline void MDR_5576RC1U_Disable(void)
{
  MDR_JTAG_WriteIR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_DISABLE);
  MDR_JTAG_SendCyclesTCK(1);
  MDR_Delay(_5576RC_Delays.ticks_ena_RD_1ms);
}

void MDR_5576RC1U_Exit(void)
{
  MDR_5576RC1U_Disable();
}

static inline void MDR_5576RC1U_SetAddr(uint32_t addr)
{
  MDR_JTAG_IR_WriteDR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_ADDRESS_SHIFT, MDR_5576RC_ADDR_LEN, addr);
  MDR_JTAG_SendCyclesTCK(1);
  MDR_Delay(_5576RC_Delays.ticks_ena_RD_1ms);
}

void MDR_5576RC1U_ProgStart(uint32_t startAddr)
{  
//  MDR_JTAG_WriteIR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_ENABLE);  //59sir (10, 0x44);//ISC_ENABLE
//  MDR_JTAG_SendCyclesTCK(2);                                          //srun(2);
//  MDR_Delay(_5576RC_Delays.ticks_1ms);                                //delay_dwt(1000);
  
//  MDR_JTAG_WriteIR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_ADDRESS_SHIFT); //sir (10, 0x10e);  // ISC_ADDRESS_SHIFT
//  MDR_JTAG_WriteDR(MDR_5576RC_ADDR_LEN, startAddr);
//  MDR_JTAG_SendCyclesTCK(5);                                                //srun(5);
//  MDR_Delay(_5576RC_Delays.ticks_1ms);                                      //delay_dwt(1000);

  MDR_5576RC1U_Enable();
  MDR_5576RC1U_SetAddr(startAddr);
  
  MDR_JTAG_WriteIR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_PROGRAM);       //sir (10, 0x196);  // ISC_PROGRAM
  MDR_JTAG_SendCyclesTCK(1);                                                //srun(1);
  MDR_Delay(_5576RC_Delays.ticks_prog_200ns);                                    //delay_dwt(300)  
}

void MDR_5576RC1U_ProgNextData(uint32_t data)
{ 
  MDR_JTAG_WriteDR(MDR_5576RC_PROG_DATA_LEN, data);
  MDR_JTAG_SendCyclesTCK(1);
  MDR_Delay(_5576RC_Delays.ticks_prog_200ns);  
}

void MDR_5576RC1U_ReadStart(uint32_t startAddr)
{  
//  MDR_JTAG_WriteIR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_ENABLE);          //59sir (10, 0x44);//ISC_ENABLE
//  MDR_JTAG_SendCyclesTCK(2);                                                  //srun(2);
//  MDR_Delay(_5576RC_Delays.ticks_1ms);                                        //delay_dwt(1000);

  //  MDR_JTAG_WriteIR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_ADDRESS_SHIFT);   //sir (10, 0x10e);  // ISC_ADDRESS_SHIFT
//  MDR_JTAG_WriteDR(MDR_5576RC_ADDR_LEN, startAddr);
//  MDR_JTAG_SendCyclesTCK(5);                                                  //srun(5);
//  MDR_Delay(_5576RC_Delays.ticks_1ms);                                        //delay_dwt(1000);
  
  MDR_5576RC1U_Enable();
  MDR_5576RC1U_SetAddr(startAddr);
  
  MDR_JTAG_WriteIR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_READ);            //sir (10, 0x196);  // ISC_PROGRAM
  MDR_JTAG_SendCyclesTCK(1);                                                  //srun(1);
  MDR_Delay(_5576RC_Delays.ticks_ena_RD_1ms);  
}

uint32_t MDR_5576RC1U_ReadNextDataCRC(void)
{
  return  MDR_JTAG_ReadDR(MDR_5576RC_RD_DATA_CRC_LEN);  
}

static inline void MDR_5576RC_FlowEnableX(void) 
{
  MDR_JTAG_IR_WriteDR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_ENABLE, MDR_5576RC_ENA_LEN, MDR_5576RC_ENA_MSK);
  MDR_JTAG_SendCyclesTCK(1);  
  MDR_Delay(_5576RC_Delays.ticks_ena_RD_1ms);
}

static inline void MDR_5576RC1U_EraseSector(uint32_t sectorAddr)
{
  MDR_JTAG_IR_WriteDR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__ISC_ERASE, MDR_5576RC_ADDR_LEN, sectorAddr);
  MDR_JTAG_SendCyclesTCK(1);  
  MDR_Delay(_5576RC_Delays.ticks_eraseSect_4s);
  
  MDR_5576RC1U_Disable();
  MDR_5576RC_FlowEnableX();
}

void MDR_5576RC1U_Erase(void)
{
  MDR_5576RC1U_EraseSector(MDR_5576RC_ADDR_SECT_0);
  MDR_5576RC1U_EraseSector(MDR_5576RC_ADDR_SECT_1);
  MDR_5576RC1U_EraseSector(MDR_5576RC_ADDR_SECT_2);
  MDR_5576RC1U_EraseSector(MDR_5576RC_ADDR_SECT_3);
  MDR_5576RC1U_EraseSector(MDR_5576RC_ADDR_SECT_4);
  MDR_5576RC1U_EraseSector(MDR_5576RC_ADDR_SECT_5);
  MDR_5576RC1U_EraseSector(MDR_5576RC_ADDR_SECT_6);  
}


uint32_t MDR_5576RC_Read_IDCODE(void)
{  
  MDR_JTAG_IR_WriteDR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__IDCODE, MDR_5576RC_IDCODE_LEN, 0);
  //MDR_JTAG_SendCyclesTCK(1);  
  return MDR_JTAG_ReadDR(MDR_5576RC_IDCODE_LEN);  
}

uint32_t MDR_5576RC1U_CheckBlank(void)
{
  MDR_5576RC1U_ReadStart(MDR_5576RC_DONE_BIT_ADDR);
  
  uint32_t i;
  uint32_t rdData;
  uint32_t errCount = 0;
  
  for (i = MDR_5576RC_DONE_BIT_ADDR; i < MDR_5576RC_DATA_LEN; ++i)
  {
    rdData = MDR_5576RC1U_ReadNextDataCRC();
    if (rdData != MDR_5576RC_DATA_CRC_BLANK)
      ++errCount;
  }
    
  return errCount; 
}

//  --------------- Config Bits --------------------------
void MDR_5576RC1U_ProgCfgBits(void)
{
  MDR_5576RC1U_ProgStart(MDR_5576RC_DONE_BIT_ADDR);
  uint32_t i;
  for (i = 0; i < _5576RC1U_CfgBits_Len; ++i)
    MDR_5576RC1U_ProgNextData(_5576RC1U_CfgBits[i]);
}

bool MDR_5576RC1U_CheckDoneBit(void)
{
  MDR_5576RC1U_ReadStart(MDR_5576RC_DONE_BIT_ADDR);
  uint32_t rdData = MDR_5576RC1U_ReadNextData();
  return ((rdData & MDR_5576RC_DONE_BIT_OK) == 0);
}

void MDR_5576RC1U_SentInitConfig(void)
{
  MDR_JTAG_WriteIR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__INIT_CONF);
  MDR_JTAG_SendCyclesTCK(1);
}

