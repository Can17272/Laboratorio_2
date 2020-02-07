/* 
 * File:   Lab2.c
 * Author: Daniel Cano; 17272
 *
 * Created on February 4, 2020, 12:06 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "7_DISPLAY.h"
#include "ADC0.h"

int CONT_BIN;
int AR1;
int AR2;
int ADC_VAL;
void setup(void);
void ADC(void);
void int_con(void);

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
    if (PIR1bits.ADIF==1){
        PORTD = CONT_BIN;
        PIR1bits.ADIF=0; //Interrupci�n del ADC
    }
    if (INTCONbits.RBIF==1 && PORTBbits.RB0 ==1){
        AR1=1;
        INTCONbits.RBIF=0;
    
    }
    if (INTCONbits.RBIF==1 && PORTBbits.RB1 ==1){
        AR2=1;
        INTCONbits.RBIF=0; //Interrupciones del puerto B para antirrebote
    }
}

void main (void){
    setup();
    ADC();
    CONT_BIN = 0;
    AR1=0;
    AR2=0;
    CONT_BIN = 0;
       
    while (1){
        if (PORTBbits.RB0 ==0 && AR1==1){
            CONT_BIN++;
            //PORTD = CONT_BIN;
            AR1=0; //Suma binaria del puerto D
           
        }
        if (PORTBbits.RB1 ==0 && AR2==1){
            CONT_BIN--;
           // PORTD = CONT_BIN;
            AR2=0; //Resta binaria del puerto D
        }
        if (ADRESH <= CONT_BIN){
            PORTAbits.RA0 =1; //Activaci�n de la alarma
        }
        if (CONT_BIN <= ADRESH){
            PORTAbits.RA0 =0; //Comparaci�n entre el valor del ADC y el puerto D
        }
            
    
    }
           
}

