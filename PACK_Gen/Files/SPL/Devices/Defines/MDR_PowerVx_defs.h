#ifndef _MDR_POWER_Vx_DEFS_H
#define _MDR_POWER_Vx_DEFS_H

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
typedef enum {
  PWR_BUcc_1V8          = 0,
  PWR_BUcc_2V2          = 1,
  PWR_BUcc_2V6          = 2,
  PWR_BUcc_3V0          = 3,
} MDR_PWR_LevelBUcc;

#define MDR_PWR_LevelBUcc_Min  PWR_BUcc_1V8
#define MDR_PWR_LevelBUcc_Max  PWR_BUcc_3V0


typedef enum {
  PWR_Ucc_2V0           = 0,
  PWR_Ucc_2V2           = 1,
  PWR_Ucc_2V4           = 2,
  PWR_Ucc_2V6           = 3,
  PWR_Ucc_2V8           = 4,
  PWR_Ucc_3V0           = 5,
  PWR_Ucc_3V2           = 6,
  PWR_Ucc_3V4           = 7,
} MDR_PWR_LevelUcc;

#define MDR_PWR_LevelUcc_Min  PWR_Ucc_2V0
#define MDR_PWR_LevelUcc_Max  PWR_Ucc_3V4

typedef struct {
      __IOM MDR_OnOff         PVDEN  : 1;       /*!< [0..0] Enable Ucc detector                                                */
      __IOM MDR_PWR_LevelBUcc PBLS   : 2;       /*!< [2..1] BUcc compare level                                                 */
      __IOM MDR_PWR_LevelUcc  PLS    : 3;       /*!< [5..3] Ucc compare level                                                  */
      __IOM MDR_OnOff         PVBD   : 1;       /*!< [6..6] Event on BUcc gt PBLS                                              */
      __IOM MDR_OnOff         PVD    : 1;       /*!< [7..7] Event on Ucc gt PLS                                                */
      __IOM MDR_OnOff         IEPVBD : 1;       /*!< [8..8] Enable IRQ by PVBD event                                           */
      __IOM MDR_OnOff         IEPVD  : 1;       /*!< [9..9] Enable IRQ by PVD event                                            */
      __IOM MDR_OnOff         INVB   : 1;       /*!< [10..10] PVBD event on BUcc lt PBLS                                       */
      __IOM MDR_OnOff         INV    : 1;       /*!< [11..11] PVD event on BUcc lt PBLS                                        */
      __IOM MDR_OnOff         PVDBEN : 1;       /*!< [12..12] Enable BUcc detector                                             */
      __IM  uint32_t                 : 19;
} MDR_PWR_PVDCS_Bits;

