#include "twi.h"

void TWI_set_prescaler(uint8_t twi_prescaler)
{
    TWSR &= ~((1<<TWPS1) | (1<<TWPS0));
    TWSR |= twi_prescaler;
}

//-------------------------------------------------------------------------------------------------

void TWI_set_bitrate(uint8_t twi_bitrate)
{
    TWBR = twi_bitrate;
}

//-------------------------------------------------------------------------------------------------

void TWI_state(bool twi_status)
{
    if (TWI_ENABLE == twi_status)
        TWCR |= (1<<TWEN);
    else
        TWCR &= (1<<TWEN);
}

//-------------------------------------------------------------------------------------------------

void TWI_start_cond()
{
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

//-------------------------------------------------------------------------------------------------

void TWI_stop_cond()
{
    TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

//-------------------------------------------------------------------------------------------------

void TWI_send_dev_addr(uint8_t twi_dev_addr, uint8_t twi_r_w)
{
    TWDR = (twi_dev_addr << 1) | twi_r_w;
    TWCR = (1<<TWINT) | (1<<TWEN);

    while (!(TWCR & (1<<TWINT)));
}

//-------------------------------------------------------------------------------------------------

uint8_t TWI_read_byte()
{
    TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT))); 

    return TWDR;  
}

//-------------------------------------------------------------------------------------------------

uint8_t TWI_read_last_byte()
{
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));   

    return TWDR;
}

//-------------------------------------------------------------------------------------------------

void TWI_write_byte(uint8_t data)
{
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);

    while (!(TWCR & (1<<TWINT)));   
}

//-------------------------------------------------------------------------------------------------

void TWI_read_data(uint8_t dev_addr, uint8_t start_addr, char *data, uint8_t num_of_bytes)
{
    TWI_start_cond();
    TWI_send_dev_addr(dev_addr, TWI_WRITE);
    TWI_write_byte(start_addr);
    TWI_start_cond();
    TWI_send_dev_addr(dev_addr, TWI_READ);
    uint8_t i;
    for (i = 0; i < num_of_bytes - 1; i++)
        data[i] = TWI_read_byte();

    data[i] = TWI_read_last_byte();
    TWI_stop_cond();
}

//-------------------------------------------------------------------------------------------------

void TWI_write_data(uint8_t dev_addr, uint8_t start_addr, const char *data, uint8_t num_of_bytes)
{
    TWI_start_cond();
    TWI_send_dev_addr(dev_addr, TWI_WRITE);
    TWI_write_byte(start_addr);

    for (uint8_t i = 0; i < num_of_bytes; i++)
        TWI_write_byte(data[i]);

    TWI_stop_cond();
}
