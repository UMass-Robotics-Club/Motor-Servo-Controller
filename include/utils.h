#ifndef __UTILS_H
#define __UTILS_H

#include "hardware/gpio.h"

#define sign(val) (val & 1 << (sizeof(val)*4 - 1)) 
#define range(val, min, max) MIN(MAX(val, min), max)

#define pin_change(pin) pin & (GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE)

#endif