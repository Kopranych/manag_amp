/* 
 * File:   pe42552.h
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
 
#define PE42552_TRIS TRISCbits.RC0
#define PE42552_PORT PORTCbits.C2INP
#define RFC_RF1 1
#define RFC_RF2 0

///////////////////////////////////////////////
void init_switch_PE42552(void);
void switch_PE42552(int com_switch);


#ifdef	__cplusplus
}
#endif

#endif	/* PE42552_H */


