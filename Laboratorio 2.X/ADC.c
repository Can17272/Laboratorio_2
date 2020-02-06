#include <xc.h>
#include "ADC0.h"
int ADC_VALUE;
void ADC(ADC_VALUE){
    switch (ADC_VALUE){
        case 0:
        ADCON0bits.ADCS0=1;
        ADCON0bits.ADCS1=0;
        ADCON0bits.CHS=0;
        ADCON0bits.ADON=1;
            
        break;
    
    }
    
}