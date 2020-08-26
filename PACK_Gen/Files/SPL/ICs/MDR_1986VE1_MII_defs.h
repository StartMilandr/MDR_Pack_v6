#ifndef MDR_MII_DEFS_VE1_H
#define MDR_MII_DEFS_VE1_H


#define MII_PIN_POWER    (uint32_t)MDR_PIN_MAXFAST

#define VE1_CLR_FUNC     MDR_GPIO_FUNC__Pin_Msk
#define VE1_CLR_HILO    (MDR_GPIO_PD_Driver__Pin_Msk | MDR_GPIO_PD_Schmitt__Pin_Msk)
#define VE1_CLR_PWR      MDR_GPIO_PWR__Pin_Msk


//------------------    Port E  ----------------
#define VE1_MII_PORT                MDR_GPIO_E

#define VE1_MII_IND_TXD0             3
#define VE1_MII_IND_TXD1             4
#define VE1_MII_IND_TXD2             5
#define VE1_MII_IND_TXD3             6
#define VE1_MII_IND_RXD0             7
#define VE1_MII_IND_RXD1             8
#define VE1_MII_IND_RXD2             9
#define VE1_MII_IND_RXD3             10
#define VE1_MII_IND_TXEN             11
#define VE1_MII_IND_CLKTX            13
#define VE1_MII_IND_CLKRX            14
#define VE1_MII_IND_RXDV             15

#define VE1_MII_FUNC_TXD0            (uint32_t)MDR_PIN_OVER
#define VE1_MII_FUNC_TXD1            (uint32_t)MDR_PIN_OVER
#define VE1_MII_FUNC_TXD2            (uint32_t)MDR_PIN_OVER
#define VE1_MII_FUNC_TXD3            (uint32_t)MDR_PIN_OVER
#define VE1_MII_FUNC_RXD0            (uint32_t)MDR_PIN_OVER
#define VE1_MII_FUNC_RXD1            (uint32_t)MDR_PIN_OVER
#define VE1_MII_FUNC_RXD2            (uint32_t)MDR_PIN_OVER
#define VE1_MII_FUNC_RXD3            (uint32_t)MDR_PIN_OVER
#define VE1_MII_FUNC_TXEN            (uint32_t)MDR_PIN_OVER
#define VE1_MII_FUNC_CLK             (uint32_t)MDR_PIN_OVER
#define VE1_MII_FUNC_RXDV            (uint32_t)MDR_PIN_OVER


//Masks
#define VE1_MII_SEL_TXD0            (1UL << VE1_MII_IND_TXD0)
#define VE1_MII_SEL_TXD1            (1UL << VE1_MII_IND_TXD1)
#define VE1_MII_SEL_TXD2            (1UL << VE1_MII_IND_TXD2)
#define VE1_MII_SEL_TXD3            (1UL << VE1_MII_IND_TXD3)
#define VE1_MII_SEL_RXD0            (1UL << VE1_MII_IND_RXD0)
#define VE1_MII_SEL_RXD1            (1UL << VE1_MII_IND_RXD1)
#define VE1_MII_SEL_RXD2            (1UL << VE1_MII_IND_RXD2)
#define VE1_MII_SEL_RXD3            (1UL << VE1_MII_IND_RXD3)
#define VE1_MII_SEL_TXEN            (1UL << VE1_MII_IND_TXEN)
#define VE1_MII_SEL_CLKTX           (1UL << VE1_MII_IND_CLKTX)
#define VE1_MII_SEL_CLKRX           (1UL << VE1_MII_IND_CLKRX)
#define VE1_MII_SEL_RXDV            (1UL << VE1_MII_IND_RXDV)

#define VE1_MII_SEL         VE1_MII_SEL_TXD0 \
                          | VE1_MII_SEL_TXD1 \
                          | VE1_MII_SEL_TXD0 \
                          | VE1_MII_SEL_TXD1 \
                          | VE1_MII_SEL_TXD2 \
                          | VE1_MII_SEL_TXD3 \
                          | VE1_MII_SEL_RXD0 \
                          | VE1_MII_SEL_RXD1 \
                          | VE1_MII_SEL_RXD2 \
                          | VE1_MII_SEL_RXD3 \
                          | VE1_MII_SEL_TXEN \
                          | VE1_MII_SEL_CLKTX  \
                          | VE1_MII_SEL_CLKRX  \
                          | VE1_MII_SEL_RXDV 


