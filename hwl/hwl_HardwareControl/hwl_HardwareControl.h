/**
 * @file hwl_HardwareControl.h
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HWL_HARDWARECONTROL_H
#define HWL_HARDWARECONTROL_H

#include "main.h"

typedef enum 
{
    Off,
    Red,
    Green,
    Blue,
    Yellow,
    White,
    Magenta,
    Cyan
}hwl_Colors;

void hwl_LedControl(hwl_Colors color);

#endif
