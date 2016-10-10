#ifndef HMC5883L_H
#define	HMC5883L_H

#include <xc.h>

#ifndef FCY
#define FCY             (unsigned long)7372800 
#endif
#include <libpic30.h>

#define HMC5883L        0x1E
#define HMC5883L_CFG_A  0
#define HMC5883L_CFG_B  1
#define HMC5883L_MODE   2
#define HMC5883L_X_MSB  3
#define HMC5883L_X_LSB  4
#define HMC5883L_Z_MSB  5
#define HMC5883L_Z_LSB  6
#define HMC5883L_Y_MSB  7
#define HMC5883L_Y_LSB  8
#define HMC5883L_STAT   9
#define HMC5883L_ID_A   10
#define HMC5883L_ID_B   11
#define HMC5883L_ID_C   12
#define AVERAGE         0b10011111
#define OUTRATE         0b11100011
#define BIAS            0b11111100
#define RESOLUTION      0b00011111
#define I2C             0b01111111
#define MODE            0b11111100



int initHMC5883L(void);
int set_parameter(unsigned char reg, unsigned char param, unsigned char val);
int get_field_x(float *val);
int get_field_y(float *val);
int get_field_z(float *val);

#endif	
