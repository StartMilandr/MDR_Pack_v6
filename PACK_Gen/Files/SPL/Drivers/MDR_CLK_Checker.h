#ifndef MDR_CLK_CHECKER_H
#define MDR_CLK_CHECKER_H

#include <MDR_CLK_Checker_defs.h>
#include <MDR_Funcs.h>

typedef enum {
  MDR_CLKCHK_CPU,
  MDR_CLKCHK_LSI,
  MDR_CLKCHK_LSE,
  MDR_CLKCHK_HSE0,
  MDR_CLKCHK_HSE1,
  MDR_CLKCHK_PLL0,
  MDR_CLKCHK_PLL1,
  MDR_CLKCHK_PLL2,
#ifdef MDR_HAS_PLL3  
  MDR_CLKCHK_PLL3
#endif      
  MDR_CLKCHK_COUNT  // - Not for Use as Item!
} MDR_CLKCHK_Target;

extern MDR_RST_CLK_CHECKER*        const MDR_CLKCHK_REGS[MDR_CLKCHK_COUNT];
extern volatile MDR_CLKCHK_Status* const MDR_CLKCHK_STATUS[MDR_CLKCHK_COUNT];
extern volatile MDR_CLKCHK_Ctrl*   const MDR_CLKCHK_CTRL[MDR_CLKCHK_COUNT];


#define MDR_CLKCHK_SEL_SLOW_EVENT0    0x1UL
#define MDR_CLKCHK_SEL_SLOW_EVENT1    0x2UL
#define MDR_CLKCHK_SEL_FAST_EVENT2    0x4UL
#define MDR_CLKCHK_SEL_FAST_EVENT3    0x8UL

#define MDR_CLKCHK_SEL_ALL_EVENTS   (MDR_CLKCHK_SEL_SLOW_EVENT0 | MDR_CLKCHK_SEL_SLOW_EVENT1 | MDR_CLKCHK_SEL_FAST_EVENT2 | MDR_CLKCHK_SEL_FAST_EVENT3)

typedef union {
  uint32_t                  eventSel;
  MDR_CLKCHK_EventSel_bits  eventSel_b;  
} MDR_CLKCHK_EventSel;

typedef struct {
  //  Prescallers
  uint16_t  PrescSlow_HSI;
  uint16_t  PrescSlow_CLK;
  uint16_t  PrescFast_HSI;  
  uint16_t  PrescFast_CLK;
  //  Event Levels
  uint8_t   level_SlowEvent0;
  uint8_t   level_SlowEvent1;
  uint8_t   level_FastEvent2;
  uint8_t   level_FastEvent3;  
  //  Events Enable
  MDR_CLKCHK_EventSel enaGoHSI_byEvents;  
} MDR_CLKCHK_Cfg;

//  Init - Activate block
void MDR_CLKCHK_Init(MDR_CLKCHK_Target target, const MDR_CLKCHK_Cfg *cfg);
//  Init - Deactivate block
void MDR_CLKCHK_Deinit(MDR_CLKCHK_Target target);

//  Более низкоуровневая инициализация через регистры.
void MDR_CLKCHK_Init_byRegs(MDR_CLKCHK_Target target, const MDR_CLKCHK_Regs *cfgRegs);

//  Stop - Restart
__STATIC_INLINE void MDR_CLKCHK_Stop(MDR_CLKCHK_Target target)    {(*MDR_CLKCHK_CTRL[target]).CTRL &= ~MDR_CLK_CHK_EN_Msk;}
__STATIC_INLINE void MDR_CLKCHK_Restart(MDR_CLKCHK_Target target) 
{
  uint32_t regCTRL = (*MDR_CLKCHK_CTRL[target]).CTRL | MDR_CLK_CHK_EN_Msk | MDR_CLK_CHK_CLR_ALL_EVENTS;
  //  Сбросить теневые регистры MAX_SHIFT раньше разрешения аварийных переключений на HSI!
  (*MDR_CLKCHK_CTRL[target]).CTRL = regCTRL & (~MDR_CLK_CHK_CLR_EN_EVENTS);
  (*MDR_CLKCHK_CTRL[target]).CTRL = regCTRL;
}


