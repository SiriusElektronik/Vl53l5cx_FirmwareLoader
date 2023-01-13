/**
 * @file swl_ExternalFlash.h
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-08-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SWL_EXTERNALFLASH_H
#define SWL_EXTERNALFLASH_H

#include "main.h"
#include "hwl_ExternalFlash.h"

void swl_ExtFlashSpiInit(void);
uint8_t swl_ExtFlashSectorErase(uint32_t sector);
void swl_ExtFlashResetQPIMode(void);
void swl_ExtFlashPageProgram(uint32_t sector, uint8_t *data);
void swl_ExtFlashCheckPage(uint32_t sector, uint8_t *data);

#endif
