#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL // or 8 MHz depending on your MCU clock
#define BUTTON_PIN PD2
#define RELAY_PIN PB0
#define LED_PIN PB1

volatile uint8_t humidifier_on = 0;

void uart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Enable RX and TX
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); // 8-bit data
}

char uart_receive() {
    while (!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

void init_io() {
    DDRB |= (1 << RELAY_PIN) | (1 << LED_PIN);  // Output
    DDRD &= ~(1 << BUTTON_PIN); // Input
    PORTD |= (1 << BUTTON_PIN); // Enable pull-up

    EICRA |= (1 << ISC01); // Falling edge on INT0
    EIMSK |= (1 << INT0);  // Enable INT0
    sei(); // Enable global interrupts
}

void update_state() {
    if (humidifier_on) {
        PORTB |= (1 << RELAY_PIN);
        PORTB |= (1 << LED_PIN);
    } else {
        PORTB &= ~(1 << RELAY_PIN);
        PORTB &= ~(1 << LED_PIN);
    }
}

ISR(INT0_vect) {
    _delay_ms(50); // debounce
    if (!(PIND & (1 << BUTTON_PIN))) {
        humidifier_on ^= 1;
        update_state();
    }
}

int main(void) {
    init_io();
    uart_init(103); // For 9600 baud at 16 MHz

    update_state();

    while (1) {
        char bt = uart_receive(); // Bluetooth command

        if (bt == '1') {
            humidifier_on = 1;
        } else if (bt == '0') {
            humidifier_on = 0;
        }

        update_state();
    }
}
