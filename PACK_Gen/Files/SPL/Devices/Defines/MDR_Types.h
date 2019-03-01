#ifndef _MDR_TYPES_H
#define _MDR_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef __I
  #ifdef __cplusplus
    #define   __I     volatile             /*!< Defines 'read only' permissions */
  #else
    #define   __I     volatile const       /*!< Defines 'read only' permissions */
  #endif
#endif
#ifndef __O
  #define     __O     volatile             /*!< Defines 'write only' permissions */
#endif
#ifndef __IO
  #define     __IO    volatile             /*!< Defines 'read / write' permissions */
#endif
#ifndef __IM                               /*! Defines 'read only' structure member permissions */
  #define __IM   __I
#endif
#ifndef __OM                               /*! Defines 'write only' structure member permissions */
  #define __OM   __O
#endif
#ifndef __IOM                              /*! Defines 'read / write' structure member permissions */
  #define __IOM  __IO
#endif



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

typedef enum {
  MDR_PSC_div1      = 0,
  MDR_PSC_div2      = 1,
  MDR_PSC_div4      = 2,
  MDR_PSC_div8      = 3,
} MDR_PSC_DIV_8;

typedef enum {
  MDR_CLK_div1      = 0,
  MDR_CLK_div2      = 8,
  MDR_CLK_div4      = 9,
  MDR_CLK_div8      = 10,
  MDR_CLK_div16     = 11,
  MDR_CLK_div32     = 12,
  MDR_CLK_div64     = 13,
  MDR_CLK_div128    = 14,
  MDR_CLK_div256    = 15
} MDR_CLK_DIV_256;

typedef enum {
  MDR_BRG_div1      = 0,
  MDR_BRG_div2      = 1,
  MDR_BRG_div4      = 2,
  MDR_BRG_div8      = 3,
  MDR_BRG_div16     = 4,
  MDR_BRG_div32     = 5,
  MDR_BRG_div64     = 6,
  MDR_BRG_div128    = 7
} MDR_BRG_DIV_128;

#define MDR_BRG_DIV_128_CLR   0x00FFUL

typedef enum {
  MDR_HSIE2_HSI             = 0,    //HSI
  MDR_HSIE2_HSI_div2        = 1,    //HSI/2
  MDR_HSIE2_HSE             = 2,    //HSE
  MDR_HSIE2_HSE_div2        = 3     //HSE/2
} MDR_CLK_SEL_HSIE2;

typedef enum {
  MDR_CPU_C1                = 0,    //CPU_C1
  MDR_CPU_PLL               = 1     //PLLCPUo
} MDR_CLK_SEL_CPU;

typedef enum {
  MDR_HCLK_HSI               = 0,
  MDR_HCLK_CPU_C3            = 1,
  MDR_HCLK_LSE               = 2,
  MDR_HCLK_LSI               = 3
} MDR_CLK_SEL_HCLK;

typedef enum {
  MDR_USB_C1                = 0,    //CPU_C1
  MDR_USB_PLL               = 1     //PLLCPUo
} MDR_CLK_SEL_USB;

typedef enum {
  MDR_LSIE2_LSI              = 0,
  MDR_LSIE2_LSI_div2         = 1,
  MDR_LSIE2_LSE              = 2,
  MDR_LSIE2_LSE_div2         = 3
} MDR_CLK_SEL_LSIE2;

typedef enum {
  MDR_PER_CPU_C1            = 0,
  MDR_PER_PER1_C1           = 1,
  MDR_PER_PLLCPUo           = 2,
  MDR_PER_HSI_C1            = 3
} MDR_CLK_SEL_PER;

typedef enum {
  MDR_ADC_C1_CPU_C1         = 0,
  MDR_ADC_C1_USB_C1         = 1,
  MDR_ADC_C1_CPU_C2         = 2,
  MDR_ADC_C1_USB_C2         = 3
} MDR_CLK_ADC_C1;

typedef enum {
  MDR_ADC_C2_LSE            = 0,
  MDR_ADC_C2_LSI            = 1,
  MDR_ADC_C2_ADC_C1         = 2,
  MDR_ADC_C2_HSI_C1         = 3
} MDR_CLK_ADC_C2;

typedef enum {
  MDR_AUC_C2_AUC_C1          = 0,
  MDR_AUC_C2_PLLCPUo         = 1,
  MDR_AUC_C2_PLLUSBo         = 2,
  MDR_AUC_C2_Zero            = 3
} MDR_CLK_AUC_C2;

typedef enum {
  MDR_DSP_C1                = 0,     //DSP_C1
  MDR_DSP_PLL               = 1     //PLLDSPo
} MDR_CLK_SEL_DSP;

typedef enum {
  MDR_PHY_HSI               = 0,
  MDR_PHY_HSE               = 1,
  MDR_PHY_PLLCPUo           = 2,
  MDR_PHY_HSE2              = 3
} MDR_CLK_SEL_PHY;

typedef enum {
  MDR_WORK                  = 0,
  MDR_RESET                 = 1
} MDR_RESET_STATE;

typedef enum {
  MDR_STOP                  = 0,
  MDR_RUN                   = 1
} MDR_RUN_STATE;

typedef enum {
  MDR_BRTRD_TRANSFER                  = 0,
  MDR_BRTRD_COMPLETED                 = 1
} MDR_RST_DSP_BRTRD;

typedef enum {
  MDR_DSP_ON                  = 0,
  MDR_DSP_OFF                 = 1,
  MDR_DSP_MEM_OFF             = 2,
  MDR_DSP_MEM_PERIF_OFF       = 3
} MDR_RST_DSP_IDLE;

#endif  //_MDR_TYPES_H
