cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../DMA/DMA_VEx.xml"
TextInsert.exe ../DMA/DMA_blank.xml ../DMA/TAGS_VEx.txt 4 #DMA
ren "../DMA/DMA_blank_out.txt" "DMA_VEx.xml"

del "../DMA/DMA_VE8ES.xml"
TextInsert.exe ../DMA/DMA_blank.xml ../DMA/TAGS_VE8ES.txt 4 #DMA
ren "../DMA/DMA_blank_out.txt" "DMA_VE8ES.xml"

del "../DMA/DMA_VK014.xml"
TextInsert.exe ../DMA/DMA_blank.xml ../DMA/TAGS_VK014.txt 4 #DMA
ren "../DMA/DMA_blank_out.txt" "DMA_VK014.xml"