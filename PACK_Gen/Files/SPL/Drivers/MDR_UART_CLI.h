#ifndef _MDR_UART_CLI_H
#define _MDR_UART_CLI_H

#include <MDR_GPIO.h>
#include <MDR_UART.h>

void MDR_CLI_UART_Init(uint32_t baudRate, uint32_t UART_ClockHz, MDR_UART_CfgPinsGPIO *pinsGPIO);

//  Опрос на наличие команды на обработку
//  Перечисление команд задать в MDR_Config.h в CLI_CMD_e
CLI_CMD_e   MDR_CLI_GetCommand(uint16_t *lenCmdParams, uint8_t **pCmdParams);

void MDR_CLI_GetResponceBuf(uint16_t *lenAckBuf, uint8_t **pAckBuf);
void MDR_CLI_SetResponse(CLI_CMD_e cmd, uint16_t lenAckParams);



#endif  //_MDR_UART_CLI_H
