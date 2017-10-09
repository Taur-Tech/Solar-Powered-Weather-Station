/*
 * File:   BMP085.c
 * Author: andrei
 *
 * Created on October 5, 2016, 10:03 PM
 */

#include "xc.h"
#include "../inc/BMP085.h"
#include "../inc/i2c.h"
#include "../inc/uart.h"
#include <stdio.h>
#include "math.h"

long b5;
char buf[30];

struct bmp085_cal{
    short ac1;
    short ac2;
    short ac3;
    unsigned short ac4;
    unsigned short ac5;
    unsigned short ac6;
    short b1;
    short b2;
    short mb;
    short mc;
    short md;
    
}BMP085CAL;

int read_cal_data(struct bmp085_cal *BMP085Cal){
    unsigned char msb, lsb;
    if(I2C_ReadReg(BMP085, BMP085_AC1_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
//    sprintf(buf, "AC1MSB:%x\r\n",msb);
//    __delay_ms(10);
//    WriteStringUART2(buf);
//    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_AC1_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
//    sprintf(buf, "AC1LSB:%x\r\n",lsb);
//    __delay_ms(100);
//    WriteStringUART2(buf);
//    __delay_ms(5);
    BMP085Cal->ac1 = (short)((msb<<8) + lsb);   
//    __delay_ms(10);
//    sprintf(buf, "AC1:%d\r\n",BMP085Cal->ac1);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    if(I2C_ReadReg(BMP085, BMP085_AC2_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_AC2_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->ac2 = (short)((msb<<8) | lsb);
//    __delay_ms(10);
//    sprintf(buf, "AC2:%d\r\n",BMP085Cal->ac2);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    if(I2C_ReadReg(BMP085, BMP085_AC3_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_AC3_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->ac3 = (short)((msb<<8) | lsb);
//    __delay_ms(10);
//    sprintf(buf, "AC3:%d\r\n",BMP085Cal->ac3);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    if(I2C_ReadReg(BMP085, BMP085_AC4_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_AC4_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->ac4 = (unsigned short)((msb<<8) | lsb);
//    __delay_ms(10);
//    sprintf(buf, "AC4:%u\r\n",BMP085Cal->ac4);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    if(I2C_ReadReg(BMP085, BMP085_AC5_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_AC5_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->ac5 = (unsigned short)((msb<<8) | lsb);
//    __delay_ms(10);
//    sprintf(buf, "AC5:%u\r\n",BMP085Cal->ac5);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    if(I2C_ReadReg(BMP085, BMP085_AC6_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_AC6_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->ac6 = (unsigned short)((msb<<8) | lsb);
//    __delay_ms(10);
//    sprintf(buf, "AC6:%u\r\n",BMP085Cal->ac6);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    if(I2C_ReadReg(BMP085, BMP085_B1_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_B1_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->b1 = (short)((msb<<8) | lsb);
//    __delay_ms(10);
//    sprintf(buf, "B1:%d\r\n",BMP085Cal->b1);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    if(I2C_ReadReg(BMP085, BMP085_B2_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_B2_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->b2 = (short)((msb<<8) | lsb);
//    __delay_ms(10);
//    sprintf(buf, "B2:%d\r\n",BMP085Cal->b2);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    if(I2C_ReadReg(BMP085, BMP085_MB_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_MB_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->mb = (short)((msb<<8) | lsb);
//    __delay_ms(10);
//    sprintf(buf, "MB:%d\r\n",BMP085Cal->mb);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    if(I2C_ReadReg(BMP085, BMP085_MC_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_MC_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->mc = (short)((msb<<8) | lsb);
//    __delay_ms(10);
//    sprintf(buf, "MC:%d\r\n",BMP085Cal->mc);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    if(I2C_ReadReg(BMP085, BMP085_MD_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(5);
    if(I2C_ReadReg(BMP085, BMP085_MD_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    BMP085Cal->md = (short)((msb<<8) | lsb);
//    __delay_ms(10);
//    sprintf(buf, "MD:%d\r\n",BMP085Cal->md);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    return I2C_OK;
}

int get_raw_temp(long *t){
    unsigned char msb, lsb;
    long temp;
    if(I2C_WriteReg(BMP085, BMP085_BUF_RD, BMP085_T_READ) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(10);
    if(I2C_ReadReg(BMP085, BMP085_BUF_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    if(I2C_ReadReg(BMP085, BMP085_BUF_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    
    temp = (long)((msb<<8) | lsb);
//     __delay_ms(10);
//    sprintf(buf, "RT:%ld\r\n",temp);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    *t = temp;
    return I2C_OK;
}

int get_raw_press(unsigned long *p){
    unsigned char msb, lsb, xlsb;
    unsigned int pressure;
    if(I2C_WriteReg(BMP085, BMP085_BUF_RD, BMP085_P_READ) == I2C_ERROR){
        return I2C_ERROR;
    }
    __delay_ms(10);
    if(I2C_ReadReg(BMP085, BMP085_BUF_MSB, &msb) == I2C_ERROR){
        return I2C_ERROR;
    }
    if(I2C_ReadReg(BMP085, BMP085_BUF_LSB, &lsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    if(I2C_ReadReg(BMP085, BMP085_BUF_XLSB, &xlsb) == I2C_ERROR){
        return I2C_ERROR;
    }    
    __delay_ms(5);
    pressure = (msb<<8) | lsb;
//    __delay_ms(10);
//    sprintf(buf, "RP:%u\r\n", pressure);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    *p = pressure;
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
//    __delay_ms(10);
//    sprintf(buf, "B5:%ld\r\n",b5);
//    __delay_ms(100);
//    WriteStringUART2(buf);
    *t = (long)(b5+8)/pow(2,4);
    return I2C_OK;
}

int get_bmp085_data(unsigned long *p, long *t){
    long b3, b6, x1, x2, x3;
    unsigned long b4, b7;
    unsigned long p1, p2;
    if(get_raw_press(&p1) == I2C_ERROR){
        return I2C_ERROR;
    }
    //needed to update b5 parameter
    if(get_temperature(t) == I2C_ERROR){
        return I2C_ERROR;
    }
    b6 = b5 - 4000;
//    __delay_ms(10);
//    sprintf(buf, "B6:%ld\r\n",b6);
//    __delay_ms(10);
//    WriteStringUART2(buf);    
    x1 = (BMP085CAL.b2*(b6*b6/pow(2,12)))/pow(2,11);
//    __delay_ms(10);
//    sprintf(buf, "X1:%ld\r\n",x1);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    x2 = BMP085CAL.ac2*b6/pow(2,11);
//    __delay_ms(10);
//    sprintf(buf, "X2:%ld\r\n",x2);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    x3 = x1 + x2;
//    __delay_ms(10);
//    sprintf(buf, "X3:%ld\r\n",x3);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    b3 = ((BMP085CAL.ac1*4+x3)+2)/4;
//    __delay_ms(10);
//    sprintf(buf, "B3:%ld\r\n",b3);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    x1 = BMP085CAL.ac3*b6/pow(2,13);
    x2 = (BMP085CAL.b1*(b6*b6/pow(2,12)))/pow(2,16);
    x3 = ((x1 + x2)+2)/4;
    b4 = BMP085CAL.ac4*(unsigned long)(x3+32768)/pow(2,15);    
//    __delay_ms(10);
//    sprintf(buf, "B4:%lu\r\n",b4);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    
    b7 = ((unsigned long)p1 - b3)*50000;
//    __delay_ms(10);
//    sprintf(buf, "B7:%lu\r\n",b7);
//    __delay_ms(10);
//    WriteStringUART2(buf);
    if(b7 < 0x80000000){
        p2 = (b7*2)/b4;
    }
    else{
        p2 = (b7/b4)*2;
    }
    x1 = (p2/pow(2,8))*(p2/pow(2,8));
    x1 = (x1*3038)/pow(2,16);
    x2 = (-7357*p2)/pow(2,16);
    *p = (unsigned long)(p2 + (x1+x2+3791)/pow(2,4));
    return I2C_OK;
}

int initBMP085(void){
   return read_cal_data(&BMP085CAL);
}