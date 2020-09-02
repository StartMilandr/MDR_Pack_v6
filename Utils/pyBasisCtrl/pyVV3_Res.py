
MDR_5600BB3_regControl      = 1
MDR_5600BB3_regStatus       = 2
MDR_5600BB3_regFD_Mode5     = 3
MDR_5600BB3_regPhyModes12   = 4
MDR_5600BB3_regPhyModes34   = 0xB

MDR_5600BB3_regRamData1     = 0x13
MDR_5600BB3_regRamData2     = 0x14
MDR_5600BB3_regRamData3     = 0x15
MDR_5600BB3_regRamData4     = 0x16
MDR_5600BB3_regRamData5     = 0x17
MDR_5600BB3_regRamData6     = 0x18
MDR_5600BB3_regRamData7     = 0x19
MDR_5600BB3_regRamData8     = 0x1A

MDR_5600BB3_regRamCtrl0     = 0x1B
MDR_5600BB3_regRamCtrl1     = 0x1C

MDR_5600BB3_regAgeCtrl0     = 0x1D
MDR_5600BB3_regAgeCtrl1     = 0x1E
MDR_5600BB3_regAgeCtrl2     = 0x1F

MDR_5600BB3_regMacRamWrEn   = 0x20

MDR_5600BB3_regPN1_MskAnd   = 0x21
MDR_5600BB3_regPN2_MskAnd   = 0x22
MDR_5600BB3_regPN3_MskAnd   = 0x23
MDR_5600BB3_regPN4_MskAnd   = 0x24
MDR_5600BB3_regPN5_MskAnd   = 0x25

MDR_5600BB3_regPN1_MskOr    = 0x26
MDR_5600BB3_regPN2_MskOr    = 0x27
MDR_5600BB3_regPN3_MskOr    = 0x28
MDR_5600BB3_regPN4_MskOr    = 0x29
MDR_5600BB3_regPN5_MskOr    = 0x2A  

MDR_5600BB3_regIPGh         = 0x2B
MDR_5600BB3_regIPGl         = 0x2C

MDR_5600BB3_regMAC_CtrlTx   = 0x2D
MDR_5600BB3_regCollWindow   = 0x2E
MDR_5600BB3_regMAC_CtrlRx   = 0x2F

MDR_5600BB3_regMinFrameH    = 0x30
MDR_5600BB3_regMinFrameL    = 0x31
MDR_5600BB3_regMaxFrameH    = 0x32
MDR_5600BB3_regMaxFrameL    = 0x33

# =========================================================  Control  ====================================================== */
MDR_5600BB3_Control_SW_RST_Pos       = 0
MDR_5600BB3_Control_SW_RST_Msk       = 1
MDR_5600BB3_Control_ClrCalcEn_Pos    = 4
MDR_5600BB3_Control_ClrCalcEn_Msk    = 0x10
MDR_5600BB3_Control_Port5Dis_Pos     = 6
MDR_5600BB3_Control_Port5Dis_Msk     = 0x40
MDR_5600BB3_Control_HSE_BYP_Pos      = 7
MDR_5600BB3_Control_HSE_BYP_Msk      = 0x80



# =========================================================  Status  ====================================================== */
MDR_5600BB3_Control_HSE_RDY_Pos      = 7
MDR_5600BB3_Control_HSE_RDY_Msk      = 0x80

# =========================================================  FD_MODE5  ====================================================== */
MDR_5600BB3_FDMode5_DFEna_Pos      = 4
MDR_5600BB3_FDMode5_FDEna_RDY_Msk  = 0x10

MDR_5600BB3_regFD_Mode5_FD   = 0x1F

# =========================================================  PHY_MODE12  ====================================================== */
MDR_5600BB3_PhyMode12_Mode1_Pos   = 0
MDR_5600BB3_PhyMode12_Mode1_Msk   = 0x07
MDR_5600BB3_PhyMode12_RST1_Pos    = 3
MDR_5600BB3_PhyMode12_RST1_Msk    = 0x08

