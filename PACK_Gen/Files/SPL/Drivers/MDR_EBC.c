#include <MDR_EBC.h>

void MDR_EBC_EnableRegion(MDR_EBC_RGN_Type *EBC_RGN, const MDR_EBC_RGN_CfgRegs *cfg)
{
  EBC_RGN->ECC_BASE = cfg->ECC_BASE;
  EBC_RGN->CS       = cfg->CS     | MDR_EBC_CLR_STATUS_ALL;
  EBC_RGN->CNTR     = cfg->CNTR   | MDR_EBC_CNTR_EN_Msk;  
}
