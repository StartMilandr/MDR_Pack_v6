#ifndef _MDR_DEVICE_DEFS_VE8_H
#define _MDR_DEVICE_DEFS_VE8_H

typedef unsigned int uint32_t;

#define REG32(x) (*((volatile uint32_t *)(x)))

//==================  CORE Cortex-M   =================
#define VTOR_ADDR               0xE000ED08UL    
#define regVTOR                 REG32(VTOR_ADDR)
#define VTABLE_IND_SP           0UL
#define VTABLE_IND_Reset        1UL
#define VTABLE_IND_NMI          2UL
#define VTABLE_IND_HardFault    3UL

//==================  RST   =================

#define BKP_ADDR_CLOCK_KEY      0x40001100UL
#define BKP_ADDR_CLOCK_MAXCLK   0x40001100UL

#define regCLOCK_KEY            REG32(BKP_ADDR_CLOCK_KEY)  
#define regCLOCK_MAXCLK         REG32(BKP_ADDR_CLOCK_MAXCLK)  

typedef enum {
  MAXCLK_HSI      = 0,
  MAXCLK_HSIdiv2  = 1,
  MAXCLK_HSE0     = 2,
  MAXCLK_HSE0div2 = 3,
  MAXCLK_HSE1     = 4,
  MAXCLK_HSE1div2 = 5,
  MAXCLK_LSI      = 6,
  MAXCLK_LSE      = 7,
  MAXCLK_PLL0     = 8,
  MAXCLK_PLL1     = 9,
  MAXCLK_PLL2     = 10,
  MAXCLK_ERR      = 11,   //  Error Value - reserved
} MDR_MAXCLK_SEL;

//==================   BKP  =================

#define BKP_ADDR_KEY            0x400010F0UL

#define BKP_ADDR_REG60_TMR0     0x40001100UL
#define BKP_ADDR_REG60_TMR1     0x40001110UL
#define BKP_ADDR_REG60_TMR2     0x40001120UL

#define BKP_ADDR_REG63_TMR0     0x4000110CUL
#define BKP_ADDR_REG63_TMR1     0x4000111CUL
#define BKP_ADDR_REG63_TMR2     0x4000112CUL


#define regBKP_KEY                REG32(BKP_ADDR_KEY)  

#define regBKP_REG60_TMR0         REG32(BKP_ADDR_REG60_TMR0)  
#define regBKP_REG60_TMR1         REG32(BKP_ADDR_REG60_TMR1)  
#define regBKP_REG60_TMR2         REG32(BKP_ADDR_REG60_TMR2)  

#define regBKP_REG63_TMR0         REG32(BKP_ADDR_REG63_TMR0)  
#define regBKP_REG63_TMR1         REG32(BKP_ADDR_REG63_TMR1)  
#define regBKP_REG63_TMR2         REG32(BKP_ADDR_REG63_TMR2)  

#define MDR_BKP_REG60_PORSTn_Dis_Msk      (0x10000000UL)       /*!< MDR_BKP REG_60_TMR0: PORSTn_Dis (Bitfield-Mask: 0x01)  */

//#define MDR_BKP_REG63_HSI_On_Pos    (22UL)                    /*!< MDR_BKP REG_63_TMR0: HSI_On (Bit 22)                  */
#define MDR_BKP_REG63_HSI_On_Msk    (0x400000UL)              /*!< MDR_BKP REG_63_TMR0: HSI_On (Bitfield-Mask: 0x01)     */
//#define MDR_BKP_REG63_HSI_RDY_Pos   (23UL)                    /*!< MDR_BKP REG_63_TMR0: HSI_RDY (Bit 23)                 */
#define MDR_BKP_REG63_HSI_RDY_Msk   (0x800000UL)              /*!< MDR_BKP REG_63_TMR0: HSI_RDY (Bitfield-Mask: 0x01)    */
//#define MDR_BKP_REG63_HSI_Trim_Pos  (24UL)                    /*!< MDR_BKP REG_63_TMR0: HSI_Trim (Bit 24)                */
#define MDR_BKP_REG63_HSI_Trim_Msk  (0x3f000000UL)            /*!< MDR_BKP REG_63_TMR0: HSI_Trim (Bitfield-Mask: 0x3f)   */



