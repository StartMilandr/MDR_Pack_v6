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