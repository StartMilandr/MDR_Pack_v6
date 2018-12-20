#ifndef _LCD_HTD_B083
#define _LCD_HTD_B083


typedef struct {
  uint32_t    s1_T1_A   : 1;
  uint32_t    s2_T2_Ar  : 1;
  uint32_t    s3_T3_Al  : 1;
  uint32_t    s4_TARIF  : 1;
  uint32_t    s5_T4_R   : 1;
  uint32_t    s6_T5_Rl  : 1;
  uint32_t    s7_T6_Rr  : 1;
  uint32_t        NUM_8 : 7;
  uint32_t    s15_plusV : 1;
  uint32_t    s16_plusH : 1;
  uint32_t        NUM_7 : 7;
  uint32_t        NUM_6 : 7;
  uint32_t    s31_P8    : 1;
  uint32_t    s32_PHASE : 1;
} LCD_HTD_REG1_Bits;

typedef struct {
  uint32_t    s33_F1_A  : 1;
  uint32_t    s34_F2_B  : 1;
  uint32_t    s35_F3_C  : 1;
  uint32_t        NUM_5 : 7;
  uint32_t    s43_P7    : 1;
  uint32_t    s44_P6    : 1;
  uint32_t        NUM_4 : 7;  
  uint32_t    s52_P6    : 1;
  uint32_t        NUM_3 : 7;
  uint32_t    s60_TIME  : 1;
  uint32_t    s61_DATE  : 1;
  uint32_t    s62_SYM   : 1;
  uint32_t    s63_P4    : 1;
  uint32_t    s64_P3    : 1;
} LCD_HTD_REG2_Bits;  


typedef struct {
  uint32_t        NUM_2 : 7;  
  uint32_t    s72_P2    : 1;
  uint32_t        NUM_1 : 7;
  uint32_t    s80_P1    : 1;
  uint32_t        NUM_0 : 7;
  uint32_t    s88_PP    : 1;
  uint32_t    s89_K1    : 1;
  uint32_t    s90_MONTH : 1;
  uint32_t       NUM_9L : 6;
} LCD_HTD_REG3_Bits;

typedef struct {  
  uint32_t       NUM_9H   : 1;
  uint32_t    s98_Circle  : 1;
  uint32_t       NUM_10   : 7;
  uint32_t    s106_Battery: 1;
  uint32_t    s107_Slash  : 1;
  uint32_t    s108_Akkum  : 1;
  uint32_t    s109_Lock   : 1;
  uint32_t    s110_N1_k   : 1;
  uint32_t    s111_N4_var : 1;
  uint32_t    s112_N7_h   : 1;
  uint32_t    s113_N2_k   : 1;
  uint32_t    s114_N5_V   : 1;
  uint32_t    s115_N6_A   : 1;
  uint32_t    s116_HZ     : 1;
  uint32_t    s117_N8_h   : 1;
  uint32_t    s118_W      : 1;
  uint32_t    s119_N3_k   : 1;
  
  uint32_t    reserved    : 10;
} LCD_HTD_REG4_Bits;


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
    __IOM  uint32_t      LCD_REG1;
    LCD_HTD_REG1_Bits    LCD_REG1_b;  
  };  
  union {
    __IOM  uint32_t      LCD_REG2;
    LCD_HTD_REG2_Bits    LCD_REG2_b;  
  };    
  union {
    __IOM  uint32_t      LCD_REG3;
    LCD_HTD_REG3_Bits    LCD_REG3_b;  
  };    
  union {
    __IOM  uint32_t      LCD_REG4;
    LCD_HTD_REG4_Bits    LCD_REG4_b;  
  };   
} LCD_HTD_REG128;


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

#endif  //  _LCD_HTD_B083

