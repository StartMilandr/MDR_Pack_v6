#ifndef _TEST_DEFS_H
#define _TEST_DEFS_H

#include <stdint.h>

typedef void  (*pTestFunc_void)(void);
  
  
typedef struct {
  pTestFunc_void            funcInit;
  pTestFunc_void            funcFinit;
  pTestFunc_void            funcChange;
  pTestFunc_void            funcExec;
  pTestFunc_void            funcMainLoop;
  pTestFunc_void            funcHandlerTim1;
  pTestFunc_void            funcHandlerTim2;
  pTestFunc_void            funcHandlerTim3;
  pTestFunc_void            funcHandlerTim4;
} TestInterface;



#endif  //_TEST_DEFS_H

