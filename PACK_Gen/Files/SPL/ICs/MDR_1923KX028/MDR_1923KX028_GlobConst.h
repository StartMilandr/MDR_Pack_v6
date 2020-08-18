#ifndef MDR_1923KX029_GLOB_CONST_H
#define MDR_1923KX029_GLOB_CONST_H

//#include <MDR_1923KX028.h>
#include <MDR_1923KX028_AXI_defs.h>
#include <MDR_1923KX028_Config.h>

// List of AXI_EMAC1_BASE_ADDR .. AXI_EMAC16_BASE_ADDR
extern const uint32_t MDR_KX028_AxiAddrEMAC[KX028_EMAC_NUMS];

// List of  AXI_EGPI1_BASE_ADDR..AXI_EGPI16_BASE_ADDR
extern const uint32_t MDR_KX028_AxiAddrEGPI[KX028_EMAC_NUMS];
extern const uint32_t MDR_KX028_AxiAddrETGPI[KX028_EMAC_NUMS];

extern const uint32_t KX028_PortOffsStruct1[AXI_CLASS_PORT_COUNT];
extern const uint32_t KX028_PortOffsStruct2[AXI_CLASS_PORT_COUNT];

// SFP Global variables for MDR_1923KX028_M0_TransferPC.c
extern uint8_t *g_pInfoSFP[SFP_COUNT];
extern uint32_t g_EventsSFP;
extern uint32_t g_PresenceSFP;



#endif  //MDR_1923KX029_GLOB_CONST_H
