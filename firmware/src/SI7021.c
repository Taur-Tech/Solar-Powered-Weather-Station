#include "../inc/i2c.h"
#include "../inc/SI7021.h"

int initSI7021(void){
//    char tmp;
//    if(I2C_ReadReg(SI7021, SI7021_USER_R, &tmp) == I2C_ERROR){
//        return I2C_ERROR;
//    }
    return I2C_OK;
}

int get_humidity(float *hum, float *temp){
    int raw_hum, raw_temp;
    float tmp;    
    if(I2C_ReadReg16_Repeat(SI7021, SI7021_HUM, &raw_hum, MEAS_RETRY) == I2C_ERROR){
        return I2C_ERROR;
    }
    tmp = (float)(125*raw_hum)/65536 - 6;
    if(tmp < 0)
        *hum = 0;
    else if(tmp > 100)
        *hum = 100;
    else
        *hum = tmp;
    if(I2C_ReadReg16(SI7021, SI7021_TEMP_PREV, &raw_temp) == I2C_ERROR){
        return I2C_ERROR;
    }
    tmp = (float)(175.72*raw_temp)/65536 - 46.85;
}