/**
 * @file swl_ExternalFlash.c
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-08-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "swl_ExternalFlash.h"

void swl_ExtFlashSpiInit(void)
{
    hwl_ExtFlashInit();
}

uint8_t swl_ExtFlashSectorErase(uint32_t sector)
{
    return hwl_ExtFlashSectorErase(sector);
}

void swl_ExtFlashResetQPIMode(void)
{
	hwl_ExtFlashResetQPIMode();
}

void swl_ExtFlashCheckPage(uint32_t sector, uint8_t *data)
{
	hwl_ExtFlashCheckPage(sector, data);
}

void swl_ExtFlashPageProgram(uint32_t sector, uint8_t *data)
{
	hwl_ExtFlashPageProgram(sector, data);
}