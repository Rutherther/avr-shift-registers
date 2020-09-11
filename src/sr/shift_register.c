#include "seduce.h"
#include "shift_register_internal.h"
#include <util/delay.h>
#include <stdlib.h>

void avr_shift_register_destroy(ShiftRegisterHandle shiftRegisterHandle)
{
    free((ShiftRegister*) shiftRegisterHandle);
}

void avr_shift_register_clock_pulse(ShiftRegisterHandle shiftRegisterHandle)
{
    ShiftRegister* sr = (ShiftRegister*) shiftRegisterHandle;
    
    data_position_set_port(sr->clockPulse);
    _delay_ms(1);
    data_position_reset_port(sr->clockPulse);
}

void avr_shift_register_enable_clock(ShiftRegisterHandle shiftRegisterHandle)
{
    ShiftRegister* sr = (ShiftRegister*) shiftRegisterHandle;
    data_position_set_port(sr->clockEnable);

    sr->clockEnabled = 1;
}

void avr_shift_register_disable_clock(ShiftRegisterHandle shiftRegisterHandle)
{
    ShiftRegister* sr = (ShiftRegister*) shiftRegisterHandle;
    data_position_reset_port(sr->clockEnable);

    sr->clockEnabled = 0;
}