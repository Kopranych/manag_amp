#include <pic18f14k22.h>

#include "spi.h"


void init_spi(void){
    SPI_SDO_TRIS = 0;
    SPI_SCK_TRIS = 0;
    SPI_CS_TRIS = 0;
    SPI_CS_PORT = 0;
    SPI_SDI_TRIS = 1;
    SSPCON1bits.SSPEN = 1;//включить SPI
    SSPCON1bits.SSPM = 0b10;//мастер режим, clock/64
    SSPCON1bits.CKP = 0;
    SSPSTATbits.CKE = 1;
    
}

unsigned int spi_txrx(unsigned int data){
    SPI_CS_PORT = 0;
    unsigned int temp;
    SSPBUF = data;
    while(SSPIF == 0);
    SSPIF = 0;
    temp = SSPBUF;
    SPI_CS_PORT = 1;
    return temp;
}
