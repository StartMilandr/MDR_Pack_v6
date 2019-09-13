#ifndef MDR_CONFIG_H
#define MDR_CONFIG_H

#if defined (USE_MDR1986VE91) || defined (USE_MDR1986VE92) || defined (USE_MDR1986VE93) || defined (USE_MDR1986VE94)
  #define USE_MDR1986VE9x
#endif

#if   defined (USE_MDR1986VE1)
  #include <MDR_ConfigVE1.h>
#elif defined (USE_MDR1986VE3)
  #include <MDR_ConfigVE3.h>
#elif defined (USE_MDR1986VE4)
  #include <MDR_ConfigVE4.h>
#elif defined (USE_MDR1986VE9x)
  #include <MDR_ConfigVE9x.h> 
#elif defined (USE_MDR1901VC1)
  #include <MDR_ConfigVC1.h>
#elif defined (USE_MDR1986VK214)
  #include <MDR_ConfigVK214.h>  
#elif defined (USE_MDR1986VK234)
  #include <MDR_ConfigVK234.h>    
#elif defined (USE_MDR1986VE8)
  #include <MDR_ConfigVE8.h>  
#elif defined (USE_MDR1986VE81)
  #include <MDR_ConfigVE81.h>
#elif defined (USE_MDR1923VK014)
  #include <MDR_ConfigVK014.h>    
#elif defined (USE_ESila)
  #include <MDR_ConfigESila.h>
#endif



// ===========   Аттрибут для расположения кода в исполняемой памяти - для DMA и контроллера EEPROM   ============
#if defined ( __ICCARM__ )
  #define __RAM_EXEC    IAR_SECTION ("EXECUTABLE_MEMORY_SECTION")
#else
  #define __RAM_EXEC    __attribute__((section("EXECUTABLE_MEMORY_SECTION")))
#endif



#endif  //  MDR_CONFIG_H
