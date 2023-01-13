/**
 * @file hwl_ExternalFlash.h
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-08-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HWL_EXTERNALFLASH_H
#define HWL_EXTERNALFLASH_H

#include "main.h"

//#define USEDMA
#define EXTFLASHCSPINHIGH       HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);
#define EXTFLASHCSPINLOW        HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
#define EXTFLASHBUFFERSIZE      260

#define SPI_SCK_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE();
#define SPI_SCK_PIN             GPIO_PIN_13
#define SPI_SCK_PORT            GPIOB
#define SPI_SCK_MODE            GPIO_MODE_AF_PP
#define SPI_SCK_PULL            GPIO_NOPULL
#define SPI_SCK_SPEED           GPIO_SPEED_FREQ_HIGH
#define SPI_SCK_ALTERNATE       GPIO_AF5_SPI2

#define SPI_MISO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE();
#define SPI_MISO_PIN            GPIO_PIN_14
#define SPI_MISO_PORT           GPIOB
#define SPI_MISO_MODE           GPIO_MODE_AF_PP
#define SPI_MISO_PULL           GPIO_NOPULL
#define SPI_MISO_SPEED          GPIO_SPEED_FREQ_HIGH
#define SPI_MISO_ALTERNATE      GPIO_AF5_SPI2

#define SPI_MOSI_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE();
#define SPI_MOSI_PIN            GPIO_PIN_15
#define SPI_MOSI_PORT           GPIOB
#define SPI_MOSI_MODE           GPIO_MODE_AF_PP
#define SPI_MOSI_PULL           GPIO_NOPULL
#define SPI_MOSI_SPEED          GPIO_SPEED_FREQ_HIGH
#define SPI_MOSI_ALTERNATE      GPIO_AF5_SPI2

#define SPI_CS_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE();
#define SPI_CS_PIN              GPIO_PIN_12
#define SPI_CS_PORT             GPIOB
#define SPI_CS_MODE             GPIO_MODE_OUTPUT_PP;
#define SPI_CS_PULL             GPIO_NOPULL
#define SPI_CS_SPEED            GPIO_SPEED_FREQ_HIGH

//Mx25l12833f Commands
#define MX25_READ_NORMAL        0x03
#define MX25_READ_FAST          0x0B
#define MX25_READ_2             0xBB
#define MX25_READ_D             0x3B
#define MX25_READ_4             0xEB
#define MX25_READ_Q             0x6B
#define MX25_PAGEPROGRAM        0x02
#define MX25_PAGEPROGRAM_4      0x38
#define MX25_SECTORERASE        0x20
#define MX25_BLOCKERASE_32K     0x52
#define MX25_BLOCKERASE_64K     0xD8
#define MX25_CHIPERASE          0xC7

//Mx25l12833f Device Operations
#define MX25_WRITEENABLE        0x06
#define MX25_WRITEDISABLE       0x04
#define MX25_WRITEPROTECT       0x68
#define MX25_ENABLEQPI          0x35
#define MX25_RESETQPI           0xF5
#define MX25_SUSPEND            0xB0
#define MX25_RESUME             0x30
#define MX25_POWERDOWN          0xB9
#define MX25_RELEASEPOWERDOWN   0xAB
#define MX25_NOP                0x00
#define MX25_RESETENABLE        0x66
#define MX25_RESETMEMORY        0x99
#define MX25_GANGBLOCKLOCK      0x7E
#define MX25_GANGBLOCKUNLOCK    0x98
#define MX25_FACTORYMODEENABLE  0x41

//Mx25l12833f Register Access
#define MX25_RDID               0x9F
#define MX25_RES                0xAB
#define MX25_REMS               0x90
#define MX25_QPIID              0xAF
#define MX25_RDSFDP             0x5A
#define MX25_RDSR               0x05
#define MX25_RDCR               0x15
#define MX25_WRSR               0x01
#define MX25_RDSCUR             0x2B
#define MX25_WRSCUR             0x2F
#define MX25_SBL                0xC0
#define MX25_ENSO               0xB1
#define MX25_EXSO               0xC1
#define MX25_WRLR               0x2C
#define MX25_RDLR               0x2D
#define MX25_WRSPB              0xE3
#define MX25_ESSPB              0xE4
#define MX25_RDSPB              0xE2
#define MX25_WRDPB              0xE1
#define MX25_RDDPB              0xE0

typedef struct
{
    unsigned char Status;
    unsigned short Sector;
    unsigned char Page;
}ExtFlashExtFlash_t;

typedef struct
{
    unsigned char WIP;  //write in progress
    unsigned char WEL;  //Write Enable Latch
    unsigned char BP0;  //Level Of Protected Block
    unsigned char BP1;  //Level Of Protected Block
    unsigned char BP2;  //Level Of Protected Block
    unsigned char BP3;  //Level Of Protected Block
    unsigned char QE;   //Quad Enable
    unsigned char SRWD; //status register write disable bit
}ExtFlashStatusRegister_t;

typedef struct
{
    unsigned char SOTP;
    unsigned char LDSO;
    unsigned char PSB;
    unsigned char ESB;
    unsigned char PFAIL;
    unsigned char EFAIL;
    unsigned char WPSEL;
}ExtFlashSecurityRegister_t;

typedef enum 
{
	None,
  EraseError,
	EraseSuccess,
	ProgrammingError,
	ProgrammingSuccess,
	IncorrectFirmware,
	CorrectFirmware,
	ContainFirmware,
	NotContainFirmware,
}ExtFlashStatus_t;

void hwl_ExtFlashInit(void);
uint8_t hwl_ExtFlashWriteCommand(uint8_t command, uint8_t registerData[], uint8_t size);
uint8_t hwl_ExtFlashReadStatusRegister(uint8_t registerData[], ExtFlashStatusRegister_t *status);
uint8_t hwl_ExtFlashReadSecurityRegister(uint8_t registerData[], ExtFlashSecurityRegister_t *status);
uint8_t hwl_ExtFlashSectorErase(uint32_t sector);
uint8_t hwl_ExtFlashPageProgram(uint32_t sector, uint8_t *data);
uint8_t hwl_ExtFlashCheckPage(uint32_t sector, uint8_t *data);
void hwl_ExtFlashResetQPIMode(void);

#endif
