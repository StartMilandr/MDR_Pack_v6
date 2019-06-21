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
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

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
                DCD     SVCall_Handler            ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts - ESila Specific 
                DCD     0           			  ; Reserved0
                DCD     0          				  ; Reserved1
                DCD     0           			  ; Reserved2
                DCD     0           			  ; Reserved3
                DCD     0           			  ; Reserved4
                DCD     0           			  ; Reserved5
                DCD     0           			  ; Reserved6
                DCD     0           			  ; Reserved7
                DCD     0           			  ; Reserved8
                DCD     0           			  ; Reserved9
                DCD     0           			  ; Reserved10
                DCD     0           			  ; Reserved11
                DCD     0           			  ; Reserved12
                DCD     0           			  ; Reserved13
                DCD     0           			  ; Reserved14
                DCD     0          				  ; Reserved15
                DCD     0           			  ; Reserved16
                DCD     0           			  ; Reserved17
                DCD     0           			  ; Reserved18
                DCD     0           			  ; Reserved19
                DCD     0           			  ; Reserved20
                DCD     0           			  ; Reserved21
				DCD 	0	           			  ; Reserved22
                DCD 	0	           			  ; Reserved23
				DCD 	0	           			  ; Reserved24
				DCD 	0	           			  ; Reserved25
				DCD 	0	           			  ; Reserved26
				DCD 	0	           			  ; Reserved27
				DCD 	0           			  ; Reserved28
				DCD 	0	           			  ; Reserved29
				DCD 	0	           			  ; Reserved30
				DCD 	0	           			  ; Reserved31
                DCD     FT_RESET0_4_IRQHandler    ; 32: FT_IF0_Handler
                DCD     FT_EVENT0_4_IRQHandler    ; 33: FT_IF1_Handler
                DCD     FT_EVENT5_8_IRQHandler    ; 34: FT_IF2_Handler
                DCD     FT_EVENT9_12_IRQHandler   ; 35: FT_IF3_Handler
                DCD     CLK_IRQHandler            ; 36: CLK_IF_Handler
                DCD     0                         ; 37: POWER_IRQHandler
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
                DCD     SCRB_ERR_IRQHandler		  ; Reserved48
                DCD     SCRB_DONE_IRQHandler      ; Reserved49
                DCD     DMA_ERR_IRQHandler        ; 50: DMA_ERR_Handler	
                DCD     DMA_DONE0_IRQHandler      ; 51: DMA_DONE0_Handler	
                DCD     DMA_DONE1_IRQHandler      ; 52: DMA_DONE1_Handler
                DCD     DMA_DONE2_IRQHandler      ; 53: DMA_DONE2_Handler	
                DCD     DMA_DONE3_IRQHandler      ; 54: DMA_DONE3_Handler	
                DCD     DMA_DONE4_IRQHandler      ; 55: DMA_DONE4_Handler	
                DCD     DMA_DONE5_IRQHandler      ; 56: DMA_DONE5_Handler	
                DCD     DMA_DONE6_IRQHandler      ; 57: DMA_DONE6_Handler	
                DCD     DMA_DONE7_IRQHandler      ; 58: DMA_DONE7_Handler	
                DCD     DMA_DONE8_IRQHandler      ; 59: DMA_DONE8_Handler	
                DCD     DMA_DONE9_IRQHandler      ; 60: DMA_DONE9_Handler	
                DCD     DMA_DONE10_IRQHandler     ; 61: DMA_DONE10_Handler	
                DCD     DMA_DONE11_IRQHandler     ; 62: DMA_DONE11_Handler
                DCD     DMA_DONE12_IRQHandler	  ; 63: DMA_DONE12_Handler	
                DCD     DMA_DONE13_IRQHandler	  ; 64: DMA_DONE13_Handler
                DCD     DMA_DONE14_IRQHandler	  ; 65: DMA_DONE14_Handler	
                DCD     DMA_DONE15_IRQHandler	  ; 66: DMA_DONE15_Handler	
                DCD     DMA_DONE16_IRQHandler	  ; 67: DMA_DONE16_Handler	
                DCD     DMA_DONE17_IRQHandler	  ; 68: DMA_DONE17_Handler	
                DCD     DMA_DONE18_IRQHandler	  ; 69: DMA_DONE18_Handler	
                DCD     DMA_DONE19_IRQHandler	  ; 70: DMA_DONE19_Handler	
                DCD     DMA_DONE20_IRQHandler	  ; 71: DMA_DONE20_Handler	
                DCD     DMA_DONE21_IRQHandler	  ; 72: DMA_DONE21_Handler	
                DCD     DMA_DONE22_IRQHandler	  ; 73: DMA_DONE22_Handler	
                DCD     DMA_DONE23_IRQHandler	  ; 74: DMA_DONE23_Handler
                DCD     DMA_DONE24_IRQHandler	  ; 75: DMA_DONE24_Handler	
                DCD     DMA_DONE25_IRQHandler	  ; 76: DMA_DONE25_Handler
                DCD     DMA_DONE26_IRQHandler	  ; 77: DMA_DONE26_Handler	
                DCD     DMA_DONE27_IRQHandler	  ; 78: DMA_DONE27_Handler	
                DCD     DMA_DONE28_IRQHandler	  ; 79: DMA_DONE28_Handler	
                DCD     DMA_DONE29_IRQHandler	  ; 80: DMA_DONE29_Handler	
                DCD     DMA_DONE30_IRQHandler	  ; 81: DMA_DONE30_Handler	
                DCD     DMA_DONE31_IRQHandler	  ; 82: DMA_DONE31_Handler				
                DCD     PORTA_IRQHandler          ; 83: IRQ_PORTA_Handler					
                DCD     PORTB_IRQHandler          ; 84: IRQ_PORTB_Handler
                DCD     PORTC_IRQHandler          ; 85: IRQ_PORTC_Handler
                DCD     PORTD_IRQHandler          ; 86: IRQ_PORTD_Handler
                DCD     0                         ; Reserved87
                DCD     0					      ; Reserved88
                DCD     ETH1_IRQHandler           ; 89: INT_ETH0_Handler
                DCD     CAN1_IRQHandler        	  ; 90: CAN0 Handler
				DCD     CAN2_IRQHandler           ; 91: CAN1 Handler
                DCD     SSP1_IRQHandler           ; 92: SSP1
                DCD     SSP1_RX_IRQHandler        ; 93
                DCD     SSP1_TX_IRQHandler        ; 94
                DCD     SSP1_ROR_IRQHandler       ; 95
                DCD     SSP1_RT_IRQHandler        ; 96
                DCD     SSP1_RX_FIFO_IRQHandler   ; 97
                DCD     SSP1_TX_FIFO_IRQHandler   ; 98
                DCD     SSP1_BUSY_IRQHandler      ; 99
                DCD     SSP2_IRQHandler           ; 100: SSP2
                DCD     SSP2_RX_IRQHandler        ; 101
                DCD     SSP2_TX_IRQHandler        ; 102
                DCD     SSP2_ROR_IRQHandler       ; 103
                DCD     SSP2_RT_IRQHandler        ; 104
                DCD     SSP2_RX_FIFO_IRQHandler   ; 105
                DCD     SSP2_TX_FIFO_IRQHandler   ; 106
                DCD     SSP2_BUSY_IRQHandler      ; 107
                DCD     UART1_IRQHandler     	  ; 108: UART1
                DCD     UART1_BUSY_IRQHandler     ; 109
                DCD     UART1_TX_FIFO_IRQHandler  ; 110
                DCD     UART1_RX_FIFO_IRQHandler  ; 111
                DCD     UART1_ERR_IRQHandler      ; 112
                DCD     UART1_RT_IRQHandler       ; 113
                DCD     UART1_TX_IRQHandler       ; 114
                DCD     UART1_RX_IRQHandler       ; 115
                DCD     UART1_MS_IRQHandler       ; 116
                DCD     UART2_IRQHandler     	  ; 117: UART2
                DCD     UART2_BUSY_IRQHandler     ; 118
                DCD     UART2_TX_FIFO_IRQHandler  ; 119
                DCD     UART2_RX_FIFO_IRQHandler  ; 120
                DCD     UART2_ERR_IRQHandler      ; 121
                DCD     UART2_RT_IRQHandler       ; 122
                DCD     UART2_TX_IRQHandler       ; 123
                DCD     UART2_RX_IRQHandler       ; 124
                DCD     UART2_MS_IRQHandler       ; 125
                DCD     UART3_IRQHandler     	  ; 126: UART3
                DCD     UART3_BUSY_IRQHandler     ; 127
                DCD     UART3_TX_FIFO_IRQHandler  ; 128
                DCD     UART3_RX_FIFO_IRQHandler  ; 129
                DCD     UART3_ERR_IRQHandler      ; 130
                DCD     UART3_RT_IRQHandler       ; 131
                DCD     UART3_TX_IRQHandler       ; 132
                DCD     UART3_RX_IRQHandler       ; 133
                DCD     UART3_MS_IRQHandler       ; 134
                DCD     UART4_IRQHandler     	  ; 135: UART4
                DCD     UART4_BUSY_IRQHandler     ; 136
                DCD     UART4_TX_FIFO_IRQHandler  ; 137
                DCD     UART4_RX_FIFO_IRQHandler  ; 138
                DCD     UART4_ERR_IRQHandler      ; 139
                DCD     UART4_RT_IRQHandler       ; 140
                DCD     UART4_TX_IRQHandler       ; 141
                DCD     UART4_RX_IRQHandler       ; 142
                DCD     UART4_MS_IRQHandler       ; 143  
                DCD     USB_IRQHandler     	      ; 144: USB
                DCD     MIL1_IRQHandler     	  ; 145: MKIO 1
                DCD     DAC1_IRQHandler     	  ; 146: DACs
                DCD     DAC2_IRQHandler     	  ; 147
                DCD     DAC3_IRQHandler     	  ; 148
                DCD     DAC4_IRQHandler     	  ; 149
                DCD     DAC1_FIFO_IRQHandler      ; 150: DAC's FIFO
                DCD     DAC2_FIFO_IRQHandler      ; 151
                DCD     DAC3_FIFO_IRQHandler      ; 152
                DCD     DAC4_FIFO_IRQHandler      ; 153  
                DCD     TIMER1_IRQHandler     	  ; 154: TIMERs
                DCD     TIMER2_IRQHandler     	  ; 155
                DCD     TIMER3_IRQHandler     	  ; 156
                DCD     TIMER4_IRQHandler     	  ; 157
                DCD     QENC1_IRQHandler     	  ; 158: ENCODERS
                DCD     QENC2_IRQHandler     	  ; 159
                DCD     0					      ; Reserved160
                DCD     0					      ; Reserved161
                DCD     CAP1_IRQHandler     	  ; 162: CAPTURE
                DCD     CAP2_IRQHandler     	  ; 163
                DCD     CAP3_IRQHandler     	  ; 164
                DCD     CAP4_IRQHandler     	  ; 165
                DCD     PWM1_IRQHandler     	  ; 166: PWM
                DCD     PWM2_IRQHandler     	  ; 167
                DCD     PWM3_IRQHandler     	  ; 168
                DCD     PWM4_IRQHandler     	  ; 169
                DCD     PWM5_IRQHandler     	  ; 170
                DCD     PWM6_IRQHandler     	  ; 171
                DCD     PWM7_IRQHandler     	  ; 172
                DCD     PWM8_IRQHandler     	  ; 173
                DCD     PWM9_IRQHandler     	  ; 174
                DCD     PWM1_TZ_IRQHandler     	  ; 175
                DCD     PWM2_TZ_IRQHandler     	  ; 176
                DCD     PWM3_TZ_IRQHandler     	  ; 177
                DCD     PWM4_TZ_IRQHandler     	  ; 178
                DCD     PWM5_TZ_IRQHandler     	  ; 179
                DCD     PWM6_TZ_IRQHandler     	  ; 180
                DCD     PWM7_TZ_IRQHandler     	  ; 181
                DCD     PWM8_TZ_IRQHandler        ; 182
                DCD     PWM9_TZ_IRQHandler        ; 183
                DCD     PWM1_FIFO_IRQHandler      ; 184
                DCD     PWM2_FIFO_IRQHandler      ; 185
                DCD     PWM3_FIFO_IRQHandler      ; 186
                DCD     PWM4_FIFO_IRQHandler      ; 187
                DCD     PWM5_FIFO_IRQHandler      ; 188
                DCD     PWM6_FIFO_IRQHandler      ; 189
                DCD     PWM7_FIFO_IRQHandler      ; 190
                DCD     PWM8_FIFO_IRQHandler      ; 191
                DCD     PWM9_FIFO_IRQHandler      ; 192
                DCD     CMP1_IRQHandler           ; 193: COMPERATORS
                DCD     CMP2_IRQHandler        	  ; 194
                DCD     CMP3_IRQHandler        	  ; 195
                DCD     CMP4_IRQHandler        	  ; 196
                DCD     ADC_A1_IRQHandler     	  ; 197: ADC
                DCD     ADC_A1_FIFO_IRQHandler    ; 198
                DCD     ADC_B1_IRQHandler     	  ; 199
                DCD     ADC_B1_FIFO_IRQHandler    ; 200
                DCD     ADC_C1_IRQHandler     	  ; 201
                DCD     ADC_C1_FIFO_IRQHandler    ; 202
                DCD     ADC_A2_IRQHandler     	  ; 203
                DCD     ADC_A2_FIFO_IRQHandler    ; 204
                DCD     ADC_B2_IRQHandler     	  ; 205
                DCD     ADC_B2_FIFO_IRQHandler    ; 206
                DCD     ADC_C2_IRQHandler     	  ; 207
                DCD     ADC_C2_FIFO_IRQHandler    ; 208
                DCD     CORDIC_IRQHandler     	  ; 209: CORDIC
                DCD     0					      ; Reserved210
                DCD     MIL2_IRQHandler     	  ; 211: MKIO 2
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors
	
                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler			[WEAK]
                IMPORT  SystemInit
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
                
                LDR     R0, =SystemInit
                BLX     R0
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

