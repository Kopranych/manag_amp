/* 
 * File:   main_key.c
 * Author: Kopranov_IN
 *
 * Created on 15 Март 2018 г., 13:09
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic18f14k22.h> 
#include <stdbool.h>
#include "euart.h"
#include "pe42552.h"
 
#define MAX_STR_SIZE 6
#define ON 1
#define OFF 0
#define FIRST_COM_INX 1
/*
 * 
 */
///////////////////////////////////////////////////
char tmprecive;
char array_char[MAX_STR_SIZE];
char start_str = '*';
char end_str = '#';
char switch_amp;
char attenuator[2];
int index_recive = 0;
int read_en = OFF;
bool isReciver = false;
///////////////////////////////////////////////////
void interrupt high_isr (void){
    if(PIR1bits.RCIF){//если прерывание от eusart1
        tmprecive = RCREG1;
        if(tmprecive == start_str){
            read_en = ON;
            index_recive = 0;
        }
        if((tmprecive == end_str)&& read_en == ON ){
            read_en = OFF;
            isReciver = true;
        }
        if(read_en == ON){
            array_char[index_recive++] = tmprecive;
            if(index_recive == MAX_STR_SIZE)
                index_recive = 0;
        }     
    }
}
///////////////////////////////////////////////////
void init_controller(void);
void init_interrupt(void);
//void sleep(void);
////////////////////////////////////////////////////

int main(int argc, char** argv) {
    
    
    UART1PutStr("Device is ready!");
    UART1PutStr("Send command in format:");
    UART1PutStr("* - command start character, enable/disable amplifier"
               "(0 - disable, 1 - enable), space,"
    "attenuator in decibel (0.5 dB steps to 31.5 dB), % - command completion character.");
    UART1PutStr("EXAMPLE: '*1 30%'.");
    UART1PutStr(" Means enable amplifier, attenuator value 30 decibels.");
    
    while(1){
//        sleep();
        if(isReciver == true){//если пришли данные по eusart
            isReciver = false;
            //парсим строку
            switch_amp = array_char[FIRST_COM_INX];
            attenuator[0] =  array_char[3];
            attenuator[1] =  array_char[4];
            
            switch(switch_amp){
                case '0':
//                    switch_PE42552(switch_amp);
//                    attenuator_PE4312(attenuator);
                    UART1PutStr("Amplifier DISABLE, attenuator is: ");
                    UART1PutStr(attenuator);
                    break;
                case '1':
//                    switch_PE42552(switch_amp);
//                    attenuator_PE4312(attenuator);
                    UART1PutStr("Amplifier ENABLE, attenuator is: ");
                    UART1PutStr(attenuator);
                    break;
                default:
                    UART1PutStr("Invalid command!");
                    UART1PutStr("Send command in format:");
                    UART1PutStr("* - command start character, enable/disable amplifier"
                            "(0 - disable, 1 - enable), space,"
                        "attenuator in decibel (0.5 dB steps to 31.5 dB), % - command completion character.");
                    UART1PutStr("Example: '*1 30%'.");
                    UART1PutStr(" Means enable amplifier, attenuator value 30 decibels.");
            }
        }
    }
    return (EXIT_SUCCESS);
}

void init_controller(void){
    init_interrupt(void);
    init_switch_PE42552(void);
    UART1Init();
}

void init_interrupt(void){
    INTCONbits.GIE = 1; //разрешаем глобальные прерывания
    INTCONbits.PEIE = 1;//разрешаем прерывания переферии
    PIE1bits.RCIE = 1;//включаем прерывания по приему eusart
    RCONbits.IPEN = 1;//включаем приоритеты прерываний
}
