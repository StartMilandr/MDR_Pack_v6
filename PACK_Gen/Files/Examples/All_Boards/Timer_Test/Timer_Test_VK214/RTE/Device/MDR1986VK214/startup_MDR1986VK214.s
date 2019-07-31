;/*****************************************************************************
; * @file:    startup_MDR1986BK214.s
; * @purpose: CMSIS Cortex-M0 Core Device Startup File 
; *           for the ARM 'Microcontroller Prototyping System' 
; * @version: V1.0
; * @date:    19. Aug. 2009
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; * Copyright (C) 2008-2009 ARM Limited. All rights reserved.
; * ARM Limited (ARM) is supplying this software for use with Cortex-M0 
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
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts - MDR1986BK214 Specific 
                DCD     0                         ; 0:  Reserved
                DCD     UART1_IRQHandler          ; 1:  UART1 Interrupt
                DCD     UART2_IRQHandler          ; 2:  UART2 Interrupt
                DCD     SSP1_IRQHandler           ; 3:  SSP1 Interrupt
                DCD     POWER_IRQHandler          ; 4:  Power Detector Interrupt
                DCD     WWDG_IRQHandler           ; 5:  WWDG Interrupt
                DCD     TIMER1_IRQHandler         ; 6:  Timer1 Interrupt
                DCD     TIMER2_IRQHandler         ; 7:  Timer1 Interrupt
                DCD     ADC_IRQHandler            ; 8:  ADC Interrupt
                DCD     I2C_IRQHandler            ; 9:  I2C Interrupt
				DCD     BKP_IRQHandler            ; 10: Backup and RTC Interrupt
				DCD     EXT1_IRQHandler           ; 11: EXT_INT1 Interrupt
				DCD     EXT2_IRQHandler	          ; 12: EXT_INT2 Interrupt
				DCD     EXT3_IRQHandler	          ; 13: EXT_INT3 Interrupt
                DCD     ADCUI_F0_IRQHandler       ; 14: ADCUI_F0 Interrupt

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
HardFault_Handler \
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
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

                EXPORT  UART1_IRQHandler             [WEAK]
                EXPORT  UART2_IRQHandler             [WEAK]
                EXPORT  SSP1_IRQHandler              [WEAK]
                EXPORT  POWER_IRQHandler             [WEAK]
                EXPORT  WWDG_IRQHandler              [WEAK]
                EXPORT  TIMER1_IRQHandler            [WEAK]
                EXPORT  TIMER2_IRQHandler            [WEAK]
                EXPORT  ADC_IRQHandler               [WEAK]
                EXPORT  I2C_IRQHandler               [WEAK]
                EXPORT  BKP_IRQHandler               [WEAK]
                EXPORT  EXT1_IRQHandler              [WEAK]
                EXPORT  EXT2_IRQHandler	             [WEAK]
                EXPORT  EXT3_IRQHandler	             [WEAK]
                EXPORT  ADCUI_F0_IRQHandler          [WEAK]


UART1_IRQHandler
UART2_IRQHandler
SSP1_IRQHandler
POWER_IRQHandler
WWDG_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
ADC_IRQHandler
I2C_IRQHandler
BKP_IRQHandler
EXT1_IRQHandler
EXT2_IRQHandler
EXT3_IRQHandler
ADCUI_F0_IRQHandler
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
