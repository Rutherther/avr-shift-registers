#ifndef _SHIFT_REGISTERS_SEDUCE
#define _SHIFT_REGISTERS_SEDUCE

// TODO: make this working with flash memory so the data is not placed on RAM
// TODO: assume PINB is x. then DDRB is x + 1 and PORTB is x + 2.

/**
 * @file seduce.h
 * @author Rutherther
 * @date 9 Sep 2020
 * @brief File containing public exports of the library.
 * 
 * This header should be included in projects that use this library.
 * There aren't any other headers that should be imported.
 * Other headers suffixed using _internal should be used only
 * internally from within the library.
 * 
 * @see DataPosition
 * @see ShiftRegisterHandle
 */

/**
 * @brief Handle to work with the shift registers.
 * 
 * This handle can be obtained using @see avr_piso_shift_register_init for PISO
 * or @see avr_sipo_shift_register_init for SIPO.
 * PISO stands for parallel-in/serial-out (used for getting input from shift register).
 * SIPO stands for serial-in/parallel-out (used for passing output using shift register).
 * 
 */
typedef void* ShiftRegisterHandle;
typedef unsigned char bool;
typedef unsigned char byte;

/**
 * @brief Hold data port info.
 * 
 * Structure used to hold DDR, PORT and PIN registers
 * along with a bit position.
 * 
 * Can be used to dynamically save a position of I/O .
 * 
 * @note Function @see data_position_create can be used as an shorthand for creating DataPosition.
 * 
 * Example usage:
 * @code
 *  data_position_create(&DDRA, &PORTA, &PINA, 1); // Pass position 1 of PINA
 * @endcode
 */
typedef struct DataPosition {
    volatile byte* ddr;
    volatile byte* port;
    volatile byte* pin;
    byte position;
} DataPosition;

/**
 * @brief Create DataPosition struct.
 * 
 * @param ddr Pointer to DDR register (for example &DDRA).
 * @param port Pointer to PORT register (for example &PORTA).
 * @param pin Pointer to PIN register (for example &PINA).
 * @param position Position within the register. 
 * @return DataPosition 
 * @note 0 is for LSB. 7 is for MSB. PORTA1 can be used.
 */
extern DataPosition* data_position_create(volatile byte* ddr, volatile byte* port, volatile byte* pin, byte position);

/**
 * @brief Destroy DataPosition
 * 
 * @param position 
 */
extern void data_position_destroy(const DataPosition* position);

/**
 * @brief Get PIN value of DataPosition.
 * 
 * @param position 
 * @return true When PIN (input) is HIGH.
 * @return false When PIN (input) is LOW.
 */
extern bool data_position_get_pin(const DataPosition* position);

/**
 * @brief Set PORT value of DataPosition.
 * 
 * This function makes DataPosition PORT register value 1.
 * If the port is OUTPUT, it will output 5V.
 * If the port is INPUT, the pull up resistor will be activated.
 * 
 * @param position 
 */
extern void data_position_set_port(const DataPosition* position);

/**
 * @brief Reset PORT value of DataPosition.
 * 
 * This function makes DataPosition PORT register value 0.
 * If the port is OUTPUT, it will output 0V.
 * If the port is INPUT, the pull up resistor will be deactivated.
 * 
 * @param position 
 */
extern void data_position_reset_port(const DataPosition* position);

/**
 * @brief Set DDR value of DataPosition
 * 
 * This function makes DataPosition DDR register value 1 and thus making it OUTPUT.
 * 
 * @param position 
 */
extern void data_position_set_ddr(const DataPosition* position);

/**
 * @brief Reset DDR value of DataPosition.
 * 
 * This function makes DataPosition DDR register value 0 and thus making it INPUT.
 * 
 * @param position 
 */
extern void data_position_reset_ddr(const DataPosition* position);

/*******************************************************************************
 *                                                                             *
 *                               SHIFT REGISTER                                *
 *  Part to define basic shift register functions used for both PISO and SIPO  *
 *                                                                             *
 *******************************************************************************/

