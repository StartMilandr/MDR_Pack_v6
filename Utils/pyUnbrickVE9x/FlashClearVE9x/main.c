#include <MDR_EEPROM.h>

int main(void)
{
  MDR_EEPROM_Init(HSI_FREQ_HZ);  
  MDR_EEPROM_EraseFull(EEPROM_EraseFull_Main);
  MDR_EEPROM_Finit();
  
  while (1);  
}
