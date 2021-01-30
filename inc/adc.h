#ifndef _ADC_H_
#define _ADC_H_


#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

enum ref_select_t {
    AREF = 0,
    AVCC,
    RESERVED,
    INTERNAL
};

void adc_ref_select(enum ref_select_t ref);

enum adc_status_t {
    ADC_DISABLE = 0,
    ADC_ENABLE
};

void adc_status(enum adc_status_t status);


enum adc_presc_t {
    ADC_PRESC_2 = 1,
    ADC_PRESC_4,
    ADC_PRESC_8,
    ADC_PRESC_16,
    ADC_PRESC_32,
    ADC_PRESC_64,
    ADC_PRESC_128
};

void adc_presc_set(enum adc_presc_t presc);


enum adc_ch_t {
    ADC_0 = 0,
    ADC_1,
    ADC_2,
    ADC_3,
    ADC_4,
    ADC_5,
    ADC_6,
    ADC_7,
    ADC_TEMP,
    ADC_INT = 14,
    ADC_GND
};

uint16_t adc_read(enum adc_ch_t chanel);


/*_ADC_H_*/
#endif
