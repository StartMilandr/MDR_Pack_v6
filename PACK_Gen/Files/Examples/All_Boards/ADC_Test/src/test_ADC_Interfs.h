#ifndef _TEST_ADC_INTERFS_H
#define _TEST_ADC_INTERFS_H

#include <MDR_RST_Clock.h>
#include <MDR_ADC.h>
#include <MDRB_LCD.h>

#include "test_Defs.h"
#include "ADC_cfg.h"


extern TestInterface TI_ADC1_CyclicOneChannel;
extern TestInterface TI_ADC2_CyclicOneChannel;

extern TestInterface TI_ADC1_CyclicSelChannels;
extern TestInterface TI_ADC2_CyclicSelChannels;

extern TestInterface TI_ADC1_ManualOneChannel;
extern TestInterface TI_ADC2_ManualOneChannel;

extern TestInterface TI_ADC1_ManualSelChannels;
extern TestInterface TI_ADC2_ManualSelChannels;

extern TestInterface TI_ADC12_SyncroOneChannel;
extern TestInterface TI_ADC12_SyncroSelChannel;


#endif  //_TEST_ADC_INTERFS_H
