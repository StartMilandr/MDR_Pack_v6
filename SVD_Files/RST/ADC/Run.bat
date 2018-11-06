cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "..\RST\ADC\ADC_VE1VE9x.txt"
TextInsert.exe ../RST/ADC/ADC_CommVEx.xml ../RST/ADC/TAGS_VE1VE9x.txt 4 #RST_REG_ADC
ren "..\RST\ADC\ADC_CommVEx_out.txt" "ADC_VE1VE9x.txt"


del "..\RST\ADC\ADC_VE3VC1.txt"
TextInsert.exe ../RST/ADC/ADC_CommVEx.xml ../RST/ADC/TAGS_VE3VC1.txt 4 #RST_REG_ADC
ren "..\RST\ADC\ADC_CommVEx_out.txt" "ADC_VE3VC1.txt"
