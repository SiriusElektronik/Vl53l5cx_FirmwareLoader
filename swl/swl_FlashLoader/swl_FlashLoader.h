/**
 * @file swl_FlashLoader.h
 * @author Furkan AYDOGAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SWL_FLASHLOADER_H
#define SWL_FLASHLOADER_H

#include "main.h"
#include "swl_ExternalFlash.h"

ExtFlashStatus_t swl_CheckFlash(void);
ExtFlashStatus_t swl_EraseFlash(void);
ExtFlashStatus_t swl_LoadFirmwareToFlash(void);
#endif
