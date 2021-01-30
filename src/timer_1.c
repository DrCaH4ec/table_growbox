#include "timer_1.h"

void tim1_set_prescaler(enum tim1_presc_t presc_type)
{
    TCCR1B &= 0xf8;
    TCCR1B |= presc_type;
}

//-------------------------------------------------------------------------------------------------

void tim1_waveform_gen_mode(enum tim1_mode_t mode)
{

    TCCR1A &= 0xfc;
    TCCR1A |= mode&0x03;

    TCCR1B &= 0xe7;
    TCCR1B |= ((mode&(0x0c))<<1);
}

//-------------------------------------------------------------------------------------------------

void tim1_comp_out_mode_set_a(enum tim1_comp_out_mode_t mode)
{
    TCCR1A &= 0x3f;
    TCCR1A |= (mode<<6);
}

//-------------------------------------------------------------------------------------------------

void tim1_comp_out_mode_set_b(enum tim1_comp_out_mode_t mode)
{
    TCCR1A &= 0xcf;
    TCCR1A |= (mode<<4);
}

//-------------------------------------------------------------------------------------------------

void tim1_int_mask_set(uint8_t mask)
{
    TIMSK1 = 0x00;
    TIMSK1 |= mask;
}
