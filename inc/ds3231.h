#ifndef _DS3231_H_
#define _DS3231_H_


#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

#include "twi.h"

#define RTC_ADDR    0x68

#define RTC_SECONDS             0x00
#define RTC_MINUTES             0x01
#define RTC_HOURS               0x02
#define RTC_DAY                 0x03
#define RTC_DATE                0x04
#define RTC_MONTH_CENTURY       0x05
#define RTC_YEAR                0x06
#define RTC_ALARM_1_SEC         0x07
#define RTC_ALARM_1_MIN         0x08
#define RTC_ALARM_1_HOURS       0x09
#define RTC_ALARM_1_DAY_DATE    0x0A
#define RTC_ALARM_2_MIN         0x0B
#define RTC_ALARM_2_HOURS       0x0C
#define RTC_ALARM_2_DAY_DATE    0x0D
#define RTC_CONTROL             0x0E
#define RTC_CONTROL_STATUS      0x0F
#define RTC_AGIGN_OFFSET        0x10
#define RTC_MSB_TEMP            0x11
#define RTC_LSB_TEMP            0x12

uint8_t rtc_get_sec();

uint8_t rtc_get_min();

uint8_t rtc_get_hour();

void rtc_set_hour(uint8_t data);

void rtc_set_min(uint8_t data);

uint8_t rtc_read_temp();

/*_DS3231_H_*/
#endif
