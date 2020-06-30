#include <MDR_1923KX028_M2_Stats.h>
#include <MDR_1923KX028_GlobConst.h>


//==========================    EMAC Statistics ========================
//MDR_KX028_StatsEMAC_t    statsEMAC[ KX028_EMAC_NUMS ];

#define MDR_KX028_ReadNextAXI_64   (uint64_t)MDR_KX028_ReadNextAXI

static void MDR_KX028_UpdateStatsEMAC(uint32_t emacBaseAddr, uint32_t egpiBaseAddr, MDR_KX028_StatsEMAC_t *item)
{
    uint64_t bytes = 0, tmp;
    
//  taskENTER_CRITICAL();
  
    MDR_KX028_ReadBeginAXI( emacBaseAddr + 0x100 );
    bytes = MDR_KX028_ReadNextAXI_64();                     // 0x100
    tmp   = MDR_KX028_ReadNextAXI_64();                     // 0x104
    item->tx_bytes      += bytes | (tmp << 32);
    item->tx_ok         += MDR_KX028_ReadNextAXI_64();      // 0x108
    item->tx_broadcast  += MDR_KX028_ReadNextAXI_64();      // 0x10C    
    item->tx_multicast  += MDR_KX028_ReadNextAXI_64();      // 0x110
    item->tx_pause      += MDR_KX028_ReadNextAXI_64();      // 0x114    
    item->tx_64         += MDR_KX028_ReadNextAXI_64();      // 0x118    
    item->tx_65_127     += MDR_KX028_ReadNextAXI_64();      // 0x11C
    item->tx_128_255    += MDR_KX028_ReadNextAXI_64();      // 0x120
    item->tx_256_511    += MDR_KX028_ReadNextAXI_64();      // 0x124    
    item->tx_512_1023   += MDR_KX028_ReadNextAXI_64();      // 0x128
    item->tx_1024_1518  += MDR_KX028_ReadNextAXI_64();      // 0x12C
    item->tx_more_1518  += MDR_KX028_ReadNextAXI_64();      // 0x130
    MDR_KX028_ReadEndAXI();

    MDR_KX028_ReadBeginAXI( emacBaseAddr + 0x138 );    
    item->tx_single_collision   += MDR_KX028_ReadNextAXI_64();  // 0x138
    item->tx_2_15_collision     += MDR_KX028_ReadNextAXI_64();  // 0x13C
    item->tx_more_15_collision  += MDR_KX028_ReadNextAXI_64();  // 0x140
    item->tx_late_collision     += MDR_KX028_ReadNextAXI_64();  // 0x144
    item->tx_deferred           += MDR_KX028_ReadNextAXI_64();  // 0x148
    MDR_KX028_ReadEndAXI();
    
    MDR_KX028_ReadBeginAXI( emacBaseAddr + 0x150 );    
    bytes = MDR_KX028_ReadNextAXI_64();                     // 0x150
    tmp   = MDR_KX028_ReadNextAXI_64();                     // 0x154
    item->rx_bytes        += bytes | (tmp << 32); 
    item->rx_ok           += MDR_KX028_ReadNextAXI_64();    // 0x158
    item->rx_broadcast    += MDR_KX028_ReadNextAXI_64();    // 0x15C
    item->rx_multicast    += MDR_KX028_ReadNextAXI_64();    // 0x160
    item->rx_pause        += MDR_KX028_ReadNextAXI_64();    // 0x164
    item->rx_64           += MDR_KX028_ReadNextAXI_64();    // 0x168
    item->rx_65_127       += MDR_KX028_ReadNextAXI_64();    // 0x16C
    item->rx_128_255      += MDR_KX028_ReadNextAXI_64();    // 0x170
    item->rx_256_511      += MDR_KX028_ReadNextAXI_64();    // 0x174
    item->rx_512_1023     += MDR_KX028_ReadNextAXI_64();    // 0x178
    item->rx_1024_1518    += MDR_KX028_ReadNextAXI_64();    // 0x17C
    item->rx_more_1518    += MDR_KX028_ReadNextAXI_64();    // 0x180
    item->rx_less_64      += MDR_KX028_ReadNextAXI_64();    // 0x184
    item->rx_excessive_len+= MDR_KX028_ReadNextAXI_64();    // 0x188
    item->rx_jabbers      += MDR_KX028_ReadNextAXI_64();    // 0x18C
    item->rx_fcs_err      += MDR_KX028_ReadNextAXI_64();    // 0x190
    item->rx_len_err      += MDR_KX028_ReadNextAXI_64();    // 0x194
    item->rx_symbol_err   += MDR_KX028_ReadNextAXI_64();    // 0x198
    item->rx_aligment_err += MDR_KX028_ReadNextAXI_64();    // 0x19C
    item->rx_recource_err += MDR_KX028_ReadNextAXI_64();    // 0x1A0
    item->rx_overruns     += MDR_KX028_ReadNextAXI_64();    // 0x1A4
    item->rx_ip_crc_err   += MDR_KX028_ReadNextAXI_64();    // 0x1A8    
    item->rx_tcp_crc_err  += MDR_KX028_ReadNextAXI_64();    // 0x1AC
    item->rx_udp_crc_err  += MDR_KX028_ReadNextAXI_64();    // 0x1B0    
    MDR_KX028_ReadEndAXI();
    
    item->rx_dropped = MDR_KX028_ReadAXI( egpiBaseAddr + 0x06C );
    
//    taskEXIT_CRITICAL();
}


