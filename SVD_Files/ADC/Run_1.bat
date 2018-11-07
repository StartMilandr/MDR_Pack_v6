cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../ADC/ADC_VE9x.txt"
TextInsert.exe ../ADC/ADC_blank.xml ../ADC/TAGS_VE9x.txt 4 #ADC
ren "../ADC/ADC_blank_out.txt" "ADC_VE9x.txt"
