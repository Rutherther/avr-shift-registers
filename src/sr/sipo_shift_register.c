#include "shift_register_internal.h"
#include <util/delay.h>
#include <stdlib.h>

ShiftRegisterHandle avr_sipo_shift_register_create(
    const DataPosition* clockEnable,
    const DataPosition* clockPulse,
    const DataPosition* input,
    const DataPosition* outputEnable,
    const DataPosition* pushOutput,
    int waitTime
)
{
    SipoShiftRegister* shiftRegister = (SipoShiftRegister*) calloc(1, sizeof(SipoShiftRegister));

    shiftRegister->input = input;
    shiftRegister->outputEnable = outputEnable;
    shiftRegister->pushOutput = pushOutput;
    shiftRegister->shiftRegister.clockEnable = clockEnable;
    shiftRegister->shiftRegister.clockPulse = clockPulse;

    return shiftRegister;
}

void avr_sipo_shift_register_init(ShiftRegisterHandle shiftRegisterHandle)
{
    SipoShiftRegister* shiftRegister = (SipoShiftRegister*) shiftRegisterHandle;

    data_position_set_ddr(shiftRegister->input);
    data_position_set_ddr(shiftRegister->outputEnable);
    data_position_set_ddr(shiftRegister->pushOutput);
    data_position_set_ddr(shiftRegister->shiftRegister.clockPulse);
    data_position_set_ddr(shiftRegister->shiftRegister.clockEnable);

    avr_sipo_shift_register_disable_output(shiftRegisterHandle);
    avr_shift_register_enable_clock(shiftRegisterHandle);
}

void avr_sipo_shift_register_destroy(ShiftRegisterHandle shiftRegisterHandle)
{
    free((SipoShiftRegister *) shiftRegisterHandle);
}

void avr_sipo_shift_register_shift(ShiftRegisterHandle shiftRegisterHandle)
{
    avr_shift_register_clock_pulse(shiftRegisterHandle);
}

void avr_sipo_shift_register_write_bit(ShiftRegisterHandle shiftRegisterHandle, byte data, int position)
{
    SipoShiftRegister* shiftRegister = (SipoShiftRegister*) shiftRegisterHandle;

    data &= (1 << position);

    if (data > 0) {
        data_position_set_port(shiftRegister->input);
    } else {
        data_position_reset_port(shiftRegister->input);
    }

    avr_sipo_shift_register_shift(shiftRegisterHandle);
}

void avr_sipo_shift_register_write_byte(ShiftRegisterHandle shiftRegisterHandle, byte data)
{
    for (int i = 0; i < 8; i++)
    {
        avr_sipo_shift_register_write_bit(shiftRegisterHandle, data, i);
    }
}

void avr_sipo_shift_register_enable_output(ShiftRegisterHandle shiftRegisterHandle)
{
    SipoShiftRegister* shiftRegister = (SipoShiftRegister*) shiftRegisterHandle;
    data_position_reset_port(shiftRegister->outputEnable);
}

void avr_sipo_shift_register_disable_output(ShiftRegisterHandle shiftRegisterHandle)
{
    SipoShiftRegister* shiftRegister = (SipoShiftRegister*) shiftRegisterHandle;
    data_position_set_port(shiftRegister->outputEnable);
}

void avr_sipo_shift_register_push_data_to_output(ShiftRegisterHandle shiftRegisterHandle)
{
    SipoShiftRegister* shiftRegister = (SipoShiftRegister*) shiftRegisterHandle;
    data_position_set_port(shiftRegister->pushOutput);
}

void avr_sipo_shift_register_reset(ShiftRegisterHandle shiftRegisterHandle)
{
    avr_shift_register_disable_clock(shiftRegisterHandle);
    _delay_ms(1);
    avr_shift_register_enable_clock(shiftRegisterHandle);
}
