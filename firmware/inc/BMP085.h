#ifndef BMP085_H
#define	BMP085_H

#include <xc.h>

#ifndef FCY
#define FCY             (unsigned long)7372800 //default FCY 10MHz
#endif
#include <libpic30.h>

#define BMP085              0x77
#define BMP085_T_READ       0x2E
#define BMP085_P_READ       0x34
#define BMP085_AC1_MSB      0xAA
#define BMP085_AC1_LSB      0xAB
#define BMP085_AC2_MSB      0xAC
#define BMP085_AC2_LSB      0xAD
#define BMP085_AC3_MSB      0xAE
#define BMP085_AC3_LSB      0xAF
#define BMP085_AC4_MSB      0xB0
#define BMP085_AC4_LSB      0xB1
#define BMP085_AC5_MSB      0xB2
#define BMP085_AC5_LSB      0xB3
#define BMP085_AC6_MSB      0xB4
#define BMP085_AC6_LSB      0xB5
#define BMP085_B1_MSB       0xB6
#define BMP085_B1_LSB       0xB7
#define BMP085_B2_MSB       0xB8
#define BMP085_B2_LSB       0xB9
#define BMP085_MB_MSB       0xBA
#define BMP085_MB_LSB       0xBB
#define BMP085_MC_MSB       0xBC
#define BMP085_MC_LSB       0xBD
#define BMP085_MD_MSB       0xBE
#define BMP085_MD_LSB       0xBF
#define BMP085_BUF_RD       0xF4
#define BMP085_BUF_MSB      0xF6
#define BMP085_BUF_LSB      0xF7
#define BMP085_BUF_XLSB     0xF8

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

int initBMP085(void);
int get_temperature(long *t);
int get_pressure(long *p);

#endif	
