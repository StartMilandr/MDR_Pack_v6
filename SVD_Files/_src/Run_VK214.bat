cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../_src/MDR1986VK214.svd"
TextInsert.exe ../_src/blank_MDR1986VK214.svd ../_src/TAGS_VK214.txt 4
ren "../_src/blank_MDR1986VK214_out.txt" "MDR1986VK214.svd"
