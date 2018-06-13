/* 
 * File:   pe42552.h 
 * Device switch
 * Author: Kopranov_IN
 *
 * Created on 19 Март 2018 г., 13:32
 */

#ifndef PE42552_H
#define	PE42552_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <pic18f14k22.h> 
 
#define SWITCH_TRIS TRISCbits.RC2
#define SWITCH_PORT PORTCbits.RC2
#define EN_AMP 1
#define DIS_AMP 0

///////////////////////////////////////////////
void init_switch(void);
void switching(int com_switch);


#ifdef	__cplusplus
}
#endif

#endif	/* PE42552_H */


