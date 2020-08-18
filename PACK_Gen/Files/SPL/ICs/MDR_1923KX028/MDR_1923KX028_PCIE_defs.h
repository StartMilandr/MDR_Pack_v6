#ifndef MDR_1923KX028_PCIE_DEFS_H
#define MDR_1923KX028_PCIE_DEFS_H

#include <stdint.h>

// ----------- PCI-совместимое конфигурационное пространство заголовка типа 0 --------------
//#define KX028_PCIE_PF0_TYPE0_HDR              0x000UL

// Регистр ID устройства и производителя
#define KX028_PCIE_DEVICE_ID_VENDOR_ID_REG    0x0 
   #define KX028_PCIE_VENDOR_ID_Pos    0
   #define KX028_PCIE_VENDOR_ID_Msk    0xFFFFUL 
   #define KX028_PCIE_DEVICE_ID_Pos    16
   #define KX028_PCIE_DEVICE_ID_Msk    0xFFFFUL
   
   #define PCIE_DEVICE_VENDOR_ID_FILL(vendID, devID)  _VAL2FLD(KX028_PCIE_VENDOR_ID, vendID) \
                                                    | _VAL2FLD(KX028_PCIE_DEVICE_ID, devID) \

// Регистр управления и статуса
#define KX028_PCIE_STATUS_COMMAND_REG         0x4 

// Регистр кода класса и ревизии ID
#define KX028_PCIE_CLASS_CODE_REVISION_ID     0x8
  #define KX028_PCIE_REVISION_ID_Pos            0
  #define KX028_PCIE_REVISION_ID_Msk            0xFFUL 
  #define KX028_PCIE_PROGRAM_INTERFACE_Pos      8
  #define KX028_PCIE_PROGRAM_INTERFACE_Msk      0xFF00UL
  #define KX028_PCIE_SUBCLASS_CODE_Pos          16
  #define KX028_PCIE_SUBCLASS_CODE_Msk          0xFF0000UL
  #define KX028_PCIE_BASE_CLASS_CODE_Pos        24
  #define KX028_PCIE_BASE_CLASS_CODE_Msk        0xFF000000UL

  #define PCIE_CLASS_CODE_REVISION_ID_FILL(rev, inrt, cls, subcls)  _VAL2FLD(KX028_PCIE_BASE_CLASS_CODE, cls) \
                                                                  | _VAL2FLD(KX028_PCIE_SUBCLASS_CODE, subcls) \
                                                                  | _VAL2FLD(KX028_PCIE_PROGRAM_INTERFACE, inrt) \
                                                                  | _VAL2FLD(KX028_PCIE_REVISION_ID, rev)

// Регистр бист, типа заголовка, размера строки кэша, таймера латентности
// BIST_HEADER_TYPE_LATENCY_CACHE_ LINE_SIZE_REG
#define KX028_PCIE_BIST_CFG_REG               0xС 
// BAR0 и маска BAR
#define KX028_PCIE_BAR0_REG                   0x10 
// BAR2 и маска BAR
#define KX028_PCIE_BAR2_REG                   0x18 
// BAR4 и маска BAR
#define KX028_PCIE_BAR4_REG                   0x20 
// Регистр указателя CardBus CIS
#define KX028_PCIE_CARDBUS_CIS_PTR_REG        0x28  
// Регистр ID подсистемы и ID производителя подсистемы
// SUBSYSTEM_ID_SUBSYSTEM_VENDOR_ ID_REG
#define KX028_PCIE_SUBSYS_VEND_ID_REG         0x2С
// Регистр BAR ПЗУ расширения и маски
#define KX028_PCIE_EXP_ROM_BAR_MASK_REG       0x30 
// Регистр указателя возможностей
#define KX028_PCIE_PCI_CAP_PTR_REG            0x34 
// Регистр линии и вывода прерывания
// MAX_LATENCY_MIN_GRANT_INTERRUPT_ PIN_INTERRUPT_LINE_REG
#define KX028_PCIE_INTERRUPT_LINE_REG         0x3С 


