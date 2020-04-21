#ifndef MDRD_BOARDSELECT_H
#define MDRD_BOARDSELECT_H

//===============   Выбор демоплаты для проекта ==========


//  Здесь будут выбираться ревизии отладочных плат
#if   defined (USE_MDR1986VE1)
  #define USE_BOARD_VE1
#elif defined (USE_MDR1986VE3)
  #define USE_BOARD_VE3
#elif defined (USE_MDR1986VE4)
  #define USE_BOARD_VE4 
#elif defined (USE_MDR1986VE91)
  #define USE_BOARD_VE91
#elif defined (USE_MDR1986VE92)
  #ifdef USE_BASIS
    #define USE_BOARD_BASIS
  #else
    #define USE_BOARD_VE92
  #endif
#elif defined (USE_MDR1986VE93)
  #define USE_BOARD_VE93
#elif defined (USE_MDR1986VE94)
  #define USE_BOARD_VE91
#elif defined (USE_MDR1901VC1)
  #define USE_BOARD_VC1
#elif defined (USE_MDR1986VK214)
  #define USE_BOARD_VK214
#elif defined (USE_MDR1986VK234)
  #define USE_BOARD_VK234   
#elif defined (USE_MDR1986VE8) || defined (USE_MDR1986VE81)
  #define USE_BOARD_VE8
#elif defined (USE_MDR1923VK014)
  #define USE_BOARD_VK014   
#elif defined (USE_MLDR155)
  #define USE_BOARD_MLDR155     
#elif defined (USE_ESila)
  #define USE_BOARD_ESila   

#endif



//===============   Подключение определений ресурсов для демоплат ==========


#if defined ( USE_BOARD_VE91 )  || defined ( USE_BOARD_VE94 )

  #include "MDRB_1986VE91.h"
   
#elif defined (USE_BOARD_BASIS)

  #include <MDRB_Basis_v2.h>

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

  #include "MDRB_1901VC1.h"
  
#elif defined ( USE_BOARD_VK214 )

  #include "MDRB_1986VK214.h"

#elif defined ( USE_BOARD_VK234 ) 

  #include "MDRB_1986VK234.h"  

#elif defined ( USE_BOARD_VE8 ) 

  #include "MDRB_1986VE8.h"  
  
#elif defined ( USE_BOARD_VK014 ) 

  #include "MDRB_1923VK014.h"    
  
#elif defined ( USE_BOARD_MLDR155 ) 

  #include "MDRB_MLDR155.h"  
  
#elif defined ( USE_BOARD_ESila ) 

  #include "MDRB_ESila.h"      

#endif


#endif  //  MDRD_BOARDSELECT_H