SVCall_Handler     PROC
                EXPORT  SVCall_Handler					[WEAK]
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

;   ================    ESila Specific Handler  ==================
FT_EVENT_HandlerDef PROC
                EXPORT  FT_RESET0_4_IRQHandler         [WEAK]
                EXPORT  FT_EVENT0_4_IRQHandler         [WEAK]
                EXPORT  FT_EVENT5_8_IRQHandler         [WEAK]
                EXPORT  FT_EVENT9_12_IRQHandler        [WEAK]
FT_RESET0_4_IRQHandler 
FT_EVENT0_4_IRQHandler 
FT_EVENT5_8_IRQHandler 
FT_EVENT9_12_IRQHandler
                B       .
                ENDP

CLK_IRQHandler  PROC
                EXPORT  CLK_IRQHandler					[WEAK]
                B       .
                ENDP
                    
RTC_IRQHandler  PROC
                EXPORT  RTC_IRQHandler					[WEAK]
                B       .
                ENDP

BKP_IRQHandler  PROC
                EXPORT  BKP_IRQHandler					[WEAK]
                B       .
                ENDP

EBC_ERROR_HandlerDef PROC
                EXPORT  EBC_ERROR0_IRQHandler           [WEAK]
                EXPORT  EBC_ERROR1_IRQHandler           [WEAK]
                EXPORT  EBC_ERROR2_IRQHandler           [WEAK]
                EXPORT  EBC_ERROR3_IRQHandler           [WEAK]
                EXPORT  EBC_ERROR4_IRQHandler           [WEAK]
                EXPORT  EBC_ERROR5_IRQHandler           [WEAK]
                EXPORT  EBC_ERROR6_IRQHandler           [WEAK]
                EXPORT  EBC_ERROR7_IRQHandler           [WEAK]
