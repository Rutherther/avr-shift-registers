#include <sr/seduce.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // SIPO
    ShiftRegisterHandle sipoSrHandle = avr_sipo_shift_register_create(
        data_position_create(&DDRB, &PORTB, &PINB, 0), // SIPO_SRCLR
        data_position_create(&DDRB, &PORTB, &PINB, 1), // SIPO_SRCLK
        data_position_create(&DDRB, &PORTB, &PINB, 2), // SIPO_SER
        data_position_create(&DDRB, &PORTB, &PINB, 3), // SIPO_OE
        data_position_create(&DDRB, &PORTB, &PINB, 4), // SIPO_RCLK
        1
    );

    avr_sipo_shift_register_init(sipoSrHandle);

    avr_sipo_shift_register_write_byte(sipoSrHandle, 207); // 0b11001111
    avr_sipo_shift_register_push_data_to_output(sipoSrHandle);
    avr_sipo_shift_register_enable_output(sipoSrHandle);

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

    avr_piso_shift_register_parallel_load(pisoSrHandle);
    avr_piso_shift_register_read_byte(pisoSrHandle);
}