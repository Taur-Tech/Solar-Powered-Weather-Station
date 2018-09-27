/* 
 * File: anemometer.h
 * Author: Andrei Chelariu  
 * Comments:
 * Revision history: 
 */

#ifndef ANEMOMETER_H
#define	ANEMOMETER_H

#include <xc.h>  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#define ANEMOMETER_CHANNEL      8
#define ANEMOMETER_DIFF_CH      1
#define ANEMOMETER_AVG_SIZE     512
#define ANEMOMETER_CALIB_A      1
#define ANEMOMETER_CALIB_B      0

float getAnemometerAvg(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* ANEMOMETER_H */


