#ifndef _MDRB_BUTTONS_H
#define _MDRB_BUTTONS_H

#include <stdint.h>
#include "MDRB_BoardSelect.h"
#include  <MDR_GPIO.h>
#include  <MDR_Funcs.h>

// Если отделных копок не хватает, они заменяются сочетанием существующих

typedef enum {
    MDRB_Key1 = 0
  , MDRB_Key2 = 1
  , MDRB_Key3 = 2
  , MDRB_Key4 = 3
  , MDRB_Key5 = 4
  , MDRB_Key6 = 5
} MDRB_Keys;

//===================  Инициализация и опрос нажатия  ==================
// Время проверки на дребезг контактов
#define DEBOUNCE_MS_DEF        10

void MDRB_Buttons_InitTick(uint32_t debounce_tick);
bool MDRB_IsKeyPushed(MDRB_Keys key, bool use_debounce);
bool MDRB_IsKeyPushedEx(const MDR_GPIO_Port *GPIO_Port, uint32_t pinSel, uint32_t debounceTicks);

void MDRB_Buttons_ChangeDebounceTick(uint32_t debounce_tick);

//  Вернет True если кнопка была нажата и отпущена, 
//  Содержит бесконечный цикл ожидания отжатия кнопки!
bool MDRB_IsKeyClicked(MDRB_Keys key, bool use_debounce);

#define MDRB_Buttons_Init(debounce_ms, CPU_FregHz)                  MDRB_Buttons_InitTick(MS_TO_DELAY_LOOPS((debounce_ms), (CPU_FregHz)))
#define MDRB_Buttons_ChangeDebounceDelay(debounce_ms, CPU_FregHz)   MDRB_Buttons_ChangeDebounceTick(MS_TO_DELAY_LOOPS((debounce_ms), (CPU_FregHz)))
#define MDRB_Buttons_ChangeFreqCPU                                  MDRB_Buttons_ChangeDebounceDelay

// =================   Именованные определения, для удобства вызова ==========================
#define MDRB_Btn_Up            MDRB_Key1
#define MDRB_Btn_Right         MDRB_Key2
#define MDRB_Btn_Down          MDRB_Key3
#define MDRB_Btn_Left          MDRB_Key4
#define MDRB_Btn_Select        MDRB_Key5
#define MDRB_Btn_Back          MDRB_Key6

#define MDRB_BntPushed_Up(use_debounce)       MDRB_IsKeyPushed(MDRB_Btn_Up,     (use_debounce))
#define MDRB_BntPushed_Right(use_debounce)    MDRB_IsKeyPushed(MDRB_Btn_Right,  (use_debounce))
#define MDRB_BntPushed_Down(use_debounce)     MDRB_IsKeyPushed(MDRB_Btn_Down,   (use_debounce))
#define MDRB_BntPushed_Left(use_debounce)     MDRB_IsKeyPushed(MDRB_Btn_Left,   (use_debounce))

#define MDRB_BntPushed_Select(use_debounce)   MDRB_IsKeyPushed(MDRB_Btn_Select, (use_debounce))
#define MDRB_BntPushed_Back(use_debounce)     MDRB_IsKeyPushed(MDRB_Btn_Back,   (use_debounce))


#define MDRB_BntClicked_Up(use_debounce)      MDRB_IsKeyClicked(MDRB_Btn_Up,     (use_debounce))
#define MDRB_BntClicked_Right(use_debounce)   MDRB_IsKeyClicked(MDRB_Btn_Right,  (use_debounce))
#define MDRB_BntClicked_Down(use_debounce)    MDRB_IsKeyClicked(MDRB_Btn_Down,   (use_debounce))
#define MDRB_BntClicked_Left(use_debounce)    MDRB_IsKeyClicked(MDRB_Btn_Left,   (use_debounce))

#define MDRB_BntClicked_Select(use_debounce)  MDRB_IsKeyClicked(MDRB_Btn_Select, (use_debounce))
#define MDRB_BntClicked_Back(use_debounce)    MDRB_IsKeyClicked(MDRB_Btn_Back,   (use_debounce))


//  ================    Keil Buttons API ===============
int32_t 	Buttons_Initialize (void);
int32_t 	Buttons_Uninitialize (void);
uint32_t 	Buttons_GetState (void);
uint32_t 	Buttons_GetCount (void);

#endif	// _MDRB_BUTTONS_H
