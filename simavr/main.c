#include <sr/seduce.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


int main(void)
{
    // SIPO
    const SipoShiftRegister sipoSr = avr_sipo_shift_register_create(
        data_position_create(&PINB, 0), // SIPO_SRCLR
        data_position_create(&PINB, 1), // SIPO_SRCLK
        data_position_create(&PINB, 2), // SIPO_SER
        data_position_create(&PINB, 3), // SIPO_OE
        data_position_create(&PINB, 4), // SIPO_RCLK
        1
    );

    avr_sipo_shift_register_init(sipoSr);

    avr_sipo_shift_register_write_byte(sipoSr, 207); // 0b11001111
    avr_sipo_shift_register_push_data_to_output(sipoSr);
    avr_sipo_shift_register_enable_output(sipoSr);

    // ------------
    // PISO
    _delay_ms(100);

    const PisoShiftRegister pisoSr = avr_piso_shift_register_create(
        data_position_create(&PINC, 0), // PISO_CE
        data_position_create(&PINC, 1), // PISO_CP
        data_position_create(&PINC, 2), // PISO_Q7
        data_position_create(&PINC, 3), // PISO_PL
        1
    );

    avr_piso_shift_register_init(pisoSr);

    avr_piso_shift_register_parallel_load(pisoSr);
    avr_piso_shift_register_read_byte(pisoSr);

    return 0;
}
