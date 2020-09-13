#include "shift_register_internal.h"
#include <util/delay.h>
#include <stdlib.h>

const PisoShiftRegister avr_piso_shift_register_create(
    const DataPosition clockEnable,
    const DataPosition clockPulse,
    const DataPosition output,
    const DataPosition parallelLoad,
    int waitTime
)
{
    const ShiftRegister shiftRegister = avr_shift_register_create(SR_PISO, clockEnable, clockPulse, waitTime);
    PisoShiftRegister pisoShiftRegister = { shiftRegister, output, parallelLoad };
    return pisoShiftRegister;
}

void avr_piso_shift_register_init(const PisoShiftRegister shiftRegister)
{    
    data_position_reset_ddr(shiftRegister.output);
    data_position_set_ddr(shiftRegister.parallelLoad);
    data_position_set_ddr(shiftRegister.shiftRegister.clockPulse);
    data_position_set_ddr(shiftRegister.shiftRegister.clockEnable);

    data_position_set_port(shiftRegister.parallelLoad);

    avr_shift_register_enable_clock(shiftRegister.shiftRegister);
}

void avr_piso_shift_register_parallel_load(const PisoShiftRegister shiftRegister)
{
    data_position_reset_port(shiftRegister.parallelLoad);
    sleep(shiftRegister.shiftRegister.waitTime);
    data_position_set_port(shiftRegister.parallelLoad);
}

void avr_piso_shift_register_shift(const PisoShiftRegister shiftRegister)
{
    avr_shift_register_clock_pulse(shiftRegister.shiftRegister);
}

bool avr_piso_shift_register_read_bit(const PisoShiftRegister shiftRegister)
{
    return data_position_get_pin(shiftRegister.output);
}

byte avr_piso_shift_register_read_byte(const PisoShiftRegister shiftRegister)
{
    byte output = 0;

    for (int i = 0; i < 8; i++)
    {
        output |= avr_piso_shift_register_read_bit(shiftRegister) << i;
        avr_piso_shift_register_shift(shiftRegister);
    }

    return output;
}
