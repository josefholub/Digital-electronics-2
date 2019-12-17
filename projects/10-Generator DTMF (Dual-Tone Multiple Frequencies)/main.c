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
 *      Generator DTMF
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>         // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>           //sin() function
#include "timer.h"
//#include "uart.h"
#include "gpio.h"


/* Define ------------------------------------------------------------*/
//#define UART_BAUD_RATE 9600
#define SAMPLE_RATE 16e-6       //Timer0 overflow

/* Global Variables ---------------------------------------------------------*/
volatile uint8_t i = 0;         //Cycle time

volatile uint8_t sine5[125];    //Array sin
volatile uint8_t sine10[125];
volatile uint8_t sine15[125];
volatile uint8_t sine20[125];
volatile uint8_t sine25[125];
volatile uint8_t sine30[125];
volatile uint8_t sine35[125];
volatile uint8_t sine40[125];
volatile uint8_t sine50[125];

volatile uint8_t *p_pole;       //Pointer start sin array
volatile uint8_t *ptr;          //Pointer actual position in sin array


/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Generate sin arrays. Arrays save to global variables.
            SAMPLE_RATE = time to overflow timer0
 *  Input:  None
 *  Return: None
 */

void generate_sin(void){  
          
    for(uint8_t x=0; x<125;x++){  
        sine5[x] = 127*(sin(2.0*M_PI*x*SAMPLE_RATE*500) + 1);       //500  Hz 
        sine10[x] = 128*(sin(2.0*M_PI*x*SAMPLE_RATE*1000) + 1);     //1.0 kHz
        sine15[x] = 128*(sin(2.0*M_PI*x*SAMPLE_RATE*1500) + 1);     //1.5 kHz 
        sine20[x] = 128*(sin(2.0*M_PI*x*SAMPLE_RATE*2000) + 1);     //2.0 kHz
        sine25[x] = 128*(sin(2.0*M_PI*x*SAMPLE_RATE*2500) + 1);     //2.5 kHz
        sine30[x] = 128*(sin(2.0*M_PI*x*SAMPLE_RATE*3000) + 1);     //3.0 kHz
        sine35[x] = 128*(sin(2.0*M_PI*x*SAMPLE_RATE*3500) + 1);     //3.5 kHz
        sine40[x] = 128*(sin(2.0*M_PI*x*SAMPLE_RATE*4000) + 1);     //4.0 kHz
        sine50[x] = 128*(sin(2.0*M_PI*x*SAMPLE_RATE*5000) + 1);     //5.0 kHz

    }  
}

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Set timer and GPIOs.
            Find preshed button on Keyboard
 *  Input:  None
 *  Return: None
 */

int main(void)
{
    volatile uint8_t x = 0;         //row keyboard
    volatile uint8_t y = 0;         //column keyboard


    GPIO_config_output(&DDRD, PD6);             //PWM output (timer0 output OC0A)

    for(uint8_t d = 0;d < 4; d++){              //--set keyboard GPIO
        DDRC |= (1<<d);                         //set output pins
        DDRB &= ~(1<<d);                        //set inputs pins
        PORTB |= (1<<d);                        //set pull-up
        GPIO_write(&PORTC, d, 1);               //set 1 to putput pins
    }


    TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << WGM00) | (1 << WGM01);  //FAST PWM   and   Set OC0A on Compare Match with register OCR0A, clear OC0A at BOTTOM
    TCCR0B |= (1 << CS00);                                                  //Presclaler 0  =16us

    TIMSK0 |= (1<<TOIE0);                                                   //enable Overflow Interrupt 

    generate_sin(); 

    p_pole = sine5; //set first sin

    sei(); //enable all Interrupt 

    while(1){
                                             //----find preshed button
        if(!bit_is_set(PINB, x)){
            if(y == 0)p_pole = sine5;        //1
            if(y == 1)p_pole = sine10;       //2
            if(y == 2)p_pole = sine15;       //3
            //if(y == 3);                    //A
        }
        x++;
        if(!bit_is_set(PINB, x)){
            if(y == 0)p_pole = sine20;       //4
            if(y == 1)p_pole = sine25;       //5
            if(y == 2)p_pole = sine30;       //6
            //if(y == 3);                    //B
        }
        x++;
        if(!bit_is_set(PINB, x)){
            if(y == 0)p_pole = sine35;       //7
            if(y == 1)p_pole = sine40;       //8
            if(y == 2)p_pole = sine50;       //9
            //if(y == 3);                    //C
        }
        x++;
        if(!bit_is_set(PINB, x)){
            //if(y == 0);        //*
            //if(y == 1);        //0
            //if(y == 2);        //#
            //if(y == 3);        //D
        }
        x = 0;

        GPIO_write(&PORTC, y, 1);   //reset actual column 
        y++;                        //Cheng column
            if(y > 4){
                y = 0;
            }
        GPIO_write(&PORTC, y, 0);   //set next column

        if(i > 124){        //--reset position pointer
            i = 0;
            ptr=p_pole;
        }
    }
}

ISR(TIMER0_OVF_vect){   //Interupt on overflow timer0
    ptr++;              //increment position pointer 
    OCR0A = *ptr;       //set value to comparatore
    i++;                //increment index
}