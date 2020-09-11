# 1 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/main.c"
# 1 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/main.c"
# 1 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h" 1
# 28 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
typedef void* ShiftRegisterHandle;
typedef uint8_t bool;
typedef uint8_t byte;
# 47 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
typedef struct {
    volatile byte* ddr;
    volatile byte* port;
    volatile byte* pin;
    byte position;
} DataPosition;
# 64 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern const DataPosition* data_position_create(volatile byte* ddr, volatile byte* port, volatile byte* pin, byte position);






extern void data_position_destroy(const DataPosition* position);
# 80 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern bool data_position_get_pin(const DataPosition* position);
# 91 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void data_position_set_port(const DataPosition* position);
# 102 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void data_position_reset_port(const DataPosition* position);
# 111 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void data_position_set_ddr(const DataPosition* position);
# 120 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void data_position_reset_ddr(const DataPosition* position);
# 137 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_shift_register_clock_pulse(ShiftRegisterHandle shiftRegisterHandle);
# 152 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_shift_register_enable_clock(ShiftRegisterHandle shiftRegisterHandle);
# 164 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_shift_register_disable_clock(ShiftRegisterHandle shiftRegisterHandle);
# 190 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern ShiftRegisterHandle avr_piso_shift_register_create(
    const DataPosition clockEnable,
    const DataPosition clockPulse,
    const DataPosition output,
    const DataPosition parallelLoad,
    int waitTime
);
# 208 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_piso_shift_register_init(ShiftRegisterHandle shiftRegisterHandle);






extern void avr_piso_shift_register_destroy(ShiftRegisterHandle shiftRegisterHandle);
# 227 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_piso_shift_register_parallel_load(ShiftRegisterHandle shiftRegisterHandle);
# 237 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_piso_shift_register_shift(ShiftRegisterHandle shiftRegisterHandle);
# 251 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern bool avr_piso_shift_register_read_bit(ShiftRegisterHandle shiftRegisterHandle);
# 264 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern byte avr_piso_shift_register_read_byte(ShiftRegisterHandle shiftRegisterHandle);
# 291 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern ShiftRegisterHandle avr_sipo_shift_register_create(
    const DataPosition clockEnable,
    const DataPosition clockPulse,
    const DataPosition input,
    const DataPosition outputEnable,
    const DataPosition pushOutput,
    int waitTime
);
# 310 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_sipo_shift_register_init(ShiftRegisterHandle shiftRegisterHandle);






extern void avr_sipo_shift_register_destroy(ShiftRegisterHandle shiftRegisterHandle);
# 327 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_sipo_shift_register_shift(ShiftRegisterHandle shiftRegisterHandle);
# 341 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_sipo_shift_register_write_bit(ShiftRegisterHandle shiftRegisterHandle, byte data, int position);
# 354 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_sipo_shift_register_write_byte(ShiftRegisterHandle shiftRegisterHandle, byte data);
# 364 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_sipo_shift_register_enable_output(ShiftRegisterHandle shiftRegisterHandle);
# 374 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_sipo_shift_register_disable_output(ShiftRegisterHandle shiftRegisterHandle);
# 385 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_sipo_shift_register_push_data_to_output(ShiftRegisterHandle shiftRegisterHandle);
# 396 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/../src/sr/seduce.h"
extern void avr_sipo_shift_register_reset(ShiftRegisterHandle shiftRegisterHandle);
# 2 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/main.c" 2
# 1 "/usr/avr/include/util/delay.h" 1 3
# 44 "/usr/avr/include/util/delay.h" 3
# 1 "/usr/avr/include/inttypes.h" 1 3
# 37 "/usr/avr/include/inttypes.h" 3
# 1 "/usr/lib/gcc/avr/10.2.0/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/avr/10.2.0/include/stdint.h" 3 4
# 1 "/usr/avr/include/stdint.h" 1 3 4
# 125 "/usr/avr/include/stdint.h" 3 4

# 125 "/usr/avr/include/stdint.h" 3 4
typedef signed int int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
typedef signed int int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));

typedef signed int int64_t __attribute__((__mode__(__DI__)));
typedef unsigned int uint64_t __attribute__((__mode__(__DI__)));
# 146 "/usr/avr/include/stdint.h" 3 4
typedef int16_t intptr_t;




typedef uint16_t uintptr_t;
# 163 "/usr/avr/include/stdint.h" 3 4
typedef int8_t int_least8_t;




