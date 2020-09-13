#include "shift_register_internal.h"
#include <util/delay.h>
#include <stdlib.h>

const SipoShiftRegister avr_sipo_shift_register_create(
    const DataPosition clockEnable,
    const DataPosition clockPulse,
    const DataPosition input,
    const DataPosition outputEnable,
    const DataPosition pushOutput,
    int waitTime
)
{
    const ShiftRegister shiftRegister = avr_shift_register_create(SR_SIPO, clockEnable, clockPulse, waitTime);
    SipoShiftRegister sipoShiftRegister = { shiftRegister, input, outputEnable, pushOutput };
    return sipoShiftRegister;
}

void avr_sipo_shift_register_init(const SipoShiftRegister shiftRegister)
{
    data_position_set_ddr(shiftRegister.input);
    data_position_set_ddr(shiftRegister.outputEnable);
    data_position_set_ddr(shiftRegister.pushOutput);
    data_position_set_ddr(shiftRegister.shiftRegister.clockPulse);
    data_position_set_ddr(shiftRegister.shiftRegister.clockEnable);

    avr_sipo_shift_register_disable_output(shiftRegister);
    avr_shift_register_enable_clock(shiftRegister.shiftRegister);
}

void avr_sipo_shift_register_shift(const SipoShiftRegister shiftRegister)
{
    avr_shift_register_clock_pulse(shiftRegister.shiftRegister);
}

void avr_sipo_shift_register_write_bit(const SipoShiftRegister shiftRegister, byte data, int position)
{
    data &= (1 << position);

    if (data > 0) {
        data_position_set_port(shiftRegister.input);
    } else {
        data_position_reset_port(shiftRegister.input);
    }

    avr_sipo_shift_register_shift(shiftRegister);
}

void avr_sipo_shift_register_write_byte(const SipoShiftRegister shiftRegister, byte data)
{
    for (int i = 0; i < 8; i++)
    {
        avr_sipo_shift_register_write_bit(shiftRegister, data, i);
    }
}

void avr_sipo_shift_register_enable_output(const SipoShiftRegister shiftRegister)
{
    data_position_reset_port(shiftRegister.outputEnable);
}

void avr_sipo_shift_register_disable_output(const SipoShiftRegister shiftRegister)
{
    data_position_set_port(shiftRegister.outputEnable);
}

void avr_sipo_shift_register_push_data_to_output(const SipoShiftRegister shiftRegister)
{
    data_position_set_port(shiftRegister.pushOutput);
}

void avr_sipo_shift_register_reset(const SipoShiftRegister shiftRegister)
{
    avr_shift_register_disable_clock(shiftRegister.shiftRegister);
    sleep(shiftRegister.shiftRegister.waitTime);
    avr_shift_register_enable_clock(shiftRegister.shiftRegister);
    sleep(shiftRegister.shiftRegister.waitTime);
}