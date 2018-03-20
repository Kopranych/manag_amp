#include "pe42552.h"


init_switch_PE42552(void){
    PE42552_TRIS = 0;
    PE42552_PORT = 0;
}

void switch_PE42552(int com_switch){
    PE42552_PORT = com_switch;
}
