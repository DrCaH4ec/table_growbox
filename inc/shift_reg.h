#ifndef _SHIFT_REG_H_
#define _SHIFT_REG_H_

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

#include "digitalio_avr.h"

#define SHIFT_REG_INIT(def_sr) def_sr = malloc(sizeof(def_sr));

struct shift_reg_t {
    volatile uint8_t *clk_port;
    uint8_t clk_pin;
    volatile uint8_t *data_port;
    uint8_t data_pin;
    volatile uint8_t *latch_port;
    uint8_t latch_pin;
};

struct shift_reg_t *shift_reg_init();

void shift_reg_write(struct shift_reg_t *sr, uint8_t *data, uint8_t num_of_bytes);


/*_SHIFT_REG_H_*/
#endif
