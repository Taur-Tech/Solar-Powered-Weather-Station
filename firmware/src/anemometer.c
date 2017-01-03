/*
 * File:   anemometer.c
 * Author: andrei
 *
 * Created on December 14, 2016, 8:38 PM
 */

#include "../inc/adc.h"
#include "../inc/anemometer.h"

float getAnemometerAvg(){    
    int i;
    double sum=0;   
    setVrefADC(1);
    setChADC(ANEMOMETER_CHANNEL, ANEMOMETER_DIFF_CH);
    for (i=0; i<ANEMOMETER_AVG_SIZE; i++){
        sum +=getADCVolt();
    }
    return (float)(sum/ANEMOMETER_AVG_SIZE)*ANEMOMETER_CALIB_A + ANEMOMETER_CALIB_B;
}
