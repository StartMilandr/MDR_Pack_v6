#ifndef _MDR_HSRPRP_CONFIG
#define _MDR_HSRPRP_CONFIG

#include <MDR_Config.h>
#include <MDR_HSR_defs.h>


#define MDR_HSR_REDBOX_EN   0



#define ETH_PortA           MDR_ETH1
#define ETH_PortB           MDR_ETH2

#ifdef MDR_ETH3
	#define ETH_PortInterlink   MDR_ETH3
	#define MDR_HSR_REDBOX_EN   0
#endif

#define ETH1_HSRPRP_PORT    MDR_HSRPRP_PortA
#define ETH2_HSRPRP_PORT    MDR_HSRPRP_PortB
#define ETH3_HSRPRP_PORT    MDR_HSRPRP_Interlink


#define DUPLICATE_TABLE_LEN_PORT				10
#define DUPLICATE_TABLE_LEN_HOST				10
#define DUPLICATE_TABLE_LEN_INTERLINK		10

#define DUPLICATE_TABLE_FREE_ITEM_ON_DUPL_RX	0

//	Количество FrameItems - фреймов на обработку
#define MDR_HSRPRP_FRAME_ITEM_COUNT   	10


//	======	Настройки времени	=======
#define TIMER_HSRPRP		MDR_TIMER1ex

//	Делители для 80MHz (максимальная частоты для 1986ВЕ3Т)
#define TIM_BRG_80MHZ_TO_1MS 		MDR_Div128P_div8
#define TIM_PSC_80MHZ_TO_1MS 		10000

//  Текущее время берется из Timer->CNT, 
//  Выставить инкремент в 1мсек из текущей частоты
#define TIM_BRG_TO_1MS 		TIM_BRG_80MHZ_TO_1MS
#define TIM_PSC_TO_1MS 		TIM_PSC_80MHZ_TO_1MS

//	Прерывание каждые 2 секунды на обслуживание таблиц и посылку суперфреймов
#define TIM_PER_1MS						  1
//#define DUPLICALE_AGE_TIME_2S		2000


//	Time after which an entry is removed from the duplicates        400 ms	 
#define HSR_EntryForgetTime 				 	400 * TIM_PER_1MS   
//	How often a node sends an HSR_Supervision frame                 2 000 ms  
#define HSR_LifeCheckInterval 				2000 * TIM_PER_1MS
//	Time after which a node entry is cleared in the NodesTable      60 000 ms  
#define HSR_NodeForgetTime    				60000	* TIM_PER_1MS 	
//  Time after which a node entry is cleared in the ProxyNodeTable  60 000 ms  
#define HSR_ProxyNodeTableForgetTime 	60000 * TIM_PER_1MS
//	Minimum time during which a node that reboots remains silent 		500 ms  
#define HSR_NodeRebootInterval 			 	500 * TIM_PER_1MS

//	Maximum number of entries in the ProxyNodeTable 								512  
#define HSR_NodeTableMaxEntries 					10
//	Maximum number of entries in the ProxyNodeTable 								512  
#define HSR_ProxyNodeTableMaxEntries 			10
//	Number of multicast addresses to be filtered 										16   
#define HSR_MulticastFilterSize 		 			16	

//	Макс. время возвращения суперфрейма - проверка целостности сети, например HSR_EntryForgetTime/2
#define HSR_WaitSuperFrameReturn					200 * TIM_PER_1MS

#endif  //  _MDR_HSRPRP_CONFIG
