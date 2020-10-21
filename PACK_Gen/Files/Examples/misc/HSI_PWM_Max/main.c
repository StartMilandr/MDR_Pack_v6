#include <MDR_Config.h>
#include <MDR_Timer.h>
#include <MDRB_Timer_PinSelect.h>

//  WPM PIN: PE3 for VE1
#define PWM_TIMERex       MDR_TIMER1ex
#define PWM_TIMER_CH      MDR_TIMER1_CH1
#define PWM_PIN_CH_CFG    _pinTim1_CH1      

#define TIM_BRG_MIN       MDR_Div128P_div1
#define TIM_PSG_MIN       0
#define TIM_PERIOD_MIN    2


int main(void)
{
  MDR_Timer_InitPeriod    (PWM_TIMERex, TIM_BRG_MIN, TIM_PSG_MIN, TIM_PERIOD_MIN, false); 
  MDR_TimerCh_InitPWM(PWM_TIMER_CH, NULL, MDR_TIM_PWM_Ref1_eqCCR, 0);
  MDR_TimerCh_InitPinGPIO(&PWM_PIN_CH_CFG, MDR_PIN_MAXFAST);
  MDR_Timer_Start(PWM_TIMERex);
  
  while(1);
}
