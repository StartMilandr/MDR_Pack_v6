cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../_src/MDR1986VE1.svd"
TextInsert.exe ../_src/blank_MDR1986VE1.svd ../_src/TAGS_VE1.txt 4
ren "../_src/blank_MDR1986VE1_out.txt" "MDR1986VE1.svd"