void MDR_KX028_M2_UpdateStatsEMAC(MDR_KX028_EMAC_e eMAC, MDR_KX028_StatsEMAC_t* pStatsEMAC)
{
  MDR_KX028_UpdateStatsEMAC(MDR_KX028_AxiAddrEMAC[eMAC], MDR_KX028_AxiAddrEGPI[eMAC], pStatsEMAC);  
}

MDR_KX028_EMAC_e MDR_KX028_M2_UpdateStatNextEMACs(uint32_t cntToProcess, MDR_KX028_EMAC_e nextEMAC, uint32_t statsEMAC_ArrLen, MDR_KX028_StatsEMAC_t* statsEMAC_Arr)
{ 
  uint32_t i;
  for (i = 0; i < cntToProcess; i++)
  {
    MDR_KX028_M2_UpdateStatsEMAC(nextEMAC, &(statsEMAC_Arr[nextEMAC]));
    nextEMAC += 1;
    if (nextEMAC >= statsEMAC_ArrLen)
      nextEMAC = KX028_EMAC1;    
  }
  
  return nextEMAC;
}

////  Return True if last MAC processed
//bool MDR_KX028_M2_UpdateStatsNextEMAC(void)
//{
//  static uint32_t activeEMAC = 0;
// 
//  MDR_KX028_UpdateStatsEMAC(MDR_KX028_AxiAddrEMAC[activeEMAC], MDR_KX028_AxiAddrEGPI[activeEMAC], &(statsEMAC[activeEMAC]));
//  
//  activeEMAC += 1;
//  if (activeEMAC >= KX028_EMAC_NUMS)
//  {
//    activeEMAC = 0;
//    return true;
//  }
//  else
//    return false;
//}


//==========================    Classif_EMAC Statistics ========================
#define CLASS_RX          MDR_KX028_STAT_CLASS_RX
#define CLASS_L3_FAIL     MDR_KX028_STAT_CLASS_L3_FAIL
#define CLASS_IPV4        MDR_KX028_STAT_CLASS_IPV4
#define CLASS_IPV6        MDR_KX028_STAT_CLASS_IPV6
#define CLASS_BAD_CRC     MDR_KX028_STAT_CLASS_BAD_CRC
#define CLASS_BAD_TTL     MDR_KX028_STAT_CLASS_BAD_TTL
#define CLASS_ICMP        MDR_KX028_STAT_CLASS_ICMP
#define CLASS_IGMP        MDR_KX028_STAT_CLASS_IGMP
#define CLASS_TCP         MDR_KX028_STAT_CLASS_TCP
#define CLASS_UDP         MDR_KX028_STAT_CLASS_UDP
//  Count
#define CLASS_CNTRS_NUMS  MDR_KX028_STAT_CLASS_CNTRS_NUMS

#define EM1     KX028_EMAC1
#define EM2     KX028_EMAC2
#define EM3     KX028_EMAC3
#define EM4     KX028_EMAC4
#define EM5     KX028_EMAC5
#define EM6     KX028_EMAC6
#define EM7     KX028_EMAC7
#define EM8     KX028_EMAC8
#define EM9     KX028_EMAC9
#define EM10    KX028_EMAC10
#define EM11    KX028_EMAC11
#define EM12    KX028_EMAC12
#define EM13    KX028_EMAC13
#define EM14    KX028_EMAC14
#define EM15    KX028_EMAC15
#define EM16    KX028_EMAC16

