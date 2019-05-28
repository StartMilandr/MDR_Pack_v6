#ifndef _MDR_GPIO_VE8x_H
#define _MDR_GPIO_VE8x_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>


#define MDR_Pin_0                  0x00000001UL  /*!< Pin 0 selected */
#define MDR_Pin_1                  0x00000002UL  /*!< Pin 1 selected */
#define MDR_Pin_2                  0x00000004UL  /*!< Pin 2 selected */
#define MDR_Pin_3                  0x00000008UL  /*!< Pin 3 selected */
#define MDR_Pin_4                  0x00000010UL  /*!< Pin 4 selected */
#define MDR_Pin_5                  0x00000020UL  /*!< Pin 5 selected */
#define MDR_Pin_6                  0x00000040UL  /*!< Pin 6 selected */
#define MDR_Pin_7                  0x00000080UL  /*!< Pin 7 selected */
#define MDR_Pin_8                  0x00000100UL  /*!< Pin 8 selected */
#define MDR_Pin_9                  0x00000200UL  /*!< Pin 9 selected */
#define MDR_Pin_10                 0x00000400UL  /*!< Pin 10 selected */
#define MDR_Pin_11                 0x00000800UL  /*!< Pin 11 selected */
#define MDR_Pin_12                 0x00001000UL  /*!< Pin 12 selected */
#define MDR_Pin_13                 0x00002000UL  /*!< Pin 13 selected */
#define MDR_Pin_14                 0x00004000UL  /*!< Pin 14 selected */
#define MDR_Pin_15                 0x00008000UL  /*!< Pin 15 selected */
#define MDR_Pin_16                 0x00010000UL  /*!< Pin 16 selected */
#define MDR_Pin_17                 0x00020000UL  /*!< Pin 17 selected */
#define MDR_Pin_18                 0x00040000UL  /*!< Pin 18 selected */
#define MDR_Pin_19                 0x00080000UL  /*!< Pin 19 selected */
#define MDR_Pin_20                 0x00100000UL  /*!< Pin 20 selected */
#define MDR_Pin_21                 0x00200000UL  /*!< Pin 21 selected */
#define MDR_Pin_22                 0x00400000UL  /*!< Pin 22 selected */
#define MDR_Pin_23                 0x00800000UL  /*!< Pin 23 selected */
#define MDR_Pin_24                 0x01000000UL  /*!< Pin 24 selected */
#define MDR_Pin_25                 0x02000000UL  /*!< Pin 25 selected */
#define MDR_Pin_26                 0x04000000UL  /*!< Pin 26 selected */
#define MDR_Pin_27                 0x08000000UL  /*!< Pin 27 selected */
#define MDR_Pin_28                 0x10000000UL  /*!< Pin 28 selected */
#define MDR_Pin_29                 0x20000000UL  /*!< Pin 29 selected */
#define MDR_Pin_30                 0x40000000UL  /*!< Pin 30 selected */
#define MDR_Pin_31                 0x80000000UL  /*!< Pin 31 selected */

#define MDR_Pin_All                0xFFFFFFFFUL  /*!< All pins selected */


// =============================================================================
// =========== Функции настройки портов GPIO, базовая реализация ===============
// =============================================================================

//  Сброс регистров к начальным настройкам. Требуется предварительное включение тактирование порта.
void MDR_Port_Reset(MDR_PORT_Type *GPIO_Port);

