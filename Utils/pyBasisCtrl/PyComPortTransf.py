import serial
import time
import struct
from ctypes import create_string_buffer

class ByteDataBuff():
  def __init__(self, buffLen):
    super().__init__()
    self.data = create_string_buffer(buffLen)
    self.dataLen = 0

class ComPortTransf():
  # Constructor
  def __init__(self):
    super().__init__()

    # Vars
    self.comPort = None
    self.started = False
    # COM port settings
    self.port = 'COM16'
    self.baud = 115200
    self.timeoutRx = 0.5
    self.maxMessageLen = 1024

  def start(self):
    try:
      self.comPort = serial.Serial(port=self.port, baudrate=self.baud, timeout=self.timeoutRx)
      if self.comPort.is_open:
        self.started = True
    except Exception as e:
      print(e)

  def stop(self):
    if self.started:
      self.comPort.close()      
      self.started = False

  def send(self, byteBuffTx):
    if self.started:
      self.comPort.write(byteBuffTx)
      print('send {} bytes'.format(len(byteBuffTx)))

  def read(self, byteDataBuff):
    if self.started:
      byteDataBuff.data = self.comPort.read(self.maxMessageLen)
      byteDataBuff.dataLen = len(byteDataBuff.data)
    else:
      byteDataBuff.dataLen = 0
    return byteDataBuff

  def transfer(self, byteBuffTx, byteDataBuffRx):
    if self.started:
      self.comPort.write(byteBuffTx)
      #print('Send {} bytes'.format(len(byteBuffTx)))

      byteDataBuffRx.data = self.comPort.read(self.maxMessageLen)
      byteDataBuffRx.dataLen = len(byteDataBuffRx.data)
      #print('Received {} bytes'.format(byteDataBuffRx.dataLen))
      return byteDataBuffRx.dataLen
    else:
      return 0  
