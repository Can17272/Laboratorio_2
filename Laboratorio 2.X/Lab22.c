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
int cont1;
int cont2;
int ADC_VAL1;
int ADC_VAL2;
int segmentos[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
void setup(void);
//void ADC(void);
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
        PIR1bits.ADIF=0; //Interrupción del ADC
    }
    if (INTCONbits.RBIF==1 && PORTBbits.RB0 ==1){
        AR1=1;
        INTCONbits.RBIF=0;
    
    }
    if (INTCONbits.RBIF==1 && PORTBbits.RB1 ==1){
        AR2=1;
        INTCONbits.RBIF=0; //Interrupciones del puerto B para antirrebote
    }
    if (INTCONbits.T0IF==1){
        TMR0=255;
        cont1++;
        cont2++;
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
            PORTAbits.RA0 =1; //Activación de la alarma
        }
        if (CONT_BIN <= ADRESH){
            PORTAbits.RA0 =0; //Comparación entre el valor del ADC y el puerto D
        }
        if (ADCON0bits.GO ==1){
            ADC_VAL1=ADRESH && 0b11110000;
            ADC_VAL2=ADRESH && 0b00001111; //Se asignan las variables para mandarlas al puerto C
            
         }
        if (cont1 >=1){
        PORTBbits.RB2=1;
        PORTBbits.RB3=0; //Multiplexación
        PORTC = segmentos[ADC_VAL1]; //Se envía el código correspondiente de la librería del 7 segmentos
        PORTC=0; //Se limpia el puerto para evitar ghosting
        cont1=0;
        }
        if (cont2 >=1){
        PORTBbits.RB2=0;
        PORTBbits.RB3=1;
        PORTC=segmentos[ADC_VAL2];
        PORTC=0;
        cont2=0;
        }    
    
    }
           
}