#define VE1_MII_SET_FUNC_TXD0       (VE1_MII_FUNC_TXD0 << (VE1_MII_IND_TXD0 << 1))
#define VE1_MII_SET_FUNC_TXD1       (VE1_MII_FUNC_TXD1 << (VE1_MII_IND_TXD1 << 1))
#define VE1_MII_SET_FUNC_TXD2       (VE1_MII_FUNC_TXD2 << (VE1_MII_IND_TXD2 << 1))
#define VE1_MII_SET_FUNC_TXD3       (VE1_MII_FUNC_TXD3 << (VE1_MII_IND_TXD3 << 1))
#define VE1_MII_SET_FUNC_RXD0       (VE1_MII_FUNC_RXD0 << (VE1_MII_IND_RXD0 << 1))
#define VE1_MII_SET_FUNC_RXD1       (VE1_MII_FUNC_RXD1 << (VE1_MII_IND_RXD1 << 1))
#define VE1_MII_SET_FUNC_RXD2       (VE1_MII_FUNC_RXD2 << (VE1_MII_IND_RXD2 << 1))
#define VE1_MII_SET_FUNC_RXD3       (VE1_MII_FUNC_RXD3 << (VE1_MII_IND_RXD3 << 1))
#define VE1_MII_SET_FUNC_TXEN       (VE1_MII_FUNC_TXEN << (VE1_MII_IND_TXEN << 1))
#define VE1_MII_SET_FUNC_CLKTX      (VE1_MII_FUNC_CLK  << (VE1_MII_IND_CLKTX  << 1))
#define VE1_MII_SET_FUNC_CLKRX      (VE1_MII_FUNC_CLK  << (VE1_MII_IND_CLKRX  << 1))
#define VE1_MII_SET_FUNC_RXDV       (VE1_MII_FUNC_RXDV  << (VE1_MII_IND_RXDV  << 1))

#define VE1_MII_CLR_FUNC_TXD0       (VE1_CLR_FUNC << (VE1_MII_IND_TXD0 << 1))
#define VE1_MII_CLR_FUNC_TXD1       (VE1_CLR_FUNC << (VE1_MII_IND_TXD1 << 1))
#define VE1_MII_CLR_FUNC_TXD2       (VE1_CLR_FUNC << (VE1_MII_IND_TXD2 << 1))
#define VE1_MII_CLR_FUNC_TXD3       (VE1_CLR_FUNC << (VE1_MII_IND_TXD3 << 1))
#define VE1_MII_CLR_FUNC_RXD0       (VE1_CLR_FUNC << (VE1_MII_IND_RXD0 << 1))
#define VE1_MII_CLR_FUNC_RXD1       (VE1_CLR_FUNC << (VE1_MII_IND_RXD1 << 1))
#define VE1_MII_CLR_FUNC_RXD2       (VE1_CLR_FUNC << (VE1_MII_IND_RXD2 << 1))
#define VE1_MII_CLR_FUNC_RXD3       (VE1_CLR_FUNC << (VE1_MII_IND_RXD3 << 1))
#define VE1_MII_CLR_FUNC_TXEN       (VE1_CLR_FUNC << (VE1_MII_IND_TXEN << 1))
#define VE1_MII_CLR_FUNC_CLKTX      (VE1_CLR_FUNC << (VE1_MII_IND_CLKTX  << 1))
#define VE1_MII_CLR_FUNC_CLKRX      (VE1_CLR_FUNC << (VE1_MII_IND_CLKRX  << 1))
#define VE1_MII_CLR_FUNC_RXDV       (VE1_CLR_FUNC << (VE1_MII_IND_RXDV  << 1))

#define VE1_MII_FUNC_SET    VE1_MII_SET_FUNC_TXD0 \
                          | VE1_MII_SET_FUNC_TXD1 \
                          | VE1_MII_SET_FUNC_TXD0 \
                          | VE1_MII_SET_FUNC_TXD1 \
                          | VE1_MII_SET_FUNC_TXD2 \
                          | VE1_MII_SET_FUNC_TXD3 \
                          | VE1_MII_SET_FUNC_RXD0 \
                          | VE1_MII_SET_FUNC_RXD1 \
                          | VE1_MII_SET_FUNC_RXD2 \
                          | VE1_MII_SET_FUNC_RXD3 \
                          | VE1_MII_SET_FUNC_TXEN \
                          | VE1_MII_SET_FUNC_CLKTX  \
                          | VE1_MII_SET_FUNC_CLKRX  \
                          | VE1_MII_SET_FUNC_RXDV 

