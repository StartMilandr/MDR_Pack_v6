cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../CAN/CAN_VE139x.txt"
TextInsert.exe ../CAN/CAN_blank.xml ../CAN/TAGS_VE139x.txt 4 #CANs
ren "../CAN/CAN_blank_out.txt" "CAN_VE139x.txt

del "../CAN/CAN_VE8.txt"
TextInsert.exe ../CAN/CAN_blank.xml ../CAN/TAGS_VE8.txt 4 #CANs
ren "../CAN/CAN_blank_out.txt" "CAN_VE8.txt

del "../CAN/CAN_VK014.txt"
TextInsert.exe ../CAN/CAN_blank.xml ../CAN/TAGS_VK014.txt 4 #CANs
ren "../CAN/CAN_blank_out.txt" "CAN_VK014.txt

del "../CAN/CAN_ES.txt"
TextInsert.exe ../CAN/CAN_blank.xml ../CAN/TAGS_ES.txt 4 #CANs
ren "../CAN/CAN_blank_out.txt" "CAN_ES.txt