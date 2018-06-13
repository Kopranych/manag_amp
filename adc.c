#include "adc.h"


void init_adc(void){
    ADC_TRIS = 1;//вывод на вход
    PIR1bits.ADIF = 0;//сброс флага прерывани€
    ANSELbits.ANS4 = 1;//аналоговый вывод
    ADCON0bits.CHS = 0b0011;//выбор канала AN3    
    ADCON1bits.PVCFG = 0;//опорное позитивное напр€жение от внутренннего Vdd
    ADCON1bits.NVCFG = 0;//опорное негативное напр€жение от GND
    ADCON2bits.ADFM = 1;//формат прин€тых данных
    ADCON2bits.ADCS = 0b101;//Fosc/16
    ADCON2bits.ACQT = 0b111;// Tad = 20
    ADCON0bits.ADON = 1; //включение ацп
    
}

int read_adc(void){
    ADCON0bits.GODONE = 1;//начать преобразование
    while((ADCON0bits.GODONE)&&(!PIR1bits.ADIF));//ждем завершени€ преобразовани€
    PIR1bits.ADIF = 0;
    return ADRES;
}


