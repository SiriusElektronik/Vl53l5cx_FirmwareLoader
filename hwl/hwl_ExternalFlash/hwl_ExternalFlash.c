/**
 * @file hwl_ExternalFlash.c
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-08-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"
#include "hwl_ExternalFlash.h"
#include "string.h"
	
SPI_HandleTypeDef hspi2;
	
uint8_t ExtFlashSpiRxBuffer[EXTFLASHBUFFERSIZE];
uint8_t ExtFlashSpiTxBuffer[EXTFLASHBUFFERSIZE];

void hwl_ExtFlashDmaInit()
{
#ifdef USEDMA
    /* DMA controller clock enable */
   __HAL_RCC_DMA2_CLK_ENABLE();    
   /* DMA interrupt init */
   /* DMA2_Stream0_IRQn interrupt configuration */
   HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
   HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
   /* DMA2_Stream3_IRQn interrupt configuration */
   HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
   HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
#endif
}

void hwl_ExtFlashSpiInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    
	__HAL_RCC_SPI2_CLK_ENABLE();

    hspi2.Instance = SPI2;

    SPI_SCK_CLK_ENABLE();

	GPIO_InitStruct.Pin = SPI_SCK_PIN;
	GPIO_InitStruct.Mode = SPI_SCK_MODE;
	GPIO_InitStruct.Pull = SPI_SCK_PULL;
	GPIO_InitStruct.Speed = SPI_SCK_SPEED;
	GPIO_InitStruct.Alternate = SPI_SCK_ALTERNATE;
	HAL_GPIO_Init(SPI_SCK_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = SPI_MISO_PIN;
	GPIO_InitStruct.Mode = SPI_MISO_MODE;
	GPIO_InitStruct.Pull = SPI_MISO_PULL;
	GPIO_InitStruct.Speed = SPI_MISO_SPEED;
	GPIO_InitStruct.Alternate = SPI_MISO_ALTERNATE;
	HAL_GPIO_Init(SPI_MISO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = SPI_MOSI_PIN;
	GPIO_InitStruct.Mode = SPI_MOSI_MODE;
	GPIO_InitStruct.Pull = SPI_MOSI_PULL;
	GPIO_InitStruct.Speed = SPI_MOSI_SPEED;
	GPIO_InitStruct.Alternate = SPI_MOSI_ALTERNATE;
	HAL_GPIO_Init(SPI_MOSI_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = SPI_CS_PIN;
    GPIO_InitStruct.Mode = SPI_CS_MODE;
    GPIO_InitStruct.Pull = SPI_CS_MODE;
    GPIO_InitStruct.Speed = SPI_CS_SPEED;
    HAL_GPIO_Init(SPI_CS_PORT, &GPIO_InitStruct);

	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_HARD_OUTPUT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi2) != HAL_OK)
	{
		Error_Handler();
	}

#ifdef USEDMA
    /* SPI1 DMA Init */
    /* SPI1_RX Init */
    hdma_spi1_rx.Instance = DMA2_Stream0;
    hdma_spi1_rx.Init.Channel = DMA_CHANNEL_3;
    hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_rx.Init.Mode = DMA_NORMAL;
    hdma_spi1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(&hspi1, hdmarx, hdma_spi1_rx);

    /* SPI1_TX Init */
    hdma_spi1_tx.Instance = DMA2_Stream3;
    hdma_spi1_tx.Init.Channel = DMA_CHANNEL_3;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(&hspi1, hdmatx, hdma_spi1_tx);
#endif
}

void hwl_ExtFlashInit()
{
    hwl_ExtFlashDmaInit();
    hwl_ExtFlashSpiInit();
	hwl_ExtFlashResetQPIMode();
}

uint8_t hwl_ExtFlashWriteCommand(uint8_t command, uint8_t registerData[], uint8_t size)
{
	memset(registerData, 0 ,EXTFLASHBUFFERSIZE);
	EXTFLASHCSPINLOW;
    uint8_t transferOK = HAL_SPI_TransmitReceive(&hspi2, &command, &registerData[0], size,500);	
    EXTFLASHCSPINHIGH;
    return transferOK;
}

