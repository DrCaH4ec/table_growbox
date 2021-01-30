#ifndef _DEFINES_H_
#define _DEFINES_H_


/******************************************************************************
 **************************** FLAPS_DEFINES ***********************************
 *****************************************************************************/

/**
 * OCR1x value for close and open states of SIDE flap
 */
#define SIDE_FLAP_CLOSE_VAL     31
#define SIDE_FLAP_OPEN_VAL      95

/**
 * OCR1x value for close and open states of TOP flap
 */
#define TOP_FLAP_OPEN_VAL       65
#define TOP_FLAP_CLOSE_VAL      113

#define SIDE_FLAP_OCR1          OCR1B
#define TOP_FLAP_OCR1           OCR1A

#define FLAPS_PORT              &PINC
#define FLAPS_PIN               0

#define FLAPS_CLOSE_STATE       LOW
#define FLAPS_OPEN_STATE        HIGH




#define CLK_PORT    &PORTB
#define CLK_PIN     5
#define DATA_PORT   &PORTB
#define DATA_PIN    4
#define LATCH_PORT  &PORTB
#define LATCH_PIN   3

#define MOISURE_CHANEL  ADC_6


/*_DEFINES_H_*/
#endif
