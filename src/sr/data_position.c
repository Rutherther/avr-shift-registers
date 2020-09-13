#include "shift_register_internal.h"
#include <stdlib.h>

const DataPosition data_position_create(volatile byte* pin, byte position) {
    DataPosition dp = { pin, position };
    return dp;
}

bool data_position_get_pin(const DataPosition position)
{
    return get_value(position.pin, position.position);
}

void data_position_set_port(const DataPosition position)
{
    set_value(position.pin + SR_PORT_OFFSET, position.position);
}

void data_position_reset_port(const DataPosition position)
{
    reset_value(position.pin + SR_PORT_OFFSET, position.position);
}

void data_position_set_ddr(const DataPosition position)
{
    set_value(position.pin + SR_DDR_OFFSET, position.position);
}

void data_position_reset_ddr(const DataPosition position)
{
    reset_value(position.pin + SR_DDR_OFFSET, position.position);
}