void hwl_ExtFlashResetQPIMode(void)
{
	hwl_ExtFlashWriteCommand(MX25_WRITEENABLE, ExtFlashSpiRxBuffer, 1);
	for(uint8_t i = 0; i <10; i++)
	{
		HAL_Delay(20);
		hwl_ExtFlashWriteCommand(MX25_RESETQPI, ExtFlashSpiRxBuffer, 1);
	}
}

uint8_t hwl_ExtFlashReadStatusRegister(uint8_t registerData[], ExtFlashStatusRegister_t *status)
{
    uint8_t transferOK = hwl_ExtFlashWriteCommand(MX25_RDSR, registerData, 2);

    if(transferOK==HAL_OK)
    {
        status->SRWD    =   (registerData[1] >> 7) & 0x01;
        status->QE      =   (registerData[1] >> 6) & 0x01;
        status->BP3     =   (registerData[1] >> 5) & 0x01;
        status->BP2     =   (registerData[1] >> 4) & 0x01;
        status->BP1     =   (registerData[1] >> 3) & 0x01;
        status->BP0     =   (registerData[1] >> 2) & 0x01;
        status->WEL     =   (registerData[1] >> 1) & 0x01;
        status->WIP     =   registerData[1] 	   & 0x01;
    }

    return transferOK;
}

uint8_t hwl_ExtFlashReadSecurityRegister(uint8_t registerData[], ExtFlashSecurityRegister_t *status)
{
    uint8_t transferOK = hwl_ExtFlashWriteCommand(MX25_RDSCUR, registerData, 2);

    if(transferOK==HAL_OK)
    {
        status->WPSEL   =   (registerData[1] >> 7) & 0x01;
        status->EFAIL   =   (registerData[1] >> 6) & 0x01;
        status->PFAIL   =   (registerData[1] >> 5) & 0x01;
        status->ESB     =   (registerData[1] >> 3) & 0x01;
        status->PSB     =   (registerData[1] >> 2) & 0x01;
        status->LDSO    =   (registerData[1] >> 1) & 0x01;
        status->SOTP    =   registerData[1]        & 0x01;
    }

    return transferOK;
}

uint8_t hwl_ExtFlashSectorErase(uint32_t sector)
{
    ExtFlashStatusRegister_t FlashStatus;
    ExtFlashSecurityRegister_t SecurityRegister;

    uint8_t eraseOK = FALSE;
    uint8_t i = 0;
    uint8_t transferOK = hwl_ExtFlashWriteCommand(MX25_WRITEENABLE, ExtFlashSpiRxBuffer, 1);
    
    FlashStatus.WEL = 0;
    while(FlashStatus.WEL == 0)
    {
        HAL_Delay(5);
        transferOK = hwl_ExtFlashReadStatusRegister(ExtFlashSpiRxBuffer, &FlashStatus);    
        i++;
        if(i==200)
        {
            transferOK = FALSE;
            return 0;
        }
    }
    i = 0;
    
		ExtFlashSpiTxBuffer[0] = MX25_SECTORERASE;
    ExtFlashSpiTxBuffer[1] = (sector >> 16) & 0xFF;
    ExtFlashSpiTxBuffer[2] = (sector >> 8) & 0xFF;
    ExtFlashSpiTxBuffer[3] = (sector) & 0xFF;

   // transferOK = hwl_ExtFlashWriteCommand(MX25_SECTORERASE, ExtFlashSpiRxBuffer, 4);
		
		EXTFLASHCSPINLOW;
    transferOK = HAL_SPI_Transmit(&hspi2, &ExtFlashSpiTxBuffer[0], 4, HAL_MAX_DELAY);
    EXTFLASHCSPINHIGH;
		
    FlashStatus.WIP=1;
    while(FlashStatus.WIP == 1)
    {
        HAL_Delay(5);
        transferOK=  hwl_ExtFlashReadStatusRegister(ExtFlashSpiRxBuffer, &FlashStatus);
        i++;
        if(i==200)
        {
            return 0;
        }
    }
    i = 0;

    transferOK = hwl_ExtFlashReadStatusRegister(ExtFlashSpiRxBuffer, &FlashStatus);
    transferOK = hwl_ExtFlashReadSecurityRegister(ExtFlashSpiRxBuffer, &SecurityRegister);

    if(transferOK==HAL_OK && SecurityRegister.EFAIL==0 && SecurityRegister.PFAIL==0)
    {
        eraseOK = TRUE;
    }
    else
    {
        eraseOK = FALSE;
    }
        
    return eraseOK;
}

