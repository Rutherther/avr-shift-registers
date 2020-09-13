#ifndef _SHIFT_REGISTERS_SEDUCE
#define _SHIFT_REGISTERS_SEDUCE

#ifndef SR_DDR_OFFSET
    #define SR_DDR_OFFSET 1
#endif

#ifndef SR_PORT_OFFSET
    #define SR_PORT_OFFSET 2
#endif

typedef unsigned char bool;
typedef unsigned char byte;

/**
 * @brief Hold data port info.
 * 
 * Structure used to hold PIN registers
 * along with a bit position.
 * 
 * DDR and PORT registers will be automatically located
 * to save some RAM. offset of DDR can be set
 * using #define SR_DDR_OFFSET (default 1). For PORT use
 * #define SR_PORT_OFFSET (default 2). This number is then
 * added to the PIN address
 * 
 * Can be used to dynamically save a position of I/O .
 * 
 * @note Function @see data_position_create can be used as an shorthand for creating DataPosition.
 * 
 * Example usage:
 * @code
 *  data_position_create(&PINA, 1); // Pass position 1 of PINA
 * @endcode
 */
typedef struct DataPosition {
    volatile byte* pin;
    byte position;
} DataPosition;

typedef enum {
    SR_PISO,
    SR_SIPO
} ShiftRegisterTypeHeader;

typedef struct {
    const ShiftRegisterTypeHeader type;
    const DataPosition clockEnable;
    const DataPosition clockPulse;
    int waitTime;
} ShiftRegister;

typedef struct {
    const ShiftRegister shiftRegister;
    const DataPosition output;
    const DataPosition parallelLoad;
} PisoShiftRegister;

typedef struct {
    const ShiftRegister shiftRegister;
    const DataPosition input;
    const DataPosition outputEnable;
    const DataPosition pushOutput;
} SipoShiftRegister;

/**
 * @brief Create DataPosition struct.
 * 
 * Pointers to PORT and DDR are automatically calculated.
 * Check out DataPosition documentation for more information.
 * 
 * @param pin Pointer to PIN register (for example &PINA).
 * @param position Position within the register. 
 * @return DataPosition 
 * @note 0 is for LSB. 7 is for MSB. PORTA1 can be used.
 */
extern const DataPosition data_position_create(volatile byte* pin, byte position);

/**
 * @brief Get PIN value of DataPosition.
 * 
 * @param position 
 * @return true When PIN (input) is HIGH.
 * @return false When PIN (input) is LOW.
 */
extern bool data_position_get_pin(const DataPosition position);

/**
 * @brief Set PORT value of DataPosition.
 * 
 * This function makes DataPosition PORT register value 1.
 * If the port is OUTPUT, it will output 5V.
 * If the port is INPUT, the pull up resistor will be activated.
 * 
 * @param position 
 */
extern void data_position_set_port(const DataPosition position);

/**
 * @brief Reset PORT value of DataPosition.
 * 
 * This function makes DataPosition PORT register value 0.
 * If the port is OUTPUT, it will output 0V.
 * If the port is INPUT, the pull up resistor will be deactivated.
 * 
 * @param position 
 */
extern void data_position_reset_port(const DataPosition position);

/**
 * @brief Set DDR value of DataPosition
 * 
 * This function makes DataPosition DDR register value 1 and thus making it OUTPUT.
 * 
 * @param position 
 */
extern void data_position_set_ddr(const DataPosition position);

/**
 * @brief Reset DDR value of DataPosition.
 * 
 * This function makes DataPosition DDR register value 0 and thus making it INPUT.
 * 
 * @param position 
 */
extern void data_position_reset_ddr(const DataPosition position);

/*******************************************************************************
 *                                                                             *
 *                               SHIFT REGISTER                                *
 *  Part to define basic shift register functions used for both PISO and SIPO  *
 *                                                                             *
 *******************************************************************************/

/**
 * @brief Create shift register.
 * 
 * This function creates generic shift register.
 * Functions beginning with avr_piso_shift_register may be used
 * with this type of ShiftRegister.
 * 
 * @param type
 * @param clockEnable
 * @param clockPulse
 * @param waitTime
 * @return ShiftRegister 
 * 
 * @note You should always init the shift register after creating it. Use @see avr_piso_shift_register_init.
 */
extern const ShiftRegister avr_shift_register_create(
    ShiftRegisterTypeHeader type,
    const DataPosition clockEnable,
    const DataPosition clockPulse,
    int waitTime
);

/**
 * @brief Send clock pulse to shift register.
 * 
 * This function makes the clockPulse position HIGH for specified waitTime
 * Then makes it LOW again.`
 * 
 * @param shiftRegister
 */
extern void avr_shift_register_clock_pulse(const ShiftRegister shiftRegister);

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
 * @param shiftRegister
 * @note This function will be called in the init function.
 */
extern void avr_shift_register_enable_clock(const ShiftRegister shiftRegister);

