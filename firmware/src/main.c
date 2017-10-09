/*
 * File:   main.c
 * Author: Andrei
 *
 * Created on June 14, 2016, 7:53 PM
 */

// DSPIC30F4013 Configuration Bit Settings

// 'C' source line config statements

// FOSC
#pragma config FOSFPR = FRC_PLL4        // Oscillator (FRC w/PLL 4x)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_OFF         // POR Timer Value (Timer Disabled)
#pragma config BODENV = BORV27          // Brown Out Voltage (2.7V)
#pragma config BOREN = PBOR_OFF         // PBOR Enable (Disabled)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

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
#include "../inc/SI7021.h"


//_FOSC(CSW_FSCM_OFF & FRC_PLL4); //7.37 MHz Internal RC oscillator, 4x PLL enabled
//_FWDT(WDT_OFF);                 //Watchdog disabled
//-----------------------------------------------------------------

void __attribute__((__interrupt__)) _U1RXInterrupt(void)
{
    IFS0bits.U1RXIF = 0;
}
void __attribute__((__interrupt__)) _U2RXInterrupt(void) {
    IFS1bits.U2RXIF = 0;
}

void sendDataToServer(float magx, float magy, float magz, float temp, float pres, float winds, float hum);

int main(void)
{
    char buf[70];
    int count = 0;
    int mag;
    char msb;
    char lsb;
    float mag_x, mag_y, mag_z, wind_speed, hum, h_temp;
    long t;
    unsigned long p;
    initADC();
    I2C_Init();
    __delay_ms(10);
    InitUART2();
    __delay_ms(10);
    //WriteStringUART2("Starting system\r\n");
    initHMC5883L();
    __delay_ms(10);
    initBMP085();
//    __delay_ms(10);
    initSI7021();
    __delay_ms(100);
    while (1)
    {   
        get_field_x(&mag_x);            
        __delay_ms(10);
        get_field_y(&mag_y);
        __delay_ms(10);
        get_field_z(&mag_z);
//        __delay_ms(10);
//        sprintf(buf, "Mag Raw Data x:%f y:%f z:%f\r\n",mag_x,mag_y,mag_z);
//        __delay_ms(100);
//        WriteStringUART2(buf);
//        __delay_ms(10);
        get_bmp085_data(&p, &t);
//        __delay_ms(10);
//        sprintf(buf, "BMP085 Data Temperature:%ld Pressure:%lu\r\n",t,p);
//        __delay_ms(100);
//        WriteStringUART2(buf);
//        __delay_ms(10);
        wind_speed = getAnemometerAvg();
//        sprintf(buf, "Wind Speed Sensor Raw: %f\r\n",wind_speed);
//        __delay_ms(10);
//        WriteStringUART2(buf);
//        __delay_ms(10);
//        if(get_humidity(&hum, &h_temp) == I2C_ERROR){
//            WriteStringUART2("Error getting humidity\r\n");
//        }
//        else{
//            sprintf(buf, "SI7021 Data Humidity: %f Temperature: %f\r\n", hum, h_temp);
//            __delay_ms(10);
//            WriteStringUART2(buf);
//        }
        sendDataToServer(mag_x, mag_y, mag_z, (float)t/10.0, (float)p/1000.0, wind_speed, 0.0);
        __delay_ms(10000);
    }
    return 0;
}

void sendDataToServer(float magx, float magy, float magz, float temp, float pres, float winds, float hum){
    char buf[255];
    sprintf(buf, "?mag_x=%.2f&mag_y=%.2f&mag_z=%.2f&temp=%.1f&pres=%.3f",magx,magy,magz,temp, pres);
    __delay_ms(10);
    WriteStringUART2(buf);
}