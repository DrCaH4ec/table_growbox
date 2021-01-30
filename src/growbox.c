#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "../inc/twi.h"
#include "../inc/digitalio_avr.h"
#include "../inc/twi_lcd.h"
#include "../inc/defines.h"
#include "../inc/api.h"
#include "../inc/timer_1.h"
#include "../inc/htu21.h"
#include "../inc/ds3231.h"
#include "../inc/adc.h"
#include "../inc/ext_int.h"



ISR(INT1_vect)
{
    if(DigitalRead(&PIND, 6))
        lcd_backlight(ON);
    else if(DigitalRead(&PIND, 7))
        lcd_backlight(OFF);
}


int main(void)
{

    PinMode(&DDRB, 5, OUTPUT);
    PinMode(&DDRB, 4, OUTPUT);
    PinMode(&DDRB, 3, OUTPUT);
    PinMode(&DDRB, 2, OUTPUT);
    PinMode(&DDRB, 1, OUTPUT);
    PinMode(&DDRC, 2, OUTPUT);

    DigitalWrite(&PORTB, 5, LOW);
    DigitalWrite(&PORTC, 2, LOW);


    TWI_set_prescaler(TWI_PRESC_4);
    TWI_set_bitrate(23);

    tim1_comp_out_mode_set_a(TIM1_CLEAR_OC1x);
    tim1_comp_out_mode_set_b(TIM1_CLEAR_OC1x);
    tim1_waveform_gen_mode(TIM1_FAST_PWM_ICR);
    tim1_set_prescaler(TIM1_PRESC_256);
    ICR1 = 1249;

    ext_int1_sense_control(EXT_FALL);
    ext_int1_status(EXT_INT_ENABLE);

    adc_ref_select(AVCC);
    adc_presc_set(ADC_PRESC_16);
    adc_status(ADC_ENABLE);

    sei();

    lcd_init(2);
    lcd_backlight(ON);

    htu21_rst();

    top_flap(FLAP_CLOSE);
    side_flap(FLAP_CLOSE);

    perif_init();
    pomp_state(PERIF_OFF);
    fan_state(PERIF_OFF);
    leds_color_set(LEDS_OFF);
    perif_update();


    char lcd_buff_1[16];
    char lcd_buff_2[16];
    uint8_t sec, min, hour;

    // // char reg;



    wind_state(PERIF_ON);
    _delay_ms(100);
    DigitalWrite(&PORTC, 2, HIGH);
    _delay_ms(5000);

    DigitalWrite(&PORTC, 2, LOW);
    _delay_ms(1000);
    wind_state(PERIF_OFF);

    leds_color_set(LEDS_PURPLE);
    top_flap(FLAP_CLOSE);
    side_flap(FLAP_OPEN);
    perif_update();


    pomp_state(PERIF_ON);
    perif_update();
    _delay_ms(2000);
    pomp_state(PERIF_OFF);
    perif_update();


    while (1) {

    // htu21_read_temp_hum(&temp, &hum);
    // sprintf(lcd_buff_1, "t%dC", temp);
    // sprintf(lcd_buff_2, "h%d%%", hum);
    // lcd_clear();
    // lcd_gotoxy(0, 0);
    // lcd_puts(lcd_buff_1);
    // lcd_gotoxy(0, 1);
    // lcd_puts(lcd_buff_2);


    // if(temp < 30 && !(DigitalRead(&PINC, 2))) {
    //     fan_state(PERIF_ON);
    //     perif_update();
    //     _delay_ms(500);
    //     DigitalWrite(&PORTC, 2, HIGH);

    // } else if(temp >= 30 && (DigitalRead(&PINC, 2))) {
    //     DigitalWrite(&PORTC, 2, LOW);
    //     _delay_ms(2000);
    //     fan_state(PERIF_OFF);
    //     perif_update();
    // }

    // if((temp - 30) >= 10)
    //     wind_state(PERIF_ON);

    // if((temp - 30) <= 10 && (temp - 30) >= 3)
    //     wind_state(PERIF_ON);
    // else
    //     top_flap(FLAP_CLOSE);


    sec = rtc_get_sec();
    min = rtc_get_min();
    hour = rtc_get_hour();
    sprintf(lcd_buff_2, "%d%d:%d%d:%d%d", hour/10, hour%10, min/10, min%10, sec/10, sec%10);  
    sprintf(lcd_buff_1, "%d", adc_read(MOISURE_CHANEL));

    lcd_clear();
    lcd_gotoxy(0, 0);
    lcd_puts(lcd_buff_1);
    lcd_gotoxy(0, 1);
    lcd_puts(lcd_buff_2);

    _delay_ms(500);


    // sec = rtc_get_sec();
    // min = rtc_get_min();
    // hour = rtc_get_hour();
    // sprintf(lcd_buff_1, "%d%d:%d%d:%d%d", hour/10, hour%10, min/10, min%10, sec/10, sec%10);
    // reg = rtc_read_temp();
    // sprintf(lcd_buff_2, "t%dC", reg);
    // lcd_clear();
    // lcd_gotoxy(0, 0);
    // lcd_puts(lcd_buff_1);
    // lcd_gotoxy(0, 1);
    // lcd_puts(lcd_buff_2);

        

        // fan_state(PERIF_OFF);

        // DigitalWrite(&PORTB, 5, LOW);
        // _delay_ms(1000);
        // DigitalWrite(&PORTB, 5, HIGH);
        // _delay_ms(1000);
    }
    return 0;
}
