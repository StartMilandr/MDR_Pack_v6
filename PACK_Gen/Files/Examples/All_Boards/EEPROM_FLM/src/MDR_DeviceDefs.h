#ifndef _MDR_DEVICE_DEFS_H
#define _MDR_DEVICE_DEFS_H

typedef unsigned int uint32_t;

#define REG32(x) (*((volatile uint32_t *)(x)))

//==================  RST   =================
#define RST_CPU_CLOCK        0x4002000C
#define RST_PER_CLOCKS       0x4002001C

#define regCPU_CLOCK        REG32(RST_CPU_CLOCK)
#define regPER_CLOCK        REG32(RST_PER_CLOCKS)
#define   bClockOn_EEPROM    (1 << 3)
#define   bClockOn_RST       (1 << 4)

#if defined (USE_MDR1986VE4)
  #define   bClockOn_BKP       (1 << 12)
#else
  #define   bClockOn_BKP       (1 << 27)
#endif


//==================   BKP  =================
#if defined (USE_MDR1986VE4)
  #define BKP_REG_0F           0x4006003C
  #define BKP_REG_0E           0x40060038
#else
  #define BKP_REG_0F           0x400D803C
  #define BKP_REG_0E           0x400D8038
#endif

#define regBKP_REG_0E       REG32(BKP_REG_0E)
#define   bFPOR              (1  << 11)

#define regBKP_REG_0F       REG32(BKP_REG_0F)
#define   bHSI_ON            (1  << 22)
#define   bHSI_RDY           (1  << 23)
#define   bHSI_Trim8MHz      (23 << 24)
#define   bHSI_TRIM_Msk      (0x3F000000UL)


//==================  EEPROM  ===============

#define READ_BY_EEPROM    0
#define FIX_DBL_READ      1

#ifndef USE_EEPROM_Info_Bank
  #define MEM_BANK  0
#else
  #define MEM_BANK  MDR_EEPROM_CMD_BIT_IFREN  // Info memory
#endif

#if defined(USE_MDR1986VE9x) || defined(USE_MDR1901VC1)
  #define FLASH_ADDR_0      0x08000000
#else
  #define FLASH_ADDR_0      0
#endif

#if defined (USE_MDR1986VE4)
  #define PAGE_SIZE          0x200
  #define PAGE_COUNT         256
#else
  #define PAGE_SIZE          0x1000
  #define PAGE_COUNT         32
#endif

#define EEPROM_KEY_ACCESS_CODE           0x8AAA5551UL

#define EEPROM_CMD        0x40018000UL
#define EEPROM_ADDR       0x40018004UL
#define EEPROM_DI         0x40018008UL
#define EEPROM_D0         0x4001800CUL
#define EEPROM_KEY        0x40018010UL

#define regCMD            REG32(EEPROM_CMD)
#define regADDR           REG32(EEPROM_ADDR)
#define regDI             REG32(EEPROM_DI)
#define regDO             REG32(EEPROM_D0)
#define regKEY            REG32(EEPROM_KEY)

#define MDR_EEPROM_CMD_BIT_CON             (0x00000001UL)
#define MDR_EEPROM_CMD_BIT_WR              (0x00000002UL)
#define MDR_EEPROM_CMD_BIT_RD              (0x00000004UL)
#define MDR_EEPROM_CMD_BIT_XE              (0x00000040UL)
#define MDR_EEPROM_CMD_BIT_YE              (0x00000080UL)
#define MDR_EEPROM_CMD_BIT_SE              (0x00000100UL)
#define MDR_EEPROM_CMD_BIT_IFREN           (0x00000200UL)
#define MDR_EEPROM_CMD_BIT_ERASE           (0x00000400UL)
#define MDR_EEPROM_CMD_BIT_MAS1            (0x00000800UL)
#define MDR_EEPROM_CMD_BIT_PROG            (0x00001000UL)
#define MDR_EEPROM_CMD_BIT_NVSTR           (0x00002000UL)

#define IFREN_ERASE_MAIN              0UL
#define IFREN_ERASE_MAIN_AND_INFO     MDR_EEPROM_CMD_BIT_IFREN


#ifdef USE_MDR1986VE1
  #define DELAY_LOOP_CYCLES_ASM_RAM   8
#elif defined(USE_MDR1986VE9x) || defined(USE_MDR1901VC1)
  #define DELAY_LOOP_CYCLES_ASM_RAM   9
#elif defined (USE_MDR1986VE4)
  #define DELAY_LOOP_CYCLES_ASM_RAM   4
#endif

//  CycPerLoop - количество тактов CPU на исполнение одного цикла
#define _SEC_TO_DELAY_LOOPS(Sec, freqCPU_Hz, CycPerLoop, SecUnit)   ((uint32_t)((double)(Sec) * (freqCPU_Hz) / (SecUnit) / (CycPerLoop)))

#define  S_TO_DELAY_LOOPS_EX(Sec,  freqCPU_Hz, CycPerLoop)    _SEC_TO_DELAY_LOOPS(Sec,  freqCPU_Hz, CycPerLoop, 1         )
#define MS_TO_DELAY_LOOPS_EX(mSec, freqCPU_Hz, CycPerLoop)    _SEC_TO_DELAY_LOOPS(mSec, freqCPU_Hz, CycPerLoop, 1000      )
#define US_TO_DELAY_LOOPS_EX(uSec, freqCPU_Hz, CycPerLoop)    _SEC_TO_DELAY_LOOPS(uSec, freqCPU_Hz, CycPerLoop, 1000000   )
#define NS_TO_DELAY_LOOPS_EX(nSec, freqCPU_Hz, CycPerLoop)    _SEC_TO_DELAY_LOOPS(nSec, freqCPU_Hz, CycPerLoop, 1000000000)


//  HSI = 8MHz, 8 clocks = 1us
#define CPU_CLK 8000000

//  Inputs for RAM_Delay(delay_cycles)
#define delay_1us         US_TO_DELAY_LOOPS_EX(1,     CPU_CLK, DELAY_LOOP_CYCLES_ASM_RAM)
#define delay_5us         US_TO_DELAY_LOOPS_EX(5,     CPU_CLK, DELAY_LOOP_CYCLES_ASM_RAM)
#define delay_10us        US_TO_DELAY_LOOPS_EX(10,    CPU_CLK, DELAY_LOOP_CYCLES_ASM_RAM)
#define delay_40us        US_TO_DELAY_LOOPS_EX(40,    CPU_CLK, DELAY_LOOP_CYCLES_ASM_RAM)
#define delay_100us       US_TO_DELAY_LOOPS_EX(100,   CPU_CLK, DELAY_LOOP_CYCLES_ASM_RAM)
#define delay_40ms        US_TO_DELAY_LOOPS_EX(40000, CPU_CLK, DELAY_LOOP_CYCLES_ASM_RAM)

//#define delay_1us         2
//#define delay_5us         10
//#define delay_10us        20
//#define delay_40us        80
//#define delay_100us       200
//#define delay_40ms        80000

void      MDR_EEPROM_ErasePage (uint32_t address);
void      MDR_EEPROM_EraseFull(void);


#if defined (USE_MDR1986VE4)
  void      MDR_EEPROM_Write(uint32_t address, uint32_t data, uint32_t maskIFREN);
#else
  void      MDR_EEPROM_Write(uint32_t address, uint32_t data);
#endif
uint32_t    MDR_EEPROM_Read (uint32_t address);



#endif //_MDR_DEVICE_DEFS_H