// ----------- Структуры возможностей PCI управления питанием -----------
// #define KX028_PCIE_PF0_PM_CAP         0x040UL

// Регистр возможностей управления питанием
#define KX028_PCIE_CAP_ID_NXT_PTR_REG         0x40
// Регистр контроля и статуса управления питанием
#define KX028_PCIE_CON_STATUS_REG             0x44


// ----------- Структуры MSI возможностей -----------
//#define KX028_PCIE_PF0_MSI_CAP        0x050UL

// Регистр ID возможностей MSI, указателя на следующую структуру, возможностей/контроля
#define KX028_PCIE_PCI_MSI_CAP_ID_NEXT_CTRL_REG 0x50
// Регистр младшего адреса сообщения MSI
#define KX028_PCIE_MSI_CAP_OFF_04H_REG          0x54
// Для 32-битных MSI сообщений, этот регистр содержит данные. Для 64-битных содержит старший адрес
#define KX028_PCIE_MSI_CAP_OFF_08H_REG          0х58
// Для 64-битных MSI сообщений, этот регистр содержит данные. Для 32-битных, содержит биты маски
#define KX028_PCIE_MSI_CAP_OFF_0CH_REG          0х5С



// ----------- Структуры возможностей PCI Express -----------
//#define KX028_PCIE_PF0_PCIE_CAP       0x070UL

// Регистр возможностей PCI Express, ID, указатель на следующую структуру
#define KX028_PCIE_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG 0x70
// Регистр возможностей устройства
#define KX028_PCIE_DEVICE_CAPABILITIES_REG          0x74
// Регистр управления и статуса устройства
#define KX028_PCIE_DEVICE_CONTROL_STATUS            0х78
// Регистр возможностей линка
#define KX028_PCIE_LINK_CAPABILITIES_REG            0х7С
// Регистр управления и статуса линка
#define KX028_PCIE_LINK_CONTROL_STATUS_REG          0х80
// Регистр 2 возможностей устройства
#define KX028_PCIE_DEVICE_CAPABILITIES2_REG         0х94
// Регистр 2 управления и статуса устройства
#define KX028_PCIE_DEVICE_CONTROL2_STATUS2_REG      0х98
// Регистр 2 возможностей линка
#define KX028_PCIE_LINK_CAPABILITIES2_REG           0х9С
// Регистр 2 управления и статуса линка
#define KX028_PCIE_LINK_CONTROL2_STATUS2_REG        0хA0


// ----------- Структуры расширенных возможностей отчета об ошибках -----------
//#define KX028_PCIE_PF0_AER_CAP        0x100UL

// Заголовок расширенных возможностей по формированию рапорта об ошибках
#define KX028_PCIE_AER_EXT_CAP_HDR_OFF              0x100
// Регистр статуса некорректируемых ошибок
#define KX028_PCIE_UNCORR_ERR_STATUS_OFF            0x104
// Регистр маски некорректируемых ошибок
#define KX028_PCIE_UNCORR_ERR_MASK_OFF              0х108
// Регистр степени серьезности некорректируемых ошибок
#define KX028_PCIE_UNCORR_ERR_SEV_OFF               0х10С
// Регистр статуса корректируемых ошибок
#define KX028_PCIE_CORR_ERR_STATUS_OFF              0х110
// Регистр маски корректируемых ошибок
#define KX028_PCIE_CORR_ERR_MASK_OFF                0x114
// Регистр расширенных возможностей и контроля ошибок
#define KX028_PCIE_ADV_ERR_CAP_CTRL_OFF             0х118
// Регистр заголовка лога 0
#define KX028_PCIE_HDR_LOG_0_OFF                    0x11С
// Регистр заголовка лога 1
#define KX028_PCIE_HDR_LOG_1_OFF                    0х120
// Регистр заголовка лога 2
#define KX028_PCIE_HDR_LOG_2_OFF                    0х124
// Регистр заголовка лога 3
#define KX028_PCIE_HDR_LOG_3_OFF                    0х128
// Регистр TLP префикса лога 1
#define KX028_PCIE_TLP_PREFIX_LOG_1_OFF             0х138
// Регистр TLP префикса лога 2
#define KX028_PCIE_TLP_PREFIX_LOG_2_OFF             0х13C
// Регистр TLP префикса лога 3
#define KX028_PCIE_TLP_PREFIX_LOG_3_OFF             0х140
// Регистр TLP префикса лога 4
#define KX028_PCIE_TLP_PREFIX_LOG_4_OFF             0х144






