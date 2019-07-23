# MDR_Pack_v6

Pack поддержки микроконтроллеров 1986ВК214 и 1986ВК234 для Keil. Поддерживаются так-же микроконтроллеры 1986ВЕ1, 1986ВЕ3, 1986ВЕ9х, 1901ВЦ1, 1986ВЕ4, но только на уровне периферийных блоков существующих в 1986ВК2х4.

Изначально Pack ориентировался на компилятор Keil v6, но эта цель временно отложена. Компилятор v6 планируется проверить при добавлении поддержки для 1986ВЕ8, 1923ВК014 и электросилы (ESila).

Ветка Pack_VK214 - Сохранен вариант Pack для 1986ВК214 и 1986ВК234.
Ветка Master - Внесение поддержки 1986ВЕ8, 1923ВК014, ESila в общий Pack.

## Migrate to master from VK214

Переименованы типы
  * MDR_CLK_DIV_256 на MDR_Div256P, соответственно MDR_CLK_div1 на MDR_Div256P_div1 и т.д.
  * MDR_BRG_DIV_128 на MDR_Div128P, соответственно MDR_BRG_div1 на MDR_Div128P_div1 и т.д.
  * MDR_PSC_DIV_8   на MDR_Div8P, соответственно MDR_PSC_div1 на MDR_Div8P_div1 и т.д.

Функции:
  * MaskClrSet на MDR_MaskClrSet
  * MDR_GPIO_ClockOn на MDR_GPIO_Enable
  * MDR_Port_InitDigPermRegs на MDR_Port_InitDigGroupPinCfg
    * MDR_Port_InitDigGroupPinCfg(MDR_PIN_PullPush на MDR_Port_InitDigGroupPinCfg(MDR_Off

Структуры:
  * MDR_Port_InitDigGroupPinCfg на MDR_PinDig_GroupPinCfg