EBC_ERROR0_IRQHandler  
EBC_ERROR1_IRQHandler  
EBC_ERROR2_IRQHandler  
EBC_ERROR3_IRQHandler  
EBC_ERROR4_IRQHandler  
EBC_ERROR5_IRQHandler  
EBC_ERROR6_IRQHandler  
EBC_ERROR7_IRQHandler 
                B       .
                ENDP         
         
SCRB_ERR_IRQHandler  PROC
                EXPORT  SCRB_ERR_IRQHandler				[WEAK]
                B       .
                ENDP 

SCRB_DONE_IRQHandler  PROC
                EXPORT  SCRB_DONE_IRQHandler			[WEAK]
                B       .
                ENDP
 
DMA_ERR_IRQHandler  PROC
                EXPORT  DMA_ERR_IRQHandler				[WEAK]
                B       .
                ENDP		
   
DMA_DONE_HandlerDef PROC
                EXPORT  DMA_DONE0_IRQHandler            [WEAK]
                EXPORT  DMA_DONE1_IRQHandler            [WEAK]
                EXPORT  DMA_DONE2_IRQHandler            [WEAK]
                EXPORT  DMA_DONE3_IRQHandler            [WEAK]
                EXPORT  DMA_DONE4_IRQHandler            [WEAK]
                EXPORT  DMA_DONE5_IRQHandler            [WEAK]
                EXPORT  DMA_DONE6_IRQHandler            [WEAK]
                EXPORT  DMA_DONE7_IRQHandler            [WEAK]
                EXPORT  DMA_DONE8_IRQHandler            [WEAK]
                EXPORT  DMA_DONE9_IRQHandler            [WEAK]
                EXPORT  DMA_DONE10_IRQHandler           [WEAK]
                EXPORT  DMA_DONE11_IRQHandler           [WEAK]
                EXPORT  DMA_DONE12_IRQHandler           [WEAK]
                EXPORT  DMA_DONE13_IRQHandler           [WEAK]
                EXPORT  DMA_DONE14_IRQHandler           [WEAK]
                EXPORT  DMA_DONE15_IRQHandler           [WEAK]
                EXPORT  DMA_DONE16_IRQHandler           [WEAK]
                EXPORT  DMA_DONE17_IRQHandler           [WEAK]
                EXPORT  DMA_DONE18_IRQHandler           [WEAK]
                EXPORT  DMA_DONE19_IRQHandler           [WEAK]
                EXPORT  DMA_DONE20_IRQHandler           [WEAK]
                EXPORT  DMA_DONE21_IRQHandler           [WEAK]
                EXPORT  DMA_DONE22_IRQHandler           [WEAK]
                EXPORT  DMA_DONE23_IRQHandler           [WEAK]
                EXPORT  DMA_DONE24_IRQHandler           [WEAK]
                EXPORT  DMA_DONE25_IRQHandler           [WEAK]
                EXPORT  DMA_DONE26_IRQHandler           [WEAK]
                EXPORT  DMA_DONE27_IRQHandler           [WEAK]
                EXPORT  DMA_DONE28_IRQHandler           [WEAK]
                EXPORT  DMA_DONE29_IRQHandler           [WEAK]
                EXPORT  DMA_DONE30_IRQHandler           [WEAK]
                EXPORT  DMA_DONE31_IRQHandler           [WEAK]
