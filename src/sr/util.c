#include "shift_register_internal.h"

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