#ifndef BASIS_CFG_H
#define BASIS_CFG_H

#include <MDR_Config.h>
#include <stdint.h>
#include <MDR_GPIO.h>
#include "MDRB_Basis_v2.h"
//#include <MDR_SoftI2C_States.h>
//#include <MDR_SoftI2C_byTimer.h>

void PhyResetPinsInit(void);
void vResetPhys( void );

extern uint32_t SFP_PinSel[SFP_COUNT];

void SFP_PresencePinsInit(void);
uint32_t SFP_PresenceGetMask(void);



#endif    //BASIS_CFG_H

