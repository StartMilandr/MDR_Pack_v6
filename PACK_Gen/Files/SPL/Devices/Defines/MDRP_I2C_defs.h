#ifndef _MDRP_I2C_DEFS_H
#define _MDRP_I2C_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

//=======================   I2C  =======================
typedef struct
{
  __IO uint32_t PRL;
  __IO uint32_t PRH;
  __IO uint32_t CTR;
  __IO uint32_t RXD;
  __IO uint32_t STA;
  __IO uint32_t TXD;
  __IO uint32_t CMD;
}MDR_I2C_TypeDef;

/* Bit field positions: */
#define I2C_CTR_S_I2C_Pos                       5
#define I2C_CTR_EN_INT_Pos                      6
#define I2C_CTR_EN_I2C_Pos                      7
/* Bit field masks: */
#define I2C_CTR_S_I2C                           ((uint32_t)0x00000020)
#define I2C_CTR_EN_INT                          ((uint32_t)0x00000040)
#define I2C_CTR_EN_I2C                          ((uint32_t)0x00000080)


/* Bit field positions: */
#define I2C_STA_INT_Pos                         0
#define I2C_STA_TR_PROG_Pos                     1
#define I2C_STA_LOST_ARB_Pos                    5
#define I2C_STA_BUSY_Pos                        6
#define I2C_STA_RX_ACK_Pos                      7
/* Bit field masks: */
#define I2C_STA_INT                             ((uint32_t)0x00000001)
#define I2C_STA_TR_PROG                         ((uint32_t)0x00000002)
#define I2C_STA_LOST_ARB                        ((uint32_t)0x00000020)
#define I2C_STA_BUSY                            ((uint32_t)0x00000040)
#define I2C_STA_RX_ACK                          ((uint32_t)0x00000080)

/* Bit field positions: */
#define I2C_CMD_CLRINT_Pos                      0
#define I2C_CMD_ACK_Pos                         3
#define I2C_CMD_WR_Pos                          4
#define I2C_CMD_RD_Pos                          5
#define I2C_CMD_STOP_Pos                        6
#define I2C_CMD_START_Pos                       7
/* Bit field masks: */
#define I2C_CMD_CLRINT                          ((uint32_t)0x00000001)
#define I2C_CMD_ACK                             ((uint32_t)0x00000008)
#define I2C_CMD_WR                              ((uint32_t)0x00000010)
#define I2C_CMD_RD                              ((uint32_t)0x00000020)
#define I2C_CMD_STOP                            ((uint32_t)0x00000040)
#define I2C_CMD_START                           ((uint32_t)0x00000080)



#ifdef __cplusplus
}
#endif

#endif  //  _MDRP_I2C_DEFS_H
