import serial
import threading
import time

selProtNone   = 0
selProtDouble = 1
selProtHdrLen = 2

def ThreadReadPort(ComPortThreadInst):
    while ComPortThreadInst.started:
      ComPortThreadInst.comReadData()

def IsEvenNum(num):
  return (num & 1) != 1

class ComPortThread():
  # Constructor
  def __init__(self, receiveDataFunc):
    super().__init__()  

    # Vars
    self.comPort = None
    self.started = False
    self.onReceiveFunc = receiveDataFunc
    # COM port settings
    self.port = 'COM15'
    self.baud = 115200
    self.timeoutRx = 0.2
    self.maxMessageLen = 1024
    self.selProtocol = selProtNone
    self.checkHash = True

  def start(self):
    try:
      self.comPort = serial.Serial(port=self.port, baudrate=self.baud, timeout=self.timeoutRx)
      if self.comPort.is_open:
        self.started = True
        # Start ReadThread
        self.thread = threading.Thread(target=ThreadReadPort, args=(self,))
        self.thread.start()
    except Exception as e:
      print(e)

  def stop(self):
    if self.started:
      # Stop ReadThread
      self.started = False
      self.thread.join()
      self.comPort.close()

  def send(self, data):
    if self.started:
      arr = bytearray(data)
      if self.selProtocol == selProtDouble:
        arr = self.toDoubleProtocol(arr)
      elif self.selProtocol == selProtHdrLen:
        arr = self.toHdrLenProtocol(arr)
        # for d in arr:
        #   print(str(d))  
      self.comPort.write(arr)

  def comReadData(self):
    if self.started:
      rdData = self.comPort.read(self.maxMessageLen)
      if len(rdData) > 0:
        if self.selProtocol == selProtDouble:
          rdData = self.fromDoubleProtocol(rdData)
        elif self.selProtocol == selProtHdrLen:
          rdData = self.fromHdrLenProtocol(rdData)  
        self.onReceiveFunc(rdData)

  def setProtocol(self, protID):
    self.selProtocol = protID
    if self.selProtocol == selProtNone:
      print('NoProtocol set')
    elif self.selProtocol == selProtDouble:      
      print('DoubleProtocol set')      
    elif self.selProtocol == selProtHdrLen:      
      print('HdrLenProtocol set')
    else:
      print('WrongProtocol set!')

  # Header16: len[10], cmd[6], data...
  # Len = 0..1023, cmdCnt = 0..63
  # Len - in length of dataTx, exclude OddTail byte
  def toHdrLenProtocol(self, dataTx):
    result = dataTx
    cnt = len(dataTx) + 1
    result.insert(0, cnt & 0xFF)
    result[1] |= (cnt >> 2) & 0xC0
    # Make Len Odd - if needed
    if IsEvenNum(len(result)):
      result.append(0)
    return result


  def fromHdrLenProtocol(self, dataRx):
    # for d in dataRx:
    #     print(str(d))
    result = []    
    dataLen = len(dataRx)
    if dataLen < 3:
      print('Mess Too Small: {}'.format(dataLen))
      for i in range(0, dataLen):
        result.append(dataRx[i])
    else:
      messLen = dataRx[0] | ((dataRx[1] & 0xC0) << 2)
      if IsEvenNum(messLen):
        protocolOk = dataLen == messLen + 1
      else:
        protocolOk = dataLen
      if protocolOk:
        # print('MessLen = {}'.format(messLen))
        for i in range(1, messLen):
          result.append(dataRx[i])
        result[0] &= 0x3F
      else:
        for i in range(0, dataLen):
          result.append(dataRx[i])
      #Exit    
      return result


  def toDoubleProtocol(self, dataTx):
    result = []
    shash = 0 & 0xFF
    for d in dataTx:
      result.append(d)
      result.append(~d & 0xFF)
      shash ^= d & 0xFF
    result.append(shash)
    #print('DoubleTx')
    return result  

  def fromDoubleProtocol(self, dataRx):
    #print('DoubleRx')
    result = []
    resultOk = False
    dataCnt = len(dataRx)
    i = 0
    shash = 0
    if dataCnt >= 3:                 # min bytes count in transfer
      while dataCnt > 0:
        if dataCnt > 1:
          val1 = dataRx[i]
          val2 = dataRx[i + 1]
          i += 2
          if val1 == (~val2 & 0xFF):
            result.append(val1)
            shash ^= val1
          else:                     #protocol error - return as is  
            break
        elif dataCnt == 1:          #last word - hash
          if self.checkHash:
            resultOk = shash == dataRx[i]
          else:
            resultOk = True  
          break

        dataCnt -= 2  
    #return
    if resultOk:  
      return result
    else:
      return dataRx


