#include "adc.h"

void adc_ref_select(enum ref_select_t ref)
{
    ADMUX &= ~(0b11<<6);
    ADMUX |= (ref<<6);
}



void adc_status(enum adc_status_t status)
{
    ADCSRA &= ~(1<<ADEN);
    ADCSRA |= (status<<ADEN);
}



void adc_presc_set(enum adc_presc_t presc)
{
    ADCSRA &= ~(0b111<<0);
    ADCSRA |= presc;
}


uint16_t adc_read(enum adc_ch_t chanel)
{
    uint8_t tmp;

    ADMUX &= 0xf0;
    ADMUX |= chanel;

    ADCSRA |= (1<<ADSC);

    while(ADCSRA&(1<<ADSC));

    tmp = ADCL;

    return (ADCH<<8) | tmp;
}
