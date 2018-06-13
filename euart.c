#include "euart.h"



void UART1Init()
{
    ANSELHbits.ANS11 = 0;//�������� ����� 
    UART1_TX_TRIS = 0;//����� tx �� �����
    UART1_RX_TRIS = 1;// ����� rx �� ����
    
    TXSTAbits.TX9 = 0;//��� 9 ��������
    TXSTAbits.TXEN = 1;//��������� ��������
    TXSTAbits.SYNC = 0;//����������� �����
    TXSTAbits.BRGH = 0;//������ ��������
    BAUDCONbits.BRG16 = 0;
    SPBRG = BAUDRATEREG;
    
    RCSTAbits.SREN = 1;// ��������� ������ 
    RCSTAbits.RX9 = 0;//��� 9 ��������
    RCSTAbits.CREN = 1;//�������� �����
    
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
    while(TXSTAbits.TRMT == 0);//���� ���� ����� ������
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

