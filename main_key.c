/* 
 * File:   main_key.c
 * Author: Kopranov_IN
 *
 * Created on 15 Март 2018 г., 13:09
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic18f14k22.h> 
#include <stdbool.h>
#include "euart.h"
#include "pe42552.h"
#include "spi.h"
 
#define MAX_STR_SIZE 5
#define ON 1
#define OFF 0
#define FIRST_COM_INX 1
#define INVALID_COM 2
#define SERIAL_BIT_TRIS TRISAbits.RA5
#define SERIAL_BIT_READ PORTAbits.RA5

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1H
#pragma config FOSC = IRC       // Oscillator Selection bits (External RC oscillator)
#pragma config PLLEN = OFF      // 4 X PLL Enable bit (PLL is under software control)
#pragma config PCLKEN = ON      // Primary Clock Enable bit (Primary clock enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 27        // Brown Out Reset Voltage bits (VBOR set to 2.7 V nominal)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bit (WDT is controlled by SWDTEN bit of the WDTCON register)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up bit (HFINTOSC starts clocking the CPU without waiting for the oscillator to stablize.)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled, RA3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config BBSIZ = OFF      // Boot Block Size Select bit (1kW boot block size)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = ON         // Code Protection bit (Block 0 code-protected)
#pragma config CP1 = ON         // Code Protection bit (Block 1 code-protected)

// CONFIG5H
#pragma config CPB = ON         // Boot Block Code Protection bit (Boot block code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = ON        // Write Protection bit (Block 0 write-protected)
#pragma config WRT1 = ON        // Write Protection bit (Block 1 write-protected)

// CONFIG6H
#pragma config WRTC = ON        // Configuration Register Write Protection bit (Configuration registers write-protected)
#pragma config WRTB = ON        // Boot Block Write Protection bit (Boot block write-protected)
#pragma config WRTD = ON        // Data EEPROM Write Protection bit (Data EEPROM write-protected)

// CONFIG7L
#pragma config EBTR0 = ON       // Table Read Protection bit (Block 0 protected from table reads executed in other blocks)
#pragma config EBTR1 = ON       // Table Read Protection bit (Block 1 protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = ON       // Boot Block Table Read Protection bit (Boot block protected from table reads executed in other blocks)

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
char temp;
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
            if(index_recive == MAX_STR_SIZE){
                index_recive = 0;
                array_char[0] = INVALID_COM;//превышен размер массива значит команда не соответствует
            }
        }     
    }
}
///////////////////////////////////////////////////
void init_controller(void);
void init_interrupt(void);
void init_IO_port(void);
//void sleep(void);
////////////////////////////////////////////////////

int main(int argc, char** argv) {
    
    
//    UART1PutStr("Device is ready!");
//    UART1PutStr("Send command in format:");
//    UART1PutStr("* - command start character, enable/disable amplifier"
//               "(0 - disable, 1 - enable), space,"
//    "attenuator in decibel (0.5 dB steps to 31.5 dB), % - command completion character.");
//    UART1PutStr("EXAMPLE: '*1 30%'.");
//    UART1PutStr(" Means enable amplifier, attenuator value 30 decibels.");
    
    while(1){

while(1){
//        sleep();
        if(isReciver == true){//если пришли данные по eusart
            isReciver = false;
            //парсим строку
            switch_amp = array_char[FIRST_COM_INX];
            attenuator[0] =  array_char[3];
            attenuator[1] =  array_char[4];
            
            switch(switch_amp){
                 case '0'://выполнить установку всей доступной переферии
                    UART1PutStr("1|0");
                    UART1PutStr("2|0");
                    UART1PutStr("3|6");
                    UART1PutStr("4|13");
                    UART1PutStr("5|1.2");
                    UART1PutStr("6|33");
                    break;
                case '1'://вкл/выкл усилитель
                    temp = array_char[2];
                    if(read_led(VD1)){
                        led_off(VD1);
                        UART1PutStr("1|0"); 
//                    switch_PE42552(switch_amp);
//                    attenuator_PE4312(attenuator);
                    }else{
                        led_on(VD1);
                        UART1PutStr("1|1");
//                    UART1PutStr(attenuator);
                    }                   
                    break;
                case '2'://вкл/выкл предусилитель
//                   temp = array_char[2];
                    if(read_led(VD2)){
                        led_off(VD2);
                        UART1PutStr("2|0"); 
//                    switch_PE42552(switch_amp);
//                    attenuator_PE4312(attenuator);
                    }else{
                        led_on(VD2);
                        UART1PutStr("2|1");
//                    UART1PutStr(attenuator);
                    }                   
                    break;
                case '3'://первый аттенюатор
                    UART1PutStr("3|31.5");
 //                    attenuator_PE4312(array_char);                           
                    break;
                
                case '4'://второй аттенюатор
                    UART1PutStr("4|0.5");
 //                    attenuator_PE4312(array_char);                         
                    break;
                case '5'://чтение данных с переферии
                    UART1PutStr("5|1.7");
                    
                             
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
    init_IO_port();
    init_interrupt();
    init_switch();
    UART1Init();
    init_spi();
}

void init_interrupt(void){
    INTCONbits.GIE = 1; //разрешаем глобальные прерывания
    INTCONbits.PEIE = 1;//разрешаем прерывания переферии
    PIE1bits.RCIE = 1;//включаем прерывания по приему eusart
//    RCONbits.IPEN = 1;//включаем приоритеты прерываний
}

void init_IO_port(void){
    ANSELbits.ANSEL = 0;//все порты 
    ANSELHbits.ANSELH = 0;//цифровые
    
    SERIAL_BIT_TRIS = 1;//pin as input
    SERIAL_BIT_READ = 0;

}

void test(){
    PORTAbits.RA2 = 1;
    PORTAbits.RA2 = 0;
}
