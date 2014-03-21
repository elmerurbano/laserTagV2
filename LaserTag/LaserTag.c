/*
 * LaserTag.c
 *
 * Created: 11/1/2013 1:20:58 PM
 *  Author: Elmer
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define TRIGGER		0
#define IR_LED		0
#define TRIG_LED	1
#define IR_DELAY	12

void delay_us(int us) {
	for (int i = 0; i < us; i++) {
		_delay_us(1);
	}
}

void send_low (void) {
	PORTB &= ~(1 << IR_LED);	//turn off IR_LED
	_delay_us(IR_DELAY);
}

void send_high (void) {
	PORTB |= (1 << IR_LED);     //turn on IR_LED
	_delay_us(IR_DELAY);
}

//send IR bursts for time specified (microseconds)
void burst(int length) {
	while (length > 0) {
		send_high();
		send_low();
		length -= IR_DELAY * 2;
	}
	PORTB &= ~(1 << IR_LED);
}

void sendCode() {  //sends 0b00101010 -> 42
	burst(1000);
	_delay_us(500);
	burst(1000);
	_delay_us(500);
	burst(1500);
	_delay_us(500);
	burst(1000);
	_delay_us(500);
	burst(1500);
	_delay_us(500);
	burst(1000);
	_delay_us(500);
	burst(1500);
	_delay_us(500);
	burst(1000);
	_delay_us(500);
}

int main(void) {	
	DDRB = 0x03;
	DDRC = 0x00;
	
	PORTB = 0x00;
	PORTC = 0x01;
	
	while (1) {
		if (PINC & (1 << TRIGGER)) { //while trigger is pushed (looking for digital high)
			sendCode();
			sendCode();
			sendCode();
			_delay_ms(100);
		}
    }
}