cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../BKP/BKP_VE1.txt"
TextInsert.exe ../BKP/BKP_Common.xml ../BKP/TAGS_VE1.txt 4 #BKP_VE1
ren "../BKP/BKP_Common_out.txt" "BKP_VE1.txt"

del "../BKP/BKP_VE3.txt"
TextInsert.exe ../BKP/BKP_Common.xml ../BKP/TAGS_VE3.txt 4 #BKP_VE3
ren "../BKP/BKP_Common_out.txt" "BKP_VE3.txt"

del "../BKP/BKP_VE4.txt"
TextInsert.exe ../BKP/BKP_Common.xml ../BKP/TAGS_VE4.txt 4 #BKP_VE4
ren "../BKP/BKP_Common_out.txt" "BKP_VE4.txt"

del "../BKP/BKP_VE9x.txt"
TextInsert.exe ../BKP/BKP_Common.xml ../BKP/TAGS_VE9x.txt 4 #BKP_VE9
ren "../BKP/BKP_Common_out.txt" "BKP_VE9x.txt"

del "../BKP/BKP_VC1.txt"
TextInsert.exe ../BKP/BKP_Common.xml ../BKP/TAGS_VC1.txt 4 #BKP_VC1
ren "../BKP/BKP_Common_out.txt" "BKP_VC1.txt"
