#include "ext_int.h"

void ext_int0_sense_control(enum sense_control_t sense)
{
    EICRA &= 0xfc;
    EICRA |= sense;
}

void ext_int1_sense_control(enum sense_control_t sense)
{
    EICRA &= 0xf3;
    EICRA |= (sense<<2);
}


void ext_int0_status(enum ext_int_stat_t status)
{
    EIMSK &= ~(1<<INT0);
    EIMSK |= (status<<INT0);
}

void ext_int1_status(enum ext_int_stat_t status)
{
    EIMSK &= ~(1<<INT1);
    EIMSK |= (status<<INT1);
}
