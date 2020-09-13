#ifndef _SHIFT_REGISTERS_INTERNAL
#define _SHIFT_REGISTERS_INTERNAL

#include "seduce.h"

void set_value_to(volatile byte* reg, byte position, byte value);
void set_value(volatile byte* reg, byte position);
void reset_value(volatile byte* reg, byte position);
bool get_value(volatile byte* reg, byte position);

void sleep(byte milliseconds);

#endif