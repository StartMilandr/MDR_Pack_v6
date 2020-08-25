#ifndef MDR_1923KX029_M2_STATS_H
#define MDR_1923KX029_M2_STATS_H

#include <MDR_1923KX028.h>
#include <MDR_1923KX028_AXI_defs.h>


//==========================    EMAC Statistics ========================
typedef struct
{
    uint64_t tx_ok;
    uint64_t tx_broadcast;
    uint64_t tx_multicast;
    uint64_t tx_pause;
    uint64_t tx_64;
    uint64_t tx_65_127;
    uint64_t tx_128_255;
    uint64_t tx_256_511;
    uint64_t tx_512_1023;
    uint64_t tx_1024_1518;
    uint64_t tx_more_1518;
    uint64_t tx_underruns;
    uint64_t tx_single_collision;
    uint64_t tx_2_15_collision;
    uint64_t tx_more_15_collision;
    uint64_t tx_late_collision;
    uint64_t tx_deferred;

    uint64_t rx_ok;
    uint64_t rx_broadcast;
    uint64_t rx_multicast;
    uint64_t rx_pause;
    uint64_t rx_64;
    uint64_t rx_65_127;
    uint64_t rx_128_255;
    uint64_t rx_256_511;
    uint64_t rx_512_1023;
    uint64_t rx_1024_1518;
    uint64_t rx_more_1518;
    uint64_t rx_less_64;
    uint64_t rx_excessive_len;
    uint64_t rx_jabbers;
    uint64_t rx_fcs_err;
    uint64_t rx_len_err;
    uint64_t rx_symbol_err;
    uint64_t rx_aligment_err;
    uint64_t rx_recource_err;
    uint64_t rx_overruns;
    uint64_t rx_ip_crc_err;
    uint64_t rx_tcp_crc_err;
    uint64_t rx_udp_crc_err;
    uint64_t rx_dropped;
    
    uint64_t tx_bytes;
    uint64_t rx_bytes;
} MDR_KX028_StatsEMAC_t;

//extern MDR_KX028_StatsEMAC_t    statsEMAC[ KX028_EMAC_NUMS ];

// Считывает статисктику блока eMAC в pStatsEMAC
void MDR_KX028_M2_UpdateStatsEMAC(MDR_KX028_EMAC_e eMAC, MDR_KX028_StatsEMAC_t* pStatsEMAC);


// Считывает статисктику cntToProcess блоков eMAC начиная с индекса nextItemInd в таблице usedEmacTable
typedef struct {
  MDR_KX028_EMAC_e       eMAC;
  MDR_KX028_StatsEMAC_t *pStatBuff;
} MDR_KX028_StatsEMAC_Item;

void MDR_KX028_M2_UpdateStatNextEMACs(MDR_KX028_StatsEMAC_Item *usedEmacTable, uint8_t usedEmacTableLen, uint8_t cntToProcess, uint8_t *nextItemInd);



//==========================    Classif_EMAC Statistics ========================
typedef enum {
    MDR_KX028_STAT_CLASS_RX = 0,
    MDR_KX028_STAT_CLASS_L3_FAIL,
    MDR_KX028_STAT_CLASS_IPV4,
    MDR_KX028_STAT_CLASS_IPV6,
    MDR_KX028_STAT_CLASS_BAD_CRC,
    MDR_KX028_STAT_CLASS_BAD_TTL,
    MDR_KX028_STAT_CLASS_ICMP,
    MDR_KX028_STAT_CLASS_IGMP,
    MDR_KX028_STAT_CLASS_TCP,
    MDR_KX028_STAT_CLASS_UDP,
    //  Count
    MDR_KX028_STAT_CLASS_CNTRS_NUMS,
} MDR_KX028_StatsClassHW_ID;

typedef union
{
    uint64_t data64[ MDR_KX028_STAT_CLASS_CNTRS_NUMS ];
    struct
    {
        uint64_t class_rx;
        uint64_t class_l3_fail;
        uint64_t class_ipv4;
        uint64_t class_ipv6;
        uint64_t class_crc_err;
        uint64_t class_ttl_err;
        uint64_t class_icmp;
        uint64_t class_igmp;
        uint64_t class_tcp;
        uint64_t class_udp;
    };
} MDR_KX028_StatsClassHW_t;


// Считывание счетчика по SPI обнуляет счетчик. Пока SPI выдает считанный счетчик, базис считывает следующий - тем самым обнуляя его.
// Поэтому счетчики можно считать только с последовательно увеличивающимися адресами. 
// Адреса перемешаны, поэтому считать счетчики отдельного ЕМАС не получится, не затронув ближайшие адреса.
// Поэтому статистика вычитывается в глобальную структуру statsClassHW, согласно очередности адресов в таблице classCountersAddrOrder.
extern MDR_KX028_StatsClassHW_t statsClassHW[ KX028_EMAC_NUMS ];

void MDR_KX028_M2_UpdateStatsClassHW(uint32_t selEMACs);


#endif  //MDR_1923KX029_M2_STATS_H
