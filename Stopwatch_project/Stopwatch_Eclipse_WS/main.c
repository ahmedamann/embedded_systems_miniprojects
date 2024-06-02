#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char ticks = 0;
int digits[6] = {0};

void update_digits() {
    digits[0]++; // Updating the last digit to increment seconds.

    /* The for loop checks for numbers that are greater than 9 and changes the value to
     * zero then increments the digit after to ensure a functional operation for
     * the Stop watch */
    for (int i = 0; i < 5; i++) {
        if (digits[i] > 9) {
            digits[i] = 0;
            digits[i + 1]++;
        }
    }
}


ISR(TIMER1_COMPA_vect) {
	/* For the ISR of interrupt of timer1 if tick reaches 4 (which is one second )
	 *  we reset ticks to start counting for the next second and update digits */
    ticks++;
    if (ticks == 4) {
        ticks = 0;
        update_digits();
    }
}

ISR(INT0_vect) {
	/* For the ISR of external interrupt 0, when the interrupt is triggered, its
	 * responsible for clearing all digits and reseting the stop watch to start counting
	 * from zero again*/

    for (int i = 0; i < 6; i++) {
        digits[i] = 0;
    }
}

ISR(INT1_vect) {
	/* For the ISR of external interrupt 1, when the interrupt is triggered, its
	 * responsible for stopping the timer to stop the digits from incrementing*/

    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); // Clear all pre-scaler bits to stop the timer.
}

ISR(INT2_vect) {
	/* For the ISR of external interrupt 2, when the interrupt is triggered, its
	 * responsible for re-enabling the timer to allow the stop watch to continue working*/

	TCCR1B = (1 << WGM12) | (1 << CS11); // Resume the timer.
}

void init_timer1(void) {
    TCCR1B = (1 << WGM12) | (1 << CS11); // Set CTC mode and pre-scaler to 8 for timer 1.
    OCR1A = 31250; // Set the compare match to trigger interrupt every 0.25 seconds.
    TIMSK = (1 << OCIE1A); // Enable interrupt on compare match A.
    sei(); // Enable I-Bit.
}


void init_interrupts(void) {
    PORTD |= (1 << PD2); // Enable internal pull-up resistor for INT0.
    PORTB |= (1 << PB2); // Enable internal pull-up resistor for INT2.

    MCUCR |= (1 << ISC01) | (1 << ISC11) | (1 << ISC10); // INT0 triggers on falling edge, INT1 on rising edge.

    GICR |= (1 << INT0) | (1 << INT1) | (1 << INT2); // Enable external interrupts INT0
    sei();
}

int main() {
    DDRA = 0xFF; // PORTA as output
    DDRC = 0xFF; // PORTC as output
    DDRD &= ~((1 << PD2) | (1 << PD3)); // PD2 and PD3 as input for interrupts INT0 and INT1.
    DDRB &= ~(1 << PB2); //PB2 as input for INT2.

    init_timer1();
    init_interrupts();


    while (1) {
			for (int i = 0; i < 6; i++) {
				PORTA = (1 << (5 - i));
				PORTC = digits[i]; // Sending digit to the 7447 decoder.
				_delay_ms(5); // Increasing delay for better visibility.
			}
    }
}