typedef struct
{
    uint16_t                    usAddr;
    MDR_KX028_EMAC_e            eEmac;
    MDR_KX028_StatsClassHW_ID   eCounter;
}class_cnt_t;

// Адреса расположены в порядке возрастания
const class_cnt_t classCountersAddrOrder[ KX028_EMAC_NUMS * CLASS_CNTRS_NUMS ] =
{
    { 0x11C, EM1, CLASS_RX },
    
    { 0x130, EM1, CLASS_L3_FAIL },
    { 0x134, EM1, CLASS_IPV4 },
    { 0x138, EM1, CLASS_IPV6 },   
    { 0x13C, EM1, CLASS_BAD_CRC },   
    { 0x140, EM1, CLASS_BAD_TTL },    
    { 0x144, EM2, CLASS_RX },   
   
    { 0x158, EM2, CLASS_L3_FAIL },
    { 0x15C, EM2, CLASS_IPV4 },
    { 0x160, EM2, CLASS_IPV6 },   
    { 0x164, EM2, CLASS_BAD_CRC },   
    { 0x168, EM2, CLASS_BAD_TTL },
    { 0x16C, EM3, CLASS_RX },    
    
    { 0x180, EM3, CLASS_L3_FAIL },
    { 0x184, EM3, CLASS_IPV4 },
    { 0x188, EM3, CLASS_IPV6 },   
    { 0x18C, EM3, CLASS_BAD_CRC },   
    { 0x190, EM3, CLASS_BAD_TTL },     
    { 0x194, EM1, CLASS_ICMP },   
    { 0x198, EM1, CLASS_IGMP },   
    { 0x19C, EM1, CLASS_TCP },  
    { 0x1A0, EM1, CLASS_UDP },  
    { 0x1A4, EM2, CLASS_ICMP },   
    { 0x1A8, EM2, CLASS_IGMP },   
    { 0x1AC, EM2, CLASS_TCP },  
    { 0x1B0, EM2, CLASS_UDP },   
    { 0x1B4, EM3, CLASS_ICMP },   
    { 0x1B8, EM3, CLASS_IGMP },   
    { 0x1BC, EM3, CLASS_TCP },  
    { 0x1C0, EM3, CLASS_UDP },     
    { 0x1C4, EM4, CLASS_ICMP },   
    { 0x1C8, EM4, CLASS_IGMP },   
    { 0x1CC, EM4, CLASS_TCP }, 
    { 0x1D0, EM4, CLASS_UDP },    
    { 0x1D4, EM4, CLASS_RX },
    
    { 0x1E8, EM4, CLASS_L3_FAIL },
    { 0x1EC, EM4, CLASS_IPV4 },
    { 0x1F0, EM4, CLASS_IPV6 },   
    { 0x1F4, EM4, CLASS_BAD_CRC },   
    { 0x1F8, EM4, CLASS_BAD_TTL },    
 
    { 0x298, EM5, CLASS_RX },
    
    { 0x2AC, EM5, CLASS_L3_FAIL },
    { 0x2B0, EM5, CLASS_IPV4 },
    { 0x2B4, EM5, CLASS_IPV6 },   
    { 0x2B8, EM5, CLASS_BAD_CRC },   
    { 0x2BC, EM5, CLASS_BAD_TTL },    
    { 0x2C0, EM5, CLASS_ICMP },   
    { 0x2C4, EM5, CLASS_IGMP },   
    { 0x2C8, EM5, CLASS_TCP },  
    { 0x2CC, EM5, CLASS_UDP },    
    { 0x2D0, EM6, CLASS_RX },
    
    { 0x2E4, EM6, CLASS_L3_FAIL },
    { 0x2E8, EM6, CLASS_IPV4 },
    { 0x2EC, EM6, CLASS_IPV6 },   
    { 0x2F0, EM6, CLASS_BAD_CRC },   
    { 0x2F4, EM6, CLASS_BAD_TTL },    
    { 0x2F8, EM6, CLASS_ICMP },   
    { 0x2FC, EM6, CLASS_IGMP },   
    { 0x300, EM6, CLASS_TCP },  
    { 0x304, EM6, CLASS_UDP },    
    { 0x308, EM7, CLASS_RX },

    { 0x31C, EM7, CLASS_L3_FAIL },
    { 0x320, EM7, CLASS_ICMP },   
    { 0x324, EM7, CLASS_IGMP },   
    { 0x328, EM7, CLASS_TCP },  
    { 0x32C, EM7, CLASS_UDP },    
    { 0x330, EM8, CLASS_RX },    
    
    { 0x344, EM8, CLASS_L3_FAIL },
    { 0x348, EM8, CLASS_IPV4 },
    { 0x34C, EM8, CLASS_IPV6 },   
    { 0x350, EM8, CLASS_BAD_CRC },   
    { 0x354, EM8, CLASS_BAD_TTL },    
    { 0x358, EM8, CLASS_ICMP },   
    { 0x35C, EM8, CLASS_IGMP },   
    { 0x360, EM8, CLASS_TCP },  
    { 0x364, EM8, CLASS_UDP },   
    
    { 0x4E8, EM7, CLASS_IPV4 },
    { 0x4EC, EM7, CLASS_IPV6 },   
    { 0x4F0, EM7, CLASS_BAD_CRC },   
    { 0x4F4, EM7, CLASS_BAD_TTL },    
   
    { 0x5F0, EM9, CLASS_RX },
   
    { 0x604, EM9, CLASS_L3_FAIL },
    { 0x608, EM9, CLASS_IPV4 },
    { 0x60C, EM9, CLASS_IPV6 },   
    { 0x610, EM9, CLASS_BAD_CRC },   
    { 0x614, EM9, CLASS_BAD_TTL },    
    { 0x618, EM10, CLASS_RX },
    
    { 0x62C, EM10, CLASS_L3_FAIL },
    { 0x630, EM10, CLASS_IPV4 },
    { 0x634, EM10, CLASS_IPV6 },   
    { 0x638, EM10, CLASS_BAD_CRC },   
    { 0x63C, EM10, CLASS_BAD_TTL },  
    { 0x640, EM11, CLASS_RX },
    
    { 0x654, EM11, CLASS_L3_FAIL },
    { 0x658, EM11, CLASS_IPV4 },
    { 0x65C, EM11, CLASS_IPV6 },   
    { 0x660, EM11, CLASS_BAD_CRC },   
    { 0x664, EM11, CLASS_BAD_TTL },     
    { 0x668, EM12, CLASS_RX },

    { 0x67C, EM12, CLASS_L3_FAIL },
    { 0x680, EM12, CLASS_IPV4 },
    { 0x684, EM12, CLASS_IPV6 },   
    { 0x688, EM12, CLASS_BAD_CRC },   
    { 0x68C, EM12, CLASS_BAD_TTL },    
    { 0x690, EM13, CLASS_RX },    

    { 0x6A4, EM13, CLASS_L3_FAIL },
    { 0x6A8, EM13, CLASS_IPV4 },
    { 0x6AC, EM13, CLASS_IPV6 },   
    { 0x6B0, EM13, CLASS_BAD_CRC },   
    { 0x6B4, EM13, CLASS_BAD_TTL },
    { 0x6B8, EM14, CLASS_RX },
 
    { 0x6CC, EM14, CLASS_L3_FAIL },
    { 0x6D0, EM14, CLASS_IPV4 },
    { 0x6D4, EM14, CLASS_IPV6 },   
    { 0x6D8, EM14, CLASS_BAD_CRC },   
    { 0x6DC, EM14, CLASS_BAD_TTL },    
    { 0x6E0, EM15, CLASS_RX },
    
    { 0x6F4, EM15, CLASS_L3_FAIL },
    { 0x6F8, EM15, CLASS_IPV4 },
    { 0x6FC, EM15, CLASS_IPV6 },   
    { 0x700, EM15, CLASS_BAD_CRC },   
    { 0x704, EM15, CLASS_BAD_TTL },    
    { 0x708, EM16, CLASS_RX },
 
    { 0x71C, EM16, CLASS_L3_FAIL },
    { 0x720, EM16, CLASS_IPV4 },
    { 0x724, EM16, CLASS_IPV6 },   
    { 0x728, EM16, CLASS_BAD_CRC },   
    { 0x72C, EM16, CLASS_BAD_TTL },    
    
    { 0x758, EM9, CLASS_ICMP },   
    { 0x75C, EM9, CLASS_IGMP },   
    { 0x760, EM9, CLASS_TCP },  
    { 0x764, EM9, CLASS_UDP }, 
    { 0x768, EM10, CLASS_ICMP },   
    { 0x76C, EM10, CLASS_IGMP },   
    { 0x770, EM10, CLASS_TCP },  
    { 0x774, EM10, CLASS_UDP },   
    { 0x778, EM11, CLASS_ICMP },   
    { 0x77C, EM11, CLASS_IGMP },   
    { 0x780, EM11, CLASS_TCP },  
    { 0x784, EM11, CLASS_UDP },     
    { 0x788, EM12, CLASS_ICMP },   
    { 0x78C, EM12, CLASS_IGMP },   
    { 0x790, EM12, CLASS_TCP },  
    { 0x794, EM12, CLASS_UDP }, 
    { 0x798, EM13, CLASS_ICMP },   
    { 0x79C, EM13, CLASS_IGMP },   
    { 0x7A0, EM13, CLASS_TCP },  
    { 0x7A4, EM13, CLASS_UDP },
    { 0x7A8, EM14, CLASS_ICMP },   
    { 0x7AC, EM14, CLASS_IGMP },   
    { 0x7B0, EM14, CLASS_TCP },  
    { 0x7B4, EM14, CLASS_UDP },
    { 0x7B8, EM15, CLASS_ICMP },   
    { 0x7BC, EM15, CLASS_IGMP },   
    { 0x7C0, EM15, CLASS_TCP },  
    { 0x7C4, EM15, CLASS_UDP },
    { 0x7C8, EM16, CLASS_ICMP },   
    { 0x7CC, EM16, CLASS_IGMP },   
    { 0x7D0, EM16, CLASS_TCP },  
    { 0x7D4, EM16, CLASS_UDP }, 
};


