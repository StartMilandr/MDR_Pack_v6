#ifndef MDR_RST_CLOCK_H
#define MDR_RST_CLOCK_H

#include <MDR_Config.h>

  
#if defined (USE_MDR1986VE8) || defined (USE_MDR1986VE81) || defined (USE_MDR1923VK014)
  #include <MDR_RST_Clock_VE8x.h>
#elif defined (USE_ESila) || defined (USE_MLDR155)
  #include <MDR_RST_Clock_ESila.h>    
#else
  #include <MDR_RST_Clock_VEx.h>
#endif


#endif //MDR_RST_CLOCK_H
