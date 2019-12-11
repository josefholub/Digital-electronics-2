/*
 * ---------------------------------------------------------------------
 * Author:      Josef HOLUB
                Tomas LORENC
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2019-11-27
 * Last update: 2019-12-11
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
volatile uint8_t i = 0;
volatile uint8_t sine5[125];
volatile uint8_t sine10[125];
volatile uint8_t sine15[125];
volatile uint8_t sine20[125];
volatile uint8_t sine25[125];
volatile uint8_t sine30[125];
volatile uint8_t sine35[125];
volatile uint8_t sine40[125];
volatile uint8_t sine50[125];

volatile uint8_t *p_pole;


/* Function prototypes -----------------------------------------------*/

void generate_sin(void){  
    //char uart_string[3];
      
    for(unsigned char x=0; x<125;x++){  
    sine5[x] = 128*(sin(2.0*M_PI*x*sample_rate*500) + 1); 
    sine10[x] = 128*(sin(2.0*M_PI*x*sample_rate*1000) + 1); 
    sine15[x] = 128*(sin(2.0*M_PI*x*sample_rate*1500) + 1); 
    sine20[x] = 128*(sin(2.0*M_PI*x*sample_rate*2000) + 1); 
    sine25[x] = 128*(sin(2.0*M_PI*x*sample_rate*2500) + 1); 
    sine30[x] = 128*(sin(2.0*M_PI*x*sample_rate*3000) + 1); 
    sine35[x] = 128*(sin(2.0*M_PI*x*sample_rate*3500) + 1); 
    sine40[x] = 128*(sin(2.0*M_PI*x*sample_rate*4000) + 1); 
    sine50[x] = 128*(sin(2.0*M_PI*x*sample_rate*5000) + 1); 

/*     itoa(sine5[x], uart_string, 10);
    uart_puts(uart_string);
    uart_puts("\r\n"); */
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
    uint8_t x = 0;  //radky
    uint8_t y = 0;  //sloupce
//char uart_string[3];
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    GPIO_config_output(&DDRD, PD6);                                         //PWM output

    for(uint8_t d = 0;d < 4; d++){
        DDRC |= (1<<d);
        DDRB &= ~(1<<d);
        PORTB |= (1<<d);
        GPIO_write(&PORTC, d, 1);
    }


    TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << WGM00) | (1 << WGM01);  //FAST PWM
    TCCR0B |= (1 << CS00);                                                  //Presclaler 0

    TIMSK0 |= (1<<TOIE0);                                                   //enable interrupt

    generate_sin();

    p_pole = sine5;

    sei();

    /* for(uint8_t d = 0;d < 200; d++){
       itoa(*p_pole, uart_string, 10);
        uart_puts(uart_string);
        uart_puts("\r\n");
         p_pole++;
         if(d == 125){
            p_pole = p_pole - 125;
        }
    } */
    while(1){

        if(!bit_is_set(PINB, x)){
            if(y == 0)p_pole = sine5;;
            if(y == 1)p_pole = sine10;
            if(y == 2)p_pole = sine15;
            if(y == 3)p_pole = sine20;
        }
        x++;
        if(!bit_is_set(PINB, x)){
            if(y == 0)p_pole = sine25;
            if(y == 1)p_pole = sine30;
            if(y == 2)p_pole = sine35
            if(y == 3)uart_putc('B');
        }
        x++;
        if(!bit_is_set(PINB, x)){
            if(y == 0)uart_putc('7');
            if(y == 1)uart_putc('8');
            if(y == 2)uart_putc('9');
            if(y == 3)uart_putc('C');
        }
        x++;
        if(!bit_is_set(PINB, x)){
            if(y == 0)uart_putc('*');
            if(y == 1)uart_putc('0');
            if(y == 2)uart_putc('#');
            if(y == 3)uart_putc('D');
        }
        x = 0;
        GPIO_write(&PORTC, y, 1);
        y++;
        if(y > 4){
            y = 0;
        }
        GPIO_write(&PORTC, y, 0);
        
        if(i > 124){
            p_pole = p_pole - i;
            i = 0;
        }
        
    }
}

ISR(TIMER0_OVF_vect){
    //char uart_string[3];
    OCR0A = *p_pole;
    p_pole++;
    i++;
    /* itoa(*p_pole, uart_string, 10);
    uart_puts(uart_string);
    uart_puts("\r\n");  */
    /* itoa(i, uart_string, 10);
    uart_puts(uart_string);
    uart_puts("\r\n"); */
}