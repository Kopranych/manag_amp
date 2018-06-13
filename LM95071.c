#include "LM95071.h"



void init_td(void)
{
    CS_TD_TRIS = 0;
}

int read_td(void)
{
    unsigned int temp;
    unsigned int tempdata = 0b11111111;
    CS_TD_PORT = 0;    
    SSPBUF = tempdata;
    while(SSPIF == 0);
    SSPIF = 0;
    temp = SSPBUF;
    CS_TD_PORT = 1;
    return temp;
}
