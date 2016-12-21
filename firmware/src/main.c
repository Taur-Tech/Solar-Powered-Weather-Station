/*
 * File:   main.c
 * Author: Andrei
 *
 * Created on June 14, 2016, 7:53 PM
 */


#include <xc.h>
#define FCY (unsigned long)7372800  
#include <libpic30.h>
#include <stdio.h>
#include "../inc/i2c.h"
#include "../inc/adc.h"
#include "../inc/uart.h"
#include "../inc/HMC5883L.h"
#include "../inc/BMP085.h"
#include "../inc/anemometer.h"


_FOSC(CSW_FSCM_OFF & FRC_PLL4); //7.37 MHz Internal RC oscillator, 4x PLL enabled
_FWDT(WDT_OFF);                 //Watchdog disabled
//-----------------------------------------------------------------

void __attribute__((__interrupt__)) _U1RXInterrupt(void)
{
    IFS0bits.U1RXIF = 0;
}
void __attribute__((__interrupt__)) _U2RXInterrupt(void) {
    IFS1bits.U2RXIF = 0;
}

int main(void)
{
    char buf[70];
    int count = 0;
    int mag;
    char msb;
    char lsb;
    float mag_x, mag_y, mag_z, wind_speed;
    long t;
    unsigned long p;
    initADC();
    I2C_Init();
    __delay_ms(10);
    InitUART2();
    __delay_ms(10);
    initHMC5883L();
    __delay_ms(10);
    if(initBMP085() == I2C_ERROR){
        WriteStringUART2("Error init BMP085\r\n");
    }
    else{
         WriteStringUART2("BMP085 Init OK2\r\n");
    }
    __delay_ms(100);
    
    while (1)
    {   
        if(get_field_x(&mag_x) == I2C_ERROR){
            WriteStringUART2("Error getting x mag\r\n");
        }
        __delay_ms(10);
        if(get_field_y(&mag_y) == I2C_ERROR){
            WriteStringUART2("Error getting y mag\r\n");
        }
        __delay_ms(10);
        if(get_field_z(&mag_z) == I2C_ERROR){
            WriteStringUART2("Error getting z mag\r\n");
        }
        __delay_ms(10);
        sprintf(buf, "Mag Raw Data x:%f y:%f z:%f\r\n",mag_x,mag_y,mag_z);
        __delay_ms(100);
        WriteStringUART2(buf);
        __delay_ms(10);
        if(get_bmp085_data(&p, &t) == I2C_ERROR){
            WriteStringUART2("Error getting x mag\r\n");
        }
        __delay_ms(10);
        sprintf(buf, "BMP085 Data temp:%ld pressure:%lu\r\n",t,p);
        __delay_ms(100);
        WriteStringUART2(buf);
        __delay_ms(10);
        wind_speed = getAnemometerAvg();
        sprintf(buf, "Wind Speed Sensor Raw: %f\r\n",wind_speed);
        __delay_ms(100);
        WriteStringUART2(buf);
        __delay_ms(1000);
    }
    return 0;
}
