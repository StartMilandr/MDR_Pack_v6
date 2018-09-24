rem SVDConv.exe MDR_GPIO_max.svd -o out -b out/logGPIO.txt --generate=header --fields=struct --fields=enum --fields=macro --generate=sfr
rem SVDConv.exe MDR1986VE1_GPIO.svd -o out -b out/logBE1.txt --generate=header --fields=struct --fields=enum --fields=macro --generate=sfr
rem SVDConv.exe MDR1986VE3_GPIO.svd -o out -b out/logBE3.txt --generate=header --fields=struct --fields=enum --fields=macro --generate=sfr

SVDConv.exe MDR1986VE9x_GPIO.svd -o out -b out/logBE9x.txt --generate=header --fields=struct --fields=enum --fields=macro --generate=sfr

rem SVDConv.exe MDR1986VE4_GPIO.svd -o out -b out/logBE4.txt --generate=header --fields=struct --fields=enum --fields=macro --generate=sfr
rem SVDConv.exe MDR1986VK214_GPIO.svd -o out -b out/logBK214.txt --generate=header --fields=struct --fields=enum --fields=macro --generate=sfr
rem SVDConv.exe MDR1986VK234_GPIO.svd -o out -b out/logBK234.txt --generate=header --fields=struct --fields=enum --fields=macro --generate=sfr
rem SVDConv.exe MDR1901VC1_GPIO.svd -o out -b out/logVC1.txt --generate=header --fields=struct --fields=enum --fields=macro --generate=sfr