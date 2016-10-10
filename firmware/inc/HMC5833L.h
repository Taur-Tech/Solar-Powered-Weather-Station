#ifndef HMC5883L_H
#define	HMC5883L_H

#include <xc.h>

#ifndef FCY
#define FCY             (unsigned long)10000000 //default FCY 10MHz
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


#endif	
