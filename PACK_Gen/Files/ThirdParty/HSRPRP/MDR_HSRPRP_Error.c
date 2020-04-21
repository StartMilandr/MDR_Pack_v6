#include "MDR_HSRPRP_Error.h"

void MDR_HSR_LogError(MDR_HSR_ErrorID errID, uint32_t tag)
{
  switch (errID) 
  {
    case MDR_HSR_Err_WrongLanID:
    {
      //  tag = selPortMask
      //  #define MDR_HSR_SEL_PORT_A             (0x1UL << MDR_HSR_ForwPortA)
      //  #define MDR_HSR_SEL_PORT_B             (0x1UL << MDR_HSR_ForwPortB)
      //  #define MDR_HSR_SEL_INTERLINK          (0x1UL << MDR_HSR_ForwInterlink)
      //  #define MDR_HSR_PROC_LINK_LAYER        (0x1UL << MDR_HSR_ForwInterlink)
      
      break;
    }
		default: {}
  }
}
