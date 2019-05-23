#ifndef _MDR_RTC_VE8x_DEFS_H
#define _MDR_RTC_VE8x_DEFS_H

// Определения блока BKP, общие для всех МК

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

typedef struct {
      __IOM MDR_OnOff  OWF        : 1;            /*!< [0..0] CNT Overflow flag, clear by set 1                                  */
      __IOM MDR_OnOff  SECF       : 1;            /*!< [1..1] DIV == PRL Event, clear by set 1                                   */
      __IOM MDR_OnOff  ALRF       : 1;            /*!< [2..2] CNT == ALRM Event, clear by set 1                                  */
      __IOM MDR_OnOff  OWF_IE     : 1;            /*!< [3..3] Enable IRQ by OWF                                                  */
      __IOM MDR_OnOff  SECF_IE    : 1;            /*!< [4..4] Enable IRQ by SECF                                                 */
      __IOM MDR_OnOff  ALRF_IE    : 1;            /*!< [5..5] Enable IRQ by ALRF                                                 */
      __IOM MDR_OnOff  WEC        : 1;            /*!< [6..6] RTC Busy flag                                                      */
      __IOM MDR_OnOff  CLR_ERRx   : 1;            /*!< [7..7] Clear Errors                                                       */
      __IOM MDR_OnOff  ERR_CNT    : 1;            /*!< [8..8] CNTx mistmatches                                                   */
      __IOM MDR_OnOff  ERR_DIV    : 1;            /*!< [9..9] DIVx mistmatches                                                   */
      __IOM MDR_OnOff  ERR_CM     : 1;            /*!< [10..10] Clock RTC too high                                               */
      __IOM MDR_OnOff  ERR_CC     : 1;            /*!< [11..11] Clock RTC too low                                                */
      __IOM MDR_OnOff  ERR_CNTx   : 1;            /*!< [12..12] Self channel CNT fault                                           */
      __IOM MDR_OnOff  ERR_DIVx   : 1;            /*!< [13..13] Self channel DIV fault                                           */
      __IOM MDR_OnOff  ERR_CMx    : 1;            /*!< [14..14] Self channel clock fault                                         */
      __IOM MDR_OnOff  ERR_IE     : 1;            /*!< [15..15] Enable IRQ on RTC faults                                         */
} MDR_RTC_CS_Bits;

typedef struct {
  __IOM uint32_t Value      : 20;             /*!< [19..0] RTC PRL value                                                     */
  __IM  uint32_t            : 12;
} MDR_RTC_PRL_Value;

#define MDR_BKP_RTC_PRL_Value_Pos    (0UL)                     /*!< MDR_BKP RTC_PRL_TMR0: Value (Bit 0)                   */
#define MDR_BKP_RTC_PRL_Value_Msk    (0xfffffUL)               /*!< MDR_BKP RTC_PRL_TMR0: Value (Bitfield-Mask: 0xfffff)  */


typedef struct {
  __IOM uint32_t      RTC_CNT;                /*!< (@ 0x00000130) Count periods of PRL                                       */  
  union {
    __IOM uint32_t    RTC_DIV;                /*!< (@ 0x00000134) Counts RTC Clock to get PRL value                          */    
    MDR_RTC_PRL_Value RTC_DIV_b;
  } ;  
  union {
    __IOM uint32_t    RTC_PRL;                /*!< (@ 0x00000138) Period value for DIV counter                               */
    MDR_RTC_PRL_Value RTC_PRL_b;
  } ; 
  __IOM uint32_t      RTC_ALRM;               /*!< (@ 0x0000013C) Event value for CNT counter                                */
  union {
    __IOM uint32_t    RTC_CS;                 /*!< (@ 0x00000140) RTC Control and Status                                     */
    MDR_RTC_CS_Bits   RTC_CS_b;
  } ;
} MDR_RTC_Type;

