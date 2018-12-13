#ifndef _SSP_COMMON_FUNCS_H
#define _SSP_COMMON_FUNCS_H

#include <MDR_SSP.h>
#include <MDRB_LCD.h>
#include <SSP_cfg.h>

#ifndef BDR_NO_SLAVE_SSP
uint32_t MasterSlave_TestTransfer(void);
#endif

extern uint32_t activeTest;

uint32_t MasterTXRX_TestTransfer(const MDR_SSP_TypeEx *exSSPx);

void LCD_ShowInit(const MDR_SSP_TypeEx *exSSPx, char *testName);
void LCD_ShowResult(uint32_t errCount);
void LCD_ShowStarted(void);

#endif  //_SSP_COMMON_FUNCS_H

