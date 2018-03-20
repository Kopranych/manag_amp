/* 
 * File:   euart.h
 * Author: Kopranov_IN
 *
 * Created on 15 ���� 2018 �., 14:07
 */

#ifndef EUART_H
#define	EUART_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <string.h>
#include <pic18f14k22.h>
    
#define SYSCLKU 40000000L
#define BAUDRATE 115200
#define BAUDRATEREG SYSCLKU/8/BAUDRATE-1
#define UART1_RX_TRIS TRISBbits.TRISB5
#define UART1_TX_TRIS TRISBbits.TRISB7

    
void UART1Init();
char UART1GetChar();
void UART1PutChar(char Ch);
void UART1PutStr(char* str);

#ifdef	__cplusplus
}
#endif

#endif	/* EUART_H */

