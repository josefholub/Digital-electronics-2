/*library DE2 Holub Lorenc*/
#include "gpio.h"

//  Function
void GPIO_config_output(volatile uint8_t *reg_name, uint8_t pin_num){
    *reg_name |= _BV(pin_num);
}
void GPIO_config_input_nopull(volatile uint8_t *reg_DDR, volatile uint8_t *reg_PORT, uint8_t pin_num){
    *reg_DDR &= ~_BV(pin_num);
    *reg_PORT &= ~_BV(pin_num);
}
void GPIO_config_input_pullup(volatile uint8_t *reg_DDR, volatile uint8_t *reg_PORT, uint8_t pin_num){
    *reg_DDR &= ~_BV(pin_num);
    *reg_PORT |= _BV(pin_num);
}
void GPIO_write(volatile uint8_t *reg_name, uint8_t pin_num, uint8_t pin_val){
    if(pin_val == 0) *reg_name &= ~_BV(pin_num);
    else *reg_name |= _BV(pin_num);
}
void GPIO_toggle(volatile uint8_t *reg_name, uint8_t pin_num){
    *reg_name ^=  _BV(pin_num);
}
uint8_t GPIO_read(volatile uint8_t *reg_name, uint8_t pin_num){
    return (*reg_name & _BV(pin_num));
}