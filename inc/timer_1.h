#ifndef _TIMER_1_H_
#define _TIMER_1_H_

#include <avr/io.h>

enum tim1_presc_t {
    TIM1_NO_CLK_SOURCE = 0, //Timer/Counter stopped
    TIM1_PRESC_1,
    TIM1_PRESC_8,
    TIM1_PRESC_64,
    TIM1_PRESC_256,
    TIM1_PRESC_1024,
    TIM1_EXT_T1_FALL,       //External clock source T1 pin. Clock on falling edge
    TIM1_EXT_T1_RISE        //External clock source T1 pin. Clock on rising edge
};

void tim1_set_prescaler(enum tim1_presc_t presc_type);



enum tim1_mode_t {                                              /*TOP*/
    TIM1_NORMAL = 0,        //Normal                          | 0xFFFF
    TIM1_PWM_PC_8,          //PWM, Phase Correct, 8-bit       | 0x00FF
    TIM1_PWM_PC_9,          //PWM, Phase Correct, 9-bit       | 0x01FF
    TIM1_PWM_PC_10,         //PWM, Phase Correct, 10-bit      | 0x03FF
    TIM1_CTC_OCR,           //CTC                             | OCR1A
    TIM1_FAST_PWM_8,        //Fast PWM, 8-bit                 | 0x00FF
    TIM1_FAST_PWM_9,        //Fast PWM, 9-bit                 | 0x01FF
    TIM1_FAST_PWM_10,       //Fast PWM, 10-bit                | 0x03FF
    TIM1_PWM_PF_COR_ICR,    //PWM, Phase and Frequency Correct| ICR1
    TIM1_PWM_PF_COR_OCR,    //PWM, Phase and Frequency Correct| OCR1A
    TIM1_PWM_PC_ICR,        //PWM, Phase Correct              | ICR1
    TIM1_PWM_PC_OCR,        //PWM, Phase Correct              | OCR1A
    TIM1_CTC_ICR,           //CTC                             | ICR1
    TIM1_RESERVED,          //Reserved                        | -
    TIM1_FAST_PWM_ICR,      //FAST PWM                        | ICR1
    TIM1_FAST_PWM_OCR       //FAST_PWM                        | OCR1A
};  

void tim1_waveform_gen_mode(enum tim1_mode_t mode);



//Additional information see in DATASHEET
enum tim1_comp_out_mode_t {
    TIM1_NORM_PORT_OP = 0,  //Normal port operation, OC1x disconnected
    TIM1_TOGGLE_OC1x,
    TIM1_CLEAR_OC1x,
    TIM1_SET_OC1x
};

void tim1_comp_out_mode_set_a(enum tim1_comp_out_mode_t mode);

void tim1_comp_out_mode_set_b(enum tim1_comp_out_mode_t mode);



#define TIM1_IN_CAP         (1<<5)  //Input Capture Interrupt Enable
#define TIM1_OUT_COMP_B     (1<<2)  //Output Compare B Match Interrupt Enable
#define TIM1_OUT_COMP_A     (1<<1)  //Output Compare A Match Interrupt Enable
#define TIM1_OVF            (1<<0)  //Overflow Interrupt Enable

void tim1_int_mask_set(uint8_t mask);

/*_TIMER_1_H_*/
#endif
