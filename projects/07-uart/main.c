/*
 * ---------------------------------------------------------------------
 * Authors:     Tomas Fryza
                Tomas Lorenc
                Josef Holub
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-23
 * Last update: 2019-11-01
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Analog-to-digital conversion with displaying result on LCD and 
 *    transmitting via UART.
 * 
 * Note:
 *    Peter Fleury's UART library.
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Read ADC result and transmit via UART.
 *  Input:  None
 *  Return: None
 */
    uint16_t value = 0;
    char uart_string[8];

void BUTTONS(){
    if(value < 10){
        strcpy(uart_string, "RIGHT");
    }
    else if(value > 90 || value < 110){
        strcpy(uart_string, "UP");
    }
    else if(value > 240 || value < 260){
        strcpy(uart_string, "DOWN");
    }
    else if(value > 400 || value < 420){
        strcpy(uart_string, "LEFT");
    }
    else strcpy(uart_string, "SELECT");
}

int main(void)
{
    // LCD display
    lcd_init(LCD_DISP_ON);

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop (8N1)
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Display string without auto linefeed
    lcd_puts("Je Bedna bedna?");
    lcd_clrscr();
    // Put string to ringbuffer for transmitting via UART.
    uart_puts("Je Bedna bedna?\r\n");

    /* ADC
     * TODO: Configure ADC reference, clock source, enable ADC module, 
     *       and enable conversion complete interrupt */
    ADMUX |= _BV(REFS0);    //reference
    ADMUX &= ~_BV(REFS1);   //reference
    ADMUX &= ~_BV(MUX3) & ~_BV(MUX2) & ~_BV(MUX1) & ~_BV(MUX0);   //input conection
    ADCSRA |= _BV(ADEN);    //enable
    ADCSRA |= _BV(ADIE);    //interrupt enable
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);

    //Timer1
    TIM_config_prescaler(TIM1, TIM_PRESC_8);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER1_OVF_vect)
{
    ADCSRA |= _BV(ADSC);     //Start ADC conversion
}

/**
 *  Brief: ADC complete interrupt routine. Update LCD and UART 
 *         transmiter.
 */
ISR(ADC_vect)
{
    value = ADC;    //Read 10-bit ACD value
    BUTTONS();

    // Update LCD and UART transmiter
    lcd_puts(uart_string);
    lcd_putc(' ');

    uart_puts(uart_string);
    uart_putc(' ');
}