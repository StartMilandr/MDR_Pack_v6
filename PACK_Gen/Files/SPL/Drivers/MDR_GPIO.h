#ifndef MDR_GPIO_H
#define MDR_GPIO_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>


#define MDR_GPIO_CfgRegs    MDR_PORT_Type__Base

#define GPIO_Pin_0                  0x0001UL  /*!< Pin 0 selected */
#define GPIO_Pin_1                  0x0002UL  /*!< Pin 1 selected */
#define GPIO_Pin_2                  0x0004UL  /*!< Pin 2 selected */
#define GPIO_Pin_3                  0x0008UL  /*!< Pin 3 selected */
#define GPIO_Pin_4                  0x0010UL  /*!< Pin 4 selected */
#define GPIO_Pin_5                  0x0020UL  /*!< Pin 5 selected */
#define GPIO_Pin_6                  0x0040UL  /*!< Pin 6 selected */
#define GPIO_Pin_7                  0x0080UL  /*!< Pin 7 selected */
#define GPIO_Pin_8                  0x0100UL  /*!< Pin 8 selected */
#define GPIO_Pin_9                  0x0200UL  /*!< Pin 9 selected */
#define GPIO_Pin_10                 0x0400UL  /*!< Pin 10 selected */
#define GPIO_Pin_11                 0x0800UL  /*!< Pin 11 selected */
#define GPIO_Pin_12                 0x1000UL  /*!< Pin 12 selected */
#define GPIO_Pin_13                 0x2000UL  /*!< Pin 13 selected */
#define GPIO_Pin_14                 0x4000UL  /*!< Pin 14 selected */
#define GPIO_Pin_15                 0x8000UL  /*!< Pin 15 selected */
#define GPIO_Pin_All                0xFFFFUL  /*!< All pins selected */

// =============================================================================
// =========== Функции настройки портов GPIO, базовая реализация ===============
// =============================================================================

//  Сброс регистров к начальным настройкам. Требуется предварительное включение тактирование порта.
void MDR_Port_Reset(MDR_PORT_Type *GPIO_Port);

// ========================= Доступ к пинам =============================
void MDR_Port_SetPins(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect);
void MDR_Port_ClearPins(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect);
uint32_t MDR_Port_GetPins(MDR_PORT_Type *GPIO_Port);


// =============================== ВАРИАНТ НАСТРОЙКИ 1 ====================================
//  Групповая настрока пинов порта в цифровой или аналоговый режим. Требуется предварительное включение такрирование порта.
//    В cfgRegs задается настройка для младшего пина, которая применяется для всех пинов, выбранных в PinSelect
void MDR_Port_InitDig   (MDR_PORT_Type *GPIO_Port, uint32_t PinSelect, MDR_GPIO_CfgRegs *cfgRegs);
void MDR_Port_InitAnalog(MDR_PORT_Type *GPIO_Port, uint32_t PinSelect);


// =============================== ВАРИАНТ НАСТРОЙКИ 2 ====================================
// Общие настройки для группы битов вынесены в отдельную структуру - MDR_Pin_PermRegs. 
// Остальные, зачастую различающиеся, настройки для одиночных или нескольких пинов задаются при вызове функций
// в параметрах - InOut и Func

typedef enum {
  MDR_Pin_Out,
  MDR_Pin_In,
  MDR_Pin_In_PU,  //  PullUp
  MDR_Pin_In_PD   //  PullDown
} MDR_Pin_IO;

typedef struct {
  uint32_t ANALOG;
  uint32_t PD;
  uint32_t PWR;
  uint32_t GFEN;
} MDR_Pin_PermRegs;

//  Выделение настроек, одинаковых для группы пинов, в отдельную структуру
void MDR_Port_InitPermRegs(MDR_PIN_PD OutDriver, MDR_OnOff InpSchmEn, MDR_PIN_PWR Power, MDR_OnOff InpFilterEn, MDR_Pin_PermRegs *PinPermRegs);

//  Инициализация пинов с дополнительными настройками и групповыми.
void MDR_Port_Init   (MDR_PORT_Type *GPIO_Port, uint32_t PinSelect, MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_Pin_PermRegs *PinPermRegs);
void MDR_Port_InitPin(MDR_PORT_Type *GPIO_Port, uint32_t PinInd   , MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_Pin_PermRegs *PinPermRegs);

