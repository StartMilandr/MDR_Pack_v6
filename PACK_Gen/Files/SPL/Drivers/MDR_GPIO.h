#ifndef _MDR_GPIO_H
#define _MDR_GPIO_H

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
  
#if MDR_GPIO_Pin_Count > 16  
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
#else
  #define MDR_Pin_All                0xFFFFUL  /*!< All pins selected */
#endif


//=================================    Защита Jtag ==============================
// В пины Jtag можно писать только 0, иначе интерфейс отваливается
#if defined (USE_JTAG_A)
  #define PORT_JTAG                 MDR_JTAG_A_PORT
  #define PORT_JTAG_PinSel          MDR_JTAG_A_PINS
  #define PORT_JTAG_FuncSel         MDR_JTAG_A_PINS_FUNC
  #define PORT_JTAG_PDSel           MDR_JTAG_A_PINS_PD

  //  for ESila
  #define PORT_JTAG_Func0Sel        MDR_JTAG_A_PINS_FUNC0
  #define PORT_JTAG_Func1Sel        MDR_JTAG_A_PINS_FUNC1
  #define PORT_JTAG_Func2Sel        MDR_JTAG_A_PINS_FUNC2
  #define PORT_JTAG_Func3Sel        MDR_JTAG_A_PINS_FUNC3 
  #define PORT_JTAG_PWR0            MDR_JTAG_A_PINS_PWR0
  #define PORT_JTAG_PWR1            MDR_JTAG_A_PINS_PWR1

#elif defined (USE_JTAG_B)
  #define PORT_JTAG                 MDR_JTAG_B_PORT
  #define PORT_JTAG_PinSel          MDR_JTAG_B_PINS
  #define PORT_JTAG_FuncSel         MDR_JTAG_B_PINS_FUNC
  #define PORT_JTAG_PDSel           MDR_JTAG_B_PINS_PD
  
  //  for ESila
  #define PORT_JTAG_Func0Sel        MDR_JTAG_B_PINS_FUNC0
  #define PORT_JTAG_Func1Sel        MDR_JTAG_B_PINS_FUNC1
  #define PORT_JTAG_Func2Sel        MDR_JTAG_B_PINS_FUNC2
  #define PORT_JTAG_Func3Sel        MDR_JTAG_B_PINS_FUNC3
  #define PORT_JTAG_PWR0            MDR_JTAG_B_PINS_PWR0
  #define PORT_JTAG_PWR1            MDR_JTAG_B_PINS_PWR1

#elif defined (USE_SWD_A)
  #define PORT_JTAG                 MDR_SWD_A_PORT
  #define PORT_JTAG_PinSel          MDR_SWD_A_PINS
  #define PORT_JTAG_FuncSel         MDR_SWD_A_PINS_FUNC
  #define PORT_JTAG_PDSel           MDR_SWD_A_PINS_PD  
  
  //  for ESila
  #define PORT_JTAG_Func0Sel        MDR_SWD_A_PINS_FUNC0
  #define PORT_JTAG_Func1Sel        MDR_SWD_A_PINS_FUNC1
  #define PORT_JTAG_Func2Sel        MDR_SWD_A_PINS_FUNC2
  #define PORT_JTAG_Func3Sel        MDR_SWD_A_PINS_FUNC3
  #define PORT_JTAG_PWR0            MDR_SWD_A_PINS_PWR0
  #define PORT_JTAG_PWR1            MDR_SWD_A_PINS_PWR1  
  
#elif defined (USE_SWD_B)
  #define PORT_JTAG                 MDR_SWD_B_PORT
  #define PORT_JTAG_PinSel          MDR_SWD_B_PINS
  #define PORT_JTAG_FuncSel         MDR_SWD_B_PINS_FUNC
  #define PORT_JTAG_PDSel           MDR_SWD_B_PINS_PD    
  
  //  for ESila
  #define PORT_JTAG_Func0Sel        MDR_SWD_B_PINS_FUNC0
  #define PORT_JTAG_Func1Sel        MDR_SWD_B_PINS_FUNC1
  #define PORT_JTAG_Func2Sel        MDR_SWD_B_PINS_FUNC2
  #define PORT_JTAG_Func3Sel        MDR_SWD_B_PINS_FUNC3  
  #define PORT_JTAG_PWR0            MDR_SWD_B_PINS_PWR0
  #define PORT_JTAG_PWR1            MDR_SWD_B_PINS_PWR1  
