cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../UART/UART_VC1.txt"
TextInsert.exe ../UART/UART_Common.xml ../UART/TAGS_VC1.txt 4 #UARTs
ren "../UART/UART_Common_out.txt" "UART_VC1.txt

del "../UART/UART_VE19.txt"
TextInsert.exe ../UART/UART_Common.xml ../UART/TAGS_VE19.txt 4 #UARTs
ren "../UART/UART_Common_out.txt" "UART_VE19.txt

del "../UART/UART_VE3.txt"
TextInsert.exe ../UART/UART_Common.xml ../UART/TAGS_VE3.txt 4 #UARTs
ren "../UART/UART_Common_out.txt" "UART_VE3.txt

del "../UART/UART_VE4x.txt"
TextInsert.exe ../UART/UART_Common.xml ../UART/TAGS_VE4x.txt 4 #UARTs
ren "../UART/UART_Common_out.txt" "UART_VE4x.txt

