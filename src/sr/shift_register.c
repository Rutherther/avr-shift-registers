#include "seduce.h"
#include "shift_register_internal.h"
#include <util/delay.h>
#include <stdlib.h>

const ShiftRegister avr_shift_register_create(
    ShiftRegisterTypeHeader type,
    const DataPosition clockEnable,
    const DataPosition clockPulse,
    int waitTime
)
{
    ShiftRegister sr = { type, clockEnable, clockPulse, waitTime };
    return sr;
}

void avr_shift_register_clock_pulse(ShiftRegister shiftRegister)
{    
    data_position_set_port(shiftRegister.clockPulse);
    sleep(shiftRegister.waitTime);
    data_position_reset_port(shiftRegister.clockPulse);
}

void avr_shift_register_enable_clock(ShiftRegister shiftRegister)
{
    data_position_set_port(shiftRegister.clockEnable);
}

void avr_shift_register_disable_clock(ShiftRegister shiftRegister)
{
    data_position_reset_port(shiftRegister.clockEnable);
}