/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-07-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_PIN_0     PB5
#define LED_PIN_1     PB0
#define BUTTON        PD2
#define BLINK_DELAY 100

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
  * Brief:  Main program. Blink a LED with delay function.
  * Input:  None
  * Return: None
  */
int main(void)
{
    /* Set output pin */
    DDRB |= _BV(LED_PIN_0);           /* DDRB = DDRB or (0010 0000) */
    DDRB |= _BV(LED_PIN_1);
    DDRD &= ~_BV(BUTTON);    /*tacitko*/

    /* Turn LED off & on */
    PORTB &= ~_BV(LED_PIN_0);         /* PORTB = PORTB and (0010 0000) */
    PORTB &= ~_BV(LED_PIN_1);
    PORTD |= _BV(BUTTON);    /*aktivace PULL UP rezistoru*/

    //loop_until_bit_is_clear(PIND , BUTTON); //ceka do stisku
    
    /* Infinite loop */
    for (;;)
    {
        /* Invert LED and delay */
        if (bit_is_set(PIND , BUTTON)){
          _delay_ms(BLINK_DELAY+BLINK_DELAY);
        }else{
          _delay_ms(BLINK_DELAY);
        } 
        PORTB ^= _BV(LED_PIN_0);      /* PORTB = PORTB xor (0010 0000) */     /* Wait for several milisecs */
        PORTB ^= _BV(LED_PIN_1);
        
    }

    return (0);
}
