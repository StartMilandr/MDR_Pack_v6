;/*****************************************************************************/
;/* 1986VE8T.s: Startup file for ARM Cortex-M4F Device Family                   */
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

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemoryMngFault_Handler    ; MemoryMngFault_Handler
                DCD     BusFault_Handler          ; BusFault_Handler
                DCD     UsageFault_Handler        ; UsageFault_Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler            ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts - MDR1986BE8 Specific 
                DCD     0           			        ; Reserved0
                DCD     0          				        ; Reserved1
                DCD     0           			        ; Reserved2
                DCD     0           			        ; Reserved3
                DCD     0           			        ; Reserved4
                DCD     0           			        ; Reserved5
                DCD     0           			        ; Reserved6
                DCD     0           			        ; Reserved7
                DCD     0           			        ; Reserved8
                DCD     0           			        ; Reserved9
                DCD     0           			        ; Reserved10
                DCD     0           			        ; Reserved11
                DCD     0           			        ; Reserved12
                DCD     0           			        ; Reserved13
                DCD     0           			        ; Reserved14
                DCD     0          				        ; Reserved15
                DCD     0           			        ; Reserved16
                DCD     0           			        ; Reserved17
                DCD     0           			        ; Reserved18
                DCD     0           			        ; Reserved19
                DCD     0           			        ; Reserved20
                DCD     0           			        ; Reserved21
				        DCD 	  0	           			        ; Reserved22
				        DCD 	  0	           			        ; Reserved23
				        DCD 	  0	           			        ; Reserved24
				        DCD 	  0	           			        ; Reserved25
				        DCD 	  0	           			        ; Reserved26
				        DCD 	  0	           			        ; Reserved27
				        DCD 	  0           			        ; Reserved28
				        DCD 	  0	           			        ; Reserved29
				        DCD 	  0	           			        ; Reserved30
				        DCD 	  0	           			        ; Reserved31
                DCD     FT_RESET0_4_IRQHandler    ; 32: FT_IF0_Handler
                DCD     FT_EVENT0_4_IRQHandler    ; 33: FT_IF1_Handler
                DCD     FT_EVENT5_8_IRQHandler    ; 34: FT_IF2_Handler
                DCD     FT_EVENT9_12_IRQHandler   ; 35: FT_IF3_Handler
                DCD     CLK_IRQHandler            ; 36: CLK_IF_Handler
                DCD     POWER_IRQHandler            ; 37: PVD_IF_Handler
                DCD     RTC_IRQHandler            ; 38: RTC_IF_Handler
                DCD     BKP_IRQHandler            ; 39: BKP_IF_Handler
                DCD     EBC_ERROR0_IRQHandler     ; 40: EXT_INTERROR0_Handler
                DCD     EBC_ERROR1_IRQHandler     ; 41: EXT_INTERROR1_Handler
                DCD     EBC_ERROR2_IRQHandler     ; 42: EXT_INTERROR2_Handler
                DCD     EBC_ERROR3_IRQHandler     ; 43: EXT_INTERROR3_Handler
                DCD     EBC_ERROR4_IRQHandler     ; 44: EXT_INTERROR4_Handler
                DCD     EBC_ERROR5_IRQHandler     ; 45: EXT_INTERROR5_Handler
                DCD     EBC_ERROR6_IRQHandler     ; 46: EXT_INTERROR6_Handler
                DCD     EBC_ERROR7_IRQHandler     ; 47: EXT_INTERROR7_Handler
                DCD     0				                  ; Reserved48
                DCD     0        				          ; Reserved49
                DCD     DMA_ERR_IRQHandler        ; 50: DMA_ERR_Handler	
                DCD     DMA_DONE0_IRQHandler      ; 51: DMA_DONE0_Handler	
                DCD     DMA_DONE1_IRQHandler      ; 52: DMA_DONE1_Handler
                DCD     DMA_DONE2_IRQHandler      ; 53: DMA_DONE2_Handler	
                DCD     DMA_DONE3_IRQHandler      ; 54: DMA_DONE3_Handler	
                DCD     DMA_DONE4_IRQHandler     	; 55: DMA_DONE4_Handler	
                DCD     DMA_DONE5_IRQHandler      ; 56: DMA_DONE5_Handler	
                DCD     DMA_DONE6_IRQHandler      ; 57: DMA_DONE6_Handler	
                DCD     DMA_DONE7_IRQHandler      ; 58: DMA_DONE7_Handler	
                DCD     DMA_DONE8_IRQHandler      ; 59: DMA_DONE8_Handler	
                DCD     DMA_DONE9_IRQHandler      ; 60: DMA_DONE9_Handler	
                DCD     DMA_DONE10_IRQHandler     ; 61: DMA_DONE10_Handler	
                DCD     DMA_DONE11_IRQHandler     ; 62: DMA_DONE11_Handler
                DCD     DMA_DONE12_IRQHandler	 	  ; 63: DMA_DONE12_Handler	
                DCD     DMA_DONE13_IRQHandler		  ; 64: DMA_DONE13_Handler
                DCD     DMA_DONE14_IRQHandler		  ; 65: DMA_DONE14_Handler	
                DCD     DMA_DONE15_IRQHandler		  ; 66: DMA_DONE15_Handler	
                DCD     DMA_DONE16_IRQHandler		  ; 67: DMA_DONE16_Handler	
                DCD     DMA_DONE17_IRQHandler		  ; 68: DMA_DONE17_Handler	
                DCD     DMA_DONE18_IRQHandler		  ; 69: DMA_DONE18_Handler	
                DCD     DMA_DONE19_IRQHandler		  ; 70: DMA_DONE19_Handler	
                DCD     DMA_DONE20_IRQHandler		  ; 71: DMA_DONE20_Handler	
                DCD     DMA_DONE21_IRQHandler		  ; 72: DMA_DONE21_Handler	
                DCD     DMA_DONE22_IRQHandler		  ; 73: DMA_DONE22_Handler	
                DCD     DMA_DONE23_IRQHandler		  ; 74: DMA_DONE23_Handler
                DCD     DMA_DONE24_IRQHandler		  ; 75: DMA_DONE24_Handler	
                DCD     DMA_DONE25_IRQHandler		  ; 76: DMA_DONE25_Handler
                DCD     DMA_DONE26_IRQHandler		  ; 77: DMA_DONE26_Handler	
                DCD     DMA_DONE27_IRQHandler		  ; 78: DMA_DONE27_Handler	
                DCD     DMA_DONE28_IRQHandler		  ; 79: DMA_DONE28_Handler	
                DCD     DMA_DONE29_IRQHandler		  ; 80: DMA_DONE29_Handler	
                DCD     DMA_DONE30_IRQHandler		  ; 81: DMA_DONE30_Handler	
                DCD     DMA_DONE31_IRQHandler		  ; 82: DMA_DONE31_Handler				
                DCD     PORTA_IRQHandler          ; 83: IRQ_PORTA_Handler					
                DCD     PORTB_IRQHandler          ; 84: IRQ_PORTB_Handler
                DCD     PORTC_IRQHandler          ; 85: IRQ_PORTC_Handler
                DCD     PORTD_IRQHandler          ; 86: IRQ_PORTD_Handler
                DCD     PORTE_IRQHandler          ; 87: IRQ_PORTE_Handler
                DCD     0					                ; Reserved88
                DCD     ETH1_IRQHandler           ; 89: INT_ETH0_Handler
                DCD     0        				          ; Reserved90	
				        DCD     SPW1_IRQHandler           ; 91: INT_SPW0_Handler
                DCD     0        				          ; Reserved92	
                DCD     TIMER1_IRQHandler         ; 93: INT_TMR0_Handler
                DCD     TIMER2_IRQHandler         ; 94: INT_TMR1_Handler
                DCD     TIMER3_IRQHandler         ; 95: INT_TMR2_Handler
                DCD     TIMER4_IRQHandler         ; 96: INT_TMR3_Handler
                DCD     0        				          ; Reserved97
                DCD     0        				          ; Reserved98
                DCD     CAN1_IRQHandler           ; 99: INT_CAN0_Handler
                DCD     0        				          ; Reserved100
                DCD     0        				          ; Reserved101	
                DCD     0        				          ; Reserved102	
                DCD     0        				          ; Reserved103					
                DCD     SSP1_IRQHandler           ; 104: INT_SSP0_Handler	
                DCD     0        				          ; Reserved105
                DCD     0        				          ; Reserved106	
                DCD     0        				          ; Reserved107	
                DCD     UART1_IRQHandler          ; 108: INT_UART0_Handler
                DCD     UART2_IRQHandler          ; 109: INT_UART1_Handler
                DCD     0        				          ; Reserved110	
                DCD     0        				          ; Reserved111	
                DCD     0        				          ; Reserved112	
                DCD     ARC1_RX_IRQHandler        ; 113: INT_RX_ARC0_Handler
                DCD     ARC1_TX_IRQHandler        ; 114: INT_TX_ARC0_Handler
                DCD     0        				          ; Reserved115
                DCD     0        				          ; Reserved116
                DCD     MIL1_IRQHandler           ; 117: INT_MIL0_Handler
                DCD     MIL2_IRQHandler           ; 118: INT_MIL1_Handler
                DCD     ADC1_IRQHandler           ; 119: INT_ADC0_Handler
                DCD     ADC2_IRQHandler           ; 120: INT_ADC1_Handler
                DCD     DAC1_IRQHandler           ; 121: INT_DAC0_Handler
                DCD     DAC2_IRQHandler           ; 122: INT_DAC1_Handler											
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors
	
                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler			[WEAK]
                IMPORT  __main

				        ; --- FPU Enable ---
				        ; CPACR is located at address 0xE000ED88
				        LDR.W R0, =0xE000ED88
				        ; Read CPACR
				        LDR R1, [R0]
				        ; Set bits 20-23 to enable CP10 and CP11 coprocessors
				        ORR R1, R1, #(0xF << 20)
				        ; Write back the modified value to the CPACR
				        STR R1, [R0]; wait for store to complete
				        DSB
				        ;reset pipeline now the FPU is enabled
				        ISB 
				
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

