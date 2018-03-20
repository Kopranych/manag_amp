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

void init_interrupt(void);
//void sleep(void);
////////////////////////////////////////////////////

int main(int argc, char** argv) {
    init_interrupt();
    
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
                    UART1PutStr("Усилитель отключен, аттенюатор:"+attenuator[0]+attenuator[1]);
                    break;
                case '1':
//                    switch_PE42552(switch_amp);
//                    attenuator_PE4312(attenuator);
                    UART1PutStr("Усилитель подключен, аттенюатор:"+attenuator[0]+attenuator[1]);
                    break;
                default:
                    UART1PutStr("Неверная команда");
                    UART1PutStr("Отправте комаду в формате:");
                    UART1PutStr("* - символ начала команды, номер подключения усилителя"
                            "(0 - отключить, 1 - подключить), пробел,"
                        "значение аттенюатора в децибелах (от 0,5 до 31,5 с шагом 0,5), # - символ завершения команды");
                    UART1PutStr("Пример:");
                    UART1PutStr("*1 30#");
                    UART1PutStr("т.е. подключить усилитель, значение аттенюатора 30 децибел");
            }
        }
    }
    return (EXIT_SUCCESS);
}

void init_interrupt(void){
    INTCONbits.GIE = 1; //разрешаем глобальные прерывания
    INTCONbits.PEIE = 1;//разрешаем прерывания переферии
    PIE1bits.RCIE = 1;//включаем прерывания по приему eusart
    RCONbits.IPEN = 1;//включаем приоритеты прерываний
}
