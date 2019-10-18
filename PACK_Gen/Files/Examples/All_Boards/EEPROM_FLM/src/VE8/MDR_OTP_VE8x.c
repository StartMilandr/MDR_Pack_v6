#include <MDR_OTP_VE8x.h>

//  Реализация от Vasili с форума - http://forum.milandr.ru/viewtopic.php?p=20531#p20531
const uint32_t H[12] = {
  0x08099264,
  0xC8080992,
  0x38C80809,
  0x0738C808,
  0xFF0738C8,
  0x64FF0738,
  0x9264FF07,
  0x099264FF,
  0x08099264,
  0xC8080992,
  0x38C80809,
  0x0738C808
};

uint8_t MDR_GetECC(uint32_t data,  uint32_t adr)
{
  uint32_t* ptr_H;
  int i1;   
  uint32_t res;
  uint32_t ecc;

   ecc = 0;
   ptr_H = (unsigned int*)(&H);
   i1 = 8;
   do
   {
      res = *ptr_H;
      res &= data;
      res ^= *(ptr_H + 4) & adr;
      ptr_H ++;
      res ^= res << 16;
      res ^= res << 8;
      res ^= res << 4;
      res ^= res << 2;
      res ^= res << 1;
      res >>= 31;
      i1--;
      res <<= i1;
      ecc |= res;
   }
   while(i1);
   return (uint8_t)ecc;
}

#ifdef USE_MDR1986VE81
//=================================   1986VE81  SRAM ===============================
  //  Реализация от того-же Vasili
  void MDR_OTPSRAM_ProgWord(uint32_t addr, uint32_t data) 
  {
    uint32_t ctrl = GetECC(data, addr) << MDR_OTP_CNTR_WECC_Pos;
    ctrl |= MDR_OTP_CNTR_WAITCYCL_SRAM_Min | MDR_OTP_CNTR_CLK_Msk | MDR_OTP_CNTR_REG_ACCESS_Msk;

    MDR_OTP->ADR = addr;
    MDR_OTP->WDATA = data;
    MDR_OTP->CNTR = ctrl;
    ctrl |= MDR_OTP_CNTR_WE_ALL_Msk;
    MDR_OTP->CNTR = ctrl;
    ctrl &= ~(MDR_OTP_CNTR_CLK_Msk | MDR_OTP_CNTR_REG_ACCESS_Msk);
    MDR_OTP->CNTR = ctrl;
  }


#else  

