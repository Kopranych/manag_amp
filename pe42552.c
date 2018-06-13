#include "pe42552.h"


void init_switch(void){
    SWITCH_TRIS = 0;
    SWITCH_PORT = 0;
}

void switching(int com_switch){
    SWITCH_PORT = com_switch;
}
