#ifndef MDR_RST_CLOCK_H
#define MDR_RST_CLOCK_H

#include <MDR_Config.h>

#ifdef  MDR_CLK_LIKE_VE8
  #include <MDR_RST_Clock_VE8x.h>
#else
  #include <MDR_RST_Clock_VEx.h>
#endif


#endif //MDR_RST_CLOCK_H
