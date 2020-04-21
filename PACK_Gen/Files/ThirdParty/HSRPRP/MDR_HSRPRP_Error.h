#ifndef _MDR_HSR_ERROR_H
#define _MDR_HSR_ERROR_H

#include <stdint.h>

typedef enum {
  MDR_HSR_Err_None        = 0,
  MDR_HSR_Err_OverItemsTX,
  
  MDR_HSR_Err_WrongLanID,
  //lreCntWrongLanIdC
  
  MDR_HSR_Err_RxNoFreeFrameItem,
	MDR_HSR_Err_TxNoFreeFrameItem,
	
	//	My errors
	MDR_HSR_Err_UnkFrameSrc_DANH,
	MDR_HSR_Err_UnkFrameSrc_RedBox,
  
} MDR_HSR_ErrorID;

void MDR_HSR_LogError(MDR_HSR_ErrorID errID, uint32_t tag);


#endif  //  _MDR_HSR_ERROR_H
