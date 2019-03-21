#ifndef _MDR_TIMER_VE13_DEFS_H
#define _MDR_TIMER_VE13_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <MDR_Types.h>
#include <MDR_Timer_Defs.h>

#define TIMER_HAS_DMA_REx
  
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

/* ========================================  CNT, ARR, CCR, CCR1 ===================================================== */
#define uint_tim        uint32_t
#define TIM_MAX_VALUE   0xFFFFFFFF

typedef struct {
  __IOM uint_tim    Value      : 32;    /*!< [31..0] Counter Value                                                     */
} MDR_TIM_VALUE_Bits;


/* ========================================  CNTRL ======================================================= */

typedef enum {                          /*!< MDR_TIMER1_CNTRL_CNT_MODE                                                 */
  TIM_CntMode_DIR_TimClk       = 0,     /*!< DIR_TIM_CLK : Count TIM_Clock pulses with DIR direction                   */
  TIM_CntMode_UpDown_TimClk    = 1,     /*!< UpDown_TIM_CLK : Count TIM_Clock pulses UP and Down                       */
  TIM_CntMode_DIR_ExtEvents    = 2,     /*!< DIR_ExtEvents : Count External Events with DIR direction                  */
  //TIM_CntMode_UpDown_ExtEvents = 3,     /*!< UpDown_ExtEvents : Count External Events UP and Down                     */
} MDR_TIM_CntMode;
  
typedef enum {                          /*!< MDR_TIMER1_CNTRL_EVENT_SEL                                                */
  MDR_TIM_Event_SEL_Rise_TIM_CLK = 0,   /*!< Rise_TIM_CLK : CNT counts from 0 to ARR                                   */
  MDR_TIM_Event_CNT_eq_ARR_TIM1  = 1,   /*!< CNT_eq_ARR_TIM1 : CNT gets ARR in Timer1                                 */
  MDR_TIM_Event_CNT_eq_ARR_TIM2  = 2,   /*!< CNT_eq_ARR_TIM2 : CNT gets ARR in Timer2                                 */
  MDR_TIM_Event_CNT_eq_ARR_TIM3  = 3,   /*!< CNT_eq_ARR_TIM3 : CNT gets ARR in Timer3                                 */
  MDR_TIM_Event_Ch1              = 4,   /*!< Event_Ch1 : Event in Channel1                                             */
  MDR_TIM_Event_Ch2              = 5,   /*!< Event_Ch2 : Event in Channel2                                             */
  MDR_TIM_Event_Ch3              = 6,   /*!< Event_Ch3 : Event in Channel3                                             */
  MDR_TIM_Event_Ch4              = 7,   /*!< Event_Ch4 : Event in Channel4                                             */
  MDR_TIM_Event_Rise_ETR         = 8,   /*!< Rise_ETR : Rise front in ETR pin                                          */
  MDR_TIM_Event_Fall_ETR         = 9,   /*!< Fall_ETR : Fall front in ETR pin                                          */
  MDR_TIM_Event_CNT_eq_ARR_TIM4  = 10,  /*!< CNT_eq_ARR_TIM4 : CNT gets ARR in Timer4                                */
} MDR_TIM_Event;

typedef struct {
  __IOM MDR_OnOff       CNT_EN     : 1;            /*!< [0..0] Timer Enable                                                       */
  __IOM MDR_OnOff       ARRB_EN    : 1;            /*!< [1..1] ARR update mode                                                    */
  __IOM MDR_OnOff       WR_CMPL    : 1;            /*!< [2..2] Can write to CNT, ARR, PSG                                         */
  __IOM MDR_TIM_Dir     DIR        : 1;            /*!< [3..3] Count Direction                                                    */
  __IOM MDR_TIM_FDTS    FDTS       : 2;            /*!< [5..4] Select Data Sampling frequency                                     */
  __IOM MDR_TIM_CntMode CNT_MODE   : 2;            /*!< [7..6] Counting mode                                                      */
  __IOM MDR_TIM_Event   EVENT_SEL  : 4;            /*!< [11..8] Events for counting                                               */
} MDR_TIM_CNTRL_Bits;

