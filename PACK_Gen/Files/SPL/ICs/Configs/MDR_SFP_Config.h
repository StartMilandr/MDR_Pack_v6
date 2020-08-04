#ifndef MDR_SFP_CONFIG_H
#define MDR_SFP_CONFIG_H


#define I2C_ADDR_SFR          0x50

//  BASE ID Fields
#define SFP_ADDR_ID           0
#define SFP_ADDR_IDEX         1
#define SFP_ADDR_CONNECTOR    2
#define SFP_ADDR_TANSCEIVER   3
#define SFP_ADDR_ENCODING     11
#define SFP_ADDR_BITRATE      12
#define SFP_ADDR_RESERVED_1   13
#define SFP_ADDR_LEN9KM       14
#define SFP_ADDR_LEN9M        15
#define SFP_ADDR_LEN50M       16
#define SFP_ADDR_LEN62P5M     17
#define SFP_ADDR_LEN_COPPER   18
#define SFP_ADDR_RESERVED_2   19
#define SFP_ADDR_VENDOR_NAME  20
#define SFP_ADDR_RESERVED_3   36
#define SFP_ADDR_VENDOR_OUI   37
#define SFP_ADDR_VENDOR_PN    40
#define SFP_ADDR_VENDOR_REV   56
#define SFP_ADDR_RESERVED_4   60
#define SFP_ADDR_CC_BASE      63

#define SFP_LEN_ID            1
#define SFP_LEN_IDEX          1
#define SFP_LEN_CONNECTOR     1
#define SFP_LEN_TANSCEIVER    8
#define SFP_LEN_ENCODING      1
#define SFP_LEN_BITRATE       1
#define SFP_LEN_RESERVED_1    1
#define SFP_LEN_LEN9KM        1
#define SFP_LEN_LEN9M         1
#define SFP_LEN_LEN50M        1
#define SFP_LEN_LEN62P5M      1
#define SFP_LEN_COPPER        1
#define SFP_LEN_RESERVED_2    1
#define SFP_LEN_VENDOR_NAME   16
#define SFP_LEN_RESERVED_3    1
#define SFP_LEN_VENDOR_OUI    3
#define SFP_LEN_VENDOR_PN     16
#define SFP_LEN_VENDOR_REV    4
#define SFP_LEN_RESERVED_4    3
#define SFP_LEN_CC_BASE       1

//  Extended ID Fields
#define SFP_ADDR_OPTIONS      64
#define SFP_ADDR_BITRATE_MAX  66
#define SFP_ADDR_BITRATE_MIN  67
#define SFP_ADDR_VENDOR_SN    68
#define SFP_ADDR_DATA_CODE    84
#define SFP_ADDR_RESERVED_5   92
#define SFP_ADDR_CC_EXT       95

#define SFP_LEN_OPTIONS       2
#define SFP_LEN_BITRATE_MAX   1
#define SFP_LEN_BITRATE_MIN   1
#define SFP_LEN_VENDOR_SN     16
#define SFP_LEN_DATA_CODE     8
#define SFP_LEN_RESERVED_5    3
#define SFP_LEN_CC_EXT        1

//  VENDOR SPECIFIC
#define SFP_ADDR_VENDOR_SPECIF_RO      96
#define SFP_LEN_VENDOR_SPECIF_RO       32


#define SFP_ITEM_LEN_MAX      16

//  Выбор какую информацию читать из SFP
#define CFG_SFP_ITEMS {  \
  /*  Standard  */    \
  {SFP_ADDR_ID         , SFP_LEN_ID         , "ID"},         \
  {SFP_ADDR_IDEX       , SFP_LEN_IDEX       , "IDex"},       \
  {SFP_ADDR_CONNECTOR  , SFP_LEN_CONNECTOR  , "CONN"},       \
  {SFP_ADDR_TANSCEIVER , SFP_LEN_TANSCEIVER , "TRANS"},      \
  {SFP_ADDR_ENCODING   , SFP_LEN_ENCODING   , "ENC"},        \
  {SFP_ADDR_BITRATE    , SFP_LEN_BITRATE    , "BITRATE"},    \
  {SFP_ADDR_RESERVED_1 , SFP_LEN_RESERVED_1 , "RES_1"},      \
  {SFP_ADDR_LEN9KM     , SFP_LEN_LEN9KM     , "LEN9KM"},     \
  {SFP_ADDR_LEN9M      , SFP_LEN_LEN9M      , "LEN9M"},      \
  {SFP_ADDR_LEN50M     , SFP_LEN_LEN50M     , "LEN50M"},     \
  {SFP_ADDR_LEN62P5M   , SFP_LEN_LEN62P5M   , "LEN62,5M"},   \
  {SFP_ADDR_LEN_COPPER , SFP_LEN_COPPER     , "COPPER"},     \
  {SFP_ADDR_RESERVED_2 , SFP_LEN_RESERVED_2 , "RES_2"},      \
  {SFP_ADDR_VENDOR_NAME, SFP_LEN_VENDOR_NAME, "VEND_NAME"},  \
  {SFP_ADDR_RESERVED_3 , SFP_LEN_RESERVED_3 , "RES_3"},      \
  {SFP_ADDR_VENDOR_OUI , SFP_LEN_VENDOR_OUI , "VEND_OUI"},   \
  {SFP_ADDR_VENDOR_PN  , SFP_LEN_VENDOR_PN  , "VEND_PN"},    \
  {SFP_ADDR_VENDOR_REV , SFP_LEN_VENDOR_REV , "VEND_REV"},   \
  {SFP_ADDR_RESERVED_4 , SFP_LEN_RESERVED_4 , "RES_4"},      \
  {SFP_ADDR_CC_BASE    , SFP_LEN_CC_BASE    , "CC_BASE"},    \
  /*  Extended  */    \
  {SFP_ADDR_OPTIONS     , SFP_LEN_OPTIONS    , "OPTIONS"},   \
  {SFP_ADDR_BITRATE_MAX , SFP_LEN_BITRATE_MAX, "BR_MAX"},    \
  {SFP_ADDR_BITRATE_MIN , SFP_LEN_BITRATE_MIN, "BR_MIN"},    \
  {SFP_ADDR_VENDOR_SN   , SFP_LEN_VENDOR_SN  , "VEND_SN"},   \
  {SFP_ADDR_DATA_CODE   , SFP_LEN_DATA_CODE  , "DATA_CODE"}, \
  {SFP_ADDR_RESERVED_5  , SFP_LEN_RESERVED_5 , "RES_5"},     \
  {SFP_ADDR_CC_EXT      , SFP_LEN_CC_EXT     , "CC_EXT"}     \
}      \

#define  CFG_SFP_ITEMS_CNT    27

#define CFG_SFP_ITEMS_TABLE_LEN   SFP_ITEM_LEN_MAX * CFG_SFP_ITEMS_CNT


#endif  //MDR_SFP_CONFIG_H
