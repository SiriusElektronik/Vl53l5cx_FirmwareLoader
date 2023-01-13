/**
 * @file hwl_HardwareControl.c
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "hwl_HardwareControl.h"

void hwl_LedControl(hwl_Colors color)
{
    switch (color)
    {
    case Off:
        HAL_GPIO_WritePin(LRGB_R_GPIO_Port, LRGB_R_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LRGB_G_GPIO_Port, LRGB_G_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LRGB_B_GPIO_Port, LRGB_B_Pin, GPIO_PIN_SET);
        break;
    case Red:
        HAL_GPIO_WritePin(LRGB_R_GPIO_Port, LRGB_R_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LRGB_G_GPIO_Port, LRGB_G_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LRGB_B_GPIO_Port, LRGB_B_Pin, GPIO_PIN_SET);
        break;
    case Green:
        HAL_GPIO_WritePin(LRGB_R_GPIO_Port, LRGB_R_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LRGB_G_GPIO_Port, LRGB_G_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LRGB_B_GPIO_Port, LRGB_B_Pin, GPIO_PIN_SET);
        break;
    case Blue:
        HAL_GPIO_WritePin(LRGB_R_GPIO_Port, LRGB_R_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LRGB_G_GPIO_Port, LRGB_G_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LRGB_B_GPIO_Port, LRGB_B_Pin, GPIO_PIN_RESET);
        break;
    case Yellow:
        HAL_GPIO_WritePin(LRGB_R_GPIO_Port, LRGB_R_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LRGB_G_GPIO_Port, LRGB_G_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LRGB_B_GPIO_Port, LRGB_B_Pin, GPIO_PIN_SET);
        break;
    case White:
        HAL_GPIO_WritePin(LRGB_R_GPIO_Port, LRGB_R_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LRGB_G_GPIO_Port, LRGB_G_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LRGB_B_GPIO_Port, LRGB_B_Pin, GPIO_PIN_RESET);
        break;
    case Magenta:
        HAL_GPIO_WritePin(LRGB_R_GPIO_Port, LRGB_R_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LRGB_G_GPIO_Port, LRGB_G_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LRGB_B_GPIO_Port, LRGB_B_Pin, GPIO_PIN_RESET);
        break;
    case Cyan:
        HAL_GPIO_WritePin(LRGB_R_GPIO_Port, LRGB_R_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LRGB_G_GPIO_Port, LRGB_G_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LRGB_B_GPIO_Port, LRGB_B_Pin, GPIO_PIN_RESET);
        break;
    }
}
