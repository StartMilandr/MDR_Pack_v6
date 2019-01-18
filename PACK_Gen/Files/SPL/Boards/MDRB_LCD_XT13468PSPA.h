#ifndef MDRB_LCD_XT13468PSPA
#define MDRB_LCD_XT13468PSPA

#include <MDR_GPIO.h>
#include <MDRB_LCD.h>
#include <MDR_Funcs.h>
#include <MDR_LCD_VK214.h>

typedef struct {
  uint32_t    s0_Reverse  : 1;
  uint32_t    s1_Tar_1    : 1;
  uint32_t    s2_Num1_F   : 1;
  uint32_t    s3_Num1_A   : 1;
  uint32_t    s4_Num2_F   : 1;
  uint32_t    s5_Num2_A   : 1;
  uint32_t    s6_Num3_F   : 1;
  uint32_t    s7_Num3_A   : 1;
  uint32_t    s8_Num4_F   : 1;
  uint32_t    s9_Num4_A  : 1;
  uint32_t    s10_Num5_F  : 1;
  uint32_t    s11_Num5_A  : 1;
  uint32_t    s12_Num6_F  : 1;
  uint32_t    s13_Num6_A  : 1;
  uint32_t    s14_Num7_F  : 1;
  uint32_t    s15_Num7_A  : 1;
  uint32_t    s16_Num8_F  : 1;
  uint32_t    s17_Num8_A  : 1;  
  uint32_t    s18_var_k   : 1;
  uint32_t    s19_A_plus  : 1;
  uint32_t    s20_W_k     : 1;
  uint32_t    s21_VA_A    : 1;
  uint32_t    s22_Circ_1  : 1;
  uint32_t    s23_Num7_dot: 1;  
  uint32_t    unused      : 8;
} LCD_XT_ROW1_Bits;

typedef struct {
  uint32_t    s0_Tarif  : 1;
  uint32_t    s1_Tar_2    : 1;
  uint32_t    s2_Num1_G   : 1;
  uint32_t    s3_Num1_B   : 1;
  uint32_t    s4_Num2_G   : 1;
  uint32_t    s5_Num2_B   : 1;
  uint32_t    s6_Num3_G   : 1;
  uint32_t    s7_Num3_B   : 1;
  uint32_t    s8_Num4_G   : 1;
  uint32_t    s9_Num4_B  : 1;
  uint32_t    s10_Num5_G  : 1;
  uint32_t    s11_Num5_B  : 1;
  uint32_t    s12_Num6_G  : 1;
  uint32_t    s13_Num6_B  : 1;
  uint32_t    s14_Num7_G  : 1;
  uint32_t    s15_Num7_B  : 1;
  uint32_t    s16_Num8_G  : 1;
  uint32_t    s17_Num8_B  : 1;  
  uint32_t    s18_var_h   : 1;
  uint32_t    s19_A_minus : 1;
  uint32_t    s20_VA_V    : 1;
  uint32_t    s21_var     : 1;
  uint32_t    s22_Circ_2  : 1;
  uint32_t    s23_Lock    : 1;  
  uint32_t    unused      : 8;
} LCD_XT_ROW2_Bits;

typedef struct {
  uint32_t    s0_In       : 1;
  uint32_t    s1_Tar_3    : 1;
  uint32_t    s2_Num1_E   : 1;
  uint32_t    s3_Num1_C   : 1;
  uint32_t    s4_Num2_E   : 1;
  uint32_t    s5_Num2_C   : 1;
  uint32_t    s6_Num3_E   : 1;
  uint32_t    s7_Num3_C   : 1;
  uint32_t    s8_Num4_E   : 1;
  uint32_t    s9_Num4_C   : 1;
  uint32_t    s10_Num5_E  : 1;
  uint32_t    s11_Num5_C  : 1;
  uint32_t    s12_Num6_E  : 1;
  uint32_t    s13_Num6_C  : 1;
  uint32_t    s14_Num7_E  : 1;
  uint32_t    s15_Num7_C  : 1;
  uint32_t    s16_Num8_E  : 1;
  uint32_t    s17_Num8_C  : 1;  
  uint32_t    s18_Data    : 1;
  uint32_t    s19_R_Plus  : 1;
  uint32_t    s20_W       : 1;
  uint32_t    s21_W_h     : 1;
  uint32_t    s22_Circ_3  : 1;
  uint32_t    s23_Battery : 1;  
  uint32_t    unused      : 8;
} LCD_XT_ROW3_Bits;

typedef struct {
  uint32_t    s0_Lambda     : 1;
  uint32_t    s1_Tar_4      : 1;
  uint32_t    s2_Num1_D     : 1;
  uint32_t    s3_Plus_H     : 1;
  uint32_t    s4_Num2_D     : 1;
  uint32_t    s5_Num2_dot   : 1;
  uint32_t    s6_Num3_D     : 1;
  uint32_t    s7_Num3_dotc  : 1;
  uint32_t    s8_Num4_D     : 1;
  uint32_t    s9_Num3_dot   : 1;
  uint32_t    s10_Num5_D    : 1;
  uint32_t    s11_Num4_dot  : 1;
  uint32_t    s12_Num6_D    : 1;
  uint32_t    s13_Num5_dot  : 1;
  uint32_t    s14_Num7_D    : 1;
  uint32_t    s15_Num6_dot  : 1;
  uint32_t    s16_Num8_D    : 1;
  uint32_t    s17_Num5_dotc : 1;  
  uint32_t    s18_Time      : 1;
  uint32_t    s19_R_Minus   : 1;
  uint32_t    s20_VA_k      : 1;
  uint32_t    s21_Hz        : 1;
  uint32_t    s22_Circ_4    : 1;
  uint32_t    s23_Plus_V    : 1;  
  uint32_t    unused        : 8;
} LCD_XT_ROW4_Bits;

#define LCD_XT_NUM_COUNT    8

#define LCD_NUMS_CLEAR_MASK_R123   0x00FC0003UL
#define LCD_NUMS_CLEAR_MASK_R4     0x00FEAAABUL

/* ========================================  Start of section using anonymous unions  ======================================== */
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
  #pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


typedef struct {
  union {
    __IOM  uint32_t     LCD_ROW1;
    LCD_XT_ROW1_Bits    LCD_ROW1_b;  
  };  
  union {
    __IOM  uint32_t     LCD_ROW2;
    LCD_XT_ROW2_Bits    LCD_ROW2_b;  
  };    
  union {
    __IOM  uint32_t     LCD_ROW3;
    LCD_XT_ROW3_Bits    LCD_ROW3_b;  
  };    
  union {
    __IOM  uint32_t     LCD_ROW4;
    LCD_XT_ROW4_Bits    LCD_ROW4_b;  
  };   
} LCD_XT_DATA;




/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#endif
/* =========================================  End of section using anonymous unions  ========================================= */

#endif  //  MDRB_LCD_XT13468PSPA

