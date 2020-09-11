#ifndef _SHIFT_REGISTERS_INTERNAL
#define _SHIFT_REGISTERS_INTERNAL

#include "seduce.h"

void set_value_to(volatile byte* reg, byte position, byte value);
void set_value(volatile byte* reg, byte position);
void reset_value(volatile byte* reg, byte position);
bool get_value(volatile byte* reg, byte position);

typedef enum {
    SR_PISO,
    SR_SIPO
} ShiftRegisterTypeHeader;

typedef struct {
    ShiftRegisterTypeHeader type;
} ShiftRegisterHeader;

typedef struct {
    ShiftRegisterHeader header;
    const DataPosition* clockEnable;
    const DataPosition* clockPulse;
    int waitTime;
    bool clockEnabled;
} ShiftRegister;

typedef struct {
    ShiftRegister shiftRegister;
    const DataPosition* output;
    const DataPosition* parallelLoad;
} PisoShiftRegister;

typedef struct {
    ShiftRegister shiftRegister;
    const DataPosition* input;
    const DataPosition* outputEnable;
    const DataPosition* pushOutput;
} SipoShiftRegister;

#endif