#define VE1_MII_FUNC_CLR    VE1_MII_CLR_FUNC_TXD0 \
                          | VE1_MII_CLR_FUNC_TXD1 \
                          | VE1_MII_CLR_FUNC_TXD0 \
                          | VE1_MII_CLR_FUNC_TXD1 \
                          | VE1_MII_CLR_FUNC_TXD2 \
                          | VE1_MII_CLR_FUNC_TXD3 \
                          | VE1_MII_CLR_FUNC_RXD0 \
                          | VE1_MII_CLR_FUNC_RXD1 \
                          | VE1_MII_CLR_FUNC_RXD2 \
                          | VE1_MII_CLR_FUNC_RXD3 \
                          | VE1_MII_CLR_FUNC_TXEN \
                          | VE1_MII_CLR_FUNC_CLKTX  \
                          | VE1_MII_CLR_FUNC_CLKRX  \
                          | VE1_MII_CLR_FUNC_RXDV 


#define VE1_MII_SET_PWR_TXD0        (MII_PIN_POWER << (VE1_MII_IND_TXD0 << 1))
#define VE1_MII_SET_PWR_TXD1        (MII_PIN_POWER << (VE1_MII_IND_TXD1 << 1))
#define VE1_MII_SET_PWR_TXD2        (MII_PIN_POWER << (VE1_MII_IND_TXD2 << 1))
#define VE1_MII_SET_PWR_TXD3        (MII_PIN_POWER << (VE1_MII_IND_TXD3 << 1))
#define VE1_MII_SET_PWR_RXD0        (MII_PIN_POWER << (VE1_MII_IND_RXD0 << 1))
#define VE1_MII_SET_PWR_RXD1        (MII_PIN_POWER << (VE1_MII_IND_RXD1 << 1))
#define VE1_MII_SET_PWR_RXD2        (MII_PIN_POWER << (VE1_MII_IND_RXD2 << 1))
#define VE1_MII_SET_PWR_RXD3        (MII_PIN_POWER << (VE1_MII_IND_RXD3 << 1))
#define VE1_MII_SET_PWR_TXEN        (MII_PIN_POWER << (VE1_MII_IND_TXEN << 1))
#define VE1_MII_SET_PWR_CLKTX       (MII_PIN_POWER << (VE1_MII_IND_CLKTX  << 1))
#define VE1_MII_SET_PWR_CLKRX       (MII_PIN_POWER << (VE1_MII_IND_CLKRX  << 1))
#define VE1_MII_SET_PWR_RXDV        (uint32_t)(MII_PIN_POWER << (VE1_MII_IND_RXDV  << 1))

#define VE1_MII_CLR_PWR_TXD0        (VE1_CLR_PWR << (VE1_MII_IND_TXD0 << 1))
#define VE1_MII_CLR_PWR_TXD1        (VE1_CLR_PWR << (VE1_MII_IND_TXD1 << 1))
#define VE1_MII_CLR_PWR_TXD2        (VE1_CLR_PWR << (VE1_MII_IND_TXD2 << 1))
#define VE1_MII_CLR_PWR_TXD3        (VE1_CLR_PWR << (VE1_MII_IND_TXD3 << 1))
#define VE1_MII_CLR_PWR_RXD0        (VE1_CLR_PWR << (VE1_MII_IND_RXD0 << 1))
#define VE1_MII_CLR_PWR_RXD1        (VE1_CLR_PWR << (VE1_MII_IND_RXD1 << 1))
#define VE1_MII_CLR_PWR_RXD2        (VE1_CLR_PWR << (VE1_MII_IND_RXD2 << 1))
#define VE1_MII_CLR_PWR_RXD3        (VE1_CLR_PWR << (VE1_MII_IND_RXD3 << 1))
#define VE1_MII_CLR_PWR_TXEN        (VE1_CLR_PWR << (VE1_MII_IND_TXEN << 1))
#define VE1_MII_CLR_PWR_CLKTX       (VE1_CLR_PWR << (VE1_MII_IND_CLKTX  << 1))
#define VE1_MII_CLR_PWR_CLKRX       (VE1_CLR_PWR << (VE1_MII_IND_CLKRX  << 1))
#define VE1_MII_CLR_PWR_RXDV        (uint32_t)(VE1_CLR_PWR << (VE1_MII_IND_RXDV  << 1))

