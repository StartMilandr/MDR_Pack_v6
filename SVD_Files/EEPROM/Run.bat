cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../EEPROM/EEPROM_VEx.txt"
TextInsert.exe ../EEPROM/blank_EEPROM.xml ../EEPROM/TAGS_VEx.txt 4 #EEPROM
ren "../EEPROM/blank_EEPROM_out.txt" "EEPROM_VEx.txt"

del "../EEPROM/EEPROM_VE4x.txt"
TextInsert.exe ../EEPROM/blank_EEPROM.xml ../EEPROM/TAGS_VE4x.txt 4 #EEPROM
ren "../EEPROM/blank_EEPROM_out.txt" "EEPROM_VE4x.txt"
