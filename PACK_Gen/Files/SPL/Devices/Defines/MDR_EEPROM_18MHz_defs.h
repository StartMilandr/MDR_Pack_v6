#ifndef _MDR_EEPROM_36MHZ_DEFS_H
#define _MDR_EEPROM_36MHZ_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "MDR_Types.h"

/* ========================================  Start of section using anonymous unions  ======================================== */
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
  #pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif
/* ========================================  Start of section using anonymous unions  ======================================== */

/* ========================================================  EEPROM Size  ======================================================== */
#define MDR_EEPROM_MAIN_BLOCK_WORD_COUNT     0x2000UL                               // 8192 32bit words in Block
#define MDR_EEPROM_MAIN_BLOCK_SIZE          (4 * MDR_EEPROM_MAIN_BLOCK_WORD_COUNT)  // 32KB
#define MDR_EEPROM_MAIN_BLOCK_COUNT          4                                      // 128KB in Total

#define MDR_EEPROM_INFO_BLOCK_WORD_COUNT     0x0200UL                               // 512 32bit words in Block
#define MDR_EEPROM_INFO_BLOCK_SIZE          (4 * MDR_EEPROM_INFO_BLOCK_WORD_COUNT)  // 2KB
#define MDR_EEPROM_INFO_BLOCK_COUNT          4                                      // 8KB in Total

#define MDR_EEPROM_PAGE_WORD_COUNT           128                                    // 32bit words in Page
#define MDR_EEPROM_PAGE_SIZE                (4 * MDR_EEPROM_PAGE_WORD_COUNT)        // 512Byte in Page

#define MDR_EEPROM_MAIN_BLOCK_PAGE_COUNT     64                                     // 64  Pages in Main Block
#define MDR_EEPROM_INFO_BLOCK_PAGE_COUNT     4                                      // 4   Pages in Info Block
#define MDR_EEPROM_MAIN_PAGE_COUNT           256                                    // 256 Pages in Total
#define MDR_EEPROM_INFO_PAGE_COUNT           16                                     // 16  Pages in Total


/* ========================================================  EEPROM_CMD  ========================================================= */
#define MDR_EEPROM_18MHz

typedef enum {
  EEPROM_IFREN_Main = 0,
  EEPROM_IFREN_Info = 1
} MDR_EEPROM_IFREN;

typedef enum {
  EEPROM_CON_Bus  = 0,
  EEPROM_CON_Regs = 1
} MDR_EEPROM_CON;

typedef enum {
  EEPROM_NVSTR_Read  = 0,
  EEPROM_NVSTR_WriteErase = 1
} MDR_EEPROM_NVSTR;

typedef enum {                                            /*!< MDR_EEPROM_CMD_DELAY                                          */
  EEPROM_Delay_le18MHz       = 0,                         /*!< le18MHz : CPU freq is up to 18MHz                             */
  EEPROM_Delay_le36MHz       = 1,                         /*!< le36MHz : CPU freq is up to 36MHz                             */
} MDR_EEPROM_DELAY;

typedef struct {
      __IOM MDR_EEPROM_CON      CON       : 1;            /*!< [0..0] Enable memory access through EEPROM controller          */
      __IOM MDR_OnOff           WR        : 1;            /*!< [1..1] Write operation                                         */
      __IOM MDR_OnOff           RD        : 1;            /*!< [2..2] Read operation                                          */
      __IOM MDR_EEPROM_DELAY    DELAY     : 3;            /*!< [5..3] Memory access CPU delay tacts                           */
      __IOM MDR_OnOff           XE        : 1;            /*!< [6..6] Enable ADDR[16..9]                                      */
      __IOM MDR_OnOff           YE        : 1;            /*!< [7..7] Enable ADDR[8..2]                                       */
      __IOM MDR_OnOff           SE        : 1;            /*!< [8..8] RD Amplifier enable                                     */
      __IOM MDR_EEPROM_IFREN    IFREN     : 1;            /*!< [9..9] Select main or info memory                              */
      __IOM MDR_OnOff           ERASE     : 1;            /*!< [10..10] Erase string at ADDR[16:0]                            */
      __IOM MDR_OnOff           MAS1      : 1;            /*!< [11..11] Erase whole block with ERASE                          */
      __IOM MDR_OnOff           PROG      : 1;            /*!< [12..12] Programm EEPROM_DI to ADDR[16:0]                      */
      __IOM MDR_EEPROM_NVSTR    NVSTR     : 1;            /*!< [13..13] Memory access mode                                   */
      __I   uint32_t                      : 18;
} MDR_EEPROM_CMD_Bits;

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


