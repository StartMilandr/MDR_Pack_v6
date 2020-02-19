#ifndef _JTAG_CONFIG_H
#define _JTAG_CONFIG_H

#define JTAG_PORT_TCK   MDR_GPIO_D
#define JTAG_PORT_TMS   MDR_GPIO_D
#define JTAG_PORT_TDI   MDR_GPIO_D
#define JTAG_PORT_TDO   MDR_GPIO_A

#define JTAG_PIN_TCK    MDR_Pin_9
#define JTAG_PIN_TMS    MDR_Pin_10
#define JTAG_PIN_TDI    MDR_Pin_8
#define JTAG_PIN_TDO    MDR_Pin_9

#define JTAG_PIN_PWR    MDR_PIN_MAXFAST

#define JTAG_REMOVE_DELAYS  0


#endif  //  _JTAG_CONFIG_H
