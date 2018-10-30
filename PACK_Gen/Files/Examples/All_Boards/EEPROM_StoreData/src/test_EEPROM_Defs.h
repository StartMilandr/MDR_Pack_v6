#ifndef _TEST_EEPROM_DEFS_H
#define _TEST_EEPROM_DEFS_H

#include <stdint.h>

typedef void      (*pTestInit_void)(void);
typedef uint32_t  (*pTestFunc_uint)(uint32_t);
typedef char*     (*pTestResultToString_uint)(uint32_t);
typedef char*     (*pTestGetName_void)(void);
   
  
typedef struct {
  pTestInit_void            funcInit;
  pTestFunc_uint            funcTestExec;
  pTestFunc_uint            funcCheckResult;
  pTestResultToString_uint  funcResultToString;
  pTestGetName_void         funcTestName;
} TestInterface;



#endif  //_TEST_EEPROM_DEFS_H

