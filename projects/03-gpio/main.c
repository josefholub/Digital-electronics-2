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
#include "gpio.h"

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
    GPIO_config_output(&DDRB, LED_PIN_0);
    GPIO_config_output(&DDRB, LED_PIN_1);

    /* Turn LED off & on */
    GPIO_write(&PORTB, LED_PIN_0, 1);
    GPIO_write(&PORTB, LED_PIN_1, 0);
    
    /* Infinite loop */
    for (;;)
    {
        /* Invert LED and delay */ 
        GPIO_toggle(&PORTB, LED_PIN_0);
        GPIO_toggle(&PORTB, LED_PIN_1);
        _delay_ms(BLINK_DELAY);   
    }
    return (0);
}