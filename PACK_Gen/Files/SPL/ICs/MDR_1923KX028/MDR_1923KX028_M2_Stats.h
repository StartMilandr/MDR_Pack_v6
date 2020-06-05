#ifndef MDR_1923KX029_M2_STATS_H
#define MDR_1923KX029_M2_STATS_H

#include <MDR_1923KX028.h>
#include <MDR_1923KX028_AXI_defs.h>


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

typedef enum
{
    MDR_KX028_STAT_ID_CLASS_RX = 0,
    MDR_KX028_STAT_ID_CLASS_L3_FAIL,
    MDR_KX028_STAT_ID_CLASS_IPV4,
    MDR_KX028_STAT_ID_CLASS_IPV6,
    MDR_KX028_STAT_ID_CLASS_BAD_CRC,
    MDR_KX028_STAT_ID_CLASS_BAD_TTL,
    MDR_KX028_STAT_ID_CLASS_ICMP,
    MDR_KX028_STAT_ID_CLASS_IGMP,
    MDR_KX028_STAT_ID_CLASS_TCP,
    MDR_KX028_STAT_ID_CLASS_UDP,
    //  Count
    MDR_KX028_STAT_ID_CLASS_CNTRS_NUMS,
} MDR_KX028_StatsClassHW_ID;

typedef union
{
    uint64_t ullData[ MDR_KX028_STAT_ID_CLASS_CNTRS_NUMS ];
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

//extern MDR_KX028_StatsEMAC_t    statsEMAC[ KX028_EMAC_NUMS ];
extern MDR_KX028_StatsClassHW_t statsClassHW[ KX028_EMAC_NUMS ];

// Считывает статисктику блока eMAC в pStatsEMAC
void MDR_KX028_M2_UpdateStatsEMAC(MDR_KX028_EMAC_e eMAC, MDR_KX028_StatsEMAC_t* pStatsEMAC);
// Считывает статисктику cntToProcess блоков eMAC в массив statsEMAC_Arr длиной statsEMAC_ArrLen, начиная с nextEMAC
// Возвращает nextEMAC для следующего вызова
MDR_KX028_EMAC_e MDR_KX028_M2_UpdateStatNextEMACs(uint32_t cntToProcess, MDR_KX028_EMAC_e nextEMAC, uint32_t statsEMAC_ArrLen, MDR_KX028_StatsEMAC_t* statsEMAC_Arr);



void MDR_KX028_M2_UpdateStatsClassHW(void);


#endif  //MDR_1923KX029_M2_STATS_H
