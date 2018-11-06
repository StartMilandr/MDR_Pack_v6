cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "..\RST\ETH\ETH_VE1.txt"
TextInsert.exe ../RST/ETH/RST_ETH_base.xml ../RST/ETH/TAGS_VE1.txt 4 #RST_REG_ETH_CLOCK
ren "..\RST\ETH\RST_ETH_base_out.txt" "ETH_VE1.txt"


del "..\RST\ETH\ETH_VE3.txt"
TextInsert.exe ../RST/ETH/RST_ETH_base.xml ../RST/ETH/TAGS_VE3.txt 4 #RST_REG_ETH_CLOCK
ren "..\RST\ETH\RST_ETH_base_out.txt" "ETH_VE3.txt"
