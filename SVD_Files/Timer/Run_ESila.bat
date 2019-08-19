cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../Timer/Timer_ES.txt"
TextInsert.exe ../Timer/Timer_Common.xml ../Timer/TAGS_ES.txt 4 #Timers
ren "../Timer/Timer_Common_out.txt" "Timer_ES.txt

del "../Timer/Timer_VE8.txt"
TextInsert.exe ../Timer/Timer_Common.xml ../Timer/TAGS_VE8.txt 4 #Timers
ren "../Timer/Timer_Common_out.txt" "Timer_VE8.txt

del "../Timer/Timer_VK014.txt"
TextInsert.exe ../Timer/Timer_Common.xml ../Timer/TAGS_VK014.txt 4 #Timers
ren "../Timer/Timer_Common_out.txt" "Timer_VK014.txt