DMA_DONE0_IRQHandler
DMA_DONE1_IRQHandler
DMA_DONE2_IRQHandler
DMA_DONE3_IRQHandler
DMA_DONE4_IRQHandler
DMA_DONE5_IRQHandler
DMA_DONE6_IRQHandler
DMA_DONE7_IRQHandler
DMA_DONE8_IRQHandler
DMA_DONE9_IRQHandler
DMA_DONE10_IRQHandler
DMA_DONE11_IRQHandler
DMA_DONE12_IRQHandler
DMA_DONE13_IRQHandler
DMA_DONE14_IRQHandler
DMA_DONE15_IRQHandler
DMA_DONE16_IRQHandler
DMA_DONE17_IRQHandler
DMA_DONE18_IRQHandler
DMA_DONE19_IRQHandler
DMA_DONE20_IRQHandler
DMA_DONE21_IRQHandler
DMA_DONE22_IRQHandler
DMA_DONE23_IRQHandler
DMA_DONE24_IRQHandler
DMA_DONE25_IRQHandler
DMA_DONE26_IRQHandler
DMA_DONE27_IRQHandler
DMA_DONE28_IRQHandler
DMA_DONE29_IRQHandler
DMA_DONE30_IRQHandler
DMA_DONE31_IRQHandler
                B       .
                ENDP

