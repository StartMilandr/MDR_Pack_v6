# Примеры использования блока UART

Пока реализован только простейший пример реализации передачи сообщений по UART. Постепенно добавятся прочие варианты работы, в частности MODBUS, IrDA, DMA и т.д.

Кнопки:
  * KEY1 (UP) - переключает активный тест
  * KEY2 (Right) - посылает сообщение "Hello! I'm fine!"

## UART_Debug
В этом тесте инициализируется драйвер логгирования через UART по умолчанию. Все что необходимо - это вызвать функцию MDR_UART_DBG_Init() и далее посылать логи через printf("text"). В этом тесте инициализируется только вывод TX, RX пин не используется.

## UART_DebugRate
Аналог варианта UART_Debug, но инициализация происходит через функцию MDR_UART_DBG_InitEx(UART_BAUD_9600, true), устанавливающую скорость и разрешающую использование приемника UART.

Для приема команд от внешнего источника (РС) включаются прерывания, где в обработчике проверяются допустимые команды. И если приходит команда на смену скорости, то меняется скорость обмена по UART.

## Comming soon...
Тесты - это варианты использования, в каждом тесте меняется один параметр и проверяется работоспособность блока.
Изменяемый параметр глобальный - т.е. при переключении в другой тест этот параметр сохраняет значение для нового теста.
....