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
   "MDR1986VE8 OTP HSI",   // Device Name 
   ONCHIP,                     // Device Type
   0x01000000,                 // Device Start Address
   0x00020000,                 // Device Size in Bytes (128kB)
   0x400,                      // Programming Page Size 1 kB
   0,                          // Reserved, must be 0
   0x00,                       // Initial Content of Erased Memory
   120000,                     // Program Page Timeout 120 Sec
   1000,                       // Erase Sector Timeout 1 Sec

// Specify Size and Address of Sectors
   0x00000400, 0x00000000,     // Page Size  1KB (128 Pages)
   SECTOR_END
};
