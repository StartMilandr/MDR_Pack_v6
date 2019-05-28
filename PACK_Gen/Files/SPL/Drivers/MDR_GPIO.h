#ifndef _MDR_GPIO_H
#define _MDR_GPIO_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>

typedef struct {                                       /*!<     MDR_PORT Structure                                        */
    uint32_t        RXTX;                        /*!< (@ 0x00000000) GPIO Pin Data                                              */    
    uint32_t        OE;                          /*!< (@ 0x00000004) Output Enable Control                                      */    
    uint32_t        FUNC;                        /*!< (@ 0x00000008) Pin Functions in Digital mode                              */
    uint32_t        ANALOG;                      /*!< (@ 0x0000000C) Enable Digital Mode Control                                */
    uint32_t        PULL;                        /*!< (@ 0x00000010) PULL Up and Down Control                                   */
    uint32_t        PD;                          /*!< (@ 0x00000014) Otput Driver Mode                                          */
    uint32_t        PWR;                         /*!< (@ 0x00000018) Output voltage switch rate                                 */
    uint32_t        GFEN;                        /*!< (@ 0x0000001C) Input pulses filter                                        */
} MDR_GPIO_CfgRegs;


#define MDR_Pin_0                  0x0001UL  /*!< Pin 0 selected */
#define MDR_Pin_1                  0x0002UL  /*!< Pin 1 selected */
#define MDR_Pin_2                  0x0004UL  /*!< Pin 2 selected */
#define MDR_Pin_3                  0x0008UL  /*!< Pin 3 selected */
#define MDR_Pin_4                  0x0010UL  /*!< Pin 4 selected */
#define MDR_Pin_5                  0x0020UL  /*!< Pin 5 selected */
#define MDR_Pin_6                  0x0040UL  /*!< Pin 6 selected */
#define MDR_Pin_7                  0x0080UL  /*!< Pin 7 selected */
#define MDR_Pin_8                  0x0100UL  /*!< Pin 8 selected */
#define MDR_Pin_9                  0x0200UL  /*!< Pin 9 selected */
#define MDR_Pin_10                 0x0400UL  /*!< Pin 10 selected */
#define MDR_Pin_11                 0x0800UL  /*!< Pin 11 selected */
#define MDR_Pin_12                 0x1000UL  /*!< Pin 12 selected */
#define MDR_Pin_13                 0x2000UL  /*!< Pin 13 selected */
#define MDR_Pin_14                 0x4000UL  /*!< Pin 14 selected */
#define MDR_Pin_15                 0x8000UL  /*!< Pin 15 selected */
#define MDR_Pin_All                0xFFFFUL  /*!< All pins selected */


//=================================    Защита Jtag ==============================
// В пины Jtag можно писать только 0, иначе интерфейс отваливается
#if defined (USE_JTAG_A)
  #define PORT_JTAG                 MDR_JTAG_A_PORT
  #define PORT_JTAG_PinSel          MDR_JTAG_A_PINS
  #define PORT_JTAG_FuncSel         MDR_JTAG_A_PINS_FUNC
  #define PORT_JTAG_PDSel           MDR_JTAG_A_PINS_PD
#elif defined (USE_JTAG_B)
  #define PORT_JTAG                 MDR_JTAG_B_PORT
  #define PORT_JTAG_PinSel          MDR_JTAG_B_PINS
  #define PORT_JTAG_FuncSel         MDR_JTAG_B_PINS_FUNC
  #define PORT_JTAG_PDSel           MDR_JTAG_B_PINS_PD
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

