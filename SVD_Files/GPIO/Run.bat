cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../GPIO/GPIO_VE1.txt"
TextInsert.exe ../GPIO/GPIO_Common.xml ../GPIO/TAGS_VE1.txt 4 #GPIO_VE1
ren "../GPIO/GPIO_Common_out.txt" "GPIO_VE1.txt"

del "../GPIO/GPIO_VE3.txt"
TextInsert.exe ../GPIO/GPIO_Common.xml ../GPIO/TAGS_VE3.txt 4 #GPIO_VE3
ren "../GPIO/GPIO_Common_out.txt" "GPIO_VE3.txt"

del "../GPIO/GPIO_VE4.txt"
TextInsert.exe ../GPIO/GPIO_Common.xml ../GPIO/TAGS_VE4.txt 4 #GPIO_VE4
ren "../GPIO/GPIO_Common_out.txt" "GPIO_VE4.txt"

del "../GPIO/GPIO_VE214.txt"
TextInsert.exe ../GPIO/GPIO_Common.xml ../GPIO/TAGS_VE214.txt 4 #GPIO_VE214
ren "../GPIO/GPIO_Common_out.txt" "GPIO_VE214.txt"

del "../GPIO/GPIO_VE9x.txt"
TextInsert.exe ../GPIO/GPIO_Common.xml ../GPIO/TAGS_VE9x.txt 4 #GPIO_VE9x
ren "../GPIO/GPIO_Common_out.txt" "GPIO_VE9x.txt"
