cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../Timer/Timer_VE9.txt"
TextInsert.exe ../Timer/Timer_Common.xml ../Timer/TAGS_VE9.txt 4 #TIMERs
ren "../Timer/Timer_Common_out.txt" "Timer_VE9.txt

del "../Timer/Timer_VE13.txt"
TextInsert.exe ../Timer/Timer_Common.xml ../Timer/TAGS_VE13.txt 4 #TIMERs
ren "../Timer/Timer_Common_out.txt" "Timer_VE13.txt

del "../Timer/Timer_VE4.txt"
TextInsert.exe ../Timer/Timer_Common.xml ../Timer/TAGS_VE4.txt 4 #TIMERs
ren "../Timer/Timer_Common_out.txt" "Timer_VE4.txt

