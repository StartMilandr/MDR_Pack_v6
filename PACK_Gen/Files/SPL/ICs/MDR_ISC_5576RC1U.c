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

//=========================     NEW API ===========================
static inline void MDR_5576RC1U_Enable(void)
{  
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

//  --------------- for debug --------------------------
#define MDR_JTAG_IR__5576RC1U_PROG_AA55   0x62

void MDR_5576RC1U_ProgDebud_AA55(void)
{
  MDR_JTAG_WriteIR(MDR_JTAG_INSTR_BIT_LEN, MDR_JTAG_IR__5576RC1U_PROG_AA55);
  MDR_JTAG_SendCyclesTCK(1);
}
