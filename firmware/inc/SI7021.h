
#ifndef SI7021_H
#define	SI7021_H

#include <xc.h>

#ifndef FCY
#define FCY             (unsigned long)7372800 //default FCY 10MHz
#endif
#include <libpic30.h>

#define SI7021              0x40
#define SI7021_HUM_MASTER   0xE5
#define SI7021_HUM          0xF5
#define SI7021_TEMP_MASTER  0xE3
#define SI7021_TEMP         0xF3
#define SI7021_TEMP_PREV    0xE0
#define SI7021_RESET        0xFE
#define SI7021_USER_W       0xE6
#define SI7021_USER_R       0xE7
#define SI7021_HEATER_W     0x51
#define SI7021_HEATER_R     0x11
#define MEAS_RETRY          0xFF

/**
 * Initialize the device with specific settings.
 * Default Values:
 *      User Register: 0x3A
 *          Resolution: 12bit RH, 14bit Temp
 *          Heater: Disabled
 *      Heater Register: 0x00
 *          Heater Current: 3.09mA
 * @return I2C_OK on success, I2C_ERROR on failure
 */
int initSI7021(void);

#endif	