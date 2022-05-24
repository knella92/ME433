#include "hw6_func.h"
#include "i2c_master_noint.h"

void setPin(unsigned char rgstr, unsigned char value){
    i2c_master_start();
    i2c_master_send(0b01000000);
    i2c_master_send(rgstr);
    i2c_master_send(value); 
    i2c_master_stop();
    
}

unsigned char readPin(unsigned char rgstr){
    i2c_master_start();
    i2c_master_send(0b01000000);
    i2c_master_send(rgstr);
    i2c_master_restart();
    i2c_master_send(0b01000001);
    unsigned char value = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    return value;
}