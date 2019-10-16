/*
library DE2 Holub Lorenc
timer.h
*/

#ifndef  TIMER_H_INCLUDED
#define  TIMER_H_INCLUDED

#include <avr/io.h>

#define TIM0 0
#define TIM1 1
#define TIM2 2

#define TIM_PRESC_1     0
#define TIM_PRESC_8     1
#define TIM_PRESC_32    2
#define TIM_PRESC_64    3
#define TIM_PRESC_128   4
#define TIM_PRESC_256   5
#define TIM_PRESC_1024  6

#define TIM_OVERFLOW_DISABLE 0
#define TIM_OVERFLOW_ENABLE  1

void TIM_config_prescaler(uint8_t  timer_name ,uint8_t  presc_val);
void TIM_config_interrupt(uint8_t  timer_name ,uint8_t  interr_mode);

#endif /*  TIMER_H_INCLUDED  */