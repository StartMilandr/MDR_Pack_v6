cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../BKP/BKP_VE1.txt"
TextInsert.exe ../BKP/BKP_Common.xml ../BKP/TAGS_VE1.txt 4 #BKP_VE1
ren "../BKP/BKP_Common_out.txt" "BKP_VE1.txt"
