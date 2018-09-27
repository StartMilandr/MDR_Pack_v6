#ifndef _MDRB_LEDS_H
#define _MDRB_LEDS_H

#include <stdint.h>
#include <MDR_GPIO.h>
#include <MDRB_BoardSelect.h>

//  ============    Управление сетодиодами на отладочной плате ===============
void MDRB_LED_Init  (uint32_t LEDs_Sel);
void MDRB_LED_Switch(uint32_t LEDs_Sel);
void MDRB_LED_Set   (uint32_t LEDs_Sel, bool isOn);

__STATIC_INLINE void MDRB_LED_InitALL(void) {MDRB_LED_Init(MDRB_LED_PinAll);}


//  ================    Keil LED API ===============
int32_t 	LED_Initialize (void);
int32_t 	LED_Uninitialize (void);
int32_t 	LED_On (uint32_t num);
int32_t 	LED_Off (uint32_t num);
int32_t 	LED_SetOut (uint32_t val);
uint32_t 	LED_GetCount (void);
 


#endif //_MDRB_LEDS_H
