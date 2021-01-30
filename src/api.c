#include "api.h"


/**************************************************************************************************
 **************************************** FLAP_FUNCTIONS ******************************************
 *************************************************************************************************/

void side_flap(enum flap_states_t state)
{
    SIDE_FLAP_OCR1 = (FLAP_OPEN == state) ? SIDE_FLAP_OPEN_VAL : SIDE_FLAP_CLOSE_VAL;
}

//-------------------------------------------------------------------------------------------------

void top_flap(enum flap_states_t state)
{
    TOP_FLAP_OCR1 = (FLAP_OPEN == state) ? TOP_FLAP_OPEN_VAL : TOP_FLAP_CLOSE_VAL;
}

//-------------------------------------------------------------------------------------------------

bool check_flaps_state()
{
    return DigitalRead(FLAPS_PORT, FLAPS_PIN);
}



/**************************************************************************************************
 ****************************************** PERIF_FUNCTIONS ***************************************
 *************************************************************************************************/

static uint8_t perif_reg = 0;
static bool perif_flag = false;
static struct shift_reg_t *sr;


void perif_init()
{
    SHIFT_REG_INIT(sr);
    sr->clk_port = CLK_PORT;
    sr->clk_pin = CLK_PIN;
    sr->data_port = DATA_PORT;
    sr->data_pin = DATA_PIN;
    sr->latch_port = LATCH_PORT;
    sr->latch_pin = LATCH_PIN;    
}

//-------------------------------------------------------------------------------------------------

void perif_update()
{
    if (true == perif_flag) {
        shift_reg_write(sr, &perif_reg, 1);
        perif_flag = false;
    }
}

//-------------------------------------------------------------------------------------------------

void leds_color_set(enum leds_color_t color)
{
    perif_reg &= ~(0b111<<COLOR_SHIFT);
    perif_reg |= (color<<COLOR_SHIFT);
    perif_flag = true;
}

//-------------------------------------------------------------------------------------------------

void fan_state(enum bin_perif_state_t state)
{
    perif_reg &= ~(1<<FAN_SHIFT);
    perif_reg |= (state<<FAN_SHIFT);
    perif_flag = true;
}

//-------------------------------------------------------------------------------------------------

void pomp_state(enum bin_perif_state_t state)
{
    perif_reg &= ~(1<<POMP_SHIFT);
    perif_reg |= (state<<POMP_SHIFT);
    perif_flag = true;
}

//-------------------------------------------------------------------------------------------------

void wind_state(enum bin_perif_state_t state)
{
    fan_state(state);
    top_flap(state);
    side_flap(state);
    perif_update();   
}




void get_temp_and_hum(int8_t *temp, uint8_t *hum)
{
    htu21_read_temp_hum(temp, hum);
}

