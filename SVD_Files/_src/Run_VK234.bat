cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../_src/MDR1986VK234.svd"
TextInsert.exe ../_src/blank_MDR1986VK234.svd ../_src/TAGS_VK234.txt 4
ren "../_src/blank_MDR1986VK234_out.txt" "MDR1986VK234.svd"
