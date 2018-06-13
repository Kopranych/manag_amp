/* 
 * File:   LM95071.h
 * Author: Kopranov_IN
 *
 * Created on 4 Èþíü 2018 ã., 15:59
 */

#ifndef LM95071_H
#define	LM95071_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <pic18f14k22.h>

#define CS_TD_TRIS TRISCbits.RC5
#define CS_TD_PORT PORTCbits.RC5
    
void init_td(void);
int read_td(void);



#ifdef	__cplusplus
}
#endif

#endif	/* LM95071_H */

