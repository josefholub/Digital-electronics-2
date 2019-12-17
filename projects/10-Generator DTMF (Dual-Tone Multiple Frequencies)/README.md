
# Project: Tone generator

### Introduction
This project generate output sine with changing frequency. Value of frequency is entered from keyboard. When user pressed a button on keyboard, software immediately cange output frequency. On output pin is connected low pass filter.
### Hardware
- Microcontroller - ATmega2560
- 4x4 keyboard
- low pass filter
- speaker (optimal)

### Software
- AVR 8-bit Toolchain

#### Libraries
- stdlib.h
- avr/io.h
- avr/interrupt.h
- math.h

### Simple principle of function
In MCU generate arrays of amplitude sinus. Program used Timer0 in Fast PWM mode. When user pressed button on keyboard, software assigned to timer comparator required array with amplitude sinus. On output pin with PWM signal is connected low pass filter.
Output sins can be in this frequency: 0.5kHz, 1kHz, 1.5kHz, 2kHz, 2.5kHz, 3kHz, 3.5kHz, 4kHz, 5kHz

### Connections
![](https://i.imgur.com/CBKO0eu.jpg)

### Layout keyboard
Pin on  keyboard | Output frequency
------------- | -------------
1   | 0.5kHz
 2  | 1kHz,
3  | 1.5kHz
4  | 2kHz
5  | 2.5kHz
6  | 3kHz
7  | 3.5kHz
8  | 4kHz
9  | 5kHz

### Output signal
![](https://i.imgur.com/xWbBwh9.jpg)

------------


------------


##### License 
MIT
