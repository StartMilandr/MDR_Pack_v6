cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../Power/Power_Vx.txt"
TextInsert.exe ../Power/Power_Common.xml ../Power/TAGS_Vx.txt 4 #PWR
ren "../Power/Power_Common_out.txt" "Power_Vx.txt

del "../Power/Power_VE9x.txt"
TextInsert.exe ../Power/Power_Common.xml ../Power/TAGS_VE9x.txt 4 #PWR
ren "../Power/Power_Common_out.txt" "Power_VE9x.txt


