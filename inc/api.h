#ifndef _API_H_
#define _API_H_

#include <avr/io.h>
#include <stdbool.h>
#include <stdlib.h>

#include "defines.h"
#include "digitalio_avr.h"
#include "shift_reg.h"
#include "htu21.h"


/**************************************************************************************************
 ****************************************** FLAP_API **********************************************
 *************************************************************************************************/
enum flap_states_t {
    FLAP_CLOSE = 0,
    FLAP_OPEN
};

void side_flap(enum flap_states_t state);

void top_flap(enum flap_states_t state);

bool check_flaps_state();



/**************************************************************************************************
 ****************************************** PERIF_API **********************************************
 *************************************************************************************************/

#define COLOR_SHIFT     1
#define FAN_SHIFT       4
#define POMP_SHIFT      0

void perif_init();

void perif_update();

enum leds_color_t {
    LEDS_OFF = 0,
    LEDS_BLUE,
    LEDS_RED,
    LEDS_PURPLE,
    LEDS_GREEN,
    LEDS_LIGHT_BLUE,
    LEDS_YELLOW,
    LEDS_WHITE
};

void leds_color_set(enum leds_color_t color);

enum bin_perif_state_t {
    PERIF_OFF = 0,
    PERIF_ON
};

void fan_state(enum bin_perif_state_t state);

void pomp_state(enum bin_perif_state_t state);




/**************************************************************************************************
 ******************************************* MODES ************************************************
 *************************************************************************************************/

void wind_state(enum bin_perif_state_t state);






void get_temp_and_hum(int8_t *temp, uint8_t *hum);


/*_API_H_*/
#endif
