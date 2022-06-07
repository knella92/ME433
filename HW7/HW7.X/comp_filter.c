#include "comp_filter.h"
#include <xc.h>
#include <math.h>
#include "UART1.h"
#include <stdio.h>



void comp_filt(uint8_t * imu_buf, float * pitch){
    float theta_xl = 0;
    float phi_xl = 0;
    float ax, ay, az, gx, gy;
                        
    ax = conv_xXL(imu_buf);
    ay = conv_yXL(imu_buf);
    az = conv_zXL(imu_buf);
    gx = conv_xG(imu_buf);
    gy = conv_yG(imu_buf);

    theta_xl = atan2f(ax,az);
    phi_xl = atan2f(gx,gy);

    *pitch += gx*DT;
    *pitch = A*theta_xl + (1-A)* *pitch;

    char msg[100];

    sprintf(msg, "%f\r\n", pitch);
    WriteUART1(msg);
     
     
}