//=================================   1986VE8T  OTP ===============================

  static MDR_OTP_ProgDelays _progDelays;

  MDR_OTP_ProgDelays MDR_OTP_GetProgDelays(uint32_t freqCPU_Hz)
  {
    MDR_OTP_ProgDelays delays;

    delays.delay_HV_PE = US_TO_DELAY_LOOPS(MDR_OTP_DELAY_US_HV_PE, freqCPU_Hz);
    delays.delay_A_D = US_TO_DELAY_LOOPS(MDR_OTP_DELAY_US_A_D,   freqCPU_Hz);
    delays.delay_Prog = US_TO_DELAY_LOOPS(MDR_OTP_DELAY_US_PROG,  freqCPU_Hz);
    return delays;
  }
  
  //  Подготовка к програамированию и финализация после его окончания - переключение DUcc
  void MDR_OTP_ProgBegin(const MDR_OTP_ProgDelays *progDelays)  
  { 
    _progDelays = *progDelays;
    
    MDR_BKP_SetTrimLDO_Min();
    MDR_Delay(_progDelays.delay_HV_PE);
    //  Разрешение вывода последних ошибок в регистры ECCADR, ECCDATA, ECCECC
    MDR_OTP->ECCCS |= MDR_OTP_ECCCS_FIX_DECC_Msk | MDR_OTP_ECCCS_FIX_SECC_Msk | MDR_OTP_ECCCS_CLR_SECNT_Msk | MDR_OTP_ECCCS_CLR_DECNT_Msk;
    // Реплики затрудняющие чтение единицы
	  MDR_OTP->TUNING = MDR_OTP_TUNING_OTP_Time_Hard1_Msk | MDR_OTP_TUNING_OTP_Repl_HardMax_Msk;
  }

  void MDR_OTP_ProgEnd(void) 
  { 
    MDR_BKP_SetTrimLDO_Def(); 
    MDR_OTP->TUNING = MDR_OTP_TUNING_OTP_Time_Norm_Msk | MDR_OTP_TUNING_OTP_Repl_Norm_Msk;
    MDR_Delay(_progDelays.delay_HV_PE);
  }

  
  #define WRITE_TRY_COUNT   30
  #define READ_TRY_COUNT    5

  static bool MDR_OTP_ProgCycle_DataBit(uint32_t wrAddr, uint32_t wrOneBitMask)
  {
    uint32_t i, j;
    bool result;
    
    //  Try Write Bit up to 30 times
    for (i = 0; i < WRITE_TRY_COUNT; ++i)
    {
      //  Prog Mode On
      MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk;	
      MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_PE_Msk;	
                                
      MDR_OTP->ADR   = wrAddr;
      MDR_Delay(_progDelays.delay_A_D);
      MDR_OTP->WDATA = wrOneBitMask; 
      MDR_Delay(_progDelays.delay_Prog);
      MDR_OTP->WDATA = 0;

      //  Prog Off
      MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk;	
      MDR_Delay(_progDelays.delay_A_D);
      
      //  Read Mode On
      MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_SE_Msk;	
      result = true;
      for (j = 0; j < READ_TRY_COUNT; ++j)
      {	
        result = result && ((MDR_OTP->RDATA & wrOneBitMask) != 0);
        if (!result) 
          break;                
      }
      if (result)
        break;
    }
    //  Read Mode Off
    MDR_OTP->CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk;
    return result;
  }
  
  static bool MDR_OTP_ProgCycle_ECCBit(uint32_t wrAddr, uint8_t wrOneBitMask)
  {
    uint32_t i, j;
    bool result;  

    //  Try Write Bit up to 30 times
    for (i = 0; i < WRITE_TRY_COUNT; ++i)
    {
      //  Prog Mode On
      MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk;	
      MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_PE_Msk;
                                
      MDR_OTP->ADR   = wrAddr;
      MDR_Delay(_progDelays.delay_A_D);
      MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_PE_Msk | ((uint32_t)wrOneBitMask  << MDR_OTP_CNTR_WECC_Pos);
      MDR_Delay(_progDelays.delay_Prog);
      MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_PE_Msk;
      
      //  Prog Mode Off
      MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk;
      MDR_Delay(_progDelays.delay_A_D);
      
      //  Read Mode On
      MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_SE_Msk;
      
      result = true;
      for (j = 0; j < READ_TRY_COUNT; ++j)
      {	
        result = result && (((MDR_OTP->CNTR >> MDR_OTP_CNTR_RECC_Pos) & wrOneBitMask) != 0);
        if(!result) 
          break;                  
      }      
      if (result)
        break;
    }    
    //  Read Mode Off
    MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk;
    return result;
  }  


  //  Возвращает FALSE если брак, т.е. бит который должен быть 0, читается как 1. (Например, уже был записан или это брак)
  static bool MDR_OTP_ProgWordOneCycle(uint32_t wrAddr, uint32_t wrData, uint32_t wrECC) 
  {
    uint32_t i;
    uint32_t rdData, rdECC;
    uint32_t bitMsk;
    bool result = true;
    uint32_t tempCtrl = MDR_OTP->CNTR & MDR_OTP_CNTR_WAITCYCL_Msk;

    //  Set Addr and ReadMode and Read Data
    MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk;
		MDR_OTP->ADR = wrAddr;
		//MDR_Delay(_progDelays.delay_A_SE); - 5ns (200MHz) too small
    MDR_OTP->CNTR = MDR_OTP_CNTR_WAITCYL_MIN | MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_SE_Msk;   
    rdData = MDR_OTP->RDATA;
    
    //  ----  WRITE DATA BITS '1' -----
    for (i = 0; i < 32; ++i)
    {
      bitMsk = 1 << i;
           
      if (((wrData ^ rdData) & bitMsk) != 0)
      {
        if ((wrData & bitMsk) != 0)
        {
          MDR_OTP_ProgCycle_DataBit(wrAddr, bitMsk);
          rdData = MDR_OTP->RDATA;
        }
        else
        {  
          result = false;  //  Return Data Fault
          break;
        }
      }
    }
   
    //  ----  WRITE ECC BITS '1' -----
    rdECC = (MDR_OTP->CNTR & MDR_OTP_CNTR_RECC_Msk) >> MDR_OTP_CNTR_RECC_Pos;
    for (i = 0; i < 8; ++i)
    {
      bitMsk = 1 << i;            
      
      if (((wrECC ^ rdECC) & bitMsk) != 0)
      {
        if ((wrECC & bitMsk) != 0)
        {
          MDR_OTP_ProgCycle_ECCBit(wrAddr, bitMsk);
          rdECC = (MDR_OTP->CNTR & MDR_OTP_CNTR_RECC_Msk) >> MDR_OTP_CNTR_RECC_Pos;
        }
        else
        {
          result = false;  //  Return Data Fault
          break;
        }
      }      
    }
    
    MDR_OTP->CNTR = tempCtrl;    
    return result;
  }

  //  RETURN
  //    true  - алгоритм отработал полностью
  //    false - брак
  bool MDR_OTP_ProgWordAndEccEx(uint32_t addr, uint32_t data, uint8_t ecc, uint32_t cycleCount) 
  {
    uint32_t i;
    bool result = true;
       
    for (i = 0; i < cycleCount; ++i)
    {
      //  Возвращает false в случае брака
      result = MDR_OTP_ProgWordOneCycle(addr, data, ecc);
      if (!result)
        break;
    } 
    
    return result;
  }
  
  bool MDR_OTP_ProgWordEx(uint32_t addr, uint32_t data, uint32_t cycleCount)
  {
    uint32_t wrECC = MDR_GetECC(data, addr);		
    return MDR_OTP_ProgWordAndEccEx(addr, data, wrECC, cycleCount);
  }  
  

  uint32_t MDR_OTP_ReadWord(uint32_t addr)
  {
    uint32_t waitCycle = MDR_OTP->CNTR & MDR_OTP_CNTR_WAITCYCL_Msk;
    
    //  Set Addr and ReadMode and Read Data
    MDR_OTP->CNTR = waitCycle | MDR_OTP_CNTR_REG_ACCESS_Msk;
		MDR_OTP->ADR  = addr;
		//MDR_Delay(_progDelays.delay_A_SE); - 5ns (200MHz) too small
    MDR_OTP->CNTR = waitCycle | MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_SE_Msk;   
    uint32_t result = MDR_OTP->RDATA;  
    
    //  Read Mode Off
    MDR_OTP->CNTR = waitCycle | MDR_OTP_CNTR_REG_ACCESS_Msk;
    MDR_OTP->CNTR = waitCycle;
    
    return result;
  }

  uint32_t MDR_OTP_ReadWordAndEcc(uint32_t addr, uint8_t *rdECC)
  {
    uint32_t waitCycle = MDR_OTP->CNTR & MDR_OTP_CNTR_WAITCYCL_Msk;
    
    //  Set Addr and ReadMode and Read Data
    MDR_OTP->CNTR = waitCycle | MDR_OTP_CNTR_REG_ACCESS_Msk;
		MDR_OTP->ADR  = addr;
		//MDR_Delay(_progDelays.delay_A_SE); - 5ns (200MHz) too small
    MDR_OTP->CNTR = waitCycle | MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_SE_Msk;   
    uint32_t result = MDR_OTP->RDATA;
    *rdECC = (MDR_OTP->CNTR & MDR_OTP_CNTR_RECC_Msk) >> MDR_OTP_CNTR_RECC_Pos;
    
    //  Read Mode Off
    MDR_OTP->CNTR = waitCycle | MDR_OTP_CNTR_REG_ACCESS_Msk;
    MDR_OTP->CNTR = waitCycle;
    
    return result;
  }
  
  bool MDR_OTP_CheckWordEmpty(uint32_t addr)
  {
    uint32_t waitCycle = MDR_OTP->CNTR & MDR_OTP_CNTR_WAITCYCL_Msk;
    
    //  Set Addr and ReadMode and Read Data
    MDR_OTP->CNTR = waitCycle | MDR_OTP_CNTR_REG_ACCESS_Msk;
		MDR_OTP->ADR  = addr;
		//MDR_Delay(_progDelays.delay_A_SE); - 5ns (200MHz) too small
    MDR_OTP->CNTR = waitCycle | MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_SE_Msk;   
    bool result = (MDR_OTP->RDATA == 0);
    result &= ((MDR_OTP->CNTR & MDR_OTP_CNTR_RECC_Msk) == 0UL);
    
    //  Read Mode Off
    MDR_OTP->CNTR = waitCycle | MDR_OTP_CNTR_REG_ACCESS_Msk;
    MDR_OTP->CNTR = waitCycle;
    
    return result;
  }  
  
#endif