PORTA_IRQHandler  PROC
                EXPORT  PORTA_IRQHandler				[WEAK]
                B       .
                ENDP	
PORTB_IRQHandler  PROC
                EXPORT  PORTB_IRQHandler				[WEAK]
                B       .
                ENDP	
PORTC_IRQHandler  PROC
                EXPORT  PORTC_IRQHandler				[WEAK]
                B       .
                ENDP	
PORTD_IRQHandler  PROC
                EXPORT  PORTD_IRQHandler				[WEAK]
                B       .
                ENDP	
ETH1_IRQHandler  PROC
                EXPORT  ETH1_IRQHandler				    [WEAK]
                B       .
                ENDP	
CAN1_IRQHandler  PROC
                EXPORT  CAN1_IRQHandler				    [WEAK]
                B       .
                ENDP
CAN2_IRQHandler  PROC
                EXPORT  CAN2_IRQHandler				    [WEAK]
                B       .
                ENDP
         
SSP1_HandlerDef  PROC
                EXPORT  SSP1_IRQHandler 			    [WEAK]
                EXPORT  SSP1_RX_IRQHandler			    [WEAK]
                EXPORT  SSP1_TX_IRQHandler			    [WEAK]
                EXPORT  SSP1_ROR_IRQHandler			    [WEAK]
                EXPORT  SSP1_RT_IRQHandler			    [WEAK]
                EXPORT  SSP1_RX_FIFO_IRQHandler			[WEAK]
                EXPORT  SSP1_TX_FIFO_IRQHandler			[WEAK]
                EXPORT  SSP1_BUSY_IRQHandler			[WEAK]                    