MDR_KX028_StatsClassHW_t statsClassHW[ KX028_EMAC_NUMS ];

void MDR_KX028_M2_UpdateStatsClassHW(uint32_t selEMACs)
{
    uint32_t ulClassBase, ulClassConfig, ulData;
    uint8_t  i, ucClassNum;
    uint32_t rdAddr;
    uint32_t emac, emacSel, ecntr;
    
//    taskENTER_CRITICAL();
    
    ulClassConfig = MDR_KX028_ReadAXI(AXI_WSP_GLOBAL_BASE_ADDR + AXI_WSP_EMAC_CLASS_CONFIG); // 0 - CLASS1, 1 - CLASS2
    
    ulClassBase = AXI_CLASS_HW1_BASE_ADDR;
    for( ucClassNum = 0; ucClassNum < 2; ucClassNum++ )
    {        
        //  OpenRead for pass first: "if (rdAddr != axiLastAddr + 4)"       
        for( i = 0; i < ( KX028_EMAC_NUMS * CLASS_CNTRS_NUMS ); i++ )
        {
            emac = classCountersAddrOrder[i].eEmac;
            emacSel = 1 << emac;
            if (selEMACs & emacSel)
              if ((ulClassConfig & emacSel) == (ucClassNum << emac)) 
              {
                rdAddr = ulClassBase + classCountersAddrOrder[i].usAddr;
                ecntr = classCountersAddrOrder[i].eCounter;
                
                ulData = MDR_KX028_ReadSequence(rdAddr);
                statsClassHW[ emac ].data64[ ecntr ] += ulData;
              }
        }        
        //  Repeat the same for CLASS_HW2
        ulClassBase = AXI_CLASS_HW2_BASE_ADDR;
    }
    MDR_KX028_ReadSequenceStop();
    
//    taskEXIT_CRITICAL();
}


