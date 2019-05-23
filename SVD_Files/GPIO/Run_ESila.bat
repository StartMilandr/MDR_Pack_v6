cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../GPIO/GPIO_VE8VK14.txt"
TextInsert.exe ../GPIO/GPIO_Common_VE8.xml ../GPIO/TAGS_VE8VK14.txt 4 #GPIO
ren "../GPIO/GPIO_Common_VE8_out.txt" "GPIO_VE8VK14.txt"

del "../GPIO/GPIO_ESila.txt"
TextInsert.exe ../GPIO/GPIO_Common_VE8.xml ../GPIO/TAGS_ESila.txt 4 #GPIO
ren "../GPIO/GPIO_Common_VE8_out.txt" "GPIO_ESila.txt"