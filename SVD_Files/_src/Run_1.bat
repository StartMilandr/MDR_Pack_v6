cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../_src/MDR1901VC1.svd"
TextInsert.exe ../_src/blank_MDR1901VC1.svd ../_src/TAGS_VC1.txt 4
ren "../_src/blank_MDR1901VC1_out.txt" "MDR1901VC1.svd"
