import serial
import threading
import time
import struct
import os
from ctypes import create_string_buffer


def UnbrickProcess(ComPortThreadInst):
    ComPortThreadInst.performUnbrick()    

def IsEvenNum(num):
  return (num & 1) != 1

class ComPortThread():
  # Constructor
  def __init__(self, showLog, binFileName):
    super().__init__()  

    # Vars
    self.comPort = None
    self.started = False
    self.threadStarted = False
    self.doThreadStop  = False
    self.syncCountMax = 10000
    self.memStartAddr = 0x20001000
    self.binFileName = binFileName
    self.onShowLog = showLog
    # COM port settings
    self.port = 'COM15'
    self.baud = 9600
    self.timeoutRx = 0.2

  def start(self):
    try:
      self.comPort = serial.Serial(port=self.port, baudrate=self.baud, timeout=0)
      if self.comPort.is_open:
        self.started = True
    except Exception as e:
      print(e)

  def stop(self):
    if self.started:
      # Stop ReadThread
      self.started = False
      if self.thread != None:
        self.doThreadStop = True
        self.thread.join()
      self.comPort.close()

  def RunUnbrick(self):
    if self.started:
      if not self.threadStarted:
        self.threadStarted = True
        self.doThreadStop  = False
        self.thread = threading.Thread(target=UnbrickProcess, args=(self,))
        self.thread.start()
      else:
        self.doThreadStop = True

    else:
      self.onShowLog('Open COM port first!')    

  def checkCR(self):
    self.comPort.timeout = self.timeoutRx
    self.comPort.write(bytearray([13]))
    rdData = self.comPort.read(3)
    self.DbgPrintList(rdData)
    # receive 13 10 62
    result = (len(rdData) == 3) and (rdData[2] == ord('>'))
    if result:
      self.onShowLog('ACK received!')
    else:
      self.onShowLog('No ACK!')  
    return result

  def sendSync(self, maxCount):
    self.comPort.timeout = 0    
    cnt = 0
    self.onShowLog('Sync started...')
    while True:
      self.comPort.write(bytearray([0]))
      rdData = self.comPort.read(1)
      if (len(rdData) > 0 and rdData[0] == ord('>')):
        self.comPort.timeout = self.timeoutRx
        self.onShowLog('Sync OK! (SentCount: {})'.format(cnt))
        return True

      cnt += 1
      if cnt == maxCount:
        self.onShowLog('Sync Fault: SentCount: {}, Received: {}'.format(maxCount, len(rdData)))  
        return False

      if self.doThreadStop:
        self.onShowLog('Sync Stopped') 
        return False

  def DbgPrintList(self, arr):
    if len(arr) > 0:
      for d in arr:
        print(chr(d))        


  def performUnbrick(self):
    # Clear Rx
    self.comPort.flushInput()

    # Sync Connect
    canLoad = self.checkCR()
    if not canLoad:
      if self.sendSync(self.syncCountMax):
        canLoad = self.checkCR()
    
    if canLoad:
      self.onShowLog('Load Init')
      # Init Mem for Load
      buffTx = create_string_buffer(9)
      struct.pack_into("B", buffTx, 0, ord('L'))
      filesize = os.path.getsize(self.binFileName)
      struct.pack_into("<LL", buffTx, 1, self.memStartAddr, filesize)
      self.comPort.write(buffTx)
      #check ACK
      rdData = self.comPort.read(1)
      ackOk = (len(rdData) == 1) and (rdData[0] == ord('L'))
      self.DbgPrintList(rdData)
      #Load File
      if ackOk:
        self.onShowLog('Load File...')        
        # Load File
        binary_file = open(self.binFileName, 'rb')
        for i in range(filesize):
          self.comPort.write(binary_file.read(1))
        binary_file.close()

        #  Check Load Ack
        rdData = self.comPort.read(1)
        self.DbgPrintList(rdData)
        if (len(rdData) == 1) and (rdData[0] == ord('K')):
          self.onShowLog('Load File Completed')
          # Run File
          buffTx = create_string_buffer(5)
          struct.pack_into("B", buffTx, 0, ord('R'))
          struct.pack_into("L", buffTx, 1, self.memStartAddr)
          self.comPort.write(buffTx)
          #check ACK
          rdData = self.comPort.read(1)
          ackOk = (len(rdData) == 1) and (rdData[0] == ord('R'))
          self.DbgPrintList(rdData)
          if ackOk:
            self.onShowLog('Application started')
          else:
            self.onShowLog('Fault: No Run ACK!') 
        else:
          self.onShowLog('Fault: No Load ACK!')
      else:
        self.onShowLog('Fault: No LoadInit ACK!') 
        
    self.thread = None
    self.threadStarted = False



