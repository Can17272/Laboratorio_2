/* 
 * File:   ADC.h
 * Author: TOSHIBA
 *
 * Created on February 5, 2020, 3:02 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

void int_con(void){
        INTCONbits.GIE=1;
        INTCONbits.INTE=1;
        INTCONbits.PEIE=1;
        INTCONbits.T0IE=1;
        INTCONbits.T0IF=0; //Interrupciones del INTCON
        PIE1bits.ADIE=1;  //Enable de las interrupciones

}
void (ADC){
        ADCON0bits.ADCS0=1;
        ADCON0bits.ADCS1=0;
        ADCON0bits.CHS=0;
        ADCON0bits.ADON=1; 
        
        ADCON1bits.ADFM=0;
        ADCON1bits.VCFG0=0;  
        ADCON1bits.VCFG1=0; // ADC configuration

}
#endif	/* ADC_H */

