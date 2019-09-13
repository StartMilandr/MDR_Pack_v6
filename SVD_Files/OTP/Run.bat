cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../OTP/OTP_VE8.txt"
TextInsert.exe ../OTP/OTP_blank.xml ../OTP/TAGS_VE8.txt 4 #OTP
ren "../OTP/OTP_blank_out.txt" "OTP_VE8.txt

del "../OTP/OTP_VE81.txt"
TextInsert.exe ../OTP/OTP_blank.xml ../OTP/TAGS_VE81.txt 4 #OTP
ren "../OTP/OTP_blank_out.txt" "OTP_VE81.txt
