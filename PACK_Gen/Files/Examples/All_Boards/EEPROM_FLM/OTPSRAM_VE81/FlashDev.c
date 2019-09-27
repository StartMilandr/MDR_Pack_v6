/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright (c) 2010 Keil - An ARM Company. All rights reserved.     */
/***********************************************************************/
/*                                                                     */
/*  FlashDev.C:  Device Description for New Device Flash               */
/*                                                                     */
/***********************************************************************/

#include "FlashOS.H"        // FlashOS Structures


struct FlashDevice const FlashDevice  =  {
   FLASH_DRV_VERS,             // Driver Version, do not modify!
   "Milandr 1986VE81 OTPSRAM",   // Device Name 
   ONCHIP,                     // Device Type
   0x01000000,                 // Device Start Address
   0x00020000,                 // Device Size in Bytes (128kB)
   0x1000,                     // Programming Page Size
   0,                          // Reserved, must be 0
   0x00,                       // Initial Content of Erased Memory
   5000,                       // Program Page Timeout 5 Sec
   5000,                       // Erase Sector Timeout 5 Sec

// Specify Size and Address of Sectors
   0x00001000, 0x00000000,     // Page Size  4KB (32 Pages)
   SECTOR_END
};
