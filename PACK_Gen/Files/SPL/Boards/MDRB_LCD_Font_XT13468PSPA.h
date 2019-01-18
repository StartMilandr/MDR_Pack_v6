#ifndef _MDRB_LCD_FONT_XT13468PSPA_H
#define _MDRB_LCD_FONT_XT13468PSPA_H

// -------------------- FONT ----------------------

#define R1_N1F      0x00004UL
#define R1_N1A      0x00008UL
#define R2_N1G      0x00004UL
#define R2_N1B      0x00008UL
#define R3_N1E      0x00004UL
#define R3_N1C      0x00008UL
#define R4_N1D      0x00004UL

static const unsigned int LCD_XT_Font[] = { 
//      ROW1,               ROW2,               ROW3,               ROW4
/* 0 */  R1_N1A | R1_N1F,   R2_N1B,             R3_N1C | R3_N1E,    R4_N1D,
/* 1 */  0,                 R2_N1B,             R3_N1C,             0,
/* 2 */  R1_N1A,            R2_N1B | R2_N1G,    R3_N1E,             R4_N1D,
/* 3 */  R1_N1A,            R2_N1B | R2_N1G,    R3_N1C,             R4_N1D,
/* 4 */           R1_N1F,   R2_N1B | R2_N1G,    R3_N1C,             0,
/* 5 */  R1_N1A | R1_N1F,            R2_N1G,    R3_N1C,             R4_N1D,
/* 6 */  R1_N1A | R1_N1F,            R2_N1G,    R3_N1C | R3_N1E,    R4_N1D,
/* 7 */  R1_N1A,            R2_N1B,             R3_N1C,             0,
/* 8 */  R1_N1A | R1_N1F,   R2_N1B | R2_N1G,    R3_N1C | R3_N1E,    R4_N1D,
/* 9 */  R1_N1A | R1_N1F,   R2_N1B | R2_N1G,    R3_N1C,             R4_N1D,
/* A */  R1_N1A | R1_N1F,   R2_N1B | R2_N1G,    R3_N1C | R3_N1E,    0,
/* B */           R1_N1F,            R2_N1G,    R3_N1C | R3_N1E,    R4_N1D,
/* C */  R1_N1A | R1_N1F,   0,                           R3_N1E,    R4_N1D,
/* D */  0,                 R2_N1B | R2_N1G,    R3_N1C | R3_N1E,    R4_N1D,
/* E */  R1_N1A | R1_N1F,            R2_N1G,             R3_N1E,    R4_N1D,
/* F */  R1_N1A | R1_N1F,            R2_N1G,             R3_N1E,    0
}; 

static const unsigned int LCD_NUM_CLEAR[] = { R1_N1A | R1_N1F, R2_N1B | R2_N1G, R3_N1C | R3_N1E, R4_N1D};


#define CHAR_0    0x30
#define CHAR_9    0x39
#define CHAR_A    0x41
#define CHAR_F    0x46
#define CHAR_a    0x61
#define CHAR_f    0x66



#endif // _MDRB_LCD_FONT_XT13468PSPA_H