SSP1_IRQHandler          
SSP1_RX_IRQHandler        
SSP1_TX_IRQHandler        
SSP1_ROR_IRQHandler       
SSP1_RT_IRQHandler        
SSP1_RX_FIFO_IRQHandler   
SSP1_TX_FIFO_IRQHandler   
SSP1_BUSY_IRQHandler      
                B       .
                ENDP         

SSP2_HandlerDef  PROC
                EXPORT  SSP2_IRQHandler 			    [WEAK]
                EXPORT  SSP2_RX_IRQHandler			    [WEAK]
                EXPORT  SSP2_TX_IRQHandler			    [WEAK]
                EXPORT  SSP2_ROR_IRQHandler			    [WEAK]
                EXPORT  SSP2_RT_IRQHandler			    [WEAK]
                EXPORT  SSP2_RX_FIFO_IRQHandler			[WEAK]
                EXPORT  SSP2_TX_FIFO_IRQHandler			[WEAK]
                EXPORT  SSP2_BUSY_IRQHandler			[WEAK]                    
SSP2_IRQHandler          
SSP2_RX_IRQHandler        
SSP2_TX_IRQHandler        
SSP2_ROR_IRQHandler       
SSP2_RT_IRQHandler        
SSP2_RX_FIFO_IRQHandler   
SSP2_TX_FIFO_IRQHandler   
SSP2_BUSY_IRQHandler      
                B       .
                ENDP

UART1_HandlerDef  PROC
                EXPORT  UART1_IRQHandler			    [WEAK]
                EXPORT  UART1_BUSY_IRQHandler			[WEAK]
                EXPORT  UART1_TX_FIFO_IRQHandler		[WEAK]
                EXPORT  UART1_RX_FIFO_IRQHandler		[WEAK]
                EXPORT  UART1_ERR_IRQHandler			[WEAK]
                EXPORT  UART1_RT_IRQHandler			    [WEAK]
                EXPORT  UART1_TX_IRQHandler			    [WEAK]
                EXPORT  UART1_RX_IRQHandler			    [WEAK]
                EXPORT  UART1_MS_IRQHandler			    [WEAK]
UART1_IRQHandler
UART1_BUSY_IRQHandler
UART1_TX_FIFO_IRQHandler
UART1_RX_FIFO_IRQHandler
UART1_ERR_IRQHandler
UART1_RT_IRQHandler
UART1_TX_IRQHandler
UART1_RX_IRQHandler
UART1_MS_IRQHandler
                B       .
                ENDP

UART2_HandlerDef  PROC
                EXPORT  UART2_IRQHandler			    [WEAK]
                EXPORT  UART2_BUSY_IRQHandler			[WEAK]
                EXPORT  UART2_TX_FIFO_IRQHandler		[WEAK]
                EXPORT  UART2_RX_FIFO_IRQHandler		[WEAK]
                EXPORT  UART2_ERR_IRQHandler			[WEAK]
                EXPORT  UART2_RT_IRQHandler			    [WEAK]
                EXPORT  UART2_TX_IRQHandler			    [WEAK]
                EXPORT  UART2_RX_IRQHandler			    [WEAK]
                EXPORT  UART2_MS_IRQHandler			    [WEAK]
UART2_IRQHandler
UART2_BUSY_IRQHandler
UART2_TX_FIFO_IRQHandler
UART2_RX_FIFO_IRQHandler
UART2_ERR_IRQHandler
UART2_RT_IRQHandler
UART2_TX_IRQHandler
UART2_RX_IRQHandler
UART2_MS_IRQHandler
                B       .
                ENDP

UART3_HandlerDef  PROC
                EXPORT  UART3_IRQHandler			    [WEAK]
                EXPORT  UART3_BUSY_IRQHandler			[WEAK]
                EXPORT  UART3_TX_FIFO_IRQHandler		[WEAK]
                EXPORT  UART3_RX_FIFO_IRQHandler		[WEAK]
                EXPORT  UART3_ERR_IRQHandler			[WEAK]
                EXPORT  UART3_RT_IRQHandler			    [WEAK]
                EXPORT  UART3_TX_IRQHandler			    [WEAK]
                EXPORT  UART3_RX_IRQHandler			    [WEAK]
                EXPORT  UART3_MS_IRQHandler			    [WEAK]
UART3_IRQHandler
UART3_BUSY_IRQHandler
UART3_TX_FIFO_IRQHandler
UART3_RX_FIFO_IRQHandler
UART3_ERR_IRQHandler
UART3_RT_IRQHandler
UART3_TX_IRQHandler
UART3_RX_IRQHandler
UART3_MS_IRQHandler
                B       .
                ENDP