// ----------- Логика порта -----------
// #define KX028_PCIE_PF0_PORT_LOGIC     0x700UL

// Регистр латентности таймера подтверждения и таймера повтора
#define KX028_PCIE_ACK_LATENCY_TIMER_OFF          0x700
// Регистр специфичного DLLP вендора
#define KX028_PCIE_VENDOR_SPEC_DLLP_OFF           0x704
// Регистр принудительного линка порта
#define KX028_PCIE_PORT_FORCE_OFF                 0x708
// Регистр частоты подтверждения и управления L0-L1 ASPM
#define KX028_PCIE_ACK_F_ASPM_CTRL_OFF            0x70c
// Регистр управления линком порта
#define KX028_PCIE_PORT_LINK_CTRL_OFF             0x710
// Регистр разбежки лэйнов
#define KX028_PCIE_LANE_SKEW_OFF                  0x714
// Регистр контроля таймера и количества максимальных функций
#define KX028_PCIE_TIMER_CTRL_MAX_FUNC_NUM_OFF    0x718
// Регистр таймера символа и регистр 1 маски фильтра. Регистр 1 маски фильтра модифицирует RADM фильтрацию
#define KX028_PCIE_SYMBOL_TIMER_FILTER_1_OFF      0x71c
// Регистр 2 маски фильтра. Этот регитср модифицирует RADM фильтрацию и правила обработки ошибок
#define KX028_PCIE_FILTER_MASK_2_OFF              0x720
// Регистр управления многочисленными выходными, разделенными NP подзапросами шины AMBA
#define KX028_PCIE_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF 0x724
// Регистр отладки 0
#define KX028_PCIE_PL_DEBUG0_OFF                  0x728
// Регистр отладки 1
#define KX028_PCIE_PL_DEBUG1_OFF                  0x72c
// Статус FC кредитов отложенных передач
#define KX028_PCIE_TX_P_FC_CREDIT_STATUS_OFF      0x730
// Статус FC кредитов не отложенных передач
#define KX028_PCIE_TX_NP_FC_CREDIT_STATUS_OFF     0x734
// Статус FC кредитов, передаваемых сompletion
#define KX028_PCIE_TX_CPL_FC_CREDIT_STATUS_OFF    0x738
// Статус очереди
#define KX028_PCIE_QUEUE_STATUS_OFF               0x73c
// Регистр 1 арбитража виртуального канала передачи
#define KX028_PCIE_VC_TX_ARBI_1_OFF               0x740
// Регистр 2 арбитража виртуального канала передачи
#define KX028_PCIE_VC_TX_ARBI_2_OFF               0x744
// Управление сегментированным буфером очереди отложенного приема виртуального канала 0
#define KX028_PCIE_VC0_P_RX_Q_CTRL_OFF            0x748
// Управление сегментированным буфером очереди не отложенного приема виртуального канала 0
#define KX028_PCIE_VC0_NP_RX_Q_CTRL_OFF           0x74c
// Управление сегментированным буфером очереди приема сompletion виртуального канала 0
#define KX028_PCIE_VC0_CPL_RX_Q_CTRL_OFF          0x750
// Регистр управления шириной линка и изменением скорости
#define KX028_PCIE_GEN2_CTRL_OFF                  0x80c
// Регистр статуса PHY
#define KX028_PCIE_PHY_STATUS_OFF                 0x810
// Регистр управления PHY
#define KX028_PCIE_PHY_CONTROL_OFF                0x814
// Регистр управления картой программирования заданий
#define KX028_PCIE_TRGT_MAP_CTRL_OFF              0x81c
// Регистр разрешения частоты RADM. Используя этот регистр можно отключить частоту RADM.
#define KX028_PCIE_CLOCK_GATING_CTRL_OFF          0x88c
// Регистр управления порядком правил
#define KX028_PCIE_ORDER_RULE_CTRL_OFF            0x8b4
// Регистр управления обратной связью PIPE
#define KX028_PCIE_PIPE_LOOPBACK_CONTROL_OFF      0x8b8
// Регистр разрешения DBI только для чтения или записи
#define KX028_PCIE_MISC_CONTROL_1_OFF             0x8bc
  // Enable DBI access to RO registers
  #define KX028_PCIE_DBI_RO_WR_EN_MSK      0x1