#define MDR_TIMER_CNTRL_CNT_EN_Pos       (0UL)                     /*!< MDR_TIMER1 CNTRL: CNT_EN (Bit 0)                      */
#define MDR_TIMER_CNTRL_CNT_EN_Msk       (0x1UL)                   /*!< MDR_TIMER1 CNTRL: CNT_EN (Bitfield-Mask: 0x01)        */
#define MDR_TIMER_CNTRL_ARRB_EN_Pos      (1UL)                     /*!< MDR_TIMER1 CNTRL: ARRB_EN (Bit 1)                     */
#define MDR_TIMER_CNTRL_ARRB_EN_Msk      (0x2UL)                   /*!< MDR_TIMER1 CNTRL: ARRB_EN (Bitfield-Mask: 0x01)       */
#define MDR_TIMER_CNTRL_WR_CMPL_Pos      (2UL)                     /*!< MDR_TIMER1 CNTRL: WR_CMPL (Bit 2)                     */
#define MDR_TIMER_CNTRL_WR_CMPL_Msk      (0x4UL)                   /*!< MDR_TIMER1 CNTRL: WR_CMPL (Bitfield-Mask: 0x01)       */
#define MDR_TIMER_CNTRL_DIR_Pos          (3UL)                     /*!< MDR_TIMER1 CNTRL: DIR (Bit 3)                         */
#define MDR_TIMER_CNTRL_DIR_Msk          (0x8UL)                   /*!< MDR_TIMER1 CNTRL: DIR (Bitfield-Mask: 0x01)           */
#define MDR_TIMER_CNTRL_FDTS_Pos         (4UL)                     /*!< MDR_TIMER1 CNTRL: FDTS (Bit 4)                        */
#define MDR_TIMER_CNTRL_FDTS_Msk         (0x30UL)                  /*!< MDR_TIMER1 CNTRL: FDTS (Bitfield-Mask: 0x03)          */
#define MDR_TIMER_CNTRL_CNT_MODE_Pos     (6UL)                     /*!< MDR_TIMER1 CNTRL: CNT_MODE (Bit 6)                    */
#define MDR_TIMER_CNTRL_CNT_MODE_Msk     (0xc0UL)                  /*!< MDR_TIMER1 CNTRL: CNT_MODE (Bitfield-Mask: 0x03)      */
#define MDR_TIMER_CNTRL_EVENT_SEL_Pos    (8UL)                     /*!< MDR_TIMER1 CNTRL: EVENT_SEL (Bit 8)                   */
#define MDR_TIMER_CNTRL_EVENT_SEL_Msk    (0xf00UL)                 /*!< MDR_TIMER1 CNTRL: EVENT_SEL (Bitfield-Mask: 0x0f)     */

#define MDR_TIMER_CNTRL_DIR_UP           0UL
#define MDR_TIMER_CNTRL_DIR_DOWN         MDR_TIMER_CNTRL_DIR_Msk


