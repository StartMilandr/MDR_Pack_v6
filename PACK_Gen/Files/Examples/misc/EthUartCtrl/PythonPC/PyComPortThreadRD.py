import serial
import threading
import time
import struct
from ctypes import create_string_buffer

selProtNone   = 0
selProtDouble = 1
selProtHdrLen = 2

CMR_RD_MAC   = 0
CMR_WR_MAC   = 1
CMR_RD_PHY   = 2
CMR_WR_PHY   = 3
CMR_RD_INFO  = 4
CMR_RD_FRAME = 5

def ThreadReadPort(ComPortThreadInst):
    while ComPortThreadInst.started:
      ComPortThreadInst.comReadData()

def IsEvenNum(num):
  return (num & 1) != 1

class ComPortThreadRD():
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
      self.comPort.write(data)

  def comReadData(self):
    if self.started:
      rdData = self.comPort.read(self.maxMessageLen)
      if len(rdData) > 0:
        self.onReceiveFunc(rdData)

  def SendCmdReadMAC(self, regAddr):
    if self.started:    
      buffTx = create_string_buffer(3)
      # struct.pack_into("BH", buffTx, 0, CMR_RD_MAC, regAddr)
      struct.pack_into("B", buffTx, 0, CMR_RD_MAC)
      struct.pack_into("H", buffTx, 1, regAddr)
      self.comPort.write(buffTx)

  def SendCmdReadPHY(self, regAddr):
    if self.started:    
      buffTx = create_string_buffer(3)
      struct.pack_into("B", buffTx, 0, CMR_RD_PHY)
      struct.pack_into("H", buffTx, 1, regAddr)
      self.comPort.write(buffTx)

  def SendCmdWriteMAC(self, regAddr, value):
    if self.started:    
      buffTx = create_string_buffer(5)
      struct.pack_into("B", buffTx, 0, CMR_WR_MAC)
      struct.pack_into("HH", buffTx, 1, regAddr, value)
      #struct.pack_into("BHH", buffTx, 0, CMR_WR_MAC, regAddr, value)
      self.comPort.write(buffTx)

  def SendCmdWritePHY(self, regAddr, value):
    if self.started:    
      buffTx = create_string_buffer(5)
      struct.pack_into("B", buffTx, 0, CMR_WR_PHY)
      struct.pack_into("HH", buffTx, 1, regAddr, value)
      #struct.pack_into("BHH", buffTx, 0, CMR_WR_PHY, regAddr, value)
      self.comPort.write(buffTx)  

  def SendCmdReadInfo(self):
    if self.started:    
      buffTx = create_string_buffer(1)
      struct.pack_into("B", buffTx, 0, CMR_RD_INFO)
      self.comPort.write(buffTx) 

  def SendCmdReadFrame(self):
    if self.started:    
      buffTx = create_string_buffer(1)
      struct.pack_into("B", buffTx, 0, CMR_RD_FRAME)
      self.comPort.write(buffTx)  

