#include "shift_register_internal.h"
#include <stdlib.h>

DataPosition* data_position_create(volatile byte* ddr, volatile byte* port, volatile byte* pin, byte position) {
    DataPosition* dp = (DataPosition*) malloc(sizeof(DataPosition));
    dp->ddr = ddr;
    dp->port = port;
    dp->pin = pin;
    dp->position = position;

    return dp;
}

void data_position_destroy(const DataPosition* position)
{
    free((DataPosition*) position);
}

bool data_position_get_pin(const DataPosition* position)
{
    return get_value(position->pin, position->position);
}

void data_position_set_port(const DataPosition* position)
{
    set_value(position->port, position->position);
}

void data_position_reset_port(const DataPosition* position)
{
    reset_value(position->port, position->position);
}

void data_position_set_ddr(const DataPosition* position)
{
    set_value(position->ddr, position->position);
}

void data_position_reset_ddr(const DataPosition* position)
{
    reset_value(position->ddr, position->position);
}