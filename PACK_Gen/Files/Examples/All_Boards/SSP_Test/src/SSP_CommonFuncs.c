#include "SSP_CommonFuncs.h"

#ifdef MDRB_HAS_NO_LCD
  #include <stdio.h>
#endif

uint32_t activeTest = 0;

#ifndef BDR_NO_SLAVE_SSP
uint32_t MasterSlave_TestTransfer(void)
{
  uint16_t dataWR_M = 0;
  uint16_t dataRD_M;
  uint16_t dataWR_S = Cfg_DataMaxValue;
  uint16_t dataRD_S;  
  uint32_t errCount = 0;
  uint32_t i;
   
  Cfg_SSP_Master_CapturePins();
  Cfg_SSP_Slave_CapturePins();
  
  for (i = 0; i < TRANSFER_WORD_COUNT; ++i)
  {
    //  Запись слова в FIFO_TX ведомого SSP, будет отправлено при обмене с мастером.
    //  Функция избыточна для данного случая, т.е. ожидать пока в FIFO_TX будет свободное место не надо.
    //  Обмен происходит по одному слову - в буфере всегда будет место.
    //  Но для проверки отработки флагов используется именно эта функция.
    //  Иначе использовать - MDR_SSPex_WriteData(SSP_SLAVE, dataWR_S);
    MDR_SSPex_WaitAndSendData(SSP_SLAVE, dataWR_S);
    
    //  Обмен данными (Передача-прием в обоих SSP)
    dataRD_M = MDR_SSPex_MasterTransfer(SSP_MASTER, dataWR_M);
    
    //  Вычитывание слова из ведомого
    //  Ожидание флага наличия данных в FIFO_RX необязательно в данном случае.
    //  После окончания трансфера в мастере очевидно, что он выставился и в ведомом.
    dataRD_S = MDR_SSPex_WaitAndReadData(SSP_SLAVE);
    
    if ((dataRD_M != dataWR_S) ||  (dataRD_S != dataWR_M))
      ++errCount;
       
    if (dataWR_M >= Cfg_DataMaxValue)
      dataWR_M = 0;
    else
      dataWR_M += 1;
    if (dataWR_S == 0)
      dataWR_S = Cfg_DataMaxValue;
    else  
      dataWR_S -= 1;
  }
  Cfg_SSP_Slave_ReleasePins();
  Cfg_SSP_Master_ReleasePins();
  
  return errCount;
}
#endif

uint32_t MasterTXRX_TestTransfer(const MDR_SSP_TypeEx *exSSPx)
{
  uint16_t dataWR = 0;
  uint16_t dataRD = 0;
  uint32_t errCount = 0;
   
  while (1)
  {
    dataRD = MDR_SSPex_MasterTransfer(exSSPx, dataWR);
    if (dataRD != dataWR)   
      ++errCount;
    
    if (dataWR == Cfg_DataMaxValue)
      break;
    
    dataWR += 1;
  }  
  return errCount;
}


#ifndef MDRB_HAS_NO_LCD

  static char message[64];

  void LCD_ShowInit(const MDR_SSP_TypeEx *exSSPx, char *testName)
  {
    MDRB_LCD_CapturePins();
    
  #ifndef LCD_IS_7SEG_DISPLAY  
    MDRB_LCD_Clear();
    
    sprintf(message , "%s B:%d", testName, cfgSSP.DataBits + 1);
    MDRB_LCD_Print (message, LCD_LINE_NAME);
    
    sprintf(message , "%s%d M:%d D:%d", Cfg_getActiveFrameName(), Cfg_GetIndexSPI(exSSPx), cfgSSP.SPI_Mode, cfgSSP.DivPSR_2_254);
    MDRB_LCD_Print (message, LCD_LINE_INIT);  
  #else
    UNUSED(exSSPx);
    UNUSED(testName);
    
    sprintf(message , "C%d", activeTest);
    MDRB_LCD_Print (message);
  #endif
    
    MDRB_LCD_ReleasePins();
    
  }

  void LCD_ShowStarted(void)
  {
    MDRB_LCD_CapturePins();
    
  #ifndef LCD_IS_7SEG_DISPLAY  
    
    sprintf(message , "Started...");
    MDRB_LCD_Print (message, LCD_LINE_RESULT);
  #else
    sprintf(message , "C ");
    MDRB_LCD_Print (message);
  #endif
    
    MDRB_LCD_ReleasePins();
  }

  void LCD_ShowResult(uint32_t errCount)
  {  
    MDRB_LCD_CapturePins();
    
  #ifndef LCD_IS_7SEG_DISPLAY  
    if (errCount == 0) {   
      sprintf(message , "Success Transfer");
      MDRB_LCD_Print (message, LCD_LINE_RESULT);
    }
    else {   
      sprintf(message , "cntErr=%d", errCount);
      MDRB_LCD_Print (message, LCD_LINE_RESULT);
    }

  #else
    sprintf(message , "C%d E%d ", activeTest, errCount);
    MDRB_LCD_Print (message);  
  #endif
    
    MDRB_LCD_ReleasePins();
  }

#else

  void LCD_ShowInit(const MDR_SSP_TypeEx *exSSPx, char *testName)
  {
    printf("%s B:%d\n", testName, cfgSSP.DataBits + 1);    
    printf("%s%d M:%d D:%d\n", Cfg_getActiveFrameName(), Cfg_GetIndexSPI(exSSPx), cfgSSP.SPI_Mode, cfgSSP.DivPSR_2_254);
  }

  void LCD_ShowStarted(void)
  {
    printf("Started...\n");
  }

  void LCD_ShowResult(uint32_t errCount)
  {
    if (errCount == 0)
      printf("Success Transfer\n");
    else
      printf("cntErr=%d\n", errCount);    
  }

#endif 
