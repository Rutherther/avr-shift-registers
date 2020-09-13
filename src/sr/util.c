#include "shift_register_internal.h"
#include <stdio.h>
#include <util/delay.h>

void set_value_to(volatile byte* reg, byte position, byte value)
{
    if (value == 1) {
        (*reg) |= (1 << position);
    } else if (value == 0) {
        (*reg) &= ~(1 << position); // TODO: check this one
    }
}

void set_value(volatile byte* reg, byte position)
{
    set_value_to(reg, position, 1);
}

void reset_value(volatile byte* reg, byte position)
{
    set_value_to(reg, position, 0);
}

bool get_value(volatile byte* reg, byte position)
{
    return (*reg & (1 << position)) >> position;
}

void sleep(byte milliseconds)
{
    if (milliseconds % 10 == 0) {
        while (milliseconds > 0) {
            _delay_ms(10);
            milliseconds -= 10;
        }
    } else if (milliseconds % 5 == 0) {
        while (milliseconds > 0) {
            _delay_ms(5);
            milliseconds -= 5;
        }
    } else if (milliseconds % 4 == 0) {
        while (milliseconds > 0) {
            _delay_ms(4);
            milliseconds -= 4;
        }
    } else if (milliseconds % 2 == 0) {
        while (milliseconds > 0) {
            _delay_ms(2);
            milliseconds -= 2;
        }
    } else {
        while (milliseconds > 0) {
            _delay_ms(1);
            milliseconds -= 1;
        }
    }
}