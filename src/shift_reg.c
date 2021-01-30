#include "shift_reg.h"

static void clk(struct shift_reg_t *sr)
{
    DigitalWrite(sr->clk_port, sr->clk_pin, LOW);
    _delay_us(100);
    DigitalWrite(sr->clk_port, sr->clk_pin, HIGH);
    _delay_us(100);
    DigitalWrite(sr->clk_port, sr->clk_pin, LOW);
    _delay_us(100);   
}

//-------------------------------------------------------------------------------------------------

static void latch(struct shift_reg_t *sr)
{
    DigitalWrite(sr->latch_port, sr->latch_pin, LOW);
    _delay_us(100);
    DigitalWrite(sr->latch_port, sr->latch_pin, HIGH);
    _delay_us(100);
    DigitalWrite(sr->latch_port, sr->latch_pin, LOW);
    _delay_us(100);     
}

//-------------------------------------------------------------------------------------------------

static void send_byte(struct shift_reg_t *sr, uint8_t data)
{
    uint8_t i = 8;

    while (i != 0) {
        i--;
        DigitalWrite(sr->data_port, sr->data_pin, data&(1<<i));
        clk(sr);
    }
}

//-------------------------------------------------------------------------------------------------

void shift_reg_write(struct shift_reg_t *sr, uint8_t *data, uint8_t num_of_bytes)
{
    while (num_of_bytes != 0) {
        num_of_bytes--;
        send_byte(sr, data[num_of_bytes]);
    }

    latch(sr);
}

//-------------------------------------------------------------------------------------------------

struct shift_reg_t *shift_reg_init()
{
    struct shift_reg_t *tmp_sr = malloc(sizeof(tmp_sr));

    return tmp_sr;
}
