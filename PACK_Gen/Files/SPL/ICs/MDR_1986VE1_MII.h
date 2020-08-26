#ifndef MDR_1986VE1_MII_H
#define MDR_1986VE1_MII_H

#include <MDR_Config.h>
#include <MDR_Ethernet.h>

// Для инициализации MII необходимо перевести Ethernet PHY в состояние сброса.
// Но чтобы PHY отработал команду записи ресета в регистр на него необходимо подать частоту.
// В рабочем состоянии PHY это должна быть частота 25МГц с HSE2.
// Но так как PHY работать не будет, то достаточно подать другую частоту - например HSE.
// Она нужна только для того, чтобы блок PHY ушел в состояние Reset!
//
// Пины MII настраиваются внутри MDR_1986VE1_MII_Init().

// ЭТАПЫ ИНИЦИАЛИЗАЦИИ:
//   1: - Подать частоту на PHY
void MDR_1986VE1_MII_SetPhyClockHSE(void);                  // HSE должен быть уже включен и готов
__STATIC_INLINE void MDR_1986VE1_MII_SetPhyClockHSE2(void)  // Функция сама включает HSE2 
{
  MDR_Eth_SetClockHSE2();
}
//   2: - Вызвать Init для настройки MAC, вывода PHY в Reset и настройки пинов MII
//   Настройки с которыми будет настроен MAC в файле - MDR_1986VE1_MII_Config.h
void MDR_1986VE1_MII_Init(void);
//   3: Настроить NVIC если требуются прерывания
//   4: Запустить блок Ethernet - MII готов к работе.
__STATIC_INLINE void MDR_1986VE1_MII_Start(void)
{
  MDR_Eth_Start(MDR_ETH1);
}


// КОМБО-ФУНКЦИИ (готовые варианты):
__STATIC_INLINE void MDR_1986VE1_MII_InitHSE(void)
{
  MDR_1986VE1_MII_SetPhyClockHSE();
  MDR_1986VE1_MII_Init();
  MDR_1986VE1_MII_Start();
}

__STATIC_INLINE void MDR_1986VE1_MII_InitHSE2(void)
{
  MDR_1986VE1_MII_SetPhyClockHSE2();
  MDR_1986VE1_MII_Init();
  MDR_1986VE1_MII_Start();
}

__STATIC_INLINE void MDR_1986VE1_MII_InitHSE_IRQ(uint32_t irqPriority)
{
  MDR_1986VE1_MII_SetPhyClockHSE();
  MDR_1986VE1_MII_Init();
  MDR_ETH_NVIC_Enable(MDR_ETH1, irqPriority);
  MDR_1986VE1_MII_Start();
}



#endif  //MDR_1986VE1_MII_H

