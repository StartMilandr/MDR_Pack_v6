#ifndef _MDR_PER_CLOCK_H
#define _MDR_PER_CLOCK_H

#include <MDR_Config.h>

  
//#if defined (USE_MDR1986VE8) || defined (USE_MDR1923VK014) || defined (USE_ESila)
#ifdef MDR_CLK_LIKE_VE8
  #include <MDR_PER_ClockVE8x.h>
#else
  #include <MDR_PER_ClockVEx.h>
#endif
  
#endif  // _MDR_PER_CLOCK_H

