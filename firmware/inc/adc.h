/* 
 * File:   adc.h
 * Author: Andrei
 *
 * Created on December 23, 2015, 11:53 PM
 */

#ifndef ADC_H
#define	ADC_H
#include <xc.h>

#define Y_RESOLUTION_AVDD (float)1.22070312
#define Y_RESOLUTION_VREF (float)0.61035156

void initADC(void);
void startADC(void);
void stopADC(void);
void setChADC(int channel, int diff);
int getADC(void);
float getADCVolt(void);




#endif	/* ADC_H */

