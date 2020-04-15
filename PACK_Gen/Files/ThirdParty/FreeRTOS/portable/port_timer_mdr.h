

#if configOVERRIDE_DEFAULT_TICK_CONFIGURATION

#include <MDR_Config.h>
#include <MDR_Timer.h>


void xPortSysTickHandler( void )
{
  uint32_t ulPreviousMask;

    MDR_FREE_RTOS_TIMER->TIMERx->STATUS = 0;
  
	ulPreviousMask = portSET_INTERRUPT_MASK_FROM_ISR();
	{
		/* Increment the RTOS tick. */
		if( xTaskIncrementTick() != pdFALSE )
		{
			/* Pend a context switch. */
			portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
		}
	}
	portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
void vPortSetupTimerInterrupt( void )
{
  /* Calculate the constants required to configure the tick interrupt. */
  #if( configUSE_TICKLESS_IDLE == 1 )
    ulTimerCountsForOneTick = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ );
    //xMaximumPossibleSuppressedTicks = portMAX_24_BIT_NUMBER / ulTimerCountsForOneTick;    
    xMaximumPossibleSuppressedTicks = MDR_TIMER_MAX_VALUE / ulTimerCountsForOneTick;
    ulStoppedTimerCompensation = portMISSED_COUNTS_FACTOR;
  #endif /* configUSE_TICKLESS_IDLE */

  
  //  Для 1986VE4,VE214,VE234 частота TIM_Clock формируется мультиплексорами
  //  В VE214 отдельный выбор частоты с делителем для каждого из блоков UART, SSP, Timer
  //  В остальных МК TIM_Clock формируется только из HCLK (равной CPU_Clock) - выбор источника не требуется
  #ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP  
    MDR_SetClock_Timer1(MDR_PER_PLLCPUo);
    MDR_SetClock_Timer2(MDR_PER_PLLCPUo);
  #elif defined (MDR_TIM_CLOCK_FROM_PER_CLOCK)
    MDR_SetClock_UartTimSSP(MDR_PER_PLLCPUo);
  #endif 
  
  uint_tim period;
  uint16_t PSG;
  MDR_Timer_CalcPeriodAndPSG_F(configTICK_RATE_HZ, configCPU_CLOCK_HZ, &period, &PSG);
  MDR_Timer_InitPeriodDir(MDR_FREE_RTOS_TIMER, MDR_Div128P_div1, PSG, period, false, TIM_CountDown);
  MDR_Timer_EnableEventIQR(MDR_FREE_RTOS_TIMER->TIMERx, TIM_FL_CNT_ZERO);
  NVIC_EnableIRQ(MDR_FREE_RTOS_TIMER->TIMERx_IRQn);
  NVIC_SetPriority(MDR_FREE_RTOS_TIMER->TIMERx_IRQn, portMIN_INTERRUPT_PRIORITY);
  MDR_Timer_Start(MDR_FREE_RTOS_TIMER);
}  
 
  /*-----------------------------------------------------------*/

