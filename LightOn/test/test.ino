#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
    // Read PD2 using the Port D Pin Input Register (PIND)
    if (PIND & _BV(PIND2))
    {
        // PD2 is high, so button is released

        // Set PB5 low using the Port B Data Register (PORTB)
        PORTB &= ~_BV(PORTB5);
    }
    else
    {
        // PD2 is low, so button is pressed

        // Set PB5 high using the Port B Data Register (PORTB)
        PORTB |= _BV(PORTB5);
    }
}

int main(void)
{

    // Configure PD2 as an input using the Data Direction Register D (DDRD)
    DDRD &= ~_BV(DDD2);

    // Enable the pull-up resistor on PD2 using the Port D
    // Data Register (PORTD)
    PORTD |= _BV(PORTD2);

    // Configure external interrupt 0 to generate an interrupt request on any
    // logical change using External Interrupt Control Register A (EICRA)
    EICRA |= _BV(ISC00);

    // Enable external interrupt 0 using the External Interrupt Mask Register
    // (EIMSK)
    EIMSK |= _BV(INT0);

    // Configure PB5 as an output using the Port B Data Direction Register
    // (DDRB)
    DDRB |= _BV(DDB5);

    // Enable interrupts
    sei();

    // Loop forever
    while (1)
    {
        // Nothing to do here
        // All work is done in the ISR
    }
}
