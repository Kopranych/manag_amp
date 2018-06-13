/* 
 * File:   spi.h
 * Author: Kopranov_IN
 *
 * Created on 21 Март 2018 г., 17:09
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SPI_SDO_TRIS TRISCbits.RC7
#define SPI_SCK_TRIS TRISBbits.RB6
#define SPI_SDI_TRIS TRISBbits.RB4   
#define SPI_CS_TRIS  TRISCbits.RC1
#define SPI_CS_PORT  PORTCbits.RC1

void init_spi(void);
unsigned int spi_txrx(unsigned int data);


#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

