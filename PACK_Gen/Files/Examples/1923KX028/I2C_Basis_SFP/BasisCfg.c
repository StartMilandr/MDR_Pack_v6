#include "BasisCfg.h"


const SFP_Info_Item  InfoItems[SFP_INFO_CNT] = {
  //  Standard
  {SFP_ADDR_ID         , SFP_LEN_ID         , "ID"},
  {SFP_ADDR_IDEX       , SFP_LEN_IDEX       , "IDex"},
  {SFP_ADDR_CONNECTOR  , SFP_LEN_CONNECTOR  , "CONN"},
  {SFP_ADDR_TANSCEIVER , SFP_LEN_TANSCEIVER , "TRANS"},
  {SFP_ADDR_ENCODING   , SFP_LEN_ENCODING   , "ENC"},
  {SFP_ADDR_BITRATE    , SFP_LEN_BITRATE    , "BITRATE"},
  {SFP_ADDR_RESERVED_1 , SFP_LEN_RESERVED_1 , "RES_1"},
  {SFP_ADDR_LEN9KM     , SFP_LEN_LEN9KM     , "LEN9KM"},
  {SFP_ADDR_LEN9M      , SFP_LEN_LEN9M      , "LEN9M"},
  {SFP_ADDR_LEN50M     , SFP_LEN_LEN50M     , "LEN50M"},
  {SFP_ADDR_LEN62P5M   , SFP_LEN_LEN62P5M   , "LEN62,5M"},
  {SFP_ADDR_LEN_COPPER , SFP_LEN_COPPER     , "COPPER"},
  {SFP_ADDR_RESERVED_2 , SFP_LEN_RESERVED_2 , "RES_2"},
  {SFP_ADDR_VENDOR_NAME, SFP_LEN_VENDOR_NAME, "VEND_NAME"},
  {SFP_ADDR_RESERVED_3 , SFP_LEN_RESERVED_3 , "RES_3"},
  {SFP_ADDR_VENDOR_OUI , SFP_LEN_VENDOR_OUI , "VEND_OUI"},
  {SFP_ADDR_VENDOR_PN  , SFP_LEN_VENDOR_PN  , "VEND_PN"},
  {SFP_ADDR_VENDOR_REV , SFP_LEN_VENDOR_REV , "VEND_REV"},
  {SFP_ADDR_RESERVED_4 , SFP_LEN_RESERVED_4 , "RES_4"},
  {SFP_ADDR_CC_BASE    , SFP_LEN_CC_BASE    , "CC_BASE"},  
  //  Extended
  {SFP_ADDR_OPTIONS     , SFP_LEN_OPTIONS    , "OPTIONS"},  
  {SFP_ADDR_BITRATE_MAX , SFP_LEN_BITRATE_MAX, "BR_MAX"},  
  {SFP_ADDR_BITRATE_MIN , SFP_LEN_BITRATE_MIN, "BR_MIN"},  
  {SFP_ADDR_VENDOR_SN   , SFP_LEN_VENDOR_SN  , "VEND_SN"},  
  {SFP_ADDR_DATA_CODE   , SFP_LEN_DATA_CODE  , "DATA_CODE"},  
  {SFP_ADDR_RESERVED_5  , SFP_LEN_RESERVED_5 , "RES_5"},  
  {SFP_ADDR_CC_EXT      , SFP_LEN_CC_EXT     , "CC_EXT"}
};


static const uint8_t SFP_toMUX[SFP_COUNT] = {SFP_MUX_X1_1, SFP_MUX_X1_2, SFP_MUX_X8_1, SFP_MUX_X8_2};
  
bool SFP_MuxSetActive(uint8_t selSFP) 
{ 
  uint8_t muxSel = SFP_toMUX[selSFP];
  return MDR_I2C_TransferWrite(I2C_ADDR_MUX, 1, &muxSel) == 1; 
}


void SFP_PresencePinsInit(void)
{
  MDR_CLOCK->PER_CLOCK |= SFP_PRES_PORT_CLK;
  
  SFP_PRES_PORT->ANALOG = SFP_PRES_PIN_ALL;
}

void PhyResetPinsInit(void)
{ 
  MDR_CLOCK->PER_CLOCK |= SHIFT_REG_PORT_CLK;
  
  SHIFT_REG_PORT->PULL   = PIN_PULL_UP(SHIFT_REG_PIN_ALL);  //0xFFE00000;	//Pull up (PB[15:5])
	SHIFT_REG_PORT->ANALOG = SHIFT_REG_PIN_ALL;               //0xFFFF;
	SHIFT_REG_PORT->OE     = SHIFT_REG_PIN_ALL;               //0x07C0;	                                                            //PB6 - BP10 - shift reg
  SHIFT_REG_PORT->PWR    = SHIFT_REG_PIN_PWR(MDR_PIN_MAXFAST);  //0x3FF000;
}  


void vResetPhys( void )
{
    uint8_t ucI;
    uint32_t ulPause;
    
    SHIFT_REG_OE_1;
    SHIFT_REG_IN_0;
    //SHIFT_REG_IN_1;
    
    SHIFT_REG_CLR_0;
    for( ulPause = 100; ulPause > 0; ulPause-- ){}
    SHIFT_REG_CLR_1;
    
    for( ucI = 0; ucI < 17; ucI++ )
    {
        SHIFT_REG_SRCLK_0;
        SHIFT_REG_RCLK_0;
        for( ulPause = 100; ulPause > 0; ulPause-- ){}
        SHIFT_REG_SRCLK_1;
        SHIFT_REG_RCLK_1;
        for( ulPause = 100; ulPause > 0; ulPause-- ){}
    }
    
    SHIFT_REG_OE_0;
    for( ulPause = 100; ulPause > 0; ulPause-- ){}
    SHIFT_REG_OE_1;    
}