UART4_HandlerDef  PROC
                EXPORT  UART4_IRQHandler			    [WEAK]
                EXPORT  UART4_BUSY_IRQHandler			[WEAK]
                EXPORT  UART4_TX_FIFO_IRQHandler		[WEAK]
                EXPORT  UART4_RX_FIFO_IRQHandler		[WEAK]
                EXPORT  UART4_ERR_IRQHandler			[WEAK]
                EXPORT  UART4_RT_IRQHandler			    [WEAK]
                EXPORT  UART4_TX_IRQHandler			    [WEAK]
                EXPORT  UART4_RX_IRQHandler			    [WEAK]
                EXPORT  UART4_MS_IRQHandler			    [WEAK]
UART4_IRQHandler
UART4_BUSY_IRQHandler
UART4_TX_FIFO_IRQHandler
UART4_RX_FIFO_IRQHandler
UART4_ERR_IRQHandler
UART4_RT_IRQHandler
UART4_TX_IRQHandler
UART4_RX_IRQHandler
UART4_MS_IRQHandler
                B       .
                ENDP

USB_IRQHandler  PROC
                EXPORT  USB_IRQHandler				    [WEAK]
                B       .
                ENDP
                    
MIL_HandlerDef  PROC
                EXPORT  MIL1_IRQHandler				    [WEAK]
                EXPORT  MIL2_IRQHandler				    [WEAK]
MIL1_IRQHandler
MIL2_IRQHandler     	  
                B       .
                ENDP
                    
DAC_HandlerDef  PROC
                EXPORT  DAC1_IRQHandler		            [WEAK]
                EXPORT  DAC2_IRQHandler		            [WEAK]     	  
                EXPORT  DAC3_IRQHandler		            [WEAK]
                EXPORT  DAC4_IRQHandler		            [WEAK]
                EXPORT  DAC1_FIFO_IRQHandler		    [WEAK]
                EXPORT  DAC2_FIFO_IRQHandler		    [WEAK]
                EXPORT  DAC3_FIFO_IRQHandler		    [WEAK]
                EXPORT  DAC4_FIFO_IRQHandler		    [WEAK]
DAC1_IRQHandler
DAC2_IRQHandler
DAC3_IRQHandler
DAC4_IRQHandler
DAC1_FIFO_IRQHandler
DAC2_FIFO_IRQHandler
DAC3_FIFO_IRQHandler
DAC4_FIFO_IRQHandler                    
                B       .
                ENDP
     	      
TIMER_HandlerDef  PROC
                EXPORT  TIMER1_IRQHandler		        [WEAK]
                EXPORT  TIMER2_IRQHandler		        [WEAK]
                EXPORT  TIMER3_IRQHandler		        [WEAK]
                EXPORT  TIMER4_IRQHandler		        [WEAK]
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
TIMER4_IRQHandler
                B       .
                ENDP

QENCODER_HandlerDef  PROC
                EXPORT  QENC1_IRQHandler		        [WEAK]
                EXPORT  QENC2_IRQHandler		        [WEAK]
QENC1_IRQHandler
QENC2_IRQHandler
                B       .
                ENDP

CAP_HandlerDef  PROC
                EXPORT  CAP1_IRQHandler		            [WEAK]
                EXPORT  CAP2_IRQHandler		            [WEAK]
                EXPORT  CAP3_IRQHandler		            [WEAK]
                EXPORT  CAP4_IRQHandler		            [WEAK]
CAP1_IRQHandler
CAP2_IRQHandler
CAP3_IRQHandler
CAP4_IRQHandler
                B       .
                ENDP