//  Конвертация в MDR_GPIO_CfgRegs для вызова первого варианта
void MDR_Port_ToCfgRegs(MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_Pin_PermRegs *PinPermRegs, MDR_GPIO_CfgRegs *cfgRegs);


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
void MDR_Port_MaskAdd(uint32_t PinSelect, MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_Pin_PermRegs *PinPermRegs, MDR_Port_ApplyMask *ApplyMask);
//  Добавление в маски настроек одного пина
void MDR_Port_MaskAddPin(uint32_t BitInd, MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_Pin_PermRegs *PinPermRegs, MDR_Port_ApplyMask *ApplyMask);
//  Применение маски в порт
void MDR_Port_MaskApply(MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *ApplyMask);



// ======= Вспомогательные функции, для логгирования и отладки ===========
void MDR_Port_ReadRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_CfgRegs *cfgRegs);
void MDR_Port_WriteRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_CfgRegs *cfgRegs);


//==================================================================================
// ===========  Расширенная реализация c включением тактирования ===================
//==================================================================================

typedef struct {
  MDR_PORT_Type *PORTx;
  uint32_t       RST_ClockEn_Addr;
  uint32_t       ClockEnaMask;
} MDR_GPIO_Port;

#define GPIO_A                &GPIO_A_Port
#define GPIO_B                &GPIO_B_Port
#define GPIO_C                &GPIO_C_Port
#define GPIO_D                &GPIO_D_Port
#define GPIO_E                &GPIO_E_Port
#define GPIO_F                &GPIO_F_Port
#define GPIO_G                &GPIO_G_Port
#define GPIO_H                &GPIO_H_Port
#define GPIO_I                &GPIO_I_Port

extern const MDR_GPIO_Port    GPIO_A_Port;
extern const MDR_GPIO_Port    GPIO_B_Port;
extern const MDR_GPIO_Port    GPIO_C_Port;
extern const MDR_GPIO_Port    GPIO_D_Port;
extern const MDR_GPIO_Port    GPIO_E_Port;
extern const MDR_GPIO_Port    GPIO_F_Port;
extern const MDR_GPIO_Port    GPIO_G_Port;
extern const MDR_GPIO_Port    GPIO_H_Port;
extern const MDR_GPIO_Port    GPIO_I_Port;

//  Тактирование блока
__STATIC_INLINE void MDR_GPIO_Open(const MDR_GPIO_Port *GPIO_Port)
{
  REG32(GPIO_Port->RST_ClockEn_Addr) |= (1 << GPIO_Port->ClockEnaMask);
}

  //  Аналоги функций базовой реализации, только со структурой MDR_GPIO_Port вместо MDR_PORT_Type

  #define MDR_GPIO_Reset(GP)                  MDR_Port_Reset((GP)->PORTx)

  // Вариант настройки 1
  #define MDR_GPIO_InitDig(GP, Sel, Cfg)      MDR_Port_InitDig((GP)->PORTx, (Sel), (Cfg))
  #define MDR_GPIO_InitAnalog(GP, Sel)        MDR_Port_InitAnalog((GP)->PORTx, (Sel))

void MDR_Port_InitDig   (MDR_PORT_Type *GPIO_Port, uint32_t PinSelect, MDR_GPIO_CfgRegs *cfgRegs);

  // Вариант настройки 2
  #define MDR_GPIO_InitPermRegs               MDR_Port_InitPermRegs

  #define MDR_GPIO_Init(GP, Sel, IO, F, pR)    MDR_Port_Init   ((GP)->PORTx, (Sel), (IO), (F), (pR))
  #define MDR_GPIO_InitPin(GP, Ind, IO, F, pR) MDR_Port_InitPin((GP)->PORTx, (Ind), (IO), (F), (pR))

//  #define MDR_Port_ApplyMask                  MDR_Port_ApplyMask

  #define MDR_GPIO_ToCfgRegs                  MDR_Port_ToCfgRegs
  #define MDR_GPIO_MaskClear                  MDR_Port_MaskClear
  #define MDR_GPIO_MaskAdd                    MDR_Port_MaskAdd
  #define MDR_GPIO_MaskAddPin                 MDR_Port_MaskAddPin
  #define MDR_GPIO_MaskApply(GP, msk)         MDR_Port_MaskApply((GP)->PORTx, (msk))

  // Вспомогательные функции
  #define MDR_GPIO_ReadRegs(GP, CfgRegs)      MDR_Port_ReadRegs((GP)->PORTx, (CfgRegs))
  #define MDR_GPIO_WriteRegs(GP, CfgRegs)     MDR_Port_WriteRegs((GP)->PORTx, (CfgRegs))


//  Отключение тактирования
__STATIC_INLINE void MDR_GPIO_Close(const MDR_GPIO_Port *GPIO_Port)
{
  REG32(GPIO_Port->RST_ClockEn_Addr) &= ~(1 << GPIO_Port->ClockEnaMask);
}

//===================================



                                     
#endif //  MDR_GPIO_H
