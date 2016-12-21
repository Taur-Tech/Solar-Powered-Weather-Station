#include "../inc/adc.h"

void initADC(void){    
    ADCON1bits.ADON = 0; // turn ADC off
    ADPCFG = 0xFEFD; // all PORTB = Digital; RB8 = analog
    ADCON2bits.VCFG = 0b000; // Vref+ = AVdd, Vref- = AVss
    ADCON1bits.FORM = 0b00; // integer data format
    ADCON1bits.SSRC = 0b111;  // auto convert
    ADCON1bits.ASAM = 0; // control sampling start manually        
    ADCON3bits.ADCS = 0b111111; // 31
    ADCON3bits.SAMC = 0b00001; //1TAD
    // Fsample ~ 30kHz
    ADCON1bits.ADON = 1; // start ADC module
}

void startADC(void){
    ADCON1bits.ADON = 1;
}

void stopADC(void){
    ADCON1bits.ADON = 0;
}

void setChADC(int channel, int diff){
    ADCHSbits.CH0NA = diff;
    ADCHSbits.CH0SA = channel;
}

int getADC(){
    ADCON1bits.SAMP = 1;
    while(!ADCON1bits.DONE);
    return ADCBUF0;
}

float getADCVolt(){
    int buf;
    float vout;
    ADCON1bits.SAMP = 1;
    while(!ADCON1bits.DONE);
    buf = ADCBUF0;
    vout = (float)buf*Y_RESOLUTION;
    return vout;
}