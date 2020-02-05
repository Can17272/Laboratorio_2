/* 
 * File:   Lab2.c
 * Author: Daniel Cano; 17272
 *
 * Created on February 4, 2020, 12:06 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

int CONT_BIN;
int AR1;
int AR2;

void setup (void){
    PORTA=0;
    PORTB=0;
    PORTC=0;
    PORTD=0;
    ANSEL=0;
    ANSELH=0;
    
    TRISA = 0x01;
    TRISB = 0x03;
    TRISC=0;
    TRISD=0;
}

void __interrupt() ISR (void){
    /*if (PIR1bits.ADIF==1){
        PORTD = CONT_BIN;
        PIR1bits.ADIF=0;
    }*/
    if (INTCONbits.RBIF==1 && PORTBbits.RB0 ==1){
        AR1=1;
        INTCONbits.RBIF=0;
    
    }
    if (INTCONbits.RBIF==1 && PORTBbits.RB1 ==1){
        AR2=1;
        INTCONbits.RBIF=0;
    }
}

void main (void){
    setup();
    CONT_BIN = 0;
    AR1=0;
    AR2=0;
    CONT_BIN = 0;
       
    while (1){
        if (PORTBbits.RB0 ==0 && AR1=1){
            CONT_BIN++;
            PORTD = CONT_BIN;
            AR1=0;
           
        }
        if (PORTBbits.RB1 ==0 && AR2=1){
            CONT_BIN--;
            PORTD = CONT_BIN;
            AR2=0;
        }
            
    
    }
           
}
