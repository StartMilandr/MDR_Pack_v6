#ifndef MDR_1923KX029_MODE0_TRANSF_PC_H
#define MDR_1923KX029_MODE0_TRANSF_PC_H

#include <MDR_Config.h>
#include <MDR_1923KX028.h>
#include <MDR_1923KX028_AXI_defs.h>
#include <MDR_1923KX028_Config.h>
#include <MDR_1923KX028_GlobConst.h>

extern uint8_t *SFP_pInfo[SFP_COUNT];

void MDR_KX028_M0_TransferPC(void);
uint32_t SFP_GetEventsAndClear(void);

#endif  //MDR_1923KX029_MODE0_TRANSF_PC_H
