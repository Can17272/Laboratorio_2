

#include <xc.h>
#include "7_DISPLAY.h"

    //Config 7 segmentos

void Timer0 (void){    
OPTION_REGbits.T0CS=0;//El timer0 actuara como temporizador
OPTION_REGbits.PSA=0;//El prescaler se le asigna al timer0
OPTION_REGbits.PS2 = 1;//con estos 3 bits a 1
INTCONbits.GIE=1;//habilita las interrupciones
INTCONbits.TMR0IE=1;//habilita el uso de la interrupción tmr0 PIC 
INTCONbits.TMR0IF=0;//a 0 para que detecte la interrupción tmr0 PIC
INTCONbits.INTE=0;   
INTCONbits.PEIE=1;
INTCONbits.RBIF=0;
INTCONbits.PEIE=1;
IOCB=0b00000011;//por desborde
//    INTCONbits.RBIF=1;
TMR0 = 255;//se inicializa a este valor para obtener Xms de temporización
}