// Регистр управления мультилэйнами. Используется для увеличения или уменьшения ширины линка.
#define KX028_PCIE_MULTI_LANE_CONTROL_OFF         0x8c0
// Регистр управления функциональной совместимостью PHY. Этот регистр зарезервирован для внутреннего применения.
#define KX028_PCIE_PHY_INTEROP_CTRL_OFF           0x8c4
// Регистр управления удалением записи TRGT_CPL_LUT. Используя этот регистр можно удалить запись в таблице LUT.
#define KX028_PCIE_TRGT_CPL_LUT_DELETE_ENTRY_OFF  0x8c8
// Регистр управления очисткой запроса на сброс линка
#define KX028_PCIE_LINK_FLUSH_CONTROL_OFF         0x8cc
// Регистр ошибки ответа AXI слэйв моста
#define KX028_PCIE_AMBA_ERROR_RESPONSE_DEFAULT_OFF 0x8d0
// Регистр таймаута потери линка AXI слэйв моста. В случае выдачи приложением исходящего запроса на AXI.
#define KX028_PCIE_AMBA_LINK_TIMEOUT_OFF          0x8d4
// Контроль упорядочивания AMBA
#define KX028_PCIE_AMBA_ORDERING_CTRL_OFF         0x8d8
// Регистр управления 1 согласованностью кэша ACE
#define KX028_PCIE_COHERENCY_CONTROL_1_OFF        0x8e0
// Регистр управления 3 согласованностью кэша ACE
#define KX028_PCIE_COHERENCY_CONTROL_3_OFF        0x8e8
// Младшие 20 бит программируемого адреса AXI куда поступают сообщения из маппированной туда шины PCIe
#define KX028_PCIE_AXI_MSTR_MSG_ADDR_LOW_OFF      0x8f0
// Старшие 32 бита программируемого адреса AXI куда поступают сообщения из маппированной туда шины PCIe
#define KX028_PCIE_AXI_MSTR_MSG_ADDR_HIGH_OFF     0x8f4
// Номер версии релиза PCIe контроллера. Номер версии предоставляется в шестнадцатеричном формате.
#define KX028_PCIE_PCIE_VERSION_NUMBER_OFF        0x8f8
// Тип версии релиза PCIe контроллера. Тип предоставляется в шестнадцатеричном формате.
#define KX028_PCIE_PCIE_VERSION_TYPE_OFF          0x8fc
// Регистр управления частотой вспомогательного синхросигнала
#define KX028_PCIE_AUX_CLK_FREQ_OFF               0xb40








// ----------- Структуры модуля трансляции адреса -----------
//#define KX028_PCIE_PF0_ATU_CAP        0x300000UL