//==========================    Read Classif_EMAC by Items  ========================
// Считывание счетчика по SPI обнуляет счетчик. Пока SPI выдает считанный счетчик, базис считывает следующий - тем самым обнуляя его.
// Поэтому счетчики можно считать только с последовательно увеличивающимися адресами. 
// Адреса перемешаны, поэтому считать счетчики отдельного ЕМАС не получится, не затронув ближайшие адреса.
// Поэтому статистика вычитывается в глобальную структуру, согласно очередности адресов в таблице classCountersAddrOrder.

//const uint32_t _ClassStatAddr[KX028_EMAC_NUMS][CLASS_CNTRS_NUMS] = {
//  // EMAC1
//  {
//    AXI_CLASS_PHY1_RX_PKTS,         //MDR_KX028_STAT_CLASS_RX = 0,
//    AXI_CLASS_PHY1_L3_FAIL_PKTS,    //MDR_KX028_STAT_CLASS_L3_FAIL,
//    AXI_CLASS_PHY1_V4_PKTS,         //MDR_KX028_STAT_CLASS_IPV4,
//    AXI_CLASS_PHY1_V6_PKTS,         //MDR_KX028_STAT_CLASS_IPV6,
//    AXI_CLASS_PHY1_CHKSUM_ERR_PKTS, //MDR_KX028_STAT_CLASS_BAD_CRC,
//    AXI_CLASS_PHY1_TTL_ERR_PKTS,    //MDR_KX028_STAT_CLASS_BAD_TTL,
//    AXI_CLASS_PHY1_ICMP_PKTS,       //MDR_KX028_STAT_CLASS_ICMP,
//    AXI_CLASS_PHY1_IGMP_PKTS,       //MDR_KX028_STAT_CLASS_IGMP,
//    AXI_CLASS_PHY1_TCP_PKTS,        //MDR_KX028_STAT_CLASS_TCP,
//    AXI_CLASS_PHY1_UDP_PKTS,        //MDR_KX028_STAT_CLASS_UDP,  
//  },
//  // EMAC2
//  {
//    AXI_CLASS_PHY2_RX_PKTS,
//    AXI_CLASS_PHY2_L3_FAIL_PKTS,
//    AXI_CLASS_PHY2_V4_PKTS,
//    AXI_CLASS_PHY2_V6_PKTS,
//    AXI_CLASS_PHY2_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY2_TTL_ERR_PKTS,
//    AXI_CLASS_PHY2_ICMP_PKTS,
//    AXI_CLASS_PHY2_IGMP_PKTS,
//    AXI_CLASS_PHY2_TCP_PKTS,
//    AXI_CLASS_PHY2_UDP_PKTS,
//  },
//  // EMAC3
//  {
//    AXI_CLASS_PHY3_RX_PKTS,
//    AXI_CLASS_PHY3_L3_FAIL_PKTS,
//    AXI_CLASS_PHY3_V4_PKTS,
//    AXI_CLASS_PHY3_V6_PKTS,
//    AXI_CLASS_PHY3_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY3_TTL_ERR_PKTS,
//    AXI_CLASS_PHY3_ICMP_PKTS,
//    AXI_CLASS_PHY3_IGMP_PKTS,
//    AXI_CLASS_PHY3_TCP_PKTS,
//    AXI_CLASS_PHY3_UDP_PKTS,
//  },
//  // EMAC4
//  {
//    AXI_CLASS_PHY4_RX_PKTS,
//    AXI_CLASS_PHY4_L3_FAIL_PKTS,
//    AXI_CLASS_PHY4_V4_PKTS,
//    AXI_CLASS_PHY4_V6_PKTS,
//    AXI_CLASS_PHY4_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY4_TTL_ERR_PKTS,
//    AXI_CLASS_PHY4_ICMP_PKTS,
//    AXI_CLASS_PHY4_IGMP_PKTS,
//    AXI_CLASS_PHY4_TCP_PKTS,
//    AXI_CLASS_PHY4_UDP_PKTS,
//  },
//  // EMAC5
//  {
//    AXI_CLASS_PHY5_RX_PKTS,
//    AXI_CLASS_PHY5_L3_FAIL_PKTS,
//    AXI_CLASS_PHY5_V4_PKTS,
//    AXI_CLASS_PHY5_V6_PKTS,
//    AXI_CLASS_PHY5_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY5_TTL_ERR_PKTS,
//    AXI_CLASS_PHY5_ICMP_PKTS,
//    AXI_CLASS_PHY5_IGMP_PKTS,
//    AXI_CLASS_PHY5_TCP_PKTS,
//    AXI_CLASS_PHY5_UDP_PKTS,
//  },
//  // EMAC6
//  {
//    AXI_CLASS_PHY6_RX_PKTS,
//    AXI_CLASS_PHY6_L3_FAIL_PKTS,
//    AXI_CLASS_PHY6_V4_PKTS,
//    AXI_CLASS_PHY6_V6_PKTS,
//    AXI_CLASS_PHY6_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY6_TTL_ERR_PKTS,
//    AXI_CLASS_PHY6_ICMP_PKTS,
//    AXI_CLASS_PHY6_IGMP_PKTS,
//    AXI_CLASS_PHY6_TCP_PKTS,
//    AXI_CLASS_PHY6_UDP_PKTS,
//  },
//  // EMAC7
//  {
//    AXI_CLASS_PHY7_RX_PKTS,
//    AXI_CLASS_PHY7_L3_FAIL_PKTS,
//    AXI_CLASS_PHY7_V4_PKTS,
//    AXI_CLASS_PHY7_V6_PKTS,
//    AXI_CLASS_PHY7_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY7_TTL_ERR_PKTS,
//    AXI_CLASS_PHY7_ICMP_PKTS,
//    AXI_CLASS_PHY7_IGMP_PKTS,
//    AXI_CLASS_PHY7_TCP_PKTS,
//    AXI_CLASS_PHY7_UDP_PKTS,
//  },
//  // EMAC8
//  {
//    AXI_CLASS_PHY8_RX_PKTS,
//    AXI_CLASS_PHY8_L3_FAIL_PKTS,
//    AXI_CLASS_PHY8_V4_PKTS,
//    AXI_CLASS_PHY8_V6_PKTS,
//    AXI_CLASS_PHY8_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY8_TTL_ERR_PKTS,
//    AXI_CLASS_PHY8_ICMP_PKTS,
//    AXI_CLASS_PHY8_IGMP_PKTS,
//    AXI_CLASS_PHY8_TCP_PKTS,
//    AXI_CLASS_PHY8_UDP_PKTS,
//  },
//  // EMAC9
//  {
//    AXI_CLASS_PHY9_RX_PKTS,
//    AXI_CLASS_PHY9_L3_FAIL_PKTS,
//    AXI_CLASS_PHY9_V4_PKTS,
//    AXI_CLASS_PHY9_V6_PKTS,
//    AXI_CLASS_PHY9_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY9_TTL_ERR_PKTS,
//    AXI_CLASS_PHY9_ICMP_PKTS,
//    AXI_CLASS_PHY9_IGMP_PKTS,
//    AXI_CLASS_PHY9_TCP_PKTS,
//    AXI_CLASS_PHY9_UDP_PKTS,
//  },
//  // EMAC10
//  {
//    AXI_CLASS_PHY10_RX_PKTS,
//    AXI_CLASS_PHY10_L3_FAIL_PKTS,
//    AXI_CLASS_PHY10_V4_PKTS,
//    AXI_CLASS_PHY10_V6_PKTS,
//    AXI_CLASS_PHY10_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY10_TTL_ERR_PKTS,
//    AXI_CLASS_PHY10_ICMP_PKTS,
//    AXI_CLASS_PHY10_IGMP_PKTS,
//    AXI_CLASS_PHY10_TCP_PKTS,
//    AXI_CLASS_PHY10_UDP_PKTS,
//  },
//  // EMAC11
//  {
//    AXI_CLASS_PHY11_RX_PKTS,
//    AXI_CLASS_PHY11_L3_FAIL_PKTS,
//    AXI_CLASS_PHY11_V4_PKTS,
//    AXI_CLASS_PHY11_V6_PKTS,
//    AXI_CLASS_PHY11_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY11_TTL_ERR_PKTS,
//    AXI_CLASS_PHY11_ICMP_PKTS,
//    AXI_CLASS_PHY11_IGMP_PKTS,
//    AXI_CLASS_PHY11_TCP_PKTS,
//    AXI_CLASS_PHY11_UDP_PKTS,
//  },
//  // EMAC12
//  {
//    AXI_CLASS_PHY12_RX_PKTS,
//    AXI_CLASS_PHY12_L3_FAIL_PKTS,
//    AXI_CLASS_PHY12_V4_PKTS,
//    AXI_CLASS_PHY12_V6_PKTS,
//    AXI_CLASS_PHY12_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY12_TTL_ERR_PKTS,
//    AXI_CLASS_PHY12_ICMP_PKTS,
//    AXI_CLASS_PHY12_IGMP_PKTS,
//    AXI_CLASS_PHY12_TCP_PKTS,
//    AXI_CLASS_PHY12_UDP_PKTS,
//  },
//  // EMAC13
//  {
//    AXI_CLASS_PHY13_RX_PKTS,
//    AXI_CLASS_PHY13_L3_FAIL_PKTS,
//    AXI_CLASS_PHY13_V4_PKTS,
//    AXI_CLASS_PHY13_V6_PKTS,
//    AXI_CLASS_PHY13_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY13_TTL_ERR_PKTS,
//    AXI_CLASS_PHY13_ICMP_PKTS,
//    AXI_CLASS_PHY13_IGMP_PKTS,
//    AXI_CLASS_PHY13_TCP_PKTS,
//    AXI_CLASS_PHY13_UDP_PKTS,
//  },
//  // EMAC14
//  {
//    AXI_CLASS_PHY14_RX_PKTS,
//    AXI_CLASS_PHY14_L3_FAIL_PKTS,
//    AXI_CLASS_PHY14_V4_PKTS,
//    AXI_CLASS_PHY14_V6_PKTS,
//    AXI_CLASS_PHY14_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY14_TTL_ERR_PKTS,
//    AXI_CLASS_PHY14_ICMP_PKTS,
//    AXI_CLASS_PHY14_IGMP_PKTS,
//    AXI_CLASS_PHY14_TCP_PKTS,
//    AXI_CLASS_PHY14_UDP_PKTS,
//  },
//  // EMAC15
//  {
//    AXI_CLASS_PHY15_RX_PKTS,
//    AXI_CLASS_PHY15_L3_FAIL_PKTS,
//    AXI_CLASS_PHY15_V4_PKTS,
//    AXI_CLASS_PHY15_V6_PKTS,
//    AXI_CLASS_PHY15_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY15_TTL_ERR_PKTS,
//    AXI_CLASS_PHY15_ICMP_PKTS,
//    AXI_CLASS_PHY15_IGMP_PKTS,
//    AXI_CLASS_PHY15_TCP_PKTS,
//    AXI_CLASS_PHY15_UDP_PKTS,
//  },
//  // EMAC16
//  {
//    AXI_CLASS_PHY16_RX_PKTS,
//    AXI_CLASS_PHY16_L3_FAIL_PKTS,
//    AXI_CLASS_PHY16_V4_PKTS,
//    AXI_CLASS_PHY16_V6_PKTS,
//    AXI_CLASS_PHY16_CHKSUM_ERR_PKTS,
//    AXI_CLASS_PHY16_TTL_ERR_PKTS,
//    AXI_CLASS_PHY16_ICMP_PKTS,
//    AXI_CLASS_PHY16_IGMP_PKTS,
//    AXI_CLASS_PHY16_TCP_PKTS,
//    AXI_CLASS_PHY16_UDP_PKTS,
//  },
//};