//==================  OTP  ===============

//#define READ_BY_EEPROM    0
//#define FIX_DBL_READ      1

//#ifndef USE_EEPROM_Info_Bank
//  #define MEM_BANK  0
//#else
//  #define MEM_BANK  MDR_EEPROM_CMD_BIT_IFREN  // Info memory
//#endif

//#if defined(USE_MDR1986VE9x) || defined(USE_MDR1901VC1)

#define OTPSRAM_START_ADDR       0x01000000UL
#define OTPSRAM_END_ADDR        (0x01020000UL - 4UL)

#define OTPSRAM_PAGE_END_ADDR   (0x00001000UL - 4UL)
	
//#else
//  #define FLASH_ADDR_0      0
//#endif

//#if defined (USE_MDR1986VE4)
//  #define PAGE_SIZE          0x200
//  #define PAGE_COUNT         256
//#else
//  #define PAGE_SIZE          0x1000
//  #define PAGE_COUNT         32
//#endif

//#define EEPROM_KEY_ACCESS_CODE           0x8AAA5551UL

#define MDR_KEY_UNLOCK    0x8555AAA1UL


#define OTP_ADDR_KEY        	0x40006000UL
#define OTP_ADDR_CNTR       	0x40006004UL
#define OTP_ADDR_ADR         0x40006008UL
#define OTP_ADDR_WDATA       0x4000600CUL
#define OTP_ADDR_RDATA       0x40006010UL
#define OTP_ADDR_ECCCS       0x40006014UL
#define OTP_ADDR_ECCADR      0x40006018UL
#define OTP_ADDR_ECCDATA     0x4000601CUL
#define OTP_ADDR_ECCECC      0x40006020UL
#define OTP_ADDR_TINING      0x40006024UL

#define regOTP_KEY         REG32(OTP_ADDR_KEY)  
#define regOTP_CNTR        REG32(OTP_ADDR_CNTR)   
#define regOTP_ADR         REG32(OTP_ADDR_ADR)
#define regOTP_WDATA       REG32(OTP_ADDR_WDATA)
#define regOTP_RDATA       REG32(OTP_ADDR_RDATA)
#define regOTP_ECCCS       REG32(OTP_ADDR_ECCCS)
#define regOTP_ECCADR      REG32(OTP_ADDR_ECCADR)
#define regOTP_ECCDATA     REG32(OTP_ADDR_ECCDATA)
#define regOTP_ECCECC      REG32(OTP_ADDR_ECCECC)
#define regOTP_TINING      REG32(OTP_ADDR_TINING)


