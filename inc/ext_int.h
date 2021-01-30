#ifndef _EXT_INT_H_
#define _EXT_INT_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

enum sense_control_t {
    EXT_LOW = 0,
    EXT_ANY,
    EXT_FALL,
    EXT_RISE
};

void ext_int0_sense_control(enum sense_control_t sense);
void ext_int1_sense_control(enum sense_control_t sense);

#define EXT_INT0    (1<<INT0)
#define EXT_INT1    (1<<INT1)

enum ext_int_stat_t {
    EXT_INT_DISABLE = 0,
    EXT_INT_ENABLE
};

void ext_int0_status(enum ext_int_stat_t status);
void ext_int1_status(enum ext_int_stat_t status);

/*_EXT_INT_H_*/
#endif
