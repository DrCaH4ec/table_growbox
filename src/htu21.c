#include "htu21.h"


void htu21_rst()
{
    TWI_start_cond();
    TWI_send_dev_addr(HTU_ADDR, TWI_WRITE);
    TWI_write_byte(SOFT_RST);
    TWI_stop_cond();
}

//-------------------------------------------------------------------------------------------------

static int16_t parce_temp(uint16_t raw_temp)
{
    raw_temp &= ~(0x0003);

    return 0.002681 * (float)raw_temp - 46.85;
}

//-------------------------------------------------------------------------------------------------

static uint8_t parce_hum(uint16_t raw_hum)
{
    raw_hum &= ~(0x0003);

    return 0.001907 * (float)raw_hum - 6;
}

//-------------------------------------------------------------------------------------------------

int8_t htu21_read_temp()
{
    uint8_t buff[2];

    TWI_start_cond();
    TWI_send_dev_addr(HTU_ADDR, TWI_WRITE);
    TWI_write_byte(TRIG_TEMP_MEASURE_HOLD);
    TWI_start_cond();
    TWI_send_dev_addr(HTU_ADDR, TWI_READ);

    buff[1] = TWI_read_byte();
    buff[0] = TWI_read_last_byte();
    
    TWI_stop_cond();

    return parce_temp((buff[1]<<8)|buff[0]);
}

//-------------------------------------------------------------------------------------------------

uint8_t htu21_read_hum()
{
    uint8_t buff[2];

    TWI_start_cond();
    TWI_send_dev_addr(HTU_ADDR, TWI_WRITE);
    TWI_write_byte(TRIG_HUM_MEASURE_HOLD);
    TWI_start_cond();
    TWI_send_dev_addr(HTU_ADDR, TWI_READ);

    buff[1] = TWI_read_byte();
    buff[0] = TWI_read_last_byte();

    TWI_stop_cond();

    return parce_hum((buff[1]<<8)|buff[0]);
}

//-------------------------------------------------------------------------------------------------

void htu21_read_temp_hum(int8_t *temp, uint8_t *hum)
{
    *temp = htu21_read_temp();

    uint8_t raw_hum = htu21_read_hum();

    int8_t f_t = -0.15 * (float)(25 - *temp);

    *hum = raw_hum + f_t;
}