typedef uint8_t uint_least8_t;




typedef int16_t int_least16_t;




typedef uint16_t uint_least16_t;




typedef int32_t int_least32_t;




typedef uint32_t uint_least32_t;







typedef int64_t int_least64_t;






typedef uint64_t uint_least64_t;
# 217 "/usr/avr/include/stdint.h" 3 4
typedef int8_t int_fast8_t;




typedef uint8_t uint_fast8_t;




typedef int16_t int_fast16_t;




typedef uint16_t uint_fast16_t;




typedef int32_t int_fast32_t;




typedef uint32_t uint_fast32_t;







typedef int64_t int_fast64_t;






typedef uint64_t uint_fast64_t;
# 277 "/usr/avr/include/stdint.h" 3 4
typedef int64_t intmax_t;




typedef uint64_t uintmax_t;
# 10 "/usr/lib/gcc/avr/10.2.0/include/stdint.h" 2 3 4
# 38 "/usr/avr/include/inttypes.h" 2 3
# 77 "/usr/avr/include/inttypes.h" 3
typedef int32_t int_farptr_t;



typedef uint32_t uint_farptr_t;
# 45 "/usr/avr/include/util/delay.h" 2 3
# 1 "/usr/avr/include/util/delay_basic.h" 1 3
# 40 "/usr/avr/include/util/delay_basic.h" 3
static __inline__ void _delay_loop_1(uint8_t __count) __attribute__((__always_inline__));
static __inline__ void _delay_loop_2(uint16_t __count) __attribute__((__always_inline__));
# 80 "/usr/avr/include/util/delay_basic.h" 3
void
_delay_loop_1(uint8_t __count)
{
 __asm__ volatile (
  "1: dec %0" "\n\t"
  "brne 1b"
  : "=r" (__count)
  : "0" (__count)
 );
}
# 102 "/usr/avr/include/util/delay_basic.h" 3
void
_delay_loop_2(uint16_t __count)
{
 __asm__ volatile (
  "1: sbiw %0,1" "\n\t"
  "brne 1b"
  : "=w" (__count)
  : "0" (__count)
 );
}
# 46 "/usr/avr/include/util/delay.h" 2 3
# 1 "/usr/avr/include/math.h" 1 3
# 127 "/usr/avr/include/math.h" 3
extern double cos(double __x) __attribute__((__const__));





extern double sin(double __x) __attribute__((__const__));





extern double tan(double __x) __attribute__((__const__));






extern double fabs(double __x) __attribute__((__const__));






extern double fmod(double __x, double __y) __attribute__((__const__));
# 168 "/usr/avr/include/math.h" 3
extern double modf(double __x, double *__iptr);


extern float modff (float __x, float *__iptr);




extern double sqrt(double __x) __attribute__((__const__));


extern float sqrtf (float) __attribute__((__const__));




extern double cbrt(double __x) __attribute__((__const__));
# 195 "/usr/avr/include/math.h" 3
extern double hypot (double __x, double __y) __attribute__((__const__));







extern double square(double __x) __attribute__((__const__));






extern double floor(double __x) __attribute__((__const__));






extern double ceil(double __x) __attribute__((__const__));
# 235 "/usr/avr/include/math.h" 3
extern double frexp(double __x, int *__pexp);







extern double ldexp(double __x, int __exp) __attribute__((__const__));





extern double exp(double __x) __attribute__((__const__));





extern double cosh(double __x) __attribute__((__const__));





extern double sinh(double __x) __attribute__((__const__));





extern double tanh(double __x) __attribute__((__const__));







extern double acos(double __x) __attribute__((__const__));







extern double asin(double __x) __attribute__((__const__));






extern double atan(double __x) __attribute__((__const__));
# 299 "/usr/avr/include/math.h" 3
extern double atan2(double __y, double __x) __attribute__((__const__));





extern double log(double __x) __attribute__((__const__));





extern double log10(double __x) __attribute__((__const__));





extern double pow(double __x, double __y) __attribute__((__const__));






extern int isnan(double __x) __attribute__((__const__));
# 334 "/usr/avr/include/math.h" 3
extern int isinf(double __x) __attribute__((__const__));






__attribute__((__const__)) static inline int isfinite (double __x)
{
    unsigned char __exp;
    __asm__ (
 "mov	%0, %C1		\n\t"
 "lsl	%0		\n\t"
 "mov	%0, %D1		\n\t"
 "rol	%0		"
 : "=r" (__exp)
 : "r" (__x) );
    return __exp != 0xff;
}