#define MDR_EEPROM_CMD_CON_Pos            (0UL)                     /*!< MDR_EEPROM CMD: CON (Bit 0)                           */
#define MDR_EEPROM_CMD_CON_Msk            (0x1UL)                   /*!< MDR_EEPROM CMD: CON (Bitfield-Mask: 0x01)             */
#define MDR_EEPROM_CMD_WR_Pos             (1UL)                     /*!< MDR_EEPROM CMD: WR (Bit 1)                            */
#define MDR_EEPROM_CMD_WR_Msk             (0x2UL)                   /*!< MDR_EEPROM CMD: WR (Bitfield-Mask: 0x01)              */
#define MDR_EEPROM_CMD_RD_Pos             (2UL)                     /*!< MDR_EEPROM CMD: RD (Bit 2)                            */
#define MDR_EEPROM_CMD_RD_Msk             (0x4UL)                   /*!< MDR_EEPROM CMD: RD (Bitfield-Mask: 0x01)              */
#define MDR_EEPROM_CMD_DELAY_Pos          (3UL)                     /*!< MDR_EEPROM CMD: DELAY (Bit 3)                         */
#define MDR_EEPROM_CMD_DELAY_Msk          (0x38UL)                  /*!< MDR_EEPROM CMD: DELAY (Bitfield-Mask: 0x07)           */
#define MDR_EEPROM_CMD_XE_Pos             (6UL)                     /*!< MDR_EEPROM CMD: XE (Bit 6)                            */
#define MDR_EEPROM_CMD_XE_Msk             (0x40UL)                  /*!< MDR_EEPROM CMD: XE (Bitfield-Mask: 0x01)              */
#define MDR_EEPROM_CMD_YE_Pos             (7UL)                     /*!< MDR_EEPROM CMD: YE (Bit 7)                            */
#define MDR_EEPROM_CMD_YE_Msk             (0x80UL)                  /*!< MDR_EEPROM CMD: YE (Bitfield-Mask: 0x01)              */
#define MDR_EEPROM_CMD_SE_Pos             (8UL)                     /*!< MDR_EEPROM CMD: SE (Bit 8)                            */
#define MDR_EEPROM_CMD_SE_Msk             (0x100UL)                 /*!< MDR_EEPROM CMD: SE (Bitfield-Mask: 0x01)              */
#define MDR_EEPROM_CMD_IFREN_Pos          (9UL)                     /*!< MDR_EEPROM CMD: IFREN (Bit 9)                         */
#define MDR_EEPROM_CMD_IFREN_Msk          (0x200UL)                 /*!< MDR_EEPROM CMD: IFREN (Bitfield-Mask: 0x01)           */
#define MDR_EEPROM_CMD_ERASE_Pos          (10UL)                    /*!< MDR_EEPROM CMD: ERASE (Bit 10)                        */
#define MDR_EEPROM_CMD_ERASE_Msk          (0x400UL)                 /*!< MDR_EEPROM CMD: ERASE (Bitfield-Mask: 0x01)           */
#define MDR_EEPROM_CMD_MAS1_Pos           (11UL)                    /*!< MDR_EEPROM CMD: MAS1 (Bit 11)                         */
#define MDR_EEPROM_CMD_MAS1_Msk           (0x800UL)                 /*!< MDR_EEPROM CMD: MAS1 (Bitfield-Mask: 0x01)            */
#define MDR_EEPROM_CMD_PROG_Pos           (12UL)                    /*!< MDR_EEPROM CMD: PROG (Bit 12)                         */
#define MDR_EEPROM_CMD_PROG_Msk           (0x1000UL)                /*!< MDR_EEPROM CMD: PROG (Bitfield-Mask: 0x01)            */
#define MDR_EEPROM_CMD_NVSTR_Pos          (13UL)                    /*!< MDR_EEPROM CMD: NVSTR (Bit 13)                        */
#define MDR_EEPROM_CMD_NVSTR_Msk          (0x2000UL)                /*!< MDR_EEPROM CMD: NVSTR (Bitfield-Mask: 0x01)           */

/* =============================================  EEPROM Block  ========================================================= */
typedef struct {                                /*!< (@ 0x40018000) MDR_EEPROM Structure                                       */  
  union {
    __IOM uint32_t      CMD;                    /*!< (@ 0x00000000) EEPROM Control register                                    */
    MDR_EEPROM_CMD_Bits CMD_b;
  } ;
  __IOM uint32_t        ADDR;                   /*!< (@ 0x00000004) Address register                                           */
  __IOM uint32_t        DI;                     /*!< (@ 0x00000008) Write data register                                        */
  __IOM uint32_t        DO;                     /*!< (@ 0x0000000C) Read data register                                         */
  __IOM uint32_t        KEY;                    /*!< (@ 0x00000010) Unlock block register                                      */
} MDR_EEPROM_Type; 

#define EEPROM_KEY_ACCESS_CODE           0x8AAA5551UL

/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#endif
/* =========================================  End of section using anonymous unions  ========================================= */

#ifdef __cplusplus
}
#endif

#endif  //_MDR_EEPROM_36MHZ_DEFS_H
