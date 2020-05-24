#ifndef MDR_1923KX029_M2_TABLES_CTRL_H
#define MDR_1923KX029_M2_TABLES_CTRL_H

#include <MDR_1923KX028_TableMAC.h>
#include <MDR_1923KX028_TableVLAN.h>
#include <MDR_1923KX028_Config.h>

//  Обработка старения пакетов
//    framesToProcessMax - сколько фреймов обработать за вызов функции
void MDR_KX028_M2_ProcessTablesAgeing(uint32_t framesToProcessMax);

//  Обучение таблиц маршрутизации, 
//    framesToProcessMax - сколько фреймов обработать за вызов функции
//    возвращает количество обработанных фреймов
uint32_t MDR_KX028_M2_ProcessFramesLearing(uint32_t framesToProcessMax);


#endif  //MDR_1923KX029_M2_TABLES_CTRL_H