MemoryMngFault_Handler     PROC
                EXPORT  MemoryMngFault_Handler			[WEAK]
                B       .
                ENDP

BusFault_Handler     PROC
                EXPORT  BusFault_Handler				[WEAK]
                B       .
                ENDP

UsageFault_Handler     PROC
                EXPORT  UsageFault_Handler				[WEAK]
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
                
FT_RESET0_4_IRQHandler     PROC
                EXPORT  FT_RESET0_4_IRQHandler					[WEAK]
                B       .
                ENDP

FT_EVENT0_4_IRQHandler     PROC
                EXPORT  FT_EVENT0_4_IRQHandler					[WEAK]
                B       .
                ENDP

FT_EVENT5_8_IRQHandler     PROC
                EXPORT  FT_EVENT5_8_IRQHandler					[WEAK]
                B       .
                ENDP

FT_EVENT9_12_IRQHandler     PROC
                EXPORT  FT_EVENT9_12_IRQHandler					[WEAK]
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

EBC_ERROR0_IRQHandler     PROC
                EXPORT  EBC_ERROR0_IRQHandler			[WEAK]
                B       .
                ENDP

EBC_ERROR1_IRQHandler     PROC
                EXPORT  EBC_ERROR1_IRQHandler			[WEAK]
                B       .
                ENDP

