#ifndef MDR_FUNCS_H
#define MDR_FUNCS_H

#include <MDR_Types.h>

typedef bool (*pBoolFunc_U32)(uint32_t);
typedef bool (*pBoolFunc_void)(void);

bool WaitCondition(uint32_t timeoutCycles, pBoolFunc_void checkFunc);

#define REG32(x) (*((volatile uint32_t *)(x)))

#define VAL2FLD(value, field)      _VAL2FLD(field, value)
#define FLD_CLEAR(value, mask)     ((uint32_t)(value) & (~(mask)))

#endif // MDR_FUNCS_H

