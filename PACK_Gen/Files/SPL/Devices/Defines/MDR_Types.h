#ifndef _MDR_TYPES_H
#define _MDR_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Определены в core_cmX.h, если не хватает подлючить MDR_Config.h раньше чем MDR_Type.h
//#ifndef __I
//  #ifdef __cplusplus
//    #define   __I     volatile             /*!< Defines 'read only' permissions */
//  #else
//    #define   __I     volatile const       /*!< Defines 'read only' permissions */
//  #endif
//#endif
//#ifndef __O
//  #define     __O     volatile             /*!< Defines 'write only' permissions */
//#endif
//#ifndef __IO
//  #define     __IO    volatile             /*!< Defines 'read / write' permissions */
//#endif
//#ifndef __IM                               /*! Defines 'read only' structure member permissions */
//  #define __IM   __I
//#endif
//#ifndef __OM                               /*! Defines 'write only' structure member permissions */
//  #define __OM   __O
//#endif
//#ifndef __IOM                              /*! Defines 'read / write' structure member permissions */
//  #define __IOM  __IO
//#endif


 //  Используемые типы функций
typedef void (*pVoidFunc_void)(void);
typedef bool (*pBoolFunc_U32)(uint32_t);
typedef bool (*pBoolFunc_void)(void);

  
//  Общие типы
typedef enum {
  MDR_Off  = 0,
  MDR_On   = 1
} MDR_OnOff;

typedef enum {
  MDR_OFF_INV   = 0,
  MDR_ON_INV    = 1
} MDR_ONOFF_INV;

typedef enum {
  MDR_x1            = 0,
  MDR_x2            = 1,
  MDR_x3            = 2,
  MDR_x4            = 3,
  MDR_x5            = 4,
  MDR_x6            = 5,
  MDR_x7            = 6,
  MDR_x8            = 7,
  MDR_x9            = 8,
  MDR_x10           = 9,
  MDR_x11           = 10,
  MDR_x12           = 11,
  MDR_x13           = 12,
  MDR_x14           = 13,
  MDR_x15           = 14,
  MDR_x16           = 15,
} MDR_MUL_x16;

typedef enum {
  MDR_div1          = 0,
  MDR_div2          = 1
} MDR_DIV_2;

//typedef enum {
//  MDR_PSC_div1      = 0,
//  MDR_PSC_div2      = 1,
//  MDR_PSC_div4      = 2,
//  MDR_PSC_div8      = 3,
//} MDR_PSC_DIV_8;

//  MDR_Div8P - Div up to 8, P - Powered 2
typedef enum {
  MDR_Div8P_div1    = 0,
  MDR_Div8P_div2    = 1,
  MDR_Div8P_div4    = 2,
  MDR_Div8P_div8    = 3,
} MDR_Div8P;

//typedef enum {
//  MDR_CLK_div1      = 0,
//  MDR_CLK_div2      = 8,
//  MDR_CLK_div4      = 9,
//  MDR_CLK_div8      = 10,
//  MDR_CLK_div16     = 11,
//  MDR_CLK_div32     = 12,
//  MDR_CLK_div64     = 13,
//  MDR_CLK_div128    = 14,
//  MDR_CLK_div256    = 15
//} MDR_CLK_DIV_256;

typedef enum {
  MDR_Div256P_div1      = 0,
  MDR_Div256P_div2      = 8,
  MDR_Div256P_div4      = 9,
  MDR_Div256P_div8      = 10,
  MDR_Div256P_div16     = 11,
  MDR_Div256P_div32     = 12,
  MDR_Div256P_div64     = 13,
  MDR_Div256P_div128    = 14,
  MDR_Div256P_div256    = 15
} MDR_Div256P;


//typedef enum {
//  MDR_BRG_div1      = 0,
//  MDR_BRG_div2      = 1,
//  MDR_BRG_div4      = 2,
//  MDR_BRG_div8      = 3,
//  MDR_BRG_div16     = 4,
//  MDR_BRG_div32     = 5,
//  MDR_BRG_div64     = 6,
//  MDR_BRG_div128    = 7
//} MDR_BRG_DIV_128;

typedef enum {
  MDR_Div128P_div1      = 0,
  MDR_Div128P_div2      = 1,
  MDR_Div128P_div4      = 2,
  MDR_Div128P_div8      = 3,
  MDR_Div128P_div16     = 4,
  MDR_Div128P_div32     = 5,
  MDR_Div128P_div64     = 6,
  MDR_Div128P_div128    = 7
} MDR_Div128P;



#endif  //_MDR_TYPES_H
