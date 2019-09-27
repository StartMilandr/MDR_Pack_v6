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

unsigned int GetECC(uint32_t data,  uint32_t adr)
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
   return ecc;
}

#ifdef USE_MDR1986VE81
  void MDR_OTPSRAM_ProgWord(uint32_t addr, uint32_t data) 
  {
    uint32_t ctrl = GetECC(data, addr) << MDR_OTP_CNTR_WECC_Pos;
    ctrl |= MDR_OTP_CNTR_WAITCYCL_SRAM_Min | MDR_OTP_CNTR_CLK_Msk | MDR_OTP_CNTR_REG_ACCESS_Msk; // MDR_OTP_CNTR_CEN_Msk

    MDR_OTP->ADR = addr;
    MDR_OTP->WDATA = data;
    MDR_OTP->CNTR = ctrl;
    ctrl |= MDR_OTP_CNTR_WE_ALL_Msk;
    MDR_OTP->CNTR = ctrl;
    ctrl &= ~(MDR_OTP_CNTR_CLK_Msk | MDR_OTP_CNTR_REG_ACCESS_Msk);
    MDR_OTP->CNTR = ctrl;
  }
#else  

  //  Memory must be in ReadMode! CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_SE_Msk;
  static void MDR_OTP_ProgWordOneCycle(uint32_t wrAddr, uint32_t wrData, uint32_t wrECC) 
  {
    uint32_t i40, ib, it, ird;
    uint32_t rdData, rdECC;
    uint32_t bitMsk;
    bool bitReady;  

    //  Read Active Data and ECC
    rdData = MDR_OTP->RDATA;
    rdECC = (MDR_OTP->CNTR & MDR_OTP_CNTR_RECC_Msk) >> MDR_OTP_CNTR_RECC_Pos;
    
    //  Select Data's bit '1' to write
    for (ib = 0; ib < 32; ++ib)
    {
      bitMsk = 1 << ib;
      if (((wrData ^ rdData) & bitMsk) != 0)
      {
        //  Try Write Bit up to 30 times
        bitReady = false;
        for (it = 0; it < 30; ++it)
        {
          //  Write Mode
          MDR_OTP->CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk;	
          MDR_OTP->CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_PE_Msk;	
                                    
          MDR_OTP->ADR   = wrAddr;
         // for (y=0;y<1000;y++) {}; // delay 1000 us
          MDR_OTP->WDATA = wrData & bitMsk; 
         // for (y=0;y<5000;y++) {}; // delay 3000 us
          MDR_OTP->WDATA = 0;
          
          //  Read Mode
          MDR_OTP->CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk;	
          MDR_OTP->CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_SE_Msk;	

          for (ird = 0; ird < 5; ++ird)
          {	
            bitReady = (MDR_OTP->RDATA & bitMsk) == bitMsk;
            if(bitReady) 
              break;                  
          }
          
          if(bitReady) 
            break;
        }
      }      
    }

    //  Select Data's bit '1' to write
    for (ib = 0; ib < 8; ++ib)
    {
      bitMsk = 1 << ib;
      if (((wrECC ^ rdECC) & bitMsk) != 0)
      {
        //  Try Write Bit up to 30 times
        bitReady = false;
        for (it = 0; it < 30; ++it)
        {
          //  Write Mode
          MDR_OTP->CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk;	
          MDR_OTP->CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_PE_Msk;
                                    
          MDR_OTP->ADR   = wrAddr;
         // for (y=0;y<1000;y++) {}; // delay 1000 us
          MDR_OTP->CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_PE_Msk | ((wrECC & bitMsk) << MDR_OTP_CNTR_WECC_Pos);
         // for (y=0;y<5000;y++) {}; // delay 3000 us
          MDR_OTP->CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_PE_Msk;
          
          //  Read Mode
          MDR_OTP->CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk;	
          MDR_OTP->CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_SE_Msk;	

          for (ird = 0; ird < 5; ++ird)
          {	
            bitReady = ((MDR_OTP->CNTR >> MDR_OTP_CNTR_WECC_Pos) & bitMsk) == bitMsk;
            if(bitReady) 
              break;                  
          }
          
          if(bitReady) 
            break;
        }
      }
    }
  }

  void MDR_OTPSRAM_ProgWord(uint32_t addr, uint32_t data) 
  {
    uint32_t i40, ib, it, ird;
    uint32_t rdData, rdECC;
    uint32_t bitMsk;
    bool bitReady;
    uint32_t wrECC = GetECC(data, addr);// << MDR_OTP_CNTR_WECC_Pos;
    //ctrl |= MDR_OTP_CNTR_WAITCYCL_SRAM_Min | MDR_OTP_CNTR_CLK_Msk | MDR_OTP_CNTR_REG_ACCESS_Msk; // MDR_OTP_CNTR_CEN_Msk    
		
	  MDR_OTP->TUNING = MDR_OTP_TUNING_OTP_Time_Hard1_Msk | MDR_OTP_TUNING_OTP_Repl_HardMax_Msk;		
	
	

	//--------------------------------------------------------------------------------------------------------------------------------------------------
		MDR_OTP->ADR = addr;
		//for (y=0;y<1000;y++) {}; // delay 1000 us      
    MDR_OTP->CNTR = MDR_OTP_CNTR_REG_ACCESS_Msk | MDR_OTP_CNTR_SE_Msk;
//      
//		readdataotp = OTP_CNTR->RDATA;
//		readeccotp = (OTP_CNTR->CNTR & (0xFF000000))>>24;    
//    rdData = MDR_OTP->RDATA;
//    rdECC = (MDR_OTP->CNTR & MDR_OTP_CNTR_RECC_Msk) >> MDR_OTP_CNTR_RECC_Pos;
    
    for (i40 = 0; i40 < 40; ++i40)
    {

    }
    
//			//Light();
//				for(cycl=0;cycl<40;cycl++){					
//					//*********************************************************************************************************************************			
//				for (i_w=0;i_w<32;i_w++)//32
//				{
//					
//					DATAbit = DATA & (1<<i_w);
//					readdataotp_bit = readdataotp & (1<<i_w);
//				
//							//-------------------------------------
//							if(DATAbit!=readdataotp_bit)
//							//-------------------------------------
//							{	
//								//Lightl();

//								if(readdataotp_bit==(1<<i_w)) 
//								{
//									while(1);
//								}
//								
//							
//													for(i_p=0;i_p<30;i_p++){
//														
//														OTP_CNTR->CNTR = 0<<0 | 1<<4   | 0<<5 | 0<<6 | 0<<7 | 0<<8 | 0<<9 |0<<14| 0<<16|  0<<24   ; // Enable REG access	
//														
//														OTP_CNTR->CNTR = 0<<0 | 1<<4   | 0<<5 | 1<<6 | 0<<7 | 0<<8 | 0<<9 |0<<14| 0<<16|  0<<24   ; // Enable REG access															
//																											
//														//......................wr........................
//														OTP_CNTR->ADR     =	ADR;
//														for (y=0;y<1000;y++) {}; // delay 1000 us
//														OTP_CNTR->WDATA   = DATA & (1<<i_w); 
//														for (y=0;y<5000;y++) {}; // delay 3000 us
//														OTP_CNTR->WDATA   = 0; 
//														//................................................			
//														
//														OTP_CNTR->CNTR = 0<<0 | 1<<4 | 0<<5 | 0<<6 | 0<<7 | 0<<8 | 0<<9 | 0<<14 | 0<<16 | 0<<24 ; // Disable REG access	
//															
//														OTP_CNTR->CNTR = 0<<0 | 1<<4 | 1<<5 | 0<<6 | 0<<7 | 0<<8 | 0<<9 | 0<<14 | 0<<16 | 0<<24 ; // Disable REG access

//																	for (i_r=0;i_r<5;i_r++)	{	
//																																									
//																				//dat = OTP_CNTR->RDATA;
//																		
//																				zero_d = (OTP_CNTR->RDATA) & (1<<i_w);
//																				
//																				if(zero_d==DATAbit) break;

//																				
//																	}
//														if(zero_d==DATAbit) break;									
//														}//for
//									
//								}
//				}
//				//*********************************************************************************************************************************	
//				
//				
//			// *********************Write ECC**********************
//				for (i_w=0;i_w<8;i_w++)
//				{
//					
//					SECCbit = SECC & (1<<i_w);
//					
//					readeccotp_bit = readeccotp & (1<<i_w);
//					
//					if(SECCbit!=readeccotp_bit)
//					{
//					//	Lighth();
//					if(readeccotp_bit==(1<<i_w))
//					{
//						while(1);
//					}						

//					for(i_p=0;i_p<30;i_p++){

//						OTP_CNTR->CNTR = 0<<0 | 1<<4 | 0<<5 | 0<<6 | 0<<7 | 0<<8 | 0<<9 |0<<14| 0<<16|  0<<24   ; // Enable REG access							
//						
//						OTP_CNTR->CNTR = 0<<0 | 1<<4 | 0<<5 | 1<<6 | 0<<7 | 0<<8 | 0<<9 |0<<14| 0<<16|  0<<24   ; // Enable REG access	
//									
//						//......................wr........................			
//						OTP_CNTR->ADR     =	ADR;
//						for (y=0;y<1000;y++) {}; // delay 1000 us
//						OTP_CNTR->CNTR = 0<<0 | 1<<4   | 0<<5 | 1<<6 | 0<<7 | 0<<8 | 0<<9 |0<<14| (SECC & (1<<i_w))<<16|  0<<24   ; // Enable REG access
//						for (y=0;y<5000;y++) {}; // delay 3000 us
//						OTP_CNTR->CNTR = 0<<0 | 1<<4   | 0<<5 | 1<<6 | 0<<7 | 0<<8 | 0<<9 |0<<14| 0 <<16 |  0<<24   ; // Enable REG access
//						//................................................			
//					
//						OTP_CNTR->CNTR = 0<<0 | 1<<4 | 0<<5 | 0<<6 | 0<<7 | 0<<8 | 0<<9 | 0<<14 | 0<<16 | 0<<24 ; // Disable REG access				
//						
//						OTP_CNTR->CNTR = 0<<0 | 1<<4 | 1<<5 | 0<<6 | 0<<7 | 0<<8 | 0<<9 | 0<<14 | 0<<16 | 0<<24 ; // Disable REG access


//																				for (i_r=0;i_r<5;i_r++)	{	
//																					
//																							zero_d = (OTP_CNTR->CNTR & (0xFF000000))>>24;
//																												
//																							zero_d_bit = zero_d & (1<<i_w);
//																							
//																							if(zero_d_bit==SECCbit) break;

//																							
//																				}		
//							if(zero_d_bit==SECCbit) break;
//							//if(i_p>12) Light();																	
//							}//for
//							
//						}
//							
//				}
//			}//for cycl	    
//    
    
    
//    uint32_t ctrl = GetECC(data, addr) << MDR_OTP_CNTR_WECC_Pos;
//    ctrl |= MDR_OTP_CNTR_W AITCYCL_SRAM_Min | MDR_OTP_CNTR_CLK_Msk | MDR_OTP_CNTR_REG_ACCESS_Msk; // MDR_OTP_CNTR_CEN_Msk

//    MDR_OTP->ADR = addr;
//    MDR_OTP->WDATA = data;
//    MDR_OTP->CNTR = ctrl;
//    ctrl |= MDR_OTP_CNTR_WE_ALL_Msk;
//    MDR_OTP->CNTR = ctrl;
//    ctrl &= ~(MDR_OTP_CNTR_CLK_Msk | MDR_OTP_CNTR_REG_ACCESS_Msk);
//    MDR_OTP->CNTR = ctrl;
  }
  
#endif
