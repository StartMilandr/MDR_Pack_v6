ACT_ACTIIONS = ['ACT_FORWARD', 'ACT_FLOOD', 'ACT_PUNT', 'ACT_DISCARD', 'ACT_OVERRIDE', 'ACT_FWD_MASK', 'ACT_COS_DISCARD']
sAPPLY_BTN_TEXT = 'Write To Device'
PORTS = [1, 2, 3, 4]

TEXT_BTN_READ  = 'Read'
TEXT_BTN_WRITE = 'Write'
TEXT_LINK_DOWN = 'Down'

SHUT_DOWN_ITEMS = ['PowerOff', 'PowerOn']
AFT_ITEMS = ['AnyTagged', 'Tagged', 'Untagged']
BLOCKSTATE_ITEMS = ['Forwarding', 'Blocked', 'LearnOnly']

TABLE_ITEM_HEIGHT = 20

_PortNames = []
def BasisGetPortNames():
  if len(_PortNames) != len(PORTS):
    _PortNames.clear()
    for d in PORTS:
      _PortNames.append('Port {}'.format(d))

  return _PortNames


def _VAL2FLD(value, valPos, ValMsk):
  return (value << valPos) & ValMsk

def _FLD2VAL(value, valPos, ValMsk):
  return (value & ValMsk) >> valPos


'''
#--- for EMac DefConfig ---
PORT0_STRUC1  = 0x46c 
PORT1_STRUC1  = 0x474 
PORT2_STRUC1  = 0x47c
PORT3_STRUC1  = 0x484
PORT4_STRUC1  = 0x48c
PORT5_STRUC1  = 0x494
PORT6_STRUC1  = 0x49c
PORT7_STRUC1  = 0x4a4
PORT8_STRUC1  = 0x548
PORT9_STRUC1  = 0x550
PORT10_STRUC1 = 0x558
PORT11_STRUC1 = 0x560
PORT12_STRUC1 = 0x568
PORT13_STRUC1 = 0x570
PORT14_STRUC1 = 0x578
PORT15_STRUC1 = 0x580
PORT16_STRUC1 = 0x588

PORT0_STRUC2  = 0x470 
PORT1_STRUC2  = 0x478
PORT2_STRUC2  = 0x480
PORT3_STRUC2  = 0x488
PORT4_STRUC2  = 0x490
PORT5_STRUC2  = 0x498
PORT6_STRUC2  = 0x4a0
PORT7_STRUC2  = 0x4a8
PORT8_STRUC2  = 0x54c
PORT9_STRUC2  = 0x554
PORT10_STRUC2 = 0x55c
PORT11_STRUC2 = 0x564
PORT12_STRUC2 = 0x56c
PORT13_STRUC2 = 0x574
PORT14_STRUC2 = 0x57c
PORT15_STRUC2 = 0x584
PORT16_STRUC2 = 0x58c

CLASS1_BASE_ADDR = 0x620000
CLASS2_BASE_ADDR = 0x770000
'''

#---  for EMAC Status ---
EMAC_NETSTAT		        = 0x0008 
EMAC_NETSTAT_LINK_Msk	  = 0x0001

EMAC1_BASE_ADDR  = 0x660000
EMAC2_BASE_ADDR  = 0x670000
EMAC3_BASE_ADDR  = 0x680000
EMAC4_BASE_ADDR  = 0x690000
EMAC5_BASE_ADDR  = 0x6A0000
EMAC6_BASE_ADDR  = 0x6B0000
EMAC7_BASE_ADDR  = 0x6C0000
EMAC8_BASE_ADDR  = 0x6D0000
EMAC9_BASE_ADDR  = 0x6E0000
EMAC10_BASE_ADDR = 0x6F0000
EMAC11_BASE_ADDR = 0x760000
EMAC12_BASE_ADDR = 0x710000
EMAC13_BASE_ADDR = 0x720000
EMAC14_BASE_ADDR = 0x730000
EMAC15_BASE_ADDR = 0x740000
EMAC16_BASE_ADDR = 0x750000

kx028_EmacAdr = [EMAC1_BASE_ADDR,  EMAC2_BASE_ADDR,  EMAC3_BASE_ADDR,  EMAC4_BASE_ADDR,  EMAC5_BASE_ADDR, \
                 EMAC6_BASE_ADDR,  EMAC7_BASE_ADDR,  EMAC8_BASE_ADDR,  EMAC9_BASE_ADDR,  EMAC10_BASE_ADDR, \
                 EMAC11_BASE_ADDR, EMAC12_BASE_ADDR, EMAC13_BASE_ADDR, EMAC14_BASE_ADDR, EMAC15_BASE_ADDR, \
                 EMAC16_BASE_ADDR]

#--- for EMac DefConfig ---
PORT0_STRUC1  = 0 
PORT1_STRUC1  = 1 
PORT2_STRUC1  = 2
PORT3_STRUC1  = 3
PORT4_STRUC1  = 4
PORT5_STRUC1  = 5
PORT6_STRUC1  = 6
PORT7_STRUC1  = 7
PORT8_STRUC1  = 8
PORT9_STRUC1  = 9
PORT10_STRUC1 = 10
PORT11_STRUC1 = 11
PORT12_STRUC1 = 12
PORT13_STRUC1 = 13
PORT14_STRUC1 = 14
PORT15_STRUC1 = 15
PORT16_STRUC1 = 16

PORT0_STRUC2  = 17
PORT1_STRUC2  = 18
PORT2_STRUC2  = 19
PORT3_STRUC2  = 20
PORT4_STRUC2  = 21
PORT5_STRUC2  = 22
PORT6_STRUC2  = 23
PORT7_STRUC2  = 24
PORT8_STRUC2  = 25
PORT9_STRUC2  = 26
PORT10_STRUC2 = 27
PORT11_STRUC2 = 28
PORT12_STRUC2 = 29
PORT13_STRUC2 = 30
PORT14_STRUC2 = 31
PORT15_STRUC2 = 32
PORT16_STRUC2 = 33

CLASS1_BASE_ADDR = 0
CLASS2_BASE_ADDR = 0

kx028_AddrStruc1 = [PORT0_STRUC1,  PORT1_STRUC1,  PORT2_STRUC1,  PORT3_STRUC1,  PORT4_STRUC1, \
                    PORT5_STRUC1,  PORT6_STRUC1,  PORT7_STRUC1,  PORT8_STRUC1,  PORT9_STRUC1, \
                    PORT10_STRUC1, PORT11_STRUC1, PORT12_STRUC1, PORT13_STRUC1, PORT14_STRUC1, \
                    PORT15_STRUC1, PORT16_STRUC1]

kx028_AddrStruc2 = [PORT0_STRUC2,  PORT1_STRUC2,  PORT2_STRUC2,  PORT3_STRUC2,  PORT4_STRUC2, \
                    PORT5_STRUC2,  PORT6_STRUC2,  PORT7_STRUC2,  PORT8_STRUC2,  PORT9_STRUC2, \
                    PORT10_STRUC2, PORT11_STRUC2, PORT12_STRUC2, PORT13_STRUC2, PORT14_STRUC2, \
                    PORT15_STRUC2, PORT16_STRUC2]
                    