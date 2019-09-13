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
  void MDR_OTPSRAM_ProgWordWord(uint32_t addr, uint32_t data) 
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
  
#endif