//  Clear Events
__STATIC_INLINE void MDR_CLKCHK_ClearAllEvents(MDR_CLKCHK_Target target) {(*MDR_CLKCHK_CTRL[target]).CTRL |= MDR_CLK_CHK_CLR_ALL_EVENTS;}
__STATIC_INLINE void MDR_CLKCHK_ClearEvents(MDR_CLKCHK_Target target, MDR_CLKCHK_EventSel selEvents) {(*MDR_CLKCHK_CTRL[target]).CTRL |= VAL2FLD(selEvents.eventSel, MDR_CLK_CHK_CLR_SLOW_EVENT0);}

__STATIC_INLINE void MDR_CLKCHK_ClearSlowEvent0(MDR_CLKCHK_Target target) {(*MDR_CLKCHK_CTRL[target]).CTRL |= MDR_CLK_CHK_CLR_SLOW_EVENT0_Msk;}
__STATIC_INLINE void MDR_CLKCHK_ClearSlowEvent1(MDR_CLKCHK_Target target) {(*MDR_CLKCHK_CTRL[target]).CTRL |= MDR_CLK_CHK_CLR_SLOW_EVENT1_Msk;}
__STATIC_INLINE void MDR_CLKCHK_ClearFastEvent2(MDR_CLKCHK_Target target) {(*MDR_CLKCHK_CTRL[target]).CTRL |= MDR_CLK_CHK_CLR_FAST_EVENT2_Msk;}
__STATIC_INLINE void MDR_CLKCHK_ClearFastEvent3(MDR_CLKCHK_Target target) {(*MDR_CLKCHK_CTRL[target]).CTRL |= MDR_CLK_CHK_CLR_FAST_EVENT3_Msk;}

__STATIC_INLINE void MDR_CLKCHK_ClearMaxShiftSlow(MDR_CLKCHK_Target target) {(*MDR_CLKCHK_CTRL[target]).CTRL |= MDR_CLK_CHK_CLR_SHIFT_SLOW_Msk;}
__STATIC_INLINE void MDR_CLKCHK_ClearMaxShiftFast(MDR_CLKCHK_Target target) {(*MDR_CLKCHK_CTRL[target]).CTRL |= MDR_CLK_CHK_CLR_SHIFT_FAST_Msk;}


//  Get Status / EventsSet
__STATIC_INLINE MDR_CLKCHK_Status  MDR_CLKCHK_GetStatus(MDR_CLKCHK_Target target)  {return   *MDR_CLKCHK_STATUS[target];}
__STATIC_INLINE bool MDR_CLKCHK_CheckFlag(MDR_CLKCHK_Target target, uint32_t flag) {return ((*MDR_CLKCHK_STATUS[target]).STAT & flag) != 0;}

__STATIC_INLINE bool MDR_CLKCHK_GetSlowEvent0(MDR_CLKCHK_Target target) {return MDR_CLKCHK_CheckFlag(target, MDR_CLK_CHK_STAT_SLOW_EVENT0_Msk);}
__STATIC_INLINE bool MDR_CLKCHK_GetSlowEvent1(MDR_CLKCHK_Target target) {return MDR_CLKCHK_CheckFlag(target, MDR_CLK_CHK_STAT_SLOW_EVENT1_Msk);}
__STATIC_INLINE bool MDR_CLKCHK_GetFastEvent2(MDR_CLKCHK_Target target) {return MDR_CLKCHK_CheckFlag(target, MDR_CLK_CHK_STAT_FAST_EVENT2_Msk);}
__STATIC_INLINE bool MDR_CLKCHK_GetFastEvent3(MDR_CLKCHK_Target target) {return MDR_CLKCHK_CheckFlag(target, MDR_CLK_CHK_STAT_FAST_EVENT3_Msk);}

__STATIC_INLINE uint16_t MDR_CLKCHK_GetMaxShiftSlow(MDR_CLKCHK_Target target) {return _FLD2VAL(MDR_CLK_CHK_STAT_MAX_CLK_SHIFT_SLOW, (*MDR_CLKCHK_STATUS[target]).STAT);}
__STATIC_INLINE uint16_t MDR_CLKCHK_GetMaxShiftFast(MDR_CLKCHK_Target target) {return _FLD2VAL(MDR_CLK_CHK_STAT_MAX_CLK_SHIFT_FAST, (*MDR_CLKCHK_STATUS[target]).STAT);}


#endif  //  MDR_CLK_CHECKER_H
