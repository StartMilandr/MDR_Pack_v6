cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "..\RST\PER2\PER2_VE4.txt"
TextInsert.exe ../RST/PER2/PER2_BaseVE4.xml ../RST/PER2/TAGS_VE4.txt 4 #RST_REG_PER
ren "..\RST\PER2\PER2_BaseVE4_out.txt" "PER2_VE4.txt"

del "..\RST\PER2\PER2_VE214.txt"
TextInsert.exe ../RST/PER2/PER2_BaseVE4.xml ../RST/PER2/TAGS_VE214.txt 4 #RST_REG_PER
ren "..\RST\PER2\PER2_BaseVE4_out.txt" "PER2_VE214.txt"

del "..\RST\PER2\PER2_VE234.txt"
TextInsert.exe ../RST/PER2/PER2_BaseVE4.xml ../RST/PER2/TAGS_VE234.txt 4 #RST_REG_PER
ren "..\RST\PER2\PER2_BaseVE4_out.txt" "PER2_VE234.txt"