MDR_5600BB3_PhyMode12_Mode2_Pos   = 4
MDR_5600BB3_PhyMode12_Mode2_Msk   = 0x70
MDR_5600BB3_PhyMode12_RST2_Pos    = 8
MDR_5600BB3_PhyMode12_RST2_Msk    = 0x80

# =========================================================  PHY_MODE34  ====================================================== */
MDR_5600BB3_PhyMode34_Mode3_Pos   = 0
MDR_5600BB3_PhyMode34_Mode3_Msk   = 0x07
MDR_5600BB3_PhyMode34_RST3_Pos    = 3
MDR_5600BB3_PhyMode34_RST3_Msk    = 0x08

MDR_5600BB3_PhyMode34_Mode4_Pos   = 4
MDR_5600BB3_PhyMode34_Mode4_Msk   = 0x70
MDR_5600BB3_PhyMode34_RST4_Pos    = 8
MDR_5600BB3_PhyMode34_RST4_Msk    = 0x80


# =========================================================  RAM_CONTROL_0 ====================================================== */
MDR_5600BB3_RamCtrl0_RAM_AddrHi_Pos   = 0
MDR_5600BB3_RamCtrl0_RAM_AddrHi_Msk   = 0x0F
MDR_5600BB3_RamCtrl0_DATA_nMAC_Pos    = 5
MDR_5600BB3_RamCtrl0_DATA_nMAC_Msk    = 0x20
MDR_5600BB3_RamCtrl0_SPI_WE_nRD_Pos   = 6
MDR_5600BB3_RamCtrl0_SPI_WE_nRD_Msk   = 0x40
MDR_5600BB3_RamCtrl0_SPI_EN_Pos       = 7
MDR_5600BB3_RamCtrl0_SPI_EN_Msk       = 0x80

MDR_5600BB3_RamCtrl0_RAM_AddrHi_Shift = 8

# =========================================================  Age_CONTROL_0 ====================================================== */
MDR_5600BB3_AgeCtrl0_MAC_AgeLimHi_Pos   = 0
MDR_5600BB3_AgeCtrl0_MAC_AgeLimHi_Msk   = 0x0F
MDR_5600BB3_AgeCtrl0_MAC_ClrEn_Pos      = 5
MDR_5600BB3_AgeCtrl0_MAC_ClrEn_Msk      = 0x20
MDR_5600BB3_AgeCtrl0_MAC_AgeIncEn_Pos   = 6
MDR_5600BB3_AgeCtrl0_MAC_AgeIncEn_Msk   = 0x40
MDR_5600BB3_AgeCtrl0_MAC_AgeDelEn_Pos   = 7
MDR_5600BB3_AgeCtrl0_MAC_AgeDelEn_Msk  =  0x80

MDR_5600BB3_AgeCtrl0_MAC_AGECLR_OFF   =  (MDR_5600BB3_AgeCtrl0_MAC_ClrEn_Msk | MDR_5600BB3_AgeCtrl0_MAC_AgeIncEn_Msk | MDR_5600BB3_AgeCtrl0_MAC_AgeLimHi_Msk)

# =========================================================  MAC_RAM_WE ====================================================== */
MDR_5600BB3_RamCtrl0_MAC1_RamWE_Pos   = 0
MDR_5600BB3_RamCtrl0_MAC1_RamWE_Msk   = 0x01
MDR_5600BB3_RamCtrl0_MAC2_RamWE_Pos   = 1
MDR_5600BB3_RamCtrl0_MAC2_RamWE_Msk   = 0x02
MDR_5600BB3_RamCtrl0_MAC3_RamWE_Pos   = 2
MDR_5600BB3_RamCtrl0_MAC3_RamWE_Msk   = 0x04
MDR_5600BB3_RamCtrl0_MAC4_RamWE_Pos   = 3
MDR_5600BB3_RamCtrl0_MAC4_RamWE_Msk   = 0x08
MDR_5600BB3_RamCtrl0_MAC5_RamWE_Pos   = 4
MDR_5600BB3_RamCtrl0_MAC5_RamWE_Msk   = 0x01

