#include "shift_register_internal.h"
#include <util/delay.h>
#include <stdlib.h>

ShiftRegisterHandle avr_piso_shift_register_create(
    const DataPosition* clockEnable,
    const DataPosition* clockPulse,
    const DataPosition* output,
    const DataPosition* parallelLoad,
    int waitTime
)
{
    PisoShiftRegister* shiftRegister = (PisoShiftRegister*) calloc(1, sizeof(PisoShiftRegister));

    shiftRegister->output = output;
    shiftRegister->parallelLoad = parallelLoad;
    shiftRegister->shiftRegister.clockEnable = clockEnable;
    shiftRegister->shiftRegister.clockPulse = clockPulse;
    shiftRegister->shiftRegister.waitTime = waitTime;

    return shiftRegister;
}

void avr_piso_shift_register_init(ShiftRegisterHandle shiftRegisterHandle)
{
    PisoShiftRegister* shiftRegister = (PisoShiftRegister*) shiftRegisterHandle;
    
    data_position_reset_ddr(shiftRegister->output);
    data_position_set_ddr(shiftRegister->parallelLoad);
    data_position_set_ddr(shiftRegister->shiftRegister.clockPulse);
    data_position_set_ddr(shiftRegister->shiftRegister.clockEnable);

    data_position_set_port(shiftRegister->parallelLoad);

    avr_shift_register_enable_clock(shiftRegisterHandle);
}

void avr_piso_shift_register_destroy(ShiftRegisterHandle shiftRegisterHandle)
{
    free((PisoShiftRegister*) shiftRegisterHandle);
}

void avr_piso_shift_register_parallel_load(ShiftRegisterHandle shiftRegisterHandle)
{
    PisoShiftRegister* shiftRegister = (PisoShiftRegister*) shiftRegisterHandle;

    data_position_reset_port(shiftRegister->parallelLoad);
    _delay_ms(1);
    data_position_set_port(shiftRegister->parallelLoad);
}

void avr_piso_shift_register_shift(ShiftRegisterHandle shiftRegisterHandle)
{
    avr_shift_register_clock_pulse(shiftRegisterHandle);
}

bool avr_piso_shift_register_read_bit(ShiftRegisterHandle shiftRegisterHandle)
{
    PisoShiftRegister* shiftRegister = (PisoShiftRegister*) shiftRegisterHandle;

    return data_position_get_pin(shiftRegister->output);
}

byte avr_piso_shift_register_read_byte(ShiftRegisterHandle shiftRegisterHandle)
{
    byte output = 0;

    for (int i = 0; i < 8; i++)
    {
        output |= avr_piso_shift_register_read_bit(shiftRegisterHandle) << i;
    }

    return output;
}
