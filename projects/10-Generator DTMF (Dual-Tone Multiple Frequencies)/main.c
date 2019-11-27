/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
                Josef HOLUB
                Tomas LORENC
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2017-10-27
 * Last update: 2019-11-08
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Scan TWI bus for all connected slave devices and transmit info
 *    to UART.
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>         // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "timer.h"
#include "uart.h"
#include "twi.h"
#include "gpio.h"

/* Typedef -----------------------------------------------------------*/


/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
uint16_t i = 0;
uint16_t freq = 1000;
uint16_t t = 0;

/* Function prototypes -----------------------------------------------*/


/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Test all TWI slave addresses and scan 
 *          connected devices.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    DDRB |= (1<<PB1);

    TCCR0A |= (1 << COM1A1) | (1 << COM1A0) | (1 << WGM10) | (1 << WGM11);
    TCCR0B |= (1 << CS11);

    TIMSK0 |= (1<<TOIE1);

    sei();

    while(1){
        OCR1A = i;
        i = 2+sin((2*3.1415*freq)*(1/t));
    }
}

ISR(TIMER0_OVF_vect){
    t = t + 1023;
}