/* =========================================================================================================================== */
/* ================                                        MDR_TIMER1                                         ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40070000) MDR_TIMER1 Structure                                       */  
  union {
    __IOM uint32_t      CNT;                         /*!< (@ 0x00000000) Counter register                                           */
    MDR_TIM_VALUE_Bits  CNT_b;
  } ;
  union {
    __IOM uint32_t      PSG;                         /*!< (@ 0x00000004) Presample Gain                                             */
    MDR_TIM_PSG_Bits    PSG_b;
  };
  union {
    __IOM uint32_t      ARR;                         /*!< (@ 0x00000008) Counter Period                                             */
    MDR_TIM_VALUE_Bits  ARR_b;
  } ; 
  union {
    __IOM uint32_t      CNTRL;                       /*!< (@ 0x0000000C) Timer Control                                              */
    MDR_TIM_CNTRL_Bits  CNTRL_b;
  } ;
  union {
    __IOM uint32_t      CCR1;                        /*!< (@ 0x00000010) CNT Compare Register                                       */
    MDR_TIM_VALUE_Bits  CCR1_b;
  } ;
  union {
    __IOM uint32_t      CCR2;                        /*!< (@ 0x00000014) CNT Compare Register                                       */
    MDR_TIM_VALUE_Bits  CCR2_b;
  } ;  
  union {
    __IOM uint32_t      CCR3;                        /*!< (@ 0x00000018) CNT Compare Register                                       */
    MDR_TIM_VALUE_Bits  CCR3_b;
  } ;
  union {
    __IOM uint32_t      CCR4;                        /*!< (@ 0x0000001C) CNT Compare Register                                       */
    MDR_TIM_VALUE_Bits  CCR4_b;
  } ;  
  union {
    __IOM uint32_t          CH1_CNTRL;                   /*!< (@ 0x00000020) Capture and PWM Channel Control                            */
    MDR_TIM_CHx_CNTRL_Bits  CH1_CNTRL_b;
  } ;
  
  union {
    __IOM uint32_t          CH2_CNTRL;                   /*!< (@ 0x00000024) Capture and PWM Channel Control                            */
    MDR_TIM_CHx_CNTRL_Bits  CH2_CNTRL_b;
  } ; 
  union {
    __IOM uint32_t          CH3_CNTRL;                   /*!< (@ 0x00000028) Capture and PWM Channel Control                            */
    MDR_TIM_CHx_CNTRL_Bits  CH3_CNTRL_b;
  } ;
  union {
    __IOM uint32_t          CH4_CNTRL;                   /*!< (@ 0x0000002C) Capture and PWM Channel Control                            */
    MDR_TIM_CHx_CNTRL_Bits  CH4_CNTRL_b;
  } ;
  union {
    __IOM uint32_t            CH1_CNTRL1;                  /*!< (@ 0x00000030) PWM Driver Control                                         */
    MDR_TIM_CHx_CNTRL1_Bits   CH1_CNTRL1_b;
  } ;
  union {
    __IOM uint32_t            CH2_CNTRL1;                  /*!< (@ 0x00000034) PWM Driver Control                                         */
    MDR_TIM_CHx_CNTRL1_Bits   CH2_CNTRL1_b;
  } ;
  union {
    __IOM uint32_t            CH3_CNTRL1;                  /*!< (@ 0x00000038) PWM Driver Control                                         */
    MDR_TIM_CHx_CNTRL1_Bits   CH3_CNTRL1_b;    
  } ;
  union {
    __IOM uint32_t            CH4_CNTRL1;                  /*!< (@ 0x0000003C) PWM Driver Control                                         */
    MDR_TIM_CHx_CNTRL1_Bits   CH4_CNTRL1_b;    
  } ;
  union {
    __IOM uint32_t            CH1_DTG;                     /*!< (@ 0x00000040) Dead Time Generator                                        */
    MDR_TIM_CHx_DTG_Bits      CH1_DTG_b;
  } ;
  union {
    __IOM uint32_t            CH2_DTG;                     /*!< (@ 0x00000044) Dead Time Generator                                        */
    MDR_TIM_CHx_DTG_Bits      CH2_DTG_b;
  } ;  
  union {
    __IOM uint32_t            CH3_DTG;                     /*!< (@ 0x00000048) Dead Time Generator                                        */
    MDR_TIM_CHx_DTG_Bits      CH3_DTG_b;
  } ;
  union {
    __IOM uint32_t            CH4_DTG;                     /*!< (@ 0x0000004C) Dead Time Generator                                        */
    MDR_TIM_CHx_DTG_Bits      CH4_DTG_b;
  } ;  
  union {
    __IOM uint32_t            BRKETR_CNTRL;                /*!< (@ 0x00000050) Break and External Count Control                           */
    MDR_TIM_BRKETR_CNTRL_Bits BRKETR_CNTRL_b;
  } ;
  union {
    __IOM uint32_t            STATUS;                      /*!< (@ 0x00000054) Status Register                                            */
    MDR_TIM_EVENT_Bits        STATUS_b;
  } ; 
  union {
    __IOM uint32_t            IE;                          /*!< (@ 0x00000058) IRQ Enable                                                 */
    MDR_TIM_EVENT_Bits        IE_b;
  } ;
  union {
    __IOM uint32_t            DMA_RE;                      /*!< (@ 0x0000005C) DMA Request Enable for TIMx_DMA_REQ                        */
    MDR_TIM_EVENT_Bits        DMA_RE_b;
  } ;
  union {
    __IOM uint32_t            CH1_CNTRL2;                  /*!< (@ 0x00000060) CCR1 Control                                               */
    MDR_TIM_CHx_CNTRL2_Bits   CH1_CNTRL2_b; 
  } ;
  union {
    __IOM uint32_t            CH2_CNTRL2;                  /*!< (@ 0x00000064) CCR1 Control                                               */
    MDR_TIM_CHx_CNTRL2_Bits   CH2_CNTRL2_b; 
  } ;
  union {
    __IOM uint32_t            CH3_CNTRL2;                  /*!< (@ 0x00000068) CCR1 Control                                               */
    MDR_TIM_CHx_CNTRL2_Bits   CH3_CNTRL2_b; 
  } ;
  union {
    __IOM uint32_t            CH4_CNTRL2;                  /*!< (@ 0x0000006C) CCR1 Control                                               */
    MDR_TIM_CHx_CNTRL2_Bits   CH4_CNTRL2_b; 
  } ;  
  union {
    __IOM uint32_t            CCR11;                       /*!< (@ 0x00000070) CNT Compare Register                                       */
    MDR_TIM_VALUE_Bits        CCR11_b;    
  } ;
  union {
    __IOM uint32_t            CCR21;                       /*!< (@ 0x00000074) CNT Compare Register                                       */
    MDR_TIM_VALUE_Bits        CCR21_b;
  } ;
  union {
    __IOM uint32_t            CCR31;                       /*!< (@ 0x00000078) CNT Compare Register                                       */
    MDR_TIM_VALUE_Bits        CCR31_b;
  } ;
  union {
    __IOM uint32_t            CCR41;                       /*!< (@ 0x0000007C) CNT Compare Register                                       */
    MDR_TIM_VALUE_Bits        CCR41_b;
  } ;
  union {
    __IOM uint32_t            DMA_RE1;                     /*!< (@ 0x00000080) DMA Request Enable for TIMx_DMA_REQ1                       */
    MDR_TIM_EVENT_Bits        DMA_RE1_b;
  } ;
  union {
    __IOM uint32_t            DMA_RE2;                     /*!< (@ 0x00000084) DMA Request Enable for TIMx_DMA_REQ2                       */
    MDR_TIM_EVENT_Bits        DMA_RE2_b;
  } ;
  union {
    __IOM uint32_t            DMA_RE3;                     /*!< (@ 0x00000088) DMA Request Enable for TIMx_DMA_REQ3                       */
    MDR_TIM_EVENT_Bits        DMA_RE3_b;
  } ;
  union {
    __IOM uint32_t            DMA_RE4;                     /*!< (@ 0x0000008C) DMA Request Enable for TIMx_DMA_REQ4                       */
    MDR_TIM_EVENT_Bits        DMA_RE4_b;    
  } ;
} MDR_TIMER_Type;                               /*!< Size = 144 (0x90) */


