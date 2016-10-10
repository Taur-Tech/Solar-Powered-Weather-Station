/*
 * File:   HMC5883L.c
 * Author: andrei
 *
 * Created on October 6, 2016, 3:07 PM
 */


#include "xc.h"
#include "../inc/HMC5883L.h"
#include "../inc/i2c.h"
#include "math.h"

float resolution = 0.92;

int two_comp_to_dec(int b){
		if(b & 0x8000){
			b = -1*(0x010000 - b);
        }
		return b;
}

int set_parameter(char reg, char param, unsigned char val){
    char tmp;
    if(I2C_ReadReg(HMC5883L, reg, &tmp) == I2C_ERROR){
        return I2C_ERROR;
    }
    tmp &= param;
    tmp |= val;
    if(I2C_WriteReg(HMC5883L, reg, tmp) == I2C_ERROR){
        return I2C_ERROR;
    }
    if(param == RESOLUTION){
        switch(val){
            case 0: resolution=0.73;break;
            case 32: resolution=0.92;break;
            case 64: resolution=1.22;break;
            case 96: resolution=1.52;break;
            case 128: resolution=2.27;break;
            case 160: resolution=2.56;break;
            case 192: resolution=3.03;break;
            case 224: resolution=4.35;break;
            default: break;
        }
    }
    return I2C_OK;
}

int initHMC5883L(void){
    return set_parameter(HMC5883L_MODE, MODE, 0);        
}

int get_field_x(float *val){
    char msb, lsb;
    int tmp;
    if(I2C_ReadReg(HMC5883L, HMC5883L_X_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(HMC5883L, HMC5883L_X_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    tmp = two_comp_to_dec(msb<<8 | lsb);
    *val = (float)tmp*resolution;
    return I2C_OK;
}

int get_field_y(float *val){
    char msb, lsb;
    int tmp;
    if(I2C_ReadReg(HMC5883L, HMC5883L_Y_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(HMC5883L, HMC5883L_Y_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    tmp = two_comp_to_dec(msb<<8 | lsb);
    *val = (float)tmp*resolution;
    return I2C_OK;
}

int get_field_z(float *val){
    char msb, lsb;
    int tmp;
    if(I2C_ReadReg(HMC5883L, HMC5883L_Z_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(HMC5883L, HMC5883L_Z_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    tmp = two_comp_to_dec(msb<<8 | lsb);
    *val = (float)tmp*resolution;
    return I2C_OK;
}