#define VE1_MII_PWR_SET   ( VE1_MII_SET_PWR_TXD0 \
                          | VE1_MII_SET_PWR_TXD1 \
                          | VE1_MII_SET_PWR_TXD0 \
                          | VE1_MII_SET_PWR_TXD1 \
                          | VE1_MII_SET_PWR_TXD2 \
                          | VE1_MII_SET_PWR_TXD3 \
                          | VE1_MII_SET_PWR_RXD0 \
                          | VE1_MII_SET_PWR_RXD1 \
                          | VE1_MII_SET_PWR_RXD2 \
                          | VE1_MII_SET_PWR_RXD3 \
                          | VE1_MII_SET_PWR_TXEN \
                          | VE1_MII_SET_PWR_CLKTX  \
                          | VE1_MII_SET_PWR_CLKRX  \
                          | VE1_MII_SET_PWR_RXDV )
                                        
#define VE1_MII_PWR_CLR   ( VE1_MII_CLR_PWR_TXD0 \
                          | VE1_MII_CLR_PWR_TXD1 \
                          | VE1_MII_CLR_PWR_TXD0 \
                          | VE1_MII_CLR_PWR_TXD1 \
                          | VE1_MII_CLR_PWR_TXD2 \
                          | VE1_MII_CLR_PWR_TXD3 \
                          | VE1_MII_CLR_PWR_RXD0 \
                          | VE1_MII_CLR_PWR_RXD1 \
                          | VE1_MII_CLR_PWR_RXD2 \
                          | VE1_MII_CLR_PWR_RXD3 \
                          | VE1_MII_CLR_PWR_TXEN \
                          | VE1_MII_CLR_PWR_CLKTX  \
                          | VE1_MII_CLR_PWR_CLKRX  \
                          | VE1_MII_CLR_PWR_RXDV )


#define VE1_MII_CLR_HILO_TXD0        (VE1_CLR_HILO << VE1_MII_IND_TXD0)
#define VE1_MII_CLR_HILO_TXD1        (VE1_CLR_HILO << VE1_MII_IND_TXD1)
#define VE1_MII_CLR_HILO_TXD2        (VE1_CLR_HILO << VE1_MII_IND_TXD2)
#define VE1_MII_CLR_HILO_TXD3        (VE1_CLR_HILO << VE1_MII_IND_TXD3)
#define VE1_MII_CLR_HILO_RXD0        (VE1_CLR_HILO << VE1_MII_IND_RXD0)
#define VE1_MII_CLR_HILO_RXD1        (VE1_CLR_HILO << VE1_MII_IND_RXD1)
#define VE1_MII_CLR_HILO_RXD2        (VE1_CLR_HILO << VE1_MII_IND_RXD2)
#define VE1_MII_CLR_HILO_RXD3        (VE1_CLR_HILO << VE1_MII_IND_RXD3)
#define VE1_MII_CLR_HILO_TXEN        (VE1_CLR_HILO << VE1_MII_IND_TXEN)
#define VE1_MII_CLR_HILO_CLKTX       (VE1_CLR_HILO << VE1_MII_IND_CLKTX )
#define VE1_MII_CLR_HILO_CLKRX       (VE1_CLR_HILO << VE1_MII_IND_CLKRX )
#define VE1_MII_CLR_HILO_RXDV        (VE1_CLR_HILO << VE1_MII_IND_RXDV )

#define VE1_MII_HILO_CLR  ( VE1_MII_CLR_HILO_TXD0 \
                          | VE1_MII_CLR_HILO_TXD1 \
                          | VE1_MII_CLR_HILO_TXD0 \
                          | VE1_MII_CLR_HILO_TXD1 \
                          | VE1_MII_CLR_HILO_TXD2 \
                          | VE1_MII_CLR_HILO_TXD3 \
                          | VE1_MII_CLR_HILO_RXD0 \
                          | VE1_MII_CLR_HILO_RXD1 \
                          | VE1_MII_CLR_HILO_RXD2 \
                          | VE1_MII_CLR_HILO_RXD3 \
                          | VE1_MII_CLR_HILO_TXEN \
                          | VE1_MII_CLR_HILO_CLKTX  \
                          | VE1_MII_CLR_HILO_CLKRX  \
                          | VE1_MII_CLR_HILO_RXDV )

//===================== PortE ===========
//------------------    Port E  ----------------
#define VE1_MII_PF_PORT                MDR_GPIO_F

#define VE1_MII_PF_IND_RXERR            0
#define VE1_MII_PF_IND_CRS              1
#define VE1_MII_PF_IND_COL              2
                