//void MDR_KX028_M2_UpdateStatsClassHW_Ex(MDR_KX028_EMAC_e eMAC, MDR_KX028_StatsClassHW_t *stats)
//{
//    uint32_t ulClassBase, ulClassConfig, ulData;
//    uint8_t  ucI, ucClassNum;
//    uint32_t rdAddr, axiLastAddr;
//    uint32_t emac, ecntr;
//  
//    bool isClassMatchWSP;
//    uint32_t updStats[MDR_KX028_STAT_CLASS_CNTRS_NUMS];
//    
////    taskENTER_CRITICAL();
//    
//    ulClassConfig = MDR_KX028_ReadAXI(AXI_WSP_GLOBAL_BASE_ADDR + AXI_WSP_EMAC_CLASS_CONFIG);// 0 - CLASS1, 1 - CLASS2
//    if (ulClassConfig & ( 1 << emac ))
//      MDR_KX028_ReadByAddrList(MDR_KX028_STAT_CLASS_CNTRS_NUMS, AXI_CLASS_HW2_BASE_ADDR, _ClassStatAddr[eMAC], updStats);
//    else
//      MDR_KX028_ReadByAddrList(MDR_KX028_STAT_CLASS_CNTRS_NUMS, AXI_CLASS_HW1_BASE_ADDR, _ClassStatAddr[eMAC], updStats); 
//    
//    //  Collect statistics   
//    uint32_t i;
//    for (i = 0; i < MDR_KX028_STAT_CLASS_CNTRS_NUMS; i++)
//      stats->data64[i] += updStats[i];
//    
////    taskEXIT_CRITICAL();
//}