#define MDR_RTC_CS_OWF_Pos       (0UL)                     /*!< MDR_BKP RTC_CS_TMR0: OWF (Bit 0)                      */
#define MDR_RTC_CS_OWF_Msk       (0x1UL)                   /*!< MDR_BKP RTC_CS_TMR0: OWF (Bitfield-Mask: 0x01)        */
#define MDR_RTC_CS_SECF_Pos      (1UL)                     /*!< MDR_BKP RTC_CS_TMR0: SECF (Bit 1)                     */
#define MDR_RTC_CS_SECF_Msk      (0x2UL)                   /*!< MDR_BKP RTC_CS_TMR0: SECF (Bitfield-Mask: 0x01)       */
#define MDR_RTC_CS_ALRF_Pos      (2UL)                     /*!< MDR_BKP RTC_CS_TMR0: ALRF (Bit 2)                     */
#define MDR_RTC_CS_ALRF_Msk      (0x4UL)                   /*!< MDR_BKP RTC_CS_TMR0: ALRF (Bitfield-Mask: 0x01)       */
#define MDR_RTC_CS_OWF_IE_Pos    (3UL)                     /*!< MDR_BKP RTC_CS_TMR0: OWF_IE (Bit 3)                   */
#define MDR_RTC_CS_OWF_IE_Msk    (0x8UL)                   /*!< MDR_BKP RTC_CS_TMR0: OWF_IE (Bitfield-Mask: 0x01)     */
#define MDR_RTC_CS_SECF_IE_Pos   (4UL)                     /*!< MDR_BKP RTC_CS_TMR0: SECF_IE (Bit 4)                  */
#define MDR_RTC_CS_SECF_IE_Msk   (0x10UL)                  /*!< MDR_BKP RTC_CS_TMR0: SECF_IE (Bitfield-Mask: 0x01)    */
#define MDR_RTC_CS_ALRF_IE_Pos   (5UL)                     /*!< MDR_BKP RTC_CS_TMR0: ALRF_IE (Bit 5)                  */
#define MDR_RTC_CS_ALRF_IE_Msk   (0x20UL)                  /*!< MDR_BKP RTC_CS_TMR0: ALRF_IE (Bitfield-Mask: 0x01)    */
#define MDR_RTC_CS_WEC_Pos       (6UL)                     /*!< MDR_BKP RTC_CS_TMR0: WEC (Bit 6)                      */
#define MDR_RTC_CS_WEC_Msk       (0x40UL)                  /*!< MDR_BKP RTC_CS_TMR0: WEC (Bitfield-Mask: 0x01)        */
#define MDR_RTC_CS_CLR_ERRx_Pos  (7UL)                     /*!< MDR_BKP RTC_CS_TMR0: CLR_ERRx (Bit 7)                 */
#define MDR_RTC_CS_CLR_ERRx_Msk  (0x80UL)                  /*!< MDR_BKP RTC_CS_TMR0: CLR_ERRx (Bitfield-Mask: 0x01)   */
#define MDR_RTC_CS_ERR_CNT_Pos   (8UL)                     /*!< MDR_BKP RTC_CS_TMR0: ERR_CNT (Bit 8)                  */
#define MDR_RTC_CS_ERR_CNT_Msk   (0x100UL)                 /*!< MDR_BKP RTC_CS_TMR0: ERR_CNT (Bitfield-Mask: 0x01)    */
#define MDR_RTC_CS_ERR_DIV_Pos   (9UL)                     /*!< MDR_BKP RTC_CS_TMR0: ERR_DIV (Bit 9)                  */
#define MDR_RTC_CS_ERR_DIV_Msk   (0x200UL)                 /*!< MDR_BKP RTC_CS_TMR0: ERR_DIV (Bitfield-Mask: 0x01)    */
#define MDR_RTC_CS_ERR_CM_Pos    (10UL)                    /*!< MDR_BKP RTC_CS_TMR0: ERR_CM (Bit 10)                  */
#define MDR_RTC_CS_ERR_CM_Msk    (0x400UL)                 /*!< MDR_BKP RTC_CS_TMR0: ERR_CM (Bitfield-Mask: 0x01)     */
#define MDR_RTC_CS_ERR_CC_Pos    (11UL)                    /*!< MDR_BKP RTC_CS_TMR0: ERR_CC (Bit 11)                  */
#define MDR_RTC_CS_ERR_CC_Msk    (0x800UL)                 /*!< MDR_BKP RTC_CS_TMR0: ERR_CC (Bitfield-Mask: 0x01)     */
#define MDR_RTC_CS_ERR_CNTx_Pos  (12UL)                    /*!< MDR_BKP RTC_CS_TMR0: ERR_CNTx (Bit 12)                */
#define MDR_RTC_CS_ERR_CNTx_Msk  (0x1000UL)                /*!< MDR_BKP RTC_CS_TMR0: ERR_CNTx (Bitfield-Mask: 0x01)   */
#define MDR_RTC_CS_ERR_DIVx_Pos  (13UL)                    /*!< MDR_BKP RTC_CS_TMR0: ERR_DIVx (Bit 13)                */
#define MDR_RTC_CS_ERR_DIVx_Msk  (0x2000UL)                /*!< MDR_BKP RTC_CS_TMR0: ERR_DIVx (Bitfield-Mask: 0x01)   */
#define MDR_RTC_CS_ERR_CMx_Pos   (14UL)                    /*!< MDR_BKP RTC_CS_TMR0: ERR_CMx (Bit 14)                 */
#define MDR_RTC_CS_ERR_CMx_Msk   (0x4000UL)                /*!< MDR_BKP RTC_CS_TMR0: ERR_CMx (Bitfield-Mask: 0x01)    */
#define MDR_RTC_CS_ERR_IE_Pos    (15UL)                    /*!< MDR_BKP RTC_CS_TMR0: ERR_IE (Bit 15)                  */
#define MDR_RTC_CS_ERR_IE_Msk    (0x8000UL)                /*!< MDR_BKP RTC_CS_TMR0: ERR_IE (Bitfield-Mask: 0x01)     */




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

#endif  //_MDR_RTC_VE8x_DEFS_H
