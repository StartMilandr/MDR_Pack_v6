cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../ADC/ADC_VE9x.txt"
TextInsert.exe ../ADC/ADC_blank.xml ../ADC/TAGS_VE9x.txt 4 #ADC
ren "../ADC/ADC_blank_out.txt" "ADC_VE9x.txt

del "../ADC/ADC_VE13.txt"
TextInsert.exe ../ADC/ADC_blank.xml ../ADC/TAGS_VE13.txt 4 #ADC
ren "../ADC/ADC_blank_out.txt" "ADC_VE13.txt

del "../ADC/ADC_VE4x.txt"
TextInsert.exe ../ADC/ADC_blank.xml ../ADC/TAGS_VE4x.txt 4 #ADC
ren "../ADC/ADC_blank_out.txt" "ADC_VE4x.txt

