/*
 * File:   main.c
 * Author: Andrei
 *
 * Created on June 14, 2016, 7:53 PM
 */

// DSPIC30F4013 Configuration Bit Settings

// 'C' source line config statements

// FOSC
#pragma config FOSFPR = FRC_PLL4      // Oscillator (FRC w/PLL 4x)
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
#define FCY (unsigned long)8000000
//#define FCY 60000000ULL
#include <libpic30.h>
#include <stdio.h>
#include "../inc/i2c.h"
#include "../inc/adc.h"
#include "../inc/uart.h"
#include "../inc/HMC5883L.h"
#include "../inc/BMP085.h"
#include "../inc/anemometer.h"
#include "../inc/SI7021.h"
#include "../inc/solar_panel.h"


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

void sendDataToServer(float magx, float magy, float magz, float temp, float pres, float winds, float hum, float sol_out);

int main(void)
{
//    OSCTUNbits.TUN3 = 0;
//    OSCTUNbits.TUN2 = 1;
//    OSCTUNbits.TUN1 = 1;
//    OSCTUNbits.TUN0 = 1;
    TRISDbits.TRISD2 = 0;
    char buf[70];
    int count = 0;
    int mag;
    char msb;
    char lsb;
    float mag_x, mag_y, mag_z, wind_speed, hum, h_temp, solar_panel_output;
    float sum_mag_x = 0, sum_mag_y = 0, sum_mag_z = 0, sum_solar_out = 0, sum_p = 0, sum_t = 0;
    long t;
    unsigned long p; 
    InitUART2();
    __delay_ms(10);
    WriteStringUART2("Starting system\r\n");
    initADC();
    I2C_Init();
    __delay_ms(10);
    initHMC5883L();
    __delay_ms(10);
    initBMP085();
//    __delay_ms(10);
//    initSI7021();
    __delay_ms(100);
    while (1)
    {   
        count++;
        get_field_x(&mag_x);   
        sum_mag_x += mag_x;
        __delay_ms(1);
        get_field_y(&mag_y);
        sum_mag_y += mag_y;
        __delay_ms(1);
        get_field_z(&mag_z);
        sum_mag_z += mag_z;
        __delay_ms(1);
        get_bmp085_data(&p, &t);
        sum_p += (float)p/1000.0;
        sum_t += (float)t/10.0;
        __delay_ms(1);
        solar_panel_output = getSolarPanelOutput();
        sum_solar_out += solar_panel_output;
        __delay_ms(1);
//        wind_speed = getAnemometerAvg();
//        __delay_ms(1);
//        if(get_humidity(&hum, &h_temp) == I2C_ERROR){
//            WriteStringUART2("Error getting humidity\r\n");
//        }
//        else{
//            sprintf(buf, "SI7021 Data Humidity: %f Temperature: %f\r\n", hum, h_temp);
//            __delay_ms(10);
//            WriteStringUART2(buf);
//        }
        if(count == 100){                    
            sendDataToServer(sum_mag_x/100.0, sum_mag_y/100.0, sum_mag_z/100.0, sum_t/100.0, sum_p/100.0, 0.0, 0.0, sum_solar_out/100.0);
            count = 0;    
            sum_mag_x = 0.0;
            sum_mag_y = 0.0;
            sum_mag_z = 0.0;
            sum_t = 0.0;
            sum_p = 0.0;
            sum_solar_out = 0.0;
        }        
        __delay_ms(6000);
    }
    return 0;
}

void sendDataToServer(float magx, float magy, float magz, float temp, float pres, float winds, float hum, float sol_out){
    char buf[255];
    sprintf(buf, "?mag_x=%.2f&mag_y=%.2f&mag_z=%.2f&temp=%.1f&pres=%.3f&sol=%.3f",magx,magy,magz,temp, pres, sol_out);
    __delay_ms(10);
    WriteStringUART2(buf);
}