// Регистр управления 1 регионом iATU
//  IATU_REGION_CTRL_1_OFF_OUTBOUND_0
#define KX028_PCIE_IATU_REGION_CTRL1_OUT        0x300000
// Регистр управления 2 регионом iATU
//  IATU_REGION_CTRL_2_OFF_OUTBOUND_0 
#define KX028_PCIE_IATU_REGION_CTRL2_OUT        0x300004
// Регистр младшей части базового адреса iATU
//  IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0
#define KX028_PCIE_IATU_LWR_BASE_ADDR0_OUT      0x300008
// Регистр старшей части базового адреса iATU
//  IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0
#define KX028_PCIE_IATU_UPPER_BASE_ADDR1_OUT    0x30000c
// Регистр предельного адреса iATU
//  IATU_LIMIT_ADDR_OFF_OUTBOUND_0
#define KX028_PCIE_IATU_LIMIT_ADDR1_OUT         0x300010
// Регистр младшей части целевого адреса iATU
//  IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0 
#define KX028_PCIE_IATU_LWR_TARGET_ADDR1_OUT    0x300014
// Регистр старшей части целевого адреса iATU
//  IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0
#define KX028_PCIE_IATU_UPPER_TARGET_ADDR1_OUT  0x300018
// Регистр управления 1 регионом iATU
//  IATU_REGION_CTRL_1_OFF_INBOUND_0 
#define KX028_PCIE_IATU_REGION_CTRL1_IN         0x300100
// Регистр управления 2 регионом iATU
//  IATU_REGION_CTRL_2_OFF_INBOUND_0
#define KX028_PCIE_IATU_REGION_CTRL2_IN        0x300104
// Регистр младшей части базового адреса iATU
//  IATU_LWR_BASE_ADDR_OFF_INBOUND_0
#define KX028_PCIE_IATU_LWR_BASE_ADDR1_IN       0x300108
// Регистр старшей части базового адреса iATU
//  IATU_UPPER_BASE_ADDR_OFF_INBOUND_0
#define KX028_PCIE_IATU_UPPER_BASE_ADDR2_IN     0x30010c
// Регистр предельного адреса iATU
//  IATU_LIMIT_ADDR_OFF_INBOUND_0
#define KX028_PCIE_IATU_LIMIT_ADDR1_IN          0x300110
// Регистр младшей части целевого адреса iATU
//  IATU_LWR_TARGET_ADDR_OFF_INBOUND_0
#define KX028_PCIE_IATU_LWR_TARGET_ADDR1_IN     0x300114

  #define KX028_PCIE_IATU_REGN_ADDR_Pos     0 
  #define KX028_PCIE_IATU_REGN_ADDR_Msk     0xFFUL
  #define KX028_PCIE_IATU_REGN_INOUT_Pos    8
  #define KX028_PCIE_IATU_REGN_INOUT_Msk    0x100UL
  #define KX028_PCIE_IATU_REGN_Pos          9
  #define KX028_PCIE_IATU_REGN_Msk          0x1FE00

  #define KX028_PCIE_IATU_REGN_IN_Msk    0x1FE00
  
  #define KX028_PCIE_IATU_REGION_IN_CTRL1_ADDR(region) KX028_PCIE_IATU_REGION_CTRL1_IN     | _VAL2FLD(KX028_PCIE_IATU_REGN, region)
  #define KX028_PCIE_IATU_REGION_IN_CTRL2_ADDR(region) KX028_PCIE_IATU_REGION_CTRL2_IN     | _VAL2FLD(KX028_PCIE_IATU_REGN, region)
  #define KX028_PCIE_IATU_REGION_IN_TARG_ADDR(region)  KX028_PCIE_IATU_LWR_TARGET_ADDR1_IN | _VAL2FLD(KX028_PCIE_IATU_REGN, region)


#endif  //MDR_1923KX028_PCIE_DEFS_H

