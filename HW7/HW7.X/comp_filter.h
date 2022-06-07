#ifndef __COMP_FILTER_H__
#define __COMP_FILTER_H__

#include "mpu6050.h"

#define DT 0.01
#define A 0.5
#define COUNT 480000
#define NUM_DATA_POINTS 14

void comp_filt(uint8_t  *, float *);


#endif
