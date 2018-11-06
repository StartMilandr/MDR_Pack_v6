cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../GPIO/GPIO_VE3.txt"
TextInsert.exe ../GPIO/GPIO_Common.xml ../GPIO/TAGS_VE3.txt 4 #GPIO_VE3
ren "../GPIO/GPIO_Common_out.txt" "GPIO_VE3.txt"