/**
 * @brief Send clock pulse to shift register.
 * 
 * This function makes the clockPulse position HIGH for specified waitTime
 * Then makes it LOW again.`
 * 
 * @param shiftRegisterHandle 
 */
extern void avr_shift_register_clock_pulse(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Enable shift register clock.
 * 
 * This function enables the DataPosition for clockEnable.
 * The clock must be enabled before using the sift register
 * Otherwise the shift register won't do anything.
 * 
 * For SIPO registers if clockEnable is made low
 * the register is also cleared.
 * 
 * @param shiftRegisterHandle 
 * @note This function will be called in the init function.
 */
extern void avr_shift_register_enable_clock(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Disable shift register clock.
 * 
 * This funciton disables the DataPosition for clockEnable.
 * @see avr_shift_register_enable_clock for more info
 * 
 * @note some SIPO registers can be cleared using this function.
 * 
 * @param shiftRegisterHandle 
 */
extern void avr_shift_register_disable_clock(ShiftRegisterHandle shiftRegisterHandle);

/*******************************************************************************
 *                                                                             *
 *                                     PISO                                    *
 *  Part to define PISO shift register functions to allow shifting and getting *
 *  input from the parallel-in/serial-out shift register                       *
 *                                                                             *
 *******************************************************************************/

/**
 * @brief Create PISO shift register.
 * 
 * This function creates PISO shift register.
 * Functions beginning with avr_piso_shift_register may be used
 * with this type of ShiftRegister.
 * 
 * @param clockEnable Can be specified as CE in datasheet.
 * @param clockPulse Can be specified as CP in datasheet.
 * @param output Can be specified as Q7 in datasheet. Be careful not to use negative Q7.
 * @param parallelLoad Can be specified as PL.
 * @param waitTime Used to wait when pulsing the clock
 * @return ShiftRegisterHandle 
 * 
 * @note You should always init the shift register after creating it. Use @see avr_piso_shift_register_init.
 */
extern ShiftRegisterHandle avr_piso_shift_register_create(
    const DataPosition* clockEnable,
    const DataPosition* clockPulse,
    const DataPosition* output,
    const DataPosition* parallelLoad,
    int waitTime
);

/**
 * @brief Setup base values for PISO shift register.
 * 
 * This function initializes the DataPositions so they are correctly set as
 * inputs or outputs.
 * 
 * @see avr_shift_register_enable_clock is also called to enable the clock.
 * 
 * @param shiftRegisterHandle
 */
extern void avr_piso_shift_register_init(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Destroy and free PISO shift register memory
 * 
 * @param shiftRegisterHandle 
 */
extern void avr_piso_shift_register_destroy(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Asynchronously load the data
 * 
 * This function is used on shift registers
 * that have the parallel load port.
 * PL port will be set LOW and then back
 * HIGH after waitTime has passed.
 * 
 * @param shiftRegisterHandle 
 */
extern void avr_piso_shift_register_parallel_load(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Shift next bit
 * 
 * This function shifts next bit from the PISO shift register.
 * It just makes the clockPulse HIGH and then LOW.
 * 
 * @param shiftRegisterHandle 
 */
extern void avr_piso_shift_register_shift(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Read current bit
 * 
 * This function gets the data from the output.
 * It will return 0 for LOW or 1 for HIGH
 * 
 * @note You can read the whole byte using @see avr_piso_shift_register_read_byte
 * 
 * @param shiftRegisterHandle 
 * @return true 
 * @return false 
 */
extern bool avr_piso_shift_register_read_bit(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Read byte from the shift register
 * 
 * This function gets byte from the output.
 * The first value read goes to the LSB.
 * 
 * @note You can read one bit using @see avr_piso_shift_register_read_bit
 * 
 * @param shiftRegisterHandle 
 * @return byte 
 */
extern byte avr_piso_shift_register_read_byte(ShiftRegisterHandle shiftRegisterHandle);

/*******************************************************************************
 *                                                                             *
 *                                     SIPO                                    *
 *  Part to define SIPO shift register functions to allow shifting and passing *
 *  output to the seiarl-in/parallel-out shift register                        *
 *                                                                             *
 *******************************************************************************/

/**
 * @brief Create SIPO shift register handle.
 * 
 * This function creates SIPO shift register.
 * Functions beginning with avr_sipo_shift_register may be used
 * with this type of ShiftRegister.
 * 
 * @param clockEnable Can be specified as SRCLR in datasheet.
 * @param clockPulse Can be specified as SRCLK in datasheet.
 * @param input Can be specified as SER in datasheet.
 * @param outputEnable Can be specified as OE in datasheet.
 * @param pushOutput Can be specified as RCLK in datasheet.
 * @param waitTime Used to wait when pulsing the clock
 * @return ShiftRegisterHandle 
 * 
 * @note You should always init the shift register after creating it. Use @see avr_sipo_shift_register_init.
 */
extern ShiftRegisterHandle avr_sipo_shift_register_create(
    const DataPosition* clockEnable, // SRCLR
    const DataPosition* clockPulse, // SRCLK
    const DataPosition* input, // SER
    const DataPosition* outputEnable, // OE
    const DataPosition* pushOutput, // RCLK
    int waitTime
);

/**
 * @brief Setup base values for PISO shift register.
 * 
 * This function initializes the DataPositions so they are correctly set as
 * inputs or outputs.
 * 
 * @see avr_shift_register_enable_clock is also called to enable the clock.
 * 
 * @param shiftRegisterHandle
 */
extern void avr_sipo_shift_register_init(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Destroy and free SIPO shift register memory
 * 
 * @param shiftRegisterHandle 
 */
extern void avr_sipo_shift_register_destroy(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Shifts data by one position.
 * 
 * This function shifts next bit from the PISO shift register.
 * It just makes the clockPulse HIGH and then LOW.
 * 
 * @param shiftRegisterHandle 
 */
extern void avr_sipo_shift_register_shift(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Write one bit to the shift register.
 * 
 * This function writes one bit to the shift register.
 * Shift function is also called to save the data.
 * 
 * @note You can read the whole byte using @see avr_sipo_shift_register_write_byte
 * 
 * @param shiftRegisterHandle 
 * @param data 
 * @param position 
 */
extern void avr_sipo_shift_register_write_bit(ShiftRegisterHandle shiftRegisterHandle, byte data, int position);

/**
 * @brief Write whole byte to the shift register.
 * 
 * This function writes whole byte to the shift register.
 * The first written bit will be the LSB.
 * 
 * @note You can write only one bit using @see avr_sipo_shift_register_write_bit
 * 
 * @param shiftRegisterHandle 
 * @param data 
 */
extern void avr_sipo_shift_register_write_byte(ShiftRegisterHandle shiftRegisterHandle, byte data);

/**
 * @brief Enable output DataPosition
 * 
 * This function enables the output so the shift register
 * outputs the data shifted in it.
 * 
 * @param shiftRegisterHandle 
 */
extern void avr_sipo_shift_register_enable_output(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Disable output DataPosition
 * 
 * This function disables the output so the shift register
 * doesn't output anything.
 * 
 * @param shiftRegisterHandle 
 */
extern void avr_sipo_shift_register_disable_output(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Psuh data to output
 * 
 * This function pushes the data from the shift register
 * to the storage register. That means the data you shift
 * in will be set only after you call this function.
 * 
 * @param shiftRegisterHandle 
 */
extern void avr_sipo_shift_register_push_data_to_output(ShiftRegisterHandle shiftRegisterHandle);

/**
 * @brief Disable and enable clock to reset the SR value
 * 
 * This funciton disables the clock, then waits a bit
 * and enables the clock. Doing that the register will
 * be reset.
 * 
 * @param shiftRegisterHandle 
 */
extern void avr_sipo_shift_register_reset(ShiftRegisterHandle shiftRegisterHandle);

#endif