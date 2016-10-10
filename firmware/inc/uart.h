/* 
 * File:   uart.h
 * Author: Andrei
 *
 * Created on June 14, 2016, 8:28 PM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

void InitUART1(void);
void WriteUART1(unsigned int data);
void WriteStringUART1(const char * s);
void InitUART2(void);
void WriteUART2(unsigned int data);
void WriteStringUART2(const char * s);


#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

