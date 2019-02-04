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

#define LCD_R1_T1_A        0x0001UL
#define LCD_R1_T2_Ar       0x0002UL
#define LCD_R1_T3_Al       0x0004UL
#define LCD_R1_Tarif       0x0008UL
#define LCD_R1_T4_R        0x0010UL
#define LCD_R1_T5_Rl       0x0020UL
#define LCD_R1_T6_Rr       0x0040UL
#define LCD_R1_PlusV       0x4000UL
#define LCD_R1_PlusH       0x8000UL
#define LCD_R1_DotP8   0x40000000UL
#define LCD_R1_Phase   0x80000000UL

typedef struct {
  uint32_t    s33_F1_A  : 1;
  uint32_t    s34_F2_B  : 1;
  uint32_t    s35_F3_C  : 1;
  uint32_t        NUM_5 : 7;
  uint32_t    s43_P7    : 1;
  uint32_t    s44_P6    : 1;
  uint32_t        NUM_4 : 7;  
  uint32_t    s52_P5    : 1;
  uint32_t        NUM_3 : 7;
  uint32_t    s60_TIME  : 1;
  uint32_t    s61_DATE  : 1;
  uint32_t    s62_SUM   : 1;
  uint32_t    s63_P4    : 1;
  uint32_t    s64_P3    : 1;
} LCD_HTD_REG2_Bits;  

#define LCD_R2_F1_A        0x0001UL
#define LCD_R2_F1_B        0x0002UL
#define LCD_R2_F1_C        0x0004UL
#define LCD_R2_DotP7       0x0400UL
#define LCD_R2_DotP6       0x0800UL
#define LCD_R2_DotP5   0x00100000UL
#define LCD_R2_Time    0x08000000UL
#define LCD_R2_Date    0x10000000UL
#define LCD_R2_SUM     0x20000000UL
#define LCD_R2_DotP4   0x40000000UL
#define LCD_R2_DotP3   0x80000000UL

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

#define LCD_R3_DotP2       0x0080UL
#define LCD_R3_DotP1       0x8000UL
#define LCD_R3_PP      0x00800000UL
#define LCD_R3_K1      0x01000000UL
#define LCD_R3_Month   0x02000000UL

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
  
  uint32_t    reserved    : 9;
} LCD_HTD_REG4_Bits;

#define LCD_R4_Circ        0x0002UL
#define LCD_R4_Batt        0x0200UL
#define LCD_R4_Slash       0x0400UL
#define LCD_R4_Akkum       0x0800UL
#define LCD_R4_Lock        0x1000UL
#define LCD_R4_N1_k        0x2000UL
#define LCD_R4_var         0x4000UL
#define LCD_R4_N7_h        0x8000UL
#define LCD_R4_N2_k    0x00010000UL
#define LCD_R4_V       0x00020000UL
#define LCD_R4_N6_A    0x00040000UL
#define LCD_R4_Hz      0x00080000UL
#define LCD_R4_N8_h    0x00100000UL
#define LCD_R4_W       0x00200000UL
#define LCD_R4_N3_k    0x00400000UL


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

