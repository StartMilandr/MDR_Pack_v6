#include <MDR_1923KX028_M0_Ctrl.h>

void MDR_KX028_M0_Clear_TxTermOffsPhyAll(void)
{
  uint32_t tto_tmp;
  // TxTermOffsPhy1 .. Phy6 = 0
  MDR_KX028_WriteReg( MDR_1923KX028_Control_19, 0 );   
  
  // TxTermOffsPhy2 .. Phy12 = 0, 
  tto_tmp = MDR_KX028_ReadReg( MDR_1923KX028_Control_20);	
  tto_tmp &= ~MDR_1923KX028_Ctrl20_TxTermOffsPhy7_12_Msk;   //  0xC0000000;	
  MDR_KX028_WriteReg( MDR_1923KX028_Control_20, tto_tmp );
  
  // TxTermOffsPhy13 .. Phy16 = 0, 
  tto_tmp = MDR_KX028_ReadReg( MDR_1923KX028_Control_21);	
  tto_tmp &= ~MDR_1923KX028_Ctrl21_TxTermOffsPhy13_16_Msk;  //  0xFFF00000;
  MDR_KX028_WriteReg( MDR_1923KX028_Control_21, tto_tmp );
}

void MDR_KX028_M0_SetupBaseAddrRegisters( void )
{
  uint32_t tmp, addr;
  
  tmp  = MDR_KX028_ReadAXI( 0x8bc);                                   // Set bit DBI_RO_WR_EN 
  MDR_KX028_WriteAXI( 0x8bc, ( tmp | 1 ) );
  
  MDR_KX028_WriteAXI( 0x000000, 0x0bad16c3 );                         // Setup DEVICE ID   
  MDR_KX028_WriteAXI( 0x000008, 0x02000000 );                         // Base Class, Sub-Class, Interface (Network controller, Ethernet controller)
  
  MDR_KX028_WriteAXI( 0x100010, 0 );                                  // Disable BAR0
  
  /* Settings for REGION 0 (Inbound)  */
  /* Define Inbound region 0 as MEM region matching BAR2 */
  /* Setup Target Address Registers */
  addr = 0x300000 |( 0 << 9 )|( 1 << 8 )|( 0x14 );
  MDR_KX028_WriteAXI( addr, 0xC0000000 );	                            // Lower Target Address
  
  /* Config the region through the Region Control 1 Register */
  addr = 0x300000 |( 0 << 9 )|( 1 << 8 )|( 0x0 );
  MDR_KX028_WriteAXI( addr, 0x00000000 );    
  
  /* Enable the region */
  addr = 0x300000 |( 0 << 9 )|( 1 << 8 )|( 0x4 );
  MDR_KX028_WriteAXI( addr, 0xC0000200 );    
  
  /* Setup Target Address Registers */
  addr = 0x300000 |( 1 << 9 )|( 1 << 8 )|( 0x14 );
  MDR_KX028_WriteAXI( addr, 0xC0800000 );	                            // Lower Target Address   
  
  /* Config the region through the Region Control 1 Register */
  addr = 0x300000 |( 1 << 9 )|( 1 << 8 )|( 0x0 );
  MDR_KX028_WriteAXI( addr, 0x00000000 );
  
  /* Enable the region */
  addr = 0x300000 |( 1 << 9 )|( 1 << 8 )|( 0x4 );
  MDR_KX028_WriteAXI( addr, 0xC0000400 );
    
  MDR_KX028_M0_Clear_TxTermOffsPhyAll(); 
}


void MDR_KX028_M0_WaitPC_DriverReady(void)
{
  uint32_t pcDriveAck;
  do 
  {
    pcDriveAck = MDR_KX028_ReadAXI(CFG_KX028_PC_ACK_ADDR);
  }while ( ( pcDriveAck & CFG_KX028_PC_ACK_MSK ) != CFG_KX028_PC_ACK_READY );
}

