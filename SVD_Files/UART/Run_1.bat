cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../UART/UART_VE4x.txt"
TextInsert.exe ../UART/UART_Common.xml ../UART/TAGS_VE4x.txt 4 #UARTs
ren "../UART/UART_Common_out.txt" "UART_VE4x.txt
