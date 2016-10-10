#include "xc.h"
#include <math.h>
#include "../inc/uart.h"
#ifndef FCY
#define FCY             (unsigned long)7372800 //default FCY 10MHz
#endif
#define UART1_BAUD 115200
#define UART2_BAUD 9600
#define UBRG1_VALUE (FCY/UART1_BAUD)/16 - 1
#define UBRG2_VALUE (FCY/UART2_BAUD)/16 - 1

void InitUART1(void)
{
    U1BRG=UBRG1_VALUE; 
    U1MODEbits.ALTIO=0;
    IEC0bits.U1RXIE=1;
    U1STA&=0xfffc;
    U1MODEbits.UARTEN=1;
    U1STAbits.UTXEN=1;
}
void WriteUART1(unsigned int data)
{
    while (U1STAbits.TRMT==0);
    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}
void WriteStringUART1(const char * s)
{
    while(*s)
            WriteUART1(*s++);
}

void InitUART2(void)
{
    U2BRG = UBRG2_VALUE; 
    U2STA &= 0xfffc;
    IEC1bits.U2RXIE = 1; 
    U2MODEbits.UARTEN = 1; 
    U2STAbits.UTXEN = 1; 
}
void WriteUART2 (unsigned int data)
{
    U2TXREG = data;
    while(!U2STAbits.TRMT){}
}
void WriteStringUART2(const char * s)
{
    while(*s)
            WriteUART2(*s++);
} 
