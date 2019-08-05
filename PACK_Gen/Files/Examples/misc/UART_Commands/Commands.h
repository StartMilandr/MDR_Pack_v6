#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>
#include <stdbool.h>

//	Получение данных
bool COMM_AddData(uint8_t data);
void COMM_DataThreadCompleted(void);

//  Исполнение команды
bool COMM_CheckDoExecCommand(void);
bool COMM_ExecCommand(void);

#endif 	//COMMANDS_H
