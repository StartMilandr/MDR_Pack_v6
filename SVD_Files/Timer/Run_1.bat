cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../Timer/Timer_VE1.txt"
TextInsert.exe ../Timer/Timer_Common.xml ../Timer/TAGS_VE1.txt 4 #Timers
ren "../Timer/Timer_Common_out.txt" "Timer_VE1.txt
