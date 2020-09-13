#include <sr/seduce.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


int main(void)
{
    DDRB = 0xFF;
    PORTB = 0xFF;

    _delay_ms(100);
    DDRB = 0;
    PORTB = 0;
    // SIPO
    ShiftRegisterHandle sipoSrHandle = avr_sipo_shift_register_create(
        data_position_create(&DDRB, &PORTB, &PINB, 0), // SIPO_SRCLR
        data_position_create(&DDRB, &PORTB, &PINB, 1), // SIPO_SRCLK
        data_position_create(&DDRB, &PORTB, &PINB, 2), // SIPO_SER
        data_position_create(&DDRB, &PORTB, &PINB, 3), // SIPO_OE
        data_position_create(&DDRB, &PORTB, &PINB, 4), // SIPO_RCLK
        1
    );
    _delay_ms(100);

    avr_sipo_shift_register_init(sipoSrHandle);
    _delay_ms(100);

    avr_sipo_shift_register_write_byte(sipoSrHandle, 207); // 0b11001111
    _delay_ms(100);
    avr_sipo_shift_register_push_data_to_output(sipoSrHandle);
    _delay_ms(100);
    avr_sipo_shift_register_enable_output(sipoSrHandle);
    _delay_ms(100);

    avr_sipo_shift_register_destroy(sipoSrHandle);
    _delay_ms(100);

    // ------------
    // PISO
    _delay_ms(100);

    ShiftRegisterHandle pisoSrHandle = avr_piso_shift_register_create(
        data_position_create(&DDRC, &PORTC, &PINC, 0), // PISO_CE
        data_position_create(&DDRC, &PORTC, &PINC, 1), // PISO_CP
        data_position_create(&DDRC, &PORTC, &PINC, 2), // PISO_Q7
        data_position_create(&DDRC, &PORTC, &PINC, 3), // PISO_PL
        1
    );
    _delay_ms(100);

    avr_piso_shift_register_init(pisoSrHandle);

    avr_piso_shift_register_parallel_load(pisoSrHandle);
    avr_piso_shift_register_read_byte(pisoSrHandle);

    avr_piso_shift_register_destroy(sipoSrHandle);

    DDRB = 0xFF;
    PORTB = 0xFF;

    _delay_ms(100);
    DDRB = 0;
    PORTB = 0;

    return 0;
}