//-----------------------------  CNTR   ---------------------------------
#define MDR_OTP_CNTR_WAITCYCL_Pos        (0UL)                     /*!< MDR_SRAM CNTR: WAITCYCL (Bit 0)                       */
#define MDR_OTP_CNTR_WAITCYCL_Msk        (0xfUL)                   /*!< MDR_SRAM CNTR: WAITCYCL (Bitfield-Mask: 0x0f)         */
#define MDR_OTP_CNTR_REG_ACCESS_Pos      (4UL)                     /*!< MDR_SRAM CNTR: REG_ACCESS (Bit 4)                     */
#define MDR_OTP_CNTR_REG_ACCESS_Msk      (0x10UL)                  /*!< MDR_SRAM CNTR: REG_ACCESS (Bitfield-Mask: 0x01)       */
#define MDR_OTP_CNTR_CLK_Pos             (5UL)                     /*!< MDR_SRAM CNTR: CLK (Bit 5)                            */
#define MDR_OTP_CNTR_CLK_Msk             (0x20UL)                  /*!< MDR_SRAM CNTR: CLK (Bitfield-Mask: 0x01)              */
#define MDR_OTP_CNTR_OE_Pos              (7UL)                     /*!< MDR_SRAM CNTR: OE (Bit 7)                             */
#define MDR_OTP_CNTR_OE_Msk              (0x80UL)                  /*!< MDR_SRAM CNTR: OE (Bitfield-Mask: 0x01)               */
#define MDR_OTP_CNTR_WE_x00_Pos          (9UL)                     /*!< MDR_SRAM CNTR: WE_x00 (Bit 9)                         */
#define MDR_OTP_CNTR_WE_x00_Msk          (0x200UL)                 /*!< MDR_SRAM CNTR: WE_x00 (Bitfield-Mask: 0x01)           */
#define MDR_OTP_CNTR_WE_x04_Pos          (10UL)                    /*!< MDR_SRAM CNTR: WE_x04 (Bit 10)                        */
#define MDR_OTP_CNTR_WE_x04_Msk          (0x400UL)                 /*!< MDR_SRAM CNTR: WE_x04 (Bitfield-Mask: 0x01)           */
#define MDR_OTP_CNTR_WE_x08_Pos          (11UL)                    /*!< MDR_SRAM CNTR: WE_x08 (Bit 11)                        */
#define MDR_OTP_CNTR_WE_x08_Msk          (0x800UL)                 /*!< MDR_SRAM CNTR: WE_x08 (Bitfield-Mask: 0x01)           */
#define MDR_OTP_CNTR_WE_x0C_Pos          (12UL)                    /*!< MDR_SRAM CNTR: WE_x0C (Bit 12)                        */
#define MDR_OTP_CNTR_WE_x0C_Msk          (0x1000UL)                /*!< MDR_SRAM CNTR: WE_x0C (Bitfield-Mask: 0x01)           */
#define MDR_OTP_CNTR_WE_ECC_Pos          (13UL)                    /*!< MDR_SRAM CNTR: WE_ECC (Bit 13)                        */
#define MDR_OTP_CNTR_WE_ECC_Msk          (0x2000UL)                /*!< MDR_SRAM CNTR: WE_ECC (Bitfield-Mask: 0x01)           */
#define MDR_OTP_CNTR_CEN_Pos             (14UL)                    /*!< MDR_SRAM CNTR: CEN (Bit 14)                           */
#define MDR_OTP_CNTR_CEN_Msk             (0x4000UL)                /*!< MDR_SRAM CNTR: CEN (Bitfield-Mask: 0x01)              */
#define MDR_OTP_CNTR_WECC_Pos            (16UL)                    /*!< MDR_SRAM CNTR: WECC (Bit 16)                          */
#define MDR_OTP_CNTR_WECC_Msk            (0xff0000UL)              /*!< MDR_SRAM CNTR: WECC (Bitfield-Mask: 0xff)             */
#define MDR_OTP_CNTR_RECC_Pos            (24UL)                    /*!< MDR_SRAM CNTR: RECC (Bit 24)                          */
#define MDR_OTP_CNTR_RECC_Msk            (0xff000000UL)            /*!< MDR_SRAM CNTR: RECC (Bitfield-Mask: 0xff)             */


#define MDR_OTP_CNTR_WAITCYCL_SRAM_Min  1
#define MDR_OTP_CNTR_WE_ALL_Pos         MDR_OTP_CNTR_WE_x00_Pos
#define MDR_OTP_CNTR_WE_ALL_Msk        (MDR_OTP_CNTR_WE_x00_Msk | MDR_OTP_CNTR_WE_x04_Msk | MDR_OTP_CNTR_WE_x08_Msk | MDR_OTP_CNTR_WE_x0C_Msk | MDR_OTP_CNTR_WE_ECC_Msk)

//-----------------------------  TEST_TUNING   ---------------------------------
#define MDR_OTP_TUNING_SRAM_TIME_Pos    (0UL)                  /*!< MDR_SRAM TEST_TUNING: SRAM_TIMEOUT (Bit 0)            */
#define MDR_OTP_TUNING_SRAM_TIME_Msk    (0x7UL)                /*!< MDR_SRAM TEST_TUNING: SRAM_TIMEOUT (Bitfield-Mask: 0x07) */
#define MDR_OTP_TUNING_TE_Pos           (4UL)                  /*!< MDR_SRAM TEST_TUNING: TE (Bit 4)                      */
#define MDR_OTP_TUNING_TE_Msk           (0x30UL)               /*!< MDR_SRAM TEST_TUNING: TE (Bitfield-Mask: 0x03)        */
#define MDR_OTP_TUNING_OTP_TIME_Pos     (8UL)                  /*!< MDR_SRAM TEST_TUNING: TIME_TUNING (Bit 8)             */
#define MDR_OTP_TUNING_OTP_TIME_Msk     (0x700UL)              /*!< MDR_SRAM TEST_TUNING: TIME_TUNING (Bitfield-Mask: 0x07) */
#define MDR_OTP_TUNING_OTP_REPL_Pos     (16UL)                 /*!< MDR_SRAM TEST_TUNING: REPL_TUNING (Bit 16)            */
#define MDR_OTP_TUNING_OTP_REPL_Msk     (0xf0000UL)            /*!< MDR_SRAM TEST_TUNING: REPL_TUNING (Bitfield-Mask: 0x0f) */

