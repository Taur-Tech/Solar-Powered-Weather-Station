/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h>  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#define ANEMOMETER_CHANNEL      8
#define ANEMOMETER_DIFF_CH      1
#define ANEMOMETER_AVG_SIZE     512

float getAnemometerAvg(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