//  One Channel's Registers
typedef struct {
  union {
    __IOM uint32_t            CCR;                        /*!< (@ 0x00000010) CNT Compare Register                                       */
    MDR_TIM_VALUE_Bits        CCR_b;
  } ;
  __IM uint32_t               reserved1[3];
  union {
    __IOM uint32_t            CHx_CNTRL;                   /*!< (@ 0x00000020) Capture and PWM Channel Control                            */
    MDR_TIM_CHx_CNTRL_Bits    CHx_CNTRL_b;
  } ;
  __IM uint32_t               reserved2[3];
  union {
    __IOM uint32_t            CHx_CNTRL1;                  /*!< (@ 0x00000030) PWM Driver Control                                         */
    MDR_TIM_CHx_CNTRL1_Bits   CHx_CNTRL1_b;
  } ;
  __IM uint32_t               reserved3[3];
  union {
    __IOM uint32_t            CHx_DTG;                     /*!< (@ 0x00000040) Dead Time Generator                                        */
    MDR_TIM_CHx_DTG_Bits      CHx_DTG_b;
  } ;
  __IM uint32_t               reserved4[7];
  union {
    __IOM uint32_t            CHx_CNTRL2;                  /*!< (@ 0x00000060) CCR1 Control                                               */
    MDR_TIM_CHx_CNTRL2_Bits   CHx_CNTRL2_b; 
  } ;
  __IM uint32_t               reserved5[3];  
  union {
    __IOM uint32_t            CCR1;                       /*!< (@ 0x00000070) CNT Compare Register                                       */
    MDR_TIM_VALUE_Bits        CCR1_b;    
  } ;
  __IM uint32_t               reserved6[3];  
  union {
    __IOM uint32_t            DMA_REx;                     /*!< (@ 0x00000080) DMA Request Enable for TIMx_DMA_REQ1                       */
    MDR_TIM_EVENT_Bits        DMA_REx_b;
  } ;
  __IOM uint32_t              reserved7[3];    
} MDR_TIMER_CH_Type;                              /*!< Size = 144 (0x90) */


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

#endif  //  _MDR_TIMER_VE13_DEFS_H