__attribute__((__const__)) static inline double copysign (double __x, double __y)
{
    __asm__ (
 "bst	%D2, 7	\n\t"
 "bld	%D0, 7	"
 : "=r" (__x)
 : "0" (__x), "r" (__y) );
    return __x;
}
# 377 "/usr/avr/include/math.h" 3
extern int signbit (double __x) __attribute__((__const__));






extern double fdim (double __x, double __y) __attribute__((__const__));
# 393 "/usr/avr/include/math.h" 3
extern double fma (double __x, double __y, double __z) __attribute__((__const__));







extern double fmax (double __x, double __y) __attribute__((__const__));







extern double fmin (double __x, double __y) __attribute__((__const__));






extern double trunc (double __x) __attribute__((__const__));
# 427 "/usr/avr/include/math.h" 3
extern double round (double __x) __attribute__((__const__));
# 440 "/usr/avr/include/math.h" 3
extern long lround (double __x) __attribute__((__const__));
# 454 "/usr/avr/include/math.h" 3
extern long lrint (double __x) __attribute__((__const__));
# 47 "/usr/avr/include/util/delay.h" 2 3
# 86 "/usr/avr/include/util/delay.h" 3
static __inline__ void _delay_us(double __us) __attribute__((__always_inline__));
static __inline__ void _delay_ms(double __ms) __attribute__((__always_inline__));
# 165 "/usr/avr/include/util/delay.h" 3
void
_delay_ms(double __ms)
{
 double __tmp ;
# 190 "/usr/avr/include/util/delay.h" 3
 uint16_t __ticks;
 __tmp = (() / 4e3) * __ms;
 if (__tmp < 1.0)
  __ticks = 1;
 else if (__tmp > 65535)
 {

  __ticks = (uint16_t) (__ms * 10.0);
  while(__ticks)
  {

   _delay_loop_2((() / 4e3) / 10);
   __ticks --;
  }
  return;
 }
 else
  __ticks = (uint16_t)__tmp;
 _delay_loop_2(__ticks);

}
# 254 "/usr/avr/include/util/delay.h" 3
void
_delay_us(double __us)
{
 double __tmp ;
# 279 "/usr/avr/include/util/delay.h" 3
 uint8_t __ticks;
 double __tmp2 ;
 __tmp = (() / 3e6) * __us;
 __tmp2 = (() / 4e6) * __us;
 if (__tmp < 1.0)
  __ticks = 1;
 else if (__tmp2 > 65535)
 {
  _delay_ms(__us / 1000.0);
 }
 else if (__tmp > 255)
 {
  uint16_t __ticks=(uint16_t)__tmp2;
  _delay_loop_2(__ticks);
  return;
 }
 else
  __ticks = (uint8_t)__tmp;
 _delay_loop_1(__ticks);

}
# 3 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/main.c" 2


# 4 "/home/ruther/Documents/MyProjects/MCU/avr-shift-registers/simavr/main.c"
int main(void)
{

    ShiftRegisterHandle sipoSrHandle = avr_sipo_shift_register_create(
        data_position_create(&DDRB, &PORTB, &PINB, 0),
        data_position_create(&DDRB, &PORTB, &PINB, 1),
        data_position_create(&DDRB, &PORTB, &PINB, 2),
        data_position_create(&DDRB, &PORTB, &PINB, 3),
        data_position_create(&DDRB, &PORTB, &PINB, 4),
        1
    );

    avr_sipo_shift_register_init(sipoSrHandle);

    avr_sipo_shift_register_write_byte(sipoSrHandle, 0b11001111);
    avr_sipo_shift_register_push_data_to_output(sipoSrHandle);
    avr_sipo_shift_register_enable_output(sipoSrHandle);



    _delay_ms(100);

    ShiftRegisterHandle pisoSrHandle = avr_piso_shift_register_create(
        data_position_create(&DDRC, &PORTC, &PINC, 0),
        data_position_create(&DDRC, &PORTC, &PINC, 1),
        data_position_create(&DDRC, &PORTC, &PINC, 2),
        data_position_create(&DDRC, &PORTC, &PINC, 3),
        1
    );

    avr_piso_shift_register_parallel_load();
    byte read = avr_piso_shift_register_read_byte();
}
