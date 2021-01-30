#ifndef _HTU21_H_
#define _HTU21_H_


#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

#include "twi.h"

#define HTU_ADDR                    0x40

//commands
#define TRIG_TEMP_MEASURE_HOLD      0xE3
#define TRIG_HUM_MEASURE_HOLD       0xE5
#define TRIG_TEMP_MEASURE_NO_HOLD   0xF3
#define TRIG_HUM_MEASURE_NO_HOLD    0xF5
#define WRITE_USR_REG               0xE6
#define READ_USR_REG                0xE7
#define SOFT_RST                    0xFE


void htu21_rst();

int8_t htu21_read_temp();

uint8_t htu21_read_hum();

void htu21_read_temp_hum(int8_t *temp, uint8_t *hum);

/*_HTU21_H_*/
#endif
