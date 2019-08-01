cd C:\CODE\PACK\MDR_Pack\SVD_Files\Exe

del "../UART/UART_ESila.txt"
TextInsert.exe ../UART/UART_Common_ESilaVK014.xml ../UART/TAGS_ESila.txt 4 #UARTs
ren "../UART/UART_Common_ESilaVK014_out.txt" "UART_ESila.txt

del "../UART/UART_VK014.txt"
TextInsert.exe ../UART/UART_Common_ESilaVK014.xml ../UART/TAGS_VK014.txt 4 #UARTs
ren "../UART/UART_Common_ESilaVK014_out.txt" "UART_VK014.txt

del "../UART/UART_VE8.txt"
TextInsert.exe ../UART/UART_Common.xml ../UART/TAGS_VE8.txt 4 #UARTs
ren "../UART/UART_Common_out.txt" "UART_VE8.txt