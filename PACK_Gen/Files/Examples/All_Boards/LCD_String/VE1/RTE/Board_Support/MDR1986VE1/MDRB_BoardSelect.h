#ifndef MDRD_BOARDSELECT_H
#define MDRD_BOARDSELECT_H

//===============   Выбор демоплаты для проекта ==========
// #define  USE_BOARD_VE91
// #define USE_BOARD_VE94
// #define USE_BOARD_VE92 
// #define USE_BOARD_VE93
 #define USE_BOARD_VE1 
// #define USE_BOARD_VE3 
// #define USE_BOARD_VE4 
// #define USE_BOARD_VE8 
// #define USE_BOARD_VC1 
// #define USE_BOARD_VK214
// #define USE_BOARD_VK234




//===============   Подключение определений ресурсов для демоплат ==========
#if defined ( USE_BOARD_VE91 )  || defined ( USE_BOARD_VE94 )

  #include "MDRB_1986VE91.h"
   
#elif defined ( USE_BOARD_VE92 )

  #include "MDRB_1986VE92.h"

#elif defined ( USE_BOARD_VE93 )

  #include "MDRB_1986VE93.h"

#elif defined ( USE_BOARD_VE1 )

  #include "MDRB_1986VE1.h"

#elif defined ( USE_BOARD_VE3 )

  #include "MDRB_1986VE3.h"

#elif defined ( USE_BOARD_VE4 ) 

  #include "MDRB_1986VE4.h"

#elif defined ( USE_BOARD_VE8 )

  #include "MDRB_1986VE8.h"
  
#elif defined ( USE_BOARD_VC1 )

  #include "MDRB_1986VC1.h"
  
#elif defined ( USE_BOARD_VK214 )

  #include "MDRB_1986VK214.h"

#elif defined ( USE_BOARD_VK234 ) 

  #include "MDRB_1986VK234.h"  

#endif

#endif  //  MDRD_BOARDSELECT_H
