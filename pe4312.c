#include "pe4312.h"



void init_pe4312()
{
    PS_ATT_TRIS = 1;
    LE_ATT1_TRIS = 0;
    LE_ATT2_TRIS = 0;
    SPI_SDO_TRIS = 0;
    SPI_SCK_TRIS = 0;
    SPI_SDI_TRIS = 1;
    SSPCON1bits.SSPEN = 1;//включить SPI
    SSPCON1bits.SSPM = 0b10;//мастер режим, clock/64
    SSPCON1bits.CKP = 0;
    SSPSTATbits.CKE = 1;
    
}

unsigned int spi_txrx_att1(unsigned int data){
    LE_ATT1_PORT = 0;
    unsigned int temp;
    SSPBUF = data;
    while(SSPIF == 0);
    SSPIF = 0;
    temp = SSPBUF;
    LE_ATT1_PORT = 1;
    return temp;
}

unsigned int spi_txrx_att2(unsigned int data){
    LE_ATT2_PORT = 0;
    unsigned int temp;
    SSPBUF = data;
    while(SSPIF == 0);
    SSPIF = 0;
    temp = SSPBUF;
    LE_ATT2_PORT = 1;
    return temp;
}

unsigned int valid_ps ()
{
    if(PS_ATT_PORT){
        return true;
    }else{
        return false;
    }
}
