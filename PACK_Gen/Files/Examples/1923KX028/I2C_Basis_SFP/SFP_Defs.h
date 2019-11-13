#ifndef SFP_DEFS
#define SFP_DEFS


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


#define SFP_LEN_MAX         16



#endif  //SFP_DEFS
