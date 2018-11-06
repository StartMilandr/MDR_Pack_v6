cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "..\RST\PER\PER_VE13.txt"
TextInsert.exe ../RST/PER/PER_BaseVEx.xml ../RST/PER/TAGS_VE13.txt 4 #RST_REG_PER
ren "..\RST\PER\PER_BaseVEx_out.txt" "PER_VE13.txt"

del "..\RST\PER\PER_VE9x.txt"
TextInsert.exe ../RST/PER/PER_BaseVEx.xml ../RST/PER/TAGS_VE9x.txt 4 #RST_REG_PER
ren "..\RST\PER\PER_BaseVEx_out.txt" "PER_VE9x.txt"

del "..\RST\PER\PER_VC1.txt"
TextInsert.exe ../RST/PER/PER_BaseVEx.xml ../RST/PER/TAGS_VC1.txt 4 #RST_REG_PER
ren "..\RST\PER\PER_BaseVEx_out.txt" "PER_VC1.txt"
