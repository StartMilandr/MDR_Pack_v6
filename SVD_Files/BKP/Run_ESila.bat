cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../BKP/BKP_VE8.txt"
TextInsert.exe ../BKP/BKP_Common_VE8.xml ../BKP/TAGS_VE8.txt 4 #BKP
ren "../BKP/BKP_Common_VE8_out.txt" "BKP_VE8.txt"

del "../BKP/BKP_VK14.txt"
TextInsert.exe ../BKP/BKP_Common_VE8.xml ../BKP/TAGS_VK14.txt 4 #BKP
ren "../BKP/BKP_Common_VE8_out.txt" "BKP_VK14.txt"

del "../BKP/BKP_ESila.txt"
TextInsert.exe ../BKP/BKP_Common_VE8.xml ../BKP/TAGS_ESila.txt 4 #BKP
ren "../BKP/BKP_Common_VE8_out.txt" "BKP_ESila.txt"
