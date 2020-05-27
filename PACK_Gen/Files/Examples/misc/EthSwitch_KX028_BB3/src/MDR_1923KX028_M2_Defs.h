#ifndef MDR_1923KX029_MODE2_DEFS_H
#define MDR_1923KX029_MODE2_DEFS_H

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


typedef struct {
  uint32_t addr;
  uint32_t data;
} MDR_KX028_AddrData_t;


extern MDR_KX028_AddrData_t sw_hwreg_settings[];
extern MDR_KX028_AddrData_t sw_hwreg_enable_bmu_1_2_egpi_1_to_16[];
extern MDR_KX028_AddrData_t sw_hwreg_enable_class_1_2[];
extern MDR_KX028_AddrData_t sw_hwreg_enable_emac_1_to_16[];


#endif  //MDR_1923KX029_MODE2_DEFS_H
