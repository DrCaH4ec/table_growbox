#include "twi_lcd.h"

static uint8_t lcd_reg = 0x00;

//#############################################################################
//#####################---INTERNAL FUNCTIONS---################################
//#############################################################################

static void PulseEnable()
{

	lcd_reg &= ~LCD_E;

    TWI_write_data(ADDR, lcd_reg, 0x00, 0);

	_delay_us(10);

	lcd_reg |= LCD_E;

  	TWI_write_data(ADDR, lcd_reg, 0x00, 0);

	_delay_us(10);		

	lcd_reg &= ~LCD_E;

    TWI_write_data(ADDR, lcd_reg, 0x00, 0);

	_delay_us(100);

}

//-----------------------------------------------------------------------------

// part=1 -> high
// part=0 -> low
static void SendHalfByte(uint8_t data, bool part)
{

	lcd_reg &= ~(LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7);

	if(part){

		lcd_reg = data&(1<<4) ? lcd_reg|LCD_D4 : lcd_reg;
		lcd_reg = data&(1<<5) ? lcd_reg|LCD_D5 : lcd_reg;
		lcd_reg = data&(1<<6) ? lcd_reg|LCD_D6 : lcd_reg;
		lcd_reg = data&(1<<7) ? lcd_reg|LCD_D7 : lcd_reg;


	}
	else{

		lcd_reg = data&(1<<0) ? lcd_reg|LCD_D4 : lcd_reg;
		lcd_reg = data&(1<<1) ? lcd_reg|LCD_D5 : lcd_reg;
		lcd_reg = data&(1<<2) ? lcd_reg|LCD_D6 : lcd_reg;
		lcd_reg = data&(1<<3) ? lcd_reg|LCD_D7 : lcd_reg;

	}

	PulseEnable();
}

//-----------------------------------------------------------------------------

static void SendInstruction(uint8_t data)
{
	lcd_reg &= ~LCD_RS;

	SendHalfByte(data, HIGH);
	SendHalfByte(data, LOW);	
}

//-----------------------------------------------------------------------------

static void SendData(uint8_t data)
{
	lcd_reg |= LCD_RS;

	_delay_us(1);

	SendHalfByte(data, HIGH);
	SendHalfByte(data, LOW);

	_delay_us(50);
}

//#############################################################################
//#####################---EXTERNAL FUNCTIONS---################################
//#############################################################################

void lcd_backlight(bool mode)
{
	lcd_reg = mode ? lcd_reg|LCD_LED : lcd_reg&(~LCD_LED);

	TWI_write_data(ADDR, lcd_reg, 0x00, 0);
}

//-----------------------------------------------------------------------------

void lcd_clear()
{
	SendInstruction(CLEAR_DISPLAY);
	_delay_ms(2);
}

//-----------------------------------------------------------------------------

void lcd_home()
{
	SendInstruction(RETURN_HOME);
	_delay_ms(2);
}

//-----------------------------------------------------------------------------

void lcd_init(uint8_t NumOfLines)
{
	uint8_t tmp = 0x00;

	_delay_ms(50);

	tmp = FUNCTION_SET | DL;

	SendHalfByte(tmp, HIGH);
	_delay_ms(5);

	SendHalfByte(tmp, HIGH);
	_delay_us(150);

	SendHalfByte(tmp, HIGH);

	_delay_us(50);

	tmp = 0x00;
	tmp |= FUNCTION_SET;
	SendHalfByte(tmp, HIGH);

	//2 lines mode set
	//5x8 dots
	tmp = NumOfLines > 1 ? (tmp | N) : tmp;
	SendInstruction(tmp);

	SendInstruction(tmp);

	tmp = 0x00;
	tmp = DISPLAY_ON_OFF_CONTROL | D;
	SendInstruction(tmp);

	tmp = 0x00;
	tmp = ENTRY_MODE_SET | I_D;
	SendInstruction(tmp);

	lcd_clear();	
}

//-----------------------------------------------------------------------------

void lcd_gotoxy(uint8_t x, uint8_t y)
{
	uint8_t tmp = (0x40 * y + x) | SET_DDRAM_ADDRES;

	SendInstruction(tmp);
	_delay_us(100);
}

//-----------------------------------------------------------------------------

void lcd_puts(char data[])
{
	uint8_t i = 0;

	while(data[i] != '\0' && i < 16){
		SendData(data[i]);
		i++;
	}
}

//-----------------------------------------------------------------------------

void lcd_put_Char(char data)
{
	SendData(data);
}

//-----------------------------------------------------------------------------

void lcd_cursor(bool mode)
{
	uint8_t tmp = DISPLAY_ON_OFF_CONTROL | D;

	tmp = mode ? (tmp | C) : tmp;

	SendInstruction(tmp);
}

//-----------------------------------------------------------------------------

void lcd_cursor_blink(bool mode)
{
	uint8_t tmp = DISPLAY_ON_OFF_CONTROL | D;

	tmp = mode ? (tmp | B) : tmp;

	SendInstruction(tmp);
}

//-----------------------------------------------------------------------------

void lcd_display(bool mode)
{
	uint8_t tmp = DISPLAY_ON_OFF_CONTROL;

	tmp = mode ? (tmp | D) : tmp;

	SendInstruction(tmp);
}

//-----------------------------------------------------------------------------

void lcd_shift_display_left()
{
	uint8_t tmp = CURSOR_OR_DISPLAY_SHIFT | S_C;

	SendInstruction(tmp);
}

//-----------------------------------------------------------------------------

void lcd_shift_display_right()
{
	uint8_t tmp = CURSOR_OR_DISPLAY_SHIFT | S_C | R_L;

	SendInstruction(tmp);
}

//-----------------------------------------------------------------------------

void lcd_create_char(uint8_t data[], uint8_t location)
{
	uint8_t tmp = SET_CGRAM_ADDRES | (location<<3);
	SendInstruction(tmp);

	uint8_t i;
	for(i = 0; i < 8; i++)
		SendData(data[i]);
}