#define VE1_MII_PF_FUNC_RXERR          (uint32_t)MDR_PIN_OVER
#define VE1_MII_PF_FUNC_CRS            (uint32_t)MDR_PIN_OVER
#define VE1_MII_PF_FUNC_COL            (uint32_t)MDR_PIN_OVER
                
                
//Masks         
#define VE1_MII_PF_SEL_RXERR            (1UL << VE1_MII_PF_IND_RXERR)
#define VE1_MII_PF_SEL_CRS              (1UL << VE1_MII_PF_IND_CRS  )
#define VE1_MII_PF_SEL_COL              (1UL << VE1_MII_PF_IND_COL  )
                
#define VE1_MII_PF_SEL      VE1_MII_PF_SEL_RXERR \
                          | VE1_MII_PF_SEL_CRS   \
                          | VE1_MII_PF_SEL_COL


#define VE1_MII_PF_SET_FUNC_RXERR       (VE1_MII_PF_FUNC_RXERR << (VE1_MII_PF_IND_RXERR << 1))
#define VE1_MII_PF_SET_FUNC_CRS         (VE1_MII_PF_FUNC_CRS   << (VE1_MII_PF_IND_CRS   << 1))
#define VE1_MII_PF_SET_FUNC_COL         (VE1_MII_PF_FUNC_COL   << (VE1_MII_PF_IND_COL   << 1))

#define VE1_MII_PF_CLR_FUNC_RXERR       (VE1_CLR_FUNC << (VE1_MII_PF_IND_RXERR << 1))
#define VE1_MII_PF_CLR_FUNC_CRS         (VE1_CLR_FUNC << (VE1_MII_PF_IND_CRS   << 1))
#define VE1_MII_PF_CLR_FUNC_COL         (VE1_CLR_FUNC << (VE1_MII_PF_IND_COL   << 1))

#define VE1_MII_PF_FUNC_SET     VE1_MII_PF_SET_FUNC_RXERR \
                              | VE1_MII_PF_SET_FUNC_CRS   \
                              | VE1_MII_PF_SET_FUNC_COL   

#define VE1_MII_PF_FUNC_CLR     VE1_MII_PF_CLR_FUNC_RXERR \
                              | VE1_MII_PF_CLR_FUNC_CRS   \
                              | VE1_MII_PF_CLR_FUNC_COL   


#define VE1_MII_PF_SET_PWR_RXERR        (MII_PIN_POWER << (VE1_MII_PF_IND_RXERR << 1))
#define VE1_MII_PF_SET_PWR_CRS          (MII_PIN_POWER << (VE1_MII_PF_IND_CRS   << 1))
#define VE1_MII_PF_SET_PWR_COL          (MII_PIN_POWER << (VE1_MII_PF_IND_COL   << 1))

#define VE1_MII_PF_CLR_PWR_RXERR        (VE1_CLR_PWR << (VE1_MII_PF_IND_RXERR << 1))
#define VE1_MII_PF_CLR_PWR_CRS          (VE1_CLR_PWR << (VE1_MII_PF_IND_CRS   << 1))
#define VE1_MII_PF_CLR_PWR_COL          (VE1_CLR_PWR << (VE1_MII_PF_IND_COL   << 1))


#define VE1_MII_PF_PWR_SET   (  VE1_MII_PF_SET_PWR_RXERR \
                              | VE1_MII_PF_SET_PWR_CRS   \
                              | VE1_MII_PF_SET_PWR_COL  )
                                        
#define VE1_MII_PF_PWR_CLR   (  VE1_MII_PF_CLR_PWR_RXERR \
                              | VE1_MII_PF_CLR_PWR_CRS   \
                              | VE1_MII_PF_CLR_PWR_COL )


#define VE1_MII_PF_CLR_HILO_RXERR        (VE1_CLR_HILO << VE1_MII_PF_IND_RXERR)
#define VE1_MII_PF_CLR_HILO_CRS          (VE1_CLR_HILO << VE1_MII_PF_IND_CRS  )
#define VE1_MII_PF_CLR_HILO_COL          (VE1_CLR_HILO << VE1_MII_PF_IND_COL  )

#define VE1_MII_PF_HILO_CLR  (  VE1_MII_PF_CLR_HILO_RXERR \
                              | VE1_MII_PF_CLR_HILO_CRS   \
                              | VE1_MII_PF_CLR_HILO_COL   )


#endif  //MDR_MII_DEFS_VE1_H
