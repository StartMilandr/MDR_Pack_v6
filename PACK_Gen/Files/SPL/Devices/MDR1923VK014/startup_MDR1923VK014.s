;/*****************************************************************************/
;/* 1923VK014.s: Startup file for ARM Cortex-M0 Device Family                   */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2008 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00001000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
	              EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

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

                ; External Interrupts - MDR1923VK014 Specific 
                DCD     FT_ERR_IRQHandler         ; 0: FT_IF0_Handler
                DCD     CLK_IRQHandler            ; 1: CLK_IF_Handler
                DCD     POWER_IRQHandler          ; 2: PVD_IF_Handler
                DCD     RTC_IRQHandler            ; 3: RTC_IF_Handler
                DCD     BKP_IRQHandler            ; 4: BKP_IF_Handler
                DCD     EBC_ERROR_IRQn            ; 5: EXT_INTERROR0_Handler
                DCD     DMA_IRQHandler            ; 6: DMA_ERR_Handler	
                DCD     CCSDS_TX_IRQHandler       ; 7: INT_ETH0_Handler
                DCD     CCSDS_RX_IRQHandler       ; 8: INT_ETH0_Handler
                DCD     GPIO_IRQHandler           ; 9: IRQ_PORTA_Handler					
                DCD     SPW1_IRQHandler           ; 10: INT_SPW0_Handler
                DCD     SPW2_IRQHandler           ; 11: INT_SPW1_Handler
                DCD     TIMER1_IRQHandler         ; 12: INT_TMR0_Handler
                DCD     TIMER2_IRQHandler         ; 13: INT_TMR1_Handler
                DCD     TIMER3_IRQHandler         ; 14: INT_TMR2_Handler
                DCD     TIMER4_IRQHandler         ; 15: INT_TMR3_Handler
                DCD     CAN1_IRQHandler           ; 16: INT_CAN0_Handler
                DCD     CAN2_IRQHandler           ; 17: INT_CAN1_Handler
                DCD     UART1_IRQHandler          ; 18: INT_UART0_Handler
                DCD     UART2_IRQHandler          ; 19: INT_UART1_Handler
                DCD     MIL1_IRQHandler           ; 20: INT_MIL0_Handler
                DCD     MIL2_IRQHandler           ; 21: INT_MIL1_Handler
                DCD     MIL3_IRQHandler           ; 22: INT_MIL2_Handler
                DCD     MIL4_IRQHandler           ; 23: INT_MIL3_Handler
                DCD     SSP1_IRQHandler           ; 24: INT_SSP0_Handler
                DCD     SSP2_IRQHandler           ; 25: INT_SSP1_Handler
                DCD     SSP3_IRQHandler           ; 26: INT_SSP2_Handler
                DCD     SSP4_IRQHandler           ; 27: INT_SSP3_Handler
                DCD     SSP5_IRQHandler           ; 28: INT_SSP4_Handler
                DCD     SSP6_IRQHandler           ; 29: INT_SSP5_Handler
                DCD     CRC_IRQHandler            ; 30: CRC_Handler
                DCD     ECC_IRQHandler            ; 31: ECC_Handler
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors
	
                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler			[WEAK]
                IMPORT  __main

				        LDR     R0,=__main
				        BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)                

NMI_Handler     PROC
                EXPORT  NMI_Handler						[WEAK]
                B       .
                ENDP

HardFault_Handler     PROC
                EXPORT  HardFault_Handler				[WEAK]
                B       .
                ENDP

SVC_Handler     PROC
                EXPORT  SVC_Handler					[WEAK]
                B       .
                ENDP

PendSV_Handler     PROC
                EXPORT  PendSV_Handler					[WEAK]
                B       .
                ENDP

SysTick_Handler     PROC
                EXPORT  SysTick_Handler					[WEAK]
                B       .
                ENDP

;================   1923VK014 ===========

FT_ERR_IRQHandler     PROC
                EXPORT  FT_ERR_IRQHandler					[WEAK]
                B       .
                ENDP

