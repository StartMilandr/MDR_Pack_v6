cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../_src/MDR1986VE8.svd"
TextInsert.exe ../_src/blank_MDR1986VE8.svd ../_src/TAGS_VE8.txt 4
ren "../_src/blank_MDR1986VE8_out.txt" "MDR1986VE8.svd"

del "../_src/MDR1986VE81.svd"
TextInsert.exe ../_src/blank_MDR1986VE81.svd ../_src/TAGS_VE81.txt 4
ren "../_src/blank_MDR1986VE81_out.txt" "MDR1986VE81.svd"