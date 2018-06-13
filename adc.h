/* 
 * File:   adc.h
 * Author: Kopranov_IN
 *
 * Created on 28 Март 2018 г., 10:16
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <pic18f14k22.h>
    
#define ADC_TRIS TRISAbits.TRISA4

    
void init_adc(void);
int read_adc(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