/**
 * @brief Disable shift register clock.
 * 
 * This funciton disables the DataPosition for clockEnable.
 * @see avr_shift_register_enable_clock for more info
 * 
 * @note some SIPO registers can be cleared using this function.
 * 
 * @param shiftRegister
 */
extern void avr_shift_register_disable_clock(const ShiftRegister shiftRegister);

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
 * @return PisoShiftRegister 
 * 
 * @note You should always init the shift register after creating it. Use @see avr_piso_shift_register_init.
 */
extern const PisoShiftRegister avr_piso_shift_register_create(
    const DataPosition clockEnable,
    const DataPosition clockPulse,
    const DataPosition output,
    const DataPosition parallelLoad,
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
 * @param shiftRegister
 */
extern void avr_piso_shift_register_init(const PisoShiftRegister shiftRegister);

/**
 * @brief Asynchronously load the data
 * 
 * This function is used on shift registers
 * that have the parallel load port.
 * PL port will be set LOW and then back
 * HIGH after waitTime has passed.
 * 
 * @param shiftRegister 
 */
extern void avr_piso_shift_register_parallel_load(const PisoShiftRegister shiftRegister);

/**
 * @brief Shift next bit
 * 
 * This function shifts next bit from the PISO shift register.
 * It just makes the clockPulse HIGH and then LOW.
 * 
 * @param shiftRegister 
 */
extern void avr_piso_shift_register_shift(const PisoShiftRegister shiftRegister);

/**
 * @brief Read current bit
 * 
 * This function gets the data from the output.
 * It will return 0 for LOW or 1 for HIGH
 * 
 * @note You can read the whole byte using @see avr_piso_shift_register_read_byte
 * 
 * @param shiftRegister 
 * @return true 
 * @return false 
 */
extern bool avr_piso_shift_register_read_bit(const PisoShiftRegister shiftRegister);

/**
 * @brief Read byte from the shift register
 * 
 * This function gets byte from the output.
 * The first value read goes to the LSB.
 * 
 * @note You can read one bit using @see avr_piso_shift_register_read_bit
 * 
 * @param shiftRegister 
 * @return byte 
 */
extern byte avr_piso_shift_register_read_byte(const PisoShiftRegister shiftRegister);

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
extern const SipoShiftRegister avr_sipo_shift_register_create(
    const DataPosition clockEnable, // SRCLR
    const DataPosition clockPulse, // SRCLK
    const DataPosition input, // SER
    const DataPosition outputEnable, // OE
    const DataPosition pushOutput, // RCLK
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
 * @param shiftRegister
 */
extern void avr_sipo_shift_register_init(const SipoShiftRegister shiftRegister);

/**
 * @brief Shifts data by one position.
 * 
 * This function shifts next bit from the PISO shift register.
 * It just makes the clockPulse HIGH and then LOW.
 * 
 * @param shiftRegister 
 */
extern void avr_sipo_shift_register_shift(const SipoShiftRegister shiftRegister);

/**
 * @brief Write one bit to the shift register.
 * 
 * This function writes one bit to the shift register.
 * Shift function is also called to save the data.
 * 
 * @note You can read the whole byte using @see avr_sipo_shift_register_write_byte
 * 
 * @param shiftRegister 
 * @param data 
 * @param position 
 */
extern void avr_sipo_shift_register_write_bit(const SipoShiftRegister shiftRegister, byte data, int position);

/**
 * @brief Write whole byte to the shift register.
 * 
 * This function writes whole byte to the shift register.
 * The first written bit will be the LSB.
 * 
 * @note You can write only one bit using @see avr_sipo_shift_register_write_bit
 * 
 * @param shiftRegister 
 * @param data 
 */
extern void avr_sipo_shift_register_write_byte(const SipoShiftRegister shiftRegister, byte data);

/**
 * @brief Enable output DataPosition
 * 
 * This function enables the output so the shift register
 * outputs the data shifted in it.
 * 
 * @param shiftRegister 
 */
extern void avr_sipo_shift_register_enable_output(const SipoShiftRegister shiftRegister);

/**
 * @brief Disable output DataPosition
 * 
 * This function disables the output so the shift register
 * doesn't output anything.
 * 
 * @param shiftRegister 
 */
extern void avr_sipo_shift_register_disable_output(const SipoShiftRegister shiftRegister);

/**
 * @brief Psuh data to output
 * 
 * This function pushes the data from the shift register
 * to the storage register. That means the data you shift
 * in will be set only after you call this function.
 * 
 * @param shiftRegister 
 */
extern void avr_sipo_shift_register_push_data_to_output(const SipoShiftRegister shiftRegister);

/**
 * @brief Disable and enable clock to reset the SR value
 * 
 * This funciton disables the clock, then waits a bit
 * and enables the clock. Doing that the register will
 * be reset.
 * 
 * @param shiftRegister 
 */
extern void avr_sipo_shift_register_reset(const SipoShiftRegister shiftRegister);

#endif