uint8_t hwl_ExtFlashPageProgram(uint32_t sector, uint8_t *data)
{
    ExtFlashStatusRegister_t FlashStatus;
    ExtFlashSecurityRegister_t SecurityRegister;

    uint32_t i;
    uint8_t transferOK;
    uint8_t pageProgramOK = FALSE;

    memset(ExtFlashSpiRxBuffer, 0, EXTFLASHBUFFERSIZE);
    memset(ExtFlashSpiTxBuffer, 0 , EXTFLASHBUFFERSIZE);

    ExtFlashSpiTxBuffer[0] = MX25_PAGEPROGRAM;
    ExtFlashSpiTxBuffer[1] = (sector >> 16) & 0xFF;
    ExtFlashSpiTxBuffer[2] = (sector >> 8) & 0xFF;
    ExtFlashSpiTxBuffer[3] = sector & 0xFF;

    for(i = 4; i < 260; i++)
    {
        ExtFlashSpiTxBuffer[i] = *data;
        data++;
    }
	
	transferOK = hwl_ExtFlashWriteCommand(MX25_WRITEENABLE, ExtFlashSpiRxBuffer, 1);
	
	FlashStatus.WEL = 0;
    while(FlashStatus.WEL == 0)
    {
        HAL_Delay(20);
        transferOK = hwl_ExtFlashReadStatusRegister(ExtFlashSpiRxBuffer, &FlashStatus);    
        i++;
        if(i==200)
        {
            transferOK = FALSE;
            return 0;
        }
    }
    i = 0;
	
    EXTFLASHCSPINLOW;
    transferOK = HAL_SPI_Transmit(&hspi2, &ExtFlashSpiTxBuffer[0], 260, HAL_MAX_DELAY);
    EXTFLASHCSPINHIGH;

    FlashStatus.WIP = 1;

    while (FlashStatus.WIP)
    {
        HAL_Delay(20);

        transferOK = hwl_ExtFlashReadStatusRegister(ExtFlashSpiRxBuffer, &FlashStatus);
        i++;
        if(i == 200)
        {
            return 0;
        }
    }
    i = 0;
    transferOK = hwl_ExtFlashReadStatusRegister(ExtFlashSpiRxBuffer, &FlashStatus);
    transferOK = hwl_ExtFlashReadSecurityRegister(ExtFlashSpiRxBuffer, &SecurityRegister);

    if(transferOK==HAL_OK && SecurityRegister.EFAIL==0 && SecurityRegister.PFAIL==0)
    {
        pageProgramOK = TRUE;
    }
    else
    {
        pageProgramOK = FALSE;
    }
    return pageProgramOK;
}

uint8_t hwl_ExtFlashCheckPage(uint32_t sector, uint8_t *data)
{
    uint8_t transferOK;
    memset(ExtFlashSpiRxBuffer, 0, EXTFLASHBUFFERSIZE);
    memset(ExtFlashSpiTxBuffer, 0 , EXTFLASHBUFFERSIZE);

    ExtFlashSpiTxBuffer[0] = MX25_READ_NORMAL;
    ExtFlashSpiTxBuffer[1] = (sector >> 16) & 0xFF;
    ExtFlashSpiTxBuffer[2] = (sector >> 8) & 0xFF;
    ExtFlashSpiTxBuffer[3] = sector & 0xFF;

    EXTFLASHCSPINLOW;
    transferOK = HAL_SPI_TransmitReceive(&hspi2, &ExtFlashSpiTxBuffer[0], &ExtFlashSpiRxBuffer[0], 260, HAL_MAX_DELAY);
    EXTFLASHCSPINHIGH;
	
	for(uint16_t i = 0; i < 256; i ++)
	{
		data[i] = ExtFlashSpiRxBuffer[i + 4];
	}
    return transferOK;
}
