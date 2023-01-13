/**
 * @file swl_FlashLoader.c
 * @author Furkan AYDOGAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "swl_FlashLoader.h"
#include "swl_Buffers.h"

int size1,size2,size3,size4;
uint8_t tbuff[256];
uint8_t rbuff[256];

ExtFlashStatus_t swl_CheckFlash(void)
{
	ExtFlashStatus_t Status;
	
	for(uint32_t i = 0x00; i < sizeof(VL53L5CX_FIRMWARE); i = i + 0x100)
	{	  
		swl_ExtFlashCheckPage(i, rbuff);
	
		for(uint16_t a = 0; a < 256; a++)
		{
			if(VL53L5CX_FIRMWARE[i+a] != rbuff[a])
			{
				Status = IncorrectFirmware;
				break;
			}
			else
			{
				Status = CorrectFirmware;
			}
		}
	}
	if(Status == CorrectFirmware)
	{
		swl_ExtFlashCheckPage(sizeof(VL53L5CX_FIRMWARE) + 1024, rbuff);
		for(uint16_t a = 0; a < 256; a++)
		{
			if(VL53L5CX_PARAMETERS[a] != rbuff[a])
			{
				Status = IncorrectFirmware;
				break;
			}
			else
			{
				Status = CorrectFirmware;
			}
		}
	}
	return Status;
}

ExtFlashStatus_t swl_EraseFlash(void)
{
	ExtFlashStatus_t Status;
	
	for(uint32_t i = 0; i < 0x020000; i = i + 0x1000)
		{
			if(swl_ExtFlashSectorErase(i) != TRUE)
			{
				Status = EraseError;
				break;
			}
			else
			{
				Status = EraseSuccess;
			}
		}
	return Status;
}

ExtFlashStatus_t swl_LoadFirmwareToFlash(void)
{
	ExtFlashStatus_t Status;
	
	for(uint32_t i = 0; i < sizeof(VL53L5CX_FIRMWARE); i = i + 256)
	{	  
		swl_ExtFlashPageProgram(i, (uint8_t*)&VL53L5CX_FIRMWARE[i]);
	
		swl_ExtFlashCheckPage(i, rbuff);
	
		for(uint16_t a = 0; a < 1; a++)
		{
			if(VL53L5CX_FIRMWARE[i+a] != rbuff[a])
			{
				Status = ProgrammingError;
				break;
			}
			else
			{
				Status = ProgrammingSuccess;
			}
		}
	}
	if(Status == ProgrammingSuccess)
	{
	
		swl_ExtFlashPageProgram(sizeof(VL53L5CX_FIRMWARE) + 1024, (uint8_t*)&VL53L5CX_PARAMETERS[0]);
		swl_ExtFlashCheckPage(sizeof(VL53L5CX_FIRMWARE) + 1024, rbuff);
		
		for(uint16_t a = 0; a < sizeof(VL53L5CX_PARAMETERS); a++)
		{
			if(VL53L5CX_PARAMETERS[a] != rbuff[a])
			{
				Status = ProgrammingError;
				break;
			}
			else
			{
				Status = ProgrammingSuccess;
			}
		}
	}
	return Status;
}