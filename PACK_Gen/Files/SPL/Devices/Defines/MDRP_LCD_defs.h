#ifndef _MDRP_LCD_DEFS_H
#define _MDRP_LCD_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

//=======================   LCD  =======================
typedef struct
{
	uint32_t TextBuf[128];
	uint32_t DecodeBuf[320];
	uint32_t CR;
	uint32_t Jark;
	uint32_t RESRVED[2];
	uint32_t DivR;
	uint32_t SR;
}MDR_LED_TypeDef;

/* Bit field positions: */
#define LED_CR_DEN_Pos						0
#define LED_CR_INTEN_Pos					1
#define LED_CR_TWINK_EN_Pos					2
#define LED_CR_FRAME_Pos					3
#define LED_CR_LEN_STR_Pos					4
#define LED_CR_LEN_STOLB_Pos				8
#define LED_CR_EN_RAM_Pos					11
#define LED_CR_INV_Y_Pos					12
#define LED_CR_INV_EN_Pos					13
#define LED_CR_INV_C_Pos					14
#define LED_CR_INV_DO_Pos					15
/* Bit field masks: */
#define LED_CR_DEN							((uint32_t)0x00000001)
#define LED_CR_INTEN     					((uint32_t)0x00000002)
#define LED_CR_TWINK_EN						((uint32_t)0x00000004)
#define LED_CR_FRAME						((uint32_t)0x00000008)
#define LED_CR_LEN_STR_Msk					((uint32_t)0x00000070)
#define LED_CR_LEN_STOLB_Msk				((uint32_t)0x00000700)
#define LED_CR_EN_RAM						((uint32_t)0x00000800)
#define LED_CR_INV_Y						((uint32_t)0x00001000)
#define LED_CR_INV_EN						((uint32_t)0x00002000)
#define LED_CR_INV_C						((uint32_t)0x00004000)
#define LED_CR_INV_DO						((uint32_t)0x00008000)

/* Bit field positions: */
#define LED_JARK_Pos      		      	0
/* Bit field masks: */
#define LED_JARK_Msk         	      		((uint32_t)0x000000FF)

/* Bit field positions: */
#define LED_DIVR_DIV_Pos      		      	0
#define LED_DIVR_DIV_TWiNK_Pos      		8
/* Bit field masks: */
#define LED_DIVR_DIV_Msk      		      	((uint32_t)0x00000007)
#define LED_DIVR_DIV_TWiNK_Msk      		((uint32_t)0x0000FF00)


/* Bit field positions: */
#define LED_SR_WR_REDY_Pos      		      	 0
/* Bit field masks: */
#define LED_SR_WR_REDY      		      	 	((uint32_t)0x00000001)


#ifdef __cplusplus
}
#endif

#endif  //  _MDRP_LCD_DEFS_H