#endif


#if defined (PORT_JTAG)
  #define JTAG_PINS(PORT)          (((PORT) == PORT_JTAG) ? PORT_JTAG_PinSel  : 0)
  #define JTAG_PINS_x2(PORT)       (((PORT) == PORT_JTAG) ? PORT_JTAG_FuncSel : 0)
  #define JTAG_PINS_HILO(PORT)     (((PORT) == PORT_JTAG) ? PORT_JTAG_PDSel   : 0)
#else
  #define JTAG_PINS(PORT)           0
  #define JTAG_PINS_x2(PORT)        0
  #define JTAG_PINS_HILO(PORT)      0
#endif



// =============================================================================
// =========== Функции настройки портов GPIO, базовая реализация ===============
// =============================================================================

//  Сброс регистров к начальным настройкам. Требуется предварительное включение тактирование порта.
void MDR_Port_Reset(MDR_PORT_Type *GPIO_Port);

// ========================= Управление пинами в режиме Port =============================
__STATIC_INLINE uint32_t MDR_Port_Get       (MDR_PORT_Type *GPIO_Port) {return GPIO_Port->RXTX;}
__STATIC_INLINE     bool MDR_Port_GetMaskSet(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {return (GPIO_Port->RXTX & pinSelect) == pinSelect;}
__STATIC_INLINE     bool MDR_Port_GetMaskClr(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {return ((~GPIO_Port->RXTX) & pinSelect) == pinSelect;}

#ifdef PORT_JTAG
  //  Обнуление битов JTAG чтобы не сломать работу отладчика.
  #if defined(MDR_GPIO_HAS_SET_CLEAR)
    __STATIC_INLINE     void MDR_Port_Set       (MDR_PORT_Type *GPIO_Port, uint32_t portData)  {GPIO_Port->RXTX     = portData  & (~JTAG_PINS(GPIO_Port));}
    __STATIC_INLINE     void MDR_Port_SetPins   (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX_Set = pinSelect & (~JTAG_PINS(GPIO_Port));}
    __STATIC_INLINE     void MDR_Port_ClearPins (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX_Clr = pinSelect;}
    __STATIC_INLINE     void MDR_Port_TogglePins(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX = (GPIO_Port->RXTX ^ pinSelect) & (~JTAG_PINS(GPIO_Port));}
  #else
    __STATIC_INLINE     void MDR_Port_Set       (MDR_PORT_Type *GPIO_Port, uint32_t portData)  {GPIO_Port->RXTX = portData & (~JTAG_PINS(GPIO_Port));}
    __STATIC_INLINE     void MDR_Port_SetPins   (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX = (GPIO_Port->RXTX |  pinSelect) & (~JTAG_PINS(GPIO_Port));}
    __STATIC_INLINE     void MDR_Port_ClearPins (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX = (GPIO_Port->RXTX & ~(pinSelect || JTAG_PINS(GPIO_Port)));}
    __STATIC_INLINE     void MDR_Port_TogglePins(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX = (GPIO_Port->RXTX ^  pinSelect) & (~JTAG_PINS(GPIO_Port));}
  #endif  
#else 
  #if defined(MDR_GPIO_HAS_SET_CLEAR)
    //  Rename VE1 reg names to VE8 style names
    #ifndef MDR_GPIO_LIKE_VE8
      #define RXTX_Set  SETTX
      #define RXTX_Clr  CLRTX
    #endif

    __STATIC_INLINE     void MDR_Port_Set       (MDR_PORT_Type *GPIO_Port, uint32_t portData)  {GPIO_Port->RXTX     = portData;}
    __STATIC_INLINE     void MDR_Port_SetPins   (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX_Set = pinSelect;}
    __STATIC_INLINE     void MDR_Port_ClearPins (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX_Clr = pinSelect;}
    __STATIC_INLINE     void MDR_Port_TogglePins(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX    ^= pinSelect;}    
  #else  
    __STATIC_INLINE     void MDR_Port_Set       (MDR_PORT_Type *GPIO_Port, uint32_t portData)  {GPIO_Port->RXTX  = portData;}
    __STATIC_INLINE     void MDR_Port_SetPins   (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX |= pinSelect;}
    __STATIC_INLINE     void MDR_Port_ClearPins (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX &= ~pinSelect;}
    __STATIC_INLINE     void MDR_Port_TogglePins(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX ^= pinSelect;}
  #endif
#endif

// =============================== ВАРИАНТ НАСТРОЙКИ 1 ====================================

typedef struct {
    MDR_PIN_RXTX    RxTx;         //  RXTX
    MDR_OnOff       OutputEnable; //  OE
    MDR_PIN_FUNC    Func;         //  FUNC
    MDR_OnOff       DigMode;      //  ANALOG
    MDR_OnOff       PullUp;       //  PULL_hi
    MDR_OnOff       PullDown;     //  PULL_lo
    MDR_OnOff       OpenDrain;    //  PD_lo
    MDR_PIN_PWR     Power;        //  PWR
  
#ifdef  MDR_GPIO_HAS_GFEN_SCHMT
    MDR_OnOff       InpFilterEn;  //  GFEN
    MDR_OnOff       InpSchmEn;    //  PD_hi
#endif  
} MDR_GPIO_PinCfg;
  
//  Настрока пинов порта в цифровой или аналоговый режим.
//  В MDR_GPIO_PinCfg задается настройка для младшего пина, которая применяется для всех пинов, выбранных в PinSelect
void MDR_Port_Init(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_GPIO_PinCfg *pinCfg);

//  Групповая настройка пинов в аналоговый режим
void MDR_Port_InitAnalog(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect);


// =============================== ВАРИАНТ НАСТРОЙКИ 2 ====================================
// Общие настройки для группы битов вынесены в отдельную структуру - MDR_PinDig_PermRegs. 
// Остальные, часто различающиеся, настройки для одиночных или нескольких пинов задаются при вызове функций
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
} MDR_Pin_InPull;

#define MDR_Pin_FuncPull  MDR_Pin_InPull

typedef struct {
  MDR_OnOff       DigMode;      //  ANALOG
  MDR_OnOff       OpenDrain;    //  PD_lo
  MDR_PIN_PWR     Power;        //  PWR
  
#ifdef  MDR_GPIO_HAS_GFEN_SCHMT  
  MDR_OnOff       InpFilterEn;  //  GFEN
  MDR_OnOff       InpSchmEn;    //  PD_hi
#endif
} MDR_PinDig_GroupPinCfg;  


//  Выделение настроек, одинаковых для группы пинов, в отдельную структуру
#ifdef MDR_GPIO_HAS_GFEN_SCHMT
  void MDR_Port_InitDigGroupPinCfg(MDR_OnOff pinOpenDrain, MDR_PIN_PWR pinPower, MDR_OnOff InpSchmEn, MDR_OnOff InpFilterEn, MDR_PinDig_GroupPinCfg *groupPinCfg);
#else
  void MDR_Port_InitDigGroupPinCfg(MDR_OnOff pinOpenDrain, MDR_PIN_PWR pinPower, MDR_PinDig_GroupPinCfg *groupPinCfg);
#endif


//  Инициализация пинов с дополнительными настройками и групповыми.
void MDR_Port_InitDig(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg);
void MDR_Port_InitDigPin(MDR_PORT_Type *GPIO_Port, uint32_t PinInd, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg);


__STATIC_INLINE 
void MDR_Port_InitDigPort(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_Pin_IO pinInOut, const MDR_PinDig_GroupPinCfg *groupPinCfg) 
{
  MDR_Port_InitDig(GPIO_Port, pinSelect, pinInOut, MDR_PIN_PORT, groupPinCfg);
}

__STATIC_INLINE 
void MDR_Port_InitDigFunc(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_Pin_FuncPull pinPull, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg)
{
  MDR_Port_InitDig(GPIO_Port, pinSelect, (MDR_Pin_IO)pinPull, pinFunc, groupPinCfg);
}

__STATIC_INLINE 
void MDR_Port_InitDigPinPort(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_Pin_IO pinInOut, const MDR_PinDig_GroupPinCfg *groupPinCfg)
{
  MDR_Port_InitDigPin(GPIO_Port, pinInd, pinInOut, MDR_PIN_PORT, groupPinCfg);
}

__STATIC_INLINE 
void MDR_Port_InitDigPinFunc(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_Pin_FuncPull pinPull, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg)
{
  MDR_Port_InitDigPin(GPIO_Port, pinInd, (MDR_Pin_IO)pinPull, pinFunc, groupPinCfg);
}

//  Конвертация в MDR_GPIO_CfgRegs для вызова первого варианта
void MDR_Port_ToPinCfg(MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_GPIO_PinCfg *pinCfg);


// Упрощенная настройка пинов/пина в функции порт IN/OUT по умолчанию
void MDR_Port_Init_PortOUT   (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_PIN_PWR pinPWR);
void MDR_Port_InitPin_PortOUT(MDR_PORT_Type *GPIO_Port, uint32_t pinInd,    MDR_PIN_PWR pinPWR);

void MDR_Port_Init_PortIN_Pull(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_Pin_InPull pinPull);
void MDR_Port_InitPin_PortIN_Pull(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_Pin_InPull pinPull);

__STATIC_INLINE 
void MDR_Port_Init_PortIN   (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) { MDR_Port_Init_PortIN_Pull(GPIO_Port, pinSelect, MDR_Pin_PullOff); }
__STATIC_INLINE 
void MDR_Port_InitPin_PortIN(MDR_PORT_Type *GPIO_Port, uint32_t pinInd) { MDR_Port_InitPin_PortIN_Pull(GPIO_Port, pinInd, MDR_Pin_PullOff); }


// =============================== ВАРИАНТ НАСТРОЙКИ 2+ (Дополнение) ========================
//  Сбор настроек пинов порта в структуру с масками CLR и SET для последующего применения к портам за один вызов Apply
//  Иногда это оптимальней, чем вызывать применение в порт для каждого отдельного пина

typedef struct {
  MDR_GPIO_ClearCfg MaskCLR;
  MDR_GPIO_SetCfg   MaskSET;
} MDR_Port_ApplyMask;

//  Обнуление структур
void MDR_Port_MaskClear(MDR_Port_ApplyMask *applyMask);
void MDR_Port_Clear_ClearCfg(MDR_GPIO_ClearCfg *cfgClr);
void MDR_Port_Clear_SetCfg(MDR_GPIO_SetCfg *cfgSet);

void MDR_Port_FillClearMask(uint32_t pinSelect, MDR_GPIO_ClearCfg *cfgClr);

//  Добавление в маски настроек группы пинов
//    Пины в аналоговую функцию
void MDR_Port_MaskAddAnalog(uint32_t pinSelect, MDR_Port_ApplyMask *applyMask);
//    Пины в цифровую функцию
void MDR_Port_MaskAdd(uint32_t pinSelect, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_Port_ApplyMask *applyMask);
//  Добавление в маски настроек одного пина
void MDR_Port_MaskAddPin(uint32_t pinInd, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_Port_ApplyMask *applyMask);
//  Применение маски в порт
void MDR_Port_MaskApply(  MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *ApplyMask);
//  Применение масок к ранее считанному состоянию регистров порта
void MDR_Port_MaskApplyEx(MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *ApplyMask,  MDR_GPIO_SetCfg *readRegs);

// ======= Вспомогательные функции, для логгирования и отладки ===========
void MDR_Port_ReadRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_SetCfg *cfgRegs);

