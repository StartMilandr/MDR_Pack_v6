cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../SSP/SSP_ESila.txt"
TextInsert.exe ../SSP/SSP_blank.xml ../SSP/TAGS_ESila.txt 4 #SSPs
ren "../SSP/SSP_blank_out.txt" "SSP_ESila.txt

del "../SSP/SSP_VE8.txt"
TextInsert.exe ../SSP/SSP_blank.xml ../SSP/TAGS_VE8.txt 4 #SSPs
ren "../SSP/SSP_blank_out.txt" "SSP_VE8.txt

del "../SSP/SSP_VK014.txt"
TextInsert.exe ../SSP/SSP_blank.xml ../SSP/TAGS_VK014.txt 4 #SSPs
ren "../SSP/SSP_blank_out.txt" "SSP_VK014.txt