PWM_HandlerDef  PROC
                EXPORT  PWM1_IRQHandler     		     [WEAK]
                EXPORT  PWM2_IRQHandler     		     [WEAK]
                EXPORT  PWM3_IRQHandler     		     [WEAK]
                EXPORT  PWM4_IRQHandler     		     [WEAK]
                EXPORT  PWM5_IRQHandler     		     [WEAK]
                EXPORT  PWM6_IRQHandler     		     [WEAK]
                EXPORT  PWM7_IRQHandler     		     [WEAK]
                EXPORT  PWM8_IRQHandler     		     [WEAK]
                EXPORT  PWM9_IRQHandler     		     [WEAK]
                EXPORT  PWM1_TZ_IRQHandler  		     [WEAK]
                EXPORT  PWM2_TZ_IRQHandler  		     [WEAK]
                EXPORT  PWM3_TZ_IRQHandler  		     [WEAK]
                EXPORT  PWM4_TZ_IRQHandler  		     [WEAK]
                EXPORT  PWM5_TZ_IRQHandler  		     [WEAK]
                EXPORT  PWM6_TZ_IRQHandler  		     [WEAK]
                EXPORT  PWM7_TZ_IRQHandler  		     [WEAK]
                EXPORT  PWM8_TZ_IRQHandler  		     [WEAK]
                EXPORT  PWM9_TZ_IRQHandler  		     [WEAK]
                EXPORT  PWM1_FIFO_IRQHandler		     [WEAK]
                EXPORT  PWM2_FIFO_IRQHandler		     [WEAK]
                EXPORT  PWM3_FIFO_IRQHandler		     [WEAK]
                EXPORT  PWM4_FIFO_IRQHandler		     [WEAK]
                EXPORT  PWM5_FIFO_IRQHandler		     [WEAK]
                EXPORT  PWM6_FIFO_IRQHandler		     [WEAK]
                EXPORT  PWM7_FIFO_IRQHandler		     [WEAK]
                EXPORT  PWM8_FIFO_IRQHandler		     [WEAK]
                EXPORT  PWM9_FIFO_IRQHandler		     [WEAK]
PWM1_IRQHandler     	  
PWM2_IRQHandler     	  
PWM3_IRQHandler     	  
PWM4_IRQHandler     	  
PWM5_IRQHandler     	  
PWM6_IRQHandler     	  
PWM7_IRQHandler     	  
PWM8_IRQHandler     	  
PWM9_IRQHandler     	  
PWM1_TZ_IRQHandler     	  
PWM2_TZ_IRQHandler     	  
PWM3_TZ_IRQHandler     	  
PWM4_TZ_IRQHandler     	  
PWM5_TZ_IRQHandler     	  
PWM6_TZ_IRQHandler     	  
PWM7_TZ_IRQHandler     	  
PWM8_TZ_IRQHandler        
PWM9_TZ_IRQHandler        
PWM1_FIFO_IRQHandler      
PWM2_FIFO_IRQHandler      
PWM3_FIFO_IRQHandler      
PWM4_FIFO_IRQHandler      
PWM5_FIFO_IRQHandler      
PWM6_FIFO_IRQHandler      
PWM7_FIFO_IRQHandler      
PWM8_FIFO_IRQHandler      
PWM9_FIFO_IRQHandler
                B       .
                ENDP

CMP_HandlerDef  PROC
                EXPORT  CMP1_IRQHandler		            [WEAK]
                EXPORT  CMP2_IRQHandler		            [WEAK]
                EXPORT  CMP3_IRQHandler		            [WEAK]
                EXPORT  CMP4_IRQHandler		            [WEAK]
CMP1_IRQHandler
CMP2_IRQHandler
CMP3_IRQHandler
CMP4_IRQHandler
                B       .
                ENDP


ADC_HandlerDef  PROC
                EXPORT  ADC_A1_IRQHandler               [WEAK]
                EXPORT  ADC_A2_IRQHandler               [WEAK]
                EXPORT  ADC_B1_IRQHandler               [WEAK]
                EXPORT  ADC_B2_IRQHandler               [WEAK]
                EXPORT  ADC_C1_IRQHandler               [WEAK]
                EXPORT  ADC_C2_IRQHandler               [WEAK]
                EXPORT  ADC_A1_FIFO_IRQHandler          [WEAK]
                EXPORT  ADC_A2_FIFO_IRQHandler          [WEAK]
                EXPORT  ADC_B1_FIFO_IRQHandler          [WEAK]
                EXPORT  ADC_B2_FIFO_IRQHandler          [WEAK]
                EXPORT  ADC_C1_FIFO_IRQHandler          [WEAK]
                EXPORT  ADC_C2_FIFO_IRQHandler          [WEAK]
ADC_A1_IRQHandler     
ADC_A2_IRQHandler     
ADC_B1_IRQHandler     
ADC_B2_IRQHandler     
ADC_C1_IRQHandler     
ADC_C2_IRQHandler     
ADC_A1_FIFO_IRQHandler
ADC_A2_FIFO_IRQHandler
ADC_B1_FIFO_IRQHandler
ADC_B2_FIFO_IRQHandler
ADC_C1_FIFO_IRQHandler
ADC_C2_FIFO_IRQHandler    
                B       .
                ENDP

CORDIC_IRQHandler  PROC
                EXPORT  CORDIC_IRQHandler				[WEAK]
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