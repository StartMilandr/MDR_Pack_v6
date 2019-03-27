cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../I2C/I2C_Vx.txt"
TextInsert.exe ../I2C/I2C_Common.xml ../I2C/TAGS_Vx.txt 4 #I2C
ren "../I2C/I2C_Common_out.txt" "I2C_Vx.txt

del "../I2C/I2C_VK214.txt"
TextInsert.exe ../I2C/I2C_Common.xml ../I2C/TAGS_VK214.txt 4 #I2C
ren "../I2C/I2C_Common_out.txt" "I2C_VK214.txt


