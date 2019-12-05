/*
 * ---------------------------------------------------------------------
 * Author:      Josef HOLUB
                Tomas LORENC
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2017-10-27
 * Last update: 2019-11-08
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    
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
#define sample_rate 16e-6

/* Variables ---------------------------------------------------------*/
volatile uint16_t i = 0;
uint16_t angle = 0;
uint16_t duty = 0;
volatile unsigned char sine[256];

/* Function prototypes -----------------------------------------------*/

void generate_sin(int freq){  
    //char uart_string[3];
      
    for(unsigned char x=0; x<255;x++){  
    sine[x] = 128*(sin(2.0*M_PI*x*sample_rate*freq) + 1); 

    /* itoa(sine[x], uart_string, 10);
    uart_puts(uart_string);
    uart_puts("\r\n");  */
    }  
}

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Test all TWI slave addresses and scan 
 *          connected devices.
 *  Input:  None
 *  Return: None
 */

int main(void)
{
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    GPIO_config_output(&DDRD, PD6);

    TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << WGM00) | (1 << WGM01);  //FAST PWM
    TCCR0B |= (1 << CS00);                                                  //Presclaler 0

    TIMSK0 |= (1<<TOIE0);                                                   //enable interrupt

    sei();

    generate_sin(2000);

    while(1){
        if(i > 249){
            i = 0;
        }
    }
}

ISR(TIMER0_OVF_vect){
    OCR0A = sine[i];
    i++;
}