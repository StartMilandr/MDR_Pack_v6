import configparser
from PyComPortConfigKeys import *


class ComPortConfigs():
  # Constructor
  def __init__(self, iniFileName):
    super().__init__()
    self.config = configparser.ConfigParser()

    if not self.tryLoadSettings(iniFileName):
      self.createSettingsDefault(iniFileName)

  def tryLoadSettings(self, fileName):
    result = False
    try:
      # with open(fileName, 'r') as configfile:
      #   self.config.read(configfile)
      #result = True

      self.config.read(fileName)  
      result = sLastSettings in self.config

    except Exception as e:
      print(e)
      print('exception!')
    return result  


  def createSettingsDefault(self, fileName):
    # Active settings
    self.config[sLastSettings] = {sPort: 'COM15', sBaud: '115200', sTimeoutRx: '0.2'}
    self.config[sBaudList] = {sRates: '115200 57600 38400 19200 9600'}
    with open(fileName, 'w') as configfile:
      self.config.write(configfile)


  def saveToFile(self, fileName):
    #self.config[sBaudList] = {sRates: {'9600', '19200', '38400', '57600', '115200'}}
    with open(fileName, 'w') as configfile:
      self.config.write(configfile)


