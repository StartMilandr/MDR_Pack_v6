cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "..\RST\PER1\PER1_VE4.txt"
TextInsert.exe ../RST/PER1/PER1_BaseVE4.xml ../RST/PER1/TAGS_VE4.txt 4 #RST_REG_PER1
ren "..\RST\PER1\PER1_BaseVE4_out.txt" "PER1_VE4.txt"

del "..\RST\PER1\PER1_VE214.txt"
TextInsert.exe ../RST/PER1/PER1_BaseVE4.xml ../RST/PER1/TAGS_VE214.txt 4 #RST_REG_PER1
ren "..\RST\PER1\PER1_BaseVE4_out.txt" "PER1_VE214.txt"

del "..\RST\PER1\PER1_VE234.txt"
TextInsert.exe ../RST/PER1/PER1_BaseVE4.xml ../RST/PER1/TAGS_VE234.txt 4 #RST_REG_PER1
ren "..\RST\PER1\PER1_BaseVE4_out.txt" "PER1_VE234.txt"