EBC_ERROR2_IRQHandler     PROC
                EXPORT  EBC_ERROR2_IRQHandler			[WEAK]
                B       .
                ENDP

EBC_ERROR3_IRQHandler     PROC
                EXPORT  EBC_ERROR3_IRQHandler			[WEAK]
                B       .
                ENDP

EBC_ERROR4_IRQHandler     PROC
                EXPORT  EBC_ERROR4_IRQHandler			[WEAK]
                B       .
                ENDP

EBC_ERROR5_IRQHandler     PROC
                EXPORT  EBC_ERROR5_IRQHandler			[WEAK]
                B       .
                ENDP

EBC_ERROR6_IRQHandler     PROC
                EXPORT  EBC_ERROR6_IRQHandler			[WEAK]
                B       .
                ENDP

EBC_ERROR7_IRQHandler     PROC
                EXPORT  EBC_ERROR7_IRQHandler			[WEAK]
                B       .
                ENDP

DMA_ERR_IRQHandler     PROC
                EXPORT  DMA_ERR_IRQHandler					[WEAK]
                B       .
                ENDP
                
DMA_DONE0_IRQHandler     PROC
                EXPORT  DMA_DONE0_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE1_IRQHandler     PROC
                EXPORT  DMA_DONE1_IRQHandler				[WEAK]
                B       .
                ENDP					

DMA_DONE2_IRQHandler     PROC
                EXPORT  DMA_DONE2_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE3_IRQHandler     PROC
                EXPORT  DMA_DONE3_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE4_IRQHandler     PROC
                EXPORT  DMA_DONE4_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE5_IRQHandler     PROC
                EXPORT  DMA_DONE5_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE6_IRQHandler     PROC
                EXPORT  DMA_DONE6_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE7_IRQHandler     PROC
                EXPORT  DMA_DONE7_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE8_IRQHandler     PROC
                EXPORT  DMA_DONE8_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE9_IRQHandler     PROC
                EXPORT  DMA_DONE9_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE10_IRQHandler     PROC
                EXPORT  DMA_DONE10_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE11_IRQHandler     PROC
                EXPORT  DMA_DONE11_IRQHandler				[WEAK]
                B       .
                ENDP					

DMA_DONE12_IRQHandler     PROC
                EXPORT  DMA_DONE12_IRQHandler				[WEAK]
                B       .
                ENDP					