// ========================= Доступ к пинам =============================
__STATIC_INLINE uint32_t MDR_Port_Get       (MDR_PORT_Type *GPIO_Port) {return GPIO_Port->RXTX;}
__STATIC_INLINE     bool MDR_Port_GetMaskSet(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {return (GPIO_Port->RXTX & pinSelect) == pinSelect;}
__STATIC_INLINE     bool MDR_Port_GetMaskClr(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {return ((~GPIO_Port->RXTX) & pinSelect) == pinSelect;}


#ifndef PORT_JTAG
__STATIC_INLINE     void MDR_Port_Set       (MDR_PORT_Type *GPIO_Port, uint32_t portData)  {GPIO_Port->RXTX  = portData;}
__STATIC_INLINE     void MDR_Port_SetPins   (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX |= pinSelect;}
__STATIC_INLINE     void MDR_Port_ClearPins (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX &= ~pinSelect;}
__STATIC_INLINE     void MDR_Port_SwitchPins(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX ^= pinSelect;}
#else
__STATIC_INLINE     void MDR_Port_Set       (MDR_PORT_Type *GPIO_Port, uint32_t portData)  {GPIO_Port->RXTX = portData & (~JTAG_PINS(GPIO_Port));}
__STATIC_INLINE     void MDR_Port_SetPins   (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX = (GPIO_Port->RXTX |  pinSelect) & (~JTAG_PINS(GPIO_Port));}
__STATIC_INLINE     void MDR_Port_ClearPins (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX = (GPIO_Port->RXTX & ~pinSelect) & (~JTAG_PINS(GPIO_Port));}
__STATIC_INLINE     void MDR_Port_SwitchPins(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect) {GPIO_Port->RXTX = (GPIO_Port->RXTX ^  pinSelect) & (~JTAG_PINS(GPIO_Port));}
#endif

// =============================== ВАРИАНТ НАСТРОЙКИ 1 ====================================
//  Групповая настрока пинов порта в цифровой или аналоговый режим.
//  В cfgRegs задается настройка для младшего пина, которая применяется для всех пинов, выбранных в PinSelect
void MDR_Port_Init(MDR_PORT_Type *GPIO_Port, uint32_t PinSelect, MDR_GPIO_CfgRegs *cfgRegs);

//  Групповая настройка пинов в аналоговый режим
void MDR_Port_InitAnalog(MDR_PORT_Type *GPIO_Port, uint32_t PinSelect);


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
} MDR_Pin_FuncPull;

typedef struct {
  uint32_t ANALOG;
  uint32_t PD;
  uint32_t PWR;
  uint32_t GFEN;
} MDR_PinDig_GroupCfgRegs;

//  Для совместимости со старыми названиями
#define MDR_PinDig_PermRegs         MDR_PinDig_GroupCfgRegs

//  Выделение настроек, одинаковых для группы пинов, в отдельную структуру
void MDR_Port_InitDigPermRegs(MDR_PIN_PD OutDriver, MDR_PIN_PWR Power, MDR_OnOff InpSchmEn, MDR_OnOff InpFilterEn, MDR_PinDig_PermRegs *PinPermRegs);

//  Инициализация пинов с дополнительными настройками и групповыми.
void MDR_Port_InitDig(MDR_PORT_Type *GPIO_Port, uint32_t PinSelect, MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_PinDig_PermRegs *PinPermRegs);
void MDR_Port_InitDigPin(MDR_PORT_Type *GPIO_Port, uint32_t PinInd, MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_PinDig_PermRegs *PinPermRegs);

__STATIC_INLINE 
void MDR_Port_InitDigPort(MDR_PORT_Type *GPIO_Port, uint32_t PinSelect, MDR_Pin_IO InOut, const MDR_PinDig_GroupCfgRegs *PinGroupRegs) 
{
  MDR_Port_InitDig(GPIO_Port, PinSelect, InOut, MDR_PIN_PORT, PinGroupRegs);
}

__STATIC_INLINE 
void MDR_Port_InitDigFunc(MDR_PORT_Type *GPIO_Port, uint32_t PinSelect, MDR_Pin_FuncPull PinPull, MDR_PIN_FUNC Func, const MDR_PinDig_GroupCfgRegs *PinGroupRegs)
{
  MDR_Port_InitDig(GPIO_Port, PinSelect, (MDR_Pin_IO)PinPull, Func, PinGroupRegs);
}

__STATIC_INLINE 
void MDR_Port_InitDigPinPort(MDR_PORT_Type *GPIO_Port, uint32_t PinInd, MDR_Pin_IO InOut, const MDR_PinDig_GroupCfgRegs *PinGroupRegs)
{
  MDR_Port_InitDigPin(GPIO_Port, PinInd, InOut, MDR_PIN_PORT, PinGroupRegs);
}

__STATIC_INLINE 
void MDR_Port_InitDigPinFunc(MDR_PORT_Type *GPIO_Port, uint32_t PinInd, MDR_Pin_FuncPull PinPull, MDR_PIN_FUNC Func, const MDR_PinDig_GroupCfgRegs *PinGroupRegs)
{
  MDR_Port_InitDigPin(GPIO_Port, PinInd, (MDR_Pin_IO)PinPull, MDR_PIN_PORT, PinGroupRegs);
}



//  Конвертация в MDR_GPIO_CfgRegs для вызова первого варианта
void MDR_Port_ToCfgRegs(MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_PinDig_PermRegs *PinPermRegs, MDR_GPIO_CfgRegs *cfgRegs);


// =============================== ВАРИАНТ НАСТРОЙКИ 2+ (Дополнение) ========================
//  Сбор настроек пинов порта в структуру с масками CLR и SET для последующего применения к портам за один вызов Apply
//  Иногда это оптимальней, чем вызывать применение в порт для каждого отдельного пина
typedef struct {
  MDR_GPIO_CfgRegs MaskCLR;
  MDR_GPIO_CfgRegs MaskSET;
} MDR_Port_ApplyMask;

// Структура масок, куда будут собираться настройки пинов
void MDR_Port_MaskClear(MDR_Port_ApplyMask *ApplyMask);

//  Добавление в маски настроек группы пинов
//    Пины в аналоговую функцию
void MDR_Port_MaskAddAnalog(uint32_t PinSelect, MDR_Port_ApplyMask *ApplyMask);
//    Пины в цифровую функцию
void MDR_Port_MaskAdd(uint32_t PinSelect, MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_PinDig_PermRegs *PinPermRegs, MDR_Port_ApplyMask *ApplyMask);
//  Добавление в маски настроек одного пина
void MDR_Port_MaskAddPin(uint32_t PinInd, MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_PinDig_PermRegs *PinPermRegs, MDR_Port_ApplyMask *ApplyMask);
//  Применение маски в порт
void MDR_Port_MaskApply(  MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *ApplyMask);
//  Применение масок к ранее считанному состоянию регистров порта
void MDR_Port_MaskApplyEx(MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *ApplyMask, MDR_GPIO_CfgRegs *readRegs);


// ======= Вспомогательные функции, для логгирования и отладки ===========
void MDR_Port_ReadRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_CfgRegs *cfgRegs);
void MDR_Port_WriteRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_CfgRegs *cfgRegs);


//==================================================================================
// ===========  Расширенная реализация c включением тактирования ===================
//==================================================================================

typedef struct {
  // GPIO Port
  MDR_PORT_Type *PORTx;
  // Clock Enable
  volatile uint32_t*      RST_ClockEn_Addr;
  uint32_t       ClockEnaMask;
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


extern const MDR_PinDig_PermRegs PinDig_PermRegsDef;

//  Тактирование блока
__STATIC_INLINE void MDR_GPIO_ClockOn(const MDR_GPIO_Port *GPIO_Port)
{
  REG32(GPIO_Port->RST_ClockEn_Addr) |= GPIO_Port->ClockEnaMask;
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
  #define MDR_GPIO_InitDigPermRegs              MDR_Port_InitDigPermRegs

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


//  Отключение тактирования
__STATIC_INLINE void MDR_GPIO_ClockOff(const MDR_GPIO_Port *GPIO_Port)
{
  REG32(GPIO_Port->RST_ClockEn_Addr) &= ~(1 << GPIO_Port->ClockEnaMask);
}

//===================================



                                     
#endif //  _MDR_GPIO_H
