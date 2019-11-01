cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../_src/MDR_ESila.svd"
TextInsert.exe ../_src/blank_MDR_ESila.svd ../_src/TAGS_ESila.txt 4
ren "../_src/blank_MDR_ESila_out.txt" "MDR_ESila.svd"