DMA_DONE13_IRQHandler     PROC
                EXPORT  DMA_DONE13_IRQHandler				[WEAK]
                B       .
                ENDP
										
DMA_DONE14_IRQHandler     PROC
                EXPORT  DMA_DONE14_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE15_IRQHandler     PROC
                EXPORT  DMA_DONE15_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE16_IRQHandler     PROC
                EXPORT  DMA_DONE16_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE17_IRQHandler     PROC
                EXPORT  DMA_DONE17_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE18_IRQHandler     PROC
                EXPORT  DMA_DONE18_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE19_IRQHandler     PROC
                EXPORT  DMA_DONE19_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE20_IRQHandler     PROC
                EXPORT  DMA_DONE20_IRQHandler				[WEAK]
                B       .
                ENDP

DMA_DONE21_IRQHandler     PROC
                EXPORT  DMA_DONE21_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE22_IRQHandler     PROC
                EXPORT  DMA_DONE22_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE23_IRQHandler     PROC
                EXPORT  DMA_DONE23_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE24_IRQHandler     PROC
                EXPORT  DMA_DONE24_IRQHandler				[WEAK]
                B       .
                ENDP

DMA_DONE25_IRQHandler     PROC
                EXPORT  DMA_DONE25_IRQHandler				[WEAK]
                B       .
                ENDP

DMA_DONE26_IRQHandler     PROC
                EXPORT  DMA_DONE26_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE27_IRQHandler     PROC
                EXPORT  DMA_DONE27_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE28_IRQHandler     PROC
                EXPORT  DMA_DONE28_IRQHandler				[WEAK]
                B       .
                ENDP
					
DMA_DONE29_IRQHandler     PROC
                EXPORT  DMA_DONE29_IRQHandler				[WEAK]
                B       .
                ENDP

DMA_DONE30_Handler     PROC
                EXPORT  DMA_DONE30_Handler				[WEAK]
                B       .
                ENDP

DMA_DONE31_Handler     PROC
                EXPORT  DMA_DONE31_Handler				[WEAK]
                B       .
                ENDP
					
PORTA_IRQHandler     PROC
                EXPORT  PORTA_IRQHandler				[WEAK]
                B       .
                ENDP

PORTB_IRQHandler     PROC
                EXPORT  PORTB_IRQHandler				[WEAK]
                B       .
                ENDP

PORTC_IRQHandler     PROC
                EXPORT  PORTC_IRQHandler				[WEAK]
                B       .
                ENDP

PORTD_IRQHandler     PROC
                EXPORT  PORTD_IRQHandler				[WEAK]
                B       .
                ENDP

PORTE_IRQHandler     PROC
                EXPORT  PORTE_IRQHandler				[WEAK]
                B       .
                ENDP

ETH1_IRQHandler     PROC
                EXPORT  ETH1_IRQHandler				[WEAK]
                B       .
                ENDP

SPW1_IRQHandler     PROC
                EXPORT  SPW1_IRQHandler				[WEAK]
                B       .
                ENDP

TIMER1_IRQHandler     PROC
                EXPORT  TIMER1_IRQHandler				[WEAK]
                B       .
                ENDP

TIMER2_IRQHandler     PROC
                EXPORT  TIMER2_IRQHandler				[WEAK]
                B       .
                ENDP

TIMER3_IRQHandler     PROC
                EXPORT  TIMER3_IRQHandler				[WEAK]
                B       .
                ENDP

TIMER4_IRQHandler     PROC
                EXPORT  TIMER4_IRQHandler				[WEAK]
                B       .
                ENDP

CAN1_IRQHandler     PROC
                EXPORT  CAN1_IRQHandler				[WEAK]
                B       .
                ENDP

SSP1_IRQHandler     PROC
                EXPORT  SSP1_IRQHandler				[WEAK]
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
					
ARC1_RX_IRQHandler     PROC
                EXPORT  ARC1_RX_IRQHandler				[WEAK]
                B       .
                ENDP

ARC1_TX_IRQHandler     PROC
                EXPORT  ARC1_TX_IRQHandler				[WEAK]
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

ADC1_IRQHandler     PROC
                EXPORT  ADC1_IRQHandler				[WEAK]
                B       .
                ENDP
					
ADC2_IRQHandler     PROC
                EXPORT  ADC2_IRQHandler				[WEAK]
                B       .
                ENDP

DAC1_IRQHandler     PROC
                EXPORT  DAC1_IRQHandler				[WEAK]
                B       .
                ENDP
					
DAC2_IRQHandler     PROC
                EXPORT  DAC2_IRQHandler				[WEAK]
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