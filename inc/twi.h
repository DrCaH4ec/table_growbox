#ifndef _TWI_H_
#define _TWI_H_


#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

#define TWI_PRESC_1     (0<<TWPS1) | (0<<TWPS0)
#define TWI_PRESC_4     (0<<TWPS1) | (1<<TWPS0)
#define TWI_PRESC_16    (1<<TWPS1) | (0<<TWPS0)
#define TWI_PRESC_64    (1<<TWPS1) | (1<<TWPS0)

#define TWI_ENABLE      true
#define TWI_DISABLE     false

#define TWI_READ        0x01
#define TWI_WRITE       0x00

void TWI_set_prescaler(uint8_t twi_prescaler);

void TWI_set_bitrate(uint8_t twi_bitrate);

void TWI_state(bool twi_status);

void TWI_start_cond();

void TWI_stop_cond();

void TWI_send_dev_addr(uint8_t twi_dev_addr, uint8_t twi_r_w);

uint8_t TWI_read_byte();

uint8_t TWI_read_last_byte();

void TWI_write_byte(uint8_t data);

void TWI_read_data(uint8_t dev_addr, uint8_t start_addr, char *data, uint8_t num_of_bytes);

void TWI_write_data(uint8_t dev_addr, uint8_t start_addr, const char *data, uint8_t num_of_bytes);

/*_TWI_H_*/
#endif