//  SRAM_TIME values
typedef enum {                            /*!< MDR_SRAM_TEST_TUNING_SRAM_TIMEOUT                                    */
  MDR_OTP_TUNING_SRAM_Time_HardMax  = 0,  /*!< Time_HardMax : SRAM Read Timeout                                     */
  MDR_OTP_TUNING_SRAM_Time_Hard2    = 1,  /*!< Time_Hard2 : SRAM Read Timeout                                       */
  MDR_OTP_TUNING_SRAM_Time_Norm     = 2,  /*!< Time_Norm : SRAM Read Timeout                                        */
  MDR_OTP_TUNING_SRAM_Time_Easy1    = 3,  /*!< Time_Easy1 : SRAM Read Timeout                                       */
  MDR_OTP_TUNING_SRAM_Time_Easy2    = 4,  /*!< Time_Easy2 : SRAM Read Timeout                                       */
  MDR_OTP_TUNING_SRAM_Time_Easy3    = 5,  /*!< Time_Easy3 : SRAM Read Timeout                                       */
  MDR_OTP_TUNING_SRAM_Time_Easy4    = 6,  /*!< Time_Easy4 : SRAM Read Timeout                                       */
  MDR_OTP_TUNING_SRAM_Time_EasyMax  = 7,  /*!< Time_EasyMax : SRAM Read Timeout                                     */
} MDR_OTP_TUNING_SRAM_Time;

#define MDR_OTP_TUNING_SRAM_Time_HardMax_Msk  ((uint32_t)MDR_OTP_TUNING_SRAM_Time_HardMax << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_Hard2_Msk    ((uint32_t)MDR_OTP_TUNING_SRAM_Time_Hard2   << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_Norm_Msk     ((uint32_t)MDR_OTP_TUNING_SRAM_Time_Norm    << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_Easy1_Msk    ((uint32_t)MDR_OTP_TUNING_SRAM_Time_Easy1   << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_Easy2_Msk    ((uint32_t)MDR_OTP_TUNING_SRAM_Time_Easy2   << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_Easy3_Msk    ((uint32_t)MDR_OTP_TUNING_SRAM_Time_Easy3   << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_Easy4_Msk    ((uint32_t)MDR_OTP_TUNING_SRAM_Time_Easy4   << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_EasyMax_Msk  ((uint32_t)MDR_OTP_TUNING_SRAM_Time_EasyMax << MDR_OTP_TUNING_SRAM_TIME_Pos)

//  OTP_TIME values
typedef enum {                          /*!< MDR_OTP_TEST_TUNING_TIME_TUNING                                           */
  MDR_OTP_TUNING_OTP_Time_HardMax = 0,  /*!< Time_HardMax : Read Timeout                                            */
  MDR_OTP_TUNING_OTP_Time_Hard2   = 1,  /*!< Time_Hard2 : Read Timeout                                                */
  MDR_OTP_TUNING_OTP_Time_Hard1   = 2,  /*!< Time_Hard1 : Read Timeout                                                */
  MDR_OTP_TUNING_OTP_Time_Norm    = 3,  /*!< Time_Norm : Read Timeout                                                  */
  MDR_OTP_TUNING_OTP_Time_Easy1   = 4,  /*!< Time_Easy1 : Read Timeout                                                */
  MDR_OTP_TUNING_OTP_Time_Easy2   = 5,  /*!< Time_Easy2 : Read Timeout                                                */
  MDR_OTP_TUNING_OTP_Time_Easy3   = 6,  /*!< Time_Easy3 : Read Timeout                                                */
  MDR_OTP_TUNING_OTP_Time_EasyMax = 7,  /*!< Time_EasyMax : Read Timeout                                            */
} MDR_OTP_TUNING_OTP_Time;

