cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../_src/MDR1923VK014.svd"
TextInsert.exe ../_src/blank_MDR1923VK014.svd ../_src/TAGS_VK014.txt 4
ren "../_src/blank_MDR1923VK014_out.txt" "MDR1923VK014.svd"
