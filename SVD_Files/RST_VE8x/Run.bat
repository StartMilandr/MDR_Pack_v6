cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../RST_VE8x/RST_VE8.txt"
TextInsert.exe ../RST_VE8x/CLK_VE8_Common.xml ../RST_VE8x/TAGS_VE8.txt 4 #RST_VE8
ren "../RST_VE8x/CLK_VE8_Common_out.txt" "RST_VE8.txt"

del "../RST_VE8x/RST_VK014.txt"
TextInsert.exe ../RST_VE8x/CLK_VE8_Common.xml ../RST_VE8x/TAGS_VK014.txt 4 #RST_VK014
ren "../RST_VE8x/CLK_VE8_Common_out.txt" "RST_VK014.txt"

del "../RST_VE8x/RST_ESila.txt"
TextInsert.exe ../RST_VE8x/CLK_VE8_Common.xml ../RST_VE8x/TAGS_ESila.txt 4 #RST_ESila
ren "../RST_VE8x/CLK_VE8_Common_out.txt" "RST_ESila.txt"

cd C:\CODE\PACK\MDR_Pack\SVD_Files\RST_VE8x