CLK_IRQHandler     PROC
                EXPORT  CLK_IRQHandler					[WEAK]
                B       .
                ENDP

POWER_IRQHandler     PROC
                EXPORT  POWER_IRQHandler					[WEAK]
                B       .
                ENDP

RTC_IRQHandler     PROC
                EXPORT  RTC_IRQHandler					[WEAK]
                B       .
                ENDP

BKP_IRQHandler     PROC
                EXPORT  BKP_IRQHandler					[WEAK]
                B       .
                ENDP

EBC_ERROR_IRQn     PROC
                EXPORT  EBC_ERROR_IRQn					[WEAK]
                B       .
                ENDP

DMA_IRQHandler     PROC
                EXPORT  DMA_IRQHandler					[WEAK]
                B       .
                ENDP

CCSDS_TX_IRQHandler     PROC
                EXPORT  CCSDS_TX_IRQHandler					[WEAK]
                B       .
                ENDP

CCSDS_RX_IRQHandler     PROC
                EXPORT  CCSDS_RX_IRQHandler			[WEAK]
                B       .
                ENDP

GPIO_IRQHandler     PROC
                EXPORT  GPIO_IRQHandler			[WEAK]
                B       .
                ENDP

SPW1_IRQHandler     PROC
                EXPORT  SPW1_IRQHandler			[WEAK]
                B       .
                ENDP

SPW2_IRQHandler     PROC
                EXPORT  SPW2_IRQHandler			[WEAK]
                B       .
                ENDP

TIMER1_IRQHandler     PROC
                EXPORT  TIMER1_IRQHandler			[WEAK]
                B       .
                ENDP

TIMER2_IRQHandler     PROC
                EXPORT  TIMER2_IRQHandler			[WEAK]
                B       .
                ENDP

TIMER3_IRQHandler     PROC
                EXPORT  TIMER3_IRQHandler			[WEAK]
                B       .
                ENDP

TIMER4_IRQHandler     PROC
                EXPORT  TIMER4_IRQHandler			[WEAK]
                B       .
                ENDP

CAN1_IRQHandler     PROC
                EXPORT  CAN1_IRQHandler					[WEAK]
                B       .
                ENDP
                
CAN2_IRQHandler     PROC
                EXPORT  CAN2_IRQHandler				[WEAK]
                B       .
                ENDP
					
UART1_IRQHandler     PROC
                EXPORT  UART1_IRQHandler				[WEAK]
                B       .
                ENDP					

UART2_IRQHandler     PROC
                EXPORT  UART2_IRQHandler				[WEAK]
                B       .
                ENDP
					
MIL1_IRQHandler     PROC
                EXPORT  MIL1_IRQHandler				[WEAK]
                B       .
                ENDP
					
MIL2_IRQHandler     PROC
                EXPORT  MIL2_IRQHandler				[WEAK]
                B       .
                ENDP
					
MIL3_IRQHandler     PROC
                EXPORT  MIL3_IRQHandler				[WEAK]
                B       .
                ENDP
					
SSP1_IRQHandler     PROC
                EXPORT  SSP1_IRQHandler				[WEAK]
                B       .
                ENDP
					
SSP2_IRQHandler     PROC
                EXPORT  SSP2_IRQHandler				[WEAK]
                B       .
                ENDP
					
SSP3_IRQHandler     PROC
                EXPORT  SSP3_IRQHandler				[WEAK]
                B       .
                ENDP
					
SSP4_IRQHandler     PROC
                EXPORT  SSP4_IRQHandler				[WEAK]
                B       .
                ENDP
					
SSP5_IRQHandler     PROC
                EXPORT  SSP5_IRQHandler				[WEAK]
                B       .
                ENDP
					
SSP6_IRQHandler     PROC
                EXPORT  SSP6_IRQHandler				[WEAK]
                B       .
                ENDP					

CRC_IRQHandler     PROC
                EXPORT  CRC_IRQHandler				[WEAK]
                B       .
                ENDP					

ECC_IRQHandler     PROC
                EXPORT  ECC_IRQHandler				[WEAK]
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