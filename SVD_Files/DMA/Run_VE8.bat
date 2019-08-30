cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../DMA/DMA_VE8.xml"
TextInsert.exe ../DMA/DMA_blank.xml ../DMA/TAGS_VE8.txt 4 #DMA
ren "../DMA/DMA_blank_out.txt" "DMA_VE8.xml"

