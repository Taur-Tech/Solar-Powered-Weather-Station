/*
 * File:   solar_panel.c
 * Author: andrei
 *
 * Created on September 27, 2018, 10:36 PM
 */

#include "../inc/adc.h"
#include "../inc/solar_panel.h"

float getSolarPanelOutput(){    
    int i;
    double sum=0;   
    setVrefADC(0);
    setChADC(SOLAR_PANEL_CHANNEL, 0);
    for (i=0; i<SOLAR_PANEL_AVG_SIZE; i++){
        sum +=getADCVolt();
    }
    return (float)(sum/SOLAR_PANEL_AVG_SIZE);
}