// ========================= Управление пинами в режиме Port =============================
__STATIC_INLINE uint32_t MDR_Port_Get       (MDR_PORT_Type *GPIO_Port) {return GPIO_Port->RXTX;}
__STATIC_INLINE     bool MDR_Port_GetMaskSet(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {return (GPIO_Port->RXTX & pinSelect) == pinSelect;}
__STATIC_INLINE     bool MDR_Port_GetMaskClr(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {return ((~GPIO_Port->RXTX) & pinSelect) == pinSelect;}


__STATIC_INLINE     void MDR_Port_Set       (MDR_PORT_Type *GPIO_Port, uint32_t portData)  {GPIO_Port->RXTX     = portData;}
__STATIC_INLINE     void MDR_Port_SetPins   (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX_Set = pinSelect;}
__STATIC_INLINE     void MDR_Port_ClearPins (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX_Clr = pinSelect;}
__STATIC_INLINE     void MDR_Port_SwitchPins(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX ^= pinSelect;}


// =============================== ВАРИАНТ ИНИЦИАЛИЗАЦИИ 1 ====================================
typedef struct {
    MDR_PIN_RXTX    RXTX;
    MDR_PIN_OE      OE;
    MDR_PIN_FUNC    FUNC;
    MDR_PIN_AD      ANALOG;
    MDR_OnOff       PULL_Up;
    MDR_OnOff       PULL_Down;
    MDR_PIN_PD      PD;
    MDR_PIN_PWR     PWR;
} MDR_GPIO_PinCfg;

//  Настрока пинов порта в цифровой или аналоговый режим.
//  В MDR_GPIO_PinCfg задается настройка для младшего пина, которая применяется для всех пинов, выбранных в PinSelect
void MDR_Port_Init(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_GPIO_PinCfg *pinCfg);

//  Групповая настройка пинов в аналоговый режим
void MDR_Port_InitAnalog(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect);

// -----------------   Дополнительная настройка - Прерывания по уровню и контроль тока  ------------------
typedef struct {
    MDR_OnOff  CurrLim_En;      //  CurrentLim Control
    MDR_OnOff  IRQ_En;          //  IRQ Enable
    MDR_OnOff  IRQ_LevelHigh;   //  Level to rise IRQ
    MDR_OnOff  IRQ_Req;         //  IRQ Request
} MDR_GPIO_PinCfgEx;

void MDR_Port_InitEx(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_GPIO_PinCfgEx *pinCfg);
void MDR_Port_InitPinEx(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_GPIO_PinCfgEx *pinCfg);

__STATIC_INLINE uint32_t MDR_Port_GetStatusLimI(MDR_PORT_Type *GPIO_Port) {return GPIO_Port->HCUR;}
__STATIC_INLINE void     MDR_Port_ClearStatusLimI(MDR_PORT_Type *GPIO_Port) {GPIO_Port->HCUR = 0xFFFFFFFFUL;}
__STATIC_INLINE void     MDR_Port_RiseIRQ (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->IR_Set = pinSelect;}
__STATIC_INLINE void     MDR_Port_ClearIRQ(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->IR_Clr = pinSelect;}


// =============================== ВАРИАНТ НАСТРОЙКИ 2 ====================================
// Настройки общие для группы битов вынесены в отдельную структуру - MDR_PinDig_GroupPinCfg. 
// Остальные настройки, часто различающиеся, для одиночных или нескольких пинов задаются при вызове функций
// в параметрах - InOut и Func.

typedef enum {
  MDR_Pin_Out   = 0,
  MDR_Pin_In    = 1,
  MDR_Pin_In_PU = 2,  //  PullUp
  MDR_Pin_In_PD = 3,  //  PullDown
} MDR_Pin_IO;

typedef enum {
  MDR_Pin_PullOff   = MDR_Pin_In,      //  Pull Off
  MDR_Pin_PullUp    = MDR_Pin_In_PU,   //  PullUp
  MDR_Pin_PullDown  = MDR_Pin_In_PD,   //  PullDown
} MDR_Pin_FuncPull;

typedef struct {
  MDR_PIN_AD  ANALOG;
  MDR_PIN_PD  PD;
  MDR_PIN_PWR PWR;
} MDR_PinDig_GroupPinCfg;


//  Выделение настроек, одинаковых для группы пинов, в отдельную структуру
void MDR_Port_InitDigGroupRegs(MDR_PIN_PD pinDriver, MDR_PIN_PWR pinPower, MDR_PinDig_GroupPinCfg *groupPinCfg);

//  Инициализация пинов с дополнительными настройками и групповыми.
void MDR_Port_InitDig(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_Pin_IO InOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg);
void MDR_Port_InitDigPin(MDR_PORT_Type *GPIO_Port, uint32_t PinInd, MDR_Pin_IO InOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg);

//  Отдельные функции по настройке выводов в режим Port
__STATIC_INLINE
void MDR_Port_InitDigPort(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_Pin_IO InOut, const MDR_PinDig_GroupPinCfg *PinGroupRegs)
{
  MDR_Port_InitDig(GPIO_Port, pinSelect, InOut, MDR_PIN_PORT, PinGroupRegs);
}

__STATIC_INLINE 
void MDR_Port_InitDigPinPort(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_Pin_IO InOut, const MDR_PinDig_GroupPinCfg *groupPinCfg)
{
  MDR_Port_InitDigPin(GPIO_Port, pinInd, InOut, MDR_PIN_PORT, groupPinCfg);
}

//  Отдельные функции по настройке выводов в функции блоков периферии
__STATIC_INLINE 
void MDR_Port_InitDigFunc(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_Pin_FuncPull PinPull, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg)
{
  MDR_Port_InitDig(GPIO_Port, pinSelect, (MDR_Pin_IO)PinPull, pinFunc, groupPinCfg);
}
__STATIC_INLINE 
void MDR_Port_InitDigPinFunc(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_Pin_FuncPull PinPull, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg)
{
  MDR_Port_InitDigPin(GPIO_Port, pinInd, (MDR_Pin_IO)PinPull, pinFunc, groupPinCfg);
}

  
#define MDR_Port_InitDigFunc

//  Конвертация для вызова первого варианта инициализации через структуру MDR_GPIO_PinCfg
void MDR_Port_ToCfgRegs(MDR_Pin_IO InOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_GPIO_PinCfg *pinCfg);


// =============================== ВАРИАНТ НАСТРОЙКИ 2+ (Дополнение) ========================
//  Сбор настроек пинов порта в структуру с масками CLR и SET для последующего применения к портам за один вызов Apply
//  Позволяет собрать несколько конфигураций настройки порта и быстро переключаться между ними с помощью функции MDR_Port_MaskApply().
typedef struct {
    uint32_t        clrPins;
    uint32_t        clrFUNC_0_7;
    uint32_t        clrFUNC_8_15;
    uint32_t        clrFUNC_16_23;
    uint32_t        clrFUNC_24_31;
    uint32_t        clrPWR_0_15;
    uint32_t        clrPWR_16_31;
} MDR_GPIO_ClearCfg;

void MDR_Port_Clear_ClearCfg(MDR_GPIO_ClearCfg *cfgClr);

typedef struct {                                 /*!<  MDR_PORT Structure                                      */
    uint32_t        RXTX;                        /*!<  GPIO Pin Data                                              */    
    uint32_t        OE;                          /*!<  Output Enable Control                                      */    
    uint32_t        FUNC_0_7;                    /*!<  Pin Functions in Digital mode                              */
    uint32_t        FUNC_8_15;                   /*!<  Pin Functions in Digital mode                              */
    uint32_t        FUNC_16_23;                  /*!<  Pin Functions in Digital mode                              */
    uint32_t        FUNC_24_31;                  /*!<  Pin Functions in Digital mode                              */
    uint32_t        ANALOG;                      /*!<  Enable Digital Mode Control                                */
    uint32_t        PULL_Up;                     /*!<  PULL Up Control                                            */
    uint32_t        PULL_Down;                   /*!<  PULL Down Control                                          */
    uint32_t        PD;                          /*!<  Otput Driver Mode                                          */
    uint32_t        PWR_0_15;                    /*!<  Output voltage switch rate                                 */
    uint32_t        PWR_16_31;                   /*!<  Output voltage switch rate                                 */
} MDR_GPIO_SetCfg;

void MDR_Port_Clear_SetCfg(MDR_GPIO_SetCfg *cfgSet);

typedef struct {
  MDR_GPIO_ClearCfg MaskCLR;
  MDR_GPIO_SetCfg   MaskSET;
} MDR_Port_ApplyMask;

// Структура масок, куда будут собираться настройки пинов
void MDR_Port_MaskClear(MDR_Port_ApplyMask *applyMask);

//  Добавление в маски настроек группы пинов
//    Пины в аналоговую функцию
void MDR_Port_MaskAddAnalog(uint32_t pinSelect, MDR_Port_ApplyMask *applyMask);
//    Пины в цифровую функцию
void MDR_Port_MaskAdd(uint32_t pinSelect, MDR_Pin_IO InOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_Port_ApplyMask *applyMask);
//  Добавление в маски настроек одного пина
void MDR_Port_MaskAddPin(uint32_t pinInd, MDR_Pin_IO InOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_Port_ApplyMask *applyMask);
//  Применение маски в порт
void MDR_Port_MaskApply(MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *applyMask);
//  Применение масок к ранее считанному состоянию регистров порта
void MDR_Port_MaskApplyEx(MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *applyMask, MDR_GPIO_PinCfg *readRegs);

// ======= Вспомогательные функции, для логгирования и отладки ===========
void MDR_Port_ReadRegs (MDR_PORT_Type *GPIO_Port, MDR_GPIO_SetCfg *portCfg);
void MDR_Port_WriteRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_SetCfg *cfgSet, MDR_GPIO_ClearCfg *cfgClr);



//==================================================================================
// ===========  Расширенная реализация c включением тактирования портов ============
//==================================================================================

typedef struct {
  // GPIO Port
  MDR_PORT_Type *PORTx;
  // Clock Enable
  volatile uint32_t*  RST_ClockEn_Addr;
  uint32_t            ClockEnaMask;
} MDR_GPIO_Port;

extern const MDR_GPIO_Port    GPIO_A_Port;
extern const MDR_GPIO_Port    GPIO_B_Port;
extern const MDR_GPIO_Port    GPIO_C_Port;
extern const MDR_GPIO_Port    GPIO_D_Port;
extern const MDR_GPIO_Port    GPIO_E_Port;
extern const MDR_GPIO_Port    GPIO_F_Port;
extern const MDR_GPIO_Port    GPIO_G_Port;
extern const MDR_GPIO_Port    GPIO_H_Port;
extern const MDR_GPIO_Port    GPIO_I_Port;

#define MDR_GPIO_A            (&GPIO_A_Port)
#define MDR_GPIO_B            (&GPIO_B_Port)
#define MDR_GPIO_C            (&GPIO_C_Port)
#define MDR_GPIO_D            (&GPIO_D_Port)
#define MDR_GPIO_E            (&GPIO_E_Port)
#define MDR_GPIO_F            (&GPIO_F_Port)
#define MDR_GPIO_G            (&GPIO_G_Port)
#define MDR_GPIO_H            (&GPIO_H_Port)
#define MDR_GPIO_I            (&GPIO_I_Port)

//  Тактирование блока и
__STATIC_INLINE void MDR_GPIO_Enable(const MDR_GPIO_Port *GPIO_Port)
{
  REG32(GPIO_Port->RST_ClockEn_Addr) |= GPIO_Port->ClockEnaMask;
  
#ifdef MDR_GPIO_HAS_KEY  
  GPIO_Port->PORTx->KEY = MDR_KEY_UNLOCK;
#endif
}

//  Отключение тактирования
__STATIC_INLINE void MDR_GPIO_Disable(const MDR_GPIO_Port *GPIO_Port)
{
  REG32(GPIO_Port->RST_ClockEn_Addr) &= ~(1 << GPIO_Port->ClockEnaMask);
  
#ifdef MDR_GPIO_HAS_KEY    
  GPIO_Port->PORTx->KEY = 0;
#endif
}

// Аналоги функций базовой реализации, только со структурой MDR_GPIO_Port вместо MDR_PORT_Type

#define MDR_GPIO_Reset(GP)                    MDR_Port_Reset((GP)->PORTx)

// Вариант настройки 1
#define MDR_GPIO_Init(GP, Sel, Cfg)           MDR_Port_Init((GP)->PORTx, (Sel), (Cfg))
#define MDR_GPIO_InitAnalog(GP, Sel)          MDR_Port_InitAnalog((GP)->PORTx, (Sel))

#define MDR_GPIO_Set(GP, Data)                MDR_Port_Set(GP)->PORTx, Data)

#define MDR_GPIO_SetPins(GP, Sel)             MDR_Port_SetPins((GP)->PORTx, Sel)
#define MDR_GPIO_ClearPins(GP, Sel)           MDR_Port_ClearPins((GP)->PORTx, Sel)
#define MDR_GPIO_SwitchPins(GP, Sel)          MDR_Port_SwitchPins((GP)->PORTx, Sel)
#define MDR_GPIO_Get(GP)                      MDR_Port_Get((GP)->PORTx)
#define MDR_GPIO_GetMaskSet(GP, Sel)          MDR_Port_GetMaskSet((GP)->PORTx, Sel)
#define MDR_GPIO_GetMaskClr(GP, Sel)          MDR_Port_GetMaskClr((GP)->PORTx, Sel)


// Вариант настройки 2
#define MDR_GPIO_InitDigGroupRegs             MDR_Port_InitDigGroupRegs

#define MDR_GPIO_InitDig(GP, Sel, IO, F, pPerm)     MDR_Port_InitDig((GP)->PORTx, (Sel), (IO), (F), (pPerm))
#define MDR_GPIO_InitDigPin(GP, Ind, IO, F, pPerm)  MDR_Port_InitDigPin((GP)->PORTx, (Ind), (IO), (F), (pPerm))

#define MDR_GPIO_ToCfgRegs                    MDR_Port_ToCfgRegs
#define MDR_GPIO_MaskClear                    MDR_Port_MaskClear
#define MDR_GPIO_MaskAddAnalog                MDR_Port_MaskAddAnalog
#define MDR_GPIO_MaskAdd                      MDR_Port_MaskAdd
#define MDR_GPIO_MaskAddPin                   MDR_Port_MaskAddPin
#define MDR_GPIO_MaskApply(GP, msk)           MDR_Port_MaskApply((GP)->PORTx, (msk))
#define MDR_GPIO_MaskApplyEx(GP, msk, rdCfg)  MDR_Port_MaskApplyEx((GP)->PORTx, (msk), (rdCfg))


#define MDR_GPIO_ReadRegs(GP, CfgRegs)        MDR_Port_ReadRegs((GP)->PORTx, (CfgRegs))
#define MDR_GPIO_WriteRegs(GP, CfgRegs)       MDR_Port_WriteRegs((GP)->PORTx, (CfgRegs))

// Настройка пинов/пина в функции порт по умолчанию
#define MDR_GPIO_InitOutDef(GP, Sel)          MDR_GPIO_InitDig   ((GP), (Sel), MDR_Pin_Out, MDR_PIN_PORT, &PinDig_PermRegsDef)
#define MDR_GPIO_InitPinOutDef(GP, Ind)       MDR_GPIO_InitDigPin((GP), (Ind), MDR_Pin_Out, MDR_PIN_PORT, &PinDig_PermRegsDef)

#define MDR_GPIO_InitInDef(GP, Sel)           MDR_GPIO_InitDig   ((GP), (Sel), MDR_Pin_In, MDR_PIN_PORT, &PinDig_PermRegsDef)
#define MDR_GPIO_InitPinInDef(GP, Ind)        MDR_GPIO_InitDigPin((GP), (Ind), MDR_Pin_In, MDR_PIN_PORT, &PinDig_PermRegsDef)


//  Для совместимости со старыми названиями
#define MDR_PinDig_PermRegs         MDR_PinDig_GroupPinCfg
#define MDR_Port_InitDigPermRegs    MDR_Port_InitDigGroupRegs
#define MDR_GPIO_ClockOn            MDR_GPIO_Enable
                                     
#endif //  _MDR_GPIO_VE8x_H
