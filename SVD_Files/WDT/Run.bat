cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../WDT/WDT_VEx.txt"
TextInsert.exe ../WDT/Common_WDT.xml ../WDT/TAGS_VEx.txt 4 #WDT
ren "../WDT/Common_WDT_out.txt" "WDT_VEx.txt"

del "../WDT/WDT_VE4x.txt"
TextInsert.exe ../WDT/Common_WDT.xml ../WDT/TAGS_VE4x.txt 4 #WDT
ren "../WDT/Common_WDT_out.txt" "WDT_VE4x.txt"
