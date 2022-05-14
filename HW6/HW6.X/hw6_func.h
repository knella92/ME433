#ifndef HW6_FUNC_H__
#define HW6_FUNC_H__
// Header file for i2c_master_noint.c
// helps implement use I2C1 as a master without using interrupts

#include <xc.h>

void setPin(unsigned char, unsigned char);
unsigned char readPin(unsigned char);

#endif
