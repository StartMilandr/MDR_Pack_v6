#include <MDRB_Buttons.h>
	
//    PD30..PD31 = DATA[0..1], PD24 = nWE, PD23 = nOE, PD19 = nCS, PD0..PD16 = ADDR[2..18], 
#define MDR_EBC_D_PINS_A2A18_D0D1   MDR_Pin_31 | MDR_Pin_30 | MDR_Pin_24 | MDR_Pin_23 | MDR_Pin_19 | 0x0001FFFFUL
//    PE0..PE5 = DATA[2..7] 
#define MDR_EBC_E_PINS_D2D7         MDR_Pin_0 | MDR_Pin_1 | MDR_Pin_2 | MDR_Pin_3 | MDR_Pin_4 | MDR_Pin_5
//    PC30..PC31 = ADDR[0..1] 
#define MDR_EBC_C_PINS_A0A1         MDR_Pin_30 | MDR_Pin_31

void MDRB_EBC_InitPins_A19_D8(void)
{
  MDR_PinDig_GroupPinCfg groupPinCfg;
  
  MDR_Port_InitDigGroupPinCfg(MDR_Off, MDR_PIN_MAXFAST, &groupPinCfg);
  
  
  MDR_GPIO_Enable(MDR_GPIO_D);
  MDR_GPIO_Enable(MDR_GPIO_E);
  MDR_GPIO_Enable(MDR_GPIO_C);
  
  MDR_GPIO_InitDigFunc(MDR_GPIO_D, MDR_EBC_D_PINS_A2A18_D0D1, MDR_Pin_PullOff, MDR_PIN_FUNC_2, &groupPinCfg);
  MDR_GPIO_InitDigFunc(MDR_GPIO_E, MDR_EBC_E_PINS_D2D7,       MDR_Pin_PullOff, MDR_PIN_FUNC_2, &groupPinCfg);
  MDR_GPIO_InitDigFunc(MDR_GPIO_C, MDR_EBC_C_PINS_A0A1,       MDR_Pin_PullOff, MDR_PIN_FUNC_2, &groupPinCfg);  
}
