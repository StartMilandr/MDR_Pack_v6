import threading

def ThreadExecText(transfTest):
    transfTest.execute()

class TransfTest():
  # Constructor
  def __init__(self, maxMessLen, sendFunc, onUpdateFunc):
    super().__init__()

    # Status
    self.CyclesCount = 0
    self.SentCount = 0
    self.ReceivedCount = 0
    self.DataError = 0
    self.LenError_LT = 0
    self.LenError_GT = 0
    # Setup Params
    self.onUpdateFunc = onUpdateFunc
    self.stopEvent = threading.Event()
    self.sendFunc = sendFunc
    self.maxMessLen = maxMessLen
    self.LenRepeatCount = 20
    self.echoCmd = 1
    # Buffs
    self.eventRx = threading.Event()
    self.dataTx = []

  def start(self):
    self.CyclesCount = 0
    self.SentCount = 0
    self.ReceivedCount = 0
    self.DataError = 0
    self.LenError_LT = 0
    self.LenError_GT = 0    
    self.stopEvent.clear()
    # Start ReadThread
    self.thread = threading.Thread(target=ThreadExecText, args=(self,))
    self.thread.start()
    
  def stop(self):  
    self.stopEvent.set()
    self.eventRx.set()
    self.thread.join()

  def execute(self):
    while not self.stopEvent.isSet():
      self.SendDataCycle(self.maxMessLen, self.LenRepeatCount)

  def SendDataCycle(self, maxDataLen, lenRepeatCount):
    for dataLen in range(1, maxDataLen):
      self.SendDataLenCycle(dataLen, lenRepeatCount)
      self.onUpdateFunc()
      if self.stopEvent.isSet():
        return
    self.CyclesCount += 1  

  def SendDataLenCycle(self, dataLen, lenRepeatCount):
    print('SendBy {} bytes'.format(dataLen))
    while lenRepeatCount > 0:
      self.NextDataTx_Rx(dataLen)
      lenRepeatCount -= 1
      if self.stopEvent.isSet():
        break

  def NextDataTx_Rx(self, dataLen):
    self.dataTx = [self.echoCmd]
    if dataLen > 1:
      self.dataTx = [x for x in range(1, dataLen)]
    self.dataTx[0] = self.echoCmd
    self.SentCount += dataLen
    #Send Data
    self.eventRx.clear()
    self.sendFunc(self.dataTx)
    while not self.eventRx.isSet():
      self.eventRx.wait(0.05)

  def dataReceived(self, rdData):
    # check Length
    lenErrors = len(self.dataTx) - len(rdData)
    if lenErrors > 0:
      self.LenError_LT += lenErrors
      dataLen = len(rdData)
    elif lenErrors < 0:
      self.LenError_GT += abs(lenErrors)
      dataLen = len(self.dataTx)
    else:
      dataLen = len(rdData)  
    # check Data  
    self.ReceivedCount += len(rdData)
    for i in range(dataLen):
      if self.dataTx[i] != rdData[i]:
        self.DataError += 1
    # clear Event
    self.eventRx.set()