#define MDR_PWR_PVDCS_PVDEN_Pos         (0UL)                     /*!< MDR_Power PVDCS: PVDEN (Bit 0)                        */
#define MDR_PWR_PVDCS_PVDEN_Msk         (0x1UL)                   /*!< MDR_Power PVDCS: PVDEN (Bitfield-Mask: 0x01)          */
#define MDR_PWR_PVDCS_PBLS_Pos          (1UL)                     /*!< MDR_Power PVDCS: PBLS (Bit 1)                         */
#define MDR_PWR_PVDCS_PBLS_Msk          (0x6UL)                   /*!< MDR_Power PVDCS: PBLS (Bitfield-Mask: 0x03)           */
#define MDR_PWR_PVDCS_PLS_Pos           (3UL)                     /*!< MDR_Power PVDCS: PLS (Bit 3)                          */
#define MDR_PWR_PVDCS_PLS_Msk           (0x38UL)                  /*!< MDR_Power PVDCS: PLS (Bitfield-Mask: 0x07)            */
#define MDR_PWR_PVDCS_PVBD_Pos          (6UL)                     /*!< MDR_Power PVDCS: PVBD (Bit 6)                         */
#define MDR_PWR_PVDCS_PVBD_Msk          (0x40UL)                  /*!< MDR_Power PVDCS: PVBD (Bitfield-Mask: 0x01)           */
#define MDR_PWR_PVDCS_PVD_Pos           (7UL)                     /*!< MDR_Power PVDCS: PVD (Bit 7)                          */
#define MDR_PWR_PVDCS_PVD_Msk           (0x80UL)                  /*!< MDR_Power PVDCS: PVD (Bitfield-Mask: 0x01)            */
#define MDR_PWR_PVDCS_IEPVBD_Pos        (8UL)                     /*!< MDR_Power PVDCS: IEPVBD (Bit 8)                       */
#define MDR_PWR_PVDCS_IEPVBD_Msk        (0x100UL)                 /*!< MDR_Power PVDCS: IEPVBD (Bitfield-Mask: 0x01)         */
#define MDR_PWR_PVDCS_IEPVD_Pos         (9UL)                     /*!< MDR_Power PVDCS: IEPVD (Bit 9)                        */
#define MDR_PWR_PVDCS_IEPVD_Msk         (0x200UL)                 /*!< MDR_Power PVDCS: IEPVD (Bitfield-Mask: 0x01)          */
#define MDR_PWR_PVDCS_INVB_Pos          (10UL)                    /*!< MDR_Power PVDCS: INVB (Bit 10)                        */
#define MDR_PWR_PVDCS_INVB_Msk          (0x400UL)                 /*!< MDR_Power PVDCS: INVB (Bitfield-Mask: 0x01)           */
#define MDR_PWR_PVDCS_INV_Pos           (11UL)                    /*!< MDR_Power PVDCS: INV (Bit 11)                         */
#define MDR_PWR_PVDCS_INV_Msk           (0x800UL)                 /*!< MDR_Power PVDCS: INV (Bitfield-Mask: 0x01)            */
#define MDR_PWR_PVDCS_PVDBEN_Pos        (12UL)                    /*!< MDR_Power PVDCS: PVDBEN (Bit 12)                      */
#define MDR_PWR_PVDCS_PVDBEN_Msk        (0x1000UL)                /*!< MDR_Power PVDCS: PVDBEN (Bitfield-Mask: 0x01)         */

#define MDR_PWR_PVDCS_ENA_MSK   (MDR_PWR_PVDCS_PVDEN_Msk | MDR_PWR_PVDCS_PVDBEN_Msk)

typedef union {
    __IOM uint32_t     PVDCS;                       /*!< (@ 0x00000000) Control-Status register                                    */
    MDR_PWR_PVDCS_Bits PVDCS_b;
} MDR_PWR_Type;



typedef enum {  
  PWR_xUcc_Higher = 0,
  PWR_xUcc_Lower  = 1,  
} MDR_Power_EventCondition;

typedef struct {
      MDR_OnOff                 enaUcc          : 1;       /*!< [0..0] Enable Ucc detector                                                */
      MDR_PWR_LevelBUcc         levelBUcc       : 2;       /*!< [2..1] BUcc compare level                                                 */
      MDR_PWR_LevelUcc          levelUcc        : 3;       /*!< [5..3] Ucc compare level                                                  */  
      MDR_OnOff                 eventBUcc       : 1;       /*!< [6..6] Event on BUcc gt PBLS                                              */
      MDR_OnOff                 eventUcc        : 1;       /*!< [7..7] Event on Ucc gt PLS                                                */  
      MDR_OnOff                 enaEventBUccIRQ : 1;       /*!< [8..8] Enable IRQ by PVBD event                                           */
      MDR_OnOff                 enaEventUccIRQ  : 1;       /*!< [9..9] Enable IRQ by PVD event                                            */
      MDR_Power_EventCondition  condEventBUcc   : 1;       /*!< [10..10] PVBD event on BUcc lt PBLS                                       */
      MDR_Power_EventCondition  condEventUcc    : 1;       /*!< [11..11] PVD event on BUcc lt PBLS                                        */
      MDR_OnOff                 enaDUcc         : 1;       /*!< [12..12] Enable BUcc detector                                             */
      uint32_t                                  : 19;
} MDR_Power_Flags;

typedef union {
    uint32_t                Value;                       /*!< (@ 0x00000000) Control-Status register                                    */
    MDR_Power_Flags         Flags;
} MDR_Power_CtrlAndStatus;

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

#endif  //_MDR_POWER_Vx_DEFS_H