#ifdef MDR_GPIO_CFG_SET_CLEAR
  void MDR_Port_WriteRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_SetCfg *cfgSet, MDR_GPIO_ClearCfg *cfgClr);
#else
  void MDR_Port_WriteRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_SetCfg *cfgRegs);
#endif


//==================================================================================
// ===========  Расширенная реализация c включением тактирования ===================
//==================================================================================

typedef struct {
  // GPIO Port
  MDR_PORT_Type        *PORTx;
  // Clock Enable
  volatile uint32_t*    RST_ClockEn_Addr;
  uint32_t              ClockEnaMask;
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



//  Тактирование блока
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
  #define MDR_GPIO_TogglePins(GP, Sel)          MDR_Port_TogglePins((GP)->PORTx, Sel)
  #define MDR_GPIO_Get(GP)                      MDR_Port_Get((GP)->PORTx)
  #define MDR_GPIO_GetMaskSet(GP, Sel)          MDR_Port_GetMaskSet((GP)->PORTx, Sel)
  #define MDR_GPIO_GetMaskClr(GP, Sel)          MDR_Port_GetMaskClr((GP)->PORTx, Sel)


  // Вариант настройки 2
  #define MDR_GPIO_InitDigPermRegs              MDR_Port_InitDigPermRegs

  #define MDR_GPIO_InitDig(GP, Sel, IO, F, pPerm)     MDR_Port_InitDig((GP)->PORTx, (Sel), (IO), (F), (pPerm))
  #define MDR_GPIO_InitDigPin(GP, Ind, IO, F, pPerm)  MDR_Port_InitDigPin((GP)->PORTx, (Ind), (IO), (F), (pPerm))
  
  #define MDR_GPIO_InitDigFunc(GP, Sel, Pull, F, pPerm)     MDR_Port_InitDigFunc((GP)->PORTx, (Sel), (Pull), (F), (pPerm)) 

  #define MDR_GPIO_ToCfgRegs                    MDR_Port_ToCfgRegs
  #define MDR_GPIO_MaskClear                    MDR_Port_MaskClear
  #define MDR_GPIO_MaskAddAnalog                MDR_Port_MaskAddAnalog
  #define MDR_GPIO_MaskAdd                      MDR_Port_MaskAdd
  #define MDR_GPIO_MaskAddPin                   MDR_Port_MaskAddPin
  #define MDR_GPIO_MaskApply(GP, msk)           MDR_Port_MaskApply((GP)->PORTx, (msk))
  #define MDR_GPIO_MaskApplyEx(GP, msk, rdCfg)  MDR_Port_MaskApplyEx((GP)->PORTx, (msk), (rdCfg))


  #define MDR_GPIO_ReadRegs(GP, CfgRegs)        MDR_Port_ReadRegs((GP)->PORTx, (CfgRegs))
  
#ifdef MDR_GPIO_CFG_SET_CLEAR
  #define MDR_GPIO_WriteRegs(GP, CfgSet, CfgClr)  MDR_Port_WriteRegs((GP)->PORTx, (CfgSet), (CfgClr))
#else
  #define MDR_GPIO_WriteRegs(GP, CfgRegs)         MDR_Port_WriteRegs((GP)->PORTx, (CfgRegs))
#endif  


  // Упрощенная настройка пинов/пина в функции порт IN/OUT по умолчанию
  #define MDR_GPIO_Init_PortOUT(GP, Sel, Pwr)     MDR_Port_Init_PortOUT   ((GP)->PORTx, (Sel), (Pwr))
  #define MDR_GPIO_InitPin_PortOUT(GP, Ind, Pwr)  MDR_Port_InitPin_PortOUT((GP)->PORTx, (Ind), (Pwr))

  #define MDR_GPIO_Init_PortIN(GP, Sel)           MDR_Port_Init_PortIN   ((GP)->PORTx, (Sel))
  #define MDR_GPIO_InitPin_PortIN(GP, Ind)        MDR_Port_InitPin_PortIN((GP)->PORTx, (Ind))

  #define MDR_GPIO_Init_PortIN_Pull(GP, Sel, pull)      MDR_Port_Init_PortIN_Pull   ((GP)->PORTx, (Sel), (pull))
  #define MDR_GPIO_InitPin_PortIN_Pull(GP, Ind, pull)   MDR_Port_InitPin_PortIN_Pull((GP)->PORTx, (Ind), (pull))


//===================================

#ifdef MDR_GPIO_HAS_CfgIRQ
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
#endif


  
//  Для совместимости со старыми названиями
#define MDR_PinDig_PermRegs         MDR_PinDig_GroupPinCfg  

//===================== Структуры для назначения пинов (унифицированный аналог MDR_SSP_CfgPinGPIO из MDR_SSP.h и аналогичных) ===============
typedef struct {
  const MDR_GPIO_Port *portGPIO;
  uint32_t       selPins;
  MDR_PIN_FUNC   pinFunc;
} MDR_GPIO_CfgPinFunc;


typedef struct {
  const MDR_GPIO_Port *portGPIO;
  uint32_t       selPins;
} MDR_GPIO_CfgPinPort;

#endif //  _MDR_GPIO_H
