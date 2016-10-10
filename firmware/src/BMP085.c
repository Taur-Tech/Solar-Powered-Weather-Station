/*
 * File:   BMP085.c
 * Author: andrei
 *
 * Created on October 5, 2016, 10:03 PM
 */

#include "xc.h"
#include "../inc/BMP085.h"
#include "../inc/i2c.h"
#include "math.h"

long b5;

int read_cal_data(struct bmp085_cal *BMP085Cal){
    char msb, lsb;
    if(I2C_ReadReg(BMP085, BMP085_AC1_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_AC1_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->ac1 = msb<<8 | lsb;        
    if(I2C_ReadReg(BMP085, BMP085_AC2_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_AC2_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->ac2 = msb<<8 | lsb;
    if(I2C_ReadReg(BMP085, BMP085_AC3_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_AC3_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->ac3 = msb<<8 | lsb;
    if(I2C_ReadReg(BMP085, BMP085_AC4_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_AC4_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->ac4 = msb<<8 | lsb;
    if(I2C_ReadReg(BMP085, BMP085_AC5_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_AC5_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->ac5 = msb<<8 | lsb;
    if(I2C_ReadReg(BMP085, BMP085_AC6_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_AC6_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->ac6 = msb<<8 | lsb;
    if(I2C_ReadReg(BMP085, BMP085_B1_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_B1_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->b1 = msb<<8 | lsb;
    if(I2C_ReadReg(BMP085, BMP085_B2_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_B2_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->b2 = msb<<8 | lsb;
    if(I2C_ReadReg(BMP085, BMP085_MB_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_MB_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->mb = msb<<8 | lsb;
    if(I2C_ReadReg(BMP085, BMP085_MC_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_MC_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->mc = msb<<8 | lsb;
    if(I2C_ReadReg(BMP085, BMP085_MD_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_MD_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->md = msb<<8 | lsb;
    return I2C_OK;
}

int get_raw_temp(long *t){
    char msb, lsb, xlsb;
    if(I2C_WriteReg(BMP085, BMP085_BUF_RD, BMP085_T_READ) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_BUF_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_BUF_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_BUF_XLSB, &xlsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    *t = (msb<<16 | lsb<<8 | xlsb) >> 8;
    return I2C_OK;
}

int get_raw_press(long *p){
    char msb, lsb, xlsb;
    if(I2C_WriteReg(BMP085, BMP085_BUF_RD, BMP085_P_READ) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_BUF_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_BUF_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_BUF_XLSB, &xlsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    *p = (msb<<16 | lsb<<8 | xlsb) >> 8;
    return I2C_OK;
}

int get_temperature(long *t){
    long x1,x2,t1;
    if(get_raw_temp(&t1) == I2C_ERROR){
        return I2C_ERROR;
    }
    x1 = (t1-BMP085CAL.ac6)*BMP085CAL.ac5/pow(2,15);
    x2 = BMP085CAL.mc*pow(2,11)/(x1+BMP085CAL.md);
    b5 = x1 + x2;
    *t = (b5+8)/pow(2,4);
    return I2C_OK;
}

int get_pressure(long *p){
    long b3, b6, x1, x2, x3, p1, p2, t1;
    unsigned long b4, b7;
    if(get_raw_press(&p1) == I2C_ERROR){
        return I2C_ERROR;
    }
    //needed to update b5 parameter
    if(get_temperature(&t1) == I2C_ERROR){
        return I2C_ERROR;
    }
    b6 = b5 - 4000;
    x1 = (BMP085CAL.b2*(b6*b6/pow(2,12)))/pow(2,11);
    x2 = BMP085CAL.ac2*b6/pow(2,11);
    x3 = x1 + x2;
    b3 = ((BMP085CAL.ac1*4+x3)+2)/4;
    x1 = BMP085CAL.ac3*b6/pow(2,13);
    x2 = (BMP085CAL.b1*(b6*b6/pow(2,12)))/pow(2,16);
    x3 = ((x1 + x2)+2)/4;
    b4 = BMP085CAL.ac4*(unsigned long)(x3+32768)/pow(2,15);    
    b7 = ((unsigned long)p1 - b3)*50000;
    if(b7 < 0x80000000){
        p2 = (b7*2)/b4;
    }
    else{
        p2 = (b7/b4)*2;
    }
    x1 = (p2/pow(2,8))*(p2/pow(2,8));
    x1 = (x1*3038)/pow(2,16);
    x2 = (-7357*p2)/pow(2,16);
    *p = p2 + (x1+x2+3791)/pow(2,4);
    return I2C_OK;
}

int initBMP085(void){
   return read_cal_data(&BMP085CAL);
}