#if( configUSE_TICKLESS_IDLE == 1 )

  #define portTIMER_STOP            MDR_FREE_RTOS_TIMER->TIMERx->CNTRL &= ~MDR_TIMER_CNTRL_CNT_EN_Msk
  #define portTIMER_START           MDR_FREE_RTOS_TIMER->TIMERx->CNTRL |= MDR_TIMER_CNTRL_CNT_EN_Msk
  #define portTIMER_CNT             MDR_FREE_RTOS_TIMER->TIMERx->CNT
  #define portTIMER_SetCnt(val)     MDR_Timer_ChangeCNT(MDR_FREE_RTOS_TIMER->TIMERx, (val))   
  #define portTIMER_CLR_CNT_ZERO    MDR_FREE_RTOS_TIMER->TIMERx->STATUS = 0
  #define portTIMER_IS_CNT_ZERO   ( MDR_FREE_RTOS_TIMER->TIMERx->STATUS & MDR_TIM_EVENT_CNT_ZERO_Msk ) != 0
         

  #if   defined (__CC_ARM)
    #define portDSB  __dsb( portSY_FULL_READ_WRITE )
    #define portISB  __isb( portSY_FULL_READ_WRITE )

  #elif (__ARMCC_VERSION >= 6010050)
    #define portDSB  __asm volatile( "dsb" );
    #define portISB  __asm volatile( "isb" );
  #endif

  void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
  {
  uint32_t ulReloadValue, ulCompleteTickPeriods, ulCompletedSysTickDecrements;
  TickType_t xModifiableIdleTime;

    /* Make sure the SysTick reload value does not overflow the counter. */
    if( xExpectedIdleTime > xMaximumPossibleSuppressedTicks )
    {
      xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
    }

    /* Stop the SysTick momentarily. The time the SysTick is stopped for
    is accounted for as best it can be, but using the tickless mode will
    inevitably result in some tiny drift of the time maintained by the
    kernel with respect to calendar time. */
    //portNVIC_SYSTICK_CTRL_REG &= ~portNVIC_SYSTICK_ENABLE_BIT;
    portTIMER_STOP;

    /* Calculate the reload value required to wait xExpectedIdleTime
    tick periods.  -1 is used because this code will execute part way
    through one of the tick periods. */
    //ulReloadValue = portNVIC_SYSTICK_CURRENT_VALUE_REG + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );
    ulReloadValue = portTIMER_CNT + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );
    if( ulReloadValue > ulStoppedTimerCompensation )
    {
      ulReloadValue -= ulStoppedTimerCompensation;
    }

    /* Enter a critical section but don't use the taskENTER_CRITICAL()
    method as that will mask interrupts that should exit sleep mode. */
    __disable_irq();
    portDSB; //__dsb( portSY_FULL_READ_WRITE );
    portISB; //__isb( portSY_FULL_READ_WRITE );

    /* If a context switch is pending or a task is waiting for the scheduler
    to be unsuspended then abandon the low power entry. */
    if( eTaskConfirmSleepModeStatus() == eAbortSleep )
    {
      /* Restart from whatever is left in the count register to complete
      this tick period. */
      //portNVIC_SYSTICK_LOAD_REG = portNVIC_SYSTICK_CURRENT_VALUE_REG;
      //portTIMER_SetCnt(portTIMER_CNT);

      /* Restart SysTick. */
      //portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;
          portTIMER_START;

      /* Reset the reload register to the value required for normal tick
      periods. */
      //portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;

      /* Re-enable interrupts - see comments above __disable_irq() call above. */
      __enable_irq();
    }
    else
    {
      /* Set the new reload value. */
      //portNVIC_SYSTICK_LOAD_REG = ulReloadValue;
      portTIMER_SetCnt(ulReloadValue);
      
      /* Clear the SysTick count flag and set the count value back to
      zero. */
      //portNVIC_SYSTICK_CURRENT_VALUE_REG = 0UL;

      /* Restart SysTick. */
      //portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;
          portTIMER_CLR_CNT_ZERO;
          portTIMER_START;


      /* Sleep until something happens. configPRE_SLEEP_PROCESSING() can
      set its parameter to 0 to indicate that its implementation contains
      its own wait for interrupt or wait for event instruction, and so wfi
      should not be executed again. However, the original expected idle
      time variable must remain unmodified, so a copy is taken. */
      xModifiableIdleTime = xExpectedIdleTime;
      configPRE_SLEEP_PROCESSING( xModifiableIdleTime );
      if( xModifiableIdleTime > 0 )
      {
        portDSB; //__dsb( portSY_FULL_READ_WRITE );
        __wfi();
        portISB; //__isb( portSY_FULL_READ_WRITE );
      }
      configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

      /* Re-enable interrupts to allow the interrupt that brought the MCU
      out of sleep mode to execute immediately. see comments above
      __disable_interrupt() call above. */
      __enable_irq();
      portDSB; //__dsb( portSY_FULL_READ_WRITE );
      portISB; //__isb( portSY_FULL_READ_WRITE );

      /* Disable interrupts again because the clock is about to be stopped
      and interrupts that execute while the clock is stopped will increase
      any slippage between the time maintained by the RTOS and calendar
      time. */
      __disable_irq();
      portDSB; //__dsb( portSY_FULL_READ_WRITE );
      portISB; //__isb( portSY_FULL_READ_WRITE );

      /* Disable the SysTick clock without reading the
      portNVIC_SYSTICK_CTRL_REG register to ensure the
      portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
      the time the SysTick is stopped for is accounted for as best it can
      be, but using the tickless mode will inevitably result in some tiny
      drift of the time maintained by the kernel with respect to calendar
      time*/
      //portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT );
          portTIMER_STOP;

      /* Determine if the SysTick clock has already counted to zero and
      been set back to the current reload value (the reload back being
      correct for the entire expected idle time) or if the SysTick is yet
      to count to zero (in which case an interrupt other than the SysTick
      must have brought the system out of sleep mode). */
      //if( ( portNVIC_SYSTICK_CTRL_REG & portNVIC_SYSTICK_COUNT_FLAG_BIT ) != 0 )
      if( ( portTIMER_IS_CNT_ZERO ) )     
      {
        uint32_t ulCalculatedLoadValue;

        /* The tick interrupt is already pending, and the SysTick count
        reloaded with ulReloadValue.  Reset the
        portNVIC_SYSTICK_LOAD with whatever remains of this tick
        period. */
        //ulCalculatedLoadValue = ( ulTimerCountsForOneTick - 1UL ) - ( ulReloadValue - portNVIC_SYSTICK_CURRENT_VALUE_REG );
        ulCalculatedLoadValue = ( ulTimerCountsForOneTick - 1UL ) - ( ulReloadValue - portTIMER_CNT );
        

        /* Don't allow a tiny value, or values that have somehow
        underflowed because the post sleep hook did something
        that took too long. */
        if( ( ulCalculatedLoadValue < ulStoppedTimerCompensation ) || ( ulCalculatedLoadValue > ulTimerCountsForOneTick ) )
        {
          ulCalculatedLoadValue = ( ulTimerCountsForOneTick - 1UL );
        }

        //portNVIC_SYSTICK_LOAD_REG = ulCalculatedLoadValue;
        portTIMER_SetCnt(ulCalculatedLoadValue);

        /* As the pending tick will be processed as soon as this
        function exits, the tick value maintained by the tick is stepped
        forward by one less than the time spent waiting. */
        ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
      }
      else
      {
        /* Something other than the tick interrupt ended the sleep.
        Work out how long the sleep lasted rounded to complete tick
        periods (not the ulReload value which accounted for part
        ticks). */
        //ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - portNVIC_SYSTICK_CURRENT_VALUE_REG;
        ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - portTIMER_CNT;

        /* How many complete tick periods passed while the processor
        was waiting? */
        ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

        /* The reload value is set to whatever fraction of a single tick
        period remains. */
        //portNVIC_SYSTICK_LOAD_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;     
        portTIMER_SetCnt(( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements);
      }

      /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD
      again, then set portNVIC_SYSTICK_LOAD back to its standard
      value. */
      //portNVIC_SYSTICK_CURRENT_VALUE_REG = 0UL;
      //portTIMER_SetCnt(0);
      
      //portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;
      portTIMER_CLR_CNT_ZERO;
      portTIMER_START;
      
      vTaskStepTick( ulCompleteTickPeriods );
      //portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
      //portTIMER_SetPeriod(ulTimerCountsForOneTick - 1UL);

      /* Exit with interrpts enabled. */
      __enable_irq();
    }
  }
#endif  //  #if( configUSE_TICKLESS_IDLE == 1 )

#endif // configOVERRIDE_DEFAULT_TICK_CONFIGURATION


