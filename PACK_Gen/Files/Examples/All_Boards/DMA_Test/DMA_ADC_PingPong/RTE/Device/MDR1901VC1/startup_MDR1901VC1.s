;/*****************************************************************************
; * @file:    startup_1901VC1.s
; * @purpose: CMSIS Cortex-M3 Core Device Startup File 
; *           for the ARM 'Microcontroller Prototyping System' 
; * @version: V1.01
; * @date:    19. Aug. 2009
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; * Copyright (C) 2008-2009 ARM Limited. All rights reserved.
; * ARM Limited (ARM) is supplying this software for use with Cortex-M3 
; * processor based microcontrollers.  This file can be freely distributed 
; * within development tools that are supporting such ARM based processors. 
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; *****************************************************************************/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts - MDR1901VC1 Specific 
                DCD     SSP3_IRQHandler               ; 0:  SSP3  Interrupt
                DCD     SSP4_IRQHandler               ; 1:  SSP4  Interrupt
                DCD     USB_IRQHandler                ; 2:  USB Interrupt
                DCD     DSP_MCBSP1_IRQHandler         ; 3:  DSP McBSP1 Interrupt
                DCD     DSP_MCBSP2_IRQHandler         ; 4:  DSP McBSP2 Interrupt
                DCD     DMA_IRQHandler                ; 5:  DMA Interrupt
                DCD     UART1_IRQHandler              ; 6:  UART1 Interrupt
                DCD     UART2_IRQHandler              ; 7:  UART2 Interrupt
                DCD     SSP1_IRQHandler               ; 8:  SSP1 Interrupt
                DCD     DSP_MCBSP3_IRQHandler         ; 9:  DSP McBSP3 Interrupt
                DCD     I2C_IRQHandler                ; 10: I2C Interrupt
                DCD     POWER_IRQHandler              ; 11: Power Detector Interrupt
                DCD     WWDG_IRQHandler               ; 12: WWDG Interrupt
                DCD     DSP_DMA_IRQHandler            ; 13: DSP DMA Device
                DCD     TIMER1_IRQHandler             ; 14: Timer1 Interrupt
                DCD     TIMER2_IRQHandler             ; 15: Timer2 Interrupt
                DCD     TIMER3_IRQHandler             ; 16: Timer3 Interrupt
                DCD     ADC_IRQHandler                ; 17: ADC Interrupt
                DCD     SDIO_IRQHandler               ; 18: SDIO Interrupt
                DCD     COMP_IRQHandler               ; 19: Comparator Interrupt
                DCD     SSP2_IRQHandler               ; 20: SSP2 Interrupt
                DCD     DSP_AUC_IRQHandler            ; 21: DSP AudioCodec Interrupt
                DCD     DSP_CRPT_IRQHandler           ; 22: DSP Crypro Interrupt
                DCD     DSP_TIMER_IRQHandler          ; 23: DSP Timer Interrupt
                DCD     DSP_CORE_IRQHandler           ; 24: DSP Core Interrupt (AIRQ)
                DCD     DSP_STATE_IRQHandler          ; 25: DSP State Interrupt (IDLE)
                DCD     UART3_IRQHandler              ; 26: UART3 Interrupt
                DCD     BKP_IRQHandler                ; 27: Backup and RTC Interrupt
                DCD     EXT1_IRQHandler               ; 28: EXT_INT1 Interrupt
                DCD     EXT2_IRQHandler               ; 29: EXT_INT2 Interrupt
                DCD     EXT3_IRQHandler               ; 30: EXT_INT3 Interrupt
                DCD     EXT4_IRQHandler               ; 31: EXT_INT4 Interrupt


                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  SSP3_IRQHandler            [WEAK]
                EXPORT  SSP4_IRQHandler            [WEAK]
                EXPORT  USB_IRQHandler             [WEAK]
                EXPORT  DSP_MCBSP1_IRQHandler      [WEAK]
                EXPORT  DSP_MCBSP2_IRQHandler      [WEAK]
                EXPORT  DMA_IRQHandler             [WEAK]
                EXPORT  UART1_IRQHandler           [WEAK]
                EXPORT  UART2_IRQHandler           [WEAK]
                EXPORT  SSP1_IRQHandler            [WEAK]
                EXPORT  DSP_MCBSP3_IRQHandler      [WEAK]
                EXPORT  I2C_IRQHandler             [WEAK]
                EXPORT  POWER_IRQHandler           [WEAK]
                EXPORT  WWDG_IRQHandler            [WEAK]
                EXPORT  DSP_DMA_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler          [WEAK]
                EXPORT  TIMER2_IRQHandler          [WEAK]
                EXPORT  TIMER3_IRQHandler          [WEAK]
                EXPORT  ADC_IRQHandler             [WEAK]
                EXPORT  SDIO_IRQHandler            [WEAK]
                EXPORT  COMP_IRQHandler            [WEAK]
                EXPORT  SSP2_IRQHandler            [WEAK]
                EXPORT  DSP_AUC_IRQHandler         [WEAK]
                EXPORT  DSP_CRPT_IRQHandler        [WEAK]
                EXPORT  DSP_TIMER_IRQHandler       [WEAK]
                EXPORT  DSP_CORE_IRQHandler        [WEAK]
                EXPORT  DSP_STATE_IRQHandler       [WEAK]
                EXPORT  UART3_IRQHandler           [WEAK]
                EXPORT  BKP_IRQHandler             [WEAK]
                EXPORT  EXT1_IRQHandler            [WEAK]
                EXPORT  EXT2_IRQHandler            [WEAK]
                EXPORT  EXT3_IRQHandler            [WEAK]
                EXPORT  EXT4_IRQHandler            [WEAK]


SSP3_IRQHandler
SSP4_IRQHandler
USB_IRQHandler
DSP_MCBSP1_IRQHandler
DSP_MCBSP2_IRQHandler
DMA_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
SSP1_IRQHandler
DSP_MCBSP3_IRQHandler
I2C_IRQHandler
POWER_IRQHandler
WWDG_IRQHandler
DSP_DMA_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
ADC_IRQHandler
SDIO_IRQHandler
COMP_IRQHandler
SSP2_IRQHandler
DSP_AUC_IRQHandler
DSP_CRPT_IRQHandler
DSP_TIMER_IRQHandler
DSP_CORE_IRQHandler
DSP_STATE_IRQHandler
UART3_IRQHandler
BKP_IRQHandler
EXT1_IRQHandler
EXT2_IRQHandler
EXT3_IRQHandler
EXT4_IRQHandler
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