#define MDR_OTP_TUNING_OTP_Time_HardMax_Msk   ((uint32_t)MDR_OTP_TUNING_OTP_Time_HardMax  << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Hard2_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Hard2    << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Hard1_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Hard1    << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Norm_Msk      ((uint32_t)MDR_OTP_TUNING_OTP_Time_Norm     << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Easy1_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Easy1    << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Easy2_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Easy2    << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Easy3_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Easy3    << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_EasyMax_Msk   ((uint32_t)MDR_OTP_TUNING_OTP_Time_EasyMax  << MDR_OTP_TUNING_SRAM_TIME_Pos)

//  OTP_REPL values
typedef enum {                          /*!< MDR_OTP_TEST_TUNING_REPL_TUNING                                           */
  MDR_OTP_TUNING_OTP_Repl_EasyMax = 0,  /*!< Repl_EasyMax : Read Resistance                                         */
  MDR_OTP_TUNING_OTP_Repl_Easy1   = 1,  /*!< Repl_Easy1 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Norm    = 2,  /*!< Repl_Norm : Read Resistance                                               */
  MDR_OTP_TUNING_OTP_Repl_Hard1   = 3,  /*!< Repl_Hard1 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard2   = 4,  /*!< Repl_Hard2 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard3   = 5,  /*!< Repl_Hard3 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard4   = 6,  /*!< Repl_Hard4 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard5   = 7,  /*!< Repl_Hard5 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard6   = 8,  /*!< Repl_Hard6 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard7   = 9,  /*!< Repl_Hard7 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard8   = 10, /*!< Repl_Hard8 : Read Resistance                                            */
  MDR_OTP_TUNING_OTP_Repl_Hard9   = 11, /*!< Repl_Hard9 : Read Resistance                                            */
  MDR_OTP_TUNING_OTP_Repl_Hard10  = 12, /*!< Repl_Hard10 : Read Resistance                                          */
  MDR_OTP_TUNING_OTP_Repl_Hard11  = 13, /*!< Repl_Hard11 : Read Resistance                                          */
  MDR_OTP_TUNING_OTP_Repl_Hard12  = 14, /*!< Repl_Hard12 : Read Resistance                                          */
  MDR_OTP_TUNING_OTP_Repl_HardMax = 15, /*!< Repl_HardMax : Read Resistance                                        */
} MDR_OTP_TUNING_OTP_Repl;

#define MDR_OTP_TUNING_OTP_Repl_EasyMax_Msk   ((uint32_t)MDR_OTP_TUNING_OTP_Repl_EasyMax  << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Easy1_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Easy1    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Norm_Msk      ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Norm     << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard1_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard1    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard2_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard2    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard3_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard3    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard4_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard4    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard5_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard5    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard6_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard6    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard7_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard7    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard8_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard8    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard9_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard9    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard10_Msk    ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard10   << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard11_Msk    ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard11   << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard12_Msk    ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard12   << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_HardMax_Msk   ((uint32_t)MDR_OTP_TUNING_OTP_Repl_HardMax  << MDR_OTP_TUNING_OTP_REPL_Pos)





////  HSI = 8MHz, 8 clocks = 1us
////  Compiler min while cycle duration ~ 4 clocks
//#define delay_1us         2
//#define delay_5us         10
//#define delay_10us        20
//#define delay_40us        80
//#define delay_100us       200
//#define delay_40ms        80000

//void      MDR_EEPROM_ErasePage (uint32_t address);
//void      MDR_EEPROM_EraseFull(void);

//#if defined (USE_MDR1986VE4)
//  void      MDR_EEPROM_Write(uint32_t address, uint32_t data, uint32_t maskIFREN);
//#else
//  void      MDR_EEPROM_Write(uint32_t address, uint32_t data);
//#endif
//uint32_t  MDR_EEPROM_Read (uint32_t address);



#endif //_MDR_DEVICE_DEFS_VE8_H
