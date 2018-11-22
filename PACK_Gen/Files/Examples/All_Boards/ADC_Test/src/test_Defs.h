#ifndef _TEST_DEFS_H
#define _TEST_DEFS_H

#include <stdint.h>

typedef void      (*pTestFunc_void)(void);
  
  
typedef struct {
  pTestFunc_void            funcInit;
  pTestFunc_void            funcFinit;
  pTestFunc_void            funcChange;
  pTestFunc_void            funcExec;
  pTestFunc_void            funcHandlerIrq;
} TestInterface;



#endif  //_TEST_DEFS_H

