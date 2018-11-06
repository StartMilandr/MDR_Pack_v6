cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe
call "../RST/ADC/Run.bat"

cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe
call "../RST/ETH/Run.bat"

cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe
call "../RST/PER/Run.bat"

cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe
call "../RST/PER1/Run.bat"

cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe
call "../RST/PER2/Run.bat"

cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../RST/RST_VE1.txt"
TextInsert.exe ../RST/RST_Common.xml ../RST/TAGS_VE1.txt 4 #RST_VE1
ren "../RST/RST_Common_out.txt" "RST_VE1.txt"

del "../RST/RST_VE3.txt"
TextInsert.exe ../RST/RST_Common.xml ../RST/TAGS_VE3.txt 4 #RST_VE3
ren "../RST/RST_Common_out.txt" "RST_VE3.txt"

del "../RST/RST_VE9x.txt"
TextInsert.exe ../RST/RST_Common.xml ../RST/TAGS_VE9x.txt 4 #RST_VE9x
ren "../RST/RST_Common_out.txt" "RST_VE9x.txt"

del "../RST/RST_VC1.txt"
TextInsert.exe ../RST/RST_Common.xml ../RST/TAGS_VC1.txt 4 #RST_VC1
ren "../RST/RST_Common_out.txt" "RST_VC1.txt"

del "../RST/RST_VE4.txt"
TextInsert.exe ../RST/RST_Common.xml ../RST/TAGS_VE4.txt 4 #RST_VE4
ren "../RST/RST_Common_out.txt" "RST_VE4.txt"

del "../RST/RST_VE234.txt"
TextInsert.exe ../RST/RST_Common.xml ../RST/TAGS_VE234.txt 4 #RST_VE234
ren "../RST/RST_Common_out.txt" "RST_VE234.txt"

del "../RST/RST_VE214.txt"
TextInsert.exe ../RST/RST_Common.xml ../RST/TAGS_VE214.txt 4 #RST_VE214
ren "../RST/RST_Common_out.txt" "RST_VE214.txt"

cd C:\CODE\PACK\__SVD\RST