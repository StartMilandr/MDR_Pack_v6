#ifndef KX028_CLI_H
#define KX028_CLI_H

#include <stdint.h>
#include <MDR_1923KX028_M2_Stats.h>
#include "board_defs.h"


//  from main.c
extern MDR_KX028_StatsEMAC_t    statsEMAC[KX028_EMAC_PORT_COUNT];

void KX028_InitCLI(uint32_t baudRate, uint32_t freqCPU_Hz);
void KX028_ProcessCLI(uint32_t waitCyclesMax);

#endif  // KX028_CLI_H
