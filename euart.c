#include "euart.h"



void UART1Init()
{
    ANSELHbits.ANS11 = 0;//цифровой вывод 
    UART1_TX_TRIS = 0;//вывод tx на выход
    UART1_RX_TRIS = 1;// вывод rx на вход
    
    TXSTAbits.TX9 = 0;//бит 9 выключен
    TXSTAbits.TXEN = 1;//включение передачи
    TXSTAbits.SYNC = 0;//асинхронный режим
    TXSTAbits.BRGH = 0;//низкая скорость
    BAUDCONbits.BRG16 = 0;
    SPBRG = BAUDRATEREG;
    
    RCSTAbits.SREN = 1;// включение модуля 
    RCSTAbits.RX9 = 0;//бит 9 выключен
    RCSTAbits.CREN = 1;//включить прием
    
    /////////////////////////
}    



//char UART1GetChar()
//{
//    char Temp;
//    while(IFS0bits.U1RXIF == 0);
//    Temp = U1RXREG;
//    IFS0bits.U1RXIF = 0;
//    return Temp;
//}

void UART1PutChar(char Ch)
{
    while(TXSTAbits.TRMT == 0);//ждем пока буфер полный
    TXREG1 = Ch;
}


void UART1PutStr(char str[]){
    int size = strlen(str);
    int i;
    for(i = 0; i < size;i++){
        UART1PutChar(str[i]);
    }
    UART1PutChar(0xD);
    UART1PutChar(0xA);
}

