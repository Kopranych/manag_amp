/* 
 * File:   pe4312.h
 * Device Attenuator
 * Author: Kopranov_IN
 *
 * Created on 22 Март 2018 г., 11:39
 */

#ifndef PE4312_H
#define	PE4312_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <pic18f14k22.h> 
#include<stdbool.h>

#define PS_ATT_TRIS TRISAbits.RA5
#define PS_ATT_PORT PORTAbits.RA5
#define LE_ATT1_TRIS TRISCbits.RC0
#define LE_ATT1_PORT PORTCbits.RC0
#define LE_ATT2_TRIS TRISCbits.RC1
#define LE_ATT2_PORT PORTCbits.RC1
#define SPI_SDO_TRIS TRISCbits.RC7
#define SPI_SCK_TRIS TRISBbits.RB6
#define SPI_SDI_TRIS TRISBbits.RB4   

void init_att(void);
unsigned int spi_txrx_att1(unsigned int data);
unsigned int spi_txrx_att2(unsigned int data);
_Bool valid_ps (void);

#ifdef	__cplusplus
}
#endif

#endif	/* PE4312_H */

