#include "ds3231.h"


static uint8_t bcd_to_dec(uint8_t bcd)
{
    return (bcd & 0x0f) + ((bcd >> 4) * 10);
}


static uint8_t dec_to_bcd(uint8_t dec)
{
    return ((dec / 10) << 4) | (dec % 10);
}

static uint8_t read_byte(uint8_t reg_addr)
{
    char tmp;

    TWI_read_data(RTC_ADDR, reg_addr, &tmp, 1);
    return (uint8_t)tmp;
}

static void write_byte(uint8_t reg_addr, char data)
{
    TWI_write_data(RTC_ADDR, reg_addr, &data, 1);    
}

void rtc_set_hour(uint8_t data)
{
    write_byte(RTC_HOURS, dec_to_bcd(data));
}

void rtc_set_min(uint8_t data)
{
    write_byte(RTC_MINUTES, dec_to_bcd(data));
}

uint8_t rtc_get_sec()
{    
    return bcd_to_dec(read_byte(RTC_SECONDS));
}

uint8_t rtc_get_min()
{
    return bcd_to_dec(read_byte(RTC_MINUTES));
}

uint8_t rtc_get_hour()
{
    return bcd_to_dec(read_byte(RTC_HOURS) & 0xbf);
}

uint8_t rtc_read_temp()
{
    char tmp;

    TWI_read_data(RTC_ADDR, RTC_CONTROL_STATUS, &tmp, 1);

    if (tmp & (1<<2)) {

        while (tmp & (1<<2))
            TWI_read_data(RTC_ADDR, RTC_CONTROL_STATUS, &tmp, 1);

        TWI_read_data(RTC_ADDR, RTC_MSB_TEMP, &tmp, 1);

        return tmp;
    }

    TWI_read_data(RTC_ADDR, 0x0e, &tmp, 1);
    tmp |= (1<<5);
    TWI_write_data(RTC_ADDR, 0x0e, &tmp, 1);

    while(tmp&(1<<5))
        TWI_read_data(RTC_ADDR, 0x0e, &tmp, 1);


    TWI_read_data(RTC_ADDR, 0x11, &tmp, 1);

    return tmp;
}