# =========================================================  PNx_Mask_AND / OR  ====================================================== */
MDR_5600BB3_RamCtrl0_PNx_MaskAndOr_Pos   = 0
MDR_5600BB3_RamCtrl0_PNx_MaskAndOr_Msk   = 0x1F

# =========================================================  MAC_TX_CTRL ====================================================== */
MDR_5600BB3_CtrlTX_PAD_EN_Pos       = 0
MDR_5600BB3_CtrlTX_PAD_EN_Msk       = 0x01
MDR_5600BB3_CtrlTX_TryLim_Pos       = 4
MDR_5600BB3_CtrlTX_TryLim_Msk       = 0xF0

# =========================================================  MAC_RX_CTRL ====================================================== */
MDR_5600BB3_CtrlRX_ErrEn_Pos      = 0
MDR_5600BB3_CtrlRX_ErrEn_Msk      = 0x01


VV3_RegsDict = { 
    'Control':     MDR_5600BB3_regControl   ,   
    'Status':      MDR_5600BB3_regStatus    ,
    'FD_Mode5':    MDR_5600BB3_regFD_Mode5  ,  
    'PhyModes12':  MDR_5600BB3_regPhyModes12,
    'PhyModes34':  MDR_5600BB3_regPhyModes34,
    # 'RamData1':    MDR_5600BB3_regRamData1  ,
    # 'RamData2':    MDR_5600BB3_regRamData2  ,
    # 'RamData3':    MDR_5600BB3_regRamData3  ,
    # 'RamData4':    MDR_5600BB3_regRamData4  ,
    # 'RamData5':    MDR_5600BB3_regRamData5  ,
    # 'RamData6':    MDR_5600BB3_regRamData6  ,
    # 'RamData7':    MDR_5600BB3_regRamData7  ,
    # 'RamData8':    MDR_5600BB3_regRamData8  ,
    # 'RamCtrl0':    MDR_5600BB3_regRamCtrl0  ,
    #'RamCtrl1':    MDR_5600BB3_regRamCtrl1  ,
    'AgeCtrl0':    MDR_5600BB3_regAgeCtrl0  ,
    'AgeCtrl1':    MDR_5600BB3_regAgeCtrl1  ,
    'AgeCtrl2':    MDR_5600BB3_regAgeCtrl2  ,
    'MacRamWrEn':  MDR_5600BB3_regMacRamWrEn,
    'PN1_MskAnd':  MDR_5600BB3_regPN1_MskAnd,
    'PN2_MskAnd':  MDR_5600BB3_regPN2_MskAnd,
    'PN3_MskAnd':  MDR_5600BB3_regPN3_MskAnd,
    'PN4_MskAnd':  MDR_5600BB3_regPN4_MskAnd,
    'PN5_MskAnd':  MDR_5600BB3_regPN5_MskAnd,
    'PN1_MskOr':   MDR_5600BB3_regPN1_MskOr ,
    'PN2_MskOr':   MDR_5600BB3_regPN2_MskOr ,
    'PN3_MskOr':   MDR_5600BB3_regPN3_MskOr ,
    'PN4_MskOr':   MDR_5600BB3_regPN4_MskOr ,
    'PN5_MskOr':   MDR_5600BB3_regPN5_MskOr ,
    'IPGh':        MDR_5600BB3_regIPGh      ,
    'IPGl':        MDR_5600BB3_regIPGl      ,
    'MAC_CtrlTx':  MDR_5600BB3_regMAC_CtrlTx,
    'CollWindow':  MDR_5600BB3_regCollWindow,
    'MAC_CtrlRx':  MDR_5600BB3_regMAC_CtrlRx,
    'MinFrameH':   MDR_5600BB3_regMinFrameH ,
    'MinFrameL':   MDR_5600BB3_regMinFrameL ,
    'MaxFrameH':   MDR_5600BB3_regMaxFrameH ,
    'MaxFrameL':   MDR_5600BB3_regMaxFrameL ,
}