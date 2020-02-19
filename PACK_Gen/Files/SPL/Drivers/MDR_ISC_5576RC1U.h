#ifndef _JTAG_ISC_H
#define _JTAG_ISC_H

#include <MDR_JTAG_GPIO.h>

//#define MDR_5576RC_DATA_LEN         (0x40000 + 10)
#define MDR_5576RC_DATA_LEN         0x40000
#define MDR_5576RC_DATA_CRC_BLANK   0x3FFFE

//#define MDR_5576RC_DATA_ADDR      0x008000UL
#define MDR_5576RC_USER_DATA_ADDR   0x008020UL


typedef struct {
  uint32_t ticks_eraseSect_4s;
  uint32_t ticks_ena_RD_1ms;
  uint32_t ticks_prog_200ns;
} MDR_5576RC_Delays;

void MDR_5576RC_Init(const MDR_JTAG_Cfg *cfgJTAG, MDR_5576RC_Delays *delays);



//attribute IDCODE_REGISTER of EPC4Q100 : entity is
//  "0000"&               --4-bit Version
//  "0001000000001010"&   --16-bit Part Number (hex 100A)
//  "00001101110"&        --11-bit Manufacturer's Identity
//  "1";                  --Mandatory LSB
//attribute USERCODE_REGISTER of EPC4Q100 : entity is
//  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
//attribute ISC_BLANK_USERCODE of EPC4Q100 : entity is
//  "11111111111111111111111111111111";
#define MDR_5576RC_USERCODE_LEN   32

//attribute REGISTER_ACCESS of EPC4Q100 : entity is
//  "DEVICE_ID        (IDCODE), "&
#define MDR_5576RC_IDCODE_LEN     32
#define MDR_5576RC_IDCODE         0x0100A0DD

//-- Following 7 registers are IEEE 1532 registers
//  "ISC_Default[2]	  (ISC_DISABLE, ISC_NOOP)," &
#define MDR_5576RC_DIS_LEN         2

//  "ISC_PData[16]	  (ISC_PROGRAM)," &
#define MDR_5576RC_PROG_DATA_LEN  16

//  "ISC_RData[18]	  (ISC_READ, ISC_STAT)," &
#define MDR_5576RC_RD_STAT_LEN        18
#define MDR_5576RC_RD_DATA_CRC_LEN    18
#define MDR_5576RC_RD_DATA_LENx       16
#define MDR_5576RC_RD_CRC_POS         2
#define MDR_5576RC_RD_CRC_MSK         0x3


//  "ISC_Sector[23]	  (ISC_ERASE)," &
//  "ISC_Address[23]	(ISC_ADDRESS_SHIFT)," &
#define MDR_5576RC_ADDR_LEN       23

//  "ISC_Config[2]	  (ISC_ENABLE)," &
#define MDR_5576RC_ENA_LEN         2
#define MDR_5576RC_ENA_MSK         1


//  "ISC_Info[5]		  (ISC_READ_INFO)";
#define MDR_5576RC_INFO_LEN        5

#define MDR_5576RC_DONE_BIT_ADDR  0x8000UL
#define MDR_5576RC_DONE_BIT_DATA  0xDFFF
#define MDR_5576RC_DONE_BIT_OK    0x2000UL    //  Бит Инверсный - (DONE = 0)


#define MDR_5576RC_RD_STAT_LEN    18
#define MDR_5576RC_RD_STAT_MSK    0x3FFFFUL

#define MDR_5576RC_ADDR_SECT_0    0x00000UL
#define MDR_5576RC_ADDR_SECT_1    0x02000UL
#define MDR_5576RC_ADDR_SECT_2    0x03000UL
#define MDR_5576RC_ADDR_SECT_3    0x04000UL
#define MDR_5576RC_ADDR_SECT_4    0x10000UL
#define MDR_5576RC_ADDR_SECT_5    0x20000UL
#define MDR_5576RC_ADDR_SECT_6    0x30000UL




//  ---------------   ISC_API   --------------------------

void MDR_5576RC1U_ProgStart(uint32_t startAddr);
void MDR_5576RC1U_ProgNextData(uint32_t data);

void     MDR_5576RC1U_ReadStart(uint32_t startAddr);
uint32_t MDR_5576RC1U_ReadNextDataCRC(void);

__STATIC_INLINE uint16_t MDR_5576RC1U_ReadNextData(void) { return (MDR_5576RC1U_ReadNextDataCRC() >> MDR_5576RC_RD_CRC_POS); }

uint32_t MDR_5576RC_Read_IDCODE(void);
void     MDR_5576RC1U_Erase(void);
uint32_t MDR_5576RC1U_CheckBlank(void);

void MDR_5576RC1U_Exit(void);


//  --------------- Config Bits --------------------------
void MDR_5576RC1U_ProgCfgBits(void);
bool MDR_5576RC1U_CheckDoneBit(void);
void MDR_5576RC1U_SentInitConfig(void);

#endif  //  _JTAG_ISC_H
