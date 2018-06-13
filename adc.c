#include "adc.h"


void init_adc(void){
    ADC_TRIS = 1;//����� �� ����
    PIR1bits.ADIF = 0;//����� ����� ����������
    ANSELbits.ANS4 = 1;//���������� �����
    ADCON0bits.CHS = 0b0011;//����� ������ AN3    
    ADCON1bits.PVCFG = 0;//������� ���������� ���������� �� ������������ Vdd
    ADCON1bits.NVCFG = 0;//������� ���������� ���������� �� GND
    ADCON2bits.ADFM = 1;//������ �������� ������
    ADCON2bits.ADCS = 0b101;//Fosc/16
    ADCON2bits.ACQT = 0b111;// Tad = 20
    ADCON0bits.ADON = 1; //��������� ���
    
}

int read_adc(void){
    ADCON0bits.GODONE = 1;//������ ��������������
    while((ADCON0bits.GODONE)&&(!PIR1bits.ADIF));//���� ���������� ��������������
    PIR1bits.ADIF = 